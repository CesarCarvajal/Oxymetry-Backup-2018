/********************************************************************************
** Form generated from reading UI file 'pol_panelHelp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POL_PANELHELP_H
#define UI_POL_PANELHELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PanelPolHelp
{
public:
    QPushButton *button_polhelp_close;
    QLabel *label_title;
    QPlainTextEdit *plainTextEdit_changelog;

    void setupUi(QDialog *PanelPolHelp)
    {
        if (PanelPolHelp->objectName().isEmpty())
            PanelPolHelp->setObjectName(QStringLiteral("PanelPolHelp"));
        PanelPolHelp->resize(500, 400);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PanelPolHelp->sizePolicy().hasHeightForWidth());
        PanelPolHelp->setSizePolicy(sizePolicy);
        PanelPolHelp->setSizeIncrement(QSize(0, 0));
        button_polhelp_close = new QPushButton(PanelPolHelp);
        button_polhelp_close->setObjectName(QStringLiteral("button_polhelp_close"));
        button_polhelp_close->setGeometry(QRect(400, 360, 75, 23));
        button_polhelp_close->setFlat(false);
        label_title = new QLabel(PanelPolHelp);
        label_title->setObjectName(QStringLiteral("label_title"));
        label_title->setGeometry(QRect(150, 20, 181, 21));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_title->setFont(font);
        plainTextEdit_changelog = new QPlainTextEdit(PanelPolHelp);
        plainTextEdit_changelog->setObjectName(QStringLiteral("plainTextEdit_changelog"));
        plainTextEdit_changelog->setGeometry(QRect(14, 80, 471, 271));
        plainTextEdit_changelog->setLayoutDirection(Qt::LeftToRight);
        plainTextEdit_changelog->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plainTextEdit_changelog->setReadOnly(true);
        plainTextEdit_changelog->setBackgroundVisible(false);
        plainTextEdit_changelog->setCenterOnScroll(false);

        retranslateUi(PanelPolHelp);

        QMetaObject::connectSlotsByName(PanelPolHelp);
    } // setupUi

    void retranslateUi(QDialog *PanelPolHelp)
    {
        PanelPolHelp->setWindowTitle(QApplication::translate("PanelPolHelp", "Polarimeter Tab Help", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_polhelp_close->setToolTip(QApplication::translate("PanelPolHelp", "Close Help Dialog", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_polhelp_close->setText(QApplication::translate("PanelPolHelp", "Close", Q_NULLPTR));
        label_title->setText(QApplication::translate("PanelPolHelp", "Polarimeter Tab Help", Q_NULLPTR));
        plainTextEdit_changelog->setPlainText(QApplication::translate("PanelPolHelp", "Welcome to the Polarimeter Measurement Tab!\n"
"\n"
"CONTENT:\n"
"\n"
"1. INTERFACE\n"
"2. CONFIGURATION\n"
"3. CALIBRATION\n"
"4. MEASUREMENTS\n"
"5. OTHERS\n"
"6. SOFTWARE ISSUES ?\n"
"\n"
"\n"
"\n"
"-> 1.  INTERFACE\n"
"\n"
"\n"
"1.1 -> How to select a Spectrometer?\n"
"\n"
"Please go to the tab \"Preview\", then select the spectrometer to use in the polarimtery tab. The first spectrometer selected on the list will be the use for the polarimetric measurements.\n"
"\n"
"\n"
"1.2 -> Show/Hide GUI elements:\n"
"\n"
"When a label is clicked, the corresponding element will be shown or hidden accordingly. For example by clicking the label \"Raw Signal\", the corresponding plot will be hidden or shown.\n"
"\n"
"\n"
"1.3 -> What is \"Clear All\"?\n"
"\n"
"With this option, any loaded information or configuration will be removed from the interface. Please remember that this option will also remove any configuration changes or loaded data from the user interface.\n"
"\n"
"\n"
"1.4 -> Interface elements by demand:\n"
""
                        "\n"
"The user interface will provide some GUI elements when they are required according to the user selection. For example, the table \"Measurement Profile\" will be displayed only after the \"Configuration\" phase, which also has some additional tables and option shown when required.\n"
"\n"
"1.5-> Overall:\n"
"\n"
"+ The box Spectrometer contains all the settings and information of the selected spectrometer from the tab preview. This options become modifiable during the Calibration phase.\n"
"+ The tube Temperature will display the actual setup temperature measured with the Teensy card. When doing click on the label, the interface will show the temperature plot along the time.\n"
"+ The table \"Measurement Profile\" will show the measured concentrations and their measurement time. Also, the corresponding substances are displayed at the bottom.\n"
"+ The 4 plots in the tab Live Data shows the current measured data of raw signal, the ratio, the FFt profile and the live signals average. \n"
"+ \n"
"\n"
"->  2. "
                        "CONFIGURATION\n"
"\n"
"\n"
"2.1 -> How to load a configuration profile?\n"
"\n"
"Please go to the button \"Configure\" and click on the button \"Load Configuration\". Then select the appropriate configuration file with extension \".csar\".\n"
"\n"
"\n"
"2.2 -> How to create a configuration file?\n"
"\n"
"Please go to the button \"Configure\", then fill the form with the label \"Create Configuration File\" with the appropriate values according to the desired configuration profile. Then click in the button \"Generate Configuration\". Here the user can select the name and folder where all the configuration files will be saved.\n"
"\n"
"\n"
"2.3 -> What is created from the option \"Generate Configuration\"?\n"
"\n"
"This option will save in the selected folder the configuration file with the measurement entries and the syringe pumps files to be loaded in the neMESYS User Interface.\n"
"\n"
"\n"
"2.4 -> What else is saved in the folder?\n"
"\n"
"This folder also will contain all the measurement results as Raw Data "
                        "and FFT values. \n"
" \n"
"\n"
"2.5 -> What GUI elements are loaded after the configuration?\n"
"\n"
"After the configuration is loaded or created, a table with the measurement entries will be displayed, as well as the saving options of Raw Data and FFT Profiles. Additionally, the syringe pumps software neMESYS User Interface will be open automatically.\n"
"\n"
"**  Please consider that this option requires a Shortcut Icon in the Desktop named \"NEMESYS\" or the default name \"neMESYS UserInterface\", Otherwise this option might not work properly.\n"
"\n"
"\n"
"2.6 -> What contains the table \"Measurement Profile\" ?\n"
"\n"
"This table contains the time intervals between the measurements and the file name saved for each time interval.\n"
"\n"
"\n"
"2.7 -> What saving options are there?\n"
"\n"
"You could save the Raw Data, which means the file that is generated directly from the Spectrometer. Also, you could save the FFT of the data from the spectrometer. Note that you could save also both files for each time"
                        " interval, however consider the amount of disk space that this option might take for long term measurements. \n"
"\n"
"** At least one type of file to save has to be selected, otherwise the measurement data could be lost.\n"
"\n"
"\n"
"2.8 -> What I'm saving when choosing \"FFT Profiles\" box?\n"
"\n"
"The amplitudes of the components DC, W, 2W and the ratio W/2W.Also their corresponding wavelengths.\n"
"\n"
"\n"
"\n"
"->  3. CALIBRATION\n"
"\n"
"\n"
"3.1 -> How to start the calibration?\n"
"\n"
"Please go to the button \"Calibrate\". The labels of the spectrometer will become editable and values could be changed.\n"
"\n"
"\n"
"3.2 -> How to change values of the configuration?\n"
"\n"
"Please click on the desired parameter and set the new value.\n"
"\n"
"** The interface will restart the calibration automatically each time a parameter is modified.\n"
"\n"
"\n"
"3.3 -> Is the configuration profile modified during the calibration?\n"
"\n"
"Yes. In this phase the user is free to change parameters of the spectrome"
                        "ter and they will be reflected in the loaded file names. However, for changes in the concentrations and time intervals, a new configuration file will have to be created or loaded.\n"
"\n"
"\n"
"3.4 -> When can I vary the spectrometer parameters?\n"
"\n"
"Only during the calibration phase, this to avoid changes for example when the measurement is running automatically.\n"
"\n"
"\n"
"3.5 ->   How long are the intervals in between the spectrometer measurements during the calibration?\n"
"\n"
"It depends on the actual settings, it can go up to minutes for large integration times, number of spectra or number of averages.\n"
"\n"
"\n"
"3.6 -> How the plots are arranged?\n"
"\n"
"During the calibration phase, first the plot of the raw signal is shown for an interval of time, then the FFT data is calculated and showed after processing. This cycle is repeated until the user stops the calibration.\n"
"\n"
"\n"
"3.7 -> Why is there a Temp.tmp file in my software folder \"data_polarimeter\"?\n"
"\n"
"This file collects th"
                        "e data from the calibration but it is not preserved since it can become large in disk space.\n"
"\n"
"\n"
"3.8 -> Why it takes some time for the interface to get the FFT?\n"
"\n"
"The Spectrometer needs certain amount of time to collect the data from the probe and save it as a temporal file during the calibration. Furthermore, this data is analyzed by the FFT and plotted in real time. The length of this time depends on (IntTime * Number of Averages * Number of Spectra). So for large values of any of this three variables, the system will take some time to process the data.\n"
"\n"
"** Please consider that in general very large number of spectra or integration time will lead to larger measurement intervals, which could also overload the computer in use.\n"
"\n"
"\n"
"3.9 -> Why I can see the Live Raw data only a few seconds?\n"
"\n"
"It can be seen for approximatelly 7 seconds. This time is short in order to also reduce the total real time processing of data. Thus the real data time processing consists of the ti"
                        "me of raw data + the time of spectra measurement + time of data processing and ploting.\n"
"\n"
"\n"
"3.10 -> What are those bars at the bottom when doing the calibration?\n"
"\n"
"There is an information bar, which will inform about the current process of the interface. Also there is a progress bar which will show on which plot the interface is working during the cycles.\n"
"\n"
"\n"
"\n"
"->  4. MEASUREMENTS\n"
"\n"
"\n"
"4.1 -> Why can't I start a measurement?\n"
"\n"
"Please check that the spectrometer is not in use in another function at that time. Also a configuration profile is required to start the measurements. (See 2).\n"
"\n"
"\n"
"4.2 -> How do I perform a measurement?\n"
"\n"
"Click the button \"Start Measurement\", the plots will be loaded automatically as well as the progress bars of the measurements. The resulting data will be saved in the same folder of the configuration file.\n"
"\n"
"\n"
"4.3 -> How do I know on which time interval the measurement is?\n"
"\n"
"The table \"Measurement Profile"
                        "\" will highlight the current time interval in process. Also, the total measurement progress bar will show the remaining percentage of measurements to finish the long term measurements.\n"
"\n"
"\n"
"4.4 -> Can I change a parameter of the configuration during the measurements?\n"
"\n"
"No. This changes are only allowed during the calibration phase. This is to prevent the user to accidentally change the configured and tested configurations.\n"
"\n"
"\n"
"4.5 -> What can I see during the measurements?\n"
"\n"
"During this phase, the raw signal is shown for a longer period of time. Then the FFT is performed when the time interval is complete. This is to avoid overloading of the system during the long term measurements. A history of the average signals can be seen in the plot \"Average Signal\". Also the plot of \"Prediction\" will be loaded by demand, which will show after each time interval the correspoding result for the linear regression algorithm.\n"
"\n"
"\n"
"\n"
"-> 5. OTHERS\n"
"\n"
"5.1 -> How can the Da"
                        "ta be loaded ?\n"
"\n"
"You can load FFT data or the Raw data to be analyzed. Press the button \"Load Data\" and then select the desired option \"Raw Data\" or \"FFT Data\" to load the file. \n"
"\n"
"** Remember that raw data has the name form XXC1_XXC2_XXms_XXHz_XX.CS/.TXT and the FFT data has the name form XXC1_XXC2_XXms_XXHz_XX_FFT.txt.\n"
"\n"
"\n"
"5.2 -> How to save a graph to PDF?\n"
"\n"
"Click on \"Save Graphs\" and select the folder where the PDF files will be saved. One per each plot of Compensation and FFT profile.\n"
"\n"
"\n"
"5.3 -> How can I change the wavelength of the FFT plot?\n"
"\n"
"To change the wavelength in the side panel plot FFT Intensity, click the label of the wavelength number and select the desired one. This change will remain during all the calibration or measurements. This parameter can be changed at any time during the calibrations or the measurements.\n"
"\n"
"\n"
"\n"
"-> 6. SOFTWARE ISSUES ?\n"
"\n"
"\n"
"6.1 -> Why the software is not responding?\n"
"\n"
"It might be that"
                        " you are trying to load a non compatible file type, for example an empty file \".txt\" for loading data or configuration. Also, it may happens when the spectrometer is overloaded with the adjusted parameters. This problems are generally avoided, usually warnings are shown to the user when a file is not appropriate, or when the spectrometer is usually stoped because the load is too high.\n"
"\n"
"\n"
"6.2 -> Why the plots are disturbed sometimes after stopping the calibration?\n"
"\n"
"Sometimes it happens when the calibration is stopped and the spectrometer was busy measuring. This interruption is most of the times catched and fixed. If this happens, you could restart the calibration to re draw the plots or click in the option \"Clear All\", remember that this last will also remove any other loaded configuration.", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelPolHelp: public Ui_PanelPolHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_PANELHELP_H
