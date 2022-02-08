import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0



Button{
    property string pathImage: ""
    property bool rotationOclock: false

    id: buttonId
    background: Rectangle {
        opacity: 0
    }

    Image {
        id: iconId
        width: Math.min(parent.width, parent.height)
        height: width
        anchors.centerIn: buttonId
        source: pathImage
        sourceSize.width: width
        sourceSize.height: height
        fillMode: Image.PreserveAspectFit
        smooth: true
        visible: false
    }
    OpacityMask {
        anchors.fill: iconId
        source: iconId
        maskSource: iconId
    }

    states: State {
        name: "down"; when: buttonId.pressed === true
        PropertyChanges { target: buttonId; rotation: rotationOclock ? 360 : -360}
    }

    transitions: Transition {
        from: ""; to: "down"; reversible: true
        ParallelAnimation {
            NumberAnimation { properties: "rotation"; duration: 500; easing.type: Easing.InOutQuad }
        }
    }
}
