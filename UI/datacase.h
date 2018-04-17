#ifndef DATACASE_H
#define DATACASE_H

#include <QObject>
/*******************************************************
 *
 * CPR case
 *
 *******************************************************/
class DataCase : public QObject
{
    Q_OBJECT
public:
    DataCase(QObject *parent = 0);
    ~DataCase(){}
};

#endif // DATACASE_H
