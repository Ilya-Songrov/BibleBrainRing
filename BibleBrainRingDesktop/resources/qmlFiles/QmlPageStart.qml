import QtQuick 2.15
import QtQuick.Controls 2.15

import biblebrainring.namespace 1.0

Item {
    anchors.fill: parent

    Column{
        id: columnButtons
        width: parent.width / 2
        height: parent.height / 2
        anchors.centerIn: parent
        spacing: 5

        Button{
            width: parent.width
            height: parent.height / columnButtons.count
            text: "Start Wifi server"
            onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.ButtonStartServerWifi)
            enabled: false
        }
        Button{
            width: parent.width
            height: parent.height / columnButtons.count
            text: "Start Bluetooth server"
            onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.ButtonStartServerBluetooth)
            enabled: false
        }
        Button{
            width: parent.width
            height: parent.height / columnButtons.count
            text: "Start Http server"
            onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.ButtonStartServerHttp)
            enabled: false // TODO: Delete me
        }
        Button{
            width: parent.width
            height: parent.height / columnButtons.count
            text: "Start Wifi client"
            onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.ButtonStartClientWifi)
            enabled: false
        }
        Button{
            width: parent.width
            height: parent.height / columnButtons.count
            text: "Start Bluetooth client"
            onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.ButtonStartClientBluetooth)
            enabled: false
        }
        Button{
            width: parent.width
            height: parent.height / columnButtons.count
            text: "Start only program"
            onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.ButtonStartOnlyProgram)
        }
    }

}
