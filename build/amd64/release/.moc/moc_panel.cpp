/****************************************************************************
** Meta object code from reading C++ file 'panel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../panel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Panel_t {
    QByteArrayData data[21];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Panel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Panel_t qt_meta_stringdata_Panel = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Panel"
QT_MOC_LITERAL(1, 6, 13), // "updateModules"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "PreviewButtons"
QT_MOC_LITERAL(4, 36, 5), // "state"
QT_MOC_LITERAL(5, 42, 17), // "ReceiveDataIsHere"
QT_MOC_LITERAL(6, 60, 6), // "WParam"
QT_MOC_LITERAL(7, 67, 6), // "LParam"
QT_MOC_LITERAL(8, 74, 13), // "togglePreview"
QT_MOC_LITERAL(9, 88, 12), // "startPreview"
QT_MOC_LITERAL(10, 101, 11), // "stopPreview"
QT_MOC_LITERAL(11, 113, 10), // "storeToRam"
QT_MOC_LITERAL(12, 124, 11), // "timePattern"
QT_MOC_LITERAL(13, 136, 10), // "showLegend"
QT_MOC_LITERAL(14, 147, 9), // "saveGraph"
QT_MOC_LITERAL(15, 157, 10), // "exportData"
QT_MOC_LITERAL(16, 168, 9), // "showAbout"
QT_MOC_LITERAL(17, 178, 14), // "updateProgress"
QT_MOC_LITERAL(18, 193, 16), // "handleClickEvent"
QT_MOC_LITERAL(19, 210, 8), // "QWidget*"
QT_MOC_LITERAL(20, 219, 6) // "widget"

    },
    "Panel\0updateModules\0\0PreviewButtons\0"
    "state\0ReceiveDataIsHere\0WParam\0LParam\0"
    "togglePreview\0startPreview\0stopPreview\0"
    "storeToRam\0timePattern\0showLegend\0"
    "saveGraph\0exportData\0showAbout\0"
    "updateProgress\0handleClickEvent\0"
    "QWidget*\0widget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Panel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a /* Public */,
       3,    1,   85,    2, 0x0a /* Public */,
       5,    2,   88,    2, 0x08 /* Private */,
       8,    0,   93,    2, 0x08 /* Private */,
       9,    0,   94,    2, 0x08 /* Private */,
      10,    0,   95,    2, 0x08 /* Private */,
      11,    0,   96,    2, 0x08 /* Private */,
      12,    0,   97,    2, 0x08 /* Private */,
      13,    0,   98,    2, 0x08 /* Private */,
      14,    0,   99,    2, 0x08 /* Private */,
      15,    0,  100,    2, 0x08 /* Private */,
      16,    0,  101,    2, 0x08 /* Private */,
      17,    0,  102,    2, 0x08 /* Private */,
      18,    1,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,

       0        // eod
};

void Panel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Panel *_t = static_cast<Panel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateModules(); break;
        case 1: _t->PreviewButtons((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->ReceiveDataIsHere((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->togglePreview(); break;
        case 4: _t->startPreview(); break;
        case 5: _t->stopPreview(); break;
        case 6: _t->storeToRam(); break;
        case 7: _t->timePattern(); break;
        case 8: _t->showLegend(); break;
        case 9: _t->saveGraph(); break;
        case 10: _t->exportData(); break;
        case 11: _t->showAbout(); break;
        case 12: _t->updateProgress(); break;
        case 13: _t->handleClickEvent((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Panel::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Panel.data,
      qt_meta_data_Panel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Panel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Panel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Panel.stringdata0))
        return static_cast<void*>(const_cast< Panel*>(this));
    return QDialog::qt_metacast(_clname);
}

int Panel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
