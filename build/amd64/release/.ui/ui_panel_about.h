/********************************************************************************
** Form generated from reading UI file 'panel_about.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_ABOUT_H
#define UI_PANEL_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelAbout
{
public:
    QPushButton *button_close;
    QLabel *label_title;
    QLabel *label_compiler;
    QLabel *label_build;
    QLabel *label_copyright;
    QLabel *label_license;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPlainTextEdit *plainTextEdit_changelog;
    QWidget *tab_2;
    QPlainTextEdit *plainTextEdit_contributors;

    void setupUi(QDialog *PanelAbout)
    {
        if (PanelAbout->objectName().isEmpty())
            PanelAbout->setObjectName(QStringLiteral("PanelAbout"));
        PanelAbout->resize(470, 400);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PanelAbout->sizePolicy().hasHeightForWidth());
        PanelAbout->setSizePolicy(sizePolicy);
        PanelAbout->setSizeIncrement(QSize(0, 0));
        button_close = new QPushButton(PanelAbout);
        button_close->setObjectName(QStringLiteral("button_close"));
        button_close->setGeometry(QRect(380, 190, 75, 23));
        button_close->setFlat(false);
        label_title = new QLabel(PanelAbout);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(140, 10, 311, 21));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_title->setFont(font);
        label_compiler = new QLabel(PanelAbout);
        label_compiler->setObjectName(QStringLiteral("label_compiler"));
        label_compiler->setGeometry(QRect(140, 40, 310, 20));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_compiler->sizePolicy().hasHeightForWidth());
        label_compiler->setSizePolicy(sizePolicy1);
        label_compiler->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_build = new QLabel(PanelAbout);
        label_build->setObjectName(QStringLiteral("label_build"));
        label_build->setGeometry(QRect(140, 60, 311, 21));
        label_build->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_copyright = new QLabel(PanelAbout);
        label_copyright->setObjectName(QStringLiteral("label_copyright"));
        label_copyright->setGeometry(QRect(140, 80, 311, 31));
        label_copyright->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_license = new QLabel(PanelAbout);
        label_license->setObjectName(QStringLiteral("label_license"));
        label_license->setGeometry(QRect(140, 120, 311, 61));
        label_license->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        tabWidget = new QTabWidget(PanelAbout);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 210, 451, 181));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        plainTextEdit_changelog = new QPlainTextEdit(tab);
        plainTextEdit_changelog->setObjectName(QStringLiteral("plainTextEdit_changelog"));
        plainTextEdit_changelog->setGeometry(QRect(10, 10, 425, 135));
        plainTextEdit_changelog->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextEdit_changelog->setReadOnly(true);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        plainTextEdit_contributors = new QPlainTextEdit(tab_2);
        plainTextEdit_contributors->setObjectName(QStringLiteral("plainTextEdit_contributors"));
        plainTextEdit_contributors->setGeometry(QRect(10, 10, 425, 135));
        plainTextEdit_contributors->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextEdit_contributors->setReadOnly(true);
        tabWidget->addTab(tab_2, QString());
        label_license->raise();
        button_close->raise();
        label_title->raise();
        label_compiler->raise();
        label_build->raise();
        label_copyright->raise();
        tabWidget->raise();

        retranslateUi(PanelAbout);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PanelAbout);
    } // setupUi

    void retranslateUi(QDialog *PanelAbout)
    {
        PanelAbout->setWindowTitle(QApplication::translate("PanelAbout", "About Oxymetry", Q_NULLPTR));
        button_close->setText(QApplication::translate("PanelAbout", "Close", Q_NULLPTR));
        label_title->setText(QApplication::translate("PanelAbout", "Oxymetry 0.8", Q_NULLPTR));
        label_compiler->setText(QApplication::translate("PanelAbout", "<Compiler info>", Q_NULLPTR));
        label_build->setText(QApplication::translate("PanelAbout", "<Build info>", Q_NULLPTR));
        label_copyright->setText(QApplication::translate("PanelAbout", "<Copyright info>", Q_NULLPTR));
        label_license->setText(QApplication::translate("PanelAbout", "<License>", Q_NULLPTR));
        plainTextEdit_changelog->setPlainText(QApplication::translate("PanelAbout", "Version 0.8: (01.11.2018)\n"
"+ The box Spectrometer contains all the settings and information of the selected spectrometer from the tab preview. This options become modifiable during the Calibration phase.\n"
"+ The tube Temperature will display the actual setup temperature measured with the Teensy card. When doing click on the label, the interface will show the temperature plot along the time.\n"
"+ The table \"Measurement Profile\" will show the measured concentrations and their measurement time. Also, the corresponding substances are displayed at the bottom.\n"
"+ The 4 plots in the tab Live Data shows the current measured data of raw signal, the ratio, the FFt profile and the live signals average. \n"
"+ \n"
"\n"
"Version 0.7.1: (30.07.2018)\n"
"+ Configuration Files with exclusive extension .csar\n"
"+ More substances can be added (up to 7 substances)\n"
"+ Measurement Summary (.sum) file to load the average signals DC, W and 2W\n"
"+ Load of the measurement summary\n"
"+ Memory space for FFT and Raw Dat"
                        "a files displayed\n"
"+ Addition of impurities is now dynamic through a button\n"
"+ The user can decide now the interval of time for the measurements (User Interval Mode)\n"
"+ The user can select the saving option sin the configuration window\n"
"+ Concentration values are now shown instead of the file names\n"
"+ The software highlights all the measurements already done\n"
"+ Names of substances are shown in the Pumps and FFT Files\n"
"- Saving options aren't shown in the main panel anymore \n"
"- File names aren't shown in the measurement list anymore\n"
"\n"
"Version 0.7: (15.06.2018)\n"
"+ Zoom of Average signal plot, now the user is able to zoom in the plots.\n"
"+ New interface to hide/show plots.\n"
"+ The user can now Normalize the measurements in counts per second.\n"
"+ New interface for the configuration of the measurements.\n"
"+ The configuration information is now saved into a file, which allows the user to load a complete measurement setting.\n"
"+ The user can now modify the configuration fil"
                        "e during the calibration phase.\n"
"+ Now the plots are divided in tabs, which will allow a separation between phases of the measurement.\n"
"+ New user interface for the selection of files for validation and calibration called \"Analize Data\".\n"
"+ More user friendly status bar.\n"
"+ The configuration interface now shows more precisely the required time for a measurement, as well as the time of start and end.\n"
"+ The user can select a delay in the start of the measurement in the configuration, for example 8 hours of waiting until the measurement starts.\n"
"+ The user can change the size of the columns in the Measurement List in order to read the file names more easily.\n"
"+ The user can create up to 2 impurities plus the glucose concentration.\n"
"+ Loading old data now shows only the needed plots.\n"
"+ Now the user has a dialog counting down 5 seconds before the start of the measurements.\n"
"+ The average plot shows numerically the average value of the signals.\n"
"+ The Maximum DC intensity and it'"
                        "s wavelength are now shown in the FFT plots in the side panel.\n"
"- Plot of Concentration prediction in main plots window. It's now present in a different plots tab.\n"
"* Several bugs fixed during calibration, measurement and configuration.\n"
"\n"
"Version 0.6.1: (17.01.2018)\n"
"\n"
"+ Plots and GUI elements selection.\n"
"+ GUI elements by demand.\n"
"+ Plot of Concentration prediction.\n"
"+ Update of GUI according to measurements.\n"
"+ Non Modal help window.\n"
"+ preview Tab now is also updated from Polarimeter tab.\n"
"+ Polarimeter plots are now a class.\n"
"- Zoom of Average signal plot.\n"
"\n"
"Version 0.6: (22.12.2017)\n"
"\n"
"+ Reintroduced the 32 bit version\n"
"+ Improved build process\n"
"+ Fluidic toolkit now supports roller pump driven by stepper motor\n"
"+ Tabs in panel are now handled as modules\n"
"+ Configuration file is now created automatically\n"
"+ Inverse Adding-Doubling algorithm is no external program anymore, but integrated as library instead\n"
"* Several bug fixes at automa"
                        "tic adjustment of integration time\n"
"\n"
"Version 0.5: (05.12.2017)\n"
"\n"
"Polarimeter Tab:\n"
"+ Live FFT in periods of time depending on spectrometer settings.\n"
"+ Live Raw signal and live FTT.\n"
"+ Live Raw signal during breaks of measurements.\n"
"+ Quit oxymetry now closes all running loops and closes the app completely.\n"
"+ Information Bar at the botton.\n"
"+ Toggle Button for data loading.\n"
"+ Clear All option to restart all configurations and plots.\n"
"+ Auto change of name of files in measurement profile when changes are made during calibration.\n"
"+ Calibration independent of measurement, but could be done with the loaded configuration.\n"
"+ Automatic adjustement of plots according to all new settings.\n"
"+ Autoadjustment of integration time adapted to calibration.\n"
"+ Warnings on adjustement of settings out of range.\n"
"+ Auto adjusting of frequency according to selected integration time when needed. As well as a top limit.\n"
"- Live Average Raw Signal Display with time dependenc"
                        "y. (Not needed).\n"
"+ Help button to guide user through the polarimeter tab.\n"
"+ When saving data, the old data with thte same name isn't overwrited, instead a new folder date_X is created, where X is a number.\n"
"+ When changing Nr Spectra or Frequency values but not pressing enter, the old values are returned to the table cell.\n"
"+ Automatic adjustement of axis on Live Raw Signal plot.\n"
"\n"
"Version 0.4.3: (26.10.2017)\n"
"\n"
"Polarimeter Tab:\n"
"+ Live Average Raw Signal Display with time dependency.\n"
"+ Autoadjust of Plot X and Y axis according to the ploted data.\n"
"+ Load of data from FFT file or Raw Data File.\n"
"+ Save option of FFT Analyzed Data.\n"
"+ Save Graphs to PDF.\n"
"+ Measurement Profile Load or Edition.\n"
"+ Calibration Option for Polarimeter Tab.\n"
"+ Plot of the FFT at the selected wavelength.\n"
"+ Raw Signal Plot independent from Preview Tab.\n"
"+ Spectra, Integration Time and Averaging Profile are now shown in Measurement Profile.\n"
"+ Colored Start/Stop measurement "
                        "toggle button.\n"
"- Disabled preview/polarimeter setup when one preview/polarimeter setup is active.\n"
"\n"
"Version 0.4.2: (08.10.2017)\n"
"\n"
"- Dropped support for 32-bit OS\n"
"+ Code cleanup and restructuring\n"
"\n"
"Version 0.4.1: (06.10.2017)\n"
"\n"
"+ Added button for polarimeter setup\n"
"+ Implemented FFT data analysis\n"
"+ Disabled preview/polarimeter setup when one preview/polarimeter setup is active\n"
"+ Modification of polarimeter setup tab panel\n"
"+ Toggle button for polarimeter setup\n"
"+ File and folder creation when polarimetric measurement starts\n"
"\n"
"Version 0.4.0: (02.10.2017)\n"
"\n"
"+ Added files for polarimeter control\n"
"+ Added FFTW library and data folder\n"
"\n"
"Version 0.3.0: (29.09.2017)\n"
"\n"
"* Legend now shows 'unknown' if serial number or readable name of spectrometer are not available\n"
"* Fixed spectra count in StoreToRAM files\n"
"* Changes of readable name are now accepted\n"
"* Disabling/enabling of a device now disables all elements in device item\n"
""
                        "+ Many code optimizations, especially to the StoreToRAM function and the spectrometer configuration dialog\n"
"+ Time-controlled measurements can now be automated via button 'time pattern'\n"
"+ The serial number of the device is no longer attached to the file names of StoreToRAM\n"
"+ StoreToRAM now supports more than 10000 spectra\n"
"+ Wavelengths are shown belong pixel numbers in configuration dialog\n"
"+ Combined 'preview start' and 'preview stop' buttons into one single button\n"
"\n"
"Version 0.2.6: (04.09.2017)\n"
"\n"
"* Fixed a bug that prevented data export\n"
"+ Increased maximum of StoreToRAM spectra\n"
"+ StoreToRAM dialog remembers last path\n"
"\n"
"Version 0.2.5: (14.08.2017)\n"
"\n"
"* Updated AvaSpec library to version 9.6.0.0\n"
"\n"
"Version 0.2.4: (19.06.2017)\n"
"\n"
"+ Support of increased peristaltic pump RPM update rate\n"
"+ RPM in fluidic toolbox is now calculated over a period of one second\n"
"* Compatibility check for Qt 5.9.0\n"
"\n"
"Version 0.2.3: (14.06.2017)\n"
"\n"
"+ The "
                        "user must now confirm whether existing files should be overwritten during data export\n"
"\n"
"Version 0.2.2: (29.05.2017)\n"
"\n"
"* Fixed calculation of fluidic circuit rollerpump RPM\n"
"* Fixed bug that prevented the first pinch valve from being switched\n"
"* Fixed a bug that caused the user to be overwhelmed with error messages when the light source was disconnected during operation\n"
"+ Added fluidic circuit auto-connect functionality\n"
"+ Added changelog and contributors lists\n"
"- Removed message if no spectrometers were found\n"
"\n"
"Version 0.2.1 (24.05.2017):\n"
"\n"
"+ The spectral data from the spectrometers are now stored in separate files\n"
"+ Additional information (dynamic dark correction enabled, time and date, ...) is now stored within the saved spectra\n"
"\n"
"Version 0.2:\n"
"\n"
"Initial release", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("PanelAbout", "Changelog", Q_NULLPTR));
        plainTextEdit_contributors->setPlainText(QApplication::translate("PanelAbout", "Benjamin Redmer, Cesar Andres Carvajal Arrieta, Torben Kruse, Isabeau Dibbern", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("PanelAbout", "Contributors", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelAbout: public Ui_PanelAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_ABOUT_H
