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

    /* Connect configuration edition */

    /* Spectrometer Settings */
    connect(ui->spinBox_BFreq, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_BNMeas, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_BNSpec, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_BNAve, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_intTime, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_startDelay, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_minW, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_maxW, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));

    /* Solutions Concentrations */
    connect(ui->doubleSpinBox_MinGluc, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_MinImp1, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_MinImp2, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_MaxGluc, SIGNAL(valueChanged(double)), this, SLOT(updateStockValues()));
    connect(ui->doubleSpinBox_MaxImp1, SIGNAL(valueChanged(double)), this, SLOT(updateStockValues()));
    connect(ui->doubleSpinBox_MaxImp2, SIGNAL(valueChanged(double)), this, SLOT(updateStockValues()));
    connect(ui->doubleSpinBox_StockGlucose, SIGNAL(editingFinished()), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_StockImp1, SIGNAL(editingFinished()), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_StockImp2, SIGNAL(editingFinished()), this, SLOT(updateConfigurationValues()));

    /* Repetitions */
    connect(ui->spinBox_Nrepet, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));

    /* Select the components */
    connect(ui->checkBox_Imp2, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_Imp1, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_Glucose, SIGNAL(clicked()), signalMapperC, SLOT(map()));

    /* Pump Flow */
    connect(ui->spinBox_ShortBreak, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_LongBreak, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->doubleSpinBox_AbsFlow, SIGNAL(valueChanged(double)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_AbsVol, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));
    connect(ui->spinBox_NSteps, SIGNAL(valueChanged(int)), this, SLOT(updateConfigurationValues()));

    /* Solutions Concentrations */
    signalMapperC->setMapping(ui->checkBox_Imp2, ui->checkBox_Imp2);
    signalMapperC->setMapping(ui->checkBox_Imp1, ui->checkBox_Imp1);
    signalMapperC->setMapping(ui->checkBox_Glucose, ui->checkBox_Glucose);

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

    /* Hide Solution 2 at the beginning */
    ui->doubleSpinBox_StockImp2->setVisible(false);
    ui->label_StockImp2->setVisible(false);
    ui->label_StockImp2_2->setVisible(false);
    ui->doubleSpinBox_MaxImp2->setVisible(false);
    ui->label_MaxImp2->setVisible(false);
    ui->label_MaxImp2_2->setVisible(false);
    ui->doubleSpinBox_MinImp2->setVisible(false);
    ui->label_MinImp2->setVisible(false);
    ui->label_MinImp2_2->setVisible(false);
    ui->label_VolI2->setVisible(false);
    ui->label_VolI22->setVisible(false);
    ui->lineEdit_VolI2->setVisible(false);

    /* Hide the time label, show it only when there is a delay */
    ui->label_timeLabel->hide();
    ui->timeEdit_timeLabel->hide();

    /* Initialize variables */
    pathOfData = "";
    ui->lineEdit_path->setText("Select a Path when Loading or Creating a Configuration File");

}

/**
 * @brief Select path for StoreToRAM files
 */
void configurePolMeasure::selectPath(void)
{
    QString pathDataM = "";

    /* No directory chosen until now? */
    if (!ui->lineEdit_path->isEnabled())
    {
        /* Get path of configuration file */
        pathDataM = QFileDialog::getOpenFileName(this, "Configuration file", QDir::currentPath(), "Text files (*.txt)");

    }
    else
    {
        /* Get path of configuration file */
        pathDataM = QFileDialog::getOpenFileName(this, "Configuration file", pathDataM, "Text files (*.txt)");
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
    externSoftware->ConfigurationFileGenerator->NrSpectra=0;
    externSoftware->ConfigurationFileGenerator->IntegrationTime=0;
    externSoftware->ConfigurationFileGenerator->NrAverages=0;
    externSoftware->ConfigurationFileGenerator->Frequency =0;
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

    /* Number of substances */
    int NumberOfSubstances = ui->checkBox_Glucose->isChecked() + ui->checkBox_Imp1->isChecked() + ui->checkBox_Imp2->isChecked();

    /* Check the substances */
    if(checkBox == ui->checkBox_Imp2 || checkBox == ui->checkBox_Imp1 || checkBox == ui->checkBox_Glucose){

        /* Show/Hide Impurity 2 values */
        ui->doubleSpinBox_StockImp2->setVisible(ui->checkBox_Imp2->isChecked());
        ui->label_StockImp2->setVisible(ui->checkBox_Imp2->isChecked());
        ui->label_StockImp2_2->setVisible(ui->checkBox_Imp2->isChecked());
        ui->doubleSpinBox_MaxImp2->setVisible(ui->checkBox_Imp2->isChecked());
        ui->label_MaxImp2->setVisible(ui->checkBox_Imp2->isChecked());
        ui->label_MaxImp2_2->setVisible(ui->checkBox_Imp2->isChecked());
        ui->doubleSpinBox_MinImp2->setVisible(ui->checkBox_Imp2->isChecked());
        ui->label_MinImp2->setVisible(ui->checkBox_Imp2->isChecked());
        ui->label_MinImp2_2->setVisible(ui->checkBox_Imp2->isChecked());
        ui->label_VolI2->setVisible(ui->checkBox_Imp2->isChecked());
        ui->label_VolI22->setVisible(ui->checkBox_Imp2->isChecked());
        ui->lineEdit_VolI2->setVisible(ui->checkBox_Imp2->isChecked());

        /* Show/Hide Impurity 1 values */
        ui->doubleSpinBox_StockImp1->setVisible(ui->checkBox_Imp1->isChecked());
        ui->label_StockImp1->setVisible(ui->checkBox_Imp1->isChecked());
        ui->label_StockImp1_2->setVisible(ui->checkBox_Imp1->isChecked());
        ui->doubleSpinBox_MaxImp1->setVisible(ui->checkBox_Imp1->isChecked());
        ui->label_MaxImp1->setVisible(ui->checkBox_Imp1->isChecked());
        ui->label_MaxImp1_2->setVisible(ui->checkBox_Imp1->isChecked());
        ui->doubleSpinBox_MinImp1->setVisible(ui->checkBox_Imp1->isChecked());
        ui->label_MinImp1->setVisible(ui->checkBox_Imp1->isChecked());
        ui->label_MinImp1_2->setVisible(ui->checkBox_Imp1->isChecked());
        ui->label_VolI1->setVisible(ui->checkBox_Imp1->isChecked());
        ui->label_VolI12->setVisible(ui->checkBox_Imp1->isChecked());
        ui->lineEdit_VolI1->setVisible(ui->checkBox_Imp1->isChecked());

        /* Show/Hide Glucose values */
        ui->doubleSpinBox_StockGlucose->setVisible(ui->checkBox_Glucose->isChecked());
        ui->label_StockGluc->setVisible(ui->checkBox_Glucose->isChecked());
        ui->label_StockGluc2->setVisible(ui->checkBox_Glucose->isChecked());
        ui->doubleSpinBox_MaxGluc->setVisible(ui->checkBox_Glucose->isChecked());
        ui->label_MaxGluc->setVisible(ui->checkBox_Glucose->isChecked());
        ui->label_MaxGluc2->setVisible(ui->checkBox_Glucose->isChecked());
        ui->doubleSpinBox_MinGluc->setVisible(ui->checkBox_Glucose->isChecked());
        ui->label_MinGluc->setVisible(ui->checkBox_Glucose->isChecked());
        ui->label_MinGluc2->setVisible(ui->checkBox_Glucose->isChecked());
        ui->label_VolGl1->setVisible(ui->checkBox_Glucose->isChecked());
        ui->label_VolG2->setVisible(ui->checkBox_Glucose->isChecked());
        ui->lineEdit_VolG->setVisible(ui->checkBox_Glucose->isChecked());

        if(NumberOfSubstances!=0){

            /* Adjust the Stock solutions or maximum concentration accordingly */
            ui->doubleSpinBox_StockGlucose->setValue(ui->doubleSpinBox_MaxGluc->value()*(NumberOfSubstances));
            ui->doubleSpinBox_StockImp1->setValue(ui->doubleSpinBox_MaxImp1->value()*(NumberOfSubstances));
            ui->doubleSpinBox_StockImp2->setValue(ui->doubleSpinBox_MaxImp2->value()*(NumberOfSubstances));
        }
    }

    /* Update all parameters */
    updateConfigurationValues();

}

/**
 * @brief Configure polarimeter from user entries
 */
void configurePolMeasure::configurePolarimeter(void)
{
    /* If the user never pressed enter or similar */
    GetConfigurationData();

    /* Get path to save configuration file */
    QString pathDataM = QFileDialog::getSaveFileName(this, tr("Save Configuration File"), "spectrometer_skript", "Text files (*.txt)");

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
 * @brief Load configuration from file .txt
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

    /* Check format of configuration file; we need at least 5 semicolons per line */
    if (wordList[0].count(QLatin1Char(';')) != 25)
    {
        /* Show message */
        showWarning("Malformed configuration file!", "");
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
            if(externSoftware->ConfigurationFileGenerator->glucoseActive){
                externSoftware->GlucoseConcentration.replace(i, name.left(name.indexOf("C1")).toDouble());
                name.remove(0, name.indexOf("C1")+3);
            }

            /* Get the impurity 1 concentration */
            if(externSoftware->ConfigurationFileGenerator->Imp1Active){
                externSoftware->Impurity1Concentration.replace(i, name.left(name.indexOf("C2")).toDouble());
                name.remove(0, name.indexOf("C2")+3);
            }

            /* Get the impurity 2 concentration */
            if(externSoftware->ConfigurationFileGenerator->Imp2Active){
                externSoftware->Impurity2Concentration.replace(i, name.left(name.indexOf("C3")).toDouble());
            }
        }

        /* At least second entry? */
        if (i > 0)
        {
            /* Calculate duration of entry before current entry */
            double duration = externSoftware->ConfigurationFileGenerator->NrSpectra * externSoftware->ConfigurationFileGenerator->IntegrationTime * externSoftware->ConfigurationFileGenerator->NrAverages;

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

    /* Save the total time */
    totalMtime = (timePoint.at(timePoint.length()-1) + timePoint.at(0))/1000;

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
        externSoftware->ConfigurationFileGenerator->absoluteFlow = dataList.at(7).toDouble();
        externSoftware->ConfigurationFileGenerator->absVol = dataList.at(8).toInt();
        externSoftware->ConfigurationFileGenerator->NSteps = dataList.at(9).toInt();
        externSoftware->ConfigurationFileGenerator->shortBreak = dataList.at(10).toInt();
        externSoftware->ConfigurationFileGenerator->longBreak = dataList.at(11).toInt();
        externSoftware->ConfigurationFileGenerator->startDelay = dataList.at(12).toDouble();
        externSoftware->ConfigurationFileGenerator->glucoseActive = dataList.at(13).toInt();
        externSoftware->ConfigurationFileGenerator->Imp1Active = dataList.at(14).toInt();
        externSoftware->ConfigurationFileGenerator->Imp2Active = dataList.at(15).toInt();
        externSoftware->minConcentrations.replace(0, dataList.at(16).toDouble());
        externSoftware->maxConcentrations.replace(0, dataList.at(17).toDouble());
        externSoftware->stockSolutions.replace(0, dataList.at(18).toDouble());
        externSoftware->minConcentrations.replace(1, dataList.at(19).toDouble());
        externSoftware->maxConcentrations.replace(1, dataList.at(20).toDouble());
        externSoftware->stockSolutions.replace(1, dataList.at(21).toDouble());
        externSoftware->minConcentrations.replace(2, dataList.at(22).toDouble());
        externSoftware->maxConcentrations.replace(2, dataList.at(23).toDouble());
        externSoftware->stockSolutions.replace(2, dataList.at(24).toDouble());
        externSoftware->ConfigurationFileGenerator->repetition = dataList.at(25).toInt();

        externSoftware->ConfigurationFileGenerator->fillRefill = (((externSoftware->ConfigurationFileGenerator->absVol/externSoftware->ConfigurationFileGenerator->absoluteFlow)*60) / externSoftware->ConfigurationFileGenerator->NSteps)*1000;
        externSoftware->ConfigurationFileGenerator->NumberOfSubstances = externSoftware->ConfigurationFileGenerator->glucoseActive + externSoftware->ConfigurationFileGenerator->Imp1Active + externSoftware->ConfigurationFileGenerator->Imp2Active;

        externSoftware->GlucoseConcentration.resize(externSoftware->ConfigurationFileGenerator->NConcentrations);
        externSoftware->Impurity1Concentration.resize(externSoftware->ConfigurationFileGenerator->NConcentrations);
        externSoftware->Impurity2Concentration.resize(externSoftware->ConfigurationFileGenerator->NConcentrations);


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

    /* Get the start delay in seconds */
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
    externSoftware->ConfigurationFileGenerator->glucoseActive = ui->checkBox_Glucose->isChecked();
    externSoftware->ConfigurationFileGenerator->Imp1Active = ui->checkBox_Imp1->isChecked();
    externSoftware->ConfigurationFileGenerator->Imp2Active = ui->checkBox_Imp2->isChecked();

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

    /* Get Refilling Times in ms */
    externSoftware->ConfigurationFileGenerator->fillRefill = (((externSoftware->ConfigurationFileGenerator->absVol/externSoftware->ConfigurationFileGenerator->absoluteFlow)*60) / externSoftware->ConfigurationFileGenerator->NSteps)*1000;

    /* Get the Breaks in ms */
    externSoftware->ConfigurationFileGenerator->shortBreak = (ui->spinBox_ShortBreak->value())*1000;
    externSoftware->ConfigurationFileGenerator->longBreak = (ui->spinBox_LongBreak->value())*1000 + (externSoftware->ConfigurationFileGenerator->IntegrationTime*externSoftware->ConfigurationFileGenerator->NrSpectra*externSoftware->ConfigurationFileGenerator->NrAverages);

    /* Stock Solutions */
    externSoftware->stockSolutions.replace(0,ui->doubleSpinBox_StockGlucose->value());
    externSoftware->stockSolutions.replace(1,ui->doubleSpinBox_StockImp1->value());
    externSoftware->stockSolutions.replace(2,ui->doubleSpinBox_StockImp2->value());

    /* Minimum Concentrations */
    externSoftware->minConcentrations.replace(0,ui->doubleSpinBox_MinGluc->value());
    externSoftware->minConcentrations.replace(1,ui->doubleSpinBox_MinImp1->value());
    externSoftware->minConcentrations.replace(2,ui->doubleSpinBox_MinImp2->value());

    /* Maximum Concentrations */
    externSoftware->maxConcentrations.replace(0,ui->doubleSpinBox_MaxGluc->value());
    externSoftware->maxConcentrations.replace(1,ui->doubleSpinBox_MaxImp1->value());
    externSoftware->maxConcentrations.replace(2,ui->doubleSpinBox_MaxImp2->value());

    /* How many substances are there now? */
    externSoftware->ConfigurationFileGenerator->NumberOfSubstances = externSoftware->ConfigurationFileGenerator->glucoseActive + externSoftware->ConfigurationFileGenerator->Imp1Active + externSoftware->ConfigurationFileGenerator->Imp2Active;

    /* Which Wavelength range will be used? */
    externSoftware->minWavelength = ui->doubleSpinBox_minW->value();
    externSoftware->maxWavelength = ui->doubleSpinBox_maxW->value();

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

    /* Number of substances */
    int NumberOfSubstances = ui->checkBox_Glucose->isChecked() + ui->checkBox_Imp1->isChecked() + ui->checkBox_Imp2->isChecked();

    /* Get Refilling Times in ms */
    int fillRefill = (((ui->spinBox_AbsVol->value()/ui->doubleSpinBox_AbsFlow->value())*60) / ui->spinBox_NSteps->value())*1000;

    /* Get the Breaks in ms */
    int ShortBreak = (ui->spinBox_ShortBreak->value())*1000;
    int LongBreak = (ui->spinBox_LongBreak->value())*1000 + (ui->doubleSpinBox_intTime->value()*ui->spinBox_BNSpec->value()*ui->spinBox_BNAve->value());

    /* Are there substances left? */
    if(!ui->checkBox_Glucose->isChecked() && !ui->checkBox_Imp1->isChecked() && !ui->checkBox_Imp2->isChecked()){

        /* Show critical */
        showCritical("At least one kind of substance has to be selected!", "");

        /* Check glucose by default */
        ui->checkBox_Glucose->setChecked(true);

        /* Enable glucose by default */
        ui->doubleSpinBox_StockGlucose->setVisible(true);
        ui->label_StockGluc->setVisible(true);
        ui->label_StockGluc2->setVisible(true);
        ui->doubleSpinBox_MaxGluc->setVisible(true);
        ui->label_MaxGluc->setVisible(true);
        ui->label_MaxGluc2->setVisible(true);
        ui->doubleSpinBox_MinGluc->setVisible(true);
        ui->label_MinGluc->setVisible(true);
        ui->label_MinGluc2->setVisible(true);
        ui->label_VolGl1->setVisible(true);
        ui->label_VolG2->setVisible(true);
        ui->lineEdit_VolG->setVisible(true);

    }

    /* Update file name preview */
    QString C = "";

    /* Is glucose active? */
    if(ui->checkBox_Glucose->isChecked()){

        /* If glucose is active, add to the name C1 */
        C.append(QString::number(ui->doubleSpinBox_MaxGluc->value()) + "C1");
    }

    /* Is glucose and one of the other two substacnes active? */
    if(ui->checkBox_Glucose->isChecked() && (ui->checkBox_Imp1->isChecked() || ui->checkBox_Imp2->isChecked())){

        /* Add the separator to the file name */
        C.append("_");
    }

    /* Is impurity 1 active? */
    if(ui->checkBox_Imp1->isChecked()){

        /* If Impurity 1 is active, add to the name C2 */
        C.append(QString::number(ui->doubleSpinBox_MaxImp1->value()) + "C2");
    }

    /* If there is also a third substance, add the separator */
    if(ui->checkBox_Imp1->isChecked() && ui->checkBox_Imp2->isChecked()){
        C.append("_");
    }

    /* Is impurity 2 active? */
    if(ui->checkBox_Imp2->isChecked()){

        /* If Impurity 2 is active, add to the name C3 */
        C.append(QString::number(ui->doubleSpinBox_MaxImp2->value()) + "C3");
    }

    /* Complete the file name preview */
    ui->lineEdit_BFileNamePrev->setText(C + "_" + QString::number(ui->doubleSpinBox_intTime->value()) + "ms_"
                                        + QString::number(ui->spinBox_BFreq->value()) + "Hz_1");

    /* Estimate the cycle time */
    double cycleTime = (2 * fillRefill + 4*ShortBreak)
            *(ui->spinBox_NSteps->value() + (ui->spinBox_NSteps->value()-1))
            +  (2 * fillRefill + 3*ShortBreak + LongBreak);

    /* Estimate the measurement time */
    double measurementTime = cycleTime - (((LongBreak + (2*ui->doubleSpinBox_intTime->value()*ui->spinBox_BNSpec->value()*ui->spinBox_BNAve->value()))/3));

    /* Convert the time to minutes, hours or days */
    QStringList ConvertedTime = externSoftware->TimeConverter(measurementTime/1000);

    /* Display the Measurement Time preview */
    ui->lineEdit_timebetweenM->setText(ConvertedTime.at(0));
    ui->label2_timebetweenM->setText(ConvertedTime.at(1));

    /* Estimate the total measurement time */
    double totalMtimer = ((measurementTime + (cycleTime * ui->spinBox_BNMeas->value()))/1000)*(ui->spinBox_Nrepet->value() + 1);

    /* Convert the time to minutes, hours or days */
    ConvertedTime = externSoftware->TimeConverter(totalMtimer);

    /* Display the Total Measurement Time */
    ui->lineEdit_BtimeInterval->setText(ConvertedTime.at(0));
    ui->label_BtimeInt2->setText(ConvertedTime.at(1));

    /* Minimum volume per stock solution */
    double volumeG = (ui->doubleSpinBox_MinGluc->value() + ui->doubleSpinBox_MaxGluc->value())/(2);
    volumeG = (volumeG/ ui->doubleSpinBox_StockGlucose->value())* double(ui->spinBox_BNMeas->value())* double(ui->spinBox_AbsVol->value());

    double volumeI1 = (ui->doubleSpinBox_MinImp1->value() + ui->doubleSpinBox_MaxImp1->value())/(2);
    volumeI1 = (volumeI1/ ui->doubleSpinBox_StockImp1->value())*double(ui->spinBox_BNMeas->value())*double(ui->spinBox_AbsVol->value());

    double volumeI2 = (ui->doubleSpinBox_MinImp2->value() + ui->doubleSpinBox_MaxImp2->value())/(2);
    volumeI2 = (volumeI2/ ui->doubleSpinBox_StockImp2->value())*double(ui->spinBox_BNMeas->value())*double(ui->spinBox_AbsVol->value());

    /* Show the user how much is needed minimum */
    ui->lineEdit_VolG->setText(QString::number(volumeG));
    ui->lineEdit_VolI1->setText(QString::number(volumeI1));
    ui->lineEdit_VolI2->setText(QString::number(volumeI2));

    /* If there is a delay in the start, show when it's going to start then */
    if(ui->doubleSpinBox_startDelay->value() != 0){

        /* Show label when there is a delay */
        ui->label_timeLabel->show();
        ui->timeEdit_timeLabel->show();

        /* Get the actual time and add the delay time */
        startTime = QDateTime::currentDateTime().addSecs(ui->doubleSpinBox_startDelay->value()*3600);

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

    /* Set range limits */
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

    /* Show critical message if the concentration of the stock is inappropriate */
    if(ui->doubleSpinBox_StockGlucose->value() < ui->doubleSpinBox_MaxGluc->value()*(NumberOfSubstances) && ui->checkBox_Glucose->isChecked()){

        QString message = "The stock of Glucose should have a minimum concentration of " + QString::number(ui->doubleSpinBox_MaxGluc->value()*(NumberOfSubstances)) + " mg/dl";
        showCritical(message, "");

        /* Set back default value */
        ui->doubleSpinBox_StockGlucose->setValue(ui->doubleSpinBox_MaxGluc->value()*(NumberOfSubstances));
    }

    /* Show critical message if the concentration of the stock is inappropriate */
    if(ui->doubleSpinBox_StockImp1->value() < ui->doubleSpinBox_MaxImp1->value()*(NumberOfSubstances) && ui->checkBox_Imp1->isChecked()){

        QString message = "The stock of Impurity 1 should have a minimum concentration of " + QString::number(ui->doubleSpinBox_MaxImp1->value()*(NumberOfSubstances)) + " mg/dl";
        showCritical(message, "");

        /* Set back default value */
        ui->doubleSpinBox_StockImp1->setValue(ui->doubleSpinBox_MaxImp1->value()*(NumberOfSubstances));
    }

    /* Show critical message if the concentration of the stock is inappropriate */
    if(ui->doubleSpinBox_StockImp2->value() < ui->doubleSpinBox_MaxImp2->value()*(NumberOfSubstances) && ui->checkBox_Imp2->isChecked() ){

        QString message = "The stock of Impurity 2 should have a minimum concentration of " + QString::number(ui->doubleSpinBox_MaxImp2->value()*(NumberOfSubstances)) + " mg/dl";
        showCritical(message, "");

        /* Set back default value */
        ui->doubleSpinBox_StockImp2->setValue(ui->doubleSpinBox_MaxImp2->value()*(NumberOfSubstances));
    }


}

/**
 * @brief Update the stock solutions as needed when changing the maximum concentration
 */
void configurePolMeasure::updateStockValues(void)
{
    /* Number of substances */
    int NumberOfSubstances = ui->checkBox_Glucose->isChecked() + ui->checkBox_Imp1->isChecked() + ui->checkBox_Imp2->isChecked();

    /* Adjust stock solutions concentration accordingly */
    ui->doubleSpinBox_StockGlucose->setValue(ui->doubleSpinBox_MaxGluc->value()*(NumberOfSubstances));

    /* Adjust stock solutions concentration accordingly */
    ui->doubleSpinBox_StockImp1->setValue(ui->doubleSpinBox_MaxImp1->value()*(NumberOfSubstances));

    /* Adjust stock solutions concentration accordingly */
    ui->doubleSpinBox_StockImp2->setValue(ui->doubleSpinBox_MaxImp2->value()*(NumberOfSubstances));

    updateConfigurationValues();
}

/**
 * @brief Update the values in the form
 */
void configurePolMeasure::updateForm(void)
{
    /* Update form */
    ui->spinBox_AbsVol->setValue(externSoftware->ConfigurationFileGenerator->absVol);
    ui->spinBox_BNMeas->setValue(externSoftware->ConfigurationFileGenerator->NConcentrations);
    ui->spinBox_NSteps->setValue(externSoftware->ConfigurationFileGenerator->NSteps);
    ui->spinBox_ShortBreak->setValue(externSoftware->ConfigurationFileGenerator->shortBreak/1000);
    ui->doubleSpinBox_AbsFlow->setValue(externSoftware->ConfigurationFileGenerator->absoluteFlow);
    ui->doubleSpinBox_startDelay->setValue(externSoftware->ConfigurationFileGenerator->startDelay/3600);
    ui->checkBox_Glucose->setChecked(externSoftware->ConfigurationFileGenerator->glucoseActive);
    ui->checkBox_Imp1->setChecked(externSoftware->ConfigurationFileGenerator->Imp1Active);
    ui->checkBox_Imp2->setChecked(externSoftware->ConfigurationFileGenerator->Imp2Active);
    ui->doubleSpinBox_MinGluc->setValue(externSoftware->minConcentrations.at(0));
    ui->doubleSpinBox_MinImp1->setValue(externSoftware->minConcentrations.at(1));
    ui->doubleSpinBox_MinImp2->setValue(externSoftware->minConcentrations.at(2));
    ui->spinBox_LongBreak->setValue((externSoftware->ConfigurationFileGenerator->longBreak -
                                     (externSoftware->ConfigurationFileGenerator->IntegrationTime*externSoftware->ConfigurationFileGenerator->NrSpectra*
                                      externSoftware->ConfigurationFileGenerator->NrAverages))/1000);
    ui->doubleSpinBox_MaxGluc->setValue(externSoftware->maxConcentrations.at(0));
    ui->doubleSpinBox_MaxImp1->setValue(externSoftware->maxConcentrations.at(1));
    ui->doubleSpinBox_MaxImp2->setValue(externSoftware->maxConcentrations.at(2));
    ui->doubleSpinBox_StockGlucose->setValue(externSoftware->stockSolutions.at(0));
    ui->doubleSpinBox_StockImp1->setValue(externSoftware->stockSolutions.at(1));
    ui->doubleSpinBox_StockImp2->setValue(externSoftware->stockSolutions.at(2));
    /* Repetition minus 1, because 1 measurement means 0 repetitions */
    ui->spinBox_Nrepet->setValue(externSoftware->ConfigurationFileGenerator->repetition - 1);

    /* Update calculable parameters */
    updateConfigurationValues();

    /* Show/Hide Impurity 2 values */
    ui->doubleSpinBox_StockImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_StockImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_StockImp2_2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->doubleSpinBox_MaxImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_MaxImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_MaxImp2_2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->doubleSpinBox_MinImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_MinImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_MinImp2_2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_VolI2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_VolI22->setVisible(ui->checkBox_Imp2->isChecked());
    ui->lineEdit_VolI2->setVisible(ui->checkBox_Imp2->isChecked());

    /* Show/Hide Impurity 1 values */
    ui->doubleSpinBox_StockImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_StockImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_StockImp1_2->setVisible(ui->checkBox_Imp1->isChecked());
    ui->doubleSpinBox_MaxImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_MaxImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_MaxImp1_2->setVisible(ui->checkBox_Imp1->isChecked());
    ui->doubleSpinBox_MinImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_MinImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_MinImp1_2->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_VolI1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_VolI12->setVisible(ui->checkBox_Imp1->isChecked());
    ui->lineEdit_VolI1->setVisible(ui->checkBox_Imp1->isChecked());

    /* Show/Hide Glucose values */
    ui->doubleSpinBox_StockGlucose->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_StockGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_StockGluc2->setVisible(ui->checkBox_Glucose->isChecked());
    ui->doubleSpinBox_MaxGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_MaxGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_MaxGluc2->setVisible(ui->checkBox_Glucose->isChecked());
    ui->doubleSpinBox_MinGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_MinGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_MinGluc2->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_VolGl1->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_VolG2->setVisible(ui->checkBox_Glucose->isChecked());
    ui->lineEdit_VolG->setVisible(ui->checkBox_Glucose->isChecked());

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
 * @brief Destructor of 'configurePolMeasure' class
 */
configurePolMeasure::~configurePolMeasure(void)
{
    delete ui;

    delete externSoftware;
    externSoftware = nullptr;

}
