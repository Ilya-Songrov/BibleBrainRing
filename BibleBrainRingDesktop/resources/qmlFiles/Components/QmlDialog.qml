import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Dialog {
    property string textFieldNameText: textFieldName.text

    id: dialog
    anchors.centerIn: parent
    implicitWidth: parent.width / 2.5
    closePolicy: Popup.NoAutoClose
    standardButtons: Dialog.Cancel | Dialog.Save
    modal: true
    Keys.onReturnPressed: accept()
    Keys.onEnterPressed: accept()
    background: Rectangle{
        anchors.fill: parent
    }
    contentItem: Item {
        id: itemContent

        property real minWidthDelegate: 11
        ColumnLayout {

            width: parent.width
            RowLayout{
                Layout.minimumHeight: parent.height / 4
                Label {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    verticalAlignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    text: "Create Team"
                    font.bold: true
                }
            }
            RowLayout{
                Label {
                    Layout.fillHeight: true
                    Layout.minimumWidth: itemContent.minWidthDelegate
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    verticalAlignment: Qt.AlignVCenter
                    text: "Name"
                    Component.onCompleted: { itemContent.minWidthDelegate = width; }
                }
                TextField {
                    id: textFieldName
                    Layout.fillWidth: true
                    selectByMouse: true
                    focus: visible
                }
            }

        }
    }
    onVisibleChanged: {
        if(visible){
            textFieldName.clear()
        }
    }
}
