import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.12

import "." as MyComponents
import ListModelQml 1.0


Item {
    readonly property real marginValue: height * 0.02

    QtObject{
        id: objSCP
        property color backgroundColor      : "black"
        property color textColor            : "white"
        property string textQuestionStr     : "Do you have any questions?"
        property real textPixelSize         : textFieldFontSize.text
        property bool visibleTeams          : true
        property int widthElements          : width * 0.9
    }

    Rectangle{
        id: rectBorder
        anchors.fill: parent
        color: "transparent"
        radius: Math.min(parent.width, parent.height) * 0.01
        border.color: "black"
    }

    ComboBox {
        id: comboBoxQuestions
        width: boundingItemScreenWidget.width
        anchors.top: parent.top
        anchors.topMargin: marginValue
        anchors.left: parent.left
        anchors.leftMargin: marginValue
        editable: true
        selectTextByMouse: true
        model: []
        contentItem: TextField{
            id: textFieldQuestions
            width: boundingItemScreenWidget.width
            selectByMouse: true
            Keys.onReturnPressed: comboBoxQuestions.findSubStr(text)
            Keys.onEnterPressed: comboBoxQuestions.findSubStr(text)
            onTextChanged: {
                comboBoxQuestions.findSubStr(text)
                if(text.length === 0){
                    comboBoxQuestions.popup.close()
                }
            }
        }
        function findSubStr(subStr){
            model = managerQuestionsQml.updateSearchQuestions(subStr)
            popup.open()
        }
        onActivated: {
            objSCP.textQuestionStr = currentText
            textFieldQuestions.text = currentText
        }
    }

    Item{
        id: boundingItemScreenWidget
        width: listScreensQml.getSizeForBoundingItemScreenWidget().width
        height: listScreensQml.getSizeForBoundingItemScreenWidget().height
        anchors.top: comboBoxQuestions.bottom
        anchors.topMargin: marginValue
        anchors.left: parent.left
        anchors.leftMargin: marginValue

        QmlScreenWidget{
            id: screenWidget
            width: listScreensQml.getSizeForScreenWidget().width
            height: listScreensQml.getSizeForScreenWidget().height
            anchors.centerIn: parent
            scalePixelSize: 1
        }
    }

    QmlTranslatorToScreens{
        id: translatorToScreens
    }

    ColumnLayout{
        id: columnLayoutSettings
        width: parent.width / 3
        anchors.top: parent.top
        anchors.topMargin: marginValue
        anchors.left: boundingItemScreenWidget.right
        anchors.leftMargin: marginValue
        anchors.right: parent.right
        anchors.rightMargin: marginValue

        Button{
            Layout.maximumWidth: columnLayoutSettings.width
            Layout.minimumWidth: Layout.maximumWidth
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            text: "background color"
            onClicked: {
                colorDialog.showDialog((color)=>{objSCP.backgroundColor = color})
            }
        }
        Button{
            Layout.maximumWidth: columnLayoutSettings.width
            Layout.minimumWidth: Layout.maximumWidth
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            text: "text color"
            onClicked: {
                colorDialog.showDialog((color)=>{objSCP.textColor = color})
            }
        }
        RowLayout{
            Layout.maximumWidth: columnLayoutSettings.width
            Layout.minimumWidth: Layout.maximumWidth
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            CheckBox{
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                checked: objSCP.visibleTeams
                text: "teams"
                onCheckedChanged: objSCP.visibleTeams = checked
            }
            Button{
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                text: "reset bulb score"
                onClicked: {
                    providerQml.resetBulbScore(0)
                }
            }
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
            }
        }
        Button{
            Layout.maximumWidth: columnLayoutSettings.width
            Layout.minimumWidth: Layout.maximumWidth
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            text: "show"
            onClicked: {
                translatorToScreens.visibleScreens = !translatorToScreens.visibleScreens
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
