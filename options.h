#ifndef OPTIONS_H
#define OPTIONS_H

#include "installer.h"

class Installer;
class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(Installer *arg_parent = 0);
    ~Options();
    void open();

private slots:
    void closeEvent(QCloseEvent *event);
    void valueChanged(QString text);

private:
    Installer *parent;
    QGroupBox *contentBox;
    QLineEdit *portLine, *fileLine, *torrentLine;
};

class ClickEater : public QObject
{
    Q_OBJECT
protected:
    bool eventFilter(QObject *obj, QEvent *event)
    {
        if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() != Qt::LeftButton)
                return QObject::eventFilter(obj, event);
            mouseEvent->accept();

            QLineEdit *object = static_cast<QLineEdit*>(obj);
            object->setText(QFileDialog::getExistingDirectory());

            return true;
        }
        else
            return QObject::eventFilter(obj, event);
    }
};

#endif // OPTIONS_H
