#ifndef SCWND_H
#define SCWND_H

#include <QWidget>

namespace Ui {
class SCWnd;
}

class SCWnd : public QWidget
{
    Q_OBJECT

public:
    explicit SCWnd(QWidget *parent = 0);
    ~SCWnd();

private:
    Ui::SCWnd *ui;
};

#endif // SCWND_H
