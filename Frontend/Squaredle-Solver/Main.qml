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

        ListView {
            id: results
            height: 500
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            width: 500
            model: delegateModel
            spacing: 25
            interactive: false
        }

        DelegateModel {
            id: delegateModel

            model: mainModule.resultsModel

            delegate: ColumnLayout {
                width: 500

                spacing: 5
                Text {
                    text: length + " letters"
                    color: "red"
                    font.pixelSize: 30
                }

                GridLayout {
                    width: 300
                    columns: 5
                    Repeater {
                        model: words

                        Text {
                            text: words[index]
                            font.pixelSize: 20
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
                text: "Grid size is " + mainModule.gridModel.rows + " X " + mainModule.gridModel.columns
                font.pixelSize: 20
                color: "black"
            }

            Slider {
                id: slider

                Layout.alignment: Qt.AlignHCenter
                from: 3
                value: 4
                to: 6
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
                    color: "grey"

                    TextField {
                        anchors.centerIn: parent
                        maximumLength: 1
                        color: "black"
                        font.pixelSize: 26
                        onTextChanged: mainModule.gridModel.updateGrid(text[0], index)
                        background: Rectangle {
                            color: "transparent"
                        }
                    }
                }
            }

            Button {

                id: solve

                Layout.alignment: Qt.AlignHCenter
                enabled: !mainModule.gridModel.isNotValidInput

                text: "Solve!"
                onClicked: mainModule.solve()

            }

            Text {

                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 15
                text: "Only a-z and " + mainModule.gridModel.emptyCellChar.toString() + " are allowed"
                font.pixelSize: 20
                color: mainModule.gridModel.isNotValidInput ? "red" : "transparent"
            }


        }
    }

}
