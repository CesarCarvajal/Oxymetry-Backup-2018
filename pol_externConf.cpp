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

/**
 * @brief Constructor of 'Pol_ExternConf' class
 */
Pol_ExternConf::Pol_ExternConf()
{

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

    double gapGlucose, gapImpurity1, gapImpurity2;

    QVector <double> GlucoseConcentration(NConcentrations);
    QVector <double> Impurity1Concentration(NConcentrations);
    QVector <double> Impurity2Concentration(NConcentrations);

    QVector <double> WaterFlow(NConcentrations);
    QVector <double> GlucoseFlow(NConcentrations);
    QVector <double> Impurity1Flow(NConcentrations);
    QVector <double> Impurity2Flow(NConcentrations);

    for(int index= 0; index < 1000; index++){

        /* Gap between concentrations */
        gapGlucose = (maxConcentrations.at(1) - minConcentrations.at(1))/(NConcentrations-1);
        gapImpurity1 = (maxConcentrations.at(2) - minConcentrations.at(2))/(NConcentrations-1);
        gapImpurity2 = (maxConcentrations.at(3) - minConcentrations.at(3))/(NConcentrations-1);

        /* Create vectors with indexes and solution concentrations */
        for(int k =0; k < NConcentrations; k++){

            /* Concentrations */
            GlucoseConcentration.append(minConcentrations.at(1) + k*gapGlucose);
            Impurity1Concentration.append(minConcentrations.at(2) + k*gapImpurity1);
            Impurity2Concentration.append(minConcentrations.at(3) + k*gapImpurity2);
        }

        /* Random Indexes */
        std::random_shuffle(GlucoseConcentration.begin(), GlucoseConcentration.end());
        std::random_shuffle(Impurity1Concentration.begin(), Impurity1Concentration.end());
        std::random_shuffle(Impurity2Concentration.begin(), Impurity2Concentration.end());

        /* Flow Calculation */
        for(int k =0; k < NConcentrations; k++){

            /* Concentrations */
            GlucoseFlow.append((GlucoseConcentration.at(k))/(stockSolutions.at(2)*absoluteFlow));
            Impurity1Flow.append((Impurity1Concentration.at(k))/(stockSolutions.at(3)*absoluteFlow));
            Impurity2Flow.append((Impurity2Concentration.at(k))/(stockSolutions.at(4)*absoluteFlow));

            /* Water Flow */
            WaterFlow.append(absoluteFlow - (GlucoseFlow.at(k) + Impurity1Flow.at(k) + Impurity2Flow.at(k)));
        }


    }

    /* Create the pump scripts */
    GeneratePumpScripts();

}

/**
 * @brief Save Configuration to file
 */
void Pol_ExternConf::SaveConfToFile(void){

    /* Did user select a path? */
    //   if (!path.isEmpty())
    //   {

    //      FILE *file = fopen(path.toLatin1().data(), "wt");

    //      for(int k = 1 ; k < NrMeasurements+1; k++){

    //       QString line = QString::number(k*TimeIntervals*1000) + ";" + "0C1_0C2_"
    //               + QString::number(integrationTime) + "ms_" + QString::number(freqToMeasure) + "Hz_" + QString::number(k) + ";" + QString::number(numSpectra) +
    //               ";" + QString::number(integrationTime) + ";" + QString::number(numberOfAverages) + ";" + QString::number(freqToMeasure) + "\n";

    //        fprintf(file, "%s", line.toLatin1().data());
    //    }

    /* Close file */
    //     fclose(file);
    //     file = nullptr;
    //  }
}

/**
 * @brief Generate Pump Scripts
 */
void Pol_ExternConf::GeneratePumpScripts(void){


}

/**
 * @brief Destructor of 'Pol_ExternConf' class
 */
Pol_ExternConf::~Pol_ExternConf(void)
{

    delete process1;
    process1 = nullptr;


}
