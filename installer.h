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
#include <QCheckBox>
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>

#include <windows.h>
#include <Tlhelp32.h>

#include "mainwindow.h"
#include "aboutlabel.h"

class MainWindow;
class FileDownloader;
class AboutLabel;
class Installer : public QObject
{
    Q_OBJECT

public:
    explicit Installer(MainWindow *argparent = 0, QString argos = "");
    virtual ~Installer();
    QGridLayout* nextStage(int incetape = 1);
    void determineClient();

public slots:
    void doNextStage(int incetape = 1);

signals:
    void refreshLayout(QGridLayout*);
    void finishedStage();

private slots:
    void doRefreshLayout(QGridLayout *newlayout);
    void saveDownloadedFile();
    void finishedSetup();
    void finishedSetup(int code, QProcess::ExitStatus status);
    void installuTorrent();
    void installConfig();
    void pressedFinish();
    void goToChoice();
    void clientChanged();

private:
    void copy(QString argsource, QString argtarget);
    void rename(QString argsource, QString argtarget);
    void remove(QString argfile);
    void killProcessByName(const char *filename);

    int etape;
    QString os, client, filePath;
    MainWindow *parent;
    FileDownloader *fileDownload;
    QCheckBox *launchClient, *createLink;
    QGroupBox *chosedClient;
    QLabel *t411label;
    AboutLabel *logolabel;
    QRadioButton *utorrentButton, *qbittorrentButton;
    bool isDownloaded, isInstalled, readyToInstall, readyToConfig, finished;
};

#include "filedownloader.h"

#endif // INSTALLER

