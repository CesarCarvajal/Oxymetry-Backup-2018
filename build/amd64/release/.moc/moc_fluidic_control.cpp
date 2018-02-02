/****************************************************************************
** Meta object code from reading C++ file 'fluidic_control.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../fluidic_control.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fluidic_control.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControlFluidic_t {
    QByteArrayData data[7];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlFluidic_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlFluidic_t qt_meta_stringdata_ControlFluidic = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ControlFluidic"
QT_MOC_LITERAL(1, 15, 10), // "connectCOM"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "apply"
QT_MOC_LITERAL(4, 33, 5), // "flush"
QT_MOC_LITERAL(5, 39, 6), // "sample"
QT_MOC_LITERAL(6, 46, 8) // "readData"

    },
    "ControlFluidic\0connectCOM\0\0apply\0flush\0"
    "sample\0readData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlFluidic[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ControlFluidic::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ControlFluidic *_t = static_cast<ControlFluidic *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectCOM(); break;
        case 1: _t->apply(); break;
        case 2: _t->flush(); break;
        case 3: _t->sample(); break;
        case 4: _t->readData(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ControlFluidic::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ControlFluidic.data,
      qt_meta_data_ControlFluidic,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ControlFluidic::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlFluidic::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControlFluidic.stringdata0))
        return static_cast<void*>(const_cast< ControlFluidic*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ControlFluidic::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
