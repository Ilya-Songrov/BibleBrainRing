import QtQuick 2.15
import QtQuick.Controls 2.15

import "." as MyComponents
import ListModelScreensQml 1.0

Item {
    property bool visibleScreens: true

    Repeater{
        id: repeaterAdditionalScreens
        model: ListModelScreens {
            listScreens: listScreensQml
        }
        Loader{
            property variant modelData: model

            sourceComponent: Component{
                ApplicationWindow{
                    x: modelData["xPos"]
                    y: modelData["yPos"]
                    width: modelData["widthReal"]
                    height: modelData["heightReal"]
                    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint // do not add Qt.Tool, because ComboBox in KYC will not work correct
                    visible:  visibleScreens

                    QmlScreenWidget{
                        width: modelData["widthVisual"]
                        height: modelData["heightVisual"]
                        anchors.centerIn: parent
                        scalePixelSize: modelData["scalePixelSize"]
                    }
                }
            }
        }
    }

}
