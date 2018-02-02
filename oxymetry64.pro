QT += core gui widgets serialport

TARGET = oxymetry64
TEMPLATE = app
CONFIG += qwt

DEFINES += amd64

DESTDIR = $$PWD/./redist/binary/amd64
QMAKE_CXXFLAGS += -m64 -static-libgcc -static-libstdc++

INCLUDEPATH += $$PWD/./ $$PWD/./include
LIBS += -L$$PWD/./ -L$$PWD/./lib/amd64 -lavaspecx64 -lqwt.dll -lusb-1.0.dll -lfftw3-3.dll -liad64

CONFIG(debug, debug|release) {
    OBJECTS_DIR = $$PWD/./build/amd64/debug/.obj
    MOC_DIR = $$PWD/./build/amd64/debug/.moc
    RCC_DIR = $$PWD/./build/amd64/debug/.rcc
    UI_DIR = $$PWD/./build/amd64/debug/.ui
}

CONFIG(release, debug|release) {
    OBJECTS_DIR = $$PWD/./build/amd64/release/.obj
    MOC_DIR = $$PWD/./build/amd64/release/.moc
    RCC_DIR = $$PWD/./build/amd64/release/.rcc
    UI_DIR = $$PWD/./build/amd64/release/.ui
}

SOURCES += \
    main.cpp \
    application.cpp \
    messages.cpp \
    splash.cpp \
    spectrometer.cpp \
    spectrometer_config.cpp \
    spectrometer_eeprom.cpp \
    clickablelabel.cpp \
    plot.cpp \
    measurementstable.cpp \
    initial_setup.cpp \
    panel.cpp \
    panel_about.cpp \
    panel_item.cpp \
    panel_change_averages.cpp \
    panel_change_time.cpp \
    panel_legend.cpp \
    panel_storetoram.cpp \
    panel_timepattern.cpp \
    iad_configure.cpp \
    iad_configure_page01.cpp \
    iad_configure_page02.cpp \
    iad_calibrate.cpp \
    iad_calibrate_page01.cpp \
    iad_calibrate_page02.cpp \
    iad_calibrate_page03.cpp \
    iad_measure.cpp \
    iad_panel.cpp \
    math_helper.cpp \
    timer.cpp \
    fluidic_connect.cpp \
    fluidic_control.cpp \
    light_control.cpp \
    pol_configureMeasurement.cpp \
    pol_fft.cpp \
    pol_changeWave_FFT.cpp \
    pol_panelHelp.cpp \
    pol_panelItem.cpp \
    pol_panel.cpp \
    pol_plot.cpp \
    pol_measurements.cpp \
    pol_externConf.cpp

HEADERS += \
    application.h \
    messages.h \
    splash.h \
    spectrometer.h \
    spectrometer_config.h \
    spectrometer_eeprom.h \
    clickablelabel.h \
    plot.h \
    measurementstable.h \
    initial_setup.h \
    panel.h \
    panel_about.h \
    panel_item.h \
    panel_change_averages.h \
    panel_change_time.h \
    panel_legend.h \
    panel_storetoram.h \
    panel_timepattern.h \
    iad_configure.h \
    iad_configure_page01.h \
    iad_configure_page02.h \
    iad_calibrate.h \
    iad_calibrate_page01.h \
    iad_calibrate_page02.h \
    iad_calibrate_page03.h \
    iad_measure.h \
    iad_panel.h \
    math_helper.h \
    timer.h \
    fluidic_connect.h \
    fluidic_control.h \
    light_control.h \
    pol_configureMeasurement.h \
    pol_fft.h \
    pol_changeWave_FFT.h \
    pol_panelHelp.h \
    pol_panelItem.h \
    pol_panel.h \
    pol_plot.h \
    pol_measurements.h \
    pol_externConf.h

FORMS += \
    initial_setup.ui \
    panel.ui \
    panel_about.ui \
    panel_item.ui \
    panel_change_averages.ui \
    panel_change_time.ui \
    panel_legend.ui \
    panel_storetoram.ui \
    panel_timepattern.ui \
    spectrometer_config.ui \
    spectrometer_eeprom.ui \
    iad_configure_page01.ui \
    iad_configure_page02.ui \
    iad_calibrate_page01.ui \
    iad_calibrate_page02.ui \
    iad_calibrate_page03.ui \
    iad_panel.ui \
    fluidic_connect.ui \
    fluidic_control.ui \
    light_control.ui \
    pol_configureMeasurement.ui \
    pol_changeWave_FFT.ui \
    pol_panelHelp.ui \
    pol_panelItem.ui \
    pol_panel.ui

DISTFILES += \
    oxymetry.rc

RC_FILE = oxymetry.rc

RESOURCES += \
    icons.qrc
