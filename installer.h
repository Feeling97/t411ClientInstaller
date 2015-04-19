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
#include "mainwindow.h"

class MainWindow;
class Installer : public QObject
{
    Q_OBJECT

public:
    explicit Installer(MainWindow *argparent = 0, QString argos = "");
    virtual ~Installer();

    QGridLayout* nextStage();
    void determineClient();

private slots:
    void saveDownloadedFile();

private:
    int etape;
    QString os, client;
    MainWindow *parent;
};

#endif // INSTALLER

