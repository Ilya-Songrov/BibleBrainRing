import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

import "." as MyComponents

Item {
    property var listModelObj           : ListModel;
    property int orientaionList         : ListView.Horizontal
    signal moveTeamToAnotherList(int index)

    Rectangle{
        anchors.fill: parent
        color: "transparent"
        border.color: "black"
    }

    ListView {
        anchors.fill: parent
        clip: true
        orientation: orientaionList
        model: listModelObj
        delegate: componentDelegate
    }
    Component {
        id: componentDelegate

        Item {
            width: ListView.view.width / (orientaionList === ListView.Horizontal ? 6 : 1)
            height: ListView.view.height / (orientaionList === ListView.Vertical ? 6 : 1)

            Rectangle{
                id: rectColor
                anchors.fill: parent
                anchors.margins: Math.min(parent.width, parent.height) * 0.02
                color: model["color"]
                radius: anchors.margins
                opacity: (model["status"] > 1 && model["status"] < 5) ? 1 : 0.5

                Text {
                    id: textName
                    width: parent.width
                    height: parent.height / 2.5
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    minimumPixelSize: 2
                    fontSizeMode: Text.Fit
                    font.pixelSize: parent.width * 0.298
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: "#252525"
                    text: model["name"]
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        moveTeamToAnotherList(index)
                    }
                }
                Row{
                    width: parent.width * 0.9
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: parent.height * 0.04
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                    spacing: parent.width * 0.1
                    Text{
                        id: textFontSize
                        height: textFieldFontSize.height
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        text: "score:"
                    }
                    SpinBox{
                        id: textFieldFontSize
                        width: parent.width - parent.spacing - textFontSize.width
                        value: model["score"]
                        inputMethodHints: Qt.ImhDigitsOnly
                        validator: IntValidator {
                            bottom: 1
                            top: 1000
                        }
                        onValueModified: {
                            model["score"] = value
                        }
                    }
                }
            }
        }
    }


}
