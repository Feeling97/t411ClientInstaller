#ifndef INSTALLPROCESS_H
#define INSTALLPROCESS_H

#include <QLayout>

class installprocess : public QLayout
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
