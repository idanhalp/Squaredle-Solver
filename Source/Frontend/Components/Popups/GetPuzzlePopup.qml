import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts
import "../../GetPuzzle.js" as Puzzle

Popup {
    id: sendIdPopup
    width: 400
    height: 200

    anchors.centerIn: parent
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#FFFFC5"
        border.color: "black"

        Text {
            id: textExplanation

            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 20
            }

            text: "Insert ID (e.g waffle):"

            font {
                bold: true
                pixelSize: 20
            }
        }

        TextField {
            id: keyInput

            anchors {
                horizontalCenter: parent.horizontalCenter
                top: textExplanation.bottom
                topMargin: 20
            }

            color: "black"
        }

        Button {
            id: sendId
            anchors {
                top: keyInput.bottom
                topMargin: 15
                horizontalCenter: parent.horizontalCenter
            }

            text: "Submit"

            onClicked: {
                if (keyInput.text !== '') {
                    mainModule.resultsModel.erasePreviousResults()
                    Puzzle.getPuzzleById(keyInput.text)
                    keyInput.clear()
                    sendIdPopup.close()
                }
            }
        }

    }
}
