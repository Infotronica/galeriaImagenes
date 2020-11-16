import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import Qt.labs.settings 1.0

ApplicationWindow {
    id: mainWindow
    title: "Galería de Imágenes"
    color: "white"
    visible: true
    visibility: Window.Maximized

    property int anchoPantalla: width
    property int altoPantalla: height
    property int anchoBoton: anchoPantalla*0.70
    property int altoBoton: altoPantalla*0.06
    property int diametroBoton: altoBoton*1.5
    property int margenX: anchoPantalla*0.05
    property int margenY: altoPantalla*0.02
    property int spacingX: anchoBoton*0.05
    property int spacingY: altoBoton*0.15

   /*ScrollView {
        anchors.fill: parent

        TextArea {
            anchors.fill: parent
            text: funcionesLocales.test()
            //text: StandardPaths.writableLocation(StandardPaths.HomeLocation)
        }
    }*/

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        StackView {
            id: stackView
            Layout.fillWidth: true
            Layout.fillHeight: true
            visible: true
            focus: true
            initialItem: listarCovers

            Keys.onPressed: {
                if (event.key===Qt.Key_Back && stackView.depth>1) {
                    if (depth==2)
                    {
                        listarPictures.stopListado()
                    }
                    if (depth==1)
                    {
                        listarCovers.stopListado()
                    }
                    stackView.pop()
                    event.accepted=true
                }
            }
        }

        Rectangle {
            id: rectVelo
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumHeight: altoBoton*2
            color: "tomato"

            BusyIndicator {
                id: busyIndicator
                running: rectVelo.visible
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    ListarCovers {
        id: listarCovers
        visible: false
    }

    ListarPictures {
        id: listarPictures
        visible: false
    }

    VerImagen {
        id: verImagen
        visible: false
    }

    VerImagen {
        id: verImagen2
        visible: false
    }

    Component.onCompleted: {
    }
}
