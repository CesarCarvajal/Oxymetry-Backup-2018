/****************************************************************************
** Meta object code from reading C++ file 'pol_analizeData.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../pol_analizeData.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pol_analizeData.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_selectAnalizeData_t {
    QByteArrayData data[24];
    char stringdata0[282];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_selectAnalizeData_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_selectAnalizeData_t qt_meta_stringdata_selectAnalizeData = {
    {
QT_MOC_LITERAL(0, 0, 17), // "selectAnalizeData"
QT_MOC_LITERAL(1, 18, 6), // "cancel"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "handleClickEvent"
QT_MOC_LITERAL(4, 43, 8), // "QWidget*"
QT_MOC_LITERAL(5, 52, 6), // "widget"
QT_MOC_LITERAL(6, 59, 9), // "sortFiles"
QT_MOC_LITERAL(7, 69, 4), // "List"
QT_MOC_LITERAL(8, 74, 14), // "addFilesToList"
QT_MOC_LITERAL(9, 89, 15), // "allowSelectPath"
QT_MOC_LITERAL(10, 105, 15), // "selectFileSteps"
QT_MOC_LITERAL(11, 121, 19), // "updateSelectionList"
QT_MOC_LITERAL(12, 141, 15), // "findRepetitions"
QT_MOC_LITERAL(13, 157, 9), // "cleanList"
QT_MOC_LITERAL(14, 167, 11), // "setDataSets"
QT_MOC_LITERAL(15, 179, 10), // "removeItem"
QT_MOC_LITERAL(16, 190, 15), // "showContextMenu"
QT_MOC_LITERAL(17, 206, 3), // "pos"
QT_MOC_LITERAL(18, 210, 10), // "selectPath"
QT_MOC_LITERAL(19, 221, 9), // "readFiles"
QT_MOC_LITERAL(20, 231, 12), // "readLongData"
QT_MOC_LITERAL(21, 244, 11), // "analizeData"
QT_MOC_LITERAL(22, 256, 16), // "automaticAnalize"
QT_MOC_LITERAL(23, 273, 8) // "PathAuto"

    },
    "selectAnalizeData\0cancel\0\0handleClickEvent\0"
    "QWidget*\0widget\0sortFiles\0List\0"
    "addFilesToList\0allowSelectPath\0"
    "selectFileSteps\0updateSelectionList\0"
    "findRepetitions\0cleanList\0setDataSets\0"
    "removeItem\0showContextMenu\0pos\0"
    "selectPath\0readFiles\0readLongData\0"
    "analizeData\0automaticAnalize\0PathAuto"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_selectAnalizeData[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    1,   95,    2, 0x08 /* Private */,
       6,    1,   98,    2, 0x08 /* Private */,
       8,    0,  101,    2, 0x08 /* Private */,
       9,    0,  102,    2, 0x08 /* Private */,
      10,    0,  103,    2, 0x08 /* Private */,
      11,    0,  104,    2, 0x08 /* Private */,
      12,    0,  105,    2, 0x08 /* Private */,
      13,    0,  106,    2, 0x08 /* Private */,
      14,    0,  107,    2, 0x08 /* Private */,
      15,    0,  108,    2, 0x08 /* Private */,
      16,    1,  109,    2, 0x08 /* Private */,
      18,    0,  112,    2, 0x08 /* Private */,
      19,    1,  113,    2, 0x08 /* Private */,
      21,    0,  116,    2, 0x08 /* Private */,
      22,    1,  117,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::QStringList, QMetaType::QStringList,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   17,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,

       0        // eod
};

void selectAnalizeData::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        selectAnalizeData *_t = static_cast<selectAnalizeData *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cancel(); break;
        case 1: _t->handleClickEvent((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: { QStringList _r = _t->sortFiles((*reinterpret_cast< QStringList(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->addFilesToList(); break;
        case 4: _t->allowSelectPath(); break;
        case 5: _t->selectFileSteps(); break;
        case 6: _t->updateSelectionList(); break;
        case 7: _t->findRepetitions(); break;
        case 8: _t->cleanList(); break;
        case 9: _t->setDataSets(); break;
        case 10: _t->removeItem(); break;
        case 11: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 12: _t->selectPath(); break;
        case 13: _t->readFiles((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->analizeData(); break;
        case 15: _t->automaticAnalize((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject selectAnalizeData::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_selectAnalizeData.data,
      qt_meta_data_selectAnalizeData,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *selectAnalizeData::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *selectAnalizeData::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_selectAnalizeData.stringdata0))
        return static_cast<void*>(const_cast< selectAnalizeData*>(this));
    return QDialog::qt_metacast(_clname);
}

int selectAnalizeData::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
