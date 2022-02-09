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
        property int widthElements          : width * 0.9
        property color backgroundColor      : "black"
        property color textColor            : "white"
        property alias textQuestionStr      : textQuestion
        property real textPixelSize         : Math.min(width, height) * 0.1
        property bool visibleTeams          : true

        id: rectangleScreen
        width: widthComponents
        anchors.top: comboBoxQuestions.bottom
        anchors.topMargin: marginValue
        anchors.bottom: parent.bottom
        anchors.bottomMargin: marginValue
        anchors.left: parent.left
        anchors.leftMargin: marginValue
        color: backgroundColor

        MyComponents.QmlComponentRowLayout{
            id: listViewScreen
            width: rectangleScreen.widthElements
            height: parent.height / 3
            anchors.top: parent.top
            anchors.topMargin: marginValue * 3
            anchors.horizontalCenter: parent.horizontalCenter
            textColor: rectangleScreen.textColor
            textPixelSize: rectangleScreen.textPixelSize
            listModelObj: ListModel {
                listTeams: listTeamsInBattleQml
            }
            visible: rectangleScreen.visibleTeams
        }
        Text {
            id: textQuestion
            width: rectangleScreen.widthElements
            anchors.top: listViewScreen.visible ? listViewScreen.bottom : parent.top
            anchors.topMargin: parent.height * 0.02
            anchors.bottom: parent.bottom
            anchors.bottomMargin: anchors.topMargin
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            wrapMode: Text.WordWrap
            fontSizeMode: Text.Fit
            minimumPixelSize: 1
            font.pixelSize: rectangleScreen.textPixelSize
            color: rectangleScreen.textColor
            text: "textQuestion textQuestion  textQuestion textQuestion textQuestion textQuestion?"
        }

    }

    ColumnLayout{
        id: columnLayoutSettings
        width: (parent.width - rectangleScreen.width) * 0.5
        anchors.top: parent.top
        anchors.topMargin: marginValue
        anchors.left: rectangleScreen.right
        anchors.leftMargin: marginValue

        Button{
            Layout.maximumWidth: columnLayoutSettings.width
            Layout.minimumWidth: Layout.maximumWidth
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            text: "background color"
            visible: true
            onClicked: {
                colorDialog.showDialog((color)=>{rectangleScreen.backgroundColor = color})
            }
        }
        Button{
            Layout.maximumWidth: columnLayoutSettings.width
            Layout.minimumWidth: Layout.maximumWidth
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            text: "text color"
            visible: true
            onClicked: {
                colorDialog.showDialog((color)=>{rectangleScreen.textColor = color})
            }
        }
        CheckBox{
            Layout.maximumWidth: columnLayoutSettings.width
            Layout.minimumWidth: Layout.maximumWidth
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            checked: rectangleScreen.visibleTeams
            text: "teams"
            onCheckedChanged: rectangleScreen.visibleTeams = checked
        }
        Row{
            Layout.maximumWidth: columnLayoutSettings.width
            Layout.minimumWidth: Layout.maximumWidth
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            spacing: parent.width * 0.1
            Text{
                id: textFontSize
                height: textFieldFontSize.height
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                text: "font size:"
            }
            TextField{
                id: textFieldFontSize
                width: parent.width - parent.spacing - textFontSize.width
                text: "22"
                selectByMouse: true
                inputMethodHints: Qt.ImhDigitsOnly
                validator: IntValidator {
                    bottom: 1
                    top: 1000
                }
                onTextChanged: rectangleScreen.textPixelSize = text
            }
        }

    }

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        onAccepted: {
            functionReply (colorDialog.color)
        }
        property var functionReply: (color) => {};
        function showDialog(varFunctionReply){
            functionReply = varFunctionReply
            open()
        }
    }
}
