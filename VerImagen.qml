import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    id: itemContainer
    Layout.fillWidth: true
    Layout.fillHeight: true
    property string pictureSource: ""

    Flickable {
        id: flick
        anchors.fill: parent
        contentWidth: anchoPantalla
        contentHeight: altoPantalla

        PinchArea {
            width: Math.max(flick.contentWidth, flick.width)
            height: Math.max(flick.contentHeight, flick.height)

            property real initialWidth
            property real initialHeight

            onPinchStarted: {
                initialWidth = flick.contentWidth
                initialHeight = flick.contentHeight
            }

            onPinchUpdated: {
                // ajustar la posición del contenido por el arrastre
                flick.contentX += pinch.previousCenter.x - pinch.center.x
                flick.contentY += pinch.previousCenter.y - pinch.center.y

                // cambiar tamaño
                flick.resizeContent(initialWidth * pinch.scale, initialHeight * pinch.scale, pinch.center)
            }

            onPinchFinished: {
                // Mover el contenido
                flick.returnToBounds()
            }

            Rectangle {
                width: flick.contentWidth
                height: flick.contentHeight
                color: "white"

                Image {
                    id: imgPreview
                    anchors.fill: parent
                    source: pictureSource
                    fillMode: Image.PreserveAspectFit

                    MouseArea {
                        anchors.fill: parent
                        onDoubleClicked: {
                            flick.contentWidth = anchoPantalla
                            flick.contentHeight = altoPantalla
                        }
                    }

                    onStatusChanged: {
                        rectVelo.visible=false
                    }
                }
            }
        }
    }
}
