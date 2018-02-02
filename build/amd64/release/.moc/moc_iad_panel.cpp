/****************************************************************************
** Meta object code from reading C++ file 'iad_panel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../iad_panel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'iad_panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PanelIAD_t {
    QByteArrayData data[9];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PanelIAD_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PanelIAD_t qt_meta_stringdata_PanelIAD = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PanelIAD"
QT_MOC_LITERAL(1, 9, 12), // "updateGraphs"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 19), // "newConfigurationIAD"
QT_MOC_LITERAL(4, 43, 20), // "openConfigurationIAD"
QT_MOC_LITERAL(5, 64, 20), // "showConfigurationIAD"
QT_MOC_LITERAL(6, 85, 12), // "calibrateIAD"
QT_MOC_LITERAL(7, 98, 10), // "measureIAD"
QT_MOC_LITERAL(8, 109, 11) // "liveViewIAD"

    },
    "PanelIAD\0updateGraphs\0\0newConfigurationIAD\0"
    "openConfigurationIAD\0showConfigurationIAD\0"
    "calibrateIAD\0measureIAD\0liveViewIAD"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PanelIAD[] = {

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
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

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

void PanelIAD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PanelIAD *_t = static_cast<PanelIAD *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateGraphs(); break;
        case 1: _t->newConfigurationIAD(); break;
        case 2: _t->openConfigurationIAD(); break;
        case 3: _t->showConfigurationIAD(); break;
        case 4: _t->calibrateIAD(); break;
        case 5: _t->measureIAD(); break;
        case 6: _t->liveViewIAD(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PanelIAD::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PanelIAD.data,
      qt_meta_data_PanelIAD,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PanelIAD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelIAD::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PanelIAD.stringdata0))
        return static_cast<void*>(const_cast< PanelIAD*>(this));
    return QDialog::qt_metacast(_clname);
}

int PanelIAD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
