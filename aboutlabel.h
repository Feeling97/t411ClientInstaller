#ifndef ABOUTLABEL_H
#define ABOUTLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QMessageBox>

class AboutLabel : public QLabel
{
    Q_OBJECT

public:
    explicit AboutLabel();
    ~AboutLabel();

public slots:
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // ABOUTLABEL_H
