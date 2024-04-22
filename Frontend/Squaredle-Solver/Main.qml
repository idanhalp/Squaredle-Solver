import QtQuick
import QtQuick.Controls
import SquaredleSolver

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    MainModule {
        id: mainModule
    }

    Text {
        anchors {
            top: slider.bottom
            horizontalCenter: grid.horizontalCenter
            topMargin: 10
        }

        text: "Grid size is " + mainModule.gridModel.rows + " X " + mainModule.gridModel.columns
        font.pixelSize: 20
        color: "black"
    }

    Slider {
        id: slider

        anchors {
            top: parent.top
            horizontalCenter: grid.horizontalCenter
            topMargin: 20
        }

        from: 3
        value: 4
        to: 6
        stepSize: 1
        snapMode: Slider.SnapAlways

        onMoved: mainModule.gridModel.resizeGrid(value, value);
    }

    GridView {

        anchors.centerIn: parent
        id: grid
        width: 500
        height: 500
        cellHeight: grid.height / mainModule.gridModel.rows
        cellWidth: grid.width / mainModule.gridModel.columns

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
        anchors {
            top: grid.bottom
            horizontalCenter: grid.horizontalCenter

        }

        enabled: !mainModule.gridModel.isNotValidInput

        text: "Solve!"
        onClicked: mainModule.solve()

    }

    Text {
        anchors {
            top: solve.bottom
            horizontalCenter: grid.horizontalCenter
            topMargin: 15
        }

        text: "Only a-z and " + mainModule.gridModel.emptyCellChar.toString() + " are allowed"
        font.pixelSize: 20
        color: "red"

        visible: mainModule.gridModel.isNotValidInput
    }

    Component {
        id: sectionHeading
        Rectangle {
            width: ListView.view.width
            height: childrenRect.height
            color: "lightsteelblue"

            required property string section

            Text {
                text: parent.section + " letters"
                font.bold: true
                font.pixelSize: 16
            }
        }
    }

    ListView {

        height: 1000
        width: 500

        model: mainModule.resultsModel
        delegate: Text {
            text: model.word
            color: "black"
            font.pixelSize: 15
        }

        section.property: "length"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading

    }

}
