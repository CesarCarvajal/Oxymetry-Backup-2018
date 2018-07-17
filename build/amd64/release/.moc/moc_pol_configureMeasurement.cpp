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
    QByteArrayData data[13];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_configurePolMeasure_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_configurePolMeasure_t qt_meta_stringdata_configurePolMeasure = {
    {
QT_MOC_LITERAL(0, 0, 19), // "configurePolMeasure"
QT_MOC_LITERAL(1, 20, 10), // "selectPath"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 13), // "addImpurities"
QT_MOC_LITERAL(4, 46, 20), // "configurePolarimeter"
QT_MOC_LITERAL(5, 67, 6), // "cancel"
QT_MOC_LITERAL(6, 74, 16), // "handleClickEvent"
QT_MOC_LITERAL(7, 91, 8), // "QWidget*"
QT_MOC_LITERAL(8, 100, 6), // "widget"
QT_MOC_LITERAL(9, 107, 24), // "getConfigurationFromFile"
QT_MOC_LITERAL(10, 132, 4), // "data"
QT_MOC_LITERAL(11, 137, 25), // "updateConfigurationValues"
QT_MOC_LITERAL(12, 163, 17) // "updateStockValues"

    },
    "configurePolMeasure\0selectPath\0\0"
    "addImpurities\0configurePolarimeter\0"
    "cancel\0handleClickEvent\0QWidget*\0"
    "widget\0getConfigurationFromFile\0data\0"
    "updateConfigurationValues\0updateStockValues"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_configurePolMeasure[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    1,   58,    2, 0x08 /* Private */,
       9,    1,   61,    2, 0x08 /* Private */,
      11,    0,   64,    2, 0x0a /* Public */,
      12,    0,   65,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void configurePolMeasure::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        configurePolMeasure *_t = static_cast<configurePolMeasure *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectPath(); break;
        case 1: _t->addImpurities(); break;
        case 2: _t->configurePolarimeter(); break;
        case 3: _t->cancel(); break;
        case 4: _t->handleClickEvent((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 5: _t->getConfigurationFromFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->updateConfigurationValues(); break;
        case 7: _t->updateStockValues(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
