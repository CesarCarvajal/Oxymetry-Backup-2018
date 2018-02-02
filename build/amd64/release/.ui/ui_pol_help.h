/********************************************************************************
** Form generated from reading UI file 'pol_help.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POL_HELP_H
#define UI_POL_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelpW
{
public:
    QWidget *Help;
    QPlainTextEdit *plainTextEdit_changelog;
    QPushButton *button_polhelp_close;
    QLabel *label_title;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HelpW)
    {
        if (HelpW->objectName().isEmpty())
            HelpW->setObjectName(QStringLiteral("HelpW"));
        HelpW->resize(800, 600);
        Help = new QWidget(HelpW);
        Help->setObjectName(QStringLiteral("Help"));
        plainTextEdit_changelog = new QPlainTextEdit(Help);
        plainTextEdit_changelog->setObjectName(QStringLiteral("plainTextEdit_changelog"));
        plainTextEdit_changelog->setGeometry(QRect(154, 110, 471, 271));
        plainTextEdit_changelog->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextEdit_changelog->setReadOnly(true);
        button_polhelp_close = new QPushButton(Help);
        button_polhelp_close->setObjectName(QStringLiteral("button_polhelp_close"));
        button_polhelp_close->setGeometry(QRect(540, 390, 75, 23));
        button_polhelp_close->setFlat(false);
        label_title = new QLabel(Help);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(290, 50, 181, 21));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_title->setFont(font);
        HelpW->setCentralWidget(Help);
        menubar = new QMenuBar(HelpW);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        HelpW->setMenuBar(menubar);
        statusbar = new QStatusBar(HelpW);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        HelpW->setStatusBar(statusbar);

        retranslateUi(HelpW);

        QMetaObject::connectSlotsByName(HelpW);
    } // setupUi

    void retranslateUi(QMainWindow *HelpW)
    {
        HelpW->setWindowTitle(QApplication::translate("HelpW", "MainWindow", Q_NULLPTR));
        plainTextEdit_changelog->setPlainText(QApplication::translate("HelpW", "Welcome to Polarimeter Measurement Tab!\n"
"\n"
"1. How do I start the Calibration?\n"
"\n"
"There are two different ways to perform the calibration, one is with a loaded configuration file (see 2) and the other is just a default settings calibration.\n"
"\n"
"Go to the \"Calibrate\" button and select option \"Yes\" in case to load a configuration file or \"No\" to use default values.\n"
"\n"
"Changes during the calibration will affect the loaded configuration according to the user modifications, also will be used for the further \"Start Measurement\" option. (See 3)\n"
"\n"
"2. How do I load a configuration?\n"
"\n"
"Go to the button \"Configure\" and load a configuration file .txt or create your own measurement profile.\n"
"\n"
"3. How I do perform a measurement?\n"
"\n"
"First load a configuration file (see 2), then press the \"Start Measurement\" and wait for each data processing. \n"
"\n"
"The resulting saved Raw data is located in the same directory than the configuration file, and the resulting FFT data"
                        " is located in \"/bin/data_polarimeter/FFT Polarimeter Measurements\" with a folder named with the date of the measurment.\n"
"\n"
"4. How do I save the data?\n"
"\n"
"You could save a Raw Data file and/or the FFT Data file.\n"
"\n"
"Select one or both options in the check boxes \" Raw Data\" and/or \"FFT Profiles\".\n"
"\n"
"5. How do I set a parameter for the calibration?\n"
"\n"
"Click the parameter's label and select or write the new value.\n"
"\n"
"The Calibration process is restarted after every change to apply them in the system.\n"
"\n"
"For the frequency and number of spectra, the key \"Enter\" is needed to accept the changes.\n"
"\n"
"6. Can I change manually the time and name of files for the measurement profile?\n"
"\n"
"No directly, to do that, you'll have to load a new configuration file.\n"
"\n"
"However, changes during the calibration could be reflected on this settings. (i. e. Integration time changes).\n"
"\n"
"7. How long are the intervals in between measurements during the calibration?\n"
""
                        "\n"
"It depends on the actual settings, it can go up to minutes for large integration times, number of spectra or number of averages.\n"
"\n"
"8. How to auto adjust the integration time?\n"
"\n"
"Just click the corresponding label.\n"
"\n"
"9. How do I know which spectrometer is currently in use?\n"
"\n"
"It is shown in the spectrometer list in polarimeter tab. Also, it's the first checked spectrometer from the Preview Tab List.\n"
"\n"
"10. How do I load Data?\n"
"\n"
"You can load FFT data or Raw data to be analyzed. Press \"Load Data\" and then select \"Raw Data\" or \"FFT Data\" to load the file.\n"
"\n"
"Remember that raw data has the form XXC1_XXC2_XXms_XXHz_XX.CS/.TXT and the FFT data has the form   XXC1_XXC2_XXms_XXHz_XX_FFT.txt.\n"
"\n"
"11. Why is there a Temp.tmp file in my folder data_polarimeter?\n"
"\n"
"This file collects the data from the calibration but it is not preserved since it can become large in disk space.\n"
"\n"
"12. What is Clear All?\n"
"\n"
"It cleans all the plots in the tab, as w"
                        "ell to restart everything to the default values. Also removes any loaded configuration.\n"
"\n"
"13. When can I vary the parameters?\n"
"\n"
"Only during the calibration phase, this to avoid changes for example when the measurement is running automatically.\n"
"\n"
"14. How to save a graph?\n"
"\n"
"Click on \"Save Graphs\" and select the folder where the PDF files will be saved. One per each plot of Compensation and FFT profile.\n"
"\n"
"15. Why the software is not responding?\n"
"\n"
"It might be that you are trying to load a corrupt file type, for example an empty file txt for loading data or configuration. Also, it may happens when the spectrometer is overloaded.\n"
"\n"
"This is avoided, in general warnings are shown to the user that a file is not correct, and the spectrometer is usually stoped when the load is to high.\n"
"\n"
"16. What I'm saving when choosing \"FFT Profiles\" box?\n"
"\n"
"The amplitudes of the components DC, W, 2W and the ratio W/2W.Also their corresponding wavelengths.\n"
"\n"
"17. H"
                        "ow can I change the wavelength of the FFT plot?\n"
"\n"
"Just click the label of the wavelength number and select the desired one. This change will remain during all the calibration or measurements.\n"
"\n"
"18. How do I change the frequency where the FFT is extracted?\n"
"\n"
"Click in the box with the frequency number in the table with the column \"Frequency\", then write the desired frequency, press the key \"Enter\" and wait for the changes to be applied.\n"
"\n"
"* Same applies for changing the number of spectra.\n"
"\n"
"19. Why it takes too long to measure the FFT?\n"
"\n"
"The Spectrometer needs certain amount of time to collect the data from the probe and save it as a temporal file during the calibration. Furthermore, this data is analyzed by the FFT and plotted in real time.\n"
"\n"
"The length of this time depends on (IntTime * Number of Averages * Number of Spectra). So for large values of any of this three variables, the system will take some time to process the data.\n"
"\n"
"20. Why I can see th"
                        "e Live Raw data only a few seconds?\n"
"\n"
"It can be seen for approximatelly 7 seconds. This time is short in order to also reduce the total real time processing of data. \n"
"\n"
"Thus the real data time processing consists of the time of raw data + the time of spectra measurement + time of data processing and ploting.\n"
"\n"
"21. Why the plots are disturbed sometimes after stopping the calibration?\n"
"\n"
"Sometimes it happens when the calibration is stopped and the spectrometer was busy measuring.", Q_NULLPTR));
        button_polhelp_close->setText(QApplication::translate("HelpW", "Close", Q_NULLPTR));
        label_title->setText(QApplication::translate("HelpW", "Polarimeter Tab Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HelpW: public Ui_HelpW {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_HELP_H
