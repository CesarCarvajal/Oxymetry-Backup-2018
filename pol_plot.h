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
#include <QtDataVisualization>

using namespace QtDataVisualization;

/* Header of Plot Object */

/**
 * @brief The 'Pol_Plot' class
 */
class Pol_Plot : public QObject
{
    Q_OBJECT

public:
    /* Constructor */
    explicit Pol_Plot();

    /* Polarimetry curves */
    QwtPlotCurve * curve_Pol;
    QwtPlotCurve *FFT_oneWave, *predictionSignal;
    QwtPlotCurve *FFT_DC, *FFT_W, *FFT_2W;
    QwtPlotCurve *Compensation_Signal, *Average_Ratio_Signal;
    QwtPlotCurve *Average_DC_Signal, *Average_W_Signal, *Average_2W_Signal, *Temperature_Plot, *Humidity_Plot;

    /* Plot some statistics */
    QwtPlotCurve *AverageDetSignalPlotter, *DeviationVsMeasNumberPlot, *DeviationVsConcentration, *DeviationVsCountsMeanDeviation;

    /* Vectors for live Plotting */
    QVector<double> averaged_Signal_time;
    QVector<double> AverageDC, AverageW, Average2W, AverageRatio, Temperature_Values, Humidity_Values;

    /* Maximum value on Y axis */
    double maxYValue;

    /* 3D Surfaces */
    Q3DSurface *surface, *surface_norm;
    QSurface3DSeries *series, *series_norm;

    /* Maximum value on X axis of average plot */
    double maxXtime;

    /* Variables to count time and plot the real time averages */
    int time_plot;

    /* Reference prediction */
    QVector<double> linearR;

    /* Standar deviation of the temperature */
    double TempStandardDev;

    /* Averages Plot time */
    int counts_average_time;

public:

    /* Plot the real time averages of the frequency components DC, W, and 2W */
    void plotAverages(bool dataloaded, QVector<double> FFTLfft_DC, QVector<double> FFTLfft_W, QVector<double> FFTLfft_2W, QVector<double> FFTLwavelengths, bool measuring, int time, double temperature, double humidity);

    /* Adjust 3D plots */
    void adjust3DPlot(void);

    /* The user wants to look the FFT at one specific wavelength */
    void plotFFTatSelectedWave(QVector<double> FFTLfft_data, QVector<double> FFTLfrequencies);

    /* Plot the graphs */
    void Plot_FFT_Graphs(QVector<double> FFTLwavelengths, QVector<double> FFTLfrequencies, QVector<double> FFTLfft_data, QVector<double> FFTLfft_DC,
                         QVector<double> FFTLfft_W, QVector<double> FFTLfft_2W, QVector<double> FFTLfft_Compensation_Signal);

    /* Clean all the plots */
    void clean_AllPlots(void);

    /* Clean 3D plots */
    void restart3DPlots(void);

    /* Further adjust of plots */
    void adjustSet3DPlots(void);

    /* Plot the prediction line */
    void plotPredictionLine(double minConcentration, double maxConcentration);

    /* Destructor */
    ~Pol_Plot(void);

};

#endif  // POL_PLOT_H
