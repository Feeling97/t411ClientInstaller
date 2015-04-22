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
#include <QProcess>

#if defined(Q_OS_WIN)
    #include <windows.h>
    #include <process.h>
    #include <Tlhelp32.h>
    #include <winbase.h>
    #include <string.h>
#endif

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
    void finishedSetup();
    void finishedSetup(int code, QProcess::ExitStatus status);
    void installuTorrent();
    void installConfig();

private:
    void copy(QString argsource, QString argtarget);
    void rename(QString argsource, QString argtarget);
    void remove(QString argfile);
    #if defined(Q_OS_WIN)
        void killProcessByName(const char *filename);
    #endif

    int etape;
    QString os, client, filePath;
    MainWindow *parent;
    FileDownloader *fileDownload;
    bool isDownloaded, isInstalled, readyToInstall, readyToConfig;
};

#endif // INSTALLER

