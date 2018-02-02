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

    /* Create signal mapper for panel */
    signalMapperC = new QSignalMapper(this);

    /* Create the connection to extern software */
    externSoftware = new Pol_ExternConf();

    /* Connect signal mapper action */
    connect(signalMapperC, SIGNAL(mapped(QWidget *)), this, SLOT(handleClickEvent(QWidget *)));

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);

    /* Connect buttons to signal mapper */
    connect(ui->pushButton_select, SIGNAL(clicked()), this, SLOT(selectPath()));
    connect(ui->label_load, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->label_basicConf, SIGNAL(clicked()), signalMapperC, SLOT(map()));

    /* Connect configuration edition */

    /* Spectrometer Settings */
    connect(ui->lineEdit_BIntTime, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_BFreq, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_BNSpec, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_BNAve, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_BNMeas, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));

    /* Solutions Concentrations */
    connect(ui->lineEdit_StockWater, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_StockGluc, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_StockImp1, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_StockImp2, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_Mingluc, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_MinImp1, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_MinImp2, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_MaxGluc, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_MaxImp1, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_MaxImp2, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));

    /* Pump Flow */
    connect(ui->lineEdit_BtimeInterval, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_ShortBreak, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_LongBreak, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_AbsFlow, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_Idle, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_NSteps, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_FillingTime, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_FillSyringe, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_CuvetteFlush, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));

    /* Map of connections */
    signalMapperC->setMapping(ui->label_load, ui->label_load);
    signalMapperC->setMapping(ui->label_basicConf, ui->label_basicConf);

    /* Spectrometer Settings */
    signalMapperC->setMapping(ui->lineEdit_BIntTime, ui->lineEdit_BIntTime);
    signalMapperC->setMapping(ui->lineEdit_BFreq, ui->lineEdit_BFreq);
    signalMapperC->setMapping(ui->lineEdit_BNSpec, ui->lineEdit_BNSpec);
    signalMapperC->setMapping(ui->lineEdit_BNAve, ui->lineEdit_BNAve);
    signalMapperC->setMapping(ui->lineEdit_BNMeas, ui->lineEdit_BNMeas);

    /* Solutions Concentrations */
    signalMapperC->setMapping(ui->lineEdit_StockWater, ui->lineEdit_StockWater);
    signalMapperC->setMapping(ui->lineEdit_StockGluc, ui->lineEdit_StockGluc);
    signalMapperC->setMapping(ui->lineEdit_StockImp1, ui->lineEdit_StockImp1);
    signalMapperC->setMapping(ui->lineEdit_StockImp2, ui->lineEdit_StockImp2);
    signalMapperC->setMapping(ui->lineEdit_Mingluc, ui->lineEdit_Mingluc);
    signalMapperC->setMapping(ui->lineEdit_MinImp1, ui->lineEdit_MinImp1);
    signalMapperC->setMapping(ui->lineEdit_MinImp2, ui->lineEdit_MinImp2);
    signalMapperC->setMapping(ui->lineEdit_MaxGluc, ui->lineEdit_MaxGluc);
    signalMapperC->setMapping(ui->lineEdit_MaxImp1, ui->lineEdit_MaxImp1);
    signalMapperC->setMapping(ui->lineEdit_MaxImp2, ui->lineEdit_MaxImp2);

    /* Pump Flow */
    signalMapperC->setMapping(ui->lineEdit_BtimeInterval, ui->lineEdit_BtimeInterval);
    signalMapperC->setMapping(ui->lineEdit_ShortBreak, ui->lineEdit_ShortBreak);
    signalMapperC->setMapping(ui->lineEdit_LongBreak, ui->lineEdit_LongBreak);
    signalMapperC->setMapping(ui->lineEdit_AbsFlow, ui->lineEdit_AbsFlow);
    signalMapperC->setMapping(ui->lineEdit_Idle, ui->lineEdit_Idle);
    signalMapperC->setMapping(ui->lineEdit_NSteps, ui->lineEdit_NSteps);
    signalMapperC->setMapping(ui->lineEdit_FillingTime, ui->lineEdit_FillingTime);
    signalMapperC->setMapping(ui->lineEdit_FillSyringe, ui->lineEdit_FillSyringe);
    signalMapperC->setMapping(ui->lineEdit_CuvetteFlush, ui->lineEdit_CuvetteFlush);

    /* Connect Button of configuration */
    connect(ui->pushButton_generate, SIGNAL(clicked()), this, SLOT(configurePolarimeter()));

    /* Connect Button of cancel */
    connect(ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(cancel()));

    /* Do you want to load a configuration? or not? */
    Conf_canceled = false;

    /* Not configuration loaded */
    configured = false;

    /* Get Default Data */
    GetConfigurationData();

}

/**
 * @brief Select path for StoreToRAM files
 */
void configurePolMeasure::selectPath(void)
{
    /* No directory chosen until now? */
    if (!ui->lineEdit_path->isEnabled())
    {
        /* Get path of configuration file */
        path = QFileDialog::getOpenFileName(this, "Configuration file", QDir::currentPath(), "Text files (*.txt)");

    }
    else
    {
        /* Get path of configuration file */
        path = QFileDialog::getOpenFileName(this, "Configuration file", path, "Text files (*.txt)");
    }

    /* Did the user select a new path? */
    if (path != ui->lineEdit_path->text() && !path.isEmpty() && ui->lineEdit_path->text() != "Please select a configuration file")
    {
        /* If a new file was loaded, clear all the configuration */
        cleanAll();

    }

    /* Load Configuration */
    loadConfiguration();
}

/**
 * @brief Clean all the configuration if a different file was loaded.
 */
void configurePolMeasure::cleanAll(void)
{
    /* Clear lists */
    timePoint.clear();
    fileName.clear();
    numSpectra=0;
    integrationTime=0;
    numberOfAverages=0;
    freqToMeasure =0;
    ui->lineEdit_path->setEnabled(false);

}

/**
 * @brief Called if a widget option was clicked,
 *        e.g. Integration time label.
 * @param widget Widget which has been clicked
 */
void configurePolMeasure::handleClickEvent(QWidget *widget)
{
    QLabel *label = qobject_cast<QLabel *>(widget);
    QLineEdit *LineLabel = qobject_cast<QLineEdit *>(widget);
    bool ok;

    /* Hide / Show GUI Elements */
    if (label == ui->label_load)
    {
        /* Hide the GUI elements for loading configuration */
        if(ui->LoadWidget->isVisible()){

            ui->label_load->setText("> Load a Spectrometer Configuration File:");
            ui->LoadWidget->hide();

        }else{

            /* Show the GUI elements for loading configuration */
            ui->label_load->setText("< Load a Spectrometer Configuration File:");
            ui->LoadWidget->show();
        }

        /* The basic configuration label has been clicked */
    }else if (label == ui->label_basicConf)
    {
        /* Hide GUI elements */
        if(ui->label_BIntTime->isVisible()){

            /* Change label name */
            ui->label_basicConf->setText("> Create Configuration File:");

            /* hide the labels */
            ui->ConfigurationLayout->hide();

        }else{

            /* Change label name */
            ui->label_basicConf->setText("< Create Configuration File:");

            /* Show labels */
            ui->ConfigurationLayout->show();

        }

    }else{

        /* Spectrometer Settings */

        /* The user decide to configure the integration time */
        if (LineLabel == ui->lineEdit_BIntTime && ui->lineEdit_BIntTime->text().toFloat(&ok) >= 0)
        {
            /* Is there a valid number */
            if(!ok){
                /* Set back default value */
                ui->lineEdit_BIntTime->setText("6");
            }

        }else
            /* The user decide to configure the number of measurements */
            if(LineLabel == ui->lineEdit_BNMeas && ui->lineEdit_BNMeas->text().toInt(&ok) >= 0){

                /* Is there a valid number */
                if(!ok){
                    /* Set back default value */
                    ui->lineEdit_BNMeas->setText("51");
                }

            }else
                /* The user decide to configure the frequency */
                if(LineLabel == ui->lineEdit_BFreq && ui->lineEdit_BFreq->text().toInt(&ok) >= 0){

                    /* Is there a valid number */
                    if(!ok){
                        /* Set back default value */
                        ui->lineEdit_BFreq->setText("7");
                    }

                }else
                    /* The user decide to configure the Nr Spectra */
                    if(LineLabel == ui->lineEdit_BNSpec && ui->lineEdit_BNSpec->text().toInt(&ok) >= 0){

                        /* Is there a valid number */
                        if(!ok){
                            /* Set back default value */
                            ui->lineEdit_BNSpec->setText("1000");
                        }

                    }else
                        /* The user decide to configure the Nr of Averages */
                        if(LineLabel == ui->lineEdit_BNAve && ui->lineEdit_BNAve->text().toInt(&ok) >= 0){

                            /* Is there a valid number */
                            if(!ok){
                                /* Set back default value */
                                ui->lineEdit_BNAve->setText("1");
                            }
                        }

        /* Solutions Concentrations Settings */

        /* The user decide to change the stock water */
        if(LineLabel == ui->lineEdit_StockWater && ui->lineEdit_StockWater->text().toInt(&ok) >= 0){

            /* Is there a valid number */
            if(!ok){
                /* Set back default value */
                ui->lineEdit_StockWater->setText("20000");
            }
        }else
            /* The user decide to change the stock glucose */
            if(LineLabel == ui->lineEdit_StockGluc && ui->lineEdit_StockGluc->text().toInt(&ok) >= 0){

                /* Is there a valid number */
                if(!ok){
                    /* Set back default value */
                    ui->lineEdit_StockGluc->setText("1000");
                }
            }else
                /* The user decide to change the stock Impurity 1 */
                if(LineLabel == ui->lineEdit_StockImp1 && ui->lineEdit_StockImp1->text().toInt(&ok) >= 0){

                    /* Is there a valid number */
                    if(!ok){
                        /* Set back default value */
                        ui->lineEdit_StockImp1->setText("4");
                    }
                }else
                    /* The user decide to change the stock Impurity 2 */
                    if(LineLabel == ui->lineEdit_StockImp2 && ui->lineEdit_StockImp2->text().toInt(&ok) >= 0){

                        /* Is there a valid number */
                        if(!ok){
                            /* Set back default value */
                            ui->lineEdit_StockImp2->setText("0");
                        }
                    }

        /* The user decide to change the minimum glucose concentration */
        if(LineLabel == ui->lineEdit_Mingluc && ui->lineEdit_Mingluc->text().toDouble(&ok) >= 0){

            /* Is there a valid number */
            if(!ok){
                /* Set back default value */
                ui->lineEdit_Mingluc->setText("0");
            }
        }else
            /* The user decide to change the minimum impurity 1 concentration */
            if(LineLabel == ui->lineEdit_MinImp1 && ui->lineEdit_MinImp1->text().toDouble(&ok) >= 0){

                /* Is there a valid number */
                if(!ok){
                    /* Set back default value */
                    ui->lineEdit_MinImp1->setText("0");
                }
            }else
                /* The user decide to change the minimum impurity 2 concentration */
                if(LineLabel == ui->lineEdit_MinImp2 && ui->lineEdit_MinImp2->text().toDouble(&ok) >= 0){

                    /* Is there a valid number */
                    if(!ok){
                        /* Set back default value */
                        ui->lineEdit_MinImp2->setText("0");
                    }
                }

        /* The user decide to change the maximum glucose concentration */
        if(LineLabel == ui->lineEdit_MaxGluc && ui->lineEdit_MaxGluc->text().toDouble(&ok) >= 0){

            /* Is there a valid number */
            if(!ok){
                /* Set back default value */
                ui->lineEdit_MaxGluc->setText("1");
            }
        }else
            /* The user decide to change the maximum impurity 1 concentration */
            if(LineLabel == ui->lineEdit_MaxImp1 && ui->lineEdit_MaxImp1->text().toDouble(&ok) >= 0){

                /* Is there a valid number */
                if(!ok){
                    /* Set back default value */
                    ui->lineEdit_MaxImp1->setText("0.1");
                }
            }else
                /* The user decide to change the maximum impurity 2 concentration */
                if(LineLabel == ui->lineEdit_MaxImp2 && ui->lineEdit_MaxImp2->text().toDouble(&ok) >= 0){

                    /* Is there a valid number */
                    if(!ok){
                        /* Set back default value */
                        ui->lineEdit_MaxImp2->setText("0");
                    }
                }

        /* Pump Flow */

        /* The user decide to change the time interval */
        if(LineLabel == ui->lineEdit_BtimeInterval && ui->lineEdit_BtimeInterval->text().toInt(&ok) >= 0){

            /* Is there a valid number */
            if(!ok){
                /* Set back default value */
                ui->lineEdit_BtimeInterval->setText("120");
            }
        }else
            /* The user decide to change the short break time */
            if(LineLabel == ui->lineEdit_ShortBreak && ui->lineEdit_ShortBreak->text().toInt(&ok) >= 0){

                /* Is there a valid number */
                if(!ok){
                    /* Set back default value */
                    ui->lineEdit_ShortBreak->setText("1");
                }
            }else
                /* The user decide to change the long break time */
                if(LineLabel == ui->lineEdit_LongBreak && ui->lineEdit_LongBreak->text().toInt(&ok) >= 0){

                    /* Is there a valid number */
                    if(!ok){
                        /* Set back default value */
                        ui->lineEdit_LongBreak->setText("30");
                    }
                }else
                    /* The user decide to change the absolute Flow */
                    if(LineLabel == ui->lineEdit_AbsFlow && ui->lineEdit_AbsFlow->text().toDouble(&ok) >= 0){

                        /* Is there a valid number */
                        if(!ok){
                            /* Set back default value */
                            ui->lineEdit_AbsFlow->setText("18.75");
                        }
                    }else
                        /* The user decide to change the Idle */
                        if(LineLabel == ui->lineEdit_Idle && ui->lineEdit_Idle->text().toInt(&ok) >= 0){

                            /* Is there a valid number */
                            if(!ok){
                                /* Set back default value */
                                ui->lineEdit_Idle->setText("0");
                            }
                        }else
                            /* The user decide to change the Nr Steps */
                            if(LineLabel == ui->lineEdit_NSteps && ui->lineEdit_NSteps->text().toInt(&ok) >= 0){

                                /* Is there a valid number */
                                if(!ok){
                                    /* Set back default value */
                                    ui->lineEdit_NSteps->setText("5");
                                }
                            }else
                                /* The user decide to change the Filling Time */
                                if(LineLabel == ui->lineEdit_FillingTime && ui->lineEdit_FillingTime->text().toInt(&ok) >= 0){

                                    /* Is there a valid number */
                                    if(!ok){
                                        /* Set back default value */
                                        ui->lineEdit_FillingTime->setText("80");
                                    }
                                }else
                                    /* The user decide to change the Syringe Filling Time */
                                    if(LineLabel == ui->lineEdit_FillSyringe && ui->lineEdit_FillSyringe->text().toInt(&ok) >= 0){

                                        /* Is there a valid number */
                                        if(!ok){
                                            /* Set back default value */
                                            ui->lineEdit_FillSyringe->setText("80");
                                        }
                                    }else
                                        /* The user decide to change the Cuvette Flushing */
                                        if(LineLabel == ui->lineEdit_CuvetteFlush && ui->lineEdit_CuvetteFlush->text().toInt(&ok) >= 0){

                                            /* Is there a valid number */
                                            if(!ok){
                                                /* Set back default value */
                                                ui->lineEdit_CuvetteFlush->setText("80");
                                            }
                                        }

        /* File name preview */
        ui->lineEdit_BFileNamePrev->setText("0C1_0C2_" + QString::number(ui->lineEdit_BIntTime->text().toFloat()) + "ms_"
                                            + QString::number(ui->lineEdit_BFreq->text().toInt()) + "Hz_1");

        /* Update Data */
        GetConfigurationData();
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
    externSoftware->pathFile = QFileDialog::getSaveFileName(this, tr("Polarimeter Configuration File"), "", "Text files (*.txt)");
    path = externSoftware->pathFile;

    /* Calculate the needed scripts for the measurements */
    externSoftware->pumpsPatternCalculator();

    /* Load saved file */
    //  loadConfiguration();

    /* Save that a configuration file was loaded */
    //     configured = true;

    /* Run pumps software */
    //     externSoftware->openPumpSoftware();

    /* Finish the window */
    //      accept();
    //}

}

/**
 * @brief Load configuration from file .txt
 */
void configurePolMeasure::loadConfiguration(void)
{

    /* Save rows in file */
    QStringList wordList;

    /* Did user select a path? */
    if (!path.isEmpty())
    {
        /* File Path */
        QFile file(path);

        /* Open configuration file */
        if (!file.open(QIODevice::ReadOnly))
        {
            /* Show message */
            showCritical("Unable to open configuration file!", "");
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

        /* Close file */
        file.close();

        /* Clear lists */
        cleanAll();

        /* Check format of configuration file; we need at least 5 semicolons per line */
        if (wordList[0].count(QLatin1Char(';')) != 5)
        {
            /* Show message */
            showWarning("Malformed configuration file!", "");
            configured = false;
            return;
        }

        unsigned int i = 0;

        /* Loop through elements */
        for (i = 0; i < (unsigned int)wordList.length(); i++)
        {
            QStringList list = wordList[i].split(';');

            /* Copy entries to lists */
            timePoint.append(list[0].toInt());
            fileName.append(list[1]);
            numSpectra = list[2].toInt();
            integrationTime = list[3].toFloat();
            numberOfAverages = list[4].toInt();
            freqToMeasure = list[5].toInt();

            /* At least second entry? */
            if (i > 0)
            {
                /* Calculate duration of entry before current entry */
                double duration = numSpectra * integrationTime * numberOfAverages;

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

        /* Copy path into line edit */
        ui->lineEdit_path->setText(path);

        /* Enable directory field and 'start' button */
        ui->lineEdit_path->setEnabled(true);

        /* Run pumps software */
        externSoftware->openPumpSoftware();

        /* Finish the window */
        accept();
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
 * @brief Get data from formular
 */
void configurePolMeasure::GetConfigurationData(void)
{

    /* Get Integration Time */
    integrationTime = ui->lineEdit_BIntTime->text().toFloat();
    externSoftware->IntegrationTime = integrationTime;

    /* Get Frequency to Measure */
    freqToMeasure = ui->lineEdit_BFreq->text().toInt();
    externSoftware->Frequency = freqToMeasure;

    /* Get Number of Spectra */
    numSpectra = ui->lineEdit_BNSpec->text().toInt();
    externSoftware->NrSpectra = numSpectra;

    /* Get Number of Averages */
    numberOfAverages = ui->lineEdit_BNAve->text().toInt();

    /* Get Number of Measurements */
    NrMeasurements = ui->lineEdit_BNMeas->text().toInt();
    externSoftware->NConcentrations = NrMeasurements;

    /* Get Refilling Times */
    externSoftware->fillRefill = ui->lineEdit_FillingTime->text().toInt() / ui->lineEdit_NSteps->text().toInt();
    externSoftware->refillSyringe = ui->lineEdit_FillSyringe->text().toInt() / ui->lineEdit_NSteps->text().toInt();
    externSoftware->flushingCuvette = ui->lineEdit_CuvetteFlush->text().toInt() / ui->lineEdit_NSteps->text().toInt();

    /* Get Flows */
    externSoftware->absoluteFlow = ui->lineEdit_AbsFlow->text().toDouble();
    externSoftware->idle = ui->lineEdit_Idle->text().toInt();

    /* Break Times */
    externSoftware->shortBreak = ui->lineEdit_ShortBreak->text().toInt();
    externSoftware->longBreak = ui->lineEdit_LongBreak->text().toInt();

    /* Stock Solutions */
    externSoftware->stockSolutions.append(ui->lineEdit_StockWater->text().toInt());
    externSoftware->stockSolutions.append(ui->lineEdit_StockGluc->text().toInt());
    externSoftware->stockSolutions.append(ui->lineEdit_StockImp1->text().toInt());
    externSoftware->stockSolutions.append(ui->lineEdit_StockImp2->text().toInt());

    /* Minimum Concentrations */
    externSoftware->minConcentrations.append(ui->lineEdit_Mingluc->text().toInt());
    externSoftware->minConcentrations.append(ui->lineEdit_MinImp1->text().toInt());
    externSoftware->minConcentrations.append(ui->lineEdit_MinImp2->text().toInt());

    /* Maximum Concentrations */
    externSoftware->maxConcentrations.append(ui->lineEdit_MaxGluc->text().toInt());
    externSoftware->maxConcentrations.append(ui->lineEdit_MaxImp1->text().toInt());
    externSoftware->maxConcentrations.append(ui->lineEdit_MaxImp2->text().toInt());

    /* Get additional time for intervals */
    externSoftware->TimeIntervals = ui->lineEdit_BtimeInterval->text().toInt();

    /* Very long Int Time? */
    if(integrationTime > 200){

        /* Show warning */
        showWarning("Please consider that large integration times will lead to a larger measurement time!", "");

    }

    /* Too large number of spectra */
    if(numSpectra > 3000){

        /* Show warning */
        showWarning("Please consider that large number of spectra will lead to a larger measurement time!", "");
    }

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
