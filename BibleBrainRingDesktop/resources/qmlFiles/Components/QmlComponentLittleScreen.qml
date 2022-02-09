import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.12

import "." as MyComponents
import ListModelQml 1.0


Item {
    readonly property real marginValue: height * 0.02
    readonly property real widthComponents: width / 1.7

    Rectangle{
        id: rectBorder
        anchors.fill: parent
        color: "transparent"
        radius: Math.min(parent.width, parent.height) * 0.01
        border.color: "black"
    }

    ComboBox {
        id: comboBoxQuestions
        width: widthComponents
        anchors.top: parent.top
        anchors.topMargin: marginValue
        anchors.left: parent.left
        anchors.leftMargin: marginValue
        editable: true
        selectTextByMouse: true
        model: ["First", "Second", "Second2", "Third"]
    }

    Rectangle{
        id: rectangleScreen
        width: widthComponents
        anchors.top: comboBoxQuestions.bottom
        anchors.topMargin: marginValue
        anchors.bottom: parent.bottom
        anchors.bottomMargin: marginValue
        anchors.left: parent.left
        anchors.leftMargin: marginValue
        color: "black"

//        Column{

//            Repeater{
//                model: 5
//                Text {
//                    id: name
//                    text: qsTr("text")
//                    color: "white"
//                }
//            }
//        }
        MyComponents.QmlComponentListView{
            Rectangle{
                anchors.fill: parent
                color: "red"
                opacity: 0.5
            }
            id: sdfsdfsdf
            width: parent.width * 0.9
            height: parent.height / 6
            anchors.top: parent.top
            anchors.topMargin: marginValue
            anchors.horizontalCenter: parent.horizontalCenter
            listModelObj: ListModel {
                listTeams: listTeamsInBattleQml
            }
            onMoveTeamToAnotherList: listTeamsInBattleQml.moveTeamToAnotherList(index)
        }

    }

    ColumnLayout{
        id: columnLayoutSettings
        width: (parent.width - rectangleScreen.width) * 0.5
        anchors.top: parent.top
        anchors.topMargin: marginValue
        anchors.bottom: parent.bottom
        anchors.bottomMargin: marginValue
        anchors.left: rectangleScreen.right
        anchors.leftMargin: marginValue

        Button{
            Layout.maximumWidth: columnLayoutSettings.width
            Layout.maximumHeight: parent.height
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            text: "color"
            visible: true
            onClicked: {
                colorDialog.visible = true
            }
        }
    }

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        onAccepted: {
            rectangleScreen.color = colorDialog.color
        }
    }
}
