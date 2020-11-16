#include "galleryworkerpictures.h"
#include "funcioneslocales.h"
#include "includes.h"

GalleryWorkerPictures::GalleryWorkerPictures(QObject *parent) : QObject(parent)
{
    detenerListado=false;
    listadoFinalizado=true;
}

QString GalleryWorkerPictures::listaDeCovers()
{
    return m_listaDeCovers;
}

QString GalleryWorkerPictures::pathRaiz()
{
    return m_pathRaiz;
}

void GalleryWorkerPictures::setPathRaiz(QString paramPathRaiz)
{
    m_pathRaiz=paramPathRaiz;
}

void GalleryWorkerPictures::listarPictures()
{
    QString pictureURL,pictureFolder,absoluteDir,pictureMiniatura;
    QDir rootDir(m_pathRaiz);
    QFileInfoList qFileInfoList = rootDir.entryInfoList(QDir::Files);
    QFileInfo fileInfo;
    bool bRes;
    int i,n;

    detenerListado=false;
    listadoFinalizado=false;
    n=qFileInfoList.count();
    for(i = 0; i<n && !detenerListado; i++)
    {
        fileInfo = qFileInfoList.at(i);
        pictureURL=fileInfo.absoluteFilePath();
        bRes=pictureURL.contains(".jpg") || pictureURL.contains(".jpeg") || pictureURL.contains(".png");
        bRes=bRes || pictureURL.contains(".gif") || pictureURL.contains(".tif") || pictureURL.contains(".bmp");

        if (bRes)
        {
            pictureFolder=funcionesLocales.extractFilePath(pictureURL);
            absoluteDir=funcionesLocales.extractAbsoluteDir(pictureFolder);
            pictureMiniatura=funcionesLocales.generarMiniatura(folderMiniaturas, pictureURL);
            emit addPictureSignal(pictureURL, pictureFolder, absoluteDir, pictureMiniatura);
        }
    }
    listadoFinalizado=true;

    emit listadoFinishedSignal();
}
