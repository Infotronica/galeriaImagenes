import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.0
import Qt.labs.settings 1.0
import gallery.manager.covers 1.0

Item {
    Layout.fillWidth: true
    Layout.fillHeight: true
    property int imgSize: mainWindow.width/2

    Component.onCompleted: {
    }

    ListModel {
        id: listaModel
    }

    GalleryManagerCovers {
        id: galleryManagerCovers

        Component.onCompleted: {
            rectVelo.visible=true;
            listarCoversSignal()
        }

        onAddCoverSignal: {
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
                source: pictureMiniatura
                width: imgSize-rectMarco.border.width
                height: imgSize-rectMarco.border.width
                fillMode: Image.PreserveAspectCrop
                sourceSize.width: imgSize
                sourceSize.height: imgSize

                onStatusChanged: {
                    if (status===Image.Error)
                    {
                        source=funcionesLocales.imagenErronea
                    }
                    if (status===Image.Ready)
                    {
                    }
                }

                Rectangle {
                    anchors.bottom: parent.bottom
                    color: "white"
                    border.color: "black"
                    width: parent.width
                    height: coverTitle.font.pixelSize*2

                    Text {
                        id: coverTitle
                        anchors.fill: parent
                        wrapMode: Text.WordWrap
                        clip: true
                        elide: Text.ElideLeft
                        text: absoluteDir
                        color: "black"
                        font.bold: true
                        lineHeight: 1.5
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        listarPictures.folder=pictureFolder
                        listarPictures.listarPictures()
                        stackView.push(listarPictures)
                    }
                }
            }
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

    function stopListado()
    {
        galleryManagerCovers.stopListado()
    }
}
