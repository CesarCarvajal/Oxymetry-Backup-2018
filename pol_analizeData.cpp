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
#include <QCollator>
#include <QMenu>

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

/**
 * @brief Constructor of 'Select Analize Data' class
 * @param[in] parent Parent widget
 */
selectAnalizeData::selectAnalizeData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectAnalizeData)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Create signal mapper for configuration window */
    signalMapperC = new QSignalMapper(this);

    /* Connect Button of cancel */
    connect(ui->pushButton_select, SIGNAL(clicked()), this, SLOT(allowSelectPath()));
    connect(ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->spinBox_repselec, SIGNAL(valueChanged(int)), this, SLOT(updateSelectionList()));
    connect(ui->spinBox_calSet, SIGNAL(valueChanged(int)), this, SLOT(setDataSets()));
    connect(ui->spinBox_ValSet, SIGNAL(valueChanged(int)), this, SLOT(setDataSets()));
    connect(ui->spinBox_stepsSelec, SIGNAL(valueChanged(int)), this, SLOT(selectFileSteps()));

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

    signalMapperC->setMapping(ui->radiobutton_selectData, ui->radiobutton_selectData);
    signalMapperC->setMapping(ui->radiobutton_selectSet, ui->radiobutton_selectSet);
    signalMapperC->setMapping(ui->listWidget_Calibration, ui->listWidget_Calibration);
    signalMapperC->setMapping(ui->listWidget_Validation, ui->listWidget_Validation);
    signalMapperC->setMapping(ui->label_restart, ui->label_restart);
    signalMapperC->setMapping(ui->label_switch, ui->label_switch);
    signalMapperC->setMapping(ui->checkBox_RandomSort, ui->checkBox_RandomSort);
    signalMapperC->setMapping(ui->checkBox_stepsSelec, ui->checkBox_stepsSelec);
    signalMapperC->setMapping(ui->checkBox_SelecManual, ui->checkBox_SelecManual);

    /* Connect signal mapper action */
    connect(signalMapperC, SIGNAL(mapped(QWidget *)), this, SLOT(handleClickEvent(QWidget *)));

    /* Set window flags */
    this->setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

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

    /* Hide items */
    ui->label_repselec->hide();
    ui->spinBox_repselec->hide();
    ui->checkBox_RandomSort->hide();
    ui->checkBox_stepsSelec->hide();
    ui->spinBox_stepsSelec->hide();
    ui->checkBox_SelecManual->hide();

}

/**
 * @brief Organize files in steps
 */
void selectAnalizeData::selectFileSteps(void){

    /*Set all as calibration */
    FFTFilesCalibration.append(FFTFilesValidation);
    FFTFilesValidation.clear();

    /* Sort file names */
    FFTFilesCalibration = sortFiles(FFTFilesCalibration);

    /* Create temporal lists */
    QStringList FFTFilesCalibration_Temp, FFTFilesValidation_Temp;

    /* For each position, randomly shuffle the vector and get the first position */
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
    FFTFilesCalibration = Dir.entryList(QStringList() << "*R"+QString::number(ui->spinBox_repselec->value())+".FFT",QDir::Files | QDir::NoSymLinks, QDir::Time | QDir::Reversed);

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

        /* restart repetitions */
        repetitions = 0;

        /* Empty vector */
        FFTFilesCalibration.clear();
        FFTFilesValidation.clear();

        /* Disable button to analyze */
        ui->pushButton_generate->setEnabled(false);

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

            /* Disable button to analyze */
            ui->pushButton_generate->setEnabled(true);
        }
    }
}

/**
 * @brief Add the files to the list
 */
void selectAnalizeData::addFilesToList()
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

            /* Disable button to analyze */
            ui->pushButton_generate->setEnabled(false);

            /* Clean Lists */
            cleanList();

            /* Are there repetitions */
            if(repetitions > 0){
                /* Add the FFT files to the list */
                FFTFilesCalibration = Dir.entryList(QStringList() << "*R"+QString::number(ui->spinBox_repselec->value())+".FFT",QDir::Files | QDir::NoSymLinks, QDir::Time | QDir::Reversed);
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

        /* Enable the button to analyze data */
        ui->pushButton_generate->setEnabled(!FFTFilesCalibration.isEmpty() && !FFTFilesValidation.isEmpty());
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
    /* Sort the vector */
    QCollator collator;
    collator.setNumericMode(true);

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
    for(int i = 1; i < 1000; i++){

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

    /* Enable the button to analyze data */
    ui->pushButton_generate->setEnabled(!FFTFilesCalibration.isEmpty() && !FFTFilesValidation.isEmpty());

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
 * @brief Left Click Menu
 */
void selectAnalizeData::showContextMenu(const QPoint &pos)
{
    // Handle global position
    QPoint globalPos = ui->listWidget_Calibration->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu LMenu;
    LMenu.addAction("Remove File",  this, SLOT(removeItem()));

    // Show context menu at handling position
    LMenu.exec(globalPos);

}

/**
 * @brief Destructor of 'analize data' class
 */
selectAnalizeData::~selectAnalizeData(void)
{
    delete ui;

}
