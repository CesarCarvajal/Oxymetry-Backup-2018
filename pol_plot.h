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

#ifndef POL_PLOT_H
#define POL_PLOT_H

/* External includes */

/* Qwt library */
#include "qwt_plot_curve.h"


/**
 * @brief The 'Pol_Plot' class
 */
class Pol_Plot : public QObject
{
    Q_OBJECT

public:
    /* Constructor */
    explicit Pol_Plot();

    /* Plot the real time averages of the frequency components DC, W, and 2W */
    void plotAverages(bool dataloaded, QVector<double> FFTLfft_DC, QVector<double> FFTLfft_W, QVector<double> FFTLfft_2W, QVector<double> FFTLwavelengths);

    /* The user wants to look the FFT at one specific wavelength */
    void plotFFTatSelectedWave(QVector<double> FFTLfft_data, QVector<double> FFTLtime);

    /* Plot the graphs */
    void Plot_FFT_Graphs(QVector<double> FFTLwavelengths, QVector<double> FFTLtime, QVector<double> FFTLfft_data, QVector<double> FFTLfft_DC,
                         QVector<double> FFTLfft_W, QVector<double> FFTLfft_2W, QVector<double> FFTLfft_Compensation_Signal);

    /* Clean all the plots */
    void clean_AllPlots(void);

    /* Averages Plot time */
    int counts_average_time;

    /* Polarimetry curves */
    QwtPlotCurve *FFT_oneWave, *predictionSignal;
    QwtPlotCurve *FFT_DC, *FFT_W, *FFT_2W;
    QwtPlotCurve *Compensation_Signal;
    QwtPlotCurve *Average_DC_Signal, *Average_W_Signal, *Average_2W_Signal;

    /* Vectors for live Plotting */
    QVector<double> averaged_Signal_time;
    QVector<double> AverageDC, AverageW, Average2W;

    /* Maximum value on Y axis */
    int maxYValue;

    /* Maximum value on X axis of average plot */
    double maxXtime;

    /* Variables to count time and plot the real time averages */
    int time_plot;

    /* Reference prediction */
    QVector<double> linearR;

    /* Destructor */
    ~Pol_Plot(void);

};

#endif  // POL_PLOT_H
