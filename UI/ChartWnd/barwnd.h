#ifndef BARWND_H
#define BARWND_H

#include <QWidget>
namespace Ui {
class BarWnd;
}

class BarWnd : public QWidget
{
    Q_OBJECT

public:
    explicit BarWnd(QWidget *parent = 0);
    ~BarWnd();
private:
    Ui::BarWnd *ui;
};

#endif // BARWND_H
