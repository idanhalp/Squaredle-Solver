import QtQuick 2.15
import QtQuick.Controls
import "../../GetPuzzle.js" as Puzzle

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
