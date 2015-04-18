#ifndef INSTALLER_H
#define INSTALLER_H

#include <QString>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>

QGridLayout* nextStage(QString client, QString os, int *etape);
QString determineClient(QString os);

#endif // INSTALLER

