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

#ifndef POL_CONFIGFILESGENERATOR_H
#define POL_CONFIGFILESGENERATOR_H

/* External includes */
#include "qobject.h"
#include "qprocess.h"
#include "QVector"

/**
 * @brief The 'Pol_configFilesGenerator' class
 */
class Pol_configFilesGenerator : public QObject
{
    Q_OBJECT

public:
    /* Constructor */
    explicit Pol_configFilesGenerator();

    /* Spectrometer variables to be written in files and calculations */
    int NConcentrations;
    int NrSpectra;
    int Frequency;
    float IntegrationTime;
    int NrAverages;

    /* Refilling Times */
    int fillRefill;

    /* Absolute Volume */
    int absVol;

    /* How many substances are active */
    int NumberOfSubstances;

    /* Number of steps for filling refilling */
    int NSteps;

    /* Absolute flow for the pumps */
    double absoluteFlow;

    /* Is the idle mode active? */
    int idle;

    /* Time Breaks */
    int shortBreak;
    int longBreak;

    /* Active substances flags */
    bool glucoseActive;
    bool Imp1Active;
    bool Imp2Active;

    /* Start delay */
    double startDelay;

    /* Repetitions */
    int repetition;

public:

    /* Generate pump files */
    void GeneratePumpScripts(QString pathFile, QString filetype, QVector<double> FlowVector);

    /* Generate Spectrometer configuration */
    void GenerateSpectrometerConfiguration(QString pathFile, QVector<double> GlucoseConcentration, QVector<double> Impurity1Concentration, QVector<double> Impurity2Concentration, QVector<double> StockSolutions, double minW, double maxW);

    /* Calculate the correlation factors */
    float correlationCoefficient(QVector <double> X, QVector <double> Y, int N);

    /* Destructor */
    ~Pol_configFilesGenerator(void);

private:

    /* Write pump files sequence */
    void writePumpFile(FILE* pumpFile, QString filetype, QVector<double> FlowVector);

    /* Write Flushing pattern */
    void writeFlushing(FILE *pFile, QString filetype);

    /* Write Filling pattern */
    void writeFilling(FILE *pFile, QVector <double> FlowVector, int k);

};

#endif  // POL_CONFIGFILES GENERATOR_H
