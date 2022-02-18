import QtQuick 2.15
import QtQuick.Controls 2.15

import "." as MyComponents

Item {
    property var listModelObj           : ListModel;

    GridView {
        property int maxQuantityCells:  6
        property int minQuantityCells:  5

        id: gridViewButtons
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        cellWidth: width / (minQuantityCells < listModelObj.length < maxQuantityCells ? minQuantityCells : listModelObj.length)
        cellHeight: cellWidth
        clip: true
        model: listModelObj
        delegate: componentDelegate

        add: Transition {
            NumberAnimation { properties: "x,y"; from: parent.width / 5; easing.type: Easing.OutBounce; duration: 1000 }
        }
        addDisplaced: Transition {
            NumberAnimation { properties: "x,y"; from: parent.width / 5; duration: 1000 }
        }
    }
    Component {
        id: componentDelegate

        Item {
            id: itemCentreGridId
            width: gridViewButtons.cellWidth
            height: gridViewButtons.cellHeight
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
                    //                   font.family: fontGlobal.family
                    text: model["name"]
                }
                Button{
                    width: parent.width / 3
                    height: parent.height / 6
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 2
                    anchors.left: parent.left
                    anchors.leftMargin: 2
                    text: "❌"
                    onClicked: {
                        model["status"] = 1 // NotValid
                    }
                }
                Button{
                    width: parent.width / 3
                    height: parent.height / 6
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 2
                    anchors.right: parent.right
                    anchors.rightMargin: 2
                    text: "✔️"
                    onClicked: {
                        model["status"] = 2 // Registered
                    }
                }
            }
        }
    }


}
