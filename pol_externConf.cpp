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
    stockSolutions.reserve(6);
    maxConcentrations.reserve(6);
    minConcentrations.reserve(6);

    /* Configuration File generator object */
    ConfigurationFileGenerator = new Pol_configFilesGenerator();

    /* Set size of the concentrations vectors */
    GlucoseConcentration.resize(0);
    Impurity1Concentration.resize(0);
    Impurity2Concentration.resize(0);
    Impurity3Concentration.resize(0);
    Impurity4Concentration.resize(0);
    Impurity5Concentration.resize(0);

    /* Create vectors of Flows */
    WaterFlow.resize(0);
    GlucoseFlow.resize(0);
    Impurity1Flow.resize(0);
    Impurity2Flow.resize(0);
    Impurity3Flow.resize(0);
    Impurity4Flow.resize(0);
    Impurity5Flow.resize(0);

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

    /* Gaps between concentrations */
    double gapGlucose, gapImpurity1, gapImpurity2, gapImpurity3, gapImpurity4, gapImpurity5 ;

    /* Set size of the concentrations vectors */
    GlucoseConcentration.resize(ConfigurationFileGenerator->NConcentrations);

    /* Is Impurity 1 active? */
    if(ConfigurationFileGenerator->activeSubstances.at(1)){
        Impurity1Concentration.resize(ConfigurationFileGenerator->NConcentrations);
        Impurity1Flow.resize(ConfigurationFileGenerator->NConcentrations);
        gapImpurity1 = (maxConcentrations.at(1) - minConcentrations.at(1))/(ConfigurationFileGenerator->NConcentrations-1);

    }

    /* Is Impurity 2 active? */
    if(ConfigurationFileGenerator->activeSubstances.at(2)){
        Impurity2Concentration.resize(ConfigurationFileGenerator->NConcentrations);
        Impurity2Flow.resize(ConfigurationFileGenerator->NConcentrations);
        gapImpurity2 = (maxConcentrations.at(2) - minConcentrations.at(2))/(ConfigurationFileGenerator->NConcentrations-1);

    }

    /* Is Impurity 3 active? */
    if(ConfigurationFileGenerator->activeSubstances.at(3)){
        Impurity3Concentration.resize(ConfigurationFileGenerator->NConcentrations);
        Impurity3Flow.resize(ConfigurationFileGenerator->NConcentrations);
        gapImpurity3 = (maxConcentrations.at(3) - minConcentrations.at(3))/(ConfigurationFileGenerator->NConcentrations-1);

    }

    /* Is Impurity 4 active? */
    if(ConfigurationFileGenerator->activeSubstances.at(4)){
        Impurity4Concentration.resize(ConfigurationFileGenerator->NConcentrations);
        Impurity4Flow.resize(ConfigurationFileGenerator->NConcentrations);
        gapImpurity4 = (maxConcentrations.at(4) - minConcentrations.at(4))/(ConfigurationFileGenerator->NConcentrations-1);

    }

    /* Is Impurity 5 active? */
    if(ConfigurationFileGenerator->activeSubstances.at(5)){
        Impurity5Concentration.resize(ConfigurationFileGenerator->NConcentrations);
        Impurity5Flow.resize(ConfigurationFileGenerator->NConcentrations);
        gapImpurity5 = (maxConcentrations.at(5) - minConcentrations.at(5))/(ConfigurationFileGenerator->NConcentrations-1);

    }

    /* Create vectors of Flows */
    WaterFlow.resize(ConfigurationFileGenerator->NConcentrations);
    GlucoseFlow.resize(ConfigurationFileGenerator->NConcentrations);

    /* Measurements vector */
    QVector <double> Nmeasurements(ConfigurationFileGenerator->NConcentrations);

    /* Get gaps between concentrations */
    gapGlucose = (maxConcentrations.at(0) - minConcentrations.at(0))/(ConfigurationFileGenerator->NConcentrations-1);

    /* Don't get gap when the number of concentrations is 1 */
    if(ConfigurationFileGenerator->NConcentrations == 1){
        gapGlucose = 0;
        gapImpurity1 = 0;
        gapImpurity2 = 0;
        gapImpurity3 = 0;
        gapImpurity4 = 0;
        gapImpurity5 = 0;

    }

    /* Create vectors with indexes and solution concentrations */
    for(int k =0; k < ConfigurationFileGenerator->NConcentrations; k++){

        /* Concentrations */
        GlucoseConcentration.replace(k,(minConcentrations.at(0)) + (k*gapGlucose));

        /* Is Impurity 1 active? */
        if(ConfigurationFileGenerator->activeSubstances.at(1)){
            Impurity1Concentration.replace(k,minConcentrations.at(1) + k*gapImpurity1);
        }

        /* Is Impurity 2 active? */
        if(ConfigurationFileGenerator->activeSubstances.at(2)){
            Impurity2Concentration.replace(k,minConcentrations.at(2) + k*gapImpurity2);
        }

        /* Is Impurity 3 active? */
        if(ConfigurationFileGenerator->activeSubstances.at(3)){
            Impurity3Concentration.replace(k,minConcentrations.at(3) + k*gapImpurity3);
        }

        /* Is Impurity 4 active? */
        if(ConfigurationFileGenerator->activeSubstances.at(4)){
            Impurity4Concentration.replace(k,minConcentrations.at(4) + k*gapImpurity4);
        }

        /* Is Impurity 5 active? */
        if(ConfigurationFileGenerator->activeSubstances.at(5)){
            Impurity5Concentration.replace(k,minConcentrations.at(5) + k*gapImpurity5);
        }

        Nmeasurements.replace(k, k);

    }

    /* Count active substances */
    int activeSubs = 0;

    /* Active substances? */
    for(int g = 0; g < ConfigurationFileGenerator->activeSubstances.length(); g++){

        /* Sum the active substances */
        activeSubs = activeSubs + ConfigurationFileGenerator->activeSubstances.at(g);
    }

    /* Is there more than 1 substance available? */
    if(activeSubs > 1){

        /* Check correlation factor, skip if the vector has 4 or less elements */
        while( true && ConfigurationFileGenerator->NConcentrations > 4){

            /* Random shuffle the vectors */
            std::random_shuffle(GlucoseConcentration.begin(), GlucoseConcentration.end());
            std::random_shuffle(Impurity1Concentration.begin(), Impurity1Concentration.end());
            std::random_shuffle(Impurity2Concentration.begin(), Impurity2Concentration.end());
            std::random_shuffle(Impurity3Concentration.begin(), Impurity3Concentration.end());
            std::random_shuffle(Impurity4Concentration.begin(), Impurity4Concentration.end());
            std::random_shuffle(Impurity5Concentration.begin(), Impurity5Concentration.end());

            float threshold = 0.05;

            /* Correlation of glucose and number of measurements */
            if(ConfigurationFileGenerator->activeSubstances.at(0)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(Nmeasurements, GlucoseConcentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Glucose and Impurity 1 */
            if(ConfigurationFileGenerator->activeSubstances.at(0) && ConfigurationFileGenerator->activeSubstances.at(1)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(GlucoseConcentration, Impurity1Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Glucose and Impurity 2 */
            if(ConfigurationFileGenerator->activeSubstances.at(0) && ConfigurationFileGenerator->activeSubstances.at(2)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(GlucoseConcentration, Impurity2Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Glucose and Impurity 3 */
            if(ConfigurationFileGenerator->activeSubstances.at(0) && ConfigurationFileGenerator->activeSubstances.at(3)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(GlucoseConcentration, Impurity3Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Glucose and Impurity 4 */
            if(ConfigurationFileGenerator->activeSubstances.at(0) && ConfigurationFileGenerator->activeSubstances.at(4)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(GlucoseConcentration, Impurity4Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Glucose and Impurity 4 */
            if(ConfigurationFileGenerator->activeSubstances.at(0) && ConfigurationFileGenerator->activeSubstances.at(5)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(GlucoseConcentration, Impurity5Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Impurity 1 and Impurity 2 */
            if(ConfigurationFileGenerator->activeSubstances.at(1) && ConfigurationFileGenerator->activeSubstances.at(2)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(Impurity2Concentration, Impurity1Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Impurity 1 and Impurity 3 */
            if(ConfigurationFileGenerator->activeSubstances.at(1) && ConfigurationFileGenerator->activeSubstances.at(3)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(Impurity3Concentration, Impurity1Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Impurity 1 and Impurity 4 */
            if(ConfigurationFileGenerator->activeSubstances.at(1) && ConfigurationFileGenerator->activeSubstances.at(4)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(Impurity4Concentration, Impurity1Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Impurity 1 and Impurity 5 */
            if(ConfigurationFileGenerator->activeSubstances.at(1) && ConfigurationFileGenerator->activeSubstances.at(5)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(Impurity5Concentration, Impurity1Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Impurity 2 and Impurity 3 */
            if(ConfigurationFileGenerator->activeSubstances.at(2) && ConfigurationFileGenerator->activeSubstances.at(3)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(Impurity3Concentration, Impurity2Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Impurity 2 and Impurity 4 */
            if(ConfigurationFileGenerator->activeSubstances.at(2) && ConfigurationFileGenerator->activeSubstances.at(4)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(Impurity4Concentration, Impurity2Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Impurity 2 and Impurity 5 */
            if(ConfigurationFileGenerator->activeSubstances.at(2) && ConfigurationFileGenerator->activeSubstances.at(5)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(Impurity5Concentration, Impurity2Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Impurity 3 and Impurity 4 */
            if(ConfigurationFileGenerator->activeSubstances.at(3) && ConfigurationFileGenerator->activeSubstances.at(4)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(Impurity4Concentration, Impurity3Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Impurity 3 and Impurity 5 */
            if(ConfigurationFileGenerator->activeSubstances.at(3) && ConfigurationFileGenerator->activeSubstances.at(5)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(Impurity5Concentration, Impurity3Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* Correlation between Impurity 4 and Impurity 5 */
            if(ConfigurationFileGenerator->activeSubstances.at(4) && ConfigurationFileGenerator->activeSubstances.at(5)){

                /* Is the factor ok?, if not start again */
                if(ConfigurationFileGenerator->correlationCoefficient(Impurity5Concentration, Impurity4Concentration, ConfigurationFileGenerator->NConcentrations) > threshold){ continue;}
            }

            /* If no correlation or just a few elements, then stop doing random order */
            break;

        }
    }else{

        /* Random Indexes if there is only 1 substance or the vector has 4 or less elements */
        std::random_shuffle(GlucoseConcentration.begin(), GlucoseConcentration.end());
        std::random_shuffle(Impurity1Concentration.begin(), Impurity1Concentration.end());
        std::random_shuffle(Impurity2Concentration.begin(), Impurity2Concentration.end());
        std::random_shuffle(Impurity3Concentration.begin(), Impurity3Concentration.end());
        std::random_shuffle(Impurity4Concentration.begin(), Impurity4Concentration.end());
        std::random_shuffle(Impurity5Concentration.begin(), Impurity5Concentration.end());


    }

    /* Flow Calculation */
    if(ConfigurationFileGenerator->intervalMode){

        /* Get the flows for each substance */
        if(ConfigurationFileGenerator->activeSubstances.at(0)){
            GlucoseFlow.replace(0,maxConcentrations.at(0)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(0))));
        }

        if(ConfigurationFileGenerator->activeSubstances.at(1)){
            Impurity1Flow.replace(0,maxConcentrations.at(1)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(1))));
        }

        if(ConfigurationFileGenerator->activeSubstances.at(2)){
            Impurity2Flow.replace(0,maxConcentrations.at(2)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(2))));
        }

        if(ConfigurationFileGenerator->activeSubstances.at(3)){
            Impurity3Flow.replace(0,maxConcentrations.at(3)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(3))));
        }

        if(ConfigurationFileGenerator->activeSubstances.at(4)){
            Impurity4Flow.replace(0,maxConcentrations.at(4)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(4))));
        }

        if(ConfigurationFileGenerator->activeSubstances.at(5)){
            Impurity5Flow.replace(0,maxConcentrations.at(5)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(5))));
        }

        /* Which substances are active? Calculate the right flow to substract from water */
        double Flow = 0;

        /* If glucose is active consider its flow */
        if(ConfigurationFileGenerator->activeSubstances.at(0)){
            Flow = Flow + GlucoseFlow.at(0);
        }

        /* If Impurity 1 is active consider its flow */
        if(ConfigurationFileGenerator->activeSubstances.at(1)){
            Flow = Flow + Impurity1Flow.at(0);
        }

        /* If Impurity 2 is active consider its flow */
        if(ConfigurationFileGenerator->activeSubstances.at(2)){
            Flow = Flow + Impurity2Flow.at(0);
        }

        /* If Impurity 3 is active consider its flow */
        if(ConfigurationFileGenerator->activeSubstances.at(3)){
            Flow = Flow + Impurity3Flow.at(0);
        }

        /* If Impurity 4 is active consider its flow */
        if(ConfigurationFileGenerator->activeSubstances.at(4)){
            Flow = Flow + Impurity4Flow.at(0);
        }

        /* If Impurity 5 is active consider its flow */
        if(ConfigurationFileGenerator->activeSubstances.at(5)){
            Flow = Flow + Impurity5Flow.at(0);
        }

        /* Water Flow */
        WaterFlow.replace(0,ConfigurationFileGenerator->absoluteFlow - Flow);

    }else{

        for(int i =0; i < ConfigurationFileGenerator->NConcentrations; i++){

            /* Get the flows for each substance */
            if(ConfigurationFileGenerator->activeSubstances.at(0)){
                GlucoseFlow.replace(i,GlucoseConcentration.at(i)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(0))));
            }

            if(ConfigurationFileGenerator->activeSubstances.at(1)){
                Impurity1Flow.replace(i,Impurity1Concentration.at(i)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(1))));
            }

            if(ConfigurationFileGenerator->activeSubstances.at(2)){
                Impurity2Flow.replace(i,Impurity2Concentration.at(i)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(2))));
            }

            if(ConfigurationFileGenerator->activeSubstances.at(3)){
                Impurity3Flow.replace(i,Impurity3Concentration.at(i)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(3))));
            }

            if(ConfigurationFileGenerator->activeSubstances.at(4)){
                Impurity4Flow.replace(i,Impurity4Concentration.at(i)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(4))));
            }

            if(ConfigurationFileGenerator->activeSubstances.at(5)){
                Impurity5Flow.replace(i,Impurity5Concentration.at(i)*((ConfigurationFileGenerator->absoluteFlow)/(stockSolutions.at(5))));
            }

            /* Which substances are active? Calculate the right flow to substract from water */
            double Flow = 0;

            /* If glucose is active consider its flow */
            if(ConfigurationFileGenerator->activeSubstances.at(0)){
                Flow = Flow + GlucoseFlow.at(i);
            }

            /* If Impurity 1 is active consider its flow */
            if(ConfigurationFileGenerator->activeSubstances.at(1)){
                Flow = Flow + Impurity1Flow.at(i);
            }

            /* If Impurity 2 is active consider its flow */
            if(ConfigurationFileGenerator->activeSubstances.at(2)){
                Flow = Flow + Impurity2Flow.at(i);
            }

            /* If Impurity 3 is active consider its flow */
            if(ConfigurationFileGenerator->activeSubstances.at(3)){
                Flow = Flow + Impurity3Flow.at(i);
            }

            /* If Impurity 4 is active consider its flow */
            if(ConfigurationFileGenerator->activeSubstances.at(4)){
                Flow = Flow + Impurity4Flow.at(i);
            }

            /* If Impurity 5 is active consider its flow */
            if(ConfigurationFileGenerator->activeSubstances.at(5)){
                Flow = Flow + Impurity5Flow.at(i);
            }

            /* Water Flow */
            WaterFlow.replace(i,ConfigurationFileGenerator->absoluteFlow - Flow);

        }
    }

    /* Write all scripts */
    writeScripts();

}

/**
 * @brief Write the scripts
 */
void Pol_ExternConf::writeScripts(void){

    /* Create the Spectrometer Script */
    ConfigurationFileGenerator->GenerateSpectrometerConfiguration(pathForScripts, GlucoseConcentration, Impurity1Concentration, Impurity2Concentration,  Impurity3Concentration,
                                                                   Impurity4Concentration,  Impurity5Concentration, stockSolutions, minWavelength, maxWavelength, UserTimeInterval);

    /* Remove the existing pump files */
    removeExistingFiles();

    /* If glucose is active, then generate its pump script */
    if(ConfigurationFileGenerator->activeSubstances.at(0)){

        /* Create the Glucose pump script */
        ConfigurationFileGenerator->GeneratePumpScripts(pathForScripts, "/GlucosePumpScript.nfp", GlucoseFlow);
    }

    /* If Impurity 1 is active, then generate its pump script */
    if(ConfigurationFileGenerator->activeSubstances.at(1)){

        /* Create the Impurity 1 pump script */
        ConfigurationFileGenerator->GeneratePumpScripts(pathForScripts, "/Impurity1PumpScript.nfp", Impurity1Flow);
    }

    /* If impurity 2 is active, then generate its pump script */
    if(ConfigurationFileGenerator->activeSubstances.at(2)){

        /* Create the Impurity 2 pump script */
        ConfigurationFileGenerator->GeneratePumpScripts(pathForScripts, "/Impurity2PumpScript.nfp", Impurity2Flow);
    }

    /* If impurity 3 is active, then generate its pump script */
    if(ConfigurationFileGenerator->activeSubstances.at(3)){

        /* Create the Impurity 3 pump script */
        ConfigurationFileGenerator->GeneratePumpScripts(pathForScripts, "/Impurity3PumpScript.nfp", Impurity3Flow);
    }

    /* If impurity 4 is active, then generate its pump script */
    if(ConfigurationFileGenerator->activeSubstances.at(4)){

        /* Create the Impurity 4 pump script */
        ConfigurationFileGenerator->GeneratePumpScripts(pathForScripts, "/Impurity4PumpScript.nfp", Impurity4Flow);
    }

    /* If impurity 5 is active, then generate its pump script */
    if(ConfigurationFileGenerator->activeSubstances.at(5)){

        /* Create the Impurity 5 pump script */
        ConfigurationFileGenerator->GeneratePumpScripts(pathForScripts, "/Impurity5PumpScript.nfp", Impurity5Flow);
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

    /* If there are some pump scripts already, remove them */
    QFile file4(folder.absolutePath() + "/Impurity3PumpScript.nfp");

    /* Does the pump file for Impurity 3 exists? */
    if(file4.exists()){

        /* Remove the impurity 3 pump file */
        file4.remove();
    }

    /* If there are some pump scripts already, remove them */
    QFile file5(folder.absolutePath() + "/Impurity4PumpScript.nfp");

    /* Does the pump file for Impurity 4 exists? */
    if(file5.exists()){

        /* Remove the impurity 4 pump file */
        file5.remove();
    }

    /* If there are some pump scripts already, remove them */
    QFile file6(folder.absolutePath() + "/Impurity5PumpScript.nfp");

    /* Does the pump file for Impurity 5 exists? */
    if(file6.exists()){

        /* Remove the impurity 5 pump file */
        file6.remove();
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
    else if(mTime >= 60 && mTime < 3600){

        mTime = mTime/60;
        unit = "min";
        precision = 2;

        /* Hours */
    }else if(mTime >= 3600 && mTime < 86400){

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
