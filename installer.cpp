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

#include "installer.h"

Installer::Installer(MainWindow *argparent, QString argos) : QObject(argparent)
{
    parent = argparent;
    os = argos;
    etape = 0;
    isDownloaded = false;
    isInstalled = false;
    readyToInstall = false;
    readyToConfig = false;
    finished = false;
    port = 50500;
    QSettings regAccess("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", QSettings::NativeFormat);
    downloadsPath = regAccess.value("{374DE290-123F-4565-9164-39C4925E467B}", QProcessEnvironment::systemEnvironment().value("USERPROFILE") + "/Downloads").toString();
    if (!QDir(downloadsPath).exists())
        QDir(downloadsPath).mkdir(downloadsPath);
    torrentsPath = downloadsPath + "/Torrents";
    if (!QDir(torrentsPath).exists())
        QDir(torrentsPath).mkdir(torrentsPath);
    connect(this, SIGNAL(finishedStage()), this, SLOT(doNextStage()), Qt::QueuedConnection);
    connect(this, SIGNAL(setupConfig()), this, SLOT(makeConfig()), Qt::QueuedConnection);

    options = new Options(this);

    QPixmap t411(":/images/t411.png");
    t411label = new QLabel;
    t411label->setObjectName("t411label");
    t411label->setPixmap(t411);

    logolabel = new AboutLabel;

    FileDownloader test;
    if (!test.isConnected())
    {
        QMessageBox::critical(parent, "Erreur", "Vous n'êtes actuellement pas connecté à Internet<br />Veuillez vous connecter puis relancer le programme");
        exit(1);
    }
}

Installer::~Installer() {}

QGridLayout* Installer::nextStage(int incetape)
{
    etape = etape + incetape;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(logolabel, 0, 0, 0, 0, Qt::AlignTop);
    layout->addWidget(t411label, 0, 0, 0, 0, Qt::AlignRight | Qt::AlignTop);

    if (etape == 0) // Choix du client
    {
        QVBoxLayout *centerlayout = new QVBoxLayout;
        QVBoxLayout *boxlayout = new QVBoxLayout;
        chosedClient = new QGroupBox("Choisissez le client que vous voulez installer :", parent);
        utorrentButton = new QRadioButton("µTorrent 2.2.1", chosedClient);
        qbittorrentButton = new QRadioButton("qBittorrent", chosedClient);
        vuzeButton = new QRadioButton("Vuze", chosedClient);
        delugeButton = new QRadioButton("Deluge", chosedClient);
        if (client == "µTorrent 2.2.1")
            utorrentButton->setChecked(true);
        else if (client == "qBittorrent")
            qbittorrentButton->setChecked(true);
        else if (client == "Vuze")
            vuzeButton->setChecked(true);
        else if (client == "Deluge")
            delugeButton->setChecked(true);
        if (!(os == "Windows 8" || os == "Windows 8.1" || os == "Windows"))
           boxlayout->addWidget(utorrentButton, Qt::AlignVCenter);
        else
            delete utorrentButton;
        boxlayout->addWidget(qbittorrentButton, Qt::AlignVCenter);
        boxlayout->addWidget(vuzeButton, Qt::AlignVCenter);
        boxlayout->addWidget(delugeButton, Qt::AlignVCenter);
        chosedClient->setLayout(boxlayout);
        centerlayout->addWidget(chosedClient);
        centerlayout->addStretch();
        QPushButton *advancedOptions = new QPushButton("Avancé");
        connect(advancedOptions, SIGNAL(released()), this, SLOT(openOptions()));
        centerlayout->addWidget(advancedOptions);
        centerlayout->setContentsMargins(0, 100, 0, 0);
        layout->addLayout(centerlayout, 0, 0, 0, 0, Qt::AlignVCenter);
        connect(utorrentButton, SIGNAL(released()), this, SLOT(clientChanged()));
        connect(qbittorrentButton, SIGNAL(released()), this, SLOT(clientChanged()));
        connect(vuzeButton, SIGNAL(released()), this, SLOT(clientChanged()));
        connect(delugeButton, SIGNAL(released()), this, SLOT(clientChanged()));
    }
    else if (etape == 1) { // Etape 1: Présentation
        QVBoxLayout *centerlayout = new QVBoxLayout;
        QLabel *text = new QLabel("Ce programme va installer " + client + " pour " + os + " avec la configuration recommandée pour <a href=\"http://www.t411.io/\">t411.io</a><br /><br />"
        "Configuration recommandée :"
        "<ul>"
            "<li>Port " + QString::number(port) + "</li>"
            "<li>DHT/Recherche locale de pairs desactivée</li>"
            "<li>Mises à jour automatiques désactivées</li>"
            "<li>Aucune limite d'envoi et de réception</li>"
            "<li>Pré-allocation de l'espace disque pour les nouveaux fichiers</li>"
            "<li>Cryptage des échanges forcé</li>"
        "</ul>");
        text->setTextFormat(Qt::RichText);
        text->setTextInteractionFlags(Qt::TextBrowserInteraction);
        text->setOpenExternalLinks(true);
        centerlayout->addWidget(text);
        centerlayout->setContentsMargins(0, 100, 0, 0);
        centerlayout->addStretch();
        QPushButton *goToChoice = new QPushButton("Autres options");
        centerlayout->addWidget(goToChoice, Qt::AlignCenter);
        connect(goToChoice, SIGNAL(released()), this, SLOT(goToChoice()));
        layout->addLayout(centerlayout, 0, 0, 0, 0, Qt::AlignVCenter);
        parent->enableNext();
    }
    else if (etape == 2) { // Etape 2: Téléchargement
        QVBoxLayout *centerlayout = new QVBoxLayout;
        QProgressBar *dbar = new QProgressBar;

        centerlayout->addWidget(new QLabel("Téléchargement de " + client + "..."));

        if (!isDownloaded)
        {
            QUrl fileUrl;
            if (client == "qBittorrent")
                fileUrl.setUrl("http://88.198.168.163/logiciels/qbittorrent_3.1.11_setup.exe");
            else if (client == "µTorrent 2.2.1")
                fileUrl.setUrl("http://88.198.168.163/logiciels/2-2-1-build-25130-utorrent.exe");
            else if (client == "Vuze")
                fileUrl.setUrl("http://tuxange.org/t411ClientInstaller/installs/VuzeInstaller.exe");
            else if (client == "Deluge")
                fileUrl.setUrl("http://88.198.168.163/logiciels/deluge-1.3.5-win32-setup.exe");
            else
            {
                QMessageBox::critical(parent, "Erreur", "Impossible de déterminer le lien de téléchargement de " + client + " pour " + os);
                qApp->quit();
            }

            fileDownload = new FileDownloader(fileUrl, this);
            filePath = qApp->applicationDirPath();
            filePath += "/setup.exe";
            connect(fileDownload, SIGNAL(downloaded()), this, SLOT(saveDownloadedFile()));
            dbar->setValue(0);
        }
        else
        {
            isDownloaded = false;
            finished = true;
            dbar->setValue(33);
        }

        centerlayout->addWidget(dbar);
        layout->addLayout(centerlayout, 0, 0, 0, 0, Qt::AlignCenter);
    }
    else if (etape == 3) { // Etape 3: Installation du client
        QVBoxLayout *centerlayout = new QVBoxLayout;
        QProgressBar *dbar = new QProgressBar;

        centerlayout->addWidget(new QLabel("Installation de " + client + "..."));

        if (!isInstalled)
        {
            if (client == "qBittorrent" || client == "Deluge")
            {
                killProcessByName(QString(client + ".exe").toLower().toUtf8().data());
                QProcess *setup = new QProcess(this);
                QStringList args;
                args << "/S";
                setup->start(qApp->applicationDirPath() + "/setup.exe", args);
                connect(setup, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finishedSetup(int, QProcess::ExitStatus)));
                dbar->setValue(33);
            }
            else if (client == "Vuze")
            {
                killProcessByName("Azureus.exe");
                QProcess *setup = new QProcess(this);
                QStringList args;
                args << "-q" << "-overwrite";
                setup->start(qApp->applicationDirPath() + "/setup.exe", args);
                connect(setup, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finishedSetup(int, QProcess::ExitStatus)));
                dbar->setValue(33);
            }
            else if (client == "µTorrent 2.2.1")
            {
                if (readyToInstall)
                {
                    QString target = QProcessEnvironment::systemEnvironment().value("ProgramFiles");

                    if (target.isEmpty())
                    {
                        QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Impossible d'accéder à la variable d'environnement %ProgramFiles%");
                        qApp->quit();
                    }

                    if (!QDir(target + "/uTorrent").exists()) { QDir().mkdir(target + "/uTorrent"); }
                    if (!QDir(QProcessEnvironment::systemEnvironment().value("AppData") + "/uTorrent").exists()) { QDir().mkdir(QProcessEnvironment::systemEnvironment().value("AppData") + "/uTorrent"); }
                    if (QFile(target + "/uTorrent/uTorrent.exe").exists()) { QFile::remove(target + "/uTorrent/uTorrent.exe"); }

                    copy(qApp->applicationDirPath() + "/setup.exe", target + "/uTorrent/uTorrent.exe");
                    QTimer::singleShot(50, this, SLOT(finishedSetup()));
                    dbar->setValue(33);
                }
                else
                {
                    killProcessByName("uTorrent.exe");
                    QTimer::singleShot(2000, this, SLOT(installuTorrent()));
                    dbar->setValue(33);
                }
            }
            else
            {
                QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Contactez Feeling97 en indiquant votre OS et le client choisi");
                qApp->quit();
            }
        }
        else
        {
            dbar->setValue(66);
            finished = true;
        }
        centerlayout->addWidget(dbar);
        layout->addLayout(centerlayout, 0, 0, 0, 0, Qt::AlignCenter);
    }
    else if (etape == 4) { // Etape 4: Installation de la config
        QVBoxLayout *centerlayout = new QVBoxLayout;
        QProgressBar *dbar = new QProgressBar;

        centerlayout->addWidget(new QLabel("Installation de la configuration recommandée pour " + client + "..."));

        if (client == "qBittorrent")
        {
            QString target = QProcessEnvironment::systemEnvironment().value("AppData");

            if (target.isEmpty())
            {
                QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Impossible d'accéder à la variable d'environnement %AppData%");
                qApp->quit();
            }

            target += "/qBittorrent";
            configPath = target + "/qBittorrent.ini";

            if (!readyToConfig)
            {
                bool replaceConfig = true;
                if (QFile::exists(configPath))
                {
                    if (!wannaReplace())
                    {
                        replaceConfig = false;
                        dbar->setValue(100);
                        finished = true;
                    }
                }

                if (replaceConfig)
                {
                    killProcessByName("qBittorrent.exe");
                    QTimer::singleShot(2000, this, SLOT(installConfig()));
                    dbar->setValue(66);
                }
            }
            else if (!isDownloaded)
            {
                if (!QDir(target).exists())
                    QDir().mkdir(target);
                rename(configPath, target + "/qBittorrent.bak.ini");
                QUrl fileUrl;
                fileUrl.setUrl("http://tuxange.org/t411ClientInstaller/dynConfigs/qBittorrent.ini");
                fileDownload = new FileDownloader(fileUrl, this);
                filePath = configPath;
                connect(fileDownload, SIGNAL(downloaded()), this, SLOT(saveDownloadedFile()));
                dbar->setValue(66);
            }
            else
            {
                emit setupConfig();
                dbar->setValue(100);
                finished = true;
            }
        }
        else if (client == "µTorrent 2.2.1")
        {
            QString target = QProcessEnvironment::systemEnvironment().value("AppData");

            if (target.isNull())
            {
                QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Impossible d'accéder à la variable d'environnement %AppData%");
                qApp->quit();
            }

            target += "/uTorrent";
            configPath = target + "/settings.dat";

            if (!readyToConfig)
            {
                bool replaceConfig = true;

                if (QFile::exists(configPath))
                {
                    if (!wannaReplace())
                    {
                        replaceConfig = false;
                        dbar->setValue(100);
                        finished = true;
                    }
                }

                if (replaceConfig)
                {
                    copy(target + "/resume.dat", target + "/resume.bak.dat");
                    killProcessByName("uTorrent.exe");
                    QTimer::singleShot(2000, this, SLOT(installConfig()));
                    dbar->setValue(66);
                }
            }
            else if (!isDownloaded)
            {
                if (!QDir(target).exists())
                    QDir().mkdir(target);
                remove(target + "/resume.dat");
                rename(target + "/resume.bak.dat", target + "/resume.dat");
                rename(configPath, target + "/settings.bak.dat");
                rename(target + "/settings.dat.old", target + "/settings.bak.dat.old");
                QUrl fileUrl;
                fileUrl.setUrl("http://tuxange.org/t411ClientInstaller/dynConfigs/uTorrent.dat");
                fileDownload = new FileDownloader(fileUrl, this);
                filePath = configPath;
                connect(fileDownload, SIGNAL(downloaded()), this, SLOT(saveDownloadedFile()));
                dbar->setValue(66);
            }
            else
            {
                emit setupConfig();
                dbar->setValue(100);
                finished = true;
            }
        }
        else if (client == "Vuze")
        {
            QString target = QProcessEnvironment::systemEnvironment().value("AppData");

            if (target.isEmpty())
            {
                QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Impossible d'accéder à la variable d'environnement %AppData%");
                qApp->quit();
            }

            target += "/Azureus";
            configPath = target + "/azureus.config";

            if (!readyToConfig)
            {
                bool replaceConfig = true;
                if (QFile::exists(configPath))
                {
                    if (!wannaReplace())
                    {
                        replaceConfig = false;
                        dbar->setValue(100);
                        finished = true;
                    }
                }

                if (replaceConfig)
                {
                    killProcessByName("Azureus.exe");
                    QTimer::singleShot(2000, this, SLOT(installConfig()));
                    dbar->setValue(66);
                }
            }
            else if (!isDownloaded)
            {
                if (!QDir(target).exists())
                    QDir().mkdir(target);
                rename(configPath, target + "/azureus.bak.config");
                QUrl fileUrl;
                fileUrl.setUrl("http://tuxange.org/t411ClientInstaller/dynConfigs/Vuze.config");
                fileDownload = new FileDownloader(fileUrl, this);
                filePath = configPath;
                connect(fileDownload, SIGNAL(downloaded()), this, SLOT(saveDownloadedFile()));
                dbar->setValue(66);
            }
            else
            {
                emit setupConfig();
                dbar->setValue(100);
                finished = true;
            }
        }
        else if (client == "Deluge")
        {
            QString target = QProcessEnvironment::systemEnvironment().value("AppData");

            if (target.isEmpty())
            {
                QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Impossible d'accéder à la variable d'environnement %AppData%");
                qApp->quit();
            }

            target += "/deluge";
            configPath = target + "/core.conf";

            if (!readyToConfig)
            {
                bool replaceConfig = true;
                if (QFile::exists(configPath))
                {
                    if (!wannaReplace())
                    {
                        replaceConfig = false;
                        dbar->setValue(100);
                        finished = true;
                    }
                }

                if (replaceConfig)
                {
                    killProcessByName("deluge.exe");
                    QTimer::singleShot(2000, this, SLOT(installConfig()));
                    dbar->setValue(66);
                }
            }
            else if (!isDownloaded)
            {
                if (!QDir(target).exists())
                    QDir().mkdir(target);
                rename(configPath, target + "/core.bak.conf");
                QUrl fileUrl;
                fileUrl.setUrl("http://tuxange.org/t411ClientInstaller/dynConfigs/Deluge.conf");
                fileDownload = new FileDownloader(fileUrl, this);
                filePath = configPath;
                connect(fileDownload, SIGNAL(downloaded()), this, SLOT(saveDownloadedFile()));
                dbar->setValue(66);
            }
            else
            {
                emit setupConfig();
                dbar->setValue(100);
                finished = true;
            }
        }
        else
        {
            QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Contactez Feeling97 en indiquant votre OS et le client que le programme vous conseille");
            qApp->quit();
        }

        centerlayout->addWidget(dbar);
        layout->addLayout(centerlayout, 0, 0, 0, 0, Qt::AlignCenter);
    }
    else if (etape == 5) { // Etape 5: Fin
        QVBoxLayout *centerlayout = new QVBoxLayout;
        launchClient = new QCheckBox("Lancer " + client + " à la fermeture", parent);
        createLink = new QCheckBox("Créer un raccourci pour " + client + " sur le bureau", parent);
        launchClient->setChecked(true);
        createLink->setChecked(true);
        centerlayout->addWidget(new QLabel(client + " pour " + os + " est maintenant installé avec sa configuration recommandée"));
        centerlayout->addWidget(launchClient);
        if (client == "Vuze" || client == "Deluge")
            createLink->setChecked(false);
        else
            centerlayout->addWidget(createLink);
        layout->addLayout(centerlayout, 0, 0, 0, 0, Qt::AlignVCenter);
        remove(qApp->applicationDirPath() + "/setup.exe");
        parent->enableFinish();
    }

    if (etape < 5 && finished)
    {
        finished = false;
        emit finishedStage();
    }

    if (etape > 1)
        parent->disableQuit();

    return layout;
}

void Installer::determineClient()
{
    if (os == "Windows 8.1" || os == "Windows 8" || os == "Windows")
        client = "qBittorrent";
    else
        client = "µTorrent 2.2.1";
}

void Installer::setOption(QString name, QVariant value)
{
    if (name == "port")
        port = value.toInt();
    else if (name == "files")
        downloadsPath = value.toString();
    else
        torrentsPath = value.toString();
}

QString Installer::getOption(QString name)
{
    if (name == "port")
        return QString::number(port);
    else if (name == "files")
        return QDir::toNativeSeparators(downloadsPath);
    else
        return QDir::toNativeSeparators(torrentsPath);
}

void Installer::makeConfig()
{
    QFile *configFile = new QFile(configPath);
    if (!configFile->open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(parent, "Erreur", "Impossible de lire le fichier de configuration<br />" + configPath + "<br />Erreur : " + configFile->errorString());
        qApp->quit();
    }

    QByteArray configBinary = configFile->readAll();
    QByteArray dPath;
    QByteArray tPath;
    if (client == "µTorrent 2.2.1" || client == "Vuze")
    {
        dPath.append(downloadsPath.length() + ":" + QDir::toNativeSeparators(downloadsPath));
        tPath.append(torrentsPath.length() + ":" + QDir::toNativeSeparators(torrentsPath));
        configBinary.replace(QByteArray::number(50500), QByteArray::number(port));
        configBinary.replace("13:DOWNLOADSHERE", dPath);
        configBinary.replace("12:TORRENTSHERE", tPath);
    }
    else
    {
        dPath.append(QDir::toNativeSeparators(downloadsPath));
        tPath.append(QDir::toNativeSeparators(torrentsPath));
        configBinary.replace("PORTHERE", QByteArray::number(port));
        configBinary.replace("DOWNLOADSHERE", dPath);
        configBinary.replace("TORRENTSHERE", tPath);
    }

    configFile->close();

    if (!configFile->open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::critical(parent, "Erreur", "Impossible d'écrire dans le fichier de configuration<br />" + configPath + "<br />Erreur : " + configFile->errorString());
        qApp->quit();
    }

    configFile->write(configBinary);
    configFile->close();
}

void Installer::doRefreshLayout(QGridLayout *newlayout)
{
    emit refreshLayout(newlayout);
}

void Installer::doNextStage(int incetape)
{
    doRefreshLayout(nextStage(incetape));
}

void Installer::goToChoice()
{
    doNextStage(-1);
}

void Installer::clientChanged()
{
    if (utorrentButton->isChecked())
        client = "µTorrent 2.2.1";
    else if (qbittorrentButton->isChecked())
        client = "qBittorrent";
    else if (vuzeButton->isChecked())
        client = "Vuze";
    else if (delugeButton->isChecked())
        client = "Deluge";
    else
    {
        QMessageBox::critical(parent, "Erreur", "Imposible de mémoriser le client à installer");
        qApp->quit();
    }
}

void Installer::openOptions()
{
    options->open();
}

bool Installer::wannaReplace()
{
    QMessageBox wannaReplace(QMessageBox::Question, "Remplacer", "Une configuration existe déjà pour " + client + " pour " + os + "<br />Voulez-vous la remplacer ?<br />Il est conseillé de la remplacer sauf si vous savez ce que vous faites", QMessageBox::Yes | QMessageBox::No);
    wannaReplace.setButtonText(QMessageBox::Yes, "Oui");
    wannaReplace.setButtonText(QMessageBox::No, "Non");
    wannaReplace.setDefaultButton(QMessageBox::Yes);

    if (wannaReplace.exec() == QMessageBox::Yes)
        return true;
    else
        return false;
}

void Installer::saveDownloadedFile()
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(parent, "Erreur", "Impossible d'écrire dans le fichier <br />" + filePath + "<br />\
        Erreur : " + file.errorString());
        qApp->quit();
    }
    QDataStream out(&file);
    out.writeRawData(fileDownload->downloadedData().data(), fileDownload->downloadedData().length());
    isDownloaded = true;
    doNextStage(0);
}

void Installer::finishedSetup()
{
    isInstalled = true;
    doNextStage(0);
}

void Installer::finishedSetup(int code, QProcess::ExitStatus status)
{
    (void)code; // Ne fait rien, enlève juste le warning de variable inutilisée
    if (status == QProcess::NormalExit)
    {
        if (client == "Vuze")
            killProcessByName("Azureus.exe");
        isInstalled = true;
        doNextStage(0);
    }
    else
    {
        QMessageBox::critical(parent, "Erreur", "Une erreur est survenue pendant l'installation de " + client + " pour " + os + "<br />\
        Vous pouvez demander de l'aide <a href=\"http://forum.t411.io/categories/info/\">sur le forum</a>");
        qApp->quit();
    }
}

void Installer::installuTorrent()
{
    readyToInstall = true;
    doNextStage(0);
}

void Installer::installConfig()
{
    readyToConfig = true;
    doNextStage(0);
}

void Installer::pressedFinish()
{
    if (launchClient->isChecked())
    {
        QProcess *clientProcess = new QProcess;

        QString path = client;
        QString exeName = client;
        if (client == "µTorrent 2.2.1")
        {
            path = "uTorrent";
            exeName = "uTorrent";
        }
        else if (client == "Vuze")
        {
            exeName = "Azureus";
            if (QDir(QProcessEnvironment::systemEnvironment().value("ProgramFiles") + "/Vuze").exists())
                path = QProcessEnvironment::systemEnvironment().value("ProgramFiles") + "/Vuze";
            else
            {
                path = QProcessEnvironment::systemEnvironment().value("ProgramFiles");
                path.chop(6);
                path += "/Vuze";
            }

            clientProcess->startDetached(QDir::toNativeSeparators(path + "/" + exeName + ".exe"), QStringList());
        }
        else if (client == "Deluge")
            exeName = "deluge";

        clientProcess->startDetached(QDir::toNativeSeparators(QProcessEnvironment::systemEnvironment().value("ProgramFiles") + "/" + path + "/" + exeName + ".exe"), QStringList());
    }

    if (createLink->isChecked())
    {
        if (client == "µTorrent 2.2.1")
            QFile::link(QDir::toNativeSeparators(QProcessEnvironment::systemEnvironment().value("ProgramFiles") + "/uTorrent/uTorrent.exe"), QDir::toNativeSeparators(QProcessEnvironment::systemEnvironment().value("UserProfile") + "/Desktop/µTorrent.lnk"));
        else if (client == "qBittorrent")
            QFile::link(QDir::toNativeSeparators(QProcessEnvironment::systemEnvironment().value("ProgramFiles") + "/qBittorrent/qBittorrent.exe"), QDir::toNativeSeparators(QProcessEnvironment::systemEnvironment().value("UserProfile") + "/Desktop/" + client + ".lnk"));
    }

    qApp->quit();
}

void Installer::copy(QString argsource, QString argtarget)
{
    argsource = QDir::toNativeSeparators(argsource);
    argtarget = QDir::toNativeSeparators(argtarget);
    if (QFile::exists(argsource))
    {
        if (QFile::copy(argsource, argtarget))
            return;
        else
        {
            QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Avez-vous les droits d'accès à <br />" + argtarget + " ?");
            qApp->quit();
        }
    }
}

void Installer::rename(QString argsource, QString argtarget)
{
    argsource = QDir::toNativeSeparators(argsource);
    argtarget = QDir::toNativeSeparators(argtarget);
    if (QFile::exists(argsource))
    {
        if (QFile::rename(argsource, argtarget))
            return;
        else if (QFile::remove(argtarget) && QFile::rename(argsource, argtarget))
            return;
        else
        {
            QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Avez-vous les droits d'accès à <br />" + argtarget + " ?");
            qApp->quit();
        }
    }
}

void Installer::remove(QString argfile)
{
    argfile = QDir::toNativeSeparators(argfile);
    if (QFile::exists(argfile))
    {
        if (QFile::remove(argfile))
            return;
        else
        {
            QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Avez-vous les droits d'accès à <br />" + argfile + " ?");
            qApp->quit();
        }
    }
}

void Installer::killProcessByName(const char *filename)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof (pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        char mbstr[128];
        std::wcstombs(mbstr, pEntry.szExeFile, 128);
        if (strcmp(mbstr, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD) pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

MainWindow* Installer::getParent()
{
    return parent;
}
