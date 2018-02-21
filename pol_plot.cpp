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
#include "pol_plot.h"

/**
 * @brief Constructor of 'Pol_Plot' class
 *
 */
Pol_Plot::Pol_Plot()
{

    /* Plot Average, range of time plotting */
    time_plot=300;

    /* Running time of Averages */
    counts_average_time = 0;

    /* Max value for plotting Y axis in Averages */
    maxYValue = 2000;

    /* Max value for plotting X axis in Averages */
    maxXtime = 150;

    /* Dc, W and 2w Averages */
    Average_DC_Signal = new QwtPlotCurve("DC");
    Average_DC_Signal->setPen(QPen("magenta"));
    Average_W_Signal = new QwtPlotCurve("W");
    Average_W_Signal->setPen(QPen("red"));
    Average_2W_Signal = new QwtPlotCurve("2W");
    Average_2W_Signal->setPen(QPen("green"));

    /* Create the DC, W and 2W plots */
    FFT_DC = new QwtPlotCurve("DC");
    FFT_W = new QwtPlotCurve("W");
    FFT_2W = new QwtPlotCurve("2W");

    /* Set colors for the plots */
    FFT_DC->setPen(QPen("magenta"));
    FFT_W->setPen(QPen("red"));
    FFT_2W->setPen(QPen("green"));

    /* Plot the Compensation W/2W Signal */
    Compensation_Signal = new QwtPlotCurve("");
    Compensation_Signal->setPen(QPen("red"));

    /* Plot the FFT at the wavelength selected by the user */
    FFT_oneWave = new QwtPlotCurve("");
    FFT_oneWave->setPen(QPen("blue"));
    FFT_oneWave->setItemAttribute(QwtPlotItem::Legend, false);

    /* Plot the concentration prediction */
    predictionSignal = new QwtPlotCurve("");
    predictionSignal->setPen(QPen("black"));
    predictionSignal->setItemAttribute(QwtPlotItem::Legend, false);

}

/**
 * @brief Receive the Data to be ploted on the Polarimeter Tab Interface.
 * @param[in] Vectors with the wavelengths, the plotting frequencies, the FFT transformation, the DC, W and 2W components, and the ratio W/2W.
 *
 */
void Pol_Plot::Plot_FFT_Graphs(QVector<double> FFTLwavelengths, QVector<double> FFTLfrequencies, QVector<double> FFTLfft_data, QVector<double> FFTLfft_DC, QVector<double> FFTLfft_W
                               , QVector<double> FFTLfft_2W, QVector<double> FFTLfft_Compensation_Signal){

    /* Plot The FFT at the default Wavelength first */
    plotFFTatSelectedWave(FFTLfft_data, FFTLfrequencies);

    /* Assign the values to the plots */
    FFT_DC->setSamples(FFTLwavelengths , FFTLfft_DC);
    FFT_W->setSamples(FFTLwavelengths , FFTLfft_W);
    FFT_2W->setSamples(FFTLwavelengths , FFTLfft_2W);

    /* Expected curve of prediction */
    for(int j=0; j< 6; j++){
        linearR.append(j*100);
    }

    /* Set expected curve of prediction */
    predictionSignal->setSamples(linearR, linearR);
    predictionSignal->setItemAttribute(QwtPlotItem::Legend, false);

    /* Assign values to plot */
    Compensation_Signal->setSamples(FFTLwavelengths , FFTLfft_Compensation_Signal);
    Compensation_Signal->setItemAttribute(QwtPlotItem::Legend, false);
}

/**
 * @brief Plot Only the FFT of the Selected Wavelength.
 * @param[in] Vectors with the FFT transformation and the plotting frequencies.
 */
void Pol_Plot::plotFFTatSelectedWave(QVector<double> FFTLfft_data, QVector<double> FFTLfrequencies){

    /* Plot the FFT */
    FFT_oneWave->setSamples(FFTLfrequencies , FFTLfft_data);
}

/**
 * @brief Plot W, DC and 2W averaged
 * @param[in] Vectors with the DC, W, 2W and ratio W/2W components, also the wavelengths. The parameter dataloaded prevents mixing of data.
 */
void Pol_Plot::plotAverages(bool dataloaded, QVector<double> FFTLfft_DC, QVector<double> FFTLfft_W, QVector<double> FFTLfft_2W, QVector<double> FFTLwavelengths){

    /* Initialize the average variables */
    double average_DC=0, average_W=0, average_2W = 0;

    /* Was there previously data loaded that may affect the new plotting? */
    if(!dataloaded){
        /* Sum all the FFT signal amplitudes */
        for ( int  i = 0; i < FFTLwavelengths.length(); i++ )
        {
            average_DC = average_DC + FFTLfft_DC.at(i);
            average_W = average_W + FFTLfft_W.at(i);
            average_2W = average_2W + FFTLfft_2W.at(i);
        }
    }

    /* Save the Average values in a vector to be ploted */
    if(FFTLwavelengths.isEmpty()){
        /* If there still no signals, just plot zero */
        AverageDC.append(0);
        AverageW.append(0);
        Average2W.append(0);
    }else{
        /* Now there is data to plot, so add the averages to the queue to plot */
        AverageDC.append(average_DC/FFTLwavelengths.length());
        AverageW.append(average_W/FFTLwavelengths.length());
        Average2W.append(average_2W/FFTLwavelengths.length());
        maxYValue =  ceil(*std::max_element(AverageDC.begin(), AverageDC.end()));
    }

    /* The signal is plotted every defined time, so run it's own timer for plotting */
    counts_average_time = counts_average_time + 1;

    /* Add the time to the x axis of the plot */
    averaged_Signal_time.append(counts_average_time);

    /* DC, W and 2W plots */
    Average_DC_Signal->setSamples(averaged_Signal_time, AverageDC);
    Average_W_Signal->setSamples(averaged_Signal_time, AverageW);
    Average_2W_Signal->setSamples(averaged_Signal_time, Average2W);

    /* Whats the maximum time reached on the vector until now? */
    maxXtime = *std::max_element(averaged_Signal_time.begin(), averaged_Signal_time.end());

}

/**
 * @brief Clean all plots and vectors.
 */
void Pol_Plot::clean_AllPlots(void){

    /* Is there any information ploted already? */
    if(Average_DC_Signal!=nullptr)
    {
        /* Detach live curves */
        Average_DC_Signal->detach();
        Average_W_Signal->detach();
        Average_2W_Signal->detach();
    }

    /* Set all vectors to zero */
    averaged_Signal_time.resize(0);
    AverageDC.resize(0);
    AverageW.resize(0);
    Average2W.resize(0);
    counts_average_time = 0;
}

/**
 * @brief Destructor of 'Pol_Plot' class
 */
Pol_Plot::~Pol_Plot(void)
{
    /* Free memory */
    if(Average_DC_Signal != nullptr){
        Average_DC_Signal->detach();
        delete Average_DC_Signal;
        Average_DC_Signal= nullptr;

        Average_W_Signal->detach();
        delete Average_W_Signal;
        Average_W_Signal= nullptr;

        Average_2W_Signal->detach();
        delete Average_2W_Signal;
        Average_2W_Signal= nullptr;
    }

    /* Delete all the existing data ploted on the interface */
    delete FFT_DC;
    FFT_DC = nullptr;

    delete FFT_W;
    FFT_W = nullptr;

    delete FFT_2W;
    FFT_2W = nullptr;

    delete Compensation_Signal;
    Compensation_Signal  = nullptr;

    delete FFT_oneWave;
    FFT_oneWave= nullptr;

    delete predictionSignal;
    predictionSignal = nullptr;
}
