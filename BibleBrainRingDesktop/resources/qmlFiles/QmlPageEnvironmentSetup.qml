import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.12

Item {
    anchors.fill: parent

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
            text: "Smart Lamp settings"
            onClicked: {
                // TODO: write me
            }
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
