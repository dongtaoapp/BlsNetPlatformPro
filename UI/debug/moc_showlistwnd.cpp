/****************************************************************************
** Meta object code from reading C++ file 'showlistwnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CPRWorkWnd/StackWidget/showlistwnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'showlistwnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_showListWnd_t {
    QByteArrayData data[8];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_showListWnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_showListWnd_t qt_meta_stringdata_showListWnd = {
    {
QT_MOC_LITERAL(0, 0, 11), // "showListWnd"
QT_MOC_LITERAL(1, 12, 20), // "ManikinDoubleClicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 6), // "Remark"
QT_MOC_LITERAL(4, 41, 16), // "ManikinClickedx9"
QT_MOC_LITERAL(5, 58, 11), // "ItemClicked"
QT_MOC_LITERAL(6, 70, 17), // "ItemDoubleClicked"
QT_MOC_LITERAL(7, 88, 6) // "remark"

    },
    "showListWnd\0ManikinDoubleClicked\0\0"
    "Remark\0ManikinClickedx9\0ItemClicked\0"
    "ItemDoubleClicked\0remark"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_showListWnd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   40,    2, 0x0a /* Public */,
       6,    1,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void showListWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        showListWnd *_t = static_cast<showListWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ManikinDoubleClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->ManikinClickedx9((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ItemClicked(); break;
        case 3: _t->ItemDoubleClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (showListWnd::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&showListWnd::ManikinDoubleClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (showListWnd::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&showListWnd::ManikinClickedx9)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject showListWnd::staticMetaObject = {
    { &ShowLineBaseWnd::staticMetaObject, qt_meta_stringdata_showListWnd.data,
      qt_meta_data_showListWnd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *showListWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *showListWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_showListWnd.stringdata0))
        return static_cast<void*>(const_cast< showListWnd*>(this));
    return ShowLineBaseWnd::qt_metacast(_clname);
}

int showListWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ShowLineBaseWnd::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void showListWnd::ManikinDoubleClicked(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void showListWnd::ManikinClickedx9(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
