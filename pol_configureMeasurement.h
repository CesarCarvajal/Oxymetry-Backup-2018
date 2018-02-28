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
#include "pol_externConf.h"

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

    /* Create the connection to extern software */
    Pol_ExternConf *externSoftware = nullptr;

    /* Configurable Variables */
    int numSpectra;
    float integrationTime;
    int numberOfAverages;
    int freqToMeasure;
    QList<double> timePoint;
    int NrMeasurements;

    /* Is configuration loaded */
    bool loadingConfigurationFromFile;

    /* Save if there was a configuration loaded */
    bool configured;

    /* Path for Store to RAM */
    QString path;

    /* Build the name of the Raw Data */
    QStringList fileName;

    /* Clean all the loaded configuration */
    void cleanAll(void);

    /* Get configuration data */
    void GetConfigurationData(void);

    /* Load configuration file */
    void loadConfiguration(void);

    /* User interface */
    Ui::configurePolMeasure *ui;

    QSignalMapper *signalMapperC;

    /* Do you want to load a configuration? or not? */
    bool Conf_canceled;

    /* Destructor */
    ~configurePolMeasure(void);

private slots:
    /* Select path */
    void selectPath(void);

    /* Configure polarimeter */
    void configurePolarimeter(void);

    /* The user decide to cancel the load of a configuration */
    void cancel(void);

    /* Handle click events */
    void handleClickEvent(QWidget *widget);

private:

    /* Abort run if set to FALSE */
    bool bRunTimePattern = false;

};

#endif // POL_CONFIGUREMEASUREMENT_H
