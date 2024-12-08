import QtQuick 2.15

Item {

    property alias result: result

    Text {
        id: wordsCount

        anchors {
            top: parent.top
            topMargin: 10
            left: parent.left
            leftMargin: 10
        }

        text: "Found " + mainModule.resultsModel.totalWordsCount + (mainModule.resultsModel.totalWordsCount === 1 ? " word" : " words")
        color: mainModule.resultsModel.totalWordsCount > 0 ? "black" : "transparent"
        font.pixelSize: 30
        font.bold: true
    }

    ListView {
        id: result

        anchors {
            top: wordsCount.bottom
            bottom: parent.bottom
            left: parent.left
            topMargin: 15
            leftMargin: 10
        }

        width: flick.width
        model: delegateModel
        spacing: 25
        interactive: false
    }

}
