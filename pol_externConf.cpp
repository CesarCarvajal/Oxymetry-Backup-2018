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
#include "pol_configFilesGenerator.h"
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
    /* Set size of vectors: there are 3 substances + 1 water */
    stockSolutions.reserve(3);
    maxConcentrations.reserve(3);
    minConcentrations.reserve(3);

    /* Configuration File generator object */
    ConfigurationFileGenerator = new Pol_configFilesGenerator();

    /* Set size of the concentrations vectors */
    GlucoseConcentration.resize(0);
    Impurity1Concentration.resize(0);
    Impurity2Concentration.resize(0);

    /* Create vectors of Flows */
    WaterFlow.resize(0);
    GlucoseFlow.resize(0);
    Impurity1Flow.resize(0);
    Impurity2Flow.resize(0);

    /* Restart paths */
    pathForScripts = "";

    /* Restart limits */
    minWavelength = 200;
    maxWavelength = 1200;
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

            /* Show critical error if the shortcut doesn't exist or the software isn't installed */
            showCritical(QString("Nemesys Pump Software shortcut in desktop named 'NEMESYS' is missing!, Please check if the software is installed, and create a desktop shortcut for it!"), QString(""));
            return;

        }
    }
}

/**
 * @brief Replaces Matlab Functions, Pump Patterns Calculator
 */
void Pol_ExternConf::pumpsPatternCalculator(void){

    /* Set size of the concentrations vectors */
    GlucoseConcentration.resize(ConfigurationFileGenerator->NConcentrations);
    Impurity1Concentration.resize(ConfigurationFileGenerator->NConcentrations);
    Impurity2Concentration.resize(ConfigurationFileGenerator->NConcentrations);

    /* Create vectors of Flows */
    WaterFlow.resize(ConfigurationFileGenerator->NConcentrations);
    GlucoseFlow.resize(ConfigurationFileGenerator->NConcentrations);
    Impurity1Flow.resize(ConfigurationFileGenerator->NConcentrations);
    Impurity2Flow.resize(ConfigurationFileGenerator->NConcentrations);

    /* Measurements vector */
    QVector <double> Nmeasurements(ConfigurationFileGenerator->NConcentrations);

    /* Gaps between concentrations */
    double gapGlucose, gapImpurity1, gapImpurity2;

    /* Get gaps between concentrations */
    gapGlucose = (maxConcentrations.at(0) - minConcentrations.at(0))/(ConfigurationFileGenerator->NConcentrations-1);
    gapImpurity1 = (maxConcentrations.at(1) - minConcentrations.at(1))/(ConfigurationFileGenerator->NConcentrations-1);
    gapImpurity2 = (maxConcentrations.at(2) - minConcentrations.at(2))/(ConfigurationFileGenerator->NConcentrations-1);

    /* Don't get gap when the number of concentrations is 1 */
    if(ConfigurationFileGenerator->NConcentrations == 1){
        gapGlucose = 0;
        gapImpurity1 = 0;
        gapImpurity2 = 0;
    }

    /* Create vectors with indexes and solution concentrations */
    for(int k =0; k < ConfigurationFileGenerator->NConcentrations; k++){

        /* Concentrations */
        GlucoseConcentration.replace(k,(minConcentrations.at(0)) + (k*gapGlucose));
        Impurity1Concentration.replace(k,minConcentrations.at(1) + k*gapImpurity1);
        Impurity2Concentration.replace(k,minConcentrations.at(2) + k*gapImpurity2);
        Nmeasurements.replace(k, k);

    }

    /* Is there more than 1 substance available? */
    if(ConfigurationFileGenerator->glucoseActive + ConfigurationFileGenerator->Imp1Active + ConfigurationFileGenerator->Imp2Active > 1){

        /* Check correlation factor, skip if the vector has 4 or less elements */
        while( true && ConfigurationFileGenerator->NConcentrations > 4){

            /* Correlation factors */
            float corrcoeffGlucImp1= 1, corrcoeffTime = 1, corrcoeffImp1Imp2= 1, corrcoeffGlucImp2= 1;

            /* Random shuffle the vectors */
            std::random_shuffle(GlucoseConcentration.begin(), GlucoseConcentration.end());
            std::random_shuffle(Impurity1Concentration.begin(), Impurity1Concentration.end());
            std::random_shuffle(Impurity2Concentration.begin(), Impurity2Concentration.end());

            /* Correlation of glucose and number of measurements */
            corrcoeffTime = ConfigurationFileGenerator->correlationCoefficient(Nmeasurements, GlucoseConcentration, ConfigurationFileGenerator->NConcentrations);

            /* Is the factor ok?, if not start again */
            if(corrcoeffTime > 0.005){ continue;}

            /* Correlation between Glucose and Impurity 1 */
            if(ConfigurationFileGenerator->glucoseActive && ConfigurationFileGenerator->Imp1Active){
                corrcoeffGlucImp1 = ConfigurationFileGenerator->correlationCoefficient(GlucoseConcentration, Impurity1Concentration, ConfigurationFileGenerator->NConcentrations);

                /* Is the factor ok?, if not start again */
                if(corrcoeffGlucImp1 > 0.005){ continue;}
            }

            /* Correlation between Impurity 1 and Impurity 2 */
            if(ConfigurationFileGenerator->Imp1Active && ConfigurationFileGenerator->Imp2Active){
                corrcoeffImp1Imp2 = ConfigurationFileGenerator->correlationCoefficient(Impurity2Concentration, Impurity1Concentration, ConfigurationFileGenerator->NConcentrations);

                /* Is the factor ok?, if not start again */
                if(corrcoeffImp1Imp2 > 0.005){ continue;}
            }

            /* Correlation between Glucose and Impurity 2 */
            if(ConfigurationFileGenerator->glucoseActive && ConfigurationFileGenerator->Imp2Active){
                corrcoeffGlucImp2 = ConfigurationFileGenerator->correlationCoefficient(GlucoseConcentration, Impurity2Concentration, ConfigurationFileGenerator->NConcentrations);

                /* Is the factor ok?, if not start again */
                if(corrcoeffGlucImp2 > 0.005){ continue;}
            }

            /* If no correlation or just a few elements, then stop doing random order */
            break;

        }
    }else{

        /* Random Indexes if there is only 1 substance or the vector has 4 or less elements */
        std::random_shuffle(GlucoseConcentration.begin(), GlucoseConcentration.end());
        std::random_shuffle(Impurity1Concentration.begin(), Impurity1Concentration.end());
        std::random_shuffle(Impurity2Concentration.begin(), Impurity2Concentration.end());

    }

    /* Flow Calculation */
    for(int i =0; i < ConfigurationFileGenerator->NConcentrations; i++){

        /* Get the flows for each substance */
        GlucoseFlow.replace(i,GlucoseConcentration.at(i)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(0))));
        Impurity1Flow.replace(i,Impurity1Concentration.at(i)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(1))));
        Impurity2Flow.replace(i,Impurity2Concentration.at(i)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(2))));

        /* Which substances are active? Calculate the right flow to substract from water */
        double Flow = 0;

        /* If glucose is active consider its flow */
        if(ConfigurationFileGenerator->glucoseActive){
            Flow = Flow + GlucoseFlow.at(i);
        }

        /* If Impurity 1 is active consider its flow */
        if(ConfigurationFileGenerator->Imp1Active){
            Flow = Flow + Impurity1Flow.at(i);
        }

        /* If Impurity 2 is active consider its flow */
        if(ConfigurationFileGenerator->Imp2Active){
            Flow = Flow + Impurity2Flow.at(i);
        }

        /* Water Flow */
        WaterFlow.replace(i,ConfigurationFileGenerator->absoluteFlow - Flow);

    }

    /* Write all scripts */
    writeScripts();

}

/**
 * @brief Write the scripts
 */
void Pol_ExternConf::writeScripts(void){

    /* Create the Spectrometer Script */
    ConfigurationFileGenerator->GenerateSpectrometerConfiguration(pathForScripts, GlucoseConcentration, Impurity1Concentration, Impurity2Concentration, stockSolutions, minWavelength, maxWavelength);

    /* Remove the existing pump files */
    removeExistingFiles();

    /* If glucose is active, then generate its pump script */
    if(ConfigurationFileGenerator->glucoseActive){

        /* Create the Glucose pump script */
        ConfigurationFileGenerator->GeneratePumpScripts(pathForScripts, "/GlucosePumpScript.nfp", GlucoseFlow);
    }

    /* If Impurity 1 is active, then generate its pump script */
    if(ConfigurationFileGenerator->Imp1Active){

        /* Create the Impurity 1 pump script */
        ConfigurationFileGenerator->GeneratePumpScripts(pathForScripts, "/Impurity1PumpScript.nfp", Impurity1Flow);
    }

    /* If impurity 2 is active, then generate its pump script */
    if(ConfigurationFileGenerator->Imp2Active){

        /* Create the Impurity 2 pump script */
        ConfigurationFileGenerator->GeneratePumpScripts(pathForScripts, "/Impurity2PumpScript.nfp", Impurity2Flow);
    }

    /* Create the Water pump script */
    ConfigurationFileGenerator->GeneratePumpScripts(pathForScripts, "/WaterPumpScript.nfp", WaterFlow);

}

/**
 * @brief If there are pump files already, delete them
 */
void Pol_ExternConf::removeExistingFiles(void){

    /* Get folder information */
    QFileInfo folder(pathForScripts);

    /* If there are some pump scripts already, remove them */
    QFile file(folder.absolutePath() + "/GlucosePumpScript.nfp");

    /* Does the pump file for glucose exist? */
    if(file.exists()){

        /* Remove the glucose pump file */
        file.remove();
    }

    /* If there are some pump scripts already, remove them */
    QFile file2(folder.absolutePath() + "/Impurity1PumpScript.nfp");

    /* Does the pump file for Impurity 1 exist? */
    if(file2.exists()){

        /* Remove the impurity 1 pump file */
        file2.remove();
    }

    /* If there are some pump scripts already, remove them */
    QFile file3(folder.absolutePath() + "/Impurity2PumpScript.nfp");

    /* Does the pump file for Impurity 2 exists? */
    if(file3.exists()){

        /* Remove the impurity 2 pump file */
        file3.remove();
    }
}

/**
 * @brief Convert the time to minutes, hours or days
 *
 */
QStringList Pol_ExternConf::TimeConverter(double mTime){

    /* Save the time and its unit */
    QStringList timeUnits;

    /* Unit */
    QString unit = "";

    /* Precision */
    int precision = 3;

    /* Convert the time to minutes, hours or days */
    if(mTime < 60){
        unit = "sec";
        precision = 0;

    }
    /* minutes */
    else if(mTime > 60 && mTime < 3600){

        mTime = mTime/60;
        unit = "min";
        precision = 2;

        /* Hours */
    }else if(mTime > 3600 && mTime < 86400){

        mTime = mTime/3600;
        unit = "hours";
        precision = 3;

        /* Days */
    }else if(mTime >= 86400){

        mTime = mTime/86400;
        unit = "days";
        precision = 4;
    }

    /* Return the time and its unit */
    timeUnits.append(QString::number(mTime,'f', precision));
    timeUnits.append(unit);

    return timeUnits;
}


/**
 * @brief Destructor of 'Pol_ExternConf' class
 */
Pol_ExternConf::~Pol_ExternConf(void)
{

    delete process1;
    process1 = nullptr;

    delete ConfigurationFileGenerator;
    ConfigurationFileGenerator = nullptr;

}
