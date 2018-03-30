/****************************************************************************
** Meta object code from reading C++ file 'cprworkwnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../CPRWorkWnd/cprworkwnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cprworkwnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CPRWorkWnd_t {
    QByteArrayData data[14];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPRWorkWnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPRWorkWnd_t qt_meta_stringdata_CPRWorkWnd = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CPRWorkWnd"
QT_MOC_LITERAL(1, 11, 9), // "maxsignal"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "listWndState"
QT_MOC_LITERAL(4, 35, 4), // "show"
QT_MOC_LITERAL(5, 40, 18), // "ListWndItemClicked"
QT_MOC_LITERAL(6, 59, 24), // "ListWndItemDoubleClicked"
QT_MOC_LITERAL(7, 84, 13), // "ManikinRemark"
QT_MOC_LITERAL(8, 98, 24), // "ManikinDouleClickedEvent"
QT_MOC_LITERAL(9, 123, 19), // "List2WndItemClicked"
QT_MOC_LITERAL(10, 143, 15), // "BtnClickedEvent"
QT_MOC_LITERAL(11, 159, 5), // "index"
QT_MOC_LITERAL(12, 165, 13), // "downPageEvent"
QT_MOC_LITERAL(13, 179, 11) // "upPageEvent"

    },
    "CPRWorkWnd\0maxsignal\0\0listWndState\0"
    "show\0ListWndItemClicked\0"
    "ListWndItemDoubleClicked\0ManikinRemark\0"
    "ManikinDouleClickedEvent\0List2WndItemClicked\0"
    "BtnClickedEvent\0index\0downPageEvent\0"
    "upPageEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPRWorkWnd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   63,    2, 0x0a /* Public */,
       6,    1,   64,    2, 0x0a /* Public */,
       8,    1,   67,    2, 0x0a /* Public */,
       9,    0,   70,    2, 0x0a /* Public */,
      10,    1,   71,    2, 0x0a /* Public */,
      12,    0,   74,    2, 0x0a /* Public */,
      13,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CPRWorkWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CPRWorkWnd *_t = static_cast<CPRWorkWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->maxsignal(); break;
        case 1: _t->listWndState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->ListWndItemClicked(); break;
        case 3: _t->ListWndItemDoubleClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->ManikinDouleClickedEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->List2WndItemClicked(); break;
        case 6: _t->BtnClickedEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->downPageEvent(); break;
        case 8: _t->upPageEvent(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CPRWorkWnd::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPRWorkWnd::maxsignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CPRWorkWnd::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPRWorkWnd::listWndState)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CPRWorkWnd::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CPRWorkWnd.data,
      qt_meta_data_CPRWorkWnd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CPRWorkWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPRWorkWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CPRWorkWnd.stringdata0))
        return static_cast<void*>(const_cast< CPRWorkWnd*>(this));
    return QWidget::qt_metacast(_clname);
}

int CPRWorkWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CPRWorkWnd::maxsignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void CPRWorkWnd::listWndState(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
