/*
 * Hemoxymetrie in non-hemolyzed human whole blood
 * Copyright (C) 2016-2017 Benjamin Redmer, ... ?
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
 *
 * In this class:   - The pump files are created and filled.
 *                  - The Spectrometer File is created and filled.
 *                  - The Correlation coefficient function.
 *
 */
Pol_configFilesGenerator::Pol_configFilesGenerator()
{
    /* Initialize spectrometer variables */
    NConcentrations = 0;    /* Number of measurements */
    NrSpectra = 1000;       /* Number of spectra */
    Frequency = 7;          /* Frequency of the measurements */
    IntegrationTime = 8;    /* Integration time */
    NrAverages = 1;         /* Number of averages */

    /* Initialize scripts variables */
    fillRefill = 0;     /* Fill and Re-Fill time */
    absVol = 0;         /* Absolute volume of cuvette */
    NSteps = 5;         /* Number of steps for Fill-ReFill */
    absoluteFlow = 0;   /* Absolute Flow given for the pumps */
    shortBreak = 0;     /* Short break of the measurements */
    longBreak = 0;      /* Long break of the measurements */

    /* Repetitions and cycles of the pump */
    repetition = 0;      /* How many repetitions should be performed? */
    PumpsCycle = 0;      /* A complete cycle of the pumps to build a concentration */

    /* Active substances flags */
    activeSubstances.resize(6);

    /* There are 5 impurities names */
    substancesNames.append(".");
    substancesNames.append(".");
    substancesNames.append(".");
    substancesNames.append(".");
    substancesNames.append(".");

    /* Glucose and Impurity 1 are always at the beginning active */
    activeSubstances.replace(0, true);
    activeSubstances.replace(1, true);

    /* Initialize the active substances vector to false */
    for(int g=2; g < activeSubstances.length() ; g++){

        /* No substances active */
        activeSubstances.replace(g, false);
    }

    /* Normalizd counts? */
    normalizedCounts = false;

    /* No interval or crossing mode active */
    intervalMode = false;
    crossingMode = false;

    /* Delay on starting the measurements? */
    startDelay = 0;

    /* Number of Sustances active, initially only glucose and impurity 1 */
    NumberOfSubstances = 2;
}

/**
 * @brief Generate Pump Scripts
 * @param[in] The type of file to be generated "Water", "Glucose" or "Impurity",
 * the vector containing the necessary flow.
 */
void Pol_configFilesGenerator::GeneratePumpScripts(QString pathFile, QString filetype, QVector <double> FlowVector){

    /* Get folder to store the pump scripts */
    QFileInfo folder(pathFile);

    /* Defines the type of pump script, Water? Glucose? Impurity 1? etc... */
    QString ScriptPath = folder.absolutePath() + filetype;

    /* Open the corresponding file */
    FILE *Sfile = fopen(ScriptPath.toLatin1().data(), "wt");

    /* Write in the file */
    fprintf(Sfile, "%s", "ml/min ");

    /* Write which substance name belongs to which type of file */
    if(filetype.contains("C2")){
        fprintf(Sfile, "%s", substancesNames.at(0).toLatin1().data());
    }
    if(filetype.contains("C3")){
        fprintf(Sfile, "%s", substancesNames.at(1).toLatin1().data());
    }
    if(filetype.contains("C4")){
        fprintf(Sfile, "%s", substancesNames.at(2).toLatin1().data());
    }
    if(filetype.contains("C5")){
        fprintf(Sfile, "%s", substancesNames.at(3).toLatin1().data());
    }
    if(filetype.contains("C6")){
        fprintf(Sfile, "%s", substancesNames.at(4).toLatin1().data());
    }
    if(filetype.contains("C1")){
        fprintf(Sfile, "%s", "Glucose");
    }
    if(filetype.contains("Water")){
        fprintf(Sfile, "%s", "Water");
    }
    fprintf(Sfile, "%s", "\n");
    fprintf(Sfile, "%s", "1 \n");

    /* Print start delay in ms if needed */
    if(startDelay!=0){
        fprintf(Sfile, "%.0f\t%d\t%i\n", startDelay*1000, 0, 0);
    }

    /* Write the pump sequence in the file */
    writePumpFile(Sfile, filetype, FlowVector);

    /* Close file */
    fclose(Sfile);

    /* Empty memory space */
    Sfile = nullptr;
}

/**
 * @brief Generate Spectrometer configuration file
 * @param[in] Vectors with Glucose and Impurities concentrations
 */
void Pol_configFilesGenerator::GenerateSpectrometerConfiguration(QString pathFile, QVector <double> GlucoseConcentration, QVector <double> Impurity1Concentration,
                                                                 QVector <double> Impurity2Concentration,
                                                                 QVector <double> Impurity3Concentration, QVector <double> Impurity4Concentration,
                                                                 QVector <double> Impurity5Concentration,
                                                                 QVector <double> StockSolutions, double minW, double maxW, double UserTimeInterval){
    /* Open the configuration file */
    FILE *file = fopen(pathFile.toLatin1().data(), "wt");

    /* Write in the spectrometer configuration file the meaning of the values */
    fprintf(file, "%s", "1Nr_M;2Nr_Sp;3Int_T;4Nr_Av;5Freq;6MinW;7MaxW;8Ab_F;9Ab_V;10N_Ste;11S_Break;12L_Break;13St_Del;14C1?;15C2?;16C3?;17C4?;18C5?;19C6?;"
                        "20mC1;21MC1;22StC1;23mC2;24MC2;25StC2;26mC3;27MC3;28StC3;29mC4;30MC4;31StC4;32mC5;33MC5;34StC5;35mC6;36MC6;37StC6;"
                        "38Rep;39NormC;40IntMode;41IntModeTime;42Imp1Name;43Imp2Name;44Imp3Name;45Imp4Name;46Imp5Name;47CrossMode,\n");

    /* Write all the configuration data consecutively */
    QString configurationData = "";

    configurationData.append(QString::number(NConcentrations) + ";");
    configurationData.append(QString::number(NrSpectra) + ";");
    configurationData.append(QString::number(IntegrationTime) + ";");
    configurationData.append(QString::number(NrAverages) + ";");
    configurationData.append(QString::number(Frequency) + ";");
    configurationData.append(QString::number(minW) + ";");
    configurationData.append(QString::number(maxW) + ";");
    configurationData.append(QString::number(absoluteFlow) + ";");
    configurationData.append(QString::number(absVol) + ";");
    configurationData.append(QString::number(NSteps) + ";");
    configurationData.append(QString::number(shortBreak) + ";");
    configurationData.append(QString::number(longBreak) + ";");
    configurationData.append(QString::number(startDelay) + ";");
    configurationData.append(QString::number(activeSubstances.at(0)) + ";");
    configurationData.append(QString::number(activeSubstances.at(1)) + ";");
    configurationData.append(QString::number(activeSubstances.at(2)) + ";");
    configurationData.append(QString::number(activeSubstances.at(3)) + ";");
    configurationData.append(QString::number(activeSubstances.at(4)) + ";");
    configurationData.append(QString::number(activeSubstances.at(5)) + ";");
    configurationData.append(QString::number(*std::min_element(GlucoseConcentration.begin(), GlucoseConcentration.end()))+ ";");
    configurationData.append(QString::number(*std::max_element(GlucoseConcentration.begin(), GlucoseConcentration.end()))+ ";");
    configurationData.append(QString::number(StockSolutions.at(0)) + ";");
    configurationData.append(QString::number(*std::min_element(Impurity1Concentration.begin(), Impurity1Concentration.end()))+ ";");
    configurationData.append(QString::number(*std::max_element(Impurity1Concentration.begin(), Impurity1Concentration.end()))+ ";");
    configurationData.append(QString::number(StockSolutions.at(1)) + ";");
    configurationData.append(QString::number(*std::min_element(Impurity2Concentration.begin(), Impurity2Concentration.end()))+ ";");
    configurationData.append(QString::number(*std::max_element(Impurity2Concentration.begin(), Impurity2Concentration.end()))+ ";");
    configurationData.append(QString::number(StockSolutions.at(2)) + ";");
    configurationData.append(QString::number(*std::min_element(Impurity3Concentration.begin(), Impurity3Concentration.end()))+ ";");
    configurationData.append(QString::number(*std::max_element(Impurity3Concentration.begin(), Impurity3Concentration.end()))+ ";");
    configurationData.append(QString::number(StockSolutions.at(3)) + ";");
    configurationData.append(QString::number(*std::min_element(Impurity4Concentration.begin(), Impurity4Concentration.end()))+ ";");
    configurationData.append(QString::number(*std::max_element(Impurity4Concentration.begin(), Impurity4Concentration.end()))+ ";");
    configurationData.append(QString::number(StockSolutions.at(4)) + ";");
    configurationData.append(QString::number(*std::min_element(Impurity5Concentration.begin(), Impurity5Concentration.end()))+ ";");
    configurationData.append(QString::number(*std::max_element(Impurity5Concentration.begin(), Impurity5Concentration.end()))+ ";");
    configurationData.append(QString::number(StockSolutions.at(5)) + ";");
    configurationData.append(QString::number(repetition) + ";");
    configurationData.append(QString::number(normalizedCounts) + ";");
    configurationData.append(QString::number(intervalMode) + ";");
    configurationData.append(QString::number(UserTimeInterval) + ";");
    configurationData.append(substancesNames.at(0) + ";");
    configurationData.append(substancesNames.at(1) + ";");
    configurationData.append(substancesNames.at(2) + ";");
    configurationData.append(substancesNames.at(3) + ";");
    configurationData.append(substancesNames.at(4) + ";");
    configurationData.append(QString::number(crossingMode) + "\n");

    /* Write in file the configuration values */
    fprintf(file, "%s", configurationData.toLatin1().data());

    /* Write in file the time titles */
    fprintf(file, "%s", "Time_Interval;File_Name;\n");

    /* Cycle of building a certain concentration */
    PumpsCycle = (2 * fillRefill + 4*shortBreak)*(NSteps + (NSteps-1)) +  (2 * fillRefill + 3*shortBreak + longBreak );

    /* Time intervals between measurements */
    double measurementTime = PumpsCycle - (((longBreak + (2*IntegrationTime*NrSpectra*NrAverages))/3));

    /* Set initial time for repetitions in case they are present */
    int initialTime = 0;

    /* Repeat the scripts when there are repetitions */
    for(int rep =1; rep <= repetition; rep++){

        /* Write measurement configuration for each concentration */
        for(int j = 0 ; j < NConcentrations; j++){

            /* Line for the file names */
            QString line  = "";

            /* Is the interval mode active? Then just consider the maximum concentration */
            if(intervalMode){

                /* Measurement cycle time */
                int mTime = initialTime + UserTimeInterval * (j+1);

                /* Configuration line */
                line = QString::number(mTime) + ";" ;

                /* If glucose is active call it Concentration 1 or C1 */
                if(activeSubstances.at(0)){

                    /* Add C1 to the file name */
                    line.append(QString::number(*std::max_element(GlucoseConcentration.begin(), GlucoseConcentration.end())) + "C1_");
                }

                /* If Impurity 1 is active call it Concentration 2 or C2 */
                if(activeSubstances.at(1)){

                    /* Add C2 to the file name */
                    line.append(QString::number(*std::max_element(Impurity1Concentration.begin(), Impurity1Concentration.end())) + "C2_");
                }

                /* If Impurity 2 is active call it Concentration 3 or C3 */
                if(activeSubstances.at(2)){

                    /* Add C3 to the file name */
                    line.append(QString::number(*std::max_element(Impurity2Concentration.begin(), Impurity2Concentration.end())) + "C3_");
                }

                /* If Impurity 3 is active call it Concentration 4 or C4 */
                if(activeSubstances.at(3)){

                    /* Add C3 to the file name */
                    line.append(QString::number(*std::max_element(Impurity3Concentration.begin(), Impurity3Concentration.end())) + "C4_");
                }

                /* If Impurity 4 is active call it Concentration 5 or C5 */
                if(activeSubstances.at(4)){

                    /* Add C3 to the file name */
                    line.append(QString::number(*std::max_element(Impurity4Concentration.begin(), Impurity4Concentration.end())) + "C5_");
                }

                /* If Impurity 5 is active call it Concentration 6 or C6 */
                if(activeSubstances.at(5)){

                    /* Add C3 to the file name */
                    line.append(QString::number(*std::max_element(Impurity5Concentration.begin(), Impurity5Concentration.end())) + "C6_");
                }

            }
            /* If the interval mode is not active, then continue normally */
            else{

                /* Measurement cycle time */
                int mTime = initialTime + measurementTime + (PumpsCycle * j);

                /* Configuration line */
                line = QString::number(mTime) + ";" ;

                /* If glucose is active call it Concentration 1 or C1 */
                if(activeSubstances.at(0)){

                    /* is there a float presicion? */
                    double num = (*std::max_element(GlucoseConcentration.begin(), GlucoseConcentration.end()))/(NConcentrations-1);
                    int num2 = (int)num;
                    double compared = (num - num2) < 0 ? (num - num2)*(-1):(num - num2);

                    if(compared < 0.0001){
                        /* Add C1 to the file name */
                        line.append(QString::number(GlucoseConcentration.at(j)) + "C1_");
                    }else{
                        line.append(QString::number(GlucoseConcentration.at(j), 'f', 3) + "C1_");
                    }
                }

                /* If Impurity 1 is active call it Concentration 2 or C2 */
                if(activeSubstances.at(1)){

                    /* is there a float presicion? */
                    double num = (*std::max_element(Impurity1Concentration.begin(), Impurity1Concentration.end()))/(NConcentrations-1);
                    int num2 = (int)num;
                    double compared = (num - num2) < 0 ? (num - num2)*(-1):(num - num2);

                    if(compared < 0.0001){
                        /* Add C2 to the file name */
                        line.append(QString::number(Impurity1Concentration.at(j)) + "C2_");
                    }else{
                        /* Add C2 to the file name */
                        line.append(QString::number(Impurity1Concentration.at(j), 'f', 3) + "C2_");
                    }
                }

                /* If Impurity 2 is active call it Concentration 3 or C3 */
                if(activeSubstances.at(2)){

                    /* is there a float presicion? */
                    double num = (*std::max_element(Impurity2Concentration.begin(), Impurity2Concentration.end()))/(NConcentrations-1);
                    int num2 = (int)num;
                    double compared = (num - num2) < 0 ? (num - num2)*(-1):(num - num2);

                    if(compared < 0.0001){
                        /* Add C3 to the file name */
                        line.append(QString::number(Impurity2Concentration.at(j)) + "C3_");
                    }else{
                        /* Add C3 to the file name */
                        line.append(QString::number(Impurity2Concentration.at(j), 'f', 3) + "C3_");
                    }
                }

                /* If Impurity 3 is active call it Concentration 4 or C4 */
                if(activeSubstances.at(3)){

                    /* is there a float presicion? */
                    double num = (*std::max_element(Impurity3Concentration.begin(), Impurity3Concentration.end()))/(NConcentrations-1);
                    int num2 = (int)num;
                    double compared = (num - num2) < 0 ? (num - num2)*(-1):(num - num2);

                    if(compared < 0.0001){
                        /* Add C4 to the file name */
                        line.append(QString::number(Impurity3Concentration.at(j)) + "C4_");
                    }else{
                        /* Add C4 to the file name */
                        line.append(QString::number(Impurity3Concentration.at(j), 'f', 3) + "C4_");
                    }
                }

                /* If Impurity 4 is active call it Concentration 5 or C5 */
                if(activeSubstances.at(4)){

                    /* is there a float presicion? */
                    double num = (*std::max_element(Impurity4Concentration.begin(), Impurity4Concentration.end()))/(NConcentrations-1);
                    int num2 = (int)num;
                    double compared = (num - num2) < 0 ? (num - num2)*(-1):(num - num2);

                    if(compared < 0.0001){
                        /* Add C5 to the file name */
                        line.append(QString::number(Impurity4Concentration.at(j)) + "C5_");
                    }else{
                        /* Add C5 to the file name */
                        line.append(QString::number(Impurity4Concentration.at(j), 'f', 3) + "C5_");
                    }
                }

                /* If Impurity 5 is active call it Concentration 6 or C6 */
                if(activeSubstances.at(5)){

                    /* is there a float presicion? */
                    double num = (*std::max_element(Impurity5Concentration.begin(), Impurity5Concentration.end()))/(NConcentrations-1);
                    int num2 = (int)num;
                    double compared = (num - num2) < 0 ? (num - num2)*(-1):(num - num2);

                    if(compared < 0.0001){
                        /* Add C6 to the file name */
                        line.append(QString::number(Impurity5Concentration.at(j)) + "C6_");
                    }else{
                        /* Add C6 to the file name */
                        line.append(QString::number(Impurity5Concentration.at(j), 'f', 3) + "C6_");
                    }
                }
            }

            /* If there are repetitions then change the file names */
            if(repetition > 1){
                /* Complete the file name with an R */
                line = line.append(QString::number(IntegrationTime) + "ms_" + QString::number(Frequency) + "Hz_" + QString::number(j+1+((rep-1)*NConcentrations)) + "_R" + QString::number(rep));
            }else{
                /* Complete the file name */
                line = line.append(QString::number(IntegrationTime) + "ms_" + QString::number(Frequency) + "Hz_" + QString::number(j+1));
            }

            /* At end of line */
            line.append(";\n");

            /* Write in file */
            fprintf(file, "%s", line.toLatin1().data());
        }

        /* Is the interval mode active? */
        if(intervalMode){

            /* If there are repetitions, then check the right time */
            initialTime = initialTime + NConcentrations*UserTimeInterval;
        }else{
            /* Measurement cycle time */
            initialTime = initialTime + (PumpsCycle * (NConcentrations));
        }
    }
    /* Close file */
    fclose(file);

    /* Free space */
    file = nullptr;
}

/**
 * @brief Write Pump Sequence File
 * @param[in] The file where the configuration is going to be written. The type of file to be written and the vector containing the flows.
 */
void Pol_configFilesGenerator::writePumpFile(FILE *pumpFile, QString filetype, QVector <double> FlowVector){

    /* Repeat the scripts when there are repetitions */
    for(int rep =0; rep < repetition; rep++){

        /* write this millisecond for the repetitions */
        if(rep > 0){
            fprintf(pumpFile, "%d\t%d\t%d\n", 1, 0, 0);
        }

        /* Get how many concentrations are really needed */
        int countfor = 0;

        /* If the interval mode is active just one is build */
        if(intervalMode){

            /* Just build the script for one concentration */
            countfor = 1;
        }else{

            /* If not, then get all of them */
            countfor = NConcentrations;
        }

        /* Flow Calculation */
        for(int k =0; k < countfor; k++){

            /* Write flushing pattern */
            writeFlushing(pumpFile, filetype);

            /* Write Filling pattern */
            writeFilling(pumpFile, FlowVector, k);
        }

        /* If there was the last repetition, add the flushing only at the end */
        if(rep == repetition - 1){
            /* Write flushing pattern for cleaning the cuvette at the end */
            writeFlushing(pumpFile, filetype);
        }
    }
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
        if(filetype.contains("Water")){

            /* 1 Flushing cuvette fill */
            fprintf(pFile, "%d\t%.4f\t%d\n", fillRefill, absoluteFlow, 0);
        }else{
            fprintf(pFile, "%d\t%d\t%d\n", fillRefill, 0, 0);
        }

        /* 2 Stop after filling valve refill */
        fprintf(pFile, "%d\t%d\t%i\n", shortBreak, 0, 0);

        /* 3 Stop after refilling valve fill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, 1);

        /* Is it water? */
        if(filetype.contains("Water")){

            /* 4 Flushing cuvette fill */
            fprintf(pFile, "%d\t%.4f\t%d\n", fillRefill, -absoluteFlow, 1);
        }else{
            fprintf(pFile, "%d\t%d\t%d\n", fillRefill, 0, 1);
        }

        /* 5 Stop after refilling valve fill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, 1);

        /* 6 Stop after refilling valve refill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, 0);
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
        fprintf(pFile, "%d\t%.4f\t%d\n", fillRefill, FlowVector.at(k), 0);

        /* 2 Stop after filling valve fill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, 0);

        /* 3 Stop after filling valve refill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, 1);

        /* High volume of dosing? More than 5 ml? */
        if(((NSteps*fillRefill)/60000.0)*(FlowVector.at(k)) > ((fillRefill)/60000.0)*(absoluteFlow)){

            /* 4 Refill after filling valve refill */
            fprintf(pFile, "%d\t%.4f\t%d\n", fillRefill, -FlowVector.at(k), 1);
        }
        /* Lower than 5 ml? */
        else{

            /* No refilling until the last step */
            if(i<NSteps){

                /* 4 Refill after filling valve refill */
                fprintf(pFile, "%d\t%d\t%d\n", fillRefill, 0, 1);
            }
            /* Use last step for refilling */
            else{

                /* 4 Refill after filling valve refill */
                fprintf(pFile, "%d\t%.4f\t%d\n", fillRefill, -FlowVector.at(k)*NSteps, 1);
            }
        }

        /* Is it the last refill pattern? */
        if(i == NSteps){

            /* 5 stop for MEASUREMENT during this block valve refill Last Refill */
            fprintf(pFile, "%d\t%d\t%d\n", longBreak, 0, 1);

        }else{
            /* 5 stop for MEASUREMENT during this block valve refill */
            fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, 1);
        }

        /* 6 Stop after measurement valve fill */
        fprintf(pFile, "%d\t%d\t%d\n", shortBreak, 0, 0);
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
