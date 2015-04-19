#ifndef INSTALLER_H
#define INSTALLER_H

#include <QString>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QProgressBar>
#include <QSpacerItem>
#include <QtNetwork>
#include <QFile>
#include <QDataStream>
#include "mainwindow.h"
#include "filedownloader.h"

class MainWindow;
class Installer : public QObject
{
    Q_OBJECT

public:
    explicit Installer(MainWindow *argparent = 0, QString argos = "");
    virtual ~Installer();

    QGridLayout* nextStage(int incetape = 1);
    void determineClient();

private slots:
    void saveDownloadedFile();

private:
    int etape;
    QString os, client;
    MainWindow *parent;
    FileDownloader *fileDownload;
    bool isDownloaded;
};

#endif // INSTALLER

