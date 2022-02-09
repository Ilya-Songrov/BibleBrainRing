import QtQuick 2.15
import QtQuick.Controls 2.15

import "Components" as MyComponents
import ListModelQml 1.0


Item {
    anchors.fill: parent

    MyComponents.QmlComponentListView{
        id: listViewTeamsGameSession
        width: parent.width * 0.8
        height: parent.height * 0.15
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.05
        anchors.horizontalCenter: parent.horizontalCenter
        listModelObj: ListModel {
            listTeams: listTeamsInGameSession
        }
        onMoveTeamToAnotherList: listTeamsInGameSession.moveTeamToAnotherList(index)
    }
    MyComponents.QmlComponentListView{
        id: listViewTeamsInBattle
        width: listViewTeamsGameSession.width
        height: listViewTeamsGameSession.height
        anchors.top: listViewTeamsGameSession.bottom
        anchors.topMargin: listViewTeamsGameSession.height * 0.1
        anchors.horizontalCenter: parent.horizontalCenter
        listModelObj: ListModel {
            listTeams: listTeamsInBattleQml
        }
        onMoveTeamToAnotherList: listTeamsInBattleQml.moveTeamToAnotherList(index)
    }

    MyComponents.QmlComponentLittleScreen{
        width: parent.width * 0.7
        height: parent.height * 0.6
        anchors.top: listViewTeamsInBattle.bottom
        anchors.topMargin: listViewTeamsInBattle.height * 0.1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height * 0.05
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
