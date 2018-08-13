/****************************************************************************
** Meta object code from reading C++ file 'pol_panel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../pol_panel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pol_panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PanelPolarimeter_t {
    QByteArrayData data[67];
    char stringdata0[1120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PanelPolarimeter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PanelPolarimeter_t qt_meta_stringdata_PanelPolarimeter = {
    {
QT_MOC_LITERAL(0, 0, 16), // "PanelPolarimeter"
QT_MOC_LITERAL(1, 17, 10), // "updateTabs"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 16), // "DisEnablePreview"
QT_MOC_LITERAL(4, 46, 11), // "showUI_Item"
QT_MOC_LITERAL(5, 58, 8), // "UIstatus"
QT_MOC_LITERAL(6, 67, 25), // "selected_Spectrometer_Pol"
QT_MOC_LITERAL(7, 93, 8), // "help_Pol"
QT_MOC_LITERAL(8, 102, 26), // "change_Number_Averages_Pol"
QT_MOC_LITERAL(9, 129, 20), // "change_Frequency_Pol"
QT_MOC_LITERAL(10, 150, 25), // "change_Number_Spectra_Pol"
QT_MOC_LITERAL(11, 176, 25), // "change_Wavelength_FFT_Pol"
QT_MOC_LITERAL(12, 202, 32), // "change_Auto_Integration_Time_Pol"
QT_MOC_LITERAL(13, 235, 12), // "Load_Summary"
QT_MOC_LITERAL(14, 248, 13), // "write_Summary"
QT_MOC_LITERAL(15, 262, 27), // "change_Integration_Time_Pol"
QT_MOC_LITERAL(16, 290, 12), // "showAllPlots"
QT_MOC_LITERAL(17, 303, 13), // "clean_All_Pol"
QT_MOC_LITERAL(18, 317, 22), // "initialize_Calibration"
QT_MOC_LITERAL(19, 340, 24), // "pol_Measurement_Progress"
QT_MOC_LITERAL(20, 365, 1), // "i"
QT_MOC_LITERAL(21, 367, 13), // "pol_Calibrate"
QT_MOC_LITERAL(22, 381, 11), // "pol_Measure"
QT_MOC_LITERAL(23, 393, 30), // "initialize_Default_Calibration"
QT_MOC_LITERAL(24, 424, 24), // "adjust_Average_Plot_Time"
QT_MOC_LITERAL(25, 449, 27), // "adjust_Integration_Time_Pol"
QT_MOC_LITERAL(26, 477, 18), // "handle_Click_Event"
QT_MOC_LITERAL(27, 496, 8), // "QWidget*"
QT_MOC_LITERAL(28, 505, 6), // "widget"
QT_MOC_LITERAL(29, 512, 16), // "receive_Data_Pol"
QT_MOC_LITERAL(30, 529, 6), // "WParam"
QT_MOC_LITERAL(31, 536, 6), // "LParam"
QT_MOC_LITERAL(32, 543, 22), // "toggle_Pol_Measurement"
QT_MOC_LITERAL(33, 566, 16), // "change_File_Name"
QT_MOC_LITERAL(34, 583, 13), // "write_To_File"
QT_MOC_LITERAL(35, 597, 5), // "FILE*"
QT_MOC_LITERAL(36, 603, 4), // "file"
QT_MOC_LITERAL(37, 608, 7), // "double*"
QT_MOC_LITERAL(38, 616, 11), // "a_pSpectrum"
QT_MOC_LITERAL(39, 628, 13), // "quit_Oxymetry"
QT_MOC_LITERAL(40, 642, 13), // "Load_From_FFT"
QT_MOC_LITERAL(41, 656, 18), // "Load_From_Raw_Data"
QT_MOC_LITERAL(42, 675, 26), // "conf_Setup_Pol_Measurement"
QT_MOC_LITERAL(43, 702, 30), // "select_Analize_Pol_Measurement"
QT_MOC_LITERAL(44, 733, 22), // "toggle_Pol_Calibration"
QT_MOC_LITERAL(45, 756, 15), // "run_Polarimetry"
QT_MOC_LITERAL(46, 772, 7), // "runType"
QT_MOC_LITERAL(47, 780, 20), // "stop_Run_Polarimetry"
QT_MOC_LITERAL(48, 801, 16), // "toggle_Load_Data"
QT_MOC_LITERAL(49, 818, 8), // "plot_FFT"
QT_MOC_LITERAL(50, 827, 10), // "clear_Plot"
QT_MOC_LITERAL(51, 838, 14), // "save_Graph_Pol"
QT_MOC_LITERAL(52, 853, 12), // "plot_Average"
QT_MOC_LITERAL(53, 866, 16), // "adjust_Run_Start"
QT_MOC_LITERAL(54, 883, 9), // "short int"
QT_MOC_LITERAL(55, 893, 7), // "typeRun"
QT_MOC_LITERAL(56, 901, 14), // "adjust_Run_End"
QT_MOC_LITERAL(57, 916, 33), // "adjust_Measurements_Saving_Fo..."
QT_MOC_LITERAL(58, 950, 25), // "process_Received_Data_Pol"
QT_MOC_LITERAL(59, 976, 4), // "Path"
QT_MOC_LITERAL(60, 981, 22), // "delay_Pol_Measurements"
QT_MOC_LITERAL(61, 1004, 23), // "update_Wavelength_Range"
QT_MOC_LITERAL(62, 1028, 23), // "adjust_Wavelength_Range"
QT_MOC_LITERAL(63, 1052, 15), // "normalizeCounts"
QT_MOC_LITERAL(64, 1068, 18), // "saveFFTcalibration"
QT_MOC_LITERAL(65, 1087, 15), // "enable_Help_Pol"
QT_MOC_LITERAL(66, 1103, 16) // "setConfiguration"

    },
    "PanelPolarimeter\0updateTabs\0\0"
    "DisEnablePreview\0showUI_Item\0UIstatus\0"
    "selected_Spectrometer_Pol\0help_Pol\0"
    "change_Number_Averages_Pol\0"
    "change_Frequency_Pol\0change_Number_Spectra_Pol\0"
    "change_Wavelength_FFT_Pol\0"
    "change_Auto_Integration_Time_Pol\0"
    "Load_Summary\0write_Summary\0"
    "change_Integration_Time_Pol\0showAllPlots\0"
    "clean_All_Pol\0initialize_Calibration\0"
    "pol_Measurement_Progress\0i\0pol_Calibrate\0"
    "pol_Measure\0initialize_Default_Calibration\0"
    "adjust_Average_Plot_Time\0"
    "adjust_Integration_Time_Pol\0"
    "handle_Click_Event\0QWidget*\0widget\0"
    "receive_Data_Pol\0WParam\0LParam\0"
    "toggle_Pol_Measurement\0change_File_Name\0"
    "write_To_File\0FILE*\0file\0double*\0"
    "a_pSpectrum\0quit_Oxymetry\0Load_From_FFT\0"
    "Load_From_Raw_Data\0conf_Setup_Pol_Measurement\0"
    "select_Analize_Pol_Measurement\0"
    "toggle_Pol_Calibration\0run_Polarimetry\0"
    "runType\0stop_Run_Polarimetry\0"
    "toggle_Load_Data\0plot_FFT\0clear_Plot\0"
    "save_Graph_Pol\0plot_Average\0"
    "adjust_Run_Start\0short int\0typeRun\0"
    "adjust_Run_End\0adjust_Measurements_Saving_Folder\0"
    "process_Received_Data_Pol\0Path\0"
    "delay_Pol_Measurements\0update_Wavelength_Range\0"
    "adjust_Wavelength_Range\0normalizeCounts\0"
    "saveFFTcalibration\0enable_Help_Pol\0"
    "setConfiguration"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PanelPolarimeter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      51,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  269,    2, 0x06 /* Public */,
       3,    1,  270,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,  273,    2, 0x08 /* Private */,
       6,    0,  276,    2, 0x08 /* Private */,
       7,    0,  277,    2, 0x08 /* Private */,
       8,    0,  278,    2, 0x08 /* Private */,
       9,    0,  279,    2, 0x08 /* Private */,
      10,    0,  280,    2, 0x08 /* Private */,
      11,    0,  281,    2, 0x08 /* Private */,
      12,    0,  282,    2, 0x08 /* Private */,
      13,    0,  283,    2, 0x08 /* Private */,
      14,    0,  284,    2, 0x08 /* Private */,
      15,    0,  285,    2, 0x08 /* Private */,
      16,    0,  286,    2, 0x08 /* Private */,
      17,    0,  287,    2, 0x08 /* Private */,
      18,    0,  288,    2, 0x08 /* Private */,
      19,    1,  289,    2, 0x08 /* Private */,
      21,    0,  292,    2, 0x08 /* Private */,
      22,    0,  293,    2, 0x08 /* Private */,
      23,    0,  294,    2, 0x08 /* Private */,
      24,    0,  295,    2, 0x08 /* Private */,
      25,    0,  296,    2, 0x08 /* Private */,
      26,    1,  297,    2, 0x08 /* Private */,
      29,    2,  300,    2, 0x08 /* Private */,
      32,    0,  305,    2, 0x08 /* Private */,
      33,    0,  306,    2, 0x08 /* Private */,
      34,    3,  307,    2, 0x08 /* Private */,
      39,    0,  314,    2, 0x08 /* Private */,
      40,    0,  315,    2, 0x08 /* Private */,
      41,    0,  316,    2, 0x08 /* Private */,
      42,    0,  317,    2, 0x08 /* Private */,
      43,    0,  318,    2, 0x08 /* Private */,
      44,    0,  319,    2, 0x08 /* Private */,
      45,    1,  320,    2, 0x08 /* Private */,
      47,    0,  323,    2, 0x08 /* Private */,
      48,    0,  324,    2, 0x08 /* Private */,
      49,    0,  325,    2, 0x08 /* Private */,
      50,    0,  326,    2, 0x08 /* Private */,
      51,    0,  327,    2, 0x08 /* Private */,
      52,    0,  328,    2, 0x08 /* Private */,
      53,    1,  329,    2, 0x08 /* Private */,
      56,    0,  332,    2, 0x08 /* Private */,
      57,    0,  333,    2, 0x08 /* Private */,
      58,    1,  334,    2, 0x08 /* Private */,
      60,    0,  337,    2, 0x08 /* Private */,
      61,    0,  338,    2, 0x08 /* Private */,
      62,    0,  339,    2, 0x08 /* Private */,
      63,    0,  340,    2, 0x08 /* Private */,
      64,    0,  341,    2, 0x08 /* Private */,
      65,    0,  342,    2, 0x0a /* Public */,
      66,    0,  343,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   30,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 35, 0x80000000 | 37, QMetaType::Int,   36,   38,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Short,   46,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 54,   55,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   59,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PanelPolarimeter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PanelPolarimeter *_t = static_cast<PanelPolarimeter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateTabs(); break;
        case 1: _t->DisEnablePreview((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->showUI_Item((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->selected_Spectrometer_Pol(); break;
        case 4: _t->help_Pol(); break;
        case 5: _t->change_Number_Averages_Pol(); break;
        case 6: _t->change_Frequency_Pol(); break;
        case 7: _t->change_Number_Spectra_Pol(); break;
        case 8: _t->change_Wavelength_FFT_Pol(); break;
        case 9: _t->change_Auto_Integration_Time_Pol(); break;
        case 10: _t->Load_Summary(); break;
        case 11: _t->write_Summary(); break;
        case 12: _t->change_Integration_Time_Pol(); break;
        case 13: _t->showAllPlots(); break;
        case 14: _t->clean_All_Pol(); break;
        case 15: _t->initialize_Calibration(); break;
        case 16: _t->pol_Measurement_Progress((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 17: _t->pol_Calibrate(); break;
        case 18: _t->pol_Measure(); break;
        case 19: _t->initialize_Default_Calibration(); break;
        case 20: _t->adjust_Average_Plot_Time(); break;
        case 21: _t->adjust_Integration_Time_Pol(); break;
        case 22: _t->handle_Click_Event((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 23: _t->receive_Data_Pol((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 24: _t->toggle_Pol_Measurement(); break;
        case 25: _t->change_File_Name(); break;
        case 26: _t->write_To_File((*reinterpret_cast< FILE*(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 27: _t->quit_Oxymetry(); break;
        case 28: _t->Load_From_FFT(); break;
        case 29: _t->Load_From_Raw_Data(); break;
        case 30: _t->conf_Setup_Pol_Measurement(); break;
        case 31: _t->select_Analize_Pol_Measurement(); break;
        case 32: _t->toggle_Pol_Calibration(); break;
        case 33: _t->run_Polarimetry((*reinterpret_cast< short(*)>(_a[1]))); break;
        case 34: _t->stop_Run_Polarimetry(); break;
        case 35: _t->toggle_Load_Data(); break;
        case 36: _t->plot_FFT(); break;
        case 37: _t->clear_Plot(); break;
        case 38: _t->save_Graph_Pol(); break;
        case 39: _t->plot_Average(); break;
        case 40: _t->adjust_Run_Start((*reinterpret_cast< short int(*)>(_a[1]))); break;
        case 41: _t->adjust_Run_End(); break;
        case 42: _t->adjust_Measurements_Saving_Folder(); break;
        case 43: _t->process_Received_Data_Pol((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 44: _t->delay_Pol_Measurements(); break;
        case 45: _t->update_Wavelength_Range(); break;
        case 46: _t->adjust_Wavelength_Range(); break;
        case 47: _t->normalizeCounts(); break;
        case 48: _t->saveFFTcalibration(); break;
        case 49: _t->enable_Help_Pol(); break;
        case 50: _t->setConfiguration(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PanelPolarimeter::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PanelPolarimeter::updateTabs)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PanelPolarimeter::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PanelPolarimeter::DisEnablePreview)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject PanelPolarimeter::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PanelPolarimeter.data,
      qt_meta_data_PanelPolarimeter,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PanelPolarimeter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelPolarimeter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PanelPolarimeter.stringdata0))
        return static_cast<void*>(const_cast< PanelPolarimeter*>(this));
    return QWidget::qt_metacast(_clname);
}

int PanelPolarimeter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 51)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 51;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 51)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 51;
    }
    return _id;
}

// SIGNAL 0
void PanelPolarimeter::updateTabs()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PanelPolarimeter::DisEnablePreview(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
