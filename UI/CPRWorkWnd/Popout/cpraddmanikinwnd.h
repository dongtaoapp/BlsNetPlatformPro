#ifndef CPRADDMANIKINWND_H
#define CPRADDMANIKINWND_H

#include <QDialog>

namespace Ui {
class CPRAddManikinWnd;
}

class CPRAddManikinWnd : public QDialog
{
    Q_OBJECT

public:
    explicit CPRAddManikinWnd(QWidget *parent = 0);
    ~CPRAddManikinWnd();

private slots:
    void on_closeBtn_clicked();

private:
    Ui::CPRAddManikinWnd *ui;
};

#endif // CPRADDMANIKINWND_H
