import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.12

import biblebrainring.namespace 1.0

Item {
    anchors.fill: parent

    Text {
        text: providerQml.currentHttpServerHostPort
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.1
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        font.weight: Font.ExtraBold
    }

    RowLayout{
        id: rowLayoutEnviromentSetup
        anchors.centerIn: parent

        Button{
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            text: "Load questions"
            onClicked: {
                fileDialog.open()
            }
        }
        Button{
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            text: "Wifi Bulb settings"
            onClicked: {
                providerQml.onQmlButtonClicked(BibleBrainRing.ButtonAddBulb)
            }
        }
        Button{
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            text: "Custom Http server"
            onClicked: {
                providerQml.onQmlButtonClicked(BibleBrainRing.ButtonRunCustomServer)
            }
        }
        CheckBox{
            width: parent.width
            height: parent.height / columnButtons.count
            text: "Use referee"
            checked: providerQml.useReferee
        }
    }
    Text {
        id: textPreview
        width: parent.width / 2
        height: parent.height / 4
        anchors.top: rowLayoutEnviromentSetup.bottom
        anchors.topMargin: rowLayoutEnviromentSetup.height
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: anchors.topMargin
        clip: true
        text: ""
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            textPreview.text = managerQuestionsQml.loadQuestions(fileDialog.fileUrls);
        }
    }
}
