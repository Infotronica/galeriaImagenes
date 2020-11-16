#ifndef FUNCIONESLOCALES_H
#define FUNCIONESLOCALES_H

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
#include <QScreen>
#include <QGuiApplication>

class FuncionesLocales: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString imagenErronea READ imagenErronea)

public:
    explicit FuncionesLocales(QObject *parent = nullptr);
    Q_INVOKABLE QString test();
    Q_INVOKABLE QString extractAbsoluteDir(QString fullName);
    Q_INVOKABLE QString extractBaseName(QString fullName);
    Q_INVOKABLE QString extractBaseExt(QString fullName);
    Q_INVOKABLE QString extractFileName(QString fullName);
    Q_INVOKABLE QString extractFilePath(QString fullName);
    QString imagenErronea();
    QString generarMiniatura(QString folderMiniaturas, QString pictureURL);

private slots:

public slots:

private:
    QString m_imagenErronea;

signals:
    void listadoCompleto();
};

extern FuncionesLocales funcionesLocales;

#endif // FUNCIONESLOCALES_H
