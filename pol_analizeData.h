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

#ifndef POL_ANALIZEDATA_H
#define POL_ANALIZEDATA_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QSignalMapper>
#include <QFileInfo>
#include <QDir>
#include <QtDataVisualization>

/* Qwt library */
#include "qwt_plot_curve.h"

using namespace QtDataVisualization;

/* Header of Analize Data Object */

namespace Ui {
class selectAnalizeData;
}

/**
 * @brief The 'Analize data' class
 */
class selectAnalizeData : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit selectAnalizeData(QWidget *parent = 0);

    /* User interface */
    Ui::selectAnalizeData *ui;

    /* Is this an automatic load after the measurements? */
    bool automaticLoading;

    /* Data path */
    QString pathDataM;

    /* Data for 3D plots */
    QSurfaceDataArray *data3D, *data3DNormalized;

    /* Save the current concentrations readed from file (temporal) */
    QStringList concentrationsList;

    /* Window canceled */
    bool canceled;

    /* Overall factor for plotting purposes */
    int factorConcentration;

    /* Intensity vs concentration plot information */
    QVector<double> AverageDetSignal;
    QVector<double> ConcentrationsPlot;

    /* Deviation vs measurement number plot information */
    QVector<double> ConcentrationPredictionDeviationVector;
    QVector<double> MrNumber, CountsMeanDifferences;

    /* Validation concentrations */
    QVector<double> ValConcentrations;

private:

    /* Own signal mapper for buttons and labels in configuration window */
    QSignalMapper *signalMapperC;

    /* File information for saving data of measurements */
    QFileInfo dataPath;

    /* The folder with the FFT files */
    QDir Dir;

    /* Save all the file names in one variable */
    QStringList allFiles;

    /* Files for calibration */
    QStringList FFTFilesCalibration, FFTFilesValidation;

    /* Size of Nr Waves */
    QVector<double> wavelengths;

    /* Signal vector */
    QVector<double> signal;

    /* Calibration concentrations */
    QVector<double> CalConcentrations;

    /* How many repetitions are there?  */
    int repetitions;

    /* How many concentrations were measured? */
    double NrConcentrations;

public:

    /* Destructor */
    ~selectAnalizeData(void);

private slots:

    /* Handle click events */
    void handleClickEvent(QWidget *widget);

    /* Sort files */
    QStringList sortFiles(QStringList List);

    /* Sort files according to the substance */
    QStringList sortFiles2(QStringList List);

    /* Add files to the lists */
    void addFilesToList(void);

    /* Allow the user to load data manually */
    void allowSelectPath(void);

    /* Organize files per steps */
    void selectFileSteps(void);

    /* Update list according to the selected repetition */
    void updateSelectionList(void);

    /* Find repetitions */
    void findRepetitions(void);

    /* Clean lists */
    void cleanList(void);

    /* Set data sets for calibration and validation */
    void setDataSets(void);

    /* Remove item from calibration */
    void removeItem(void);

    /* left click menu */
    void showContextMenu(const QPoint &pos);

    /* Activate the logarithm when I(2W) is selected */
    void activateLogarithm(void);

    /* Select files path */
    void selectPath(void);

    /* Read information from files */
    void readFiles(void);

    /* Read initial data */
    void readInitialFile(bool list, QString path);

    /* Analize data */
    void analizeData(void);

    /* Create the files with the calibration and validation data */
    void writeCalValFiles(void);

public slots:

    /* Adjust the automatic loading of data */
    void automaticAnalize(QString PathAuto);

    /* The user decide to cancel the data analysis */
    void cancel(void);

};

#endif // POL_ANALIZEDATA_H
