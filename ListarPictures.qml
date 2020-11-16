import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import Qt.labs.settings 1.0
import gallery.manager.pictures 1.0

Item {
    Layout.fillWidth: true
    Layout.fillHeight: true
    property string folder: ""
    property int imgSize: mainWindow.width/2

    ListModel {
        id: listaModel
    }

    GalleryManagerPictures {
        id: galleryManagerPictures

        Component.onCompleted: {
        }

        onAddPictureSignal: {
            listaModel.append(
                {
                  "pictureURL": pictureURL,
                  "pictureFolder": pictureFolder,
                  "absoluteDir": absoluteDir,
                  "pictureMiniatura": pictureMiniatura
                }
            )
        }

        onListadoFinishedSignal: {
            rectVelo.visible=false;
        }
    }

    Component {
        id: pictureDelegate

        Rectangle {
            id: rectMarco
            width: imgSize
            height: imgSize
            color: "transparent"
            border {
                width: 1
                color: "white"
            }

            Image {
                id: imagenMosaico
                source: pictureMiniatura
                width: imgSize-rectMarco.border.width
                height: imgSize-rectMarco.border.width
                fillMode: Image.PreserveAspectCrop
                sourceSize.width: imgSize
                sourceSize.height: imgSize
                cache: true

                onStatusChanged: {
                    if (status===Image.Error)
                    {
                        source=funcionesLocales.imagenErronea
                    }
                    if (status===Image.Ready)
                    {
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        rectVelo.visible=true
                        if (imagenMosaico.source==funcionesLocales.imagenErronea)
                        {
                            timerLoadPicture.pictureSource=imagenMosaico.source
                        }
                        else
                        {
                            timerLoadPicture.pictureSource="file://"+pictureURL
                        }
                        timerLoadPicture.start()
                    }
                }
            }
        }
    }

    Timer
    {
        property string pictureSource: ""
        id: timerLoadPicture
        running: false
        repeat: false
        interval: 200

        onTriggered: {
            verImagen.pictureSource=pictureSource
            stackView.push(verImagen)
        }
    }

    ColumnLayout {
        anchors.fill: parent

        GridView {
            id: gridViewFotos
            Layout.fillWidth: true
            Layout.fillHeight: true
            cellWidth: imgSize
            cellHeight: imgSize
            model: listaModel
            delegate: pictureDelegate
            focus: true
            visible: true
            //cacheBuffer: 50
        }
    }

    function listarPictures()
    {
        listaModel.clear()
        rectVelo.visible=true;
        galleryManagerPictures.pathRaiz=folder
        galleryManagerPictures.listarPicturesSignal()
    }

    function stopListado()
    {
        galleryManagerPictures.stopListado()
    }
}
