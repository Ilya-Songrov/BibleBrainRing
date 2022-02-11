import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

import "." as MyComponents
import ListModelQml 1.0

Item {
    property var listModelObj           : ListModel;
    property color textColor            : "white"
    property real textPixelSize         : Math.min(parent.width, parent.height) * 0.1

    RowLayout {
        id: rowLayoutModel
        width: parent.width
        height: parent.height
        spacing: 0

        Repeater {
            property int minMaxWidthElement: count < 4 ? parent.width / 4 : parent.width / count
            property int minMaxHeightElement: parent.height / 2

            // for example
            // function updateminPixelSize(){
            //     let minPs = textPixelSize
            //     for (var index = 0; index < count; index++) {
            //         let ps = repeaterModel.itemAt(index).children[0].fontInfo.pixelSize
            //     }
            // }

            id: repeaterModel
            model: listModelObj
            ColumnLayout{
                id: columnLayoutNameScore
                Layout.fillHeight: true
                Layout.minimumWidth: repeaterModel.minMaxWidthElement
                Layout.maximumWidth: repeaterModel.minMaxWidthElement
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                spacing: 0

                Text {
                    Layout.fillWidth: true
                    Layout.minimumHeight: repeaterModel.minMaxHeightElement
                    Layout.maximumHeight: repeaterModel.minMaxHeightElement
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    wrapMode: Text.WordWrap
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 1
                    font.pixelSize: textPixelSize
                    color: textColor
                    text: model["name"]
                }
                Text {
                    Layout.fillWidth: true
                    Layout.minimumHeight: repeaterModel.minMaxHeightElement
                    Layout.maximumHeight: repeaterModel.minMaxHeightElement
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    wrapMode: Text.WordWrap
                    fontSizeMode: Text.Fit
                    minimumPixelSize: 1
                    font.pixelSize: textPixelSize
                    color: textColor
                    text: model["score"]
                }

            }

        }
    }

}
