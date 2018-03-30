#ifndef CPRWORKWND_H
#define CPRWORKWND_H

#include <QWidget>
#include <QButtonGroup>
#include <QListWidgetItem>
#include <QList>
#include <QMouseEvent>
#include <QLineEdit>
#include "qmlistwnd.h"
#include "setsyswnd.h"
#include "setmanikinwnd.h"
#include "setsuccesswnd.h"
#include "showlistwnd.h"
#include "cpraddmanikinwnd.h"
#include "cprchangewnd.h"
#include "cprremanikinwnd.h"
namespace Ui {
    class CPRWorkWnd;
}

class CPRWorkWnd : public QWidget
{
    Q_OBJECT

public:
    enum BntIndex{
        StartBtn = 0,
        RetBtn = 1,
        OneLineBtn = 2,
        DoubleLineBtn = 3,
        MoreLineBtn = 4,
        UpPageBtn = 5,
        DownPageBtn = 6,
        HideListBtn = 7,
        showListBtn = 8,
        setBtn = 9,
        SuccessSetBtn = 10,
        ManikinSetBtn = 11,

    };
    enum LineType{
        OneLine = 1,
        DoubleLine = 2,
        MoreLine = 3,
    };
    explicit CPRWorkWnd(QWidget *parent = 0);
    ~CPRWorkWnd();
    void btngroupInit();
    void GetManikinList(QStringList list);
    void InitList2Wnd();
    void InitListWnd();
    void InitHiRightWnd();
    void InitStackWidget();
    QList<QMlistWnd *> GetmListWnd_List(){return mlistWnd_list;}
Q_SIGNALS:
    void maxsignal();
    void listWndState(bool show);
public slots:
    void ListWndItemClicked();
    void ListWndItemDoubleClicked(QString ManikinRemark);
    void ManikinDouleClickedEvent(QString ManikinRemark);
    void List2WndItemClicked();
    void BtnClickedEvent(int index);
    void downPageEvent();
    void upPageEvent();
private:
    Ui::CPRWorkWnd *ui;
    QButtonGroup btnGroup;
    SetManikinWnd *SMWnd;
    SetSysWnd *SSysWnd;
    SetSuccessWnd *SSWnd;
    showListWnd *listWnd;
    CPRAddManikinWnd *addManWnd;
    CPRChangeWnd *changeManWnd;
    CPRReManikinWnd *ReManWnd;
    QList<QMlistWnd *> mlistWnd_list;
    QMlistWnd *CurrentManikin;
    QStringList ManikinList;
    int CurrentBtnID; bool fullscreenlist;

};

#endif // CPRWORKWND_H
