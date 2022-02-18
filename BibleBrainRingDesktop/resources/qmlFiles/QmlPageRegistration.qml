import QtQuick 2.15
import QtQuick.Controls 2.15

import "Components" as MyComponents
import ListModelQml 1.0
import biblebrainring.namespace 1.0


Item {
    anchors.fill: parent

    Text {
        text: "Registration"
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.1
        anchors.horizontalCenter: parent.horizontalCenter
        font.bold: true
        font.weight: Font.ExtraBold
    }

    MyComponents.QmlComponentGridView{
        id: gridViewRegistration
        width: parent.width * 0.8
        height: parent.height * 0.73
        anchors.centerIn: parent
        listModelObj: ListModel {
            listTeams: listTeamsRegistrationQml
        }
    }

    MyComponents.QmlComponentHelpBoard{
        id: helpBoard
        width: gridViewRegistration.width
        anchors.top: gridViewRegistration.bottom
        anchors.topMargin: parent.height * 0.01
        anchors.bottom: parent.bottom
        anchors.bottomMargin: anchors.topMargin
        anchors.horizontalCenter: gridViewRegistration.horizontalCenter
        textHelp: qsTr("Select the teams that will take part in the game")
    }

    Button{
        id: buttonAddTeam
        height: helpBoard.height
        anchors.left: helpBoard.right
        anchors.leftMargin: width * 0.1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: helpBoard.anchors.bottomMargin
        visible: providerQml.currentAppMode === BibleBrainRing.AppModeOnlyProgram
        text: "ADD TEAM"
        onClicked: dialogAddTeam.open()
    }

    MyComponents.QmlDialog{
        id: dialogAddTeam
        onAccepted: listTeamsRegistrationQml.addTeam(textFieldNameText, Qt.rgba(Math.random(),Math.random(),Math.random(),1))
    }
}
