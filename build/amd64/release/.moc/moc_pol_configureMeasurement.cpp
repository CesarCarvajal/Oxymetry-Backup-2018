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
    QByteArrayData data[9];
    char stringdata0[119];
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
QT_MOC_LITERAL(3, 32, 20), // "configurePolarimeter"
QT_MOC_LITERAL(4, 53, 6), // "cancel"
QT_MOC_LITERAL(5, 60, 16), // "handleClickEvent"
QT_MOC_LITERAL(6, 77, 8), // "QWidget*"
QT_MOC_LITERAL(7, 86, 6), // "widget"
QT_MOC_LITERAL(8, 93, 25) // "updateConfigurationValues"

    },
    "configurePolMeasure\0selectPath\0\0"
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
       5,    1,   42,    2, 0x08 /* Private */,
       8,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
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
        case 1: _t->configurePolarimeter(); break;
        case 2: _t->cancel(); break;
        case 3: _t->handleClickEvent((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 4: _t->updateConfigurationValues(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
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
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
