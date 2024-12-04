import QtQuick 2.15


Item {

    property alias errorPopup: errorPopup
    property alias sendIdPopup: sendIdPopup

    ErrorPopup {
        id: errorPopup

        anchors.centerIn: parent
    }

    GetPuzzlePopup {
        id: sendIdPopup

        anchors.centerIn: parent
    }
}
