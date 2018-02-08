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

/* Qwt library */

/* Internal includes */
#include "pol_externConf.h"
#include "qfile.h"
#include "qprocess.h"
#include "qdir.h"
#include "messages.h"
#include "qdebug.h"
#include "stdlib.h"
#include <math.h>

/**
 * @brief Constructor of 'Pol_ExternConf' class
 */
Pol_ExternConf::Pol_ExternConf()
{

    /* Set size of vectors */
    stockSolutions.reserve(4);
    maxConcentrations.reserve(3);
    minConcentrations.reserve(3);

}

/**
 * @brief Open the Nemesys Pump Software
 */
void Pol_ExternConf::openPumpSoftware(void){

    /* Check if the desktop shortcut exists for the software */
    QFile pumps(QDir().homePath() + "/Desktop/neMESYS UserInterface.lnk");

    /* If it exists with the default installation shortcut name, then rename it */
    if(pumps.exists()){

        /* Rename shortcut */
        pumps.rename(QDir().homePath() + "/Desktop/neMESYS UserInterface.lnk", QDir().homePath() + "/Desktop/NEMESYS.lnk");

    }else{

        /* Or the renamed file already exists? */
        QFile pumps2(QDir().homePath() + "/Desktop/NEMESYS.lnk");

        /* If it exists, run it */
        if(pumps2.exists()){

            /* Create a process */
            process1 = new QProcess(this);

            /* Check the name and path of the software */
            QString text = "start " + QDir().homePath() + "/Desktop/NEMESYS.lnk";

            /* Run the software from console, this is to avoid paths from C:/.. etc, just shortcut in desktop is needed */
            process1->start("cmd", QStringList() << "/C" << text);

        }else{

            /* Show critical error if the shortcut doesnßt exist or the software isn't installed */
            showCritical(QString("Nemesys Pump Software shortcut in desktop named 'NEMESYS' is missing!, Please check if the software is installed, and create a desktop shortcut for it!"), QString(""));
            return;

        }
    }
}

/**
 * @brief Replaces Matlab Functions, Pump Patterns Calculator
 */
void Pol_ExternConf::pumpsPatternCalculator(void){

    /* Get gaps between concentrations */
    double gapGlucose, gapImpurity1, gapImpurity2;

    /* Concentrations */
    QVector <double> GlucoseConcentration(NConcentrations);
    QVector <double> Impurity1Concentration(NConcentrations);
    QVector <double> Impurity2Concentration(NConcentrations);

    /* Flows */
    QVector <double> WaterFlow(NConcentrations);
    QVector <double> GlucoseFlow(NConcentrations);
    QVector <double> Impurity1Flow(NConcentrations);
    QVector <double> Impurity2Flow(NConcentrations);

    /* Measurements vector */
    QVector <double> Nmeasurements(NConcentrations);

    /* Gap between concentrations */
    gapGlucose = (maxConcentrations.at(0) - minConcentrations.at(0))/(NConcentrations-1);
    gapImpurity1 = (maxConcentrations.at(1) - minConcentrations.at(1))/(NConcentrations-1);
    gapImpurity2 = (maxConcentrations.at(2) - minConcentrations.at(2))/(NConcentrations-1);

    /* Create vectors with indexes and solution concentrations */
    for(int k =0; k < NConcentrations; k++){

        /* Concentrations */
        GlucoseConcentration.replace(k,(minConcentrations.at(0)) + (k*gapGlucose));
        Impurity1Concentration.replace(k,minConcentrations.at(1) + k*gapImpurity1);
        Impurity2Concentration.replace(k,minConcentrations.at(2) + k*gapImpurity2);
        Nmeasurements.replace(k, k);

    }

    /* Check correlation factor */
    while(true){

        /* Correlation factors */
        float corrcoeffImpurities = 1, corrcoeffTime = 1;

        /* Random Indexes */
        std::random_shuffle(GlucoseConcentration.begin(), GlucoseConcentration.end());
        std::random_shuffle(Impurity1Concentration.begin(), Impurity1Concentration.end());
        std::random_shuffle(Impurity2Concentration.begin(), Impurity2Concentration.end());

        /* Correlation? */
        corrcoeffImpurities = correlationCoefficient(GlucoseConcentration, Impurity1Concentration, NConcentrations);
        corrcoeffTime = correlationCoefficient(Nmeasurements, GlucoseConcentration, NConcentrations);

        /* If no correlation, then stop doing random order */
        if(corrcoeffImpurities <= 0.05 && corrcoeffTime <= 0.05 ){
            break;
        }
    }

    /* Flow Calculation */
    for(int i =0; i < NConcentrations; i++){

        /* Concentrations */
        GlucoseFlow.replace(i,(GlucoseConcentration.at(i))/(stockSolutions.at(1)*absoluteFlow));
        Impurity1Flow.replace(i,(Impurity1Concentration.at(i))/(stockSolutions.at(2)*absoluteFlow));
        Impurity2Flow.replace(i,(Impurity2Concentration.at(i))/(stockSolutions.at(3)*absoluteFlow));

        /* Water Flow */
        WaterFlow.replace(i,absoluteFlow - (GlucoseFlow.at(i) + Impurity1Flow.at(i) + Impurity2Flow.at(i)));
    }

    /* Create the Glucose pump script */
    GenerateGlucosePumpScript();

    /* Create the Spectrometer Script */
    GenerateSpectrometerConfiguration(GlucoseConcentration, Impurity1Concentration);
}

/**
 * @brief Generate Pump Scripts
 */
void Pol_ExternConf::GenerateGlucosePumpScript(void){

    /* Get folder information */
    QFileInfo folder(pathFile);

    QString glucoseSciptPath = folder.absolutePath() + "/GlucosePumpScript.nfp";

    /* Open the file */
    FILE *Glucosefile = fopen(glucoseSciptPath.toLatin1().data(), "wt");

    /* Write in file */
    fprintf(Glucosefile, "%s", "ml/min \n");

    /* Flow Calculation */
    for(int k =0; k < NConcentrations; k++){

        /* Write in file */
        writePumpFile(Glucosefile);

    }

    /* Close file */
    fclose(Glucosefile);
    Glucosefile = nullptr;

}

/**
 * @brief Generate Spectrometer configuration
 */
void Pol_ExternConf::GenerateSpectrometerConfiguration(QVector <double> GlucoseConcentration, QVector <double> Impurity1Concentration){

    /* Open the file */
    FILE *file = fopen(pathFile.toLatin1().data(), "wt");

    /* Write measurement configuration for each concentration */
    for(int j = 0 ; j < NConcentrations; j++){

        /* Time intervals between measurements */
        int startTime = (10*fillRefill + 20*shortBreak + 7) + TimeIntervals*j;

        /* Configuration line */
        QString line = QString::number(startTime*1000) + ";" + QString::number(GlucoseConcentration.at(j)) + "C1_" + QString::number(Impurity1Concentration.at(j)) + "C2_"
                + QString::number(IntegrationTime) + "ms_" + QString::number(Frequency) + "Hz_" + QString::number(j+1) + ";" + QString::number(NrSpectra) +
                ";" + QString::number(IntegrationTime) + ";" + QString::number(NrAverages) + ";" + QString::number(Frequency) + "\n";

        /* Write in file */
        fprintf(file, "%s", line.toLatin1().data());
    }

    /* Close file */
    fclose(file);
    file = nullptr;

}

/**
 * @brief Write Pump File
 */
void Pol_ExternConf::writePumpFile(FILE *pumpFile){

    /* fprintf(pumpFile, "%s", (QString::number(0) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(1) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(2) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(3) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(4) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(5) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(6) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(7) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(8) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(9) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(10) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(11) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(12) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(13) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(14) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());
    fprintf(pumpFile, "%s", (QString::number(15) + "\t" + QString::number(0) + "\t" + QString::number(0) + "\n").toLatin1().data());*/
}

/**
 * @brief Calculate the correlation coefficient
 */
float Pol_ExternConf::correlationCoefficient(QVector <double> X, QVector <double> Y, int N){

    /* Variables to calculate the correlation factor */
    double sumX=0, sumY = 0, sumX2 = 0, sumY2 = 0, sumXY = 0;

    /* Sum through the vectors */
    for(int i = 0; i < N; i++){

        /* Sum of vector values */
        sumX = sumX + X.at(i);
        sumY= sumY + Y.at(i);

        /* Sum of squares of vectors*/
        sumX2 = sumX2 + (X.at(i)*X.at(i));
        sumY2 = sumY2 + (Y.at(i)*Y.at(i));

        /* Sum of multiplication of vectors */
        sumXY = sumXY + (X.at(i) * Y.at(i));
    }

    /* Get the correlation coefficient */
    float corrcoeff = abs(((N*sumXY) - (sumX*sumY))/(sqrt(((N*sumX2) - (sumX*sumX))*((N*sumY2) - (sumY*sumY)))));

    return corrcoeff;
}


/**
 * @brief Destructor of 'Pol_ExternConf' class
 */
Pol_ExternConf::~Pol_ExternConf(void)
{

    delete process1;
    process1 = nullptr;


}
