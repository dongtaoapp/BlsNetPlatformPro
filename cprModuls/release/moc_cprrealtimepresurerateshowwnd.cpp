/****************************************************************************
** Meta object code from reading C++ file 'cprrealtimepresurerateshowwnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cprrealtimepresurerateshowwnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cprrealtimepresurerateshowwnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CPRRealTimePresureRateShowWnd_t {
    QByteArrayData data[6];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPRRealTimePresureRateShowWnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPRRealTimePresureRateShowWnd_t qt_meta_stringdata_CPRRealTimePresureRateShowWnd = {
    {
QT_MOC_LITERAL(0, 0, 29), // "CPRRealTimePresureRateShowWnd"
QT_MOC_LITERAL(1, 30, 17), // "updatePresureRate"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 12), // "nPresureRate"
QT_MOC_LITERAL(4, 62, 8), // "updateUI"
QT_MOC_LITERAL(5, 71, 21) // "on_pushButton_clicked"

    },
    "CPRRealTimePresureRateShowWnd\0"
    "updatePresureRate\0\0nPresureRate\0"
    "updateUI\0on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPRRealTimePresureRateShowWnd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   32,    2, 0x0a /* Public */,
       5,    0,   33,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CPRRealTimePresureRateShowWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CPRRealTimePresureRateShowWnd *_t = static_cast<CPRRealTimePresureRateShowWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updatePresureRate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateUI(); break;
        case 2: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CPRRealTimePresureRateShowWnd::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPRRealTimePresureRateShowWnd::updatePresureRate)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CPRRealTimePresureRateShowWnd::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CPRRealTimePresureRateShowWnd.data,
      qt_meta_data_CPRRealTimePresureRateShowWnd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CPRRealTimePresureRateShowWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPRRealTimePresureRateShowWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CPRRealTimePresureRateShowWnd.stringdata0))
        return static_cast<void*>(const_cast< CPRRealTimePresureRateShowWnd*>(this));
    return QWidget::qt_metacast(_clname);
}

int CPRRealTimePresureRateShowWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CPRRealTimePresureRateShowWnd::updatePresureRate(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
