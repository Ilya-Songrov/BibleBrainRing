import QtQuick 2.15
import QtQuick.Controls 2.15

import "Components" as MyComponents

Item {
    anchors.fill: parent

    MyComponents.QmlComponentGridView{
        width: parent.width * 0.8
        height: parent.height * 0.8
        anchors.centerIn: parent
    }

}
