#include "galleryworkercovers.h"
#include "funcioneslocales.h"
#include "includes.h"

GalleryWorkerCovers::GalleryWorkerCovers(QObject *parent) : QObject(parent)
{
    detenerListado=false;
    listadoFinalizado=true;
}

QString GalleryWorkerCovers::listaDeCovers()
{
    return m_listaDeCovers;
}

QString GalleryWorkerCovers::pathRaiz()
{
    return m_pathRaiz;
}

void GalleryWorkerCovers::setPathRaiz(QString paramPathRaiz)
{
    m_pathRaiz=paramPathRaiz;
}

QStringList GalleryWorkerCovers::listarDrives()
{
    QDir rootDir(m_pathRaiz);
    QFileInfoList qFileInfoList = rootDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    QStringList qStringList;
    QString qString;
    int i,n;

    n=qFileInfoList.count();
    for(i = 0; i<n; i++)
    {
        QFileInfo fileInfo = qFileInfoList.at(i);

        qString=fileInfo.absoluteFilePath();
        if (qString.contains("emulated"))
        {
            qString+="/0";
        }
        qStringList.append(qString);
    }

    return qStringList;
}

void GalleryWorkerCovers::listarCovers()
{
    QString pictureURL,pictureFolder,absoluteDir,pictureMiniatura,currentDrive;
    QStringList stringListNoRepeat,stringListDrives;
    int i,n;
    bool bRes;

    stringListDrives=listarDrives();
    n=stringListDrives.count();

    detenerListado=false;
    listadoFinalizado=false;
    for (i=0; i<n && !detenerListado; i++)
    {
        currentDrive=stringListDrives.at(i);
        QDirIterator qDirIterator(m_pathRaiz, QDirIterator::Subdirectories);
        while (qDirIterator.hasNext())
        {
            pictureURL=qDirIterator.next();
            bRes=pictureURL.contains(".jpg") || pictureURL.contains(".jpeg") || pictureURL.contains(".png");
            bRes=bRes || pictureURL.contains(".gif") || pictureURL.contains(".tif") || pictureURL.contains(".bmp");

            if (bRes)
            {
                pictureFolder=funcionesLocales.extractFilePath(pictureURL);
                absoluteDir=funcionesLocales.extractAbsoluteDir(pictureFolder);
                bRes=stringListNoRepeat.contains(pictureFolder);
                if (!bRes)
                {
                    pictureMiniatura=funcionesLocales.generarMiniatura(folderMiniaturas, pictureURL);
                    stringListNoRepeat.append(pictureFolder); // para no repetir
                    emit addCoverSignal(pictureURL, pictureFolder, absoluteDir, pictureMiniatura);
                }
            }
        }
    }
    listadoFinalizado=true;

    emit listadoFinishedSignal();
}
