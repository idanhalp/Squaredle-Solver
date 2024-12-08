import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

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
        color: mainModule.gridModel.validIndices[index] ? "#D3D3D3" : "red"
        radius: 10

        TextField {
            anchors.fill: parent
            horizontalAlignment: TextField.AlignHCenter
            maximumLength: 1
            color: "black"
            font.pixelSize: 26
            text: letter == ' ' ? '' : letter
            onTextChanged: {
                mainModule.resultsModel.erasePreviousResults()
                mainModule.gridModel.resetAllErrors()
                mainModule.gridModel.updateGrid(text[0], index)
            }

            validator: RegularExpressionValidator {
                regularExpression: {
                    const re = new RegExp(`^[a-z\\${mainModule.gridModel.emptyCellChar}]+$`);
                    return re;
                }
            }

            background: Rectangle {
                color: "transparent"
            }
        }
    }
}
