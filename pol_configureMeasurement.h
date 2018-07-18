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

#ifndef POL_CONFIGUREMEASUREMENT_H
#define POL_CONFIGUREMEASUREMENT_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QList>
#include <QStringList>
#include <QSignalMapper>
#include <QDateTime>
#include "pol_externConf.h"
#include <QFileInfo>

/* Internal includes */
#include "pol_panelItem.h"

namespace Ui {
class configurePolMeasure;
}

/**
 * @brief The 'configurePolMeasure' class
 */
class configurePolMeasure : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit configurePolMeasure(QWidget *parent = 0);

    /* User interface */
    Ui::configurePolMeasure *ui;

    /* Create the connection to extern software */
    Pol_ExternConf *externSoftware = nullptr;

    /* Configurable Variables loaded form files or created */
    QList<double> timePoint;

    /* Total measurement time */
    double totalMtime;

    /* Save if there was a configuration loaded */
    bool configured;

    /* Was the pumps software open already? */
    bool openPumps;

    /* File information for saving data of measurements */
    QFileInfo pathDataMeasurements;

    /* Build the name of the Raw Data files */
    QStringList savingFilesNames;

    /*Start time of the measurement with delay */
    QDateTime startTime;

    /* Do you want to load a configuration? or not? */
    bool Conf_canceled;

private:

    /* Abort run if set to FALSE */
    bool bRunTimePattern = false;

    /* Own signal mapper for buttons and labels in configuration window */
    QSignalMapper *signalMapperC;

    /* Is a configuration loaded */
    bool loadingConfigurationFromFile;

public:

    /* Clean all the loaded configuration */
    void cleanAll(void);

    /* Update form */
    void updateForm(void);

    /* Load configuration file */
    void loadConfiguration(void);

    /* Get configuration data */
    void GetConfigurationData(void);

    /* Get correct number of spectra values */
    int NrSpectraSteps(int Fint);

    /* Initialize the form according to the actual spectrometer settings */
    void InitializeForm(PanelItem_Pol *PolarimetrySpectrometer);

    /* Return preview name */
    void filePreviewName(void);

    /* Hide impurities */
    void hideAdditionalSubstances(bool status1, bool status2, bool status3, bool status4, bool status5);

    /* Destructor */
    ~configurePolMeasure(void);

private slots:

    /* Select path */
    void selectPath(void);

    /* Add more impurities */
    void addImpurities(void);

    /* Configure polarimeter */
    void configurePolarimeter(void);

    /* The user decide to cancel the load of a configuration */
    void cancel(void);

    /* Handle click events */
    void handleClickEvent(QWidget *widget);

    /* Get complete configuration data from file */
    void getConfigurationFromFile(QString data);

public slots:

    /* Update parameters */
    void updateConfigurationValues(void);

    /* Update parameters */
    void updateStockValues(void);

};

#endif // POL_CONFIGUREMEASUREMENT_H
