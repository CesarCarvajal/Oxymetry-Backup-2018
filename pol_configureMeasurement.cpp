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

    /* Loading configuration from file? */
    loadingConfigurationFromFile = false;

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint  | Qt::WindowCloseButtonHint);

    /* Connect buttons to signal mapper */
    connect(ui->pushButton_select, SIGNAL(clicked()), this, SLOT(selectPath()));
    connect(ui->label_load, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->label_basicConf, SIGNAL(clicked()), signalMapperC, SLOT(map()));

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
    connect(ui->lineEdit_StockGluc, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_StockImp1, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_StockImp2, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_Mingluc, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_MinImp1, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_MinImp2, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_MaxGluc, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_MaxImp1, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));
    connect(ui->lineEdit_MaxImp2, SIGNAL(returnPressed()), signalMapperC, SLOT(map()));

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

    /* Map of connections */
    signalMapperC->setMapping(ui->label_load, ui->label_load);
    signalMapperC->setMapping(ui->label_basicConf, ui->label_basicConf);

    /* Solutions Concentrations */
    signalMapperC->setMapping(ui->lineEdit_StockGluc, ui->lineEdit_StockGluc);
    signalMapperC->setMapping(ui->lineEdit_StockImp1, ui->lineEdit_StockImp1);
    signalMapperC->setMapping(ui->lineEdit_StockImp2, ui->lineEdit_StockImp2);
    signalMapperC->setMapping(ui->lineEdit_Mingluc, ui->lineEdit_Mingluc);
    signalMapperC->setMapping(ui->lineEdit_MinImp1, ui->lineEdit_MinImp1);
    signalMapperC->setMapping(ui->lineEdit_MinImp2, ui->lineEdit_MinImp2);
    signalMapperC->setMapping(ui->lineEdit_MaxGluc, ui->lineEdit_MaxGluc);
    signalMapperC->setMapping(ui->lineEdit_MaxImp1, ui->lineEdit_MaxImp1);
    signalMapperC->setMapping(ui->lineEdit_MaxImp2, ui->lineEdit_MaxImp2);
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
    ui->lineEdit_StockImp2->setVisible(false);
    ui->label_StockImp2->setVisible(false);
    ui->label_StockImp2_2->setVisible(false);
    ui->lineEdit_MaxImp2->setVisible(false);
    ui->label_MaxImp2->setVisible(false);
    ui->label_MaxImp2_2->setVisible(false);
    ui->lineEdit_MinImp2->setVisible(false);
    ui->label_MinImp2->setVisible(false);
    ui->label_MinImp2_2->setVisible(false);
    ui->label_VolI2->setVisible(false);
    ui->label_VolI22->setVisible(false);
    ui->lineEdit_VolI2->setVisible(false);

    /* Hide the time label, show it only when there is a delay */
    ui->label_timeLabel->hide();
    ui->timeEdit_timeLabel->hide();

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

    /* Is configuration loaded */
    loadingConfigurationFromFile = true;

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
    QLabel *label = qobject_cast<QLabel *>(widget);
    QLineEdit *LineLabel = qobject_cast<QLineEdit *>(widget);
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(widget);

    /* Is it a valid number? */
    bool ok;

    /* Get actual Data */
    GetConfigurationData();

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

    }

    /* Solutions Concentrations Settings */

    /* The user decide to change the stock glucose */
    if(LineLabel == ui->lineEdit_StockGluc && ui->lineEdit_StockGluc->text().toDouble(&ok) >= 0){

        /* Is there a valid number */
        if(!ok){
            /* If not, then set back default value */
            ui->lineEdit_StockGluc->setText("1000");
        }

        /* Show critical message if the concentration of the stock is inappropriate */
        if(ui->lineEdit_StockGluc->text().toDouble() < externSoftware->maxConcentrations.at(0)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances) ){

            QString message = "The stock of Glucose should have a minimum concentration of " + QString::number(externSoftware->maxConcentrations.at(0)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances)) + " mg/dl";
            showCritical(message, "");

            /* Set back default value */
            ui->lineEdit_StockGluc->setText(QString::number( externSoftware->maxConcentrations.at(0)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances) ));
        }

    }else
        /* The user decide to change the stock Impurity 1 */
        if(LineLabel == ui->lineEdit_StockImp1 && ui->lineEdit_StockImp1->text().toDouble(&ok) >= 0){

            /* Is there a valid number */
            if(!ok){
                /* If not, then set back default value */
                ui->lineEdit_StockImp1->setText("4");
            }

            /* Show critical message if the concentration of the stock is inappropriate */
            if(ui->lineEdit_StockImp1->text().toDouble() < externSoftware->maxConcentrations.at(1)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances) ){

                QString message = "The stock of Impurity 1 should have a minimum concentration of " + QString::number(externSoftware->maxConcentrations.at(1)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances)) + " mg/dl";
                showCritical(message, "");

                /* Set back default value */
                ui->lineEdit_StockImp1->setText(QString::number(externSoftware->maxConcentrations.at(1)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances)));
            }

        }else
            /* The user decide to change the stock Impurity 2 */
            if(LineLabel == ui->lineEdit_StockImp2 && ui->lineEdit_StockImp2->text().toDouble(&ok) >= 0){

                /* Is there a valid number */
                if(!ok){
                    /* If not, then set back default value */
                    ui->lineEdit_StockImp2->setText("0");
                }

                /* Show critical message if the concentration of the stock is inappropriate */
                if(ui->lineEdit_StockImp2->text().toDouble() < externSoftware->maxConcentrations.at(2)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances) ){

                    QString message = "The stock of Impurity 2 should have a minimum concentration of " + QString::number(externSoftware->maxConcentrations.at(2)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances)) + " mg/dl";
                    showCritical(message, "");

                    /* Set back default value */
                    ui->lineEdit_StockImp2->setText(QString::number(externSoftware->maxConcentrations.at(2)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances)));
                }

            }

    /* The user decide to change the minimum glucose concentration */
    if(LineLabel == ui->lineEdit_Mingluc && ui->lineEdit_Mingluc->text().toDouble(&ok) >= 0){

        /* Is there a valid number */
        if(!ok){
            /* If not, then set back default value */
            ui->lineEdit_Mingluc->setText("0");
        }
    }else
        /* The user decide to change the minimum impurity 1 concentration */
        if(LineLabel == ui->lineEdit_MinImp1 && ui->lineEdit_MinImp1->text().toDouble(&ok) >= 0){

            /* Is there a valid number */
            if(!ok){
                /* If not, then set back default value */
                ui->lineEdit_MinImp1->setText("0");
            }
        }else
            /* The user decide to change the minimum impurity 2 concentration */
            if(LineLabel == ui->lineEdit_MinImp2 && ui->lineEdit_MinImp2->text().toDouble(&ok) >= 0){

                /* Is there a valid number */
                if(!ok){
                    /* If not, then set back default value */
                    ui->lineEdit_MinImp2->setText("0");
                }
            }

    /* The user decide to change the maximum glucose concentration */
    if(LineLabel == ui->lineEdit_MaxGluc && ui->lineEdit_MaxGluc->text().toDouble(&ok) >= 0){

        /* Is there a valid number */
        if(!ok){
            /* If not, then set back default value */
            ui->lineEdit_MaxGluc->setText("1");
        }

        /* Update stock solutions concentrations */
        externSoftware->stockSolutions.replace(0, externSoftware->maxConcentrations.at(0)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances));

        /* Adjust stock solutions concentration accordingly */
        ui->lineEdit_StockGluc->setText(QString::number(externSoftware->stockSolutions.at(0)));

    }else
        /* The user decide to change the maximum impurity 1 concentration */
        if(LineLabel == ui->lineEdit_MaxImp1 && ui->lineEdit_MaxImp1->text().toDouble(&ok) >= 0){

            /* Is there a valid number */
            if(!ok){
                /* If not, then set back default value */
                ui->lineEdit_MaxImp1->setText("0.1");
            }

            /* Update stock solutions concentrations */
            externSoftware->stockSolutions.replace(1, externSoftware->maxConcentrations.at(1)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances));

            /* Adjust stock solutions concentration accordingly */
            ui->lineEdit_StockImp1->setText(QString::number(externSoftware->stockSolutions.at(1)));

        }else
            /* The user decide to change the maximum impurity 2 concentration */
            if(LineLabel == ui->lineEdit_MaxImp2 && ui->lineEdit_MaxImp2->text().toDouble(&ok) >= 0){

                /* Is there a valid number */
                if(!ok){
                    /* If not, then set back default value */
                    ui->lineEdit_MaxImp2->setText("0");
                }

                /* Update stock solutions concentrations */
                externSoftware->stockSolutions.replace(2, externSoftware->maxConcentrations.at(2)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances));

                /* Adjust stock solutions concentration accordingly */
                ui->lineEdit_StockImp2->setText(QString::number(externSoftware->stockSolutions.at(2)));
            }

/* Check the substances */
if(checkBox == ui->checkBox_Imp2 || checkBox == ui->checkBox_Imp1 || checkBox == ui->checkBox_Glucose){

    /* Show/Hide Impurity 2 values */
    ui->lineEdit_StockImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_StockImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_StockImp2_2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->lineEdit_MaxImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_MaxImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_MaxImp2_2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->lineEdit_MinImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_MinImp2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_MinImp2_2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_VolI2->setVisible(ui->checkBox_Imp2->isChecked());
    ui->label_VolI22->setVisible(ui->checkBox_Imp2->isChecked());
    ui->lineEdit_VolI2->setVisible(ui->checkBox_Imp2->isChecked());

    /* Show/Hide Impurity 1 values */
    ui->lineEdit_StockImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_StockImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_StockImp1_2->setVisible(ui->checkBox_Imp1->isChecked());
    ui->lineEdit_MaxImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_MaxImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_MaxImp1_2->setVisible(ui->checkBox_Imp1->isChecked());
    ui->lineEdit_MinImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_MinImp1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_MinImp1_2->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_VolI1->setVisible(ui->checkBox_Imp1->isChecked());
    ui->label_VolI12->setVisible(ui->checkBox_Imp1->isChecked());
    ui->lineEdit_VolI1->setVisible(ui->checkBox_Imp1->isChecked());

    /* Show/Hide Glucose values */
    ui->lineEdit_StockGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_StockGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_StockGluc2->setVisible(ui->checkBox_Glucose->isChecked());
    ui->lineEdit_MaxGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_MaxGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_MaxGluc2->setVisible(ui->checkBox_Glucose->isChecked());
    ui->lineEdit_Mingluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_MinGluc->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_MinGluc2->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_VolGl1->setVisible(ui->checkBox_Glucose->isChecked());
    ui->label_VolG2->setVisible(ui->checkBox_Glucose->isChecked());
    ui->lineEdit_VolG->setVisible(ui->checkBox_Glucose->isChecked());

    if(externSoftware->ConfigurationFileGenerator->NumberOfSubstances!=0){

        /* Update maximum concentrations */
        for(int l=0; l<3; l++){
            externSoftware->stockSolutions.replace(l, externSoftware->maxConcentrations.at(l)*(externSoftware->ConfigurationFileGenerator->NumberOfSubstances));
        }

        /* Adjust the Stock solutions or maximum concentration accordingly */
        ui->lineEdit_StockGluc->setText(QString::number(externSoftware->stockSolutions.at(0)));
        ui->lineEdit_StockImp1->setText(QString::number(externSoftware->stockSolutions.at(1)));
        ui->lineEdit_StockImp2->setText(QString::number(externSoftware->stockSolutions.at(2)));
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

    /* Is there a configuration loaded? */
    loadingConfigurationFromFile = false;

    /* Get path to save configuration file */
    path = QFileDialog::getSaveFileName(this, tr("Save Configuration File"), "spectrometer_skript", "Text files (*.txt)");

    /* Is there a path? */
    if(!path.isEmpty()){

        /* Get path to create the configuration file */
        externSoftware->pathFile = path;

        /* Create the needed scripts for the measurements */
        externSoftware->pumpsPatternCalculator();

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

        /* Remove the first row since it only has a description of the file */
        wordList.removeAt(0);

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

        /* Loading configuration from file? */
        if(loadingConfigurationFromFile){

            /* Concentrations */
            externSoftware->GlucoseConcentration.resize((unsigned int)wordList.length());
            externSoftware->Impurity1Concentration.resize((unsigned int)wordList.length());
            externSoftware->Impurity2Concentration.resize((unsigned int)wordList.length());

            /* Deactivate substances */
            externSoftware->ConfigurationFileGenerator->glucoseActive = false;
            externSoftware->ConfigurationFileGenerator->Imp1Active = false;
            externSoftware->ConfigurationFileGenerator->Imp2Active = false;
        }

        unsigned int i = 0;

        /* Loop through elements */
        for (i = 0; i < (unsigned int)wordList.length(); i++)
        {
            /* Divide by the semicolon ";" */
            QStringList list = wordList[i].split(';');

            /* Copy entries to the lists */
            timePoint.append(list[0].toInt());
            fileName.append(list[1]);
            externSoftware->ConfigurationFileGenerator->NrSpectra = list[2].toInt();
            externSoftware->ConfigurationFileGenerator->IntegrationTime = list[3].toFloat();
            externSoftware->ConfigurationFileGenerator->NrAverages = list[4].toInt();
            externSoftware->ConfigurationFileGenerator->Frequency = list[5].toInt();

            /* Are you loading a file without the pump description? */
            if(loadingConfigurationFromFile){

                /* Get the File Name information */
                QStringList listC = QString(list[1]).split("_");

                /* Loop throught the file name */
                for(int j = 0; j < listC.length() ; j++){

                    /* Is glucose or C1 included? */
                    if(QString(listC[j]).contains("C1")){

                        /* Glucose is active */
                        externSoftware->ConfigurationFileGenerator->glucoseActive = true;

                        /* Add the corresponding concentration */
                        externSoftware->GlucoseConcentration.replace(i, QString(listC[j]).left(QString(listC[j]).lastIndexOf("C1")).toDouble());
                    }

                    /* Is Impurity 1 or C2 included? */
                    if(QString(listC[j]).contains("C2")){

                        /* Glucose is active */
                        externSoftware->ConfigurationFileGenerator->Imp1Active = true;

                        /* Add the corresponding concentration */
                        externSoftware->Impurity1Concentration.replace(i, QString(listC[j]).left(QString(listC[j]).lastIndexOf("C2")).toDouble());
                    }

                    /* Is impurity 2 or C3 included? */
                    if(QString(listC[j]).contains("C3")){

                        /* Impurity 2 is active */
                        externSoftware->ConfigurationFileGenerator->Imp2Active = true;

                        /* Add the corresponding concentration */
                        externSoftware->Impurity2Concentration.replace(i, QString(listC[j]).left(QString(listC[j]).lastIndexOf("C3")).toDouble());
                    }
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

    /* Get absolute Flow */
    externSoftware->ConfigurationFileGenerator->absoluteFlow = ui->doubleSpinBox_AbsFlow->value();

    /* Is the idle active? */
    int idled = ui->checkBox->isChecked();
    externSoftware->ConfigurationFileGenerator->idle = idled;

    /* Get Refilling Times in ms */
    externSoftware->ConfigurationFileGenerator->fillRefill = (((ui->spinBox_AbsVol->value()/externSoftware->ConfigurationFileGenerator->absoluteFlow)*60) / externSoftware->ConfigurationFileGenerator->NSteps)*1000;

    /* Get the Breaks in ms */
    externSoftware->ConfigurationFileGenerator->shortBreak = (ui->spinBox_ShortBreak->value())*1000;
    externSoftware->ConfigurationFileGenerator->longBreak = (ui->spinBox_LongBreak->value())*1000 + (externSoftware->ConfigurationFileGenerator->IntegrationTime*externSoftware->ConfigurationFileGenerator->NrSpectra);

    /* Stock Solutions */
    externSoftware->stockSolutions.replace(0,ui->lineEdit_StockGluc->text().toDouble());
    externSoftware->stockSolutions.replace(1,ui->lineEdit_StockImp1->text().toDouble());
    externSoftware->stockSolutions.replace(2,ui->lineEdit_StockImp2->text().toDouble());

    /* Minimum Concentrations */
    externSoftware->minConcentrations.replace(0,ui->lineEdit_Mingluc->text().toDouble());
    externSoftware->minConcentrations.replace(1,ui->lineEdit_MinImp1->text().toDouble());
    externSoftware->minConcentrations.replace(2,ui->lineEdit_MinImp2->text().toDouble());

    /* Maximum Concentrations */
    externSoftware->maxConcentrations.replace(0,ui->lineEdit_MaxGluc->text().toDouble());
    externSoftware->maxConcentrations.replace(1,ui->lineEdit_MaxImp1->text().toDouble());
    externSoftware->maxConcentrations.replace(2,ui->lineEdit_MaxImp2->text().toDouble());

    /* How many substances are there now? */
    externSoftware->ConfigurationFileGenerator->NumberOfSubstances = externSoftware->ConfigurationFileGenerator->glucoseActive + externSoftware->ConfigurationFileGenerator->Imp1Active + externSoftware->ConfigurationFileGenerator->Imp2Active;

    /* Which Wavelength range will be used? */
    externSoftware->ConfigurationFileGenerator->minWavelength = ui->doubleSpinBox_minW->value();
    externSoftware->ConfigurationFileGenerator->maxWavelength = ui->doubleSpinBox_maxW->value();

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
    /* Get actual Data */
    GetConfigurationData();

    /* Are there substances left? */
    if(!externSoftware->ConfigurationFileGenerator->glucoseActive && !externSoftware->ConfigurationFileGenerator->Imp1Active && !externSoftware->ConfigurationFileGenerator->Imp2Active){

        /* Show critical */
        showCritical("At least one kind of substance has to be selected!", "");

        /* Check glucose by default */
        ui->checkBox_Glucose->setChecked(true);

        /* Enable glucose by default */
        ui->lineEdit_StockGluc->setVisible(true);
        ui->label_StockGluc->setVisible(true);
        ui->label_StockGluc2->setVisible(true);
        ui->lineEdit_MaxGluc->setVisible(true);
        ui->label_MaxGluc->setVisible(true);
        ui->label_MaxGluc2->setVisible(true);
        ui->lineEdit_Mingluc->setVisible(true);
        ui->label_MinGluc->setVisible(true);
        ui->label_MinGluc2->setVisible(true);
        ui->label_VolGl1->setVisible(true);
        ui->label_VolG2->setVisible(true);
        ui->lineEdit_VolG->setVisible(true);

        /* Get actual Data */
        GetConfigurationData();
    }

    /* Update file name preview */
    QString C = "";

    /* Is glucose active? */
    if(externSoftware->ConfigurationFileGenerator->glucoseActive){

        /* If glucose is active, add to the name C1 */
        C.append(QString::number(externSoftware->maxConcentrations.at(0)) + "C1");
    }

    /* Is glucose and one of the other two substacnes active? */
    if(externSoftware->ConfigurationFileGenerator->glucoseActive && (externSoftware->ConfigurationFileGenerator->Imp1Active || externSoftware->ConfigurationFileGenerator->Imp2Active)){

        /* Add the separator to the file name */
        C.append("_");
    }

    /* Is impurity 1 active? */
    if(externSoftware->ConfigurationFileGenerator->Imp1Active){

        /* If Impurity 1 is active, add to the name C2 */
        C.append(QString::number(externSoftware->maxConcentrations.at(1)) + "C2");
    }

    /* If there is also a third substance, add the separator */
    if(externSoftware->ConfigurationFileGenerator->Imp1Active && externSoftware->ConfigurationFileGenerator->Imp2Active){
        C.append("_");
    }

    /* Is impurity 2 active? */
    if(externSoftware->ConfigurationFileGenerator->Imp2Active){

        /* If Impurity 2 is active, add to the name C3 */
        C.append(QString::number(externSoftware->maxConcentrations.at(2)) + "C3");
    }

    /* Complete the file name preview */
    ui->lineEdit_BFileNamePrev->setText(C + "_" + QString::number(externSoftware->ConfigurationFileGenerator->IntegrationTime) + "ms_"
                                        + QString::number(externSoftware->ConfigurationFileGenerator->Frequency) + "Hz_1");

    /* Estimate the cycle time */
    double cycleTime = (2 * externSoftware->ConfigurationFileGenerator->fillRefill + 4*externSoftware->ConfigurationFileGenerator->shortBreak)
            *(externSoftware->ConfigurationFileGenerator->NSteps + (externSoftware->ConfigurationFileGenerator->NSteps-1))
            +  (2 * externSoftware->ConfigurationFileGenerator->fillRefill + 3*externSoftware->ConfigurationFileGenerator->shortBreak + externSoftware->ConfigurationFileGenerator->longBreak );

    /* Estimate the measurement time */
    double measurementTime = cycleTime - (((externSoftware->ConfigurationFileGenerator->longBreak + (2*externSoftware->ConfigurationFileGenerator->IntegrationTime*externSoftware->ConfigurationFileGenerator->NrSpectra))/3));

    /* Convert the time to minutes, hours or days */
    QStringList ConvertedTime = externSoftware->TimeConverter(measurementTime/1000);

    /* Display the Measurement Time preview */
    ui->lineEdit_timebetweenM->setText(ConvertedTime.at(0));
    ui->label2_timebetweenM->setText(ConvertedTime.at(1));

    /* Estimate the total measurement time */
    double totalMtimer = (measurementTime + (cycleTime * externSoftware->ConfigurationFileGenerator->NConcentrations))/1000;

    /* Convert the time to minutes, hours or days */
    ConvertedTime = externSoftware->TimeConverter(totalMtimer);

    /* Display the Total Measurement Time */
    ui->lineEdit_BtimeInterval->setText(ConvertedTime.at(0));
    ui->label_BtimeInt2->setText(ConvertedTime.at(1));

    /* Calculate the needed minimum volume of the stock solutions */
    QVector <double> Volume(3);

    /* Minimum volume per stock solution */
    for(int l=0; l<3; l++){
        double vol = (externSoftware->minConcentrations.at(l)+externSoftware->maxConcentrations.at(l))/(externSoftware->ConfigurationFileGenerator->NumberOfSubstances);
        vol = (vol/ externSoftware->stockSolutions.at(l))*externSoftware->ConfigurationFileGenerator->NConcentrations*ui->spinBox_AbsVol->value();
        Volume.replace(l, vol);
    }

    /* Show the user how much is needed minimum */
    ui->lineEdit_VolG->setText(QString::number(Volume.at(0)));
    ui->lineEdit_VolI1->setText(QString::number(Volume.at(1)));
    ui->lineEdit_VolI2->setText(QString::number(Volume.at(2)));

    /* If there is a delay in the start, show when it's going to start then */
    if(externSoftware->ConfigurationFileGenerator->startDelay != 0){

        /* Show label when there is a delay */
        ui->label_timeLabel->show();
        ui->timeEdit_timeLabel->show();

        /* Get the actual time and add the delay time */
        startTime = QDateTime::currentDateTime().addSecs(externSoftware->ConfigurationFileGenerator->startDelay);

        /* Print it in format of h:m:s AM/PM */
        ui->timeEdit_timeLabel->setText(startTime.toString("hh:mm:ss ap"));

    }else{

        /* Hide the time label when there is not delay */
        ui->label_timeLabel->hide();
        ui->timeEdit_timeLabel->hide();
    }

    /* Set range limits */
    ui->doubleSpinBox_minW->setMaximum(ui->doubleSpinBox_maxW->value());
    ui->doubleSpinBox_maxW->setMinimum(ui->doubleSpinBox_minW->value());
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
