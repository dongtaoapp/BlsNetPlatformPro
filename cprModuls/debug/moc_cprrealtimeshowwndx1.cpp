/****************************************************************************
** Meta object code from reading C++ file 'cprrealtimeshowwndx1.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cprrealtimeshowwndx1.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cprrealtimeshowwndx1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CprRealTimeShowWndx1_t {
    QByteArrayData data[6];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CprRealTimeShowWndx1_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CprRealTimeShowWndx1_t qt_meta_stringdata_CprRealTimeShowWndx1 = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CprRealTimeShowWndx1"
QT_MOC_LITERAL(1, 21, 23), // "DoUpdatePresureDepthVal"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 4), // "nVal"
QT_MOC_LITERAL(4, 51, 19), // "DoUpdatePresureRate"
QT_MOC_LITERAL(5, 71, 12) // "nPresureRate"

    },
    "CprRealTimeShowWndx1\0DoUpdatePresureDepthVal\0"
    "\0nVal\0DoUpdatePresureRate\0nPresureRate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CprRealTimeShowWndx1[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       4,    1,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void CprRealTimeShowWndx1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CprRealTimeShowWndx1 *_t = static_cast<CprRealTimeShowWndx1 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DoUpdatePresureDepthVal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->DoUpdatePresureRate((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject CprRealTimeShowWndx1::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CprRealTimeShowWndx1.data,
      qt_meta_data_CprRealTimeShowWndx1,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CprRealTimeShowWndx1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CprRealTimeShowWndx1::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CprRealTimeShowWndx1.stringdata0))
        return static_cast<void*>(const_cast< CprRealTimeShowWndx1*>(this));
    if (!strcmp(_clname, "IDistributeCPRRealTimeData"))
        return static_cast< IDistributeCPRRealTimeData*>(const_cast< CprRealTimeShowWndx1*>(this));
    if (!strcmp(_clname, "CShowCPRStatisticUpdateInterface"))
        return static_cast< CShowCPRStatisticUpdateInterface*>(const_cast< CprRealTimeShowWndx1*>(this));
    return QWidget::qt_metacast(_clname);
}

int CprRealTimeShowWndx1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
