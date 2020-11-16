#ifndef GALLERYMANAGERCOVERS_H
#define GALLERYMANAGERCOVERS_H

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
#include "galleryworkercovers.h"

class GalleryManagerCovers: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString pathRaiz READ pathRaiz WRITE setPathRaiz)

public:
    explicit GalleryManagerCovers(QObject *parent = nullptr);
    ~GalleryManagerCovers();

    QString pathRaiz();
    Q_INVOKABLE void setPathRaiz(QString paramPathRaiz);
    Q_INVOKABLE void startListado();
    Q_INVOKABLE void stopListado();

    QThread hiloGalleryWorker;
    GalleryWorkerCovers *galleryWorkerCovers;

signals:
    void listarCoversSignal();
    void addCoverSignal(QString pictureURL, QString pictureFolder, QString absoluteDir, QString pictureMiniatura);
    void listadoFinishedSignal();

public slots:
    void addCover(QString pictureURL, QString pictureFolder, QString absoluteDir, QString pictureMiniatura);
    void listadoFinished();

private:
    QString m_pathRaiz;

private slots:
};

#endif // GALLERYMANAGERCOVERS_H
