/*
 * Hemoxymetrie in non-hemolyzed human whole blood
 * Copyright (C) 2016-2017 Benjamin Redmer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* External includes */
#include <QApplication>
#include <QDialog>
#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include <QLineEdit>
#include <QList>
#include <QTimer>
#include <QDateTime>
#include <QElapsedTimer>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

/* Internal includes */
#include "application.h"
#include "messages.h"
#include "spectrometer.h"
#include "timer.h"
#include "pol_configureMeasurement.h"
#include "ui_pol_configureMeasurement.h"
#include "pol_externConf.h"
#include "pol_panelItem.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Constructor of 'configure Pol Measure' class
 * @param[in] parent Parent widget
 */
configurePolMeasure::configurePolMeasure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configurePolMeasure)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Create signal mapper for configuration window */
    signalMapperC = new QSignalMapper(this);

    /* Create the connection to extern software object */
    externSoftware = new Pol_ExternConf();

    /* Connect signal mapper action */
    connect(signalMapperC, SIGNAL(mapped(QWidget *)), this, SLOT(handleClickEvent(QWidget *)));

    /* Set window flags */
    this->setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    /* Connect buttons to signal mapper */
    connect(ui->pushButton_select, SIGNAL(clicked()), this, SLOT(selectPath()));

    /* Connect button to add impurities */
    connect(ui->pushButton_addImpurity, SIGNAL(clicked()), this, SLOT(addImpurities()));

    /* Spectrometer Settings */
    connect(ui->spinBox_BFreq, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_BNMeas, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_BNSpec, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_BNAve, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_intTime, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_startDelay, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_minW, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_maxW, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_timebetweenM, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));

    /* Solutions Concentrations */
    connect(ui->doubleSpinBox_MinGluc, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_MinImp1, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_MinImp2, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_MinImp3, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_MinImp4, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_MinImp5, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_MaxGluc, SIGNAL(valueChanged(double)), this, SLOT(updateStockValues()));
    connect(ui->doubleSpinBox_MaxImp1, SIGNAL(valueChanged(double)), this, SLOT(updateStockValues()));
    connect(ui->doubleSpinBox_MaxImp2, SIGNAL(valueChanged(double)), this, SLOT(updateStockValues()));
    connect(ui->doubleSpinBox_MaxImp3, SIGNAL(valueChanged(double)), this, SLOT(updateStockValues()));
    connect(ui->doubleSpinBox_MaxImp4, SIGNAL(valueChanged(double)), this, SLOT(updateStockValues()));
    connect(ui->doubleSpinBox_MaxImp5, SIGNAL(valueChanged(double)), this, SLOT(updateStockValues()));
    connect(ui->doubleSpinBox_StockGlucose, SIGNAL(editingFinished()), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_StockImp1, SIGNAL(editingFinished()), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_StockImp2, SIGNAL(editingFinished()), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_StockImp3, SIGNAL(editingFinished()), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_StockImp4, SIGNAL(editingFinished()), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_StockImp5, SIGNAL(editingFinished()), this, SLOT(updateConfigurationValues()));

    /* Repetitions */
    connect(ui->spinBox_Nrepet, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));

    /* Select the components */
    connect(ui->checkBox_Imp5, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_Imp4, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_Imp3, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_Imp2, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_Imp1, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_Glucose, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_saveFFT, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_saveRaw, SIGNAL(clicked()), signalMapperC, SLOT(map()));

    /* Normalize the counts? */
    connect(ui->checkBox_NormalizeCountsConfig, SIGNAL(clicked()), signalMapperC, SLOT(map()));

    /* Set manually mesurement intervals */
    connect(ui->checkBox_IntervalMode, SIGNAL(clicked()), signalMapperC, SLOT(map()));

    /* Pump Flow */
    connect(ui->spinBox_ShortBreak, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_LongBreak, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_AbsFlow, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_AbsVol, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_NSteps, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));

    /* Solutions Concentrations */
    signalMapperC->setMapping(ui->checkBox_Imp5, ui->checkBox_Imp5);
    signalMapperC->setMapping(ui->checkBox_Imp4, ui->checkBox_Imp4);
    signalMapperC->setMapping(ui->checkBox_Imp3, ui->checkBox_Imp3);
    signalMapperC->setMapping(ui->checkBox_Imp2, ui->checkBox_Imp2);
    signalMapperC->setMapping(ui->checkBox_Imp1, ui->checkBox_Imp1);
    signalMapperC->setMapping(ui->checkBox_Glucose, ui->checkBox_Glucose);
    signalMapperC->setMapping(ui->checkBox_NormalizeCountsConfig, ui->checkBox_NormalizeCountsConfig);
    signalMapperC->setMapping(ui->checkBox_IntervalMode, ui->checkBox_IntervalMode);
    signalMapperC->setMapping(ui->checkBox_saveFFT, ui->checkBox_saveFFT);
    signalMapperC->setMapping(ui->checkBox_saveRaw, ui->checkBox_saveRaw);

    /* Connect Button of configuration */
    connect(ui->pushButton_generate, SIGNAL(clicked()), this, SLOT(configurePolarimeter()));

    /* Connect Button of cancel */
    connect(ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(cancel()));

    /* Do you want to load a configuration? or not? */
    Conf_canceled = false;

    /* Not configuration loaded */
    configured = false;

    /* Start total measurement time in 0 */
    totalMtime = 0;

    /* Hide the time label, show it only when there is a delay */
    ui->label_timeLabel->hide();
    ui->timeEdit_timeLabel->hide();

    /* Initialize variables */
    ui->lineEdit_path->setText("Select a Path when Loading or Creating a Configuration File");

    /* Hide Solutions C3 to C6 at the beginning */
    hideAdditionalSubstances(true, false, false, false, false);
}

/**
 * @brief Select path for StoreToRAM files
 */
void configurePolMeasure::selectPath(void)
{
    /* Path variable */
    QString pathDataM = "";

    /* No directory chosen until now? */
    if (!ui->lineEdit_path->isEnabled())
    {
        /* Get path of configuration file */
        pathDataM = QFileDialog::getOpenFileName(this, "Configuration file", QDir::currentPath(), "Text files (*.csar)");
    }
    else
    {
        /* Get path of configuration file */
        pathDataM = QFileDialog::getOpenFileName(this, "Configuration file", pathDataM, "Text files (*.csar)");
    }

    /* Did the user select a new path? */
    if (pathDataM  != ui->lineEdit_path->text() && !pathDataM.isEmpty() && ui->lineEdit_path->text() != "Select a Path when Loading or Creating a Configuration Files")
    {
        /* If a new file was loaded, clear all the configuration */
        cleanAll();
    }

    /* Is there a path? */
    if(!pathDataM.isEmpty()){

        /* Get the path */
        pathDataMeasurements = QFileInfo(pathDataM);

        /* Get path to create the configuration file */
        externSoftware->pathForScripts = pathDataMeasurements.absoluteFilePath();

        /* Loading from file */
        loadingConfigurationFromFile = true;

        /* Load Configuration */
        loadConfiguration();
    }
}

/**
 * @brief Clean all the configuration if a different file was loaded.
 */
void configurePolMeasure::cleanAll(void)
{
    /* Clear lists */
    timePoint.clear();
    savingFilesNames.clear();

    /* Restart some values */
    externSoftware->ConfigurationFileGenerator->NrSpectra=1000;
    externSoftware->ConfigurationFileGenerator->IntegrationTime=8;
    externSoftware->ConfigurationFileGenerator->NrAverages=1;
    externSoftware->ConfigurationFileGenerator->Frequency =7;
    externSoftware->maxWavelength = 1100.23;
    externSoftware->minWavelength = 277.299;
    ui->lineEdit_path->setEnabled(false);
}

/**
 * @brief Called if a widget option was clicked,
 *        e.g. Integration time label.
 * @param widget Widget which has been clicked
 */
void configurePolMeasure::handleClickEvent(QWidget *widget)
{
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(widget);

    /* Check box of impurities */
    if(checkBox == ui->checkBox_Imp1 || checkBox == ui->checkBox_Imp2 || checkBox == ui->checkBox_Imp3 || checkBox == ui->checkBox_Imp4 || checkBox == ui->checkBox_Imp5){

        /* Show/Hide Impurities values */
        hideAdditionalSubstances((ui->checkBox_Imp1->isChecked() && ui->checkBox_Imp1->isVisible()), (ui->checkBox_Imp2->isChecked() && ui->checkBox_Imp2->isVisible()),
                                 (ui->checkBox_Imp3->isChecked() && ui->checkBox_Imp3->isVisible()), (ui->checkBox_Imp4->isChecked() && ui->checkBox_Imp4->isVisible()),
                                 (ui->checkBox_Imp5->isChecked() && ui->checkBox_Imp5->isVisible()));

        /* Set them to checked again */
        ui->checkBox_Imp1->setChecked(true);
        ui->checkBox_Imp2->setChecked(true);
        ui->checkBox_Imp3->setChecked(true);
        ui->checkBox_Imp4->setChecked(true);
        ui->checkBox_Imp5->setChecked(true);

        /* Enable button because at least one substance was removed */
        ui->pushButton_addImpurity->setEnabled(true);
    }

    /* Check the substances */
    if(checkBox == ui->checkBox_Glucose){

        /* Show/Hide Glucose values */
        ui->doubleSpinBox_StockGlucose->setVisible(ui->checkBox_Glucose->isChecked());
        ui->doubleSpinBox_MaxGluc->setVisible(ui->checkBox_Glucose->isChecked());
        ui->doubleSpinBox_MinGluc->setVisible(ui->checkBox_Glucose->isChecked());
        ui->doubleSpinBox_VolG->setVisible(ui->checkBox_Glucose->isChecked());
    }

    /* Number of substances */
    int NumberOfSubstances = ui->checkBox_Glucose->isChecked() + ui->checkBox_Imp1->isEnabled() + ui->checkBox_Imp2->isEnabled() + ui->checkBox_Imp3->isEnabled()
            + ui->checkBox_Imp4->isEnabled()+ ui->checkBox_Imp5->isEnabled();

    /* Adjust stock */
    if(NumberOfSubstances > 0){

        /* Adjust the Stock solutions or maximum concentration accordingly */
        ui->doubleSpinBox_StockGlucose->setValue(ui->doubleSpinBox_MaxGluc->value()*(NumberOfSubstances));
        ui->doubleSpinBox_StockImp1->setValue(ui->doubleSpinBox_MaxImp1->value()*(NumberOfSubstances));
        ui->doubleSpinBox_StockImp2->setValue(ui->doubleSpinBox_MaxImp2->value()*(NumberOfSubstances));
        ui->doubleSpinBox_StockImp3->setValue(ui->doubleSpinBox_MaxImp3->value()*(NumberOfSubstances));
        ui->doubleSpinBox_StockImp4->setValue(ui->doubleSpinBox_MaxImp4->value()*(NumberOfSubstances));
        ui->doubleSpinBox_StockImp5->setValue(ui->doubleSpinBox_MaxImp5->value()*(NumberOfSubstances));
    }

    /* Check the normalization of counts */
    if(checkBox == ui->checkBox_NormalizeCountsConfig){

        /* Is the normalization of counts checked? */
        externSoftware->ConfigurationFileGenerator->normalizedCounts = ui->checkBox_NormalizeCountsConfig->isChecked();
    }

    /* Check if the Interval Mode is activated */
    if(checkBox == ui->checkBox_IntervalMode){

        /* Is the Interval mode checked? */
        if(ui->checkBox_IntervalMode->isChecked()){

            /* Do you want to set this mode? */
            if (QMessageBox::Yes == QMessageBox::question(this, "Interval Mode", "Are you sure that you want to set the measurement time manually? \n \n "
                                                          "This mode might not be synchronized with the Syringe Pumps. Also the generation of Pump Files"
                                                          " will be enabled for just the maximum concentrations.",
                                                          QMessageBox::Yes | QMessageBox::No))
            {
                /* Show that this mode is active */
                ui->label_intervalMode->setText("Interval Mode is Active");
                ui->label_intervalMode->setStyleSheet("QLabel { color: red; }");

                /* Change labels colors and frames */
                ui->label_timebetweenM->setStyleSheet("QLabel { color: black; }");
                ui->label2_timebetweenM->setStyleSheet("QLabel { color: black; }");
                ui->doubleSpinBox_timebetweenM->setStyleSheet("QDoubleSpinBox { color: black; }");
                ui->doubleSpinBox_timebetweenM->setReadOnly(false);
                ui->doubleSpinBox_timebetweenM->setButtonSymbols(QDoubleSpinBox::UpDownArrows);
                ui->doubleSpinBox_timebetweenM->setFrame(true);

            }else{

                /* Deselect the option */
                ui->checkBox_IntervalMode->setChecked(false);
            }

        }else{

            /* Restart notification of interval mode active */
            ui->label_intervalMode->setText("");
            ui->label_timebetweenM->setStyleSheet("QLabel { color: rgb(0, 85, 0); }");
            ui->label2_timebetweenM->setStyleSheet("QLabel { color: rgb(0, 85, 0); }");
            ui->doubleSpinBox_timebetweenM->setStyleSheet("QDoubleSpinBox { color: rgb(0, 170, 0); }");
            ui->doubleSpinBox_timebetweenM->setReadOnly(true);
            ui->doubleSpinBox_timebetweenM->setButtonSymbols(QDoubleSpinBox::NoButtons);
            ui->doubleSpinBox_timebetweenM->setFrame(false);
        }

        /* Save that the Interval Mode is active now */
        externSoftware->ConfigurationFileGenerator->intervalMode = ui->checkBox_IntervalMode->isChecked();

        /* Disable changes on pumps scripts, not needed in this mode */
        ui->doubleSpinBox_MinGluc->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->doubleSpinBox_MinImp1->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->doubleSpinBox_MinImp2->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->doubleSpinBox_MinImp3->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->doubleSpinBox_MinImp4->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->doubleSpinBox_MinImp5->setEnabled(!ui->checkBox_IntervalMode->isChecked());

        /* Disable time breaks */
        ui->spinBox_ShortBreak->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->spinBox_LongBreak->setEnabled(!ui->checkBox_IntervalMode->isChecked());
    }

    /* Update all parameters */
    updateConfigurationValues();

    /* The user doesn't have any saving option selected for the measurement, are you sure that you don't want to save the data? */
    if(!ui->checkBox_saveFFT->isChecked() && !ui->checkBox_saveRaw->isChecked()){

        /* Show message for saving options */
        showWarning("Data might not be saved during the Measurement, FFT Data will be selected by default!", "");

        /* Select FFT data saving for default */
        ui->checkBox_saveFFT->setChecked(true);
    }
}

/**
 * @brief Configure polarimeter from user entries
 */
void configurePolMeasure::configurePolarimeter(void)
{
    /* If the user never pressed enter or similar */
    GetConfigurationData();

    /* Get path to save configuration file */
    QString pathDataM = QFileDialog::getSaveFileName(this, tr("Save Configuration File"), "spectrometer_skript", "Text files (*.csar)");

    /* Is there a path? */
    if(!pathDataM.isEmpty()){

        /* Get the path */
        pathDataMeasurements = QFileInfo(pathDataM);

        /* Get path to create the configuration file */
        externSoftware->pathForScripts = pathDataMeasurements.absoluteFilePath();

        /* Create the needed scripts for the measurements */
        externSoftware->pumpsPatternCalculator();

        /* Creating a configuration */
        loadingConfigurationFromFile = false;

        /* Load saved file */
        loadConfiguration();

        /* Save that a configuration file was loaded */
        configured = true;

        /* Finish the window */
        accept();
    }
}

/**
 * @brief Load configuration from file .csar
 */
void configurePolMeasure::loadConfiguration(void)
{
    /* Save rows in file */
    QStringList wordList;

    /* File Path */
    QFile file(pathDataMeasurements.absoluteFilePath());

    /* Open configuration file */
    if (!file.open(QIODevice::ReadOnly))
    {
        /* Show message */
        showCritical("Unable to open the configuration file!", "");
        return;
    }

    /* Save that a configuration file was loaded */
    configured = true;

    /* Loop through lines in file */
    while (!file.atEnd())
    {
        /* Get row in file */
        wordList.append(file.readLine().split(',').first());
    }

    /* Remove the first row since it only has a description of the file */
    wordList.removeAt(0);

    /* Close file */
    file.close();

    /* Clear lists */
    cleanAll();

    /* Check format of configuration file; we need at least 45 semicolons in this conf line */
    if (wordList[0].count(QLatin1Char(';')) != 45)
    {
        /* Show message */
        showWarning("Malformed configuration file. Please check the file version. It should contain 46 configuration values and 45 semicolons", "");
        configured = false;
        return;
    }

    /* Loading configuration from file? */
    getConfigurationFromFile(wordList.at(0));

    /* Remove the first row since it as the configuration data already obtained from the file */
    wordList.removeAt(0);

    /* Remove the first row since it as the configuration data already obtained from the file */
    wordList.removeAt(0);

    unsigned int i = 0;

    /* Loop through elements */
    for (i = 0; i < (unsigned int)wordList.length(); i++)
    {
        /* Divide by the semicolon ";" */
        QStringList list = wordList[i].split(';');

        /* Copy entries to the lists */
        timePoint.append(list[0].toInt());
        savingFilesNames.append(list[1]);

        /* Get the concentration vectors from the loaded file names */
        if(loadingConfigurationFromFile){

            /* Save the name */
            QString name = savingFilesNames.at(i);

            /* Get the glucose concentration */
            if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(0)){
                externSoftware->GlucoseConcentration.replace(i, name.left(name.indexOf("C1")).toDouble());
                name.remove(0, name.indexOf("C1")+3);
            }

            /* Get the impurity 1 concentration */
            if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(1)){
                externSoftware->Impurity1Concentration.replace(i, name.left(name.indexOf("C2")).toDouble());
                name.remove(0, name.indexOf("C2")+3);
            }

            /* Get the impurity 2 concentration */
            if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(2)){
                externSoftware->Impurity2Concentration.replace(i, name.left(name.indexOf("C3")).toDouble());
                name.remove(0, name.indexOf("C3")+3);
            }

            /* Get the impurity 3 concentration */
            if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(3)){
                externSoftware->Impurity3Concentration.replace(i, name.left(name.indexOf("C4")).toDouble());
                name.remove(0, name.indexOf("C4")+3);
            }

            /* Get the impurity 4 concentration */
            if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(4)){
                externSoftware->Impurity4Concentration.replace(i, name.left(name.indexOf("C5")).toDouble());
                name.remove(0, name.indexOf("C5")+3);
            }

            /* Get the impurity 5 concentration */
            if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(5)){
                externSoftware->Impurity5Concentration.replace(i, name.left(name.indexOf("C6")).toDouble());
                name.remove(0, name.indexOf("C6")+3);
            }
        }

        /* At least second entry? */
        if (i > 0)
        {
            /* Calculate duration of entry before current entry */
            double duration = externSoftware->ConfigurationFileGenerator->NrSpectra * externSoftware->ConfigurationFileGenerator->IntegrationTime
                    * externSoftware->ConfigurationFileGenerator->NrAverages;

            /* Check if there's a time overlap between last and current entry */
            if ((timePoint[i - 1] + duration) > timePoint[i])
            {
                /* Clear lists */
                cleanAll();

                /* Create message */
                QString message;
                message = QString("Error in configuration file! Time overlap between entries %1 and %2.").arg(QString::number(i - 1),
                                                                                                              QString::number(i));
                /* Show message */
                showCritical(message, "");
                return;
            }
        }
    }

    /* If the interval mode is active, then recalculate the total time */
    if(externSoftware->ConfigurationFileGenerator->intervalMode){

        /* Total time for the interval mode */
        totalMtime = (externSoftware->ConfigurationFileGenerator->NConcentrations+1) * (externSoftware->UserTimeInterval/1000);

    }else{
        /* How long last a measurement? */
        double Mduration = (externSoftware->ConfigurationFileGenerator->NrSpectra * externSoftware->ConfigurationFileGenerator->IntegrationTime
                            * externSoftware->ConfigurationFileGenerator->NrAverages);

        /* Save the total time */
        totalMtime = ((timePoint.at(timePoint.length()-1))/1000) + externSoftware->ConfigurationFileGenerator->PumpsCycle/1000 + Mduration/1000;
    }
    /* Copy path into line edit */
    ui->lineEdit_path->setText(pathDataMeasurements.absoluteFilePath());

    /* Enable directory field and 'start' button */
    ui->lineEdit_path->setEnabled(true);

    /* Run pumps software */
    if(openPumps){
        externSoftware->openPumpSoftware();
        openPumps = false;
    }

    /* Finish the window */
    accept();
}

/**
 * @brief Get the configuration data from file
 */
void configurePolMeasure::getConfigurationFromFile(QString data)
{
    /* Divide by the semicolon ";" */
    QStringList dataList = data.split(';');

    /* Get complete configuration data */
    externSoftware->ConfigurationFileGenerator->NConcentrations = dataList.at(0).toInt();
    externSoftware->ConfigurationFileGenerator->NrSpectra = dataList.at(1).toInt();
    externSoftware->ConfigurationFileGenerator->IntegrationTime = dataList.at(2).toDouble();
    externSoftware->ConfigurationFileGenerator->NrAverages = dataList.at(3).toInt();
    externSoftware->ConfigurationFileGenerator->Frequency = dataList.at(4).toInt();
    externSoftware->minWavelength = dataList.at(5).toDouble();
    externSoftware->maxWavelength = dataList.at(6).toDouble();

    /* If loading from file then get all the values, otherwise it's not necessary and save time */
    if(loadingConfigurationFromFile){

        /* Load information from file */
        externSoftware->ConfigurationFileGenerator->absoluteFlow = dataList.at(7).toDouble();
        externSoftware->ConfigurationFileGenerator->absVol = dataList.at(8).toInt();
        externSoftware->ConfigurationFileGenerator->NSteps = dataList.at(9).toInt();
        externSoftware->ConfigurationFileGenerator->shortBreak = dataList.at(10).toInt();
        externSoftware->ConfigurationFileGenerator->longBreak = dataList.at(11).toInt();
        externSoftware->ConfigurationFileGenerator->startDelay = dataList.at(12).toDouble();
        externSoftware->ConfigurationFileGenerator->activeSubstances.replace(0, dataList.at(13).toInt());
        externSoftware->ConfigurationFileGenerator->activeSubstances.replace(1, dataList.at(14).toInt());
        externSoftware->ConfigurationFileGenerator->activeSubstances.replace(2, dataList.at(15).toInt());
        externSoftware->ConfigurationFileGenerator->activeSubstances.replace(3, dataList.at(16).toInt());
        externSoftware->ConfigurationFileGenerator->activeSubstances.replace(4, dataList.at(17).toInt());
        externSoftware->ConfigurationFileGenerator->activeSubstances.replace(5, dataList.at(18).toInt());
        externSoftware->minConcentrations.replace(0, dataList.at(19).toDouble());
        externSoftware->maxConcentrations.replace(0, dataList.at(20).toDouble());
        externSoftware->stockSolutions.replace(0, dataList.at(21).toDouble());
        externSoftware->minConcentrations.replace(1, dataList.at(22).toDouble());
        externSoftware->maxConcentrations.replace(1, dataList.at(23).toDouble());
        externSoftware->stockSolutions.replace(1, dataList.at(24).toDouble());
        externSoftware->minConcentrations.replace(2, dataList.at(25).toDouble());
        externSoftware->maxConcentrations.replace(2, dataList.at(26).toDouble());
        externSoftware->stockSolutions.replace(2, dataList.at(27).toDouble());
        externSoftware->minConcentrations.replace(3, dataList.at(28).toDouble());
        externSoftware->maxConcentrations.replace(3, dataList.at(29).toDouble());
        externSoftware->stockSolutions.replace(3, dataList.at(30).toDouble());
        externSoftware->minConcentrations.replace(4, dataList.at(31).toDouble());
        externSoftware->maxConcentrations.replace(4, dataList.at(32).toDouble());
        externSoftware->stockSolutions.replace(4, dataList.at(33).toDouble());
        externSoftware->minConcentrations.replace(5, dataList.at(34).toDouble());
        externSoftware->maxConcentrations.replace(5, dataList.at(35).toDouble());
        externSoftware->stockSolutions.replace(5, dataList.at(36).toDouble());
        externSoftware->ConfigurationFileGenerator->repetition = dataList.at(37).toInt();
        externSoftware->ConfigurationFileGenerator->normalizedCounts = dataList.at(38).toInt();
        externSoftware->ConfigurationFileGenerator->intervalMode = dataList.at(39).toInt();
        externSoftware->UserTimeInterval = dataList.at(40).toDouble();
        externSoftware->ConfigurationFileGenerator->substancesNames.replace(0, dataList.at(41));
        externSoftware->ConfigurationFileGenerator->substancesNames.replace(1, dataList.at(42));
        externSoftware->ConfigurationFileGenerator->substancesNames.replace(2, dataList.at(43));
        externSoftware->ConfigurationFileGenerator->substancesNames.replace(3, dataList.at(44));
        externSoftware->ConfigurationFileGenerator->substancesNames.replace(4, dataList.at(45));

        /* Calculate some parameters according to the loaded information */
        externSoftware->ConfigurationFileGenerator->fillRefill = (((externSoftware->ConfigurationFileGenerator->absVol
                                                                    /externSoftware->ConfigurationFileGenerator->absoluteFlow)
                                                                   *60) / externSoftware->ConfigurationFileGenerator->NSteps)*1000;
        /* Count active substances */
        updateActiveSubstances();

        /* Resize vectors if the substances are active */
        if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(0)){
            externSoftware->GlucoseConcentration.resize(externSoftware->ConfigurationFileGenerator->NConcentrations * externSoftware->ConfigurationFileGenerator->repetition);
        }
        if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(1)){
            externSoftware->Impurity1Concentration.resize(externSoftware->ConfigurationFileGenerator->NConcentrations* externSoftware->ConfigurationFileGenerator->repetition);
        }
        if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(2)){
            externSoftware->Impurity2Concentration.resize(externSoftware->ConfigurationFileGenerator->NConcentrations* externSoftware->ConfigurationFileGenerator->repetition);
        }
        if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(3)){
            externSoftware->Impurity3Concentration.resize(externSoftware->ConfigurationFileGenerator->NConcentrations* externSoftware->ConfigurationFileGenerator->repetition);
        }
        if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(4)){
            externSoftware->Impurity4Concentration.resize(externSoftware->ConfigurationFileGenerator->NConcentrations* externSoftware->ConfigurationFileGenerator->repetition);
        }
        if(externSoftware->ConfigurationFileGenerator->activeSubstances.at(5)){
            externSoftware->Impurity5Concentration.resize(externSoftware->ConfigurationFileGenerator->NConcentrations* externSoftware->ConfigurationFileGenerator->repetition);
        }

        /* How long is a cycle? */
        externSoftware->ConfigurationFileGenerator->PumpsCycle = (2 * externSoftware->ConfigurationFileGenerator->fillRefill +
                                                                  4 * externSoftware->ConfigurationFileGenerator->shortBreak) *
                (externSoftware->ConfigurationFileGenerator->NSteps + (externSoftware->ConfigurationFileGenerator->NSteps-1)) +
                (2 * externSoftware->ConfigurationFileGenerator->fillRefill + 3 * externSoftware->ConfigurationFileGenerator->shortBreak +
                 externSoftware->ConfigurationFileGenerator->longBreak);
    }
}

/**
 * @brief Loading a configuration has been canceled
 */
void configurePolMeasure::cancel(void)
{
    /* The user aborted the load of a configuration, so don't adjust GUI */
    Conf_canceled = true;

    /* Close dialog */
    reject();
}

/**
 * @brief Get data from the form
 */
void configurePolMeasure::GetConfigurationData(void)
{
    /* Get the interval mode */
    externSoftware->ConfigurationFileGenerator->intervalMode = ui->checkBox_IntervalMode->isChecked();

    /* Get the interval mode time from the user from minutes to ms */
    externSoftware->UserTimeInterval = ui->doubleSpinBox_timebetweenM->value()*60000;

    /* Get the start delay from hours to seconds */
    externSoftware->ConfigurationFileGenerator->startDelay = ui->doubleSpinBox_startDelay->value()*3600;

    /* Get Integration Time in ms */
    externSoftware->ConfigurationFileGenerator->IntegrationTime = ui->doubleSpinBox_intTime->value();

    /* Get Frequency to Measure in Hz */
    externSoftware->ConfigurationFileGenerator->Frequency = ui->spinBox_BFreq->value();

    /* Get Number of Spectra */
    externSoftware->ConfigurationFileGenerator->NrSpectra = ui->spinBox_BNSpec->value();

    /* Get Number of Averages */
    externSoftware->ConfigurationFileGenerator->NrAverages = ui->spinBox_BNAve->value();

    /* Save the actual selected substances */
    externSoftware->ConfigurationFileGenerator->activeSubstances.replace(0,ui->checkBox_Glucose->isChecked());
    externSoftware->ConfigurationFileGenerator->activeSubstances.replace(1,ui->checkBox_Imp1->isEnabled());
    externSoftware->ConfigurationFileGenerator->activeSubstances.replace(2,ui->checkBox_Imp2->isEnabled());
    externSoftware->ConfigurationFileGenerator->activeSubstances.replace(3,ui->checkBox_Imp3->isEnabled());
    externSoftware->ConfigurationFileGenerator->activeSubstances.replace(4,ui->checkBox_Imp4->isEnabled());
    externSoftware->ConfigurationFileGenerator->activeSubstances.replace(5,ui->checkBox_Imp5->isEnabled());

    /* Required for the Pump Scripts */

    /* Get Number of Measurements */
    externSoftware->ConfigurationFileGenerator->NConcentrations = ui->spinBox_BNMeas->value();

    /* Get Number of Steps */
    externSoftware->ConfigurationFileGenerator->NSteps = ui->spinBox_NSteps->value();

    /* Get Number of Repetitions */
    /* Repetition plus 1, because 0 repetitions means 1 measurement */
    externSoftware->ConfigurationFileGenerator->repetition = ui->spinBox_Nrepet->value() + 1;

    /* Get absolute Flow */
    externSoftware->ConfigurationFileGenerator->absoluteFlow = ui->doubleSpinBox_AbsFlow->value();

    /* Is the idle active? */
    int idled = ui->checkBox->isChecked();
    externSoftware->ConfigurationFileGenerator->idle = idled;

    /* Get absolute Volume */
    externSoftware->ConfigurationFileGenerator->absVol = ui->spinBox_AbsVol->value();

    /* Get Refilling Times from seconds to ms */
    externSoftware->ConfigurationFileGenerator->fillRefill = (((externSoftware->ConfigurationFileGenerator->absVol/externSoftware->ConfigurationFileGenerator->absoluteFlow)*60)
                                                              / externSoftware->ConfigurationFileGenerator->NSteps)*1000;

    /* Get the Breaks from seconds to ms */
    externSoftware->ConfigurationFileGenerator->shortBreak = (ui->spinBox_ShortBreak->value())*1000;
    externSoftware->ConfigurationFileGenerator->longBreak = (ui->spinBox_LongBreak->value())*1000 +
            (externSoftware->ConfigurationFileGenerator->IntegrationTime * externSoftware->ConfigurationFileGenerator->NrSpectra *
             externSoftware->ConfigurationFileGenerator->NrAverages);

    /* Stock Solutions */
    externSoftware->stockSolutions.replace(0,ui->doubleSpinBox_StockGlucose->value());
    externSoftware->stockSolutions.replace(1,ui->doubleSpinBox_StockImp1->value());
    externSoftware->stockSolutions.replace(2,ui->doubleSpinBox_StockImp2->value());
    externSoftware->stockSolutions.replace(3,ui->doubleSpinBox_StockImp3->value());
    externSoftware->stockSolutions.replace(4,ui->doubleSpinBox_StockImp4->value());
    externSoftware->stockSolutions.replace(5,ui->doubleSpinBox_StockImp5->value());

    /* Minimum Concentrations */
    externSoftware->minConcentrations.replace(0,ui->doubleSpinBox_MinGluc->value());
    externSoftware->minConcentrations.replace(1,ui->doubleSpinBox_MinImp1->value());
    externSoftware->minConcentrations.replace(2,ui->doubleSpinBox_MinImp2->value());
    externSoftware->minConcentrations.replace(3,ui->doubleSpinBox_MinImp3->value());
    externSoftware->minConcentrations.replace(4,ui->doubleSpinBox_MinImp4->value());
    externSoftware->minConcentrations.replace(5,ui->doubleSpinBox_MinImp5->value());

    /* Maximum Concentrations */
    externSoftware->maxConcentrations.replace(0,ui->doubleSpinBox_MaxGluc->value());
    externSoftware->maxConcentrations.replace(1,ui->doubleSpinBox_MaxImp1->value());
    externSoftware->maxConcentrations.replace(2,ui->doubleSpinBox_MaxImp2->value());
    externSoftware->maxConcentrations.replace(3,ui->doubleSpinBox_MaxImp3->value());
    externSoftware->maxConcentrations.replace(4,ui->doubleSpinBox_MaxImp4->value());
    externSoftware->maxConcentrations.replace(5,ui->doubleSpinBox_MaxImp5->value());

    /* Save substances names, starting from Impurity 1 since glucose is always glucose */
    externSoftware->ConfigurationFileGenerator->substancesNames.replace(0, ui->lineEdit_Imp1->text());
    externSoftware->ConfigurationFileGenerator->substancesNames.replace(1, ui->lineEdit_Imp2->text());
    externSoftware->ConfigurationFileGenerator->substancesNames.replace(2, ui->lineEdit_Imp3->text());
    externSoftware->ConfigurationFileGenerator->substancesNames.replace(3, ui->lineEdit_Imp4->text());
    externSoftware->ConfigurationFileGenerator->substancesNames.replace(4, ui->lineEdit_Imp5->text());

    /* Update active substances number */
    updateActiveSubstances();

    /* Which Wavelength range will be used? */
    externSoftware->minWavelength = ui->doubleSpinBox_minW->value();
    externSoftware->maxWavelength = ui->doubleSpinBox_maxW->value();

    /* Get normalize counts */
    externSoftware->ConfigurationFileGenerator->normalizedCounts = ui->checkBox_NormalizeCountsConfig->isChecked();

    /* Very long Int Time? */
    if(externSoftware->ConfigurationFileGenerator->IntegrationTime > 200){

        /* Show warning */
        showWarning("Please consider that large integration times will lead to a larger measurement time!", "");
    }

    /* Too large number of spectra */
    if(externSoftware->ConfigurationFileGenerator->NrSpectra > 3000){

        /* Show warning */
        showWarning("Please consider that large number of spectra will lead to a larger measurement time!", "");
    }
}

/**
 * @brief Update the parameters when changes are done in the configuration
 */
void configurePolMeasure::updateConfigurationValues(void)
{
    /* Get Refilling Times in ms */
    int fillRefill = (((ui->spinBox_AbsVol->value()/ui->doubleSpinBox_AbsFlow->value())*60) / ui->spinBox_NSteps->value())*1000;

    /* Get the Breaks in ms */
    int ShortBreak = (ui->spinBox_ShortBreak->value())*1000;
    int LongBreak = (ui->spinBox_LongBreak->value())*1000 + (ui->doubleSpinBox_intTime->value()*ui->spinBox_BNSpec->value()*ui->spinBox_BNAve->value());

    /* Are there substances left? */
    if(!ui->checkBox_Glucose->isChecked() && !ui->checkBox_Imp1->isEnabled() && !ui->checkBox_Imp2->isEnabled() && !ui->checkBox_Imp3->isEnabled()
            && !ui->checkBox_Imp4->isEnabled() && !ui->checkBox_Imp5->isEnabled()){

        /* Show critical */
        showCritical("At least one kind of substance has to be selected!", "");

        /* Check glucose by default */
        ui->checkBox_Glucose->setChecked(true);

        /* Enable glucose by default */
        ui->doubleSpinBox_StockGlucose->setVisible(true);
        ui->doubleSpinBox_MaxGluc->setVisible(true);
        ui->doubleSpinBox_MinGluc->setVisible(true);
        ui->doubleSpinBox_VolG->setVisible(true);
    }

    /* Total absolute volume */
    double Vol = double(ui->spinBox_BNMeas->value())* double(ui->spinBox_AbsVol->value());

    /* Minimum volume per stock solution */
    double volumeG = ((ui->doubleSpinBox_MinGluc->value() + ui->doubleSpinBox_MaxGluc->value())/(2*ui->doubleSpinBox_StockGlucose->value()))* (Vol);
    double volumeI1 = ((ui->doubleSpinBox_MinImp1->value() + ui->doubleSpinBox_MaxImp1->value())/(2*ui->doubleSpinBox_StockImp1->value()))*(Vol);
    double volumeI2 = ((ui->doubleSpinBox_MinImp2->value() + ui->doubleSpinBox_MaxImp2->value())/(2*ui->doubleSpinBox_StockImp2->value()))*(Vol);
    double volumeI3 = ((ui->doubleSpinBox_MinImp3->value() + ui->doubleSpinBox_MaxImp3->value())/(2*ui->doubleSpinBox_StockImp3->value()))*(Vol);
    double volumeI4 = ((ui->doubleSpinBox_MinImp4->value() + ui->doubleSpinBox_MaxImp4->value())/(2*ui->doubleSpinBox_StockImp4->value()))*(Vol);
    double volumeI5 = ((ui->doubleSpinBox_MinImp5->value() + ui->doubleSpinBox_MaxImp5->value())/(2*ui->doubleSpinBox_StockImp5->value()))*(Vol);

    /* Estimate the cycle time */
    double cycleTime = (2 * fillRefill + 4*ShortBreak)
            *(ui->spinBox_NSteps->value() + (ui->spinBox_NSteps->value()-1))
            +  (2 * fillRefill + 3*ShortBreak + LongBreak);

    /* Estimate the measurement time */
    double measurementTime = cycleTime - (((LongBreak + (2*ui->doubleSpinBox_intTime->value()*ui->spinBox_BNSpec->value()*ui->spinBox_BNAve->value()))/3));

    /* What's the total time? */
    double totalMtimer = 0;

    /* Show the time */
    QStringList ConvertedTime;

    /* Was the time manually introduced? */
    if(!ui->checkBox_IntervalMode->isChecked()){

        /* Convert the time to minutes, hours or days */
        ConvertedTime = externSoftware->TimeConverter(measurementTime/1000);

        /* Display the Measurement Time preview */
        ui->doubleSpinBox_timebetweenM->setValue(ConvertedTime.at(0).toDouble());
        ui->label2_timebetweenM->setText(ConvertedTime.at(1));

        /* Estimate the total measurement time */
        totalMtimer = ((measurementTime + (cycleTime * ui->spinBox_BNMeas->value()))/1000)*(ui->spinBox_Nrepet->value() + 1);

        /* Convert the time to minutes, hours or days */
        ConvertedTime = externSoftware->TimeConverter(totalMtimer);

        /* Show the user how much is needed minimum for the substances */
        ui->doubleSpinBox_VolG->setValue(volumeG*(ui->spinBox_Nrepet->value()+1));
        ui->doubleSpinBox_VolI1->setValue(volumeI1*(ui->spinBox_Nrepet->value()+1));
        ui->doubleSpinBox_VolI2->setValue(volumeI2*(ui->spinBox_Nrepet->value()+1));
        ui->doubleSpinBox_VolI3->setValue(volumeI3*(ui->spinBox_Nrepet->value()+1));
        ui->doubleSpinBox_VolI4->setValue(volumeI4*(ui->spinBox_Nrepet->value()+1));
        ui->doubleSpinBox_VolI5->setValue(volumeI5*(ui->spinBox_Nrepet->value()+1));

    }else{

        /* Estimate the total measurement time */
        totalMtimer = ui->doubleSpinBox_timebetweenM->value()*ui->spinBox_BNMeas->value()*60*(ui->spinBox_Nrepet->value() + 1);

        /* Convert the time to minutes, hours or days */
        ConvertedTime = externSoftware->TimeConverter(totalMtimer);

        /* Show the user how much is needed minimum when there is just one concentration in the interval mode */
        ui->doubleSpinBox_VolG->setValue((volumeG/ui->spinBox_BNMeas->value())*(ui->spinBox_Nrepet->value()+1));
        ui->doubleSpinBox_VolI1->setValue((volumeI1/ui->spinBox_BNMeas->value())*(ui->spinBox_Nrepet->value()+1));
        ui->doubleSpinBox_VolI2->setValue((volumeI2/ui->spinBox_BNMeas->value())*(ui->spinBox_Nrepet->value()+1));
        ui->doubleSpinBox_VolI3->setValue((volumeI3/ui->spinBox_BNMeas->value())*(ui->spinBox_Nrepet->value()+1));
        ui->doubleSpinBox_VolI4->setValue((volumeI4/ui->spinBox_BNMeas->value())*(ui->spinBox_Nrepet->value()+1));
        ui->doubleSpinBox_VolI5->setValue((volumeI5/ui->spinBox_BNMeas->value())*(ui->spinBox_Nrepet->value()+1));
    }

    /* Display the Total Measurement Time */
    ui->doubleSpinBox_totalTime->setValue(ConvertedTime.at(0).toDouble());
    ui->label_BtimeInt2->setText(ConvertedTime.at(1));

    /* If there is a delay in the start, show when it's going to start then */
    if(ui->doubleSpinBox_startDelay->value() != 0){

        /* Show label when there is a delay */
        ui->label_timeLabel->show();
        ui->timeEdit_timeLabel->show();

        /* Get the actual time and add the delay time */
        startTime = QDateTime::currentDateTime().addSecs(ui->doubleSpinBox_startDelay->value()*3600+20);

        /* Print it in format of h:m:s AM/PM */
        ui->timeEdit_timeLabel->setText(startTime.toString("dddd, d MMMM yyyy, hh:mm ap"));

    }else{

        /* Hide the time label when there is not delay */
        ui->label_timeLabel->hide();
        ui->timeEdit_timeLabel->hide();
    }

    /* Show the end time of the measurements */
    QDateTime endTime = QDateTime::currentDateTime().addSecs(ui->doubleSpinBox_startDelay->value()*3600+ totalMtimer);

    /* Show the time when the measurements are finish */
    ui->lineEdit_EndTime->setText(endTime.toString("dddd, d MMMM yyyy, hh:mm ap"));

    /* Set wavelength range limits */
    ui->doubleSpinBox_minW->setMaximum(ui->doubleSpinBox_maxW->value());
    ui->doubleSpinBox_maxW->setMinimum(ui->doubleSpinBox_minW->value());

    /* Update range of number of averages */
    ui->spinBox_BNAve->setMaximum(floor((1000)/(4*ui->doubleSpinBox_intTime->value()*ui->spinBox_BFreq->value())));

    /* Get the step size */
    int NumberSpectraStep = NrSpectraSteps(ceil(ui->doubleSpinBox_intTime->value()*ui->spinBox_BFreq->value()));

    /* Use the correct number of spectra according to the frequency resolution */
    ui->spinBox_BNSpec->setSingleStep(NumberSpectraStep);
    ui->spinBox_BNSpec->setMinimum(NumberSpectraStep);

    /* Is the input of the user valid? */
    if(ui->spinBox_BNSpec->value() % NumberSpectraStep !=0){

        /* Show message */
        showWarning(QString("The number of spectra should be a multiple of %1!").arg(NumberSpectraStep), QString(""));

        /* Use old value */
        ui->spinBox_BNSpec->setValue(externSoftware->ConfigurationFileGenerator->NrSpectra);
    }

    /* Check intriduced stock solutions amounts */
    checkStockValues();

    /* Update approximate memory space */
    double space = 0;

    /* Which saving options is there? */
    if(ui->checkBox_saveFFT->isChecked() && ui->checkBox_saveRaw->isChecked()){

        /* Both files together can make all this space approximately */
        space = ui->spinBox_BNMeas->value()*(75 + 15000)*(ui->spinBox_Nrepet->value() + 1);

    }else if(!ui->checkBox_saveFFT->isChecked() && ui->checkBox_saveRaw->isChecked()){

        /* Only Raw data can have all this space approximately */
        space = ui->spinBox_BNMeas->value()*(15000)*(ui->spinBox_Nrepet->value() + 1);

    }else{

        /* Only FFT data can have all this space approximately */
        space = ui->spinBox_BNMeas->value()*(75)*(ui->spinBox_Nrepet->value() + 1);
    }

    /* Calculate the memory space */
    if(space < 1000){

        /* Show Kbytes */
        ui->doubleSpinBox_MSpace->setValue(space);
        ui->label_MSpace2->setText("KB");

    }else if(space >= 1000 && space < 1000000){

        /* Show Mega Bytes */
        ui->doubleSpinBox_MSpace->setValue(space/1000);
        ui->label_MSpace2->setText("MB");

    }else{

        /* Even Gigabytes? */
        ui->doubleSpinBox_MSpace->setValue(space/1000000);
        ui->label_MSpace2->setText("GB");
    }

    /* Update file name preview */
    filePreviewName();
}

/**
 * @brief Update the stock solutions as needed when changing the maximum concentration
 */
void configurePolMeasure::updateStockValues(void)
{
    /* Number of substances */
    int NumberOfSubstances = ui->checkBox_Glucose->isChecked() + ui->checkBox_Imp1->isEnabled() + ui->checkBox_Imp2->isEnabled() + ui->checkBox_Imp3->isEnabled()
            + ui->checkBox_Imp4->isEnabled()+ ui->checkBox_Imp5->isEnabled();

    /* Adjust stock solutions concentration accordingly */
    ui->doubleSpinBox_StockGlucose->setValue(ui->doubleSpinBox_MaxGluc->value()*(NumberOfSubstances));
    ui->doubleSpinBox_StockImp1->setValue(ui->doubleSpinBox_MaxImp1->value()*(NumberOfSubstances));
    ui->doubleSpinBox_StockImp2->setValue(ui->doubleSpinBox_MaxImp2->value()*(NumberOfSubstances));
    ui->doubleSpinBox_StockImp3->setValue(ui->doubleSpinBox_MaxImp3->value()*(NumberOfSubstances));
    ui->doubleSpinBox_StockImp4->setValue(ui->doubleSpinBox_MaxImp4->value()*(NumberOfSubstances));
    ui->doubleSpinBox_StockImp5->setValue(ui->doubleSpinBox_MaxImp5->value()*(NumberOfSubstances));

    /* Update all values */
    updateConfigurationValues();
}

/**
 * @brief Update the values in the form
 */
void configurePolMeasure::updateForm(void)
{
    /* Update form values when changes during the calibration */
    ui->spinBox_AbsVol->setValue(externSoftware->ConfigurationFileGenerator->absVol);
    ui->spinBox_BNMeas->setValue(externSoftware->ConfigurationFileGenerator->NConcentrations);
    ui->spinBox_NSteps->setValue(externSoftware->ConfigurationFileGenerator->NSteps);
    ui->spinBox_ShortBreak->setValue(externSoftware->ConfigurationFileGenerator->shortBreak/1000);
    ui->doubleSpinBox_AbsFlow->setValue(externSoftware->ConfigurationFileGenerator->absoluteFlow);
    ui->doubleSpinBox_startDelay->setValue(externSoftware->ConfigurationFileGenerator->startDelay/3600);
    ui->spinBox_LongBreak->setValue((externSoftware->ConfigurationFileGenerator->longBreak -
                                     (externSoftware->ConfigurationFileGenerator->IntegrationTime*externSoftware->ConfigurationFileGenerator->NrSpectra*
                                      externSoftware->ConfigurationFileGenerator->NrAverages))/1000);

    /* Update Substances status, which ones should be shown and what were their values? */
    ui->checkBox_Glucose->setChecked(externSoftware->ConfigurationFileGenerator->activeSubstances.at(0));
    ui->doubleSpinBox_MinGluc->setValue(externSoftware->minConcentrations.at(0));
    ui->doubleSpinBox_MinImp1->setValue(externSoftware->minConcentrations.at(1));
    ui->doubleSpinBox_MinImp2->setValue(externSoftware->minConcentrations.at(2));
    ui->doubleSpinBox_MinImp3->setValue(externSoftware->minConcentrations.at(3));
    ui->doubleSpinBox_MinImp4->setValue(externSoftware->minConcentrations.at(4));
    ui->doubleSpinBox_MinImp5->setValue(externSoftware->minConcentrations.at(5));
    ui->doubleSpinBox_MaxGluc->setValue(externSoftware->maxConcentrations.at(0));
    ui->doubleSpinBox_MaxImp1->setValue(externSoftware->maxConcentrations.at(1));
    ui->doubleSpinBox_MaxImp2->setValue(externSoftware->maxConcentrations.at(2));
    ui->doubleSpinBox_MaxImp3->setValue(externSoftware->maxConcentrations.at(3));
    ui->doubleSpinBox_MaxImp4->setValue(externSoftware->maxConcentrations.at(4));
    ui->doubleSpinBox_MaxImp5->setValue(externSoftware->maxConcentrations.at(5));
    ui->doubleSpinBox_StockGlucose->setValue(externSoftware->stockSolutions.at(0));
    ui->doubleSpinBox_StockImp1->setValue(externSoftware->stockSolutions.at(1));
    ui->doubleSpinBox_StockImp2->setValue(externSoftware->stockSolutions.at(2));
    ui->doubleSpinBox_StockImp3->setValue(externSoftware->stockSolutions.at(3));
    ui->doubleSpinBox_StockImp4->setValue(externSoftware->stockSolutions.at(4));
    ui->doubleSpinBox_StockImp5->setValue(externSoftware->stockSolutions.at(5));
    ui->lineEdit_Imp1->setText(externSoftware->ConfigurationFileGenerator->substancesNames.at(0));
    ui->lineEdit_Imp2->setText(externSoftware->ConfigurationFileGenerator->substancesNames.at(1));
    ui->lineEdit_Imp3->setText(externSoftware->ConfigurationFileGenerator->substancesNames.at(2));
    ui->lineEdit_Imp4->setText(externSoftware->ConfigurationFileGenerator->substancesNames.at(3));
    ui->lineEdit_Imp5->setText(externSoftware->ConfigurationFileGenerator->substancesNames.at(4));

    /* Repetition minus 1, because 1 measurement means 0 repetitions */
    ui->spinBox_Nrepet->setValue(externSoftware->ConfigurationFileGenerator->repetition - 1);

    /* Update normalized counts */
    ui->checkBox_NormalizeCountsConfig->setChecked(externSoftware->ConfigurationFileGenerator->normalizedCounts);

    /* Update the interval mode */
    ui->checkBox_IntervalMode->setChecked(externSoftware->ConfigurationFileGenerator->intervalMode);

    /* Update user time interval */
    ui->doubleSpinBox_timebetweenM->setValue(externSoftware->UserTimeInterval/(60*1000));

    /* Is the Interval Mode checked? Then the available options change */
    if(ui->checkBox_IntervalMode->isChecked()){

        /* Show that this mode is active */
        ui->label_intervalMode->setText("Interval Mode is Active");
        ui->label_intervalMode->setStyleSheet("QLabel { color: red; }");

        /* Change labels colors? */
        ui->label_timebetweenM->setStyleSheet("QLabel { color: black; }");
        ui->label2_timebetweenM->setStyleSheet("QLabel { color: black; }");
        ui->doubleSpinBox_timebetweenM->setStyleSheet("QDoubleSpinBox { color: black; }");
        ui->doubleSpinBox_timebetweenM->setReadOnly(false);
        ui->doubleSpinBox_timebetweenM->setButtonSymbols(QDoubleSpinBox::UpDownArrows);
        ui->doubleSpinBox_timebetweenM->setFrame(true);

        /* Disable changes on pumps scripts */
        ui->doubleSpinBox_MinGluc->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->doubleSpinBox_MinImp1->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->doubleSpinBox_MinImp2->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->doubleSpinBox_MinImp3->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->doubleSpinBox_MinImp4->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->doubleSpinBox_MinImp5->setEnabled(!ui->checkBox_IntervalMode->isChecked());

        /* Disable breaks */
        ui->spinBox_ShortBreak->setEnabled(!ui->checkBox_IntervalMode->isChecked());
        ui->spinBox_LongBreak->setEnabled(!ui->checkBox_IntervalMode->isChecked());
    }

    /* Show/Hide Impurities values if they were shown */
    hideAdditionalSubstances(externSoftware->ConfigurationFileGenerator->activeSubstances.at(1), externSoftware->ConfigurationFileGenerator->activeSubstances.at(2),
                             externSoftware->ConfigurationFileGenerator->activeSubstances.at(3), externSoftware->ConfigurationFileGenerator->activeSubstances.at(4),
                             externSoftware->ConfigurationFileGenerator->activeSubstances.at(5));

    /* Show/Hide Glucose values */
    ui->doubleSpinBox_StockGlucose->setVisible(ui->checkBox_Glucose->isChecked());
    ui->doubleSpinBox_MaxGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->doubleSpinBox_MinGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->doubleSpinBox_VolG->setVisible(ui->checkBox_Glucose->isChecked());

    /* Update calculable parameters */
    updateConfigurationValues();
}

/**
 * @brief Calculates the correct values for the number of spectra according to the frequency resolution
 * @param[in] Intervals for the correct number of spectra
 */
int configurePolMeasure::NrSpectraSteps(int Fint){

    /* Use the frequency and integration time to calculate the appropriate position in the FFT vector */

    /* Find multiples of 2 and 5 */
    int two=1, five = 1;

    /* Find multiples */
    while(true){

        /* Multiple of 2? */
        if(Fint % 2 == 0 && two < 4){
            two = two * 2;
            Fint = Fint/2;
        }
        /* Multiple of 5? */
        else if(Fint % 5 == 0 && five < 125){
            five = five * 5;
            Fint = Fint/5;
        }

        /* None? */
        else{ break;}
    }

    /* Return the interval of change for the possible number of spectra values */
    return 500/(two*five);
}

/**
 * @brief Initialize the configuration according to the new spectrometer settings
 * @param[in] Spectrometer settings Item
 */
void configurePolMeasure::InitializeForm(PanelItem_Pol* PolarimetrySpectrometer){

    /* Set some values in the configuration form */
    ui->doubleSpinBox_intTime->setValue(PolarimetrySpectrometer->getIntegrationTime());
    ui->spinBox_BNAve->setValue(PolarimetrySpectrometer->getNumberOfAverages());
    ui->spinBox_BNAve->setMaximum(floor((1000)/(4*PolarimetrySpectrometer->getIntegrationTime()*PolarimetrySpectrometer->getFrequency())));
    ui->spinBox_BFreq->setValue(PolarimetrySpectrometer->getFrequency());
    ui->spinBox_BNSpec->setValue(PolarimetrySpectrometer->getNumberOfSpectra());

    /* Select the correct number of spectra according to the frequency resolution */
    ui->spinBox_BNSpec->setSingleStep(NrSpectraSteps(PolarimetrySpectrometer->getIntegrationTime()*PolarimetrySpectrometer->getFrequency()));
    ui->spinBox_BNSpec->setMinimum(NrSpectraSteps(PolarimetrySpectrometer->getIntegrationTime()*PolarimetrySpectrometer->getFrequency()));
    ui->doubleSpinBox_minW->setValue(PolarimetrySpectrometer->getMinimumWavelength());
    ui->doubleSpinBox_maxW->setValue(PolarimetrySpectrometer->getMaximumWavelength());

    /* Keep loaded and saved values despite canceled changes: alloes edition of previously loaded configuration */
    if(configured){

        /* Update values in the configuration form */
        updateForm();
    }

    /* Did the user cancel the loading of a configuration? */
    Conf_canceled = false;
}

/**
 * @brief Add more impurities
 */
void configurePolMeasure::addImpurities(void){

    /* Flag */
    bool flag = false;

    /* Is the impurity 2 added? */
    if(!ui->checkBox_Imp1->isVisible()){

        /* Show the substance */
        hideAdditionalSubstances(!ui->checkBox_Imp1->isVisible(), ui->checkBox_Imp2->isVisible(), ui->checkBox_Imp3->isVisible(),
                                 ui->checkBox_Imp4->isVisible(), ui->checkBox_Imp5->isVisible());
        flag = true;
    }

    /* Is the impurity 2 added? */
    if(ui->checkBox_Imp1->isVisible() && !ui->checkBox_Imp2->isVisible() && !flag){

        /* Show the substance */
        hideAdditionalSubstances(ui->checkBox_Imp1->isVisible(),!ui->checkBox_Imp2->isVisible(), ui->checkBox_Imp3->isVisible(),
                                 ui->checkBox_Imp4->isVisible(), ui->checkBox_Imp5->isVisible());
        flag = true;
    }

    /* Is the impurity 3 added? */
    if(ui->checkBox_Imp2->isVisible() && !ui->checkBox_Imp3->isVisible() && !flag){

        /* Show the substance */
        hideAdditionalSubstances(ui->checkBox_Imp1->isVisible(),ui->checkBox_Imp2->isVisible(), !ui->checkBox_Imp3->isVisible(),
                                 ui->checkBox_Imp4->isVisible(), ui->checkBox_Imp5->isVisible());
        flag = true;
    }

    /* Is the impurity 4 added? */
    if(ui->checkBox_Imp2->isVisible() && ui->checkBox_Imp3->isVisible() && !ui->checkBox_Imp4->isVisible() && !flag){

        /* Show the substance */
        hideAdditionalSubstances(ui->checkBox_Imp1->isVisible(),ui->checkBox_Imp2->isVisible(), ui->checkBox_Imp3->isVisible(),
                                 !ui->checkBox_Imp4->isVisible(), ui->checkBox_Imp5->isVisible());
        flag = true;
    }

    /* Is the impurity 5 added? */
    if(ui->checkBox_Imp2->isVisible() && ui->checkBox_Imp3->isVisible() && ui->checkBox_Imp4->isVisible() && !ui->checkBox_Imp5->isVisible() && !flag){

        /* Show the substance */
        hideAdditionalSubstances(ui->checkBox_Imp1->isVisible(),ui->checkBox_Imp2->isVisible(), ui->checkBox_Imp3->isVisible(),
                                 ui->checkBox_Imp4->isVisible(), !ui->checkBox_Imp5->isVisible());
        flag = true;
    }

    /* All impurities are shown */
    if(ui->checkBox_Imp1->isVisible() && ui->checkBox_Imp2->isVisible() && ui->checkBox_Imp3->isVisible() && ui->checkBox_Imp4->isVisible() &&
            ui->checkBox_Imp5->isVisible()){

        /* user can't add more impurities */
        ui->pushButton_addImpurity->setEnabled(false);
    }

    /* Update stock solutions */
    updateStockValues();

    /* Update all parameters */
    updateConfigurationValues();
}

/**
 * @brief Hide/Show impurities
 */
void configurePolMeasure::hideAdditionalSubstances(bool status1, bool status2, bool status3, bool status4, bool status5){

    /* Hide 1 */
    ui->checkBox_Imp1->setVisible(status1);
    ui->checkBox_Imp1->setEnabled(status1);
    ui->lineEdit_Imp1->setVisible(status1);
    ui->doubleSpinBox_StockImp1->setVisible(status1);
    ui->doubleSpinBox_MaxImp1->setVisible(status1);
    ui->doubleSpinBox_MinImp1->setVisible(status1);
    ui->doubleSpinBox_VolI1->setVisible(status1);

    /* Hide 2 */
    ui->checkBox_Imp2->setVisible(status2);
    ui->checkBox_Imp2->setEnabled(status2);
    ui->lineEdit_Imp2->setVisible(status2);
    ui->doubleSpinBox_StockImp2->setVisible(status2);
    ui->doubleSpinBox_MaxImp2->setVisible(status2);
    ui->doubleSpinBox_MinImp2->setVisible(status2);
    ui->doubleSpinBox_VolI2->setVisible(status2);

    /* Hide 3 */
    ui->checkBox_Imp3->setVisible(status3);
    ui->checkBox_Imp3->setEnabled(status3);
    ui->lineEdit_Imp3->setVisible(status3);
    ui->doubleSpinBox_StockImp3->setVisible(status3);
    ui->doubleSpinBox_MaxImp3->setVisible(status3);
    ui->doubleSpinBox_MinImp3->setVisible(status3);
    ui->doubleSpinBox_VolI3->setVisible(status3);

    /* Hide 4 */
    ui->checkBox_Imp4->setVisible(status4);
    ui->checkBox_Imp4->setEnabled(status4);
    ui->lineEdit_Imp4->setVisible(status4);
    ui->doubleSpinBox_StockImp4->setVisible(status4);
    ui->doubleSpinBox_MaxImp4->setVisible(status4);
    ui->doubleSpinBox_MinImp4->setVisible(status4);
    ui->doubleSpinBox_VolI4->setVisible(status4);

    /* Hide 5 */
    ui->checkBox_Imp5->setVisible(status5);
    ui->checkBox_Imp5->setEnabled(status5);
    ui->lineEdit_Imp5->setVisible(status5);
    ui->doubleSpinBox_StockImp5->setVisible(status5);
    ui->doubleSpinBox_MaxImp5->setVisible(status5);
    ui->doubleSpinBox_MinImp5->setVisible(status5);
    ui->doubleSpinBox_VolI5->setVisible(status5);
}

/**
 * @brief Return the file name preview according to the added substances
 */
void configurePolMeasure::filePreviewName(void){

    /* File preview name */
    QString C = "";

    /* Is glucose active? */
    if(ui->checkBox_Glucose->isChecked()){

        /* If glucose is active, add to the name C1 */
        C.append(QString::number(ui->doubleSpinBox_MaxGluc->value()) + "C1");
    }

    /* Is glucose and one of the other two substacnes active? */
    if(ui->checkBox_Glucose->isChecked() && ((ui->checkBox_Imp1->isEnabled()) || ui->checkBox_Imp2->isEnabled() || ui->checkBox_Imp3->isEnabled()
                                             || ui->checkBox_Imp4->isEnabled() || ui->checkBox_Imp5->isEnabled())){

        /* Add the separator to the file name */
        C.append("_");
    }

    /* Is impurity 1 active? */
    if(ui->checkBox_Imp1->isEnabled()){

        /* If Impurity 1 is active, add to the name C2 */
        C.append(QString::number(ui->doubleSpinBox_MaxImp1->value()) + "C2");
    }

    /* If there is also a third substance, add the separator */
    if(ui->checkBox_Imp1->isEnabled() && (ui->checkBox_Imp2->isEnabled() || ui->checkBox_Imp3->isEnabled() || ui->checkBox_Imp4->isEnabled()
                                          || ui->checkBox_Imp5->isEnabled())){
        C.append("_");
    }

    /* Is impurity 2 active? */
    if(ui->checkBox_Imp2->isEnabled()){

        /* If Impurity 2 is active, add to the name C3 */
        C.append(QString::number(ui->doubleSpinBox_MaxImp2->value()) + "C3");
    }

    /* If there is also a fourth substance, add the separator */
    if(ui->checkBox_Imp2->isEnabled() && (ui->checkBox_Imp3->isEnabled() || ui->checkBox_Imp4->isEnabled() || ui->checkBox_Imp5->isEnabled())){
        C.append("_");
    }

    /* Is impurity 3 active? */
    if(ui->checkBox_Imp3->isEnabled()){

        /* If Impurity 3 is active, add to the name C4 */
        C.append(QString::number(ui->doubleSpinBox_MaxImp3->value()) + "C4");
    }

    /* If there is also a fifth substance, add the separator */
    if(ui->checkBox_Imp3->isEnabled() && (ui->checkBox_Imp4->isEnabled() || ui->checkBox_Imp5->isEnabled())){
        C.append("_");
    }

    /* Is impurity 4 active? */
    if(ui->checkBox_Imp4->isEnabled()){

        /* If Impurity 4 is active, add to the name C5 */
        C.append(QString::number(ui->doubleSpinBox_MaxImp4->value()) + "C5");
    }

    /* If there is also a sixt substance, add the separator */
    if(ui->checkBox_Imp4->isEnabled() && ui->checkBox_Imp5->isEnabled()){
        C.append("_");
    }

    /* Is impurity 5 active? */
    if(ui->checkBox_Imp5->isEnabled()){

        /* If Impurity 5 is active, add to the name C6 */
        C.append(QString::number(ui->doubleSpinBox_MaxImp5->value()) + "C6");
    }

    /* Are there repetitions? */
    if(ui->spinBox_Nrepet->value() > 0){

        /* Complete the file name preview */
        ui->lineEdit_BFileNamePrev->setText(C + "_" + QString::number(ui->doubleSpinBox_intTime->value()) + "ms_"
                                            + QString::number(ui->spinBox_BFreq->value()) + "Hz_1_R1");
    }
    else{

        /* Complete the file name preview */
        ui->lineEdit_BFileNamePrev->setText(C + "_" + QString::number(ui->doubleSpinBox_intTime->value()) + "ms_"
                                            + QString::number(ui->spinBox_BFreq->value()) + "Hz_1");
    }
}

/**
 * @brief Check if the introduced values of Stock solutions is correct.
 */
void configurePolMeasure::checkStockValues(void){

    /* Number of substances */
    int NumberOfSubstances = ui->checkBox_Glucose->isChecked() + ui->checkBox_Imp1->isEnabled() + ui->checkBox_Imp2->isEnabled() + ui->checkBox_Imp3->isEnabled()
            + ui->checkBox_Imp4->isEnabled()+ ui->checkBox_Imp5->isEnabled();

    /* Show critical message if the concentration of the stock is inappropriate */
    if(ui->doubleSpinBox_StockGlucose->value() < ui->doubleSpinBox_MaxGluc->value()*(NumberOfSubstances) && ui->checkBox_Glucose->isChecked()){

        /* Set back default value */
        ui->doubleSpinBox_StockGlucose->setValue(ui->doubleSpinBox_MaxGluc->value()*(NumberOfSubstances));

        QString message = "The stock of Glucose should have a minimum concentration of "
                + QString::number(ui->doubleSpinBox_MaxGluc->value()*(NumberOfSubstances)) + " mg/dl";
        showCritical(message, "");
    }

    /* Show critical message if the concentration of the stock is inappropriate */
    if(ui->doubleSpinBox_StockImp1->value() <ui->doubleSpinBox_MaxImp1->value()*(NumberOfSubstances) && ui->checkBox_Imp1->isEnabled()){

        /* Set back default value */
        ui->doubleSpinBox_StockImp1->setValue(ui->doubleSpinBox_MaxImp1->value()*(NumberOfSubstances));

        QString message = "The stock of " + ui->lineEdit_Imp1->text() + " should have a minimum concentration of "
                + QString::number(ui->doubleSpinBox_MaxImp1->value()*(NumberOfSubstances)) + " mg/dl";
        showCritical(message, "");
    }

    /* Show critical message if the concentration of the stock is inappropriate */
    if(ui->doubleSpinBox_StockImp2->value() < ui->doubleSpinBox_MaxImp2->value()*(NumberOfSubstances) && ui->checkBox_Imp2->isEnabled()){

        /* Set back default value */
        ui->doubleSpinBox_StockImp2->setValue(ui->doubleSpinBox_MaxImp2->value()*(NumberOfSubstances));

        QString message = "The stock of " + ui->lineEdit_Imp2->text() + " should have a minimum concentration of "
                + QString::number(ui->doubleSpinBox_MaxImp2->value()*(NumberOfSubstances)) + " mg/dl";
        showCritical(message, "");
    }

    /* Show critical message if the concentration of the stock is inappropriate */
    if(ui->doubleSpinBox_StockImp3->value() < ui->doubleSpinBox_MaxImp3->value()*(NumberOfSubstances) && ui->checkBox_Imp3->isEnabled()){

        /* Set back default value */
        ui->doubleSpinBox_StockImp3->setValue(ui->doubleSpinBox_MaxImp3->value()*(NumberOfSubstances));

        QString message = "The stock of " + ui->lineEdit_Imp3->text() + " should have a minimum concentration of "
                + QString::number(ui->doubleSpinBox_MaxImp3->value()*(NumberOfSubstances)) + " mg/dl";
        showCritical(message, "");
    }

    /* Show critical message if the concentration of the stock is inappropriate */
    if(ui->doubleSpinBox_StockImp4->value() < ui->doubleSpinBox_MaxImp4->value()*(NumberOfSubstances) && ui->checkBox_Imp4->isEnabled()){

        /* Set back default value */
        ui->doubleSpinBox_StockImp4->setValue(ui->doubleSpinBox_MaxImp4->value()*(NumberOfSubstances));

        QString message = "The stock of " + ui->lineEdit_Imp4->text() + " should have a minimum concentration of "
                + QString::number(ui->doubleSpinBox_MaxImp4->value()*(NumberOfSubstances)) + " mg/dl";
        showCritical(message, "");
    }

    /* Show critical message if the concentration of the stock is inappropriate */
    if(ui->doubleSpinBox_StockImp5->value() < ui->doubleSpinBox_MaxImp5->value()*(NumberOfSubstances) && ui->checkBox_Imp5->isEnabled()){

        /* Set back default value */
        ui->doubleSpinBox_StockImp5->setValue(ui->doubleSpinBox_MaxImp5->value()*(NumberOfSubstances));

        QString message = "The stock of " + ui->lineEdit_Imp5->text() + " should have a minimum concentration of "
                + QString::number(ui->doubleSpinBox_MaxImp5->value()*(NumberOfSubstances)) + " mg/dl";
        showCritical(message, "");
    }
}

/**
 * @brief Update how many substances are there.
 */
void configurePolMeasure::updateActiveSubstances(void){

    /* Count active substances */
    int activeSubs = 0;

    /* Active substances? */
    for(int g = 0; g < externSoftware->ConfigurationFileGenerator->activeSubstances.length(); g++){

        /* Sum the active substances */
        activeSubs = activeSubs + externSoftware->ConfigurationFileGenerator->activeSubstances.at(g);
    }

    /* Get the active substances */
    externSoftware->ConfigurationFileGenerator->NumberOfSubstances = activeSubs;
}

/**
 * @brief Destructor of 'configurePolMeasure' class
 */
configurePolMeasure::~configurePolMeasure(void)
{
    delete ui;

    delete externSoftware;
    externSoftware = nullptr;

}
