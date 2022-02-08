import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import biblebrainring.namespace 1.0

ApplicationWindow {
    id: rootWindow
    width: rectScreen.width
    height: rectScreen.height
    x: rectScreen.x
    y: rectScreen.y
    visible: true

    Connections{
        target: providerQml
        function onShowMessage(message){
            toolTipMessage.text = message
            toolTipMessage.visible = true
        }
    }

    Rectangle{
        anchors.fill: parent
        color: "lightblue"
        opacity: 0.5
    }

    QmlPageStart{
        id: pageStartMenu
        visible: providerQml.currentAppState === BibleBrainRing.StartMenu
    }

    QmlPageRegistration{
        id: pageRegistration
        visible: providerQml.currentAppState === BibleBrainRing.Registration
    }

    ToolTip{
        id: toolTipMessage
        text: "Hello!"
        visible: false
        timeout: 2222
        background: Rectangle{
            anchors.fill: parent
            color: "red"
            radius: 2
        }
//        closePolicy: Popup.CloseOnPressOutsideParent
    }

    Component.onCompleted: { providerQml.onEndQmlCreation() }
}
