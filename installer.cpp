#include "installer.h"

Installer::Installer(MainWindow *argparent, QString argos) : QObject(argparent) {
    parent = argparent;
    os = argos;
    etape = 0;
    isDownloaded = false;
    isInstalled = false;
    readyToInstall = false;
    readyToConfig = false;
    finished = false;
    connect(this, SIGNAL(finishedStage()), this, SLOT(doNextStage()), Qt::QueuedConnection);
}

Installer::~Installer() {}

QGridLayout* Installer::nextStage(int incetape)
{
    etape = etape + incetape;
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(new QLabel("<h1>t411 Client Installer <small>v0.2.2</small></h1>"), 0, 0, 0, 0, Qt::AlignTop);
    QPixmap logo(":/images/logo.png");
    QLabel *logolabel = new QLabel;
    logolabel->setPixmap(logo);
    layout->addWidget(logolabel, 0, 0, 0, 0, Qt::AlignRight | Qt::AlignTop);

    if (etape == 1) { // Etape 1: Présentation
        layout->addWidget(new QLabel("Ce programme va installer " + client + " pour " + os + " avec la configuration recommandée pour <a href=\"http://www.t411.io/\">t411.io</a><br /><br />\
        Configuration recommandée :\
        <ul>\
            <li>Port 50500</li>\
            <li>DHT/Recherche locale de pairs desactivé</li>\
            <li>Mises à jour automatiques désactivées</li>\
            <li>Aucune limite d'envoi et de réception</li>\
            <li>Pré-allocation de l'espace disque pour les nouveaux fichiers</li>\
            <li>Cryptage des échanges forcé</li>\
        </ul>\
        "), 0, 0, 0, 0);
        parent->enableNext();
    }
    else if (etape == 2) { // Etape 2: Téléchargement
        QVBoxLayout *centerlayout = new QVBoxLayout();
        QProgressBar *dbar = new QProgressBar();

        centerlayout->addWidget(new QLabel("Téléchargement de " + client + "..."));

        if (!isDownloaded)
        {
            QUrl fileUrl;
            if (client == "qBittorrent")
                fileUrl.setUrl("http://irc.t411.io/logiciels/qbittorrent_3.1.11_setup.exe");
            else if (client == "µTorrent 2.2.1")
                fileUrl.setUrl("http://irc.t411.io/logiciels/2-2-1-build-25130-utorrent.exe");
            else if (client == "Transmission 2.84" && os == "Mac")
                fileUrl.setUrl("http://irc.t411.io/logiciels/Transmission-2.84.dmg");
            else if (os == "Linux")
            {
                QMessageBox::critical(parent, "Erreur", "Le téléchargement et l'installation de " + client + " pour " + os + " n'est pas encore pris en charge<br />\
                Vous pouvez aller sur le site officiel de " + client + " en cliquant <a href=\"http://www.transmissionbt.com/\">ici</a>");
                qApp->quit();
            }
            else
            {
                QMessageBox::critical(parent, "Erreur", "Impossible de déterminer le lien de téléchargement de " + client + " pour " + os);
                qApp->quit();
            }

            fileDownload = new FileDownloader(fileUrl, this);
            filePath = qApp->applicationDirPath();
            #if defined(Q_OS_WIN)
                filePath += "/setup.exe";
            #elif defined(Q_OS_MAC)
                filePath += "/setup.dmg";
            #endif
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
        QVBoxLayout *centerlayout = new QVBoxLayout();
        QProgressBar *dbar = new QProgressBar();

        centerlayout->addWidget(new QLabel("Installation de " + client + "..."));

        if (!isInstalled)
        {
            if (client == "qBittorrent")
            {
                #if defined(Q_OS_WIN)
                    killProcessByName("qBittorrent.exe");
                #endif
                QProcess *setup = new QProcess(this);
                QStringList args;
                args << "/S";
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
                    #if defined(Q_OS_WIN)
                        killProcessByName("uTorrent.exe");
                    #endif
                    QTimer::singleShot(2000, this, SLOT(installuTorrent()));
                    dbar->setValue(33);
                }
            }
            else if (client == "Transmission 2.84" && os == "Mac")
            {
                QProcess *setup = new QProcess(this);
                setup->start(qApp->applicationDirPath() + "/setup.dmg");
                connect(setup, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finishedSetup(int, QProcess::ExitStatus)));
                dbar->setValue(33);
            }
            else
            {
                QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Contactez Feeling97 en indiquant votre OS et le client que le programme vous conseille");
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
        QVBoxLayout *centerlayout = new QVBoxLayout();
        QProgressBar *dbar = new QProgressBar();

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

            if (!readyToConfig)
            {
                #if defined(Q_OS_WIN)
                    killProcessByName("qBittorrent.exe");
                #endif
                QTimer::singleShot(2000, this, SLOT(installConfig()));
                dbar->setValue(66);
            }
            else if (!isDownloaded)
            {
                rename(target + "/qBittorrent.ini", target + "/qBittorrent.bak.ini");
                QUrl fileUrl;
                fileUrl.setUrl("http://tuxange.org/t411ClientInstaller/configs/qBittorrent.ini");
                fileDownload = new FileDownloader(fileUrl, this);
                filePath = target + "/qBittorrent.ini";
                connect(fileDownload, SIGNAL(downloaded()), this, SLOT(saveDownloadedFile()));
                dbar->setValue(66);
            }
            else
            {
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

            if (!readyToConfig)
            {
                copy(target + "/resume.dat", target + "/resume.bak.dat");
                #if defined(Q_OS_WIN)
                    killProcessByName("uTorrent.exe");
                #endif
                QTimer::singleShot(2000, this, SLOT(installConfig()));
                dbar->setValue(66);
            }
            else if (!isDownloaded)
            {
                remove(target + "/resume.dat");
                rename(target + "/resume.bak.dat", target + "/resume.dat");
                rename(target + "/settings.dat", target + "/settings.bak.dat");
                rename(target + "/settings.dat.old", target + "/settings.bak.dat.old");
                QUrl fileUrl;
                fileUrl.setUrl("http://tuxange.org/t411ClientInstaller/configs/uTorrent.dat");
                fileDownload = new FileDownloader(fileUrl, this);
                filePath = target + "/settings.dat";
                connect(fileDownload, SIGNAL(downloaded()), this, SLOT(saveDownloadedFile()));
                dbar->setValue(66);
            }
            else
            {
                dbar->setValue(100);
                finished = true;
            }
        }
        else if (client == "Transmission 2.84" && os == "Mac")
        {
            QMessageBox::critical(parent, "Erreur", "Le téléchargement et l'installation de la configuration de " + client + " pour " + os + " n'est pas encore pris en charge<br />\
            Vous pouvez aller sur le tuto de configuration de " + client + " en cliquant <a href=\"http://irc.t411.io/pics/tuto-tr-mac.png/\">ici</a>");
            qApp->quit();
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
        QVBoxLayout *centerlayout = new QVBoxLayout();
        launchClient = new QCheckBox("Lancer " + client + " à la fermeture", parent);
        createLink = new QCheckBox("Créer un raccourci pour " + client + " sur le bureau", parent);
        launchClient->setChecked(true);
        createLink->setChecked(true);
        centerlayout->addWidget(new QLabel(client + " pour " + os + " est maintenant installé avec sa configuration recommandée"));
        centerlayout->addWidget(launchClient);
        centerlayout->addWidget(createLink);
        layout->addLayout(centerlayout, 0, 0, 0, 0, Qt::AlignVCenter);
        parent->enableFinish();
    }

    if (etape < 5 && finished)
    {
        finished = false;
        emit finishedStage();
    }

    return layout;
}

void Installer::determineClient()
{
    #if defined(Q_OS_WIN) // Windows
        if (os == "Windows 8.1")
            client = "qBittorrent";
        else if (os == "Windows 8")
            client = "qBittorrent";
        else if (os == "Windows 7")
            client = "µTorrent 2.2.1";
        else if (os == "Windows Vista")
            client = "µTorrent 2.2.1";
        else if (os == "Windows XP x64")
            client = "µTorrent 2.2.1";
        else if (os == "Windows XP")
            client = "µTorrent 2.2.1";
        else if (os == "Windows 2000")
            client = "µTorrent 2.2.1";
        else if (os == "Windows NT")
            client = "µTorrent 2.2.1";
        else
        {
            QMessageBox::critical(parent, "Erreur", "Impossible de déterminer le client correspondant à votre système<br />Vous pouvez utiliser le checker en ligne :<br /><a href='http://irc.t411.io/checker/'>Cliquez ici</a>");
            qApp->quit();
        }
    #else // Linux et Mac
        client = "Transmission 2.84";
    #endif
}

void Installer::doNextStage(int incetape)
{
    parent->refreshLayout(nextStage(incetape));
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
        QProcess *clientProcess = new QProcess();

        QString path;
        if (client == "µTorrent 2.2.1")
        {
            path = "uTorrent";
        }

        clientProcess->startDetached(QDir::toNativeSeparators(QProcessEnvironment::systemEnvironment().value("ProgramFiles") + "/" + path + "/" + path + ".exe"), QStringList());
    }

    if (createLink->isChecked())
    {
        if (client == "µTorrent 2.2.1")
            QFile::link(QDir::toNativeSeparators(QProcessEnvironment::systemEnvironment().value("ProgramFiles") + "/uTorrent/uTorrent.exe"), QDir::toNativeSeparators(QProcessEnvironment::systemEnvironment().value("UserProfile") + "/Desktop/µTorrent.lnk"));
        else if (client == "qBittorrent")
            QFile::link(QDir::toNativeSeparators(QProcessEnvironment::systemEnvironment().value("ProgramFiles") + "/" + client + "/" + client + ".exe"), QDir::toNativeSeparators(QProcessEnvironment::systemEnvironment().value("UserProfile") + "/Desktop/" + client + ".lnk"));
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
        {
            return;
        }
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
        {
            return;
        }
        else if (QFile::remove(argtarget) && QFile::rename(argsource, argtarget))
        {
            return;
        }
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
        {
            return;
        }
        else
        {
            QMessageBox::critical(parent, "Erreur", "Impossible d'installer " + client + " pour " + os + "<br />Avez-vous les droits d'accès à <br />" + argfile + " ?");
            qApp->quit();
        }
    }
}

#if defined(Q_OS_WIN)
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
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                                          (DWORD) pEntry.th32ProcessID);
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
#endif
