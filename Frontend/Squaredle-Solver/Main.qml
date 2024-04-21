import QtQuick
import QtQuick.Controls
import GridModel

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    Text {
        anchors {
            top: slider.bottom
            horizontalCenter: grid.horizontalCenter
            topMargin: 10
        }

        text: "Grid size is " + GridModel.rows + " X " + GridModel.columns
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

        onMoved: GridModel.resizeGrid(value, value);
    }

    GridView {

        anchors.centerIn: parent
        id: grid
        width: 500
        height: 500
        cellHeight: grid.height / GridModel.rows
        cellWidth: grid.width / GridModel.columns

        model: GridModel
        delegate: Rectangle {
            width: 400 / GridModel.rows
            height: 400 / GridModel.columns
            color: "grey"

            TextField {
                anchors.centerIn: parent
                maximumLength: 1
                color: "black"
                font.pixelSize: 26
                onTextChanged: GridModel.updateGrid(text[0], index)
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

        enabled: !GridModel.isNotValidInput

        text: "Solve!"
        onClicked: GridModel.solve()

    }

    Text {
        anchors {
            top: solve.bottom
            horizontalCenter: grid.horizontalCenter
            topMargin: 15
        }

        text: "Only a-z and " + GridModel.emptyCellChar.toString() + " are allowed"
        font.pixelSize: 20
        color: "red"

        visible: GridModel.isNotValidInput
    }

}
