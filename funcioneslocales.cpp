#include "funcioneslocales.h"
#include "includes.h"

FuncionesLocales funcionesLocales;

FuncionesLocales::FuncionesLocales(QObject *parent) : QObject(parent)
{
    m_imagenErronea="qrc:/img/error_imagen.svg";
}

QString FuncionesLocales::test()
{
    QString pathRaiz,qString;

    pathRaiz="/storage";
    //pathRaiz="/storage/emulated/0";
    //pathRaiz="/storage/A398-13E4";
    //pathRaiz="/storage/self";
    //qString=QStandardPaths::standardLocations(QStandardPaths::PicturesLocation)[0];

    QDir rootDir(pathRaiz);
    QFileInfoList list = rootDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    int i,n;

    qString="";
    n=list.count();
    qString+=QString::number(n)+"\n";
    for(i = 0; i<n; i++)
    {
        QFileInfo fileInfo = list.at(i);

        qString+=fileInfo.absoluteFilePath()+"\n";
    }

    qString+="\n\n";

    //pathRaiz="/storage";
    //pathRaiz="/storage/emulated/0";
    //pathRaiz="/storage/A398-13E4";
/*    pathRaiz="/storage/emulated/0/sdcard";
    QDirIterator qDirIterator(pathRaiz, QDirIterator::Subdirectories);

    while (qDirIterator.hasNext())
    {
        qString+=qDirIterator.next()+"\n";
    }*/

    return qString;
}

QString FuncionesLocales::extractAbsoluteDir(QString fullName)
{
    QFileInfo fileInfo;
    QString nombre;

    fileInfo.setFile(fullName);
    nombre=fileInfo.absoluteDir().dirName();

    return nombre;
}

QString FuncionesLocales::extractBaseName(QString fullName)
{
    QFileInfo fileInfo;
    QString nombre;

    fileInfo.setFile(fullName);
    nombre=fileInfo.completeBaseName();

    return nombre;
}

QString FuncionesLocales::extractBaseExt(QString fullName)
{
    QFileInfo fileInfo;
    QString extension;

    fileInfo.setFile(fullName);
    extension=fileInfo.suffix();

    return extension;
}

QString FuncionesLocales::extractFileName(QString fullName)
{
    QFileInfo fileInfo;
    QString fileName;

    fileInfo.setFile(fullName);
    fileName=fileInfo.fileName();

    return fileName;
}

QString FuncionesLocales::extractFilePath(QString fullName)
{
    QFileInfo fileInfo;
    QString filePath;

    fileInfo.setFile(fullName);
    filePath=fileInfo.absolutePath()+"/";

    return filePath;
}

QString FuncionesLocales::imagenErronea()
{
    return m_imagenErronea;
}

QString FuncionesLocales::generarMiniatura(QString folderMiniaturas, QString pictureURL)
{
    QString pictureMiniatura;
    QScreen *qScreen;
    QImage qImage;
    QFile qFile;
    bool existe,imgOk;
    int screenWidth;

    qScreen=QGuiApplication::primaryScreen();
    screenWidth=qScreen->geometry().width();

    pictureMiniatura=pictureURL.toLatin1().toBase64();
    pictureMiniatura=folderMiniaturas+pictureMiniatura+".jpg";
    qFile.setFileName(pictureMiniatura);
    existe=qFile.exists();

    if (existe)
    {
        pictureMiniatura="file://"+pictureMiniatura;
    }
    else
    {
        imgOk=qImage.load(pictureURL);
        if (imgOk)
        {
            qImage=qImage.scaledToWidth(screenWidth/2);
            qImage.save(pictureMiniatura);
            pictureMiniatura="file://"+pictureMiniatura;
        }
        else
        {
            pictureMiniatura=m_imagenErronea;
        }
    }

    return pictureMiniatura;
}
