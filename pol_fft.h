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

#ifndef POL_FFT_H
#define POL_FFT_H

/*
 * External includes
 */

/* Qt library */
#include <QString>
#include <QFileDialog>
#include "qobject.h"

/*
 * Internal includes
 */

/* FFT Library */
#include <fftw3.h>

/* Header of FFT Calculator Object */

/**
 * @brief The 'FFT' class
 */
class fft : public QObject
{

public:

    /* Vector with time frequencies */
    QVector<double> time;

    /* FFT raw data */
    QVector<double> fft_data;

    /* Size of Nr Waves */
    QVector<double> wavelengths;

    /* Extracted components */
    QVector<double> fft_DC, fft_W, fft_2W;
    QVector<double> fft_Compensation_Signal;

    /* Parameters from Files, initialization: */
    int NrSpectra = 1000;
    double IntTime = 8;
    double FrequencyF = 7;
    int NrAverages = 1;

    /* Concentrations */
    double ConcentrationC1=-1;
    double ConcentrationC2=-1;
    double ConcentrationC3=-1;
    double ConcentrationC4=-1;
    double ConcentrationC5=-1;
    double ConcentrationC6=-1;

    double TemperatureSetup = 0;

    /* Where are we going to extract the components of the FFT */
    int f_w;

    /* The position in the array of FFT to show by default */
    int SelectedWaveL=-1;

    /* Maximum Intensity measured */
    double MaximumIntensity = 0;

    /* Normalize Counts? */
    bool normalizeCounts = false;

    /* Change the selected wavelength for the FFT plot */
    bool changeFFTwavelength = true;

private:

    /* Counts */
    QVector<double> counts;

    /* Output FFT vector */
    fftw_complex *outputFFT = nullptr;

public:

    /* Get the FFT from the loaded file */
    void getFFTfromRawData(QFileInfo FileName, bool Calibrating, double minWavelength, double maxWavelength);
    void getFFTfromFFTData(QFileInfo FileName);

    /* Initialize the arrays according to the file */
    void InitializeFFTArrays();

    /* Save FFT to a file */
    void saveFFTtoFile(QFileInfo FileDetails, bool userSaving, QStringList substancesNames, double Temperature);

    /* Destructor */
    ~fft(void);

private:

    /* Read info from file */
    void ReadFile(QString FilePath);

    /* Calculate the FFT from the Data */
    void CalculateFFT(int N, QVector<double> Data);

};

#endif // POL_FFT_H
