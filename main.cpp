#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "gallerymanagercovers.h"
#include "gallerymanagerpictures.h"
#include "funcioneslocales.h"

/*
    Este es un proyecto galería de imágenes sencilla
    el propósito es que tu la incluyas en tus proyectos
    si te es de utilidad.
    No es una aplicación de galeria completa con
    un Drawer, Menu etc.
    Está en idioma español porque es mi idioma natural,
    si gustas puedes traducir los comentarios, mensajes,
    funciones, objetos etc a ingles o tu idioma natural.

    Gracias
*/

QString folderMiniaturas;

int main(int argc, char *argv[])
{
    QDir qDir;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    folderMiniaturas=QStandardPaths::standardLocations(QStandardPaths::PicturesLocation)[0]+"/.miniaturas/";
#endif
#if (defined(Q_OS_WIN) || defined(Q_OS_LINUX) || defined(Q_OS_DARWIN)) && !defined(Q_OS_ANDROID)
    folderMiniaturas=QDir::homePath()+"/miniaturas/";
#endif

    qDir.setPath(folderMiniaturas);
    if (!qDir.exists())
    {
        qDir.mkpath(folderMiniaturas);
    }

    qmlRegisterType<GalleryManagerCovers>("gallery.manager.covers", 1, 0, "GalleryManagerCovers");
    qmlRegisterType<GalleryManagerPictures>("gallery.manager.pictures", 1, 0, "GalleryManagerPictures");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("funcionesLocales",&funcionesLocales);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
