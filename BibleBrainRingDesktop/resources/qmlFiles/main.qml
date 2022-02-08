import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import biblebrainring.namespace 1.0
import "Components" as MyComponents


ApplicationWindow {
    id: rootWindow
    width: rectScreen.width
    height: rectScreen.height
    x: rectScreen.x
    y: rectScreen.y
    visible: true

    readonly property string pathArrow:  "qrc:/qmlFiles/images/3313578_arrow_left_direction_pointing_icon.svg"
    Connections{
        target: providerQml
        function onShowMessage(message){
            toolTipMessage.show(message)
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

    QmlPageGameSession{
        id: pageGameSession
        visible: providerQml.currentAppState === BibleBrainRing.GameSession
    }

    QmlPageShowingResult{
        id: pageShowingResult
        visible: providerQml.currentAppState === BibleBrainRing.ShowingResult
    }

    QmlToolTip{
        id: toolTipMessage
    }

    MyComponents.QmlComponentButtonImage{
        id: buttonComeback
        width: Math.min(parent.width, parent.height) * 0.05
        height: width
        anchors.left: parent.left
        anchors.leftMargin: width * 0.2
        anchors.top: parent.top
        anchors.topMargin: width * 0.2
        pathImage: pathArrow
        visible: providerQml.currentAppState !== BibleBrainRing.None &&
                 providerQml.currentAppState !== BibleBrainRing.Init &&
                 providerQml.currentAppState !== BibleBrainRing.StartMenu
        onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.ButtonComeback)
    }
    MyComponents.QmlComponentButtonImage{
        id: buttonNext
        width: Math.min(parent.width, parent.height) * 0.05
        height: width
        anchors.right: parent.right
        anchors.rightMargin: width * 0.2
        anchors.top: parent.top
        anchors.topMargin: width * 0.2
        transformOrigin: Item.Center
        rotation: 180
        rotationOclock: true
        pathImage: pathArrow
        visible: providerQml.currentAppState !== BibleBrainRing.None &&
                 providerQml.currentAppState !== BibleBrainRing.Init &&
                 providerQml.currentAppState !== BibleBrainRing.StartMenu
        onClicked: providerQml.onQmlButtonClicked(BibleBrainRing.ButtonNext)
    }

    Component.onCompleted: { providerQml.onEndQmlCreation() }
}
