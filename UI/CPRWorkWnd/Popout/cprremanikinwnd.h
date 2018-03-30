#ifndef CPRREMANIKINWND_H
#define CPRREMANIKINWND_H

#include <QDialog>

namespace Ui {
class CPRReManikinWnd;
}

class CPRReManikinWnd : public QDialog
{
    Q_OBJECT

public:
    explicit CPRReManikinWnd(QWidget *parent = 0);
    ~CPRReManikinWnd();

private slots:
    void on_closeBtn_clicked();

private:
    Ui::CPRReManikinWnd *ui;
};

#endif // CPRREMANIKINWND_H
