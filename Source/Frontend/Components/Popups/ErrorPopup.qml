import QtQuick 2.15
import QtQuick.Controls

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
