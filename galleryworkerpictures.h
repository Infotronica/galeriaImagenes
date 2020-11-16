#ifndef GALLERYWORKERPICTURES_H
#define GALLERYWORKERPICTURES_H

#include <QObject>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDirIterator>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>

class GalleryWorkerPictures: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString listaDeCovers READ listaDeCovers NOTIFY listadoFinishedSignal)
    Q_PROPERTY(QString pathRaiz READ pathRaiz WRITE setPathRaiz)

public:
    explicit GalleryWorkerPictures(QObject *parent = nullptr);
    QString listaDeCovers();
    QString pathRaiz();
    Q_INVOKABLE void setPathRaiz(QString paramPathRaiz);

    bool detenerListado,listadoFinalizado;

signals:
    void addPictureSignal(QString pictureURL, QString pictureFolder, QString absoluteDir, QString pictureMiniatura);
    void listadoFinishedSignal();

public slots:
    void listarPictures();

private:
    QString m_listaDeCovers,m_pathRaiz;

private slots:
};

#endif // GALLERYWORKERPICTURES_H
