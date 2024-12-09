import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import SquaredleSolver
import 'https://cloudflare-cors-anywhere.oranhero.workers.dev/?https://squaredle.app/api/today-puzzle-config.js' as Script
import "Components"
import "Components/Popups"

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    color: "#A0A0A0"

    MainModule {
        id: mainModule
    }

    function showIndices(word)
    {
        mainModule.showIndices(word)
        highlightTimer.start()
    }

    Flickable {

        id: scroller
        anchors.fill: parent
        contentHeight: main.height
        contentWidth: main.width
        GridLayout {
            id: main
            height: scroller.width > 600 ? scroller.height : children.length * 800
            width: scroller.width > 600 ? scroller.width : gameGrid.width

            columns: 2

            states: [
                State {
                    when: root.width <= 600
                    PropertyChanges {target: left; Layout.row: 1}
                    PropertyChanges {target: right; Layout.row: 0}
                },
                State {
                    when: root.width > 600
                    PropertyChanges {target: left; Layout.column: 0}
                    PropertyChanges {target: right; Layout.column: 1}
                }
            ]

            ColumnLayout {
                id: left
                Layout.fillHeight: true
                spacing: 20

                Flickable {
                    id: flick
                    interactive: true
                    Layout.fillHeight: true
                    width: root.width > 600 ? 600 : (0.75 * root.width)
                    contentHeight: results.result.contentHeight + 200
                    clip: true

                    Results {
                        id: results
                        height: flick.contentHeight
                        anchors {
                            top: parent.top
                            left: parent.left
                            leftMargin: 10
                        }
                    }

                }
            }

            DelegateModel {
                id: delegateModel

                model: mainModule.resultsModel

                delegate: ColumnLayout {
                    width: 500

                    spacing: 5
                    Text {
                        text: length + " letters" + " - " + section_count + (section_count == 1 ? " word" : " words")
                        color: length > 0 ? "#00224b" : "transparent"
                        font.pixelSize: 30
                    }

                    GridLayout {
                        width: 300
                        columns: 5
                        columnSpacing: 10
                        Repeater {
                            model: words

                            Text {
                                text: words[index]
                                font.pixelSize: 15

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        scroller.contentY = 0
                                        showIndices(text)
                                    }
                                    hoverEnabled: true
                                    onEntered: color = "green"
                                    onExited: color = "black"
                                }
                            }
                        }
                    }
                }
            }

            ColumnLayout {
                id: right
                Layout.alignment: scroller.width > 600 ? Qt.AlignCenter : Qt.AlignLeft
                Layout.fillWidth: scroller.width <= 600 ? true : false
                Layout.fillHeight: true

                spacing: 20

                Row {
                    Layout.alignment: Qt.AlignHCenter

                    spacing: 15
                    Button {
                        id: today

                        text: "Today's normal puzzle"
                        onClicked: {
                            mainModule.resultsModel.erasePreviousResults()
                            let puzzles = Script.gPuzzleConfig["puzzles"];
                            mainModule.gridModel.fillGrid(puzzles[Object.keys(puzzles)[1]]["board"])
                        }
                    }

                    Button {
                        id: express

                        text: "Today's express puzzle"
                        onClicked: {
                            mainModule.resultsModel.erasePreviousResults()
                            let puzzles = Script.gPuzzleConfig["puzzles"];
                            mainModule.gridModel.fillGrid(puzzles[Object.keys(puzzles)[0]]["board"])
                        }
                    }
                }

                Button {
                    Layout.alignment: Qt.AlignHCenter
                    id: puzzleById

                    text: "Puzzle by id"

                    onClicked: popups.sendIdPopup.open()
                }

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Type " + "\"" + mainModule.gridModel.emptyCellChar + "\"" + " for an empty cell."
                    font.pixelSize: 20
                    color: "red"
                }

                Text {

                    Layout.alignment: Qt.AlignHCenter
                    text: "Grid size is " + mainModule.gridModel.rows + " X " + mainModule.gridModel.columns
                    font.pixelSize: 20
                    color: "black"
                }

                Slider {
                    id: slider

                    Layout.alignment: Qt.AlignHCenter
                    from: 3
                    value: mainModule.gridModel.rows
                    to: 10
                    stepSize: 1
                    snapMode: Slider.SnapAlways

                    onMoved: {
                        mainModule.gridModel.resizeGrid(value, value)
                        mainModule.resultsModel.erasePreviousResults()
                    }
                }

                GameGrid {
                    id: gameGrid
                }

                Row {
                    Layout.alignment: Qt.AlignHCenter
                    spacing: 20
                    Button {

                        id: solve

                        enabled: mainModule.gridModel.isValidInput

                        text: "Solve!"
                        onClicked: mainModule.solve()

                    }

                    Button {
                        id: clear

                        text: "Clear"
                        onClicked: {
                            mainModule.resultsModel.erasePreviousResults()
                            mainModule.gridModel.clearGrid()
                        }
                    }
                }



                Text {

                    Layout.alignment: Qt.AlignHCenter
                    Layout.topMargin: 15
                    text: "Only a-z and " + mainModule.gridModel.emptyCellChar.toString() + " are allowed"
                    font.pixelSize: 20
                    color: !mainModule.gridModel.isValidInput ? "red" : "transparent"
                }
            }
        }
    }

    HighlightTimer {
        id: highlightTimer
    }

    Popups {
        id: popups

        anchors.centerIn: parent
    }
}
