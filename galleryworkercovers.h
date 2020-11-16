#ifndef GALLERYWORKERCOVERS_H
#define GALLERYWORKERCOVERS_H

#include <QObject>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDirIterator>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>

class GalleryWorkerCovers: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString listaDeCovers READ listaDeCovers NOTIFY listadoFinishedSignal)
    Q_PROPERTY(QString pathRaiz READ pathRaiz WRITE setPathRaiz)

public:
    explicit GalleryWorkerCovers(QObject *parent = nullptr);
    QString listaDeCovers();
    QString pathRaiz();
    Q_INVOKABLE void setPathRaiz(QString paramPathRaiz);
    QStringList listarDrives();

    bool detenerListado,listadoFinalizado;

signals:
    void addCoverSignal(QString pictureURL, QString pictureFolder, QString absoluteDir, QString pictureMiniatura);
    void listadoFinishedSignal();

public slots:
    void listarCovers();

private:
    QString m_listaDeCovers,m_pathRaiz;

private slots:
};

#endif // GALLERYWORKERCOVERS_H
