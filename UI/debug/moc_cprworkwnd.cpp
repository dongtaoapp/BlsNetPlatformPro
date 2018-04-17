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
    QByteArrayData data[18];
    char stringdata0[242];
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
QT_MOC_LITERAL(3, 22, 10), // "addManikin"
QT_MOC_LITERAL(4, 33, 6), // "remark"
QT_MOC_LITERAL(5, 40, 13), // "deleteManikin"
QT_MOC_LITERAL(6, 54, 13), // "changeManikin"
QT_MOC_LITERAL(7, 68, 18), // "ListWndItemClicked"
QT_MOC_LITERAL(8, 87, 24), // "ManikinDouleClickedEvent"
QT_MOC_LITERAL(9, 112, 13), // "ManikinRemark"
QT_MOC_LITERAL(10, 126, 19), // "ManikinClickedEvent"
QT_MOC_LITERAL(11, 146, 19), // "List2WndItemClicked"
QT_MOC_LITERAL(12, 166, 15), // "BtnClickedEvent"
QT_MOC_LITERAL(13, 182, 5), // "index"
QT_MOC_LITERAL(14, 188, 13), // "downPageEvent"
QT_MOC_LITERAL(15, 202, 11), // "upPageEvent"
QT_MOC_LITERAL(16, 214, 20), // "DoubleWndItemClicked"
QT_MOC_LITERAL(17, 235, 6) // "Remark"

    },
    "CPRWorkWnd\0maxsignal\0\0addManikin\0"
    "remark\0deleteManikin\0changeManikin\0"
    "ListWndItemClicked\0ManikinDouleClickedEvent\0"
    "ManikinRemark\0ManikinClickedEvent\0"
    "List2WndItemClicked\0BtnClickedEvent\0"
    "index\0downPageEvent\0upPageEvent\0"
    "DoubleWndItemClicked\0Remark"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPRWorkWnd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   75,    2, 0x0a /* Public */,
       5,    0,   78,    2, 0x0a /* Public */,
       6,    0,   79,    2, 0x0a /* Public */,
       7,    0,   80,    2, 0x0a /* Public */,
       8,    1,   81,    2, 0x0a /* Public */,
      10,    1,   84,    2, 0x0a /* Public */,
      11,    0,   87,    2, 0x0a /* Public */,
      12,    1,   88,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,
      15,    0,   92,    2, 0x0a /* Public */,
      16,    1,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString,    4,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,

       0        // eod
};

void CPRWorkWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CPRWorkWnd *_t = static_cast<CPRWorkWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->maxsignal(); break;
        case 1: { bool _r = _t->addManikin((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->deleteManikin();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->changeManikin();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: _t->ListWndItemClicked(); break;
        case 5: _t->ManikinDouleClickedEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->ManikinClickedEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->List2WndItemClicked(); break;
        case 8: _t->BtnClickedEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->downPageEvent(); break;
        case 10: _t->upPageEvent(); break;
        case 11: _t->DoubleWndItemClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CPRWorkWnd::maxsignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
