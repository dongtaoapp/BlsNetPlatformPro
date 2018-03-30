#ifndef ADDMANIKINWND_H
#define ADDMANIKINWND_H

#include <QWidget>

namespace Ui {
class addManikinWnd;
}
//IP地址
class addManikinWnd : public QWidget
{
    Q_OBJECT
public:
    explicit addManikinWnd(QWidget *parent = 0);
    ~addManikinWnd();
    void addManikinInfo();
public slots:
    void okBtnClickedEvent();
    void backBtnClickedEvent();
Q_SIGNALS:
    void backSignal();

    void addManikin(QString Remark);
private:
    Ui::addManikinWnd *ui;
};

#endif // ADDMANIKINWND_H
