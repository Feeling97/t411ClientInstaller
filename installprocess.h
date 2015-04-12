#ifndef INSTALLPROCESS_H
#define INSTALLPROCESS_H

#include <QLayout>

class installprocess : public QLayout
{
public:
    installprocess();
    ~installprocess();

private:
    int etape;
};

#endif // INSTALLPROCESS_H
