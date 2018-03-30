#ifndef CHOSEMANIKINWND_H
#define CHOSEMANIKINWND_H
#include <QStackedWidget>
#include "registermanikinwnd.h"
#include "addmanikinwnd.h"
class ChoseManikinWnd : public QStackedWidget
{
    Q_OBJECT
public:
    enum WndType{
        RMWND = 0,
        ADDMWND = 1,
    };
    ChoseManikinWnd(QWidget *parent = 0);
    ~ChoseManikinWnd(){;}

public slots:
    void addManikinEvent();
    void backEvent();
    void ConManikinEvent();
    QStringList GetRemarkList(){return RemarkList;}
Q_SIGNALS:
    void ConManikins();
private:
    RegisterManikinWnd *RMwnd;
    addManikinWnd *addMwnd;

    QStringList RemarkList;
};

#endif // CHOSEMANIKINWND_H
