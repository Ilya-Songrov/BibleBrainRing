import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property string textHelp: ""
    property color colorBackground: "#87CEFA"

    Rectangle{
        id: rectHelp
        anchors.fill: parent
        radius: parent.height * 0.1
        color: colorBackground
        Text {
            anchors.fill: parent
            anchors.margins: Math.min(parent.width, parent.height) * 0.05
            color: "black"
            text: textHelp
//            font.family: fontGlobal.family
//            font.bold: fontGlobal.bold
            minimumPointSize: 2
            fontSizeMode: Text.Fit
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
