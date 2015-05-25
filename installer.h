/*  This file is part of t411 Client Installer.

    t411 Client Installer is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    t411 Client Installer is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with t411 Client Installer.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef INSTALLER_H
#define INSTALLER_H

#include <QApplication>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QProgressBar>
#include <QTextCodec>
#include <QNetworkReply>
#include <QDir>
#include <QTimer>
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
    bool wannaReplace();
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
    QRadioButton *utorrentButton, *qbittorrentButton, *bittorrentButton, *vuzeButton, *delugeButton;
    bool isDownloaded, isInstalled, readyToInstall, readyToConfig, finished;
};

#include "filedownloader.h"

#endif // INSTALLER

