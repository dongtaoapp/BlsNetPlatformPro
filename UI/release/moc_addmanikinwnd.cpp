/****************************************************************************
** Meta object code from reading C++ file 'addmanikinwnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LoginWnd/addmanikinwnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addmanikinwnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_addManikinWnd_t {
    QByteArrayData data[7];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_addManikinWnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_addManikinWnd_t qt_meta_stringdata_addManikinWnd = {
    {
QT_MOC_LITERAL(0, 0, 13), // "addManikinWnd"
QT_MOC_LITERAL(1, 14, 10), // "backSignal"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 10), // "addManikin"
QT_MOC_LITERAL(4, 37, 6), // "Remark"
QT_MOC_LITERAL(5, 44, 17), // "okBtnClickedEvent"
QT_MOC_LITERAL(6, 62, 19) // "backBtnClickedEvent"

    },
    "addManikinWnd\0backSignal\0\0addManikin\0"
    "Remark\0okBtnClickedEvent\0backBtnClickedEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_addManikinWnd[] = {

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
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void addManikinWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        addManikinWnd *_t = static_cast<addManikinWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backSignal(); break;
        case 1: _t->addManikin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->okBtnClickedEvent(); break;
        case 3: _t->backBtnClickedEvent(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (addManikinWnd::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&addManikinWnd::backSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (addManikinWnd::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&addManikinWnd::addManikin)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject addManikinWnd::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_addManikinWnd.data,
      qt_meta_data_addManikinWnd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *addManikinWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *addManikinWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_addManikinWnd.stringdata0))
        return static_cast<void*>(const_cast< addManikinWnd*>(this));
    return QWidget::qt_metacast(_clname);
}

int addManikinWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void addManikinWnd::backSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void addManikinWnd::addManikin(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
