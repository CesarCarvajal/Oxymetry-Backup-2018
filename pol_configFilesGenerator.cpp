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
#include "pol_configFilesGenerator.h"
#include "qfile.h"
#include "qdir.h"
#include "messages.h"
#include "qdebug.h"
#include "stdlib.h"
#include <math.h>

/**
 * @brief Constructor of 'Pol_configFilesGenerator' class
 */
Pol_configFilesGenerator::Pol_configFilesGenerator()
{

    /* Active substances flags */
    glucoseActive = false;
    Imp1Active = false;
    Imp2Active = false;

    /* Delay on starting the measurements */
    startDelay = 0;

    /* Number of Sustances active */
    NumberOfSubstances = 2;

    /* Range of Wavelengths */
    minWavelength = 400;
    maxWavelength = 1000;

}

/**
 * @brief Generate Pump Scripts
 * @param[in] The type of file to be generated "Water", "Glucose" or "Impurity", the vector containing the necessary flow.
 */
void Pol_configFilesGenerator::GeneratePumpScripts(QString pathFile, QString filetype, QVector <double> FlowVector){

    /* Get folder to store the information */
    QFileInfo folder(pathFile);

    /* Defines the type of pump script */
    QString ScriptPath = folder.absolutePath() + filetype;

    /* Open the file */
    FILE *Sfile = fopen(ScriptPath.toLatin1().data(), "wt");

    /* Write in file */
    fprintf(Sfile, "%s", "ml/min \n");
    fprintf(Sfile, "%s", "1 \n");

    /* Print start delay if needed */
    if(startDelay!=0){
        fprintf(Sfile, "%.0f\t%d\t%i\n", startDelay*1000, 0, 0);
    }

    /* Write in file */
    writePumpFile(Sfile, filetype, FlowVector);

    /* Close file */
    fclose(Sfile);
    Sfile = nullptr;

}

/**
 * @brief Generate Spectrometer configuration
 * @param[in] Vectors with Glucose and Impurities concentrations
 */
void Pol_configFilesGenerator::GenerateSpectrometerConfiguration(QString pathFile, QVector <double> GlucoseConcentration, QVector <double> Impurity1Concentration, QVector <double> Impurity2Concentration){

    /* Open the file */
    FILE *file = fopen(pathFile.toLatin1().data(), "wt");

    /* Write in file */
    fprintf(file, "%s", "Time_interval ; File_name ; Nr_Spectra ; Int_time ; Nr_Averages ; Modulation_frequency\n");

    /* Cycle of a concentration */
    double cycleTime = (2 * fillRefill + 4*shortBreak)*(NSteps + (NSteps-1)) +  (2 * fillRefill + 3*shortBreak + longBreak );

    /* Time intervals between measurements */
    double measurementTime = cycleTime - (((longBreak + (2*IntegrationTime*NrSpectra))/3));

    /* Write measurement configuration for each concentration */
    for(int j = 0 ; j < NConcentrations; j++){

        /* Measurement cycle time */
        int mTime = measurementTime + (cycleTime * j);

        /* Configuration line */
        QString line = QString::number(mTime) + ";" ;

        /* If glucose is active call it Concentration 1 or C1 */
        if(glucoseActive){

            /* Add C1 to the file name */
            line.append(QString::number(GlucoseConcentration.at(j)) + "C1_");

        }

        /* If Impurity 1 is active call it Concentration 2 or C2 */
        if(Imp1Active){

            /* Add C2 to the file name */
            line.append(QString::number(Impurity1Concentration.at(j)) + "C2_");
        }

        /* If Impurity 2 is active call it Concentration 3 or C3 */
        if(Imp2Active){

            /* Add C3 to the file name */
            line.append(QString::number(Impurity2Concentration.at(j)) + "C3_");
        }

        /* Complete the file name */
        line = line + QString::number(IntegrationTime) + "ms_" + QString::number(Frequency) + "Hz_" + QString::number(j+1) + ";" + QString::number(NrSpectra) +
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
 * @param[in] The file where the configuration is going to be written. The type of file to be written and the vector containing the flows.
 */
void Pol_configFilesGenerator::writePumpFile(FILE *pumpFile, QString filetype, QVector <double> FlowVector){

    /* Flow Calculation */
    for(int k =0; k < NConcentrations; k++){

        /* Write flushing pattern */
        writeFlushing(pumpFile, filetype);

        /* Write Filling pattern */
        writeFilling(pumpFile, FlowVector, k);

    }

    /* Write flushing pattern for cleaning the cuvette at the end */
    writeFlushing(pumpFile, filetype);

}

/**
 * @brief Write Flushing pattern to File
 * @param[in] The file where the information will be written and the type of file.
 */
void Pol_configFilesGenerator::writeFlushing(FILE *pFile, QString filetype){

    /* Use comas instead of dots */
    setlocale(LC_NUMERIC, "French_Canada.1252");

    /* Write the flusing pattern */
    for(int j = 0; j < NSteps; j++){

        /* Is it water? */
        if(filetype == "/WaterPumpScript.nfp"){

            /* 7 flushing cuvette fill */
            fprintf(pFile, "%d\t%.4f\t%d\n", fillRefill, absoluteFlow, idle);

        }else{

            /* 7 flushing cuvette fill */
            fprintf(pFile, "%d\t%d\t%d\n", fillRefill, 0, idle);
        }

        /* 8 stop after filling valve refill */
        fprintf(pFile, "%d\t%d\t%i\n", shortBreak, 0, idle);

        /* 9 stop after refilling valve fill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, 1);

        /* Is it water? */
        if(filetype == "/WaterPumpScript.nfp"){

            /* 10 flushing cuvette fill */
            fprintf(pFile, "%d\t%.4f\t%d\n", fillRefill, -absoluteFlow, 1);

        }else{

            /* 10 flushing cuvette fill */
            fprintf(pFile, "%d\t%d\t%d\n", fillRefill, 0, 1);
        }

        /* 11 stop after refilling valve fill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, 1);

        /* 12 stop after refilling valve refill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, idle);
    }
}

/**
 * @brief Write Filling Pattern to File
 * @param[in] The file where the information is going to be written, the vector of flows and the corresponding concentration position k.
 */
void Pol_configFilesGenerator::writeFilling(FILE *pFile, QVector <double> FlowVector, int k){

    /* Use comas instead of dots */
    setlocale(LC_NUMERIC, "French_Canada.1252");

    /*  Write the filling patterns */
    for(int i = 1; i <= NSteps; i++){

        /* i-th FILLING */
        /* 1 Filling cuvette with solution valve fill */
        fprintf(pFile, "%d\t%.4f\t%d\n", fillRefill, FlowVector.at(k), idle);

        /* 2 Stop after filling valve fill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, idle);

        /* 3 Stop after filling valve refill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, 1);

        /* 4 Refill after filling valve refill */
        fprintf(pFile, "%d\t%.4f\t%d\n", fillRefill, -FlowVector.at(k), 1);

        /* Is it the last refill pattern? */
        if(i == NSteps){

            /* 5 stop for MEASUREMENT during this block valve refill Last Refill */
            fprintf(pFile, "%d\t%d\t%d\n", longBreak, 0, 1);

        }else{

            /* 5 stop for MEASUREMENT during this block valve refill */
            fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, 1);
        }

        /* 6 Stop after measurement valve fill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, idle);
    }
}

/**
 * @brief Calculate the correlation coefficient
 * @param[in] The vectors X and Y of size N are compared to find the correlation coefficient.
 * @param[out] Correlation coefficient
 */
float Pol_configFilesGenerator::correlationCoefficient(QVector <double> X, QVector <double> Y, int N){

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

    /* Square the correlation coefficient */
    corrcoeff = corrcoeff*corrcoeff;

    return corrcoeff;
}


/**
 * @brief Destructor of 'Pol_ExternConf' class
 */
Pol_configFilesGenerator::~Pol_configFilesGenerator(void)
{

}
