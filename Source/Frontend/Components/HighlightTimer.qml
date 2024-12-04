import QtQuick 2.15

Timer {
    id: timer
    property int i: 0
    property int prevIndex: i
    interval: 500
    repeat: true
    onTriggered: {
        if (i === mainModule.resultsModel.wordIndices.length)
        {
            gameGrid.itemAtIndex(mainModule.resultsModel.wordIndices[prevIndex]).color = "grey";
            i = 0;
            prevIndex = i;
            timer.running = false;
        }
        else {
            gameGrid.itemAtIndex(mainModule.resultsModel.wordIndices[prevIndex]).color = "grey";
            gameGrid.itemAtIndex(mainModule.resultsModel.wordIndices[i]).color = "green";
            prevIndex = i;
            i++;
        }
    }
}
