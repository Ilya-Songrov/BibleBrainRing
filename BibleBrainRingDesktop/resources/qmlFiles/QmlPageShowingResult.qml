import QtQuick 2.15
import QtQuick.Controls 2.15

import "Components" as MyComponents
import ListModelQml 1.0

Item {
    anchors.fill: parent

    Rectangle{
        anchors.fill: parent
        color: "yellow"
        opacity: 0.5
    }
    Text {
        id: name
        anchors.centerIn: parent
        text: qsTr("Show result: 0 : 0")
    }

}
