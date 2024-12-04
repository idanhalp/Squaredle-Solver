import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import SquaredleSolver
import 'https://cloudflare-cors-anywhere.oranhero.workers.dev/?https://squaredle.app/api/today-puzzle-config.js' as Script
import "GetPuzzle.js" as Puzzle

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    MainModule {
        id: mainModule
    }

    function showIndices(word)
    {
        mainModule.showIndices(word)
        timer.start()
    }

    Flickable {

        id: scroller
        anchors.fill: parent
        contentHeight: main.height
        contentWidth: main.width
        GridLayout {
            id: main
            height: scroller.width > 600 ? scroller.height : children.length * 800
            width: scroller.width > 600 ? scroller.width : grid.width

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
                    contentHeight: result.contentHeight + 200
                    clip: true
                    Text {
                        id: wordsCount

                        anchors {
                            top: parent.top
                            left: parent.left
                            leftMargin: 10
                        }

                        text: "Found " + mainModule.resultsModel.totalWordsCount + " words"
                        color: mainModule.resultsModel.totalWordsCount > 0 ? "black" : "transparent"
                        font.pixelSize: 20
                        font.bold: true
                    }
                    ListView {
                        id: result

                        anchors {
                            top: wordsCount.bottom
                            bottom: parent.bottom
                            left: parent.left
                            topMargin: 15
                            leftMargin: 10
                        }

                        width: flick.width
                        model: delegateModel
                        spacing: 25
                        interactive: false
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
                        color: "red"
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

                    onClicked: sendIdPopup.open()
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

                GridView {

                    id: grid
                    width: 500
                    height: 500
                    cellHeight: grid.height / mainModule.gridModel.rows
                    cellWidth: grid.width / mainModule.gridModel.columns

                    interactive: false

                    model: mainModule.gridModel
                    delegate: Rectangle {
                        width: 400 / mainModule.gridModel.rows
                        height: 400 / mainModule.gridModel.columns
                        color: mainModule.gridModel.validIndices[index] ? "grey" : "red"

                        TextField {
                            anchors.centerIn: parent
                            maximumLength: 1
                            color: "black"
                            font.pixelSize: 26
                            text: letter == ' ' ? '' : letter
                            onTextChanged: {
                                mainModule.resultsModel.erasePreviousResults()
                                mainModule.gridModel.updateGrid(text[0], index)
                                if (text.length === 1) {
                                    nextItemInFocusChain().forceActiveFocus()
                                }
                            }
                            background: Rectangle {
                                color: "transparent"
                            }
                        }
                    }
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



    Timer {
        id: timer
        property int i: 0
        property int prevIndex: i
        interval: 500
        repeat: true
        onTriggered: {
            if (i === mainModule.resultsModel.wordIndices.length)
            {
                grid.itemAtIndex(mainModule.resultsModel.wordIndices[prevIndex]).color = "grey";
                i = 0;
                prevIndex = i;
                timer.running = false;
            }
            else {
                grid.itemAtIndex(mainModule.resultsModel.wordIndices[prevIndex]).color = "grey";
                grid.itemAtIndex(mainModule.resultsModel.wordIndices[i]).color = "green";
                prevIndex = i;
                i++;
            }
        }
    }

    Popup {
        id: sendIdPopup
        width: 550
        height: 250

        anchors.centerIn: parent
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        Rectangle {
            width: parent.width
            height: parent.height
            color: "#FFFFC5"
            border.color: "black"

            Text {
                id: link
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 5
                }

                text: "https://squaredle.app/?puzzle="

                font {
                    bold: true
                    pixelSize: 20
                }
            }

            TextField {
                id: keyInput
                anchors {
                    left: link.right
                    verticalCenter: link.verticalCenter
                }

                color: "black"
            }

            Button {
                id: sendId
                anchors {
                    top: link.bottom
                    topMargin: 15
                    horizontalCenter: parent.horizontalCenter
                }

                text: "Submit"

                onClicked: {
                    if (keyInput.text !== '') {
                        mainModule.resultsModel.erasePreviousResults()
                        Puzzle.getPuzzleById(keyInput.text)
                        sendIdPopup.close()
                    }
                }
            }

        }
    }

    Popup {
        id: errorPopup

        width: 450
        height: 250

        anchors.centerIn: parent
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        Rectangle {
            width: parent.width
            height: parent.height
            color: "red"
            border.color: "black"

            Text {
                text: "Error: Invalid puzzle key!"
                anchors.centerIn: parent

                font {
                    bold: true
                    pixelSize: 30
                }
            }
        }
    }
}
