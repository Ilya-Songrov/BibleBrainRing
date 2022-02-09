import QtQuick 2.15
import QtQuick.Controls 2.15

import "." as MyComponents

Item {
    property var listModelObj           : ListModel;
    signal moveTeamToAnotherList(int index)

    Rectangle{
        anchors.fill: parent
        color: "transparent"
        border.color: "black"
    }

    ListView {
        anchors.fill: parent
        clip: true
        orientation: ListView.Horizontal
        model: listModelObj
        delegate: componentDelegate
    }
    Component {
        id: componentDelegate

        Item {
            width: ListView.view.width / 6
            height: ListView.view.height

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
            }
        }
    }


}
