/*
 * Hemoxymetrie in non-hemolyzed human whole blood
 * Copyright (C) 2016-2017 Benjamin Redmer, ... ?
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
#include <QCollator>
#include <QMenu>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>

/* Internal includes */
#include "application.h"
#include "messages.h"
#include "spectrometer.h"
#include "timer.h"
#include "pol_analizeData.h"
#include "ui_pol_AnalizeData.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/* Needed for the PLS implementation */
//using namespace Eigen;

/**
 * @brief Constructor of 'Select Analize Data' class
 * @param[in] parent Parent widget
 *
 * In this class:   - The files for calibration and validation are selected, sorted and displayed.
 *                  - This window is loaded at the end of a measurement profile for further data analysis.
 *                  - The user selects the path folder where the FFT files are located.
 *                  - The window can be opened by the button "Analize Data" in the polarimeter tab.
 *                  - The window opens automatically after finishing a measurement profile.
 *                  - The calibration and validation files are sorted according to the selected substance.
 *                  - The 3D plots of spectra and normalized spectra are created.
 *                  - The plot of prediction and further statistics could be added further this class.
 *                  - The folder "Data_Analysis" is created and contains two files.
 *                  - The file calibration "Cal_Data.cal" contains the information for the PLSR calibration.
 *                  - The file validation "Val_Data.val" contains the information for the PLSR validation.
 *                  - A block of data as repetitions, can be used for calibration and validation too.
 *                  - Calibration and validation files can be sorted automatically or manually.
 *
 *                  GO TO THE FUNCTION ANALIZE DATA ...
 *
 */
selectAnalizeData::selectAnalizeData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectAnalizeData)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Create signal mapper for configuration window */
    signalMapperC = new QSignalMapper(this);

    /* Connect UI Buttons */
    connect(ui->pushButton_select, SIGNAL(clicked()), this, SLOT(allowSelectPath()));
    connect(ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->pushButton_Analize, SIGNAL(clicked()), this, SLOT(analizeData()));
    connect(ui->spinBox_repselec, SIGNAL(valueChanged(int)), this, SLOT(updateSelectionList()));
    connect(ui->spinBox_calSet, SIGNAL(valueChanged(int)), this, SLOT(setDataSets()));
    connect(ui->spinBox_ValSet, SIGNAL(valueChanged(int)), this, SLOT(setDataSets()));
    connect(ui->spinBox_stepsSelec, SIGNAL(valueChanged(int)), this, SLOT(selectFileSteps()));
    connect(ui->comboBox_DetSignal, SIGNAL(currentIndexChanged(int)), this, SLOT(activateLogarithm()));

    /* Connect signals */
    connect(ui->radiobutton_selectData, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->radiobutton_selectSet, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->listWidget_Calibration, SIGNAL(itemClicked(QListWidgetItem*)), signalMapperC, SLOT(map()));
    connect(ui->listWidget_Calibration, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->listWidget_Validation, SIGNAL(itemClicked(QListWidgetItem*)), signalMapperC, SLOT(map()));
    connect(ui->label_restart, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->label_switch, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_RandomSort, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_stepsSelec, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_SelecManual, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->checkBox_applyLogarithm, SIGNAL(clicked()), signalMapperC, SLOT(map()));

    /* Signal mapper */
    signalMapperC->setMapping(ui->radiobutton_selectData, ui->radiobutton_selectData);
    signalMapperC->setMapping(ui->radiobutton_selectSet, ui->radiobutton_selectSet);
    signalMapperC->setMapping(ui->listWidget_Calibration, ui->listWidget_Calibration);
    signalMapperC->setMapping(ui->listWidget_Validation, ui->listWidget_Validation);
    signalMapperC->setMapping(ui->label_restart, ui->label_restart);
    signalMapperC->setMapping(ui->label_switch, ui->label_switch);
    signalMapperC->setMapping(ui->checkBox_RandomSort, ui->checkBox_RandomSort);
    signalMapperC->setMapping(ui->checkBox_stepsSelec, ui->checkBox_stepsSelec);
    signalMapperC->setMapping(ui->checkBox_SelecManual, ui->checkBox_SelecManual);
    signalMapperC->setMapping(ui->checkBox_applyLogarithm, ui->checkBox_applyLogarithm);

    /* Connect signal mapper action */
    connect(signalMapperC, SIGNAL(mapped(QWidget *)), this, SLOT(handleClickEvent(QWidget *)));

    /* Set window flags */
    this->setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint);

    /* Set restart label color */
    ui->label_restart->setStyleSheet("QLabel { color: blue; }");
    ui->label_switch->setStyleSheet("QLabel { color: blue; }");

    /* Set repetitions in 0 */
    repetitions = 0;

    /* set maximum repetitions */
    ui->spinBox_repselec->setMaximum(1);
    ui->spinBox_calSet->setMaximum(1);
    ui->spinBox_ValSet->setMaximum(1);

    /* Assume no automatic load of data */
    automaticLoading = false;

    /* Number of measured concentrations */
    NrConcentrations = 0;

    /* Hide items */
    ui->label_repselec->hide();
    ui->spinBox_repselec->hide();
    ui->checkBox_RandomSort->hide();
    ui->checkBox_stepsSelec->hide();
    ui->spinBox_stepsSelec->hide();
    ui->checkBox_SelecManual->hide();

    /* Not canceled the window, initialize */
    canceled = false;

    /* Create the data array for the 3D spectra plot */
    data3D = new QSurfaceDataArray;
    data3DNormalized = new QSurfaceDataArray;

    /* Overall factor for plotting purposes */
    factorConcentration = 1;

}

/**
 * @brief Adjust the automatic loading of the data at the end of the measurements
 */
void selectAnalizeData::automaticAnalize(QString PathAuto){

    /* Set the automatic loading on */
    automaticLoading = true;

    /* Give the path for the files */
    pathDataM = PathAuto;

    /* Select the path from the measured data */
    selectPath();
}

/**
 * @brief Organize files in steps when selected the option
 */
void selectAnalizeData::selectFileSteps(void){

    /* Set all as calibration */
    FFTFilesCalibration.append(FFTFilesValidation);
    FFTFilesValidation.clear();

    /* Check which substance we want to analize? */
    if(ui->comboBox_Substance->currentIndex() == 0){

        /* Sort file names according to the first substance */
        FFTFilesCalibration = sortFiles(FFTFilesCalibration);
    }else{

        /* Sort file names according to the other substances order */
        FFTFilesCalibration = sortFiles2(FFTFilesCalibration);
    }

    /* Create temporal lists */
    QStringList FFTFilesCalibration_Temp, FFTFilesValidation_Temp;

    /* For each position, shuffle the vector and get the first position */
    for(int i = 0; i < FFTFilesCalibration.size(); i++){

        /* select the right positions */
        if(i % ui->spinBox_stepsSelec->value() == 0){

            /* Get the validation values */
            FFTFilesValidation_Temp.append(FFTFilesCalibration.at(i));
        }else{

            /* Get the calibration values */
            FFTFilesCalibration_Temp.append(FFTFilesCalibration.at(i));
        }
    }

    /* Save the shuffle values */
    FFTFilesValidation.append(FFTFilesValidation_Temp);
    FFTFilesCalibration.clear();
    FFTFilesCalibration.append(FFTFilesCalibration_Temp);

    /* Clean Lists */
    cleanList();
}

/**
 * @brief Update selection list of files according to the selected repetition if there are some
 */
void selectAnalizeData::updateSelectionList(void){

    /* Empty vector */
    FFTFilesCalibration.clear();
    FFTFilesValidation.clear();

    /* Clean Lists */
    cleanList();

    /* Add the FFT files to the list */
    FFTFilesCalibration = Dir.entryList(QStringList() << "*R"+QString::number(ui->spinBox_repselec->value())
                                        +".FFT",QDir::Files | QDir::NoSymLinks, QDir::Time | QDir::Reversed);

    /* Add files to the list */
    addFilesToList();

    /* Set manual change */
    ui->checkBox_SelecManual->setChecked(true);
    ui->checkBox_stepsSelec->setChecked(false);
    ui->checkBox_RandomSort->setChecked(false);
    ui->spinBox_stepsSelec->setEnabled(false);
}

/**
 * @brief Allow to the user to select path for files
 */
void selectAnalizeData::allowSelectPath(void)
{
    /* Allow the loading by hand */
    automaticLoading = false;

    /* Allow to select a path */
    selectPath();
}

/**
 * @brief Select path for files
 */
void selectAnalizeData::selectPath(void)
{
    /* The user wants to analize data */
    if(!automaticLoading){

        /* Get path of configuration file */
        pathDataM = QFileDialog::getExistingDirectory(this, tr("Open FFT Files Directory"), "", QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);
    }

    /* Is there a path? */
    if(!pathDataM.isEmpty()){

        /* Open the Folder */
        Dir = QDir(pathDataM);

        /* Check that it's not an empty folder */
        if(Dir.isEmpty()){

            /* Show message if its empty */
            showCritical("The folder is empty or doesn't exist anymore, please select a folder with FFT data", "");
            return;
        }

        /* Get the path */
        dataPath = QFileInfo(pathDataM);

        /* Restart repetitions */
        repetitions = 0;

        /* Empty vector */
        FFTFilesCalibration.clear();
        FFTFilesValidation.clear();

        /* Clean Lists */
        cleanList();

        /* Find if there are repetitions */
        findRepetitions();

        /* If there are repetitions */
        if(repetitions > 0){

            /* Add the FFT files to the list */
            FFTFilesCalibration = Dir.entryList(QStringList() << "*R1.FFT",QDir::Files | QDir::NoSymLinks, QDir::Time | QDir::Reversed);

        }else{

            /* Add the FFT files to the list */
            FFTFilesCalibration = Dir.entryList(QStringList() << "*.FFT",QDir::Files | QDir::NoSymLinks, QDir::Time | QDir::Reversed);
        }

        /* If there aren't calibration files */
        if(FFTFilesCalibration.isEmpty()){

            /* Show message if its empty */
            showCritical("No FFT data files found in this directory, please select a folder with FFT data", "");
            return;
        }

        /* Add initial files to the list */
        addFilesToList();

        /* Get the total concentrations in this measurement */
        NrConcentrations = FFTFilesCalibration.length();

        /* Read information from files */
        readInitialFile(false, pathDataM + "/" + FFTFilesCalibration.at(0));

        /* Show Ui Items */
        ui->checkBox_RandomSort->show();
        ui->checkBox_stepsSelec->show();
        ui->spinBox_stepsSelec->show();
        ui->checkBox_SelecManual->show();

        /* Set the maximum value to organize the values */
        ui->spinBox_stepsSelec->setMaximum(FFTFilesCalibration.size());

        /* If the selection of data is enabled */
        if(ui->radiobutton_selectSet->isChecked()){

            /* Add the FFT files to the list */
            setDataSets();

        }
    }
}

/**
 * @brief Read Initial file to analize, just to get some header information.
 */
void selectAnalizeData::readInitialFile(bool list, QString path)
{
    /* Just get the header information */
    if(!FFTFilesCalibration.isEmpty()){

        if(!list){
            /* Clear combo box of substances */
            ui->comboBox_Substance->clear();
        }

        /* Open the file to get the Nr of Spectra and Average Nr. */
        QFile file(path);

        /* Row of the file */
        QString ReadRow;

        /* Does the File exists? */
        if(!file.exists()){
            /* If not, tell the user that it coulnd't be found */
            showWarning("File not Found!", "");
            return;
        }

        /* Open the file */
        if(file.open(QIODevice::ReadOnly)) {

            QTextStream stream(&file);

            /* Read lines */
            while(!stream.atEnd()){

                /* Read a line from the file */
                ReadRow = stream.readLine();

                /* Read the text and get the values */
                QStringList Readed_Row = ReadRow.split(": ");

                /* Concentrations found */
                if(ReadRow.contains("Concentrations")){

                    if(!list){
                        /* Get substances names */
                        QString Substances = Readed_Row.at(1);
                        QStringList ListS = Substances.split("/");
                        ListS.removeLast();

                        /* Add substances names */
                        ui->comboBox_Substance->addItems(ListS);

                    }else{

                        /* Get subtances concentrations */
                        QString Substances = Readed_Row.at(2);
                        concentrationsList = Substances.split(",");
                    }

                    /* From here ahead just counts and other data, not needed yet */
                }else if(ReadRow.contains("Wavelength")){

                    break;
                }
            }
        }

        /* Close files */
        file.close();
    }
}

/**
 * @brief Read files to fill the plot arrays and to create the analize data files
 */
void selectAnalizeData::readFiles(void)
{

    /* Resize vector with all the file names */
    allFiles.clear();

    /* Are we using complete sets of data? */
    bool completeSet = false;

    /* Check if we have repeated values */
    for(int z =0; z < FFTFilesValidation.length(); z++){
        completeSet = FFTFilesCalibration.contains(FFTFilesValidation.at(z));

        /* If there is already one repeated, means that there is a complete set */
        if(completeSet){
            break;
        }
    }

    /* If we are using a complete set, then only add one set of files */
    if(completeSet){

        allFiles.append(FFTFilesCalibration);
    }else{
        allFiles.append(FFTFilesCalibration);
        allFiles.append(FFTFilesValidation);
    }

    /* Overall factor for plotting purposes */
    factorConcentration = 1;

    /* Create vectors with the concentrations for validation and calibration */
    CalConcentrations.resize(0);
    ValConcentrations.resize(0);

    /* Sort files appropriatelly, if the first concentration should be taken */
    if(ui->comboBox_Substance->currentIndex() == 0){
        allFiles = sortFiles(allFiles);

    }else{

        /* Different substance sort */
        allFiles = sortFiles2(allFiles);
    }

    /* Restart vectors */
    ConcentrationsPlot.resize(0);
    AverageDetSignal.resize(0);
    ConcentrationPredictionDeviationVector.resize(0);
    MrNumber.resize(0);
    CountsMeanDifferences.resize(0);

    /* Get the average of the actual determination signal */
    double AverageDetSignalT;

    /* Iterate through the file names */
    for(int index = 0; index < allFiles.length(); index++){

        /* Read the concentration from the files */
        readInitialFile(true, pathDataM + "/" + allFiles.at(index));

        /* Get the file name to get the measurement number */
        QString fileName = allFiles.at(index);

        if(FFTFilesValidation.contains(fileName)){
            /* Remove other information in the file name */
            fileName = fileName.remove(0,fileName.lastIndexOf("Hz_")+3);

            /* Check if it's a repetition */
            if(fileName.contains("_R")){

                /* Remove the values */
                fileName = fileName.remove(fileName.lastIndexOf("_R"), fileName.length()-fileName.lastIndexOf("_R"));

            }
            /* If it's not a repetition then remove the file extension */
            else{

                /* Get the measurement number */
                fileName = fileName.remove(".FFT");
            }

            /* Save the measurement number */
            MrNumber.append(fileName.toInt());
        }

        /* This vector saves the information per file or per concentration */
        signal.resize(0);

        /* Restart the average value */
        AverageDetSignalT = 0;

        /* Open the file to get the Nr of Spectra and Average Nr. */
        QFile file(pathDataM + "/" + allFiles.at(index));

        /* Row of the file */
        QString ReadRow;

        /* Does the File exists? */
        if(!file.exists()){
            /* If not, tell the user that it coulnd't be found */
            showWarning("File not Found!", "");
            return;
        }

        /* Open the file */
        if(file.open(QIODevice::ReadOnly)) {

            /* Read file */
            QTextStream stream(&file);

            /* Read lines */
            while(!stream.atEnd()){

                /* When should it start reading the FFT data? */
                bool read = false;

                /* Read a line from the file */
                ReadRow = stream.readLine();

                /* Indicates where to start reading the numerical information from file */
                QString in = ReadRow.at(1);

                /* If a number was found at the first position, then start reading */
                in.toInt(&read);

                /* start reading numbers */
                if(read){

                    /* Get the values from the line separated by 2 tabulars and replace (,) by (.) to read numbers */
                    QStringList Readed_Row = ReadRow.split("\t\t");
                    Readed_Row.replaceInStrings(",",".");

                    /* We don't need all the saved values */
                    if(Readed_Row.at(0).toDouble() > ui->doubleSpinBox_maxWavel->value()){break;}
                    if(Readed_Row.at(0).toDouble() < ui->doubleSpinBox_minWavel->value()){continue;}

                    /* Save the wavelengths in Position 0 */
                    if(index < 1){
                        wavelengths.append(Readed_Row.at(0).toDouble());
                    }

                    /* 4th column is the ratio */
                    if(ui->comboBox_DetSignal->currentIndex() == 0){
                        signal.append(Readed_Row.at(4).toDouble());
                    }

                    /* 2nd column is I(w) */
                    if(ui->comboBox_DetSignal->currentIndex() == 1){
                        signal.append(Readed_Row.at(2).toDouble());
                    }

                    /* 3rd column is I(2w) */
                    if(ui->comboBox_DetSignal->currentIndex() == 2){
                        double data2W = Readed_Row.at(3).toDouble();

                        /* Use the logarithm with I(2W) */
                        if(ui->checkBox_applyLogarithm->isChecked()){
                            data2W = log10(data2W);
                        }
                        /* Add the signal to the plot */
                        signal.append(data2W);
                    }

                    /* 1st column is I(DC) */
                    if(ui->comboBox_DetSignal->currentIndex() == 3){
                        signal.append(Readed_Row.at(1).toDouble());
                    }
                }
            }
        }

        /* Rows of 3D plots */
        QSurfaceDataRow *newRow = new QSurfaceDataRow(wavelengths.length());
        QSurfaceDataRow *newRow_norm = new QSurfaceDataRow(wavelengths.length());

        /* Get the data for the 3D plot - Spectra */
        for (int j = 0; j < wavelengths.length(); j++)

            (*newRow)[j].setPosition(QVector3D(wavelengths.at(j), signal.at(j),
                                               QString(concentrationsList.at(ui->comboBox_Substance->currentIndex())).toDouble()));
        /* All information for the 3D plot */
        *data3D << newRow;

        /* Get the data for the 3D plot - Normalized spectra */
        for (int j = 0; j < wavelengths.length(); j++)
            (*newRow_norm)[j].setPosition(QVector3D(wavelengths.at(j), signal.at(j)/(data3D->at(0)->at(j).y()),
                                                    QString(concentrationsList.at(ui->comboBox_Substance->currentIndex())).toDouble()));

        /* All information for the 3D plot */
        *data3DNormalized << newRow_norm;

        /* Fill the lists of calibration or validation data */
        if(FFTFilesCalibration.indexOf(allFiles.at(index))!=-1){
            CalConcentrations.append(QString(concentrationsList.at(ui->comboBox_Substance->currentIndex())).toDouble());
        }
        if(FFTFilesValidation.indexOf(allFiles.at(index))!=-1){
            ValConcentrations.append(QString(concentrationsList.at(ui->comboBox_Substance->currentIndex())).toDouble());
        } /*else (the file was removed by the user) */

        /* Calculate the average of the determination signal */
        for(int k=0; k < signal.length(); k++){
            AverageDetSignalT = AverageDetSignalT + signal.at(k);
        }

        double average = AverageDetSignalT/signal.length();

        /* Added the plot vector */
        AverageDetSignal.append(average);
        ConcentrationsPlot.append(QString(concentrationsList.at(ui->comboBox_Substance->currentIndex())).toDouble());

        /* Restart the vector */
        concentrationsList.clear();

    }

    /* Is there any repetition to correct the measurement number? */
    int minMrNumber = *std::min_element(MrNumber.begin(), MrNumber.end());

    /* Check if it is a repetition */
    if(minMrNumber > NrConcentrations){

        /* Which repetition was that? */
        int repeated = minMrNumber/NrConcentrations;

        /* Substract the differentce */
        for(int l =0; l < MrNumber.length(); l++){

            /* This gives the measurement number always from 1 to the maximum amount of measured concentrations */
            MrNumber.replace(l, MrNumber.at(l)-(NrConcentrations*repeated));
        }
    }

    /* Get the maximum concentration and check if its not aorund 100 to 1000, problems with Qt */
    if(data3D->last()->at(0).z() <= 1){

        /* If the added impurity concentration is less than 1, then multiply by 1000, units of x10^-3 */
        factorConcentration = 1000;

    }else if(data3D->last()->at(0).z() > 1 && data3D->last()->at(0).z() < 10){

        /* If the added impurity concentration is less than 1, then multiply by 100, units of x10^-2 */
        factorConcentration = 100;

    }else if(data3D->last()->at(0).z() > 10 && data3D->last()->at(0).z() < 100){

        /* If the added impurity concentration is less than 100, then multiply by 100, units of x10^-1 */
        factorConcentration = 10;
    }

    /* Was it necessary to adjust the plot units? For plotting purposes */
    if(factorConcentration > 1){

        /* Then replace the very small concentrations for the same multiplied by the plot factor */
        for(int k = 0; k < allFiles.length(); k++){

            /* Create new rows */
            QSurfaceDataRow *newRow = new QSurfaceDataRow(wavelengths.length());
            QSurfaceDataRow *newRow_norm = new QSurfaceDataRow(wavelengths.length());

            /* Replace the rows in the data Spectra */
            for(int m = 0; m < wavelengths.length(); m++){
                (*newRow)[m].setPosition(QVector3D(data3D->at(k)->at(m).x(), data3D->at(k)->at(m).y(), data3D->at(k)->at(m).z()*factorConcentration));
            }
            data3D->replace(k, newRow);

            /* Replace the rows in the data Normalized Spectra */
            for(int m = 0; m < wavelengths.length(); m++){
                (*newRow_norm)[m].setPosition(QVector3D(data3DNormalized ->at(k)->at(m).x(), data3DNormalized ->at(k)->at(m).y(), data3DNormalized->at(k)->at(m).z()*factorConcentration));
            }
            data3DNormalized ->replace(k, newRow_norm);
        }
    }
}

/**
 * @brief Add the files to the list
 */
void selectAnalizeData::addFilesToList(void)
{
    /* Sort Files */
    FFTFilesCalibration = sortFiles(FFTFilesCalibration);

    /* Add items to the list */
    ui->listWidget_Calibration->addItems(FFTFilesCalibration);

    /* Show current working path */
    ui->lineEdit_currentDataPath->setText(dataPath.absoluteFilePath());
}

/**
 * @brief Called if a widget option was clicked,
 *        e.g. Integration time label.
 * @param widget Widget which has been clicked
 */
void selectAnalizeData::handleClickEvent(QWidget *widget)
{
    /* Cast the events */
    QRadioButton *radioBox = qobject_cast<QRadioButton *>(widget);
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(widget);
    QListWidget *listItem = qobject_cast<QListWidget *>(widget);
    QLabel *label = qobject_cast<QLabel *>(widget);

    /* Enable the type of data selection */
    ui->SelectFiles->setEnabled(ui->radiobutton_selectData->isChecked());
    ui->SelectSet->setEnabled(ui->radiobutton_selectSet->isChecked());

    /* Check which option is active */
    if(radioBox == ui->radiobutton_selectData){

        /* Set manual change */
        ui->checkBox_SelecManual->setChecked(true);
        ui->checkBox_stepsSelec->setChecked(false);
        ui->checkBox_RandomSort->setChecked(false);
        ui->spinBox_stepsSelec->setEnabled(false);

        /* If there is an existing data path then add the data to the lists */
        if(dataPath.exists()){

            /* Empty vector */
            FFTFilesCalibration.clear();
            FFTFilesValidation.clear();

            /* Clean Lists */
            cleanList();

            /* Are there repetitions */
            if(repetitions > 0){
                /* Add the FFT files to the list */
                FFTFilesCalibration = Dir.entryList(QStringList() << "*R"+QString::number(ui->spinBox_repselec->value())
                                                    +".FFT",QDir::Files | QDir::NoSymLinks, QDir::Time | QDir::Reversed);
            }else{
                /* Add the FFT files to the list */
                FFTFilesCalibration = Dir.entryList(QStringList() << "*.FFT",QDir::Files | QDir::NoSymLinks, QDir::Time | QDir::Reversed);
            }

            /* Add initial files to the list */
            addFilesToList();
        }
    }

    /* Check which option is active */
    if(radioBox == ui->radiobutton_selectSet){

        /* Empty vector */
        FFTFilesCalibration.clear();
        FFTFilesValidation.clear();

        /* Choose data sets for the calibration and validation */
        setDataSets();

    }

    /* Click in the calibration or validation list */
    if(listItem == ui->listWidget_Calibration || listItem == ui->listWidget_Validation || label == ui->label_restart || label == ui->label_switch){

        /* User clicks one file in the calibration list */
        if(listItem == ui->listWidget_Calibration && ui->checkBox_SelecManual->isChecked()){

            /* Add to the other list the selected files */
            FFTFilesValidation.append(ui->listWidget_Calibration->selectedItems().at(0)->text());
            FFTFilesCalibration.removeAt(FFTFilesCalibration.indexOf(ui->listWidget_Calibration->selectedItems().at(0)->text()));
        }

        /* User clicks one file in the validation list */
        else if(listItem == ui->listWidget_Validation && ui->checkBox_SelecManual->isChecked()){

            /* Add to the other list the selected files */
            FFTFilesCalibration.append(ui->listWidget_Validation->selectedItems().at(0)->text());
            FFTFilesValidation.removeAt(FFTFilesValidation.indexOf(ui->listWidget_Validation->selectedItems().at(0)->text()));
        }

        /* Set all files as calibration */
        if(label == ui->label_restart){

            /*Set all as calibration */
            automaticLoading = true;

            /* Load data with the known path */
            selectPath();

            /* If there is more than 1 data set */
            if(repetitions > 1){

                /* Update the selection list */
                updateSelectionList();
            }

            /* Set falg to false again */
            automaticLoading = false;

            /* Restart the automatic selection options */
            ui->checkBox_RandomSort->setChecked(false);
            ui->checkBox_stepsSelec->setChecked(false);
        }

        /* Switch files from calibration to validation */
        if(label == ui->label_switch){

            /* Save vectors temporarly */
            QStringList FFTFilesCalibration_Temp, FFTFilesValidation_Temp;

            /* Get actual values */
            FFTFilesCalibration_Temp = FFTFilesValidation;
            FFTFilesValidation_Temp = FFTFilesCalibration;

            /*Set all as calibration */
            FFTFilesCalibration.clear();
            FFTFilesValidation.clear();

            /* Switch vectors */
            FFTFilesCalibration.append(FFTFilesCalibration_Temp);
            FFTFilesValidation.append(FFTFilesValidation_Temp);

        }

        /* Clean Lists */
        cleanList();
    }

    /* The user wants to select random files */
    if(checkBox == ui->checkBox_RandomSort){

        /* Disable spin roll */
        ui->spinBox_stepsSelec->setEnabled(false);
        ui->checkBox_stepsSelec->setChecked(false);
        ui->checkBox_SelecManual->setChecked(false);

        /* The random selection option was checked */
        if(ui->checkBox_RandomSort->isChecked()){

            /*Set all as calibration */
            FFTFilesCalibration.append(FFTFilesValidation);
            FFTFilesValidation.clear();

            /* Get the total amount of files */
            int size = floor(FFTFilesCalibration.size()/2);

            /* For each position, randomly shuffle the vector and get the first position */
            for(int i = 0; i < size; i++){

                /* Shuffle the vector */
                std::random_shuffle(FFTFilesCalibration.begin(), FFTFilesCalibration.end());

                /* Get the first value each time it shuffles */
                FFTFilesValidation.append(FFTFilesCalibration.at(0));
                FFTFilesCalibration.removeAt(0);
            }

            /* Clean Lists */
            cleanList();
        }
    }

    /* The user wants to select random files */
    if(checkBox == ui->checkBox_stepsSelec){

        /* Disable spin roll */
        ui->spinBox_stepsSelec->setEnabled(ui->checkBox_stepsSelec->isChecked());
        ui->checkBox_RandomSort->setChecked(false);
        ui->checkBox_SelecManual->setChecked(false);

        /* Add files */
        selectFileSteps();
    }

    /* Always choose manual selection if there is no option selected by the user */
    if(!ui->checkBox_RandomSort->isChecked() && !ui->checkBox_stepsSelec->isChecked()){

        /* Check the manual selection on */
        ui->checkBox_SelecManual->setChecked(true);
    }

    /* The user wants to select random files */
    if(checkBox == ui->checkBox_SelecManual){

        /* Disable spin roll */
        ui->spinBox_stepsSelec->setEnabled(false);
        ui->checkBox_RandomSort->setChecked(false);
        ui->checkBox_stepsSelec->setChecked(false);
    }
}

/**
 * @brief Sort the list with the files names
 * in: Qstring List to be sorted
 * out: Sorted list
 */
QStringList selectAnalizeData::sortFiles(QStringList List)
{
    /* Set the sort criteria */
    QCollator collator;
    collator.setNumericMode(true);

    /* Sort the vector */
    std::sort(
                List.begin(),
                List.end(),
                [&collator](const QString &file1, const QString &file2)
    {
        return collator.compare(file1, file2) < 0;
    });

    return List;

}

/**
 * @brief Sort the list with the files names acording to the substance
 * in: Qstring List to be sorted
 * out: Sorted list
 */
QStringList selectAnalizeData::sortFiles2(QStringList List)
{
    /* Create a temporal list */
    QStringList temp;

    /* Needed to organize the data according to the files */
    for(int remover = 0; remover < List.length(); remover++){

        /* Get the file name */
        QString name = List.at(remover);

        /* Iterate in the substances to find the right one */
        for(int k =0; k < ui->comboBox_Substance->currentIndex(); k++){

            /* Remove other substances from the name */
            name.remove(0,name.indexOf("C")+3);
        }

        /* Save the names of the substances */
        temp.append(name);
    }

    /* Sort the temporal file list of substances */
    temp = sortFiles(temp);

    /* Save the sorted names in a new list */
    QStringList sorted;

    /* Iterate to find them */
    for(int i = 0; i < temp.length(); i++){
        for(int sorter = 0; sorter < List.length(); sorter++){

            /* When the original list finds a match with the sort criteria then add it to the sorted list */
            if(QString(List.at(sorter)).contains(temp.at(i))){

                /* Add the right order according to the substances */
                sorted.append(List.at(sorter));
            }
        }
    }

    /* return the files sorted according to the selected susbtance */
    return sorted;
}

/**
 * @brief Set sets of data as calibration or validation
 */
void selectAnalizeData::setDataSets(void)
{
    /* If there is an existing data path then add the data to the lists */
    if(dataPath.exists()){

        /* Are there more repetitions */
        if(repetitions > 0){
            /* Add the FFT files to the list */
            FFTFilesCalibration = Dir.entryList(QStringList() << "*R"+QString::number(ui->spinBox_calSet->value())+".FFT",QDir::Files | QDir::NoSymLinks, QDir::Time | QDir::Reversed);

            /* Sort file names */
            FFTFilesCalibration = sortFiles(FFTFilesCalibration);

            /* Add the FFT files to the list */
            FFTFilesValidation = Dir.entryList(QStringList() << "*R"+QString::number(ui->spinBox_ValSet->value())+".FFT",QDir::Files | QDir::NoSymLinks, QDir::Time | QDir::Reversed);

            /* Sort file names */
            FFTFilesValidation = sortFiles(FFTFilesValidation);

        }else{

            /* Add the FFT files to the list */
            FFTFilesCalibration = Dir.entryList(QStringList() << "*.FFT",QDir::Files | QDir::NoSymLinks, QDir::Time | QDir::Reversed);

            /* Sort file names */
            FFTFilesCalibration = sortFiles(FFTFilesCalibration);

            /* Add the FFT files to the list */
            FFTFilesValidation = FFTFilesCalibration;
        }
    }
}

/**
 * @brief Find Repetitions
 */
void selectAnalizeData::findRepetitions(void)
{
    /* How many repetitions are there? */
    for(int i = 1; i < 100; i++){

        /* Are there R1? */
        QStringList R1 = Dir.entryList(QStringList() << "*R"+QString::number(i)+".FFT",QDir::Files | QDir::NoSymLinks);

        /* Count how many repetitions are in the folder */
        if(R1.isEmpty()){break;}else{ repetitions = repetitions + 1;}

    }

    /* No repetitions found */
    if(repetitions == 0){

        /* Set repetitions */
        repetitions = 0;

        /* set maximum repetitions */
        ui->spinBox_repselec->setMaximum(1);
        ui->spinBox_repselec->setValue(1);
        ui->spinBox_calSet->setMaximum(1);
        ui->spinBox_calSet->setValue(1);
        ui->spinBox_ValSet->setMaximum(1);
        ui->spinBox_ValSet->setValue(1);

        /* Hide items */
        ui->label_repselec->hide();
        ui->spinBox_repselec->hide();

    }else{

        /* Show items */
        ui->label_repselec->show();
        ui->spinBox_repselec->show();

        /* set maximum repetitions */
        ui->spinBox_repselec->setMaximum(repetitions);
        ui->spinBox_calSet->setMaximum(repetitions);
        ui->spinBox_ValSet->setMaximum(repetitions);
    }
}

/**
 * @brief Loading a configuration has been canceled
 */
void selectAnalizeData::cancel(void)
{

    /* Save it was canceled */
    canceled = true;

    /* Close dialog */
    reject();
}

/**
 * @brief Clean the lists
 */
void selectAnalizeData::cleanList(void){

    /* Disconnect the signal temporarly to refresh the list */
    disconnect(ui->listWidget_Calibration, SIGNAL(itemClicked(QListWidgetItem*)), signalMapperC, SLOT(map()));
    disconnect(ui->listWidget_Validation, SIGNAL(itemClicked(QListWidgetItem*)), signalMapperC, SLOT(map()));
    disconnect(ui->listWidget_Calibration, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    /* Clear the list */
    ui->listWidget_Calibration->clear();
    ui->listWidget_Validation->clear();

    /* Sort lists */
    if(!FFTFilesCalibration.isEmpty()){
        FFTFilesCalibration = sortFiles(FFTFilesCalibration);
        FFTFilesValidation = sortFiles(FFTFilesValidation);
    }

    /* Add the new items for calibration */
    ui->listWidget_Calibration->addItems(FFTFilesCalibration);

    /* Add the new items for validation */
    ui->listWidget_Validation->addItems(FFTFilesValidation);

    /* Connecta again the signal */
    connect(ui->listWidget_Calibration, SIGNAL(itemClicked(QListWidgetItem*)), signalMapperC, SLOT(map()));
    connect(ui->listWidget_Validation, SIGNAL(itemClicked(QListWidgetItem*)), signalMapperC, SLOT(map()));
    connect(ui->listWidget_Calibration, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

}

/**
 * @brief Remove the item
 */
void selectAnalizeData::removeItem(void){

    /* If it has data */
    if(!FFTFilesCalibration.isEmpty()){

        /* Add to the other list the selected files */
        FFTFilesCalibration.removeAt(FFTFilesCalibration.indexOf(ui->listWidget_Calibration->selectedItems().at(0)->text()));

        /* Clean Lists */
        cleanList();
    }

}

/**
 * @brief Left Click Menu in lists
 */
void selectAnalizeData::showContextMenu(const QPoint &pos)
{
    /* Handle global position */
    QPoint globalPos = ui->listWidget_Calibration->mapToGlobal(pos);

    /* Create menu and insert some actions */
    QMenu LMenu;
    LMenu.addAction("Remove File",  this, SLOT(removeItem()));

    /* Show context menu at handling position */
    LMenu.exec(globalPos);

}

/**
 * @brief Automatically activate logarithm when the selected signal is I(2W)
 */
void selectAnalizeData::activateLogarithm(void){

    /* Select or deselect the option automatically */
    ui->comboBox_DetSignal->currentIndex() == 2 ? ui->checkBox_applyLogarithm->setChecked(true) : ui->checkBox_applyLogarithm->setChecked(false);

}

/**
 * @brief Analize data from the files
 */
void selectAnalizeData::analizeData(void){

    /* After pressing the button of Analize, this function checks if there are files to open */
    if(!FFTFilesCalibration.isEmpty() && !FFTFilesValidation.isEmpty()){

        /* Yes. Get the FFT data from the .FFT files */
        if(!FFTFilesCalibration.isEmpty()){

            /* Resize reading vectors */
            wavelengths.resize(0);
            signal.resize(0);
            data3D = new QSurfaceDataArray;
            data3DNormalized = new QSurfaceDataArray;

            /* Create Folder to store the data analysis results, in this folder the files .cal and .val can be found. This folder is created in the same folder than the .FFT files are located */
            QDir(pathDataM).mkdir("Data_Analysis");

            /* Read Files data -> Complex function, for more details floow the code lines to it */
            readFiles();
        }

        /* Write calibration and validation files. The .cal and .val files are created according to what the user decided for both. */
        writeCalValFiles();

        /* ----- CONTINUE ----- */

        // The vector "PredictedConcentrationsVector" should be created in this class. It will save all the predicted values of the substance concentrations.

        // Create a function to read the data from the .cal and .val files. -> Depends on the PLSR library: The .dat files might be needed, depends in the library.

        // Once the information is available as needed for the PLS, a vector? a matrix (observe that it might be a matrix of 1500 x Nr of concentrations usually 51)? a file? how does the PLS need the data?

        // Create here a function that calls the PLS regression
        // This function should haveinside variables that save the values:
        // [PLS.Xloadings,PLS.Yloadings,PLS.Xscores,PLS.Yscores,PLS.betaPLS,PLS.PctVar,PLS.mse,PLS.stats] = plsregress(cal.counts',cal.conc,adjust.optimum_PLS_komponenten);

        // Note that here the extracted function of matlab requires a bit more of work...
        // The variable cal.counts is the counts comming from the .cal file
        // The variable cal.conc are in the vector CalConcentrations or can be also read from the .cal file.
        // TAKE EXTREME CARE OF THE SORTING OF THE VECTORS! THAT REQUIRES A BIT OF THINKING BEFORE USING THE VARIABLES.
        // The variable adjust.optimum_PLS_komponenten can be given by the user in the UI with the spin box: spinBox_PLSComponents

        // return here the SEP, the R2 and some other parameters that could be still ploted -- MORE INFO ASK CHRISTIAN: THIS PART REQUIRES MORE DEEP KNOWLEDGE OF THE PROJECT.

        // The variable SEP will replace what i simulate as the double variable "PredictionSEP".

        // FROM HERE AHEAD THE PROGRAMMER CAN MAKE FREE USE OF THE INFORMATION. FOLLOW SIMILAR PLOTS FOR GETTING THE IDEA.

        // DON'T FORGET TO READ THE SECTION "HELP" IN THE UI FOR MORE INFORMATION.

        // REMEBER: LEARNING THE CODE AND 1 YEAR WORK OF SOMEONE ELSE MIGHT REQUIRE SOME PATIENCE AND GOOD LOGICAL SKILLS!

        // GOOD LUCK, AND CONTACT ME IN CASE THAT IT BECOMES TOO DIFICULT, REMEMBER THAT IT MIGHT TAKE ME ONLY A MINUTE TO UNDERSTAND WHAT COULD BE GIVING YOU SEVERAL HOURS OF PROBLEMS :)

        /*  ----- END --------- */

        /* How much is the deviation of the predicted values with the validation concentrations? */
        for(int h = 0; h < ValConcentrations.length(); h++){

            //*********** Here the expression '(ValConcentrations.at(h) - 1)' will be replaced by the actual predicted values vector from the PLS *//

            /* This value will be the measured SEP - simulated CHANGE HERE THE SEP */
            double PredictionSEP = ValConcentrations.at(h) + ((((qrand() % 10)*(pow((-1),(qrand() % 2)))))*(0.001*(*std::max_element(ValConcentrations.begin(), ValConcentrations.end()))));

            /* Calculate the deviation of the prediction with the validation concentrations */
            ConcentrationPredictionDeviationVector.append(ValConcentrations.at(h) - PredictionSEP);  // Simulate the predicted values with an SEP of 1 mg/dl
        }

        /* Calculate the Counts deviation from the counts mean */
        double allSpektra = 0;
        QVector<double> allSpectraVectorMean;
        allSpectraVectorMean.resize(0);

        /* Get the all spectrum average */
        for(int k = 0; k < wavelengths.length(); k++){
            for(int i=0; i < allFiles.length(); i++){

                /* Sum up all the counts pero wavelength per concentration */
                allSpektra = allSpektra + data3D->at(i)->at(k).y();
            }

            /* Get the mean of all the spectrum */
            allSpectraVectorMean.append(allSpektra/allFiles.length());

            /* Restart the sum variable */
            allSpektra=0;
        }

        /* Calculate the counts deviation mean */
        double CountsDeviationFromMean=0;

        /* Select the concentration in the validation list only */
        bool addConcentrationCounts = false;

        /* Save the index in the general data */
        int indexConcentration = -1;

        /* Get the counts per wavelength per concentration to perform the difference */
        for(int j=0; j < ValConcentrations.length(); j++){

            /* Because QT can not handle comparisson between double, then this long process should be done to check if the current concentration belongs to the validation */
            for(int in = 0; in < allFiles.length(); in++){

                /* Get the actual concentration in the large data list */
                double concentration = data3D->at(in)->at(0).z()/factorConcentration;

                /* Is the actual concentration in the validation concentrations vector? */
                double compare = (ValConcentrations.at(j) - concentration) < 0 ? (ValConcentrations.at(j) - concentration)*(-1):(ValConcentrations.at(j) - concentration);
                if(compare < 0.0001){

                    addConcentrationCounts = true;
                    indexConcentration = in;
                    break;
                }
            }

            /* This concentration in the validation is needed then */
            if(addConcentrationCounts){

                /* For each concentration get the count deviation from mean counts */
                CountsDeviationFromMean=0;

                /* Run along the wavelengths */
                for(int k = 0; k < wavelengths.length(); k++){

                    /* Sum up all the counts per wavelength per concentration */
                    CountsDeviationFromMean = CountsDeviationFromMean + (allSpectraVectorMean.at(k)-data3D->at(indexConcentration)->at(k).y());
                }

                /* Get the mean counts deviation from the average counts value */
                CountsMeanDifferences.append(CountsDeviationFromMean/wavelengths.length());

                /* Restart the index */
                indexConcentration = -1;
            }

            /* Don't add any concentration to the list, just those in the validation */
            addConcentrationCounts = false;
        }

        /* Close the dialog */
        accept();

    }else{

        /* Analysis can't be performed */
        showCritical("Please first select the measurement data.  Then, divide the file names in calibration and validation for further data analysis.","No files were selected as calibration and validation. \n Select files for calibration "
                                                                                                                                                       "and validation.");
    }
}

/**
 * @brief Create the files with the calibration and validation data
 */
void selectAnalizeData::writeCalValFiles(void){

    /* Create the path for the files */
    QString pathCal(pathDataM + "/Data_Analysis/" + "/Cal_Data.cal");
    QString pathCalCounts(pathDataM + "/Data_Analysis/" + "/Cal_Counts.dat");
    QString pathCalConcentrations(pathDataM + "/Data_Analysis/" + "/Cal_Concentrations.dat");
    QString pathVal(pathDataM + "/Data_Analysis/" + "/Val_Data.val");

    /* Save the calibration data to files */
    FILE *Calfile = fopen(pathCal.toLatin1().data(), "wt");
    FILE *Valfile = fopen(pathVal.toLatin1().data(), "wt");
    FILE *CalfileCounts = fopen(pathCalCounts.toLatin1().data(), "wt");
    FILE *CalfileConcentrations = fopen(pathCalConcentrations.toLatin1().data(), "wt");

    /* Check file handle */
    if (nullptr == Calfile || nullptr == Valfile){
        return;
    }

    /* Write some useful data on file */
    fprintf(Calfile, "CALIBRATION DATA \n");
    fprintf(Calfile, "Substance: %s \n", ui->comboBox_Substance->currentText().toLatin1().data());
    fprintf(Calfile, "Determination Signal: %s \n", ui->comboBox_DetSignal->currentText().toLatin1().data());
    fprintf(Calfile, "Minimum Wavelength: %.2f \n", ui->doubleSpinBox_minWavel->value());
    fprintf(Calfile, "Maximum Wavelength: %.2f \n", ui->doubleSpinBox_maxWavel->value());
    fprintf(Calfile, "Logarithm: %i \n\n", ui->checkBox_applyLogarithm->isChecked());

    /* Write some useful data on file */
    fprintf(Valfile, "VALIDATION DATA \n");
    fprintf(Valfile, "Substance: %s \n", ui->comboBox_Substance->currentText().toLatin1().data());
    fprintf(Valfile, "Determination Signal: %s \n", ui->comboBox_DetSignal->currentText().toLatin1().data());
    fprintf(Valfile, "Minimum Wavelength: %.2f \n", ui->doubleSpinBox_minWavel->value());
    fprintf(Valfile, "Maximum Wavelength: %.2f \n", ui->doubleSpinBox_maxWavel->value());
    fprintf(Valfile, "Logarithm: %i \n\n", ui->checkBox_applyLogarithm->isChecked());

    /* Write concentrations for the data for Cal File */
    fprintf(Calfile, "Concentrations:\t");
    for(int j = 0; j < CalConcentrations.length(); j++){
        fprintf(Calfile, "%.2f\t", CalConcentrations.at(j));

        /* Is that the last value? */
        if(j+1 >= CalConcentrations.length()){
            fprintf(CalfileConcentrations, "%.2f", CalConcentrations.at(j));
        }else{
            /* Don't print an empty row at the end */
            fprintf(CalfileConcentrations, "%.2f\n", CalConcentrations.at(j));
        }
    }

    /* Close the concentrations file */
    fclose(CalfileConcentrations);
    CalfileConcentrations = nullptr;

    /* Write space and wavelength titles for Cal File */
    fprintf(Calfile, "\n");

    /* Add if the logarithm was used */
    if(ui->checkBox_applyLogarithm->isChecked()){
        fprintf(Calfile, "\nWavelength:\tIntensity ln(%s): \n\n", ui->comboBox_DetSignal->currentText().toLatin1().data());
    }else{
        fprintf(Calfile, "\nWavelength:\tIntensity %s: \n\n", ui->comboBox_DetSignal->currentText().toLatin1().data());
    }

    /* Write concentrations for the data for Val File */
    fprintf(Valfile, "Concentrations:\t");
    for(int j = 0; j < ValConcentrations.length(); j++){
        fprintf(Valfile, "%.2f\t", ValConcentrations.at(j));
    }
    /* Write space and wavelength titles for Cal File */
    fprintf(Calfile, "\n");

    /* Add if the logarithm was used */
    if(ui->checkBox_applyLogarithm->isChecked()){
        fprintf(Valfile, "\nWavelength:\tIntensity ln(%s): \n\n", ui->comboBox_DetSignal->currentText().toLatin1().data());
    }else{
        fprintf(Valfile, "\nWavelength:\tIntensity %s: \n\n", ui->comboBox_DetSignal->currentText().toLatin1().data());
    }

    /* Iterate through the rows of the data */
    for(int m = 0; m < wavelengths.length(); m++){

        fprintf(Calfile, "%.4f\t", wavelengths.at(m));
        fprintf(Valfile, "%.4f\t", wavelengths.at(m));

        /* Iterate through the (x, y, z) positions to get the information */
        for(int k = 0; k < allFiles.length(); k++){

            /* Get the actual concentration and intensity for each wavelength */
            double concentration =data3D->at(k)->at(0).z()/factorConcentration;
            double intensity =  data3D->at(k)->at(m).y();

            /* Because QT can not handle comparisson between double, then this long process should be done */
            for(int in = 0; in < CalConcentrations.length(); in++){
                /* Is the actual concentration in the calibration concentrations vector? */
                double compare = (CalConcentrations.at(in) - concentration) < 0 ? (CalConcentrations.at(in) - concentration)*(-1):(CalConcentrations.at(in) - concentration);
                if(compare < 0.0001){
                    /* Added to the calibration file */
                    fprintf(Calfile, "%.4f\t", intensity);
                    fprintf(CalfileCounts, "%.4f\t", intensity);
                    break;
                }
            }

            /* Because QT can not handle comparisson between double, then this long process should be done */
            for(int in = 0; in < ValConcentrations.length(); in++){
                /* Is the actual concentration in the validation concentrations vector? */
                double compare = (ValConcentrations.at(in) - concentration) < 0 ? (ValConcentrations.at(in) - concentration)*(-1):(ValConcentrations.at(in) - concentration);
                if(compare < 0.0001){
                    /* Added to the validation file */
                    fprintf(Valfile, "%.4f\t", intensity);
                    break;
                }
            }
        }

        /* Don't print an empty row at the end */
        if(m+1 != wavelengths.length()){
            fprintf(Calfile, "\n");
            fprintf(CalfileCounts, "\n");
            fprintf(Valfile, "\n");
        }

    }

    /* Close the files */
    fclose(Calfile);
    fclose(Valfile);
    fclose(CalfileCounts);

    /* Free pointers */
    Calfile = nullptr;
    Valfile = nullptr;
    CalfileCounts = nullptr;
}

/**
 * @brief Destructor of 'analize data' class
 */
selectAnalizeData::~selectAnalizeData(void)
{
    delete ui;

}
