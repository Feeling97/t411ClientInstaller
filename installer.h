#ifndef INSTALLER_H
#define INSTALLER_H

#include <QString>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include "mainwindow.h"

QGridLayout* nextStage(MainWindow *parent, QString client, QString os, int *etape);
QString determineClient(QString os);

#endif // INSTALLER

