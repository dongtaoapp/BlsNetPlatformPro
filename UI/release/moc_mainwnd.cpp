/****************************************************************************
** Meta object code from reading C++ file 'mainwnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWnd_t {
    QByteArrayData data[9];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWnd_t qt_meta_stringdata_MainWnd = {
    {
QT_MOC_LITERAL(0, 0, 7), // "MainWnd"
QT_MOC_LITERAL(1, 8, 22), // "CPRWorkBtnClickedEvent"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 17), // "SCBtnClickedEvent"
QT_MOC_LITERAL(4, 50, 16), // "SBtnClickedEvent"
QT_MOC_LITERAL(5, 67, 21), // "MinWndBtnClickedEvent"
QT_MOC_LITERAL(6, 89, 21), // "MaxWndBtnClicledEvent"
QT_MOC_LITERAL(7, 111, 23), // "CloseWndBtnClickedEvent"
QT_MOC_LITERAL(8, 135, 16) // "ConManikiSuccess"

    },
    "MainWnd\0CPRWorkBtnClickedEvent\0\0"
    "SCBtnClickedEvent\0SBtnClickedEvent\0"
    "MinWndBtnClickedEvent\0MaxWndBtnClicledEvent\0"
    "CloseWndBtnClickedEvent\0ConManikiSuccess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWnd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWnd *_t = static_cast<MainWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CPRWorkBtnClickedEvent(); break;
        case 1: _t->SCBtnClickedEvent(); break;
        case 2: _t->SBtnClickedEvent(); break;
        case 3: _t->MinWndBtnClickedEvent(); break;
        case 4: _t->MaxWndBtnClicledEvent(); break;
        case 5: _t->CloseWndBtnClickedEvent(); break;
        case 6: _t->ConManikiSuccess(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWnd::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainWnd.data,
      qt_meta_data_MainWnd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWnd.stringdata0))
        return static_cast<void*>(const_cast< MainWnd*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
