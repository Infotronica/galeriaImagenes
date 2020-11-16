#include "gallerymanagerpictures.h"

GalleryManagerPictures::GalleryManagerPictures(QObject *parent) : QObject(parent)
{
    galleryWorkerPictures = new GalleryWorkerPictures;
    galleryWorkerPictures->moveToThread(&hiloGalleryWorker);

    connect(this, SIGNAL(listarPicturesSignal()), galleryWorkerPictures, SLOT(listarPictures()));
    connect(galleryWorkerPictures, SIGNAL(addPictureSignal(QString,QString,QString,QString)), this, SLOT(addPicture(QString,QString,QString,QString)));
    connect(galleryWorkerPictures, SIGNAL(listadoFinishedSignal()), this, SLOT(listadoFinished()));
}

GalleryManagerPictures::~GalleryManagerPictures()
{
    while (!galleryWorkerPictures->listadoFinalizado)
    {
        galleryWorkerPictures->detenerListado=true;
    }
    delete galleryWorkerPictures;
    hiloGalleryWorker.quit();
    //hiloGalleryWorker.wait();
    emit listadoFinishedSignal();
}

QString GalleryManagerPictures::pathRaiz()
{
    return m_pathRaiz;
}

void GalleryManagerPictures::setPathRaiz(QString paramPathRaiz)
{
    m_pathRaiz=paramPathRaiz;
    galleryWorkerPictures->setPathRaiz(m_pathRaiz);
    startListado();
}

void GalleryManagerPictures::startListado()
{
    hiloGalleryWorker.start();
}

void GalleryManagerPictures::stopListado()
{
    galleryWorkerPictures->detenerListado=true;
    hiloGalleryWorker.quit();
    emit listadoFinishedSignal();
}

void GalleryManagerPictures::addPicture(QString pictureURL, QString pictureFolder, QString absoluteDir, QString pictureMiniatura)
{
    emit addPictureSignal(pictureURL, pictureFolder, absoluteDir, pictureMiniatura);
}

void GalleryManagerPictures::listadoFinished()
{
    hiloGalleryWorker.quit();
    hiloGalleryWorker.wait();
    emit listadoFinishedSignal();
}
