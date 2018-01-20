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

/*
 * External includes
 */

/* Qt libraries */
#include <QMessageBox>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <QTime>
#include <QDate>

/*
 * Internal includes
 */

/* General stuff */
#include <math.h>
#include <algorithm>
#include <messages.h>

/* FFT */
#include "pol_fft.h"
#include <fftw3.h>
#include <complex.h>

/* Panel */
#include "ui_panel.h"
#include "panel.h"

/* Spectrometer control */
#include "spectrometer.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Get the Data from a FFT File type.
 */
void fft::getFFTfromFFTData(QFileInfo fileInformation)
{
    /* Enroute File */
    QFile file(fileInformation.absoluteFilePath());

    /* Does the File exists? */
    if(!file.exists()){
        /* If not, tell the user that it coulnd't be found */
        showWarning("File not Found!", "");
        return;
    }

    /* Get Information from File Name */
    ReadFileName(fileInformation.completeBaseName(), fileInformation.absoluteFilePath(), true);

    /* Create the readed row */
    QString Row;

    /* Initialize row counter */
    int rowcounter = 0;

    /* Open the file */
    if(file.open(QIODevice::ReadOnly)) {

        /* Get lines from file */
        QTextStream stream(&file);

        /* Read row by row */
        while(!stream.atEnd()){

            /* When should it start reading the FFT data? */
            bool read = false;

            /* Read the current line in file */
            Row = stream.readLine();

            /* Indicates where to start reading the numerical information from file */
            QString in = Row.at(0);

            /* If a number was found at the first position, then start reading */
            in.toInt(&read);

            /* Have already skipped the first lines and there is information to get? */
            if (read){

                /* Get the values from the line separated by 2 tabulars and replace (,) by (.) to read numbers */
                QStringList Readed_Row = Row.split("\t\t");
                Readed_Row.replaceInStrings(",",".");

                /* Save the wavelengths - Position 0 */
                wavelengths.append(Readed_Row.at(0).toDouble());

                /* Save the DC - Position 1 */
                fft_DC.append(Readed_Row.at(1).toDouble());

                /* Save W - Position 2 */
                fft_W.append(Readed_Row.at(2).toDouble());

                /* Save 2W - Position 3 */
                fft_2W.append(Readed_Row.at(3).toDouble());

                /* Calculate the Compensation signal, there is no need to have it in the file */
                fft_Compensation_Signal.append(fft_W.at(rowcounter)/fft_2W.at(rowcounter));

                /* What is the modulation frequency? */
                f_w = NrSpectra*(IntTime/1000)*FrequencyF;

                /* By default show the FFT values for the wavelength 537,57 nm */
                if (wavelengths.length() == SelectedWaveL){

                    for ( int  i = 0; i < NrSpectra/2; i++ )
                    {
                        /* Amplitude at all other frequencies are set to zero */
                        fft_data.append(0);

                        /* Which frequencies are shown in the FFT? */
                        time.append(i/(NrSpectra*(IntTime/1000)));
                    }

                    /* Get the frequency share amplitudes */
                    fft_data.replace(0,fft_DC.at(rowcounter));
                    fft_data.replace(f_w, fft_W.at(rowcounter));
                    fft_data.replace(2*f_w, fft_2W.at(rowcounter));

                }
                /* Counter of File Lines */
                rowcounter = rowcounter + 1;
            }
        }
    }

    /* Close file */
    file.close();
    return ;
}

/**
 * @brief Get the Raw Data from File and Calculate/Plot the FFT.
 */
void fft::getFFTfromRawData(QFileInfo fileInformation, bool Calibrating, double maxWavelength)
{
    /* Enroute File */
    QFile file(fileInformation.absoluteFilePath());

    /* Does the File exists? If no do nothing */
    if(!file.exists()){
        /* If not, tell the user that it coulnd't be found */
        showWarning("File not Found!", "");
        return;
    }

    /* Initialize row counter */
    QString Row;

    /* Initialize the spliter according to the type CS (Oxymetry) Software file */
    QString spliter = "\t\t";
    /* Start reading at the second column for CS file */
    int column = 1;

    /* But, Is it a TXT from Avantes Software? */
    bool isTXT = false;
    if(fileInformation.suffix()=="TXT"){
        /* Initialize the spliter according to the type TXT Avantes Software file */
        spliter = ";";
        /* Start reading at the forth column for TXT file */
        column = 3;
        /* Save what file type are you reading */
        isTXT = true;
    }

    /* Indicates when to start reading the numerical data from file */
    bool read = false;

    /* Initialize the row counter */
    int rowcounter = 0;

    /* Get Information from File Name if loading the data from a File*/
    if(!Calibrating){
        ReadFileName(fileInformation.completeBaseName(), fileInformation.absoluteFilePath(), isTXT);
    }else{
        /* If calibrating, there is not need to read the Nr. spectra, frequency, etc from file */
        InitializeFFTArrays();
        read = true;
    }

    /* Open the file */
    if(file.open(QIODevice::ReadOnly)) {

        /* Get lines from file */
        QTextStream stream(&file);

        /* Read row by row */
        while(!stream.atEnd()){

            /* Read the current line in file */
            Row = stream.readLine();

            /* If reading a file, the format is different than the file for calibrating */
            if(!Calibrating){

                /* Indicates where to start reading the numerical information from file */
                QString in = Row.at(1);

                /* If a number was found at the first position, then start reading */
                in.toInt(&read);
            }

            /* Have already skipped the first lines and there is information to get? */
            if (read && Row!=""){

                /* Get the values from the line separated by 2 tabulars and replace (,) by (.) to read numbers */
                QStringList Readed_Row = Row.split(spliter);
                Readed_Row.replaceInStrings(",",".");

                if(Readed_Row.at(0).toDouble() > maxWavelength && Calibrating){break;}

                /* Save the wavelengths in Position 0 */
                wavelengths.append(Readed_Row.at(0).toDouble());

                /* Save all the counts per row from Raw Data for future calculation of FFT */
                for (int j=column; j < Readed_Row.length(); j++){
                    counts.append(Readed_Row.at(j).toDouble());
                }

                /* The amount of columns of the file determines how many sprecta we have, only for raw data */
                NrSpectra = counts.length();

                /* With the current counts from a row, calculate the FFT */
                CalculateFFT(NrSpectra, counts);

                /* What is the modulation frequency? */
                f_w = NrSpectra*(IntTime/1000)*FrequencyF;

                /* From the Output array of FFT, save each of the frequency shares amplitude */
                fft_DC.append(sqrt(fabs((outputFFT[0][0]*outputFFT[0][0])) + fabs((outputFFT[0][1]*outputFFT[0][1]))));
                fft_W.append(sqrt(fabs((outputFFT[f_w][0]*outputFFT[f_w][0])) + fabs((outputFFT[f_w][1]*outputFFT[f_w][1]))));
                fft_2W.append(sqrt(fabs((outputFFT[2*f_w][0]*outputFFT[2*f_w][0])) + fabs((outputFFT[2*f_w][1]*outputFFT[2*f_w][1]))));
                fft_Compensation_Signal.append(fft_W.at(rowcounter)/fft_2W.at(rowcounter));

                /* By default show the FFT values for the wavelength 537,57 nm */
                if (wavelengths.length() == SelectedWaveL){
                    for ( int  i = 0; i < NrSpectra/2; i++ )
                    {
                        /* Amplitude at all frequencies */
                        fft_data.append(sqrt(fabs((outputFFT[i][0]*outputFFT[i][0])) + fabs((outputFFT[i][1]*outputFFT[i][1]))));

                        /* Which frequencies are shown in the FFT? */
                        time.append(i/(NrSpectra*(IntTime/1000)));
                    }
                }
                /* Counter of File Lines */
                rowcounter = rowcounter + 1;

                /* For the next calculation another counts from another row are needed, so restart the vector */
                counts.resize(0);

                /* Free Memory */
                fftw_free(outputFFT);
            }
        }
    }

    /* Close file and Free Memory*/
    file.close();
    return ;
}

/**
 * @brief Get Information from File Name and from the file itself, for example the amount of frequencies or spectra used.
 *
 * Every File Name should have exactly the form: 0C1_0C2_0ms_0Hz_0.TXT, 0C1_0C2_0ms_0Hz_0.CS, 0C1_0C2_0ms_0Hz_0_FFT.txt
 * Where the number 0 represents the value of the parameter.
 *
 * For .CS Files Always:
 * Row 4 has the Spectra Values.
 * Row 3 has the Number of Averages.
 *
 */
void fft::ReadFileName(QString ExtractInfoName, QString FilePath, bool isTXT)
{
    /* Data to get from the File Name */
    QString Concentration1_File,Concentration2_File, IntTime_File, Frequency_File = "";
    ConcentrationC1 = IntTime = FrequencyF = ConcentrationC2 = NrAverages = NrSpectra = 0;

    /* Which "_" are we? */
    int l=0;

    /* Iterate through the name and find the "_" on it */
    for(int i=0; i < ExtractInfoName.length();i++){
        if (ExtractInfoName[i] == "_"){
            l = l+1;
            continue;
        }

        /* Extract the Data from the File Name depending on which "_" are we */
        if (l==0 && (ExtractInfoName[i] != 'C') && (ExtractInfoName[i-1] != 'C')){
            Concentration1_File = Concentration1_File + ExtractInfoName[i];
        } else if (l==1 && (ExtractInfoName[i] != 'C') && (ExtractInfoName[i-1] != 'C')){
            Concentration2_File = Concentration2_File + ExtractInfoName[i];
        }else if (l==2 && ExtractInfoName[i] != 'm' && ExtractInfoName[i] != 's'){
            IntTime_File = IntTime_File + ExtractInfoName[i];
        }else if (l==3 &&  ExtractInfoName[i] != 'H'){
            Frequency_File = Frequency_File + ExtractInfoName[i];
        }else{
            if (ExtractInfoName[i] == 'H'){ break;}
            continue;
        }
    }

    /* Get the number from file name and save it */
    ConcentrationC1 = Concentration1_File.toDouble();
    ConcentrationC2 = Concentration2_File.toDouble();
    IntTime = IntTime_File.toDouble();
    FrequencyF = Frequency_File.toDouble();

    /* There is some information in the file very important to know how many data are we using */

    /* Open the file to get the Nr of Spectra and Average Nr. */
    QFile file(FilePath);

    /* Is it a file from Avantes or from Oxymetry Software? It defines where to start reading the data */
    int line = (isTXT) ? 4 : 3;

    /* Which column read? */
    int wordcounter = 1;

    /* Open the file */
    if(file.open(QIODevice::ReadOnly)) {

        QString ReadRow;
        QTextStream stream(&file);

        while(!stream.atEnd()){

            /* Read a line from the file */
            ReadRow = stream.readLine();

            /* Read the text and get the values */
            QStringList Readed_Row = ReadRow.split(" ");

            /* Get the number of Averages and Spectra from the file depending on its type */
            if (wordcounter==3 && isTXT==false){
                /* Third Row of CS file has the number of averages */
                NrAverages = Readed_Row.at(line).toDouble();
            }else if (wordcounter==4 && isTXT==false)
            {
                /* Row 4 of CS file has the number of spectra */
                NrSpectra = Readed_Row.at(line).toInt();
            }else if (wordcounter==3 && isTXT==true)
            {
                NrSpectra = Readed_Row.at(line).toInt();
                NrAverages = 0;
            }
            /* Which row are we reading? */
            wordcounter = wordcounter+1;

            /* Don't read further by now */
            if(wordcounter > 5) {break;}
        }
    }

    /* Close files */
    file.close();

    /* Initialize vectors */
    InitializeFFTArrays();
}

/**
 * @brief Initialize the FFT Vectors.
 *
 */
void fft::InitializeFFTArrays()
{
    /* Initialize the vectors to empty */
    if(!fft_DC.isEmpty()){
        fft_data.resize(0);
        fft_Compensation_Signal.resize(0);
        wavelengths.resize(0);
        fft_DC.resize(0);
        fft_W.resize(0);
        fft_2W.resize(0);
        counts.resize(0);
        time.resize(0);
    }
}

/**
 * @brief Calculate the FFT from incoming Data
 */
void fft::CalculateFFT(int N, QVector<double> Data)
{
    /* Create the arrays to save the FFT inputs and outputs */
    fftw_complex *in;
    fftw_plan plan_forward;

    /* Initialize the input and output arrays. */
    in = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);
    outputFFT = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * N);

    /* Create the Plan of the FFT */
    plan_forward = fftw_plan_dft_1d ( N, in, outputFFT, FFTW_FORWARD, FFTW_ESTIMATE );

    /* Get the data from the function input and save it as the input for FFT */
    for (int j=0; j < N; j++){
        in[j][1] = 0;
        in[j][0] = Data.at(j);
    }

    /* Calculate the FFT of the given data */
    fftw_execute ( plan_forward );

    /* Free memory */
    fftw_destroy_plan ( plan_forward );
    fftw_free ( in );

    /* Normalize the output FFT vector, real and complex components */
    for (int j=0; j < N; j++){
        outputFFT[j][0] = outputFFT[j][0]/N;
        outputFFT[j][1] = outputFFT[j][1]/N;
    }
}

/**
 * @brief Save the FFT Data to a File
 */
void fft::saveFFTtoFile(QFileInfo FileDetails)
{
    /* Get current path to executable */
    QString current = QDir::currentPath();

    /* Remove 'binary/[platform]' part from string */
    current = current.left(current.lastIndexOf("binary"));

    /* Path to be in the search for the files; is always a subdirectory in the application path */
    QString pathc(QString("%1%2").arg(current, "data_polarimeter/"));

    /* Create a Date Folder*/
    QString folder = "FFT Data " + QDate::currentDate().toString("dd MM yyyy") + "_0";
    QDir(pathc).mkdir(folder);

    /* Save the file with the same input data name, but adding FFT at the end */
    QString path = pathc +folder+"/"+ FileDetails.completeBaseName() + "_FFT.txt";

    QFile FFT_File(path);
    QFileInfo checkFile1(path);

    /* Check if file exists */
    if (checkFile1.exists() && checkFile1.isFile())
    {
        /* Create a folder with the same name but add a number to it */
        int i = 1;

        /* Depending on how many folder are there already, then create the next in the list */
        while(true){

            /* Change the folder name to don't overwrite or ask the user when saving */
            folder = "FFT Data " + QDate::currentDate().toString("dd MM yyyy") + "_" + QString::number(i);
            QDir(pathc).mkdir(folder);

            /* Try again to see if the file exists? */
            path = pathc + folder+"/"+ FileDetails.completeBaseName() + "_FFT.txt";
            QFile FFT_File(path);
            QFileInfo checkFile(path);

           /* The new name doesn't exists, so stop creating folders */
            if(!checkFile.exists()){break;}

            /* Next folder number */
            i++;
        }
    }

    /* Open the file for writing */
    FILE *fileFFT = fopen(path.toLatin1().data(), "wt");

    /* Write serial number */
    fprintf(fileFFT, "Serial number: %s\n", ptrSpectrometers[0]->getSerialNumber().toLatin1().data());

    /* Check for readable name */
    if (ptrSpectrometers[0]->hasReadableName())
    {
        /* Write readable name */
        fprintf(fileFFT, "Readable name: %s\n", ptrSpectrometers[0]->getReadableName().toLatin1().data());
    }

    /* Write integration time, number of averages, number of spectra and frequency on file */
    fprintf(fileFFT, "Number of Recorded Spectra: %i\n", NrSpectra);
    fprintf(fileFFT, "Averages: %i\n", NrAverages);
    fprintf(fileFFT, "Integration time: %.2f ms\n", IntTime);
    fprintf(fileFFT, "Frequency: %.2f Hz\n\n", FrequencyF);

    /* Loop through the wavelengths */
    for (int z = 0; z < wavelengths.length(); z++)
    {
        /* Write FFT data headers */
        if (z == 0)
        {
            fprintf(fileFFT, "Wavelength \t \t");
            fprintf(fileFFT, "DC Amplitude \t \t");
            fprintf(fileFFT, "W Amplitude \t");
            fprintf(fileFFT, "2W Amplitude \t");
            fprintf(fileFFT, "W/2W \n");
        }

        /* Write wavelengths and amplitudes */
        fprintf(fileFFT, "%.4f\t\t", wavelengths.at(z));
        fprintf(fileFFT, "%.6f\t\t", fft_DC.at(z));
        fprintf(fileFFT, "%.6f\t\t", fft_W.at(z));
        fprintf(fileFFT, "%.5f\t\t", fft_2W.at(z));
        fprintf(fileFFT, "%.5f\t\t", fft_Compensation_Signal.at(z));

        fprintf(fileFFT, "\n");

    }

    fprintf(fileFFT, "\n");

    /* Close the file */
    fclose(fileFFT);

    /* Free pointer */
    fileFFT = nullptr;
}