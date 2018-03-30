#ifndef REGISTERMANIKINWND_H
#define REGISTERMANIKINWND_H

#include <QWidget>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QStringList>
#include <QMap>
#include <QList>
#include <QCheckBox>
#include <QPushButton>
#include <QButtonGroup>
typedef struct ManikinData{
    QString Remark;
    QString IP;
}M_Data;

Q_DECLARE_METATYPE(M_Data);

typedef QMap<QString,QString> ManikinInfo_Map;
namespace Ui {
class RegisterManikinWnd;
}

class RegisterManikinWnd : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterManikinWnd(QWidget *parent = 0);
    ~RegisterManikinWnd();
public:
    void GetManikinRemarkByIniFile();
    void GetManikinIP(ManikinInfo_Map map){info_map = map;}
    QStringList ManikinRemark(){return RemarkList;}
    void InitTableView();
public slots:
    void ConManikinBntClickedEvent();
    void AddManikinBtnClickedEvent();

    void CheckGroupClicked(int id);
    void BtnGroupClicked(int id);

    void addManikinList(QString Remark);


    QStringList GetRemarkList(){return RemarkList;}
Q_SIGNALS:
    void addManikin();
    void ConManikin();
private:
    Ui::RegisterManikinWnd *ui;
    QTableView *m_view;
    QStandardItemModel *m_model;
    QStringList RemarkList;//模拟人标识码

    ManikinInfo_Map info_map;//Remark IP

    QMap<int,M_Data> Num_info;//num ManikinInfo

    QButtonGroup CheckGroup,BtnGroup;

};

#endif // REGISTERMANIKINWND_H
