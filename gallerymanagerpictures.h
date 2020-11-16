#ifndef GALLERYMANAGERPICTURES_H
#define GALLERYMANAGERPICTURES_H

#include <QObject>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDirIterator>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QThread>
#include "galleryworkerpictures.h"

class GalleryManagerPictures: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString pathRaiz READ pathRaiz WRITE setPathRaiz)

public:
    explicit GalleryManagerPictures(QObject *parent = nullptr);
    ~GalleryManagerPictures();

    QString pathRaiz();
    Q_INVOKABLE void setPathRaiz(QString paramPathRaiz);
    Q_INVOKABLE void startListado();
    Q_INVOKABLE void stopListado();

    QThread hiloGalleryWorker;
    GalleryWorkerPictures *galleryWorkerPictures;

signals:
    void listarPicturesSignal();
    void addPictureSignal(QString pictureURL, QString pictureFolder, QString absoluteDir, QString pictureMiniatura);
    void listadoFinishedSignal();

public slots:
    void addPicture(QString pictureURL, QString pictureFolder, QString absoluteDir, QString pictureMiniatura);
    void listadoFinished();

private:
    QString m_pathRaiz;

private slots:
};

#endif // GALLERYMANAGERPICTURES_H
