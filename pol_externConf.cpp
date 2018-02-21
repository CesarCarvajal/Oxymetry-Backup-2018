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

    /* Set size of vectors: there are 3 components */
    stockSolutions.reserve(3);
    maxConcentrations.reserve(3);
    minConcentrations.reserve(3);

    /* Active substances */
    glucoseActive = false;
    Imp1Active = false;
    Imp2Active = false;
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

    /* Is there more than 1 substance available? */
    if(glucoseActive+Imp1Active+Imp2Active > 1){

        /* Check correlation factor */
        while(true && NConcentrations>4){

            /* Correlation factors */
            float corrcoeffGlucImp1= 1, corrcoeffTime = 1, corrcoeffImp1Imp2= 1, corrcoeffGlucImp2= 1;

            /* Random Indexes */
            std::random_shuffle(GlucoseConcentration.begin(), GlucoseConcentration.end());
            std::random_shuffle(Impurity1Concentration.begin(), Impurity1Concentration.end());
            std::random_shuffle(Impurity2Concentration.begin(), Impurity2Concentration.end());

            /* correlation of glucose and number of measurements */
            corrcoeffTime = correlationCoefficient(Nmeasurements, GlucoseConcentration, NConcentrations);

            /* Is the factor ok?, if not start again */
            if(corrcoeffTime > 0.05){ continue;}

            /* Correlation between Glucose and Impurity 1 */
            if(glucoseActive && Imp1Active){
                corrcoeffGlucImp1 = correlationCoefficient(GlucoseConcentration, Impurity1Concentration, NConcentrations);

                /* Is the factor ok?, if not start again */
                if(corrcoeffGlucImp1 > 0.05){ continue;}
            }

            /* Correlation between Impurity 1 and Impurity 2 */
            if(Imp1Active && Imp2Active){
                corrcoeffImp1Imp2 = correlationCoefficient(Impurity2Concentration, Impurity1Concentration, NConcentrations);

                /* Is the factor ok?, if not start again */
                if(corrcoeffImp1Imp2 > 0.05){ continue;}
            }

            /* Correlation between Glucose and Impurity 2 */
            if(glucoseActive && Imp2Active){
                corrcoeffGlucImp2 = correlationCoefficient(GlucoseConcentration, Impurity2Concentration, NConcentrations);

                /* Is the factor ok?, if not start again */
                if(corrcoeffGlucImp2 > 0.05){ continue;}
            }

            /* If no correlation or just a few elements, then stop doing random order */
            break;
        }
    }else{

        /* Random Indexes if there is only 1 substance */
        std::random_shuffle(GlucoseConcentration.begin(), GlucoseConcentration.end());
        std::random_shuffle(Impurity1Concentration.begin(), Impurity1Concentration.end());
        std::random_shuffle(Impurity2Concentration.begin(), Impurity2Concentration.end());

    }

    /* Flow Calculation */
    for(int i =0; i < NConcentrations; i++){

        /* Concentrations */
        GlucoseFlow.replace(i,GlucoseConcentration.at(i)*((absoluteFlow)/(stockSolutions.at(0))));
        Impurity1Flow.replace(i,Impurity1Concentration.at(i)*((absoluteFlow)/(stockSolutions.at(1))));
        Impurity2Flow.replace(i,Impurity2Concentration.at(i)*((absoluteFlow)/(stockSolutions.at(2))));

        /* Water Flow */
        WaterFlow.replace(i,absoluteFlow - (GlucoseFlow.at(i) + Impurity1Flow.at(i)));
    }

    /* Create the Spectrometer Script */
    GenerateSpectrometerConfiguration(GlucoseConcentration, Impurity1Concentration, Impurity2Concentration);

    /* If glucose is active, then generate its pump script */
    if(glucoseActive){
        /* Create the Glucose pump script */
        GeneratePumpScripts("/GlucosePumpScript.nfp", GlucoseFlow);
    }

    /* If Impurity 1 is active, then generate its pump script */
    if(Imp1Active){
        /* Create the Impurity 1 pump script */
        GeneratePumpScripts("/Impurity1PumpScript.nfp", Impurity1Flow);
    }

    /* If impurity 2 is active, then generate its pump script */
    if(Imp2Active){
        /* Create the Impurity 2 pump script */
        GeneratePumpScripts("/Impurity2PumpScript.nfp", Impurity2Flow);
    }

    /* Create the Water pump script */
    GeneratePumpScripts("/WaterPumpScript.nfp", WaterFlow);

}

/**
 * @brief Generate Pump Scripts
 * @param[in] The type of file to be generated "Water", "Glucose" or "Impurity", the vector containing the necessary flow.
 */
void Pol_ExternConf::GeneratePumpScripts(QString filetype, QVector <double> FlowVector){

    /* Get folder information */
    QFileInfo folder(pathFile);

    /* Defines the type of pump script */
    QString ScriptPath = folder.absolutePath() + filetype;

    /* Open the file */
    FILE *Sfile = fopen(ScriptPath.toLatin1().data(), "wt");

    /* Write in file */
    fprintf(Sfile, "%s", "ml/min \n");
    fprintf(Sfile, "%s", "1 \n");

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
void Pol_ExternConf::GenerateSpectrometerConfiguration(QVector <double> GlucoseConcentration, QVector <double> Impurity1Concentration, QVector <double> Impurity2Concentration){

    /* Open the file */
    FILE *file = fopen(pathFile.toLatin1().data(), "wt");

    /* Write measurement configuration for each concentration */
    for(int j = 0 ; j < NConcentrations; j++){

        /* Time intervals between measurements */
        int startTime = (10*fillRefill + 20*shortBreak + 7000) + TimeIntervals*j;

        /* Configuration line */
        QString line = QString::number(startTime) + ";" ;

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
void Pol_ExternConf::writePumpFile(FILE *pumpFile, QString filetype, QVector <double> FlowVector){

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
void Pol_ExternConf::writeFlushing(FILE *pFile, QString filetype){

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
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, idle);

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
void Pol_ExternConf::writeFilling(FILE *pFile, QVector <double> FlowVector, int k){

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
