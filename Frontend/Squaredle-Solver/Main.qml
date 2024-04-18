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

            TextInput {
                anchors.centerIn: parent
                text: " "
                color: "black"
                font.pixelSize: 26

                onAccepted: console.log(text, index)
            }
        }
    }
}
