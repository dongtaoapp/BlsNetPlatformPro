/****************************************************************************
** Meta object code from reading C++ file 'registermanikinwnd.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LoginWnd/registermanikinwnd.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'registermanikinwnd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RegisterManikinWnd_t {
    QByteArrayData data[12];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RegisterManikinWnd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RegisterManikinWnd_t qt_meta_stringdata_RegisterManikinWnd = {
    {
QT_MOC_LITERAL(0, 0, 18), // "RegisterManikinWnd"
QT_MOC_LITERAL(1, 19, 10), // "addManikin"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 10), // "ConManikin"
QT_MOC_LITERAL(4, 42, 25), // "ConManikinBntClickedEvent"
QT_MOC_LITERAL(5, 68, 25), // "AddManikinBtnClickedEvent"
QT_MOC_LITERAL(6, 94, 17), // "CheckGroupClicked"
QT_MOC_LITERAL(7, 112, 2), // "id"
QT_MOC_LITERAL(8, 115, 15), // "BtnGroupClicked"
QT_MOC_LITERAL(9, 131, 14), // "addManikinList"
QT_MOC_LITERAL(10, 146, 6), // "Remark"
QT_MOC_LITERAL(11, 153, 13) // "GetRemarkList"

    },
    "RegisterManikinWnd\0addManikin\0\0"
    "ConManikin\0ConManikinBntClickedEvent\0"
    "AddManikinBtnClickedEvent\0CheckGroupClicked\0"
    "id\0BtnGroupClicked\0addManikinList\0"
    "Remark\0GetRemarkList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RegisterManikinWnd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    1,   58,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      11,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::QStringList,

       0        // eod
};

void RegisterManikinWnd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RegisterManikinWnd *_t = static_cast<RegisterManikinWnd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addManikin(); break;
        case 1: _t->ConManikin(); break;
        case 2: _t->ConManikinBntClickedEvent(); break;
        case 3: _t->AddManikinBtnClickedEvent(); break;
        case 4: _t->CheckGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->BtnGroupClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->addManikinList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: { QStringList _r = _t->GetRemarkList();
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RegisterManikinWnd::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RegisterManikinWnd::addManikin)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RegisterManikinWnd::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RegisterManikinWnd::ConManikin)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject RegisterManikinWnd::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RegisterManikinWnd.data,
      qt_meta_data_RegisterManikinWnd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RegisterManikinWnd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RegisterManikinWnd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RegisterManikinWnd.stringdata0))
        return static_cast<void*>(const_cast< RegisterManikinWnd*>(this));
    return QWidget::qt_metacast(_clname);
}

int RegisterManikinWnd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void RegisterManikinWnd::addManikin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void RegisterManikinWnd::ConManikin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
