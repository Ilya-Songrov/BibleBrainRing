import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ToolTip{
    readonly property real centerWidth: parent.width / 2 - width / 2

    id: toolTipMessage
    x: centerWidth
    text: "Hello!"
    visible: false
    timeout: 1000
    background: Rectangle{
        anchors.fill: parent
        color: "red"
        radius: 2
    }
    function show(message){
        toolTipMessage.text     = message
        toolTipMessage.visible  = true
        x = Math.random() * centerWidth * 2
    }
//        closePolicy: Popup.CloseOnPressOutsideParent
}

