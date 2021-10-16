import QtQuick 2.15
import QtQuick.Controls 2.15

import biblebrainring.namespace 1.0

Item {
    anchors.fill: parent

    Column{
        width: parent.width / 2
        height: parent.height / 2
        anchors.centerIn: parent
        spacing: 5

        Button{
            width: parent.width
            height: parent.height / 3
            text: "Start Server Wifi"
            onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.ButtonStartServerWifi)
        }
        Button{
            width: parent.width
            height: parent.height / 3
            text: "Start Server Bluetooth"
            onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.ButtonStartServerBluetooth)
        }
        Button{
            width: parent.width
            height: parent.height / 3
            text: "Start Without Server"
            onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.ButtonStartServerBluetooth)
        }
    }

}
