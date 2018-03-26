/****************************************************************************
** Meta object code from reading C++ file 'pol_configureMeasurement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../pol_configureMeasurement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pol_configureMeasurement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_configurePolMeasure_t {
    QByteArrayData data[11];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_configurePolMeasure_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_configurePolMeasure_t qt_meta_stringdata_configurePolMeasure = {
    {
QT_MOC_LITERAL(0, 0, 19), // "configurePolMeasure"
QT_MOC_LITERAL(1, 20, 20), // "GetConfigurationData"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 17), // "loadConfiguration"
QT_MOC_LITERAL(4, 60, 10), // "selectPath"
QT_MOC_LITERAL(5, 71, 20), // "configurePolarimeter"
QT_MOC_LITERAL(6, 92, 6), // "cancel"
QT_MOC_LITERAL(7, 99, 16), // "handleClickEvent"
QT_MOC_LITERAL(8, 116, 8), // "QWidget*"
QT_MOC_LITERAL(9, 125, 6), // "widget"
QT_MOC_LITERAL(10, 132, 25) // "updateConfigurationValues"

    },
    "configurePolMeasure\0GetConfigurationData\0"
    "\0loadConfiguration\0selectPath\0"
    "configurePolarimeter\0cancel\0"
    "handleClickEvent\0QWidget*\0widget\0"
    "updateConfigurationValues"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_configurePolMeasure[] = {

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
       7,    1,   54,    2, 0x08 /* Private */,
      10,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,

       0        // eod
};

void configurePolMeasure::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        configurePolMeasure *_t = static_cast<configurePolMeasure *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GetConfigurationData(); break;
        case 1: _t->loadConfiguration(); break;
        case 2: _t->selectPath(); break;
        case 3: _t->configurePolarimeter(); break;
        case 4: _t->cancel(); break;
        case 5: _t->handleClickEvent((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 6: _t->updateConfigurationValues(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject configurePolMeasure::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_configurePolMeasure.data,
      qt_meta_data_configurePolMeasure,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *configurePolMeasure::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *configurePolMeasure::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_configurePolMeasure.stringdata0))
        return static_cast<void*>(const_cast< configurePolMeasure*>(this));
    return QDialog::qt_metacast(_clname);
}

int configurePolMeasure::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
