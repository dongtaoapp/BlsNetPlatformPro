#ifndef CPRCHANGEWND_H
#define CPRCHANGEWND_H

#include <QDialog>

namespace Ui {
class CPRChangeWnd;
}

class CPRChangeWnd : public QDialog
{
    Q_OBJECT

public:
    explicit CPRChangeWnd(QWidget *parent = 0);
    ~CPRChangeWnd();

private slots:
    void on_closeBtn_clicked();

private:
    Ui::CPRChangeWnd *ui;
};

#endif // CPRCHANGEWND_H
