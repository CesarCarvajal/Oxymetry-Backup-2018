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

using namespace QtDataVisualization;

/* Internal includes */


namespace Ui {
class selectAnalizeData;
}

/**
 * @brief The 'AnaliZe data' class
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

    /* Data for 3D plot */
    QSurfaceDataArray *data3D;

    /* Save the concentrations */
    QStringList concentrationsList;

    /* window canceled */
    bool canceled;

private:

    /* Own signal mapper for buttons and labels in configuration window */
    QSignalMapper *signalMapperC;

    /* File information for saving data of measurements */
    QFileInfo dataPath;

    /* The folder with the FFT files */
    QDir Dir;

    /* Files for calibration */
    QStringList FFTFilesCalibration, FFTFilesValidation;

    /* Size of Nr Waves */
    QVector<double> wavelengths;

    /* Size of Nr Waves */
    QVector<double> signal;

    /* How many repetitions are there?  */
    int repetitions;

public:

    /* Destructor */
    ~selectAnalizeData(void);

private slots:

    /* The user decide to cancel the data analysis */
    void cancel(void);

    /* Handle click events */
    void handleClickEvent(QWidget *widget);

    /* Sort files */
    QStringList sortFiles(QStringList List);

    /* Add files to the lists */
    void addFilesToList(void);

    /* Allow the user to load data manually */
    void allowSelectPath(void);

    /* Create data for 3D plot */
    void createData3D(void);

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

    /* Select files path */
    void selectPath(void);

    /* Read information from files */
    void readFiles(void);

    /* Read initial data */
    void readInitialFile(bool list, QString path);

    /* Analize data */
    void analizeData(void);

public slots:

    /* Adjust the automatic loading of data */
    void automaticAnalize(QString PathAuto);

};

#endif // POL_ANALIZEDATA_H
