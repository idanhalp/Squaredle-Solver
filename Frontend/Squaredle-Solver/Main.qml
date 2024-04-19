import QtQuick
import QtQuick.Controls
import GridModel

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    GridView {

        anchors.centerIn: parent
        id: grid
        width: 500
        height: 500
        cellHeight: grid.height / 4
        cellWidth: grid.width / 4

        model: GridModel
        delegate: Rectangle {
            width: 100
            height: 100
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
                validator: RegularExpressionValidator{
                    regularExpression: /^[a-z-]+$/ // Only allows a-z and -
                }

            }
        }
    }

    Button {
        anchors {
            top: grid.bottom
            horizontalCenter: grid.horizontalCenter

        }

        text: "Solve!"
        onClicked: GridModel.solve()

    }
}
