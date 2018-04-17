/****************************************************************************
** Meta object code from reading C++ file 'statisticswnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ChartWnd/statisticswnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'statisticswnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_StatisticsWnd_t {
    QByteArrayData data[8];
    char stringdata0[84];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StatisticsWnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StatisticsWnd_t qt_meta_stringdata_StatisticsWnd = {
    {
QT_MOC_LITERAL(0, 0, 13), // "StatisticsWnd"
QT_MOC_LITERAL(1, 14, 15), // "BtnClickedEvent"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "index"
QT_MOC_LITERAL(4, 37, 14), // "CBClickedEvent"
QT_MOC_LITERAL(5, 52, 16), // "QAbstractButton*"
QT_MOC_LITERAL(6, 69, 2), // "cb"
QT_MOC_LITERAL(7, 72, 11) // "SearchEvent"

    },
    "StatisticsWnd\0BtnClickedEvent\0\0index\0"
    "CBClickedEvent\0QAbstractButton*\0cb\0"
    "SearchEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StatisticsWnd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       7,    0,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void StatisticsWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StatisticsWnd *_t = static_cast<StatisticsWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->BtnClickedEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->CBClickedEvent((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 2: _t->SearchEvent(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractButton* >(); break;
            }
            break;
        }
    }
}

const QMetaObject StatisticsWnd::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StatisticsWnd.data,
      qt_meta_data_StatisticsWnd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *StatisticsWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StatisticsWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_StatisticsWnd.stringdata0))
        return static_cast<void*>(const_cast< StatisticsWnd*>(this));
    return QWidget::qt_metacast(_clname);
}

int StatisticsWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
