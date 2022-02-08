import QtQuick 2.15
import QtQuick.Controls 2.15

import "Components" as MyComponents
import ListModelQml 1.0

Item {
    anchors.fill: parent

    MyComponents.QmlComponentGridView{
        id: gridViewRegistration
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
        listModelObj: ListModel {
            listTeams: listTeamsRegistrationQml
        }
    }

    MyComponents.QmlComponentHelpBoard{
        width: gridViewRegistration.width
        anchors.top: gridViewRegistration.bottom
        anchors.topMargin: parent.height * 0.01
        anchors.bottom: parent.bottom
        anchors.bottomMargin: anchors.topMargin
        anchors.horizontalCenter: gridViewRegistration.horizontalCenter
        textHelp: qsTr("Select the teams that will take part in the game")
    }
}
