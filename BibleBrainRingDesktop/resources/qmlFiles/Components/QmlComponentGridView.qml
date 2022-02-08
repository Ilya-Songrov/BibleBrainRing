import QtQuick 2.15
import QtQuick.Controls 2.15

import "." as MyComponents

Item {
    property variant variantListTeams: []

    Rectangle{
        anchors.fill: parent
        color: "red"
        opacity: 0.5
    }
    GridView {
        property int maxQuantityCells:  4
        property int minQuantityCells:  3

        id: gridViewButtons
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        cellWidth: width / (minQuantityCells < variantListTeams.length < maxQuantityCells ? minQuantityCells : variantListTeams.length)
        cellHeight: cellWidth
        clip: true
        model: variantListTeams
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
                color: modelData["color"]
            }
            Text {
                id: textName
                text: modelData["name"]
            }
            Text {
                id: textScore
                text: modelData["score"]
            }
        }
    }


}
