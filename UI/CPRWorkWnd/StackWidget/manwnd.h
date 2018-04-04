#ifndef MANWND_H
#define MANWND_H

#include <QWidget>

namespace Ui {
class ManWnd;
}

class ManWnd : public QWidget
{
    Q_OBJECT

public:
    explicit ManWnd(QWidget *parent = 0);
    ~ManWnd();

private:
    Ui::ManWnd *ui;
};

#endif // MANWND_H
