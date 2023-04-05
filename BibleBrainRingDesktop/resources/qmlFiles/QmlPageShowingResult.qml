import QtQuick 2.15
import QtQuick.Controls 2.15

import "Components" as MyComponents
import ListModelQml 1.0
import biblebrainring.namespace 1.0


Item {
    anchors.fill: parent

//    MyComponents.QmlComponentListView{
//        id: listViewShowingResult
//        width: parent.width * 0.8
//        height: parent.height * 0.8
//        anchors.top: parent.top
//        anchors.centerIn: parent
//        orientaionList: ListView.Vertical
//        listModelObj: ListModel {
//            listTeams: listTeamsInResultQml
//        }
//    }

//    MyComponents.QmlComponentHelpBoard{
//        id: helpBoardShowingResult
//        width: listViewShowingResult.width
//        anchors.top: listViewShowingResult.bottom
//        anchors.topMargin: parent.height * 0.01
//        anchors.bottom: parent.bottom
//        anchors.bottomMargin: anchors.topMargin
//        anchors.horizontalCenter: listViewShowingResult.horizontalCenter
//        textHelp: qsTr("Save team result here")
//    }
    ScrollView{
        id: view
        anchors.fill: parent
        anchors.margins: parent.width * 0.04
        TextArea{
            text: providerQml.textResult
            readOnly: false
        }
    }
    Button{
        anchors.top: view.bottom
        anchors.right: view.right
        text: "save to file:"
        onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.SaveTextToFile)
    }

}

