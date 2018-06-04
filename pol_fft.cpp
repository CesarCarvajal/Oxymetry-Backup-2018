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
#include <QFileDialog>


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

/* Spectrometer control */
#include "spectrometer.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Get the Data from a FFT File type.
 * @param[in] Information of the file where the FFT data will be read.
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
    ReadFile(fileInformation.absoluteFilePath());

    /* Create the readed row */
    QString Row;

    /* Get the maximum DC value */
    double DCValue = 0;

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
                DCValue = Readed_Row.at(1).toDouble();
                fft_DC.append(DCValue);

                /* Save W - Position 2 */
                fft_W.append(Readed_Row.at(2).toDouble());

                /* Save 2W - Position 3 */
                fft_2W.append(Readed_Row.at(3).toDouble());

                /* Calculate the Compensation signal, there is no need to have it in the file */
                fft_Compensation_Signal.append(fft_W.at(rowcounter)/fft_2W.at(rowcounter));

                /* What is the modulation frequency? */
                f_w = NrSpectra*(IntTime/1000)*FrequencyF;

                /* The user haven't selected a wavelength for the FFT plot */
                if(changeFFTwavelength){

                    /* Find the highest DC intensity and choose that wavelength for the FFT plot */
                    if(DCValue > MaximumIntensity && wavelengths.length()!=0){

                        /* Save the maximum intensity */
                        MaximumIntensity =DCValue;

                        /* Save the position where the intensity is the maximum */
                        SelectedWaveL = wavelengths.length()-1;

                        /* Restart the maximum */
                        fft_data.resize(0);
                        time.resize(0);

                    }
                }

                /* Show the intensities for the maximum DC value */
                if (SelectedWaveL == wavelengths.length()-1 && wavelengths.length()> 0){

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
 * @param[in] Information of the Raw Data file to be processed, the type of running "calibrating or measuring" and the maximum wavelength in use.
 */
void fft::getFFTfromRawData(QFileInfo fileInformation, bool Calibrating, double minWavelength, double maxWavelength)
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
    QString Row = "";

    /* DC value to get maximum intensity */
    double DCValue = 0;

    /* Initialize the spliter according to the Oxymetry type ".CS" or ".tmp" file */
    QString spliter = "\t\t";

    /* Start reading at the second column for CS file */
    int column = 1;

    /* But, Is it a TXT from Avantes Software? */
    if(fileInformation.suffix()=="TXT"){
        /* Initialize the spliter according to the type TXT Avantes Software file */
        spliter = ";";
        /* Start reading at the forth column for TXT file */
        column = 3;
    }

    /* Indicates when to start reading the numerical data from file */
    bool read = false;

    /* Initialize the row counter */
    int rowcounter = 0;

    /* Get Information from File Name if loading the data from a File*/
    if(!Calibrating){
        ReadFile(fileInformation.absoluteFilePath());
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

                /* We don't need all the saved values */
                if(Readed_Row.at(0).toDouble() > maxWavelength){break;}
                if(Readed_Row.at(0).toDouble() < minWavelength){continue;}

                /* Save the wavelengths in Position 0 */
                wavelengths.append(Readed_Row.at(0).toDouble());

                /* Save all the counts per row from Raw Data for future calculation of FFT */
                for (int j=column; j < Readed_Row.length(); j++){

                    /* Save counts */
                    counts.append(Readed_Row.at(j).toDouble());
                }

                /* The amount of columns of the file determines how many sprectra we have, only for raw data */
                NrSpectra = counts.length();

                /* With the current counts from a row, calculate the FFT */
                CalculateFFT(NrSpectra, counts);

                /* What is the modulation frequency? */
                f_w = NrSpectra*(IntTime/1000)*FrequencyF*NrAverages;

                /* From the Output array of FFT, save each of the frequency shares amplitude */
                DCValue = sqrt(fabs((outputFFT[0][0]*outputFFT[0][0])) + fabs((outputFFT[0][1]*outputFFT[0][1])));
                fft_DC.append(DCValue);
                fft_W.append(sqrt(fabs((outputFFT[f_w][0]*outputFFT[f_w][0])) + fabs((outputFFT[f_w][1]*outputFFT[f_w][1]))));
                fft_2W.append(sqrt(fabs((outputFFT[2*f_w][0]*outputFFT[2*f_w][0])) + fabs((outputFFT[2*f_w][1]*outputFFT[2*f_w][1]))));
                fft_Compensation_Signal.append(fft_W.at(rowcounter)/fft_2W.at(rowcounter));

                /* The user haven't selected a wavelength for the FFT plot */
                if(changeFFTwavelength){

                    /* Find the highest DC intensity and choose that wavelength for the FFT plot */
                    if(DCValue > MaximumIntensity && wavelengths.length()!=0){

                        /* Save the maximum intensity */
                        MaximumIntensity =DCValue;

                        /* Save the position where the intensity is the maximum */
                        SelectedWaveL = wavelengths.length()-1;

                        /* Restart the maximum */
                        fft_data.resize(0);
                        time.resize(0);

                    }
                }

                /* By default show the FFT values for the wavelength 537,57 nm */
                if (SelectedWaveL == wavelengths.length()-1 && wavelengths.length()> 0){
                    for ( int  i = 0; i < NrSpectra/2; i++ )
                    {
                        /* Amplitude at all frequencies */
                        fft_data.append(sqrt(fabs((outputFFT[i][0]*outputFFT[i][0])) + fabs((outputFFT[i][1]*outputFFT[i][1]))));

                        /* Which frequencies are shown in the FFT? */
                        time.append(i/(NrAverages*NrSpectra*(IntTime/1000)));
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
 * @param[in] Name of the file to extract the information, the path of the file and the corresponding file type CS or TXT.
 *
 */
void fft::ReadFile(QString FilePath)
{
    /* Data to get from the File Name */
    ConcentrationC1 = IntTime = FrequencyF = ConcentrationC2 = ConcentrationC3 = NrAverages = NrSpectra = -1;

    /* There is some information in the file very important to know how many data are we using */

    /* Open the file to get the Nr of Spectra and Average Nr. */
    QFile file(FilePath);

    /* Row of the file */
    QString ReadRow;

    /* Open the file */
    if(file.open(QIODevice::ReadOnly)) {

        QTextStream stream(&file);

        /* Read lines */
        while(!stream.atEnd()){

            /* Read a line from the file */
            ReadRow = stream.readLine();

            /* Read the text and get the values */
            QStringList Readed_Row = ReadRow.split(" ");

            /* Integration time found */
            if(ReadRow.contains("Integration") && IntTime==-1){

                /* Get the integration time from file */
                IntTime = QString(Readed_Row.at(2)).replace(",",".").toDouble();

                /* Number of Spectra found */
            }else if(ReadRow.contains("Spectra") && NrSpectra==-1){

                /* Get the number of spectra from file */
                NrSpectra = Readed_Row.at(3).toInt();

                /* Number of Averages found */
            }else if(ReadRow.contains("Averages") && NrAverages==-1){

                /* Get the number of averages from file */
                NrAverages = Readed_Row.at(3).toInt();

                /* Frequency found */
            }else if(ReadRow.contains("Frequency") && FrequencyF==-1){

                /* Get the frequency from file */
                FrequencyF = QString(Readed_Row.at(1)).replace(",",".").toDouble();

                /* Concentrations found */
            }else if(ReadRow.contains("Concentrations") && ConcentrationC1==-1 && ConcentrationC2==-1 && ConcentrationC3==-1){

                /* Is there glucose? */
                if(ReadRow.contains("C1")){
                    ConcentrationC1 = QString(Readed_Row.at(2)).replace(",",".").toDouble();
                }

                /* Is there Impurity 1? */
                if(ReadRow.contains("C2")){
                    ConcentrationC2 = QString(Readed_Row.at(4)).replace(",",".").toDouble();
                }

                /* Is there Impurity 2? */
                if(ReadRow.contains("C3")){
                    ConcentrationC3 = QString(Readed_Row.at(6)).replace(",",".").toDouble();
                }

                /* From here ahead just counts and other data */
            }else if(ReadRow.contains("Wavelength")){

                break;
            }
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
* @param[in] The Raw Data and the size of the measurements N.
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

        /* Normalize the measured counts? */
        if(normalizeCounts){
            in[j][0] = (Data.at(j)*1000)/(IntTime);
        }else{
            in[j][0] = Data.at(j);
        }
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
* @param[in] Details of the file where the FFT will be saved. Also if the user is saving or the system is saving automatically.
*/
void fft::saveFFTtoFile(QFileInfo FileDetails, bool userSaving)
{
    /* Create the path and file name for the FFT file */
    QString path;
    QString fileN = FileDetails.completeBaseName();

    /* The user wants to save the FFT data in an specific folder */
    if(userSaving){

        /* Get the user path */
        path = QFileDialog::getSaveFileName(0, tr("Save FFT Data"), fileN, "FFT files (*.FFT)");

    }else{

        /* Create a Date Folder automatically */
        QString folder = "FFT Data " + QDate::currentDate().toString("dd MM yyyy");

        /* Create Folder */
        QDir(FileDetails.absolutePath()).mkdir(folder);

        /* Save the file with the same input data name, but adding FFT at the end */
        path = FileDetails.absolutePath() +"/" + folder + "/" + fileN + ".FFT";
    }

    /* Open the file for writing */
    FILE *fileFFT = fopen(path.toLatin1().data(), "wt");

    /* Write serial number */
    fprintf(fileFFT, "Serial Number: %s\n", ptrSpectrometers[0]->getSerialNumber().toLatin1().data());

    /* Check for readable name */
    if (ptrSpectrometers[0]->hasReadableName())
    {
        /* Write readable name */
        fprintf(fileFFT, "Readable Name: %s\n", ptrSpectrometers[0]->getReadableName().toLatin1().data());
    }

    /* Write integration time, number of averages, number of spectra and frequency on file */
    fprintf(fileFFT, "Integration Time: %.2f ms\n", IntTime);
    fprintf(fileFFT, "Nr. of Spectra: %i\n", NrSpectra);
    fprintf(fileFFT, "Nr. of Averages: %i\n", NrAverages);
    fprintf(fileFFT, "Frequency: %.2f Hz\n", FrequencyF);

    /* Include the concentrations in the file */
    QString concentrations, conc = "";

    /* Is there glucose? */
    if(ConcentrationC1 >= 0){
        concentrations.append(QString::number(ConcentrationC1));
        conc.append("C1");
    }

    /* Is there Impurity 1? */
    if(ConcentrationC2 >= 0){
        concentrations.append(" , " + QString::number(ConcentrationC2));
        conc.append("C2");
    }

    /* Is there Impurity 2? */
    if(ConcentrationC3 >= 0){
        concentrations.append(" , " + QString::number(ConcentrationC3));
        conc.append("C3");
    }

    /* Write the concentrations to the file */
    fprintf(fileFFT, "Concentrations %s: %s\n\n", conc.toLatin1().data() , concentrations.toLatin1().data());

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

/**
* @brief Destructor of 'fft' class
*
*/
fft::~fft(void)
{

}
