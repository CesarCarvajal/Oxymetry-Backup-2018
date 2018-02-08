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

#ifndef POL_EXTERNCONF_H
#define POL_EXTERNCONF_H

/* External includes */
#include "qobject.h"
#include "qprocess.h"
#include "QVector"

/**
 * @brief The 'Pol_ExternConf' class
 */
class Pol_ExternConf : public QObject
{
    Q_OBJECT

public:
    /* Constructor */
    explicit Pol_ExternConf();

    /* Run an external process for pump software */
    QProcess *process1 = nullptr;

    /* Spectrometer variables */
    int NConcentrations;
    int NrSpectra;
    int Frequency;
    float IntegrationTime;
    int NrAverages;

    /* Refilling Times */
    int fillRefill;
    int refillSyringe;
    int flushingCuvette;

    /* Pump variables */
    double absoluteFlow;
    double idle;
    int TimeIntervals;

    /* Time Breaks */
    int shortBreak;
    int longBreak;

    /* Stock Solutions */
    QVector<int> stockSolutions;
    QVector<double> minConcentrations;
    QVector<double> maxConcentrations;

    /* Path to save configuration file */
    QString pathFile;

    /* Open Nemesys Pump Software */
    void openPumpSoftware(void);

    /* Generate pump files */
    void GenerateGlucosePumpScript(void);

    /* Generate Spectrometer configuration */
    void GenerateSpectrometerConfiguration(QVector<double> GlucoseConcentration, QVector<double> Impurity1Concentration);

    /* Replaces the function of matlab */
    void pumpsPatternCalculator(void);

    /* Write pump files sequence */
    void writePumpFile(FILE* pumpFile);

    /* Returns the correlation coefficient */
    float correlationCoefficient(QVector <double> X, QVector <double> Y, int N);

    /* Destructor */
    ~Pol_ExternConf(void);

};

#endif  // POL_EXTERNCONF_H
