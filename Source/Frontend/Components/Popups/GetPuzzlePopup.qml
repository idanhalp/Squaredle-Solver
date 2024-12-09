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

    property bool isLoading: false

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#FFFFC5"
        border.color: "black"

        Text {
            id: textExplanation

            anchors {
                horizontalCenter: isLoading ? undefined : parent.horizontalCenter
                top: isLoading ? undefined : parent.top
                topMargin: isLoading ? 0 : 20
                centerIn: isLoading ? parent : undefined
            }

            text: isLoading ? "Loading puzzle..." : "Insert ID (e.g waffle):"

            font {
                bold: true
                pixelSize: 20
            }
        }

        TextField {
            id: keyInput

            visible: !isLoading

            anchors {
                horizontalCenter: parent.horizontalCenter
                top: textExplanation.bottom
                topMargin: 20
            }

            color: "black"
        }

        Button {
            id: sendId

            visible: !isLoading

            anchors {
                top: keyInput.bottom
                topMargin: 15
                horizontalCenter: parent.horizontalCenter
            }

            text: "Submit"

            onClicked: {
                if (keyInput.text !== '') {
                    mainModule.resultsModel.erasePreviousResults()

                    isLoading = true
                    Puzzle.getPuzzleById(keyInput.text) // `isLoading` is set to false once this function terminates.

                    keyInput.clear()
                }
            }
        }

    }
}
