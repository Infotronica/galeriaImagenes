#include "gallerymanagercovers.h"

GalleryManagerCovers::GalleryManagerCovers(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_ANDROID
    m_pathRaiz = "/storage";
#endif
#ifdef Q_OS_IOS
    m_pathRaiz = "/"; // pendiente
#endif
#if (defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_DARWIN)) && !defined(Q_OS_ANDROID)
    m_pathRaiz=QStandardPaths::standardLocations(QStandardPaths::PicturesLocation)[0];
#endif

    galleryWorkerCovers = new GalleryWorkerCovers;
    galleryWorkerCovers->setPathRaiz(m_pathRaiz);
    galleryWorkerCovers->moveToThread(&hiloGalleryWorker);

    connect(this, SIGNAL(listarCoversSignal()), galleryWorkerCovers, SLOT(listarCovers()));
    connect(galleryWorkerCovers, SIGNAL(addCoverSignal(QString,QString,QString,QString)), this, SLOT(addCover(QString,QString,QString,QString)));
    connect(galleryWorkerCovers, SIGNAL(listadoFinishedSignal()), this, SLOT(listadoFinished()));

    startListado();
}

GalleryManagerCovers::~GalleryManagerCovers()
{
    while (!galleryWorkerCovers->listadoFinalizado)
    {
        galleryWorkerCovers->detenerListado=true;
    }
    delete galleryWorkerCovers;
    hiloGalleryWorker.quit();
    hiloGalleryWorker.wait();
}

QString GalleryManagerCovers::pathRaiz()
{
    return m_pathRaiz;
}

void GalleryManagerCovers::setPathRaiz(QString paramPathRaiz)
{
    m_pathRaiz=paramPathRaiz;
}

void GalleryManagerCovers::startListado()
{
    hiloGalleryWorker.start();
}

void GalleryManagerCovers::stopListado()
{
    while (!galleryWorkerCovers->listadoFinalizado)
    {
        galleryWorkerCovers->detenerListado=true;
    }
    emit listadoFinishedSignal();
}

void GalleryManagerCovers::addCover(QString pictureURL, QString pictureFolder, QString absoluteDir, QString pictureMiniatura)
{
    emit addCoverSignal(pictureURL, pictureFolder, absoluteDir, pictureMiniatura);
}

void GalleryManagerCovers::listadoFinished()
{
    hiloGalleryWorker.quit();
    hiloGalleryWorker.wait();
    emit listadoFinishedSignal();
}
