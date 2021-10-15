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

    Rectangle{
        anchors.fill: parent
        color: "lightblue"
        opacity: 0.5
    }

    QmlPageStart{
        id: pageStart
        visible: providerQml.currentAppState === BibleBrainRing.Start
    }

    QmlPageRegistration{
        id: pageRegistration
        visible: providerQml.currentAppState === BibleBrainRing.Registration
    }

    Component.onCompleted: { providerQml.onEndQmlCreation() }
}
