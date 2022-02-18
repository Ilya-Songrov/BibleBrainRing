import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.12

import "." as MyComponents
import ListModelQml 1.0


Rectangle{
    required property real scalePixelSize

    color: objSCP.backgroundColor
    MyComponents.QmlRowLayout{
        id: rowLayoutNameScore
        width: parent.width * 0.9
        height: parent.height / 2.7
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.025
        anchors.horizontalCenter: parent.horizontalCenter
        textColor: objSCP.textColor
        textPixelSize: objSCP.textPixelSize * scalePixelSize
        listModelObj: listModelObjInstance
        visible: objSCP.visibleTeams
    }
    Text {
        Rectangle{
            anchors.fill: parent
            color: "green"
            opacity: 0.5
        }
        id: textQuestion
        width: rowLayoutNameScore.width
        anchors.top: rowLayoutNameScore.visible ? rowLayoutNameScore.bottom : parent.top
        anchors.topMargin: rowLayoutNameScore.anchors.topMargin
        anchors.bottom: parent.bottom
        anchors.bottomMargin: anchors.topMargin
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
        wrapMode: Text.WordWrap
        fontSizeMode: Text.Fit
        minimumPixelSize: 1
        font.pixelSize: Number(objSCP.textPixelSize) * scalePixelSize
        color: objSCP.textColor
        text: objSCP.textQuestionStr
    }
}
