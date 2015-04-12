#ifndef INSTALLPROCESS_H
#define INSTALLPROCESS_H

#include <QLayout>

class installprocess : public QGridLayout
{
public:
    installprocess(QString os);
    ~installprocess();

private:
    int etape;
    QString os;
    QString client;
};

#endif // INSTALLPROCESS_H
