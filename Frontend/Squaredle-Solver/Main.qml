import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import SquaredleSolver

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    MainModule {
        id: mainModule
    }


    RowLayout {

        anchors.fill: parent
        ColumnLayout {
            Layout.fillHeight: true
            spacing: 20

            Flickable {
                interactive: true
                Layout.fillHeight: true
                width: 600
                contentHeight: result.contentHeight + 200
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

                    width: 600
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
                        }
                    }
                }
            }
        }

        ColumnLayout {

            Layout.alignment: Qt.AlignCenter
            Layout.fillHeight: true

            spacing: 20

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
                value: 4
                to: 10
                stepSize: 1
                snapMode: Slider.SnapAlways

                onMoved: mainModule.gridModel.resizeGrid(value, value);
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
                    onClicked: mainModule.gridModel.clearGrid()
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
