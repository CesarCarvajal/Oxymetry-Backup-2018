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
#include <QtDataVisualization>
#include <QApplication>

#include "application.h"

using namespace QtDataVisualization;

/**
 * @brief Constructor of 'Pol_Plot' class
 *
 * In this class:   - The calculated FFT plot is displayed in the tab "Setup Status".
 *                  - The plots of raw data, Ratio, FFT profiles and live averages are created here.
 *                  - The 3D plots settings are also adjusted here.
 *                  - The live FFT averages and the temperature plots are created here.
 *                  - The prediction plot is built here.
 *                  - Further plot related functions can be included in this class.
 *
 */
Pol_Plot::Pol_Plot()
{
    /* Plot Average, range of time plotting */
    time_plot=450;

    /* Running time of Averages */
    counts_average_time = 0;

    /* 3D Surface */
    surface = new Q3DSurface();
    series = new QSurface3DSeries();
    surface_norm = new Q3DSurface();
    series_norm = new QSurface3DSeries();

    /* Max value for plotting Y axis in Averages */
    maxYValue = 0;

    /* Max value for plotting X axis in Averages */
    maxXtime = 150;

    /* Dc, W and 2w Averages plot curves */
    Average_DC_Signal = new QwtPlotCurve("I(DC)");
    Average_DC_Signal->setPen(QPen("magenta"));
    Average_W_Signal = new QwtPlotCurve("I(ω)");
    Average_W_Signal->setPen(QPen(QColor( 0,179,0 )));
    Average_2W_Signal = new QwtPlotCurve("I(2ω)");
    Average_2W_Signal->setPen(QPen(QColor( 230,92,0 )));
    Average_Ratio_Signal = new QwtPlotCurve("I(ω)/I(2ω)");
    Average_Ratio_Signal->setPen(QPen(QColor( 0,0,0 )));

    /* Temperature plot curve  */
    Temperature_Plot = new QwtPlotCurve("");
    Temperature_Plot->setPen(QPen("red"));

    /* Humidity plot curve  */
    Humidity_Plot = new QwtPlotCurve("");
    Humidity_Plot->setPen(QPen("Blue"));

    /* Create the DC, W and 2W plots */
    FFT_DC = new QwtPlotCurve("I(DC)");
    FFT_W = new QwtPlotCurve("I(ω)");
    FFT_2W = new QwtPlotCurve("I(2ω)");

    /* Set colors for the plots */
    FFT_DC->setPen(QPen("magenta"));
    FFT_2W->setPen(QPen(QColor(  230,92,0 )));
    FFT_W->setPen(QPen(QColor( 0,179,0 )));

    /* Plot the Compensation W/2W Signal */
    Compensation_Signal = new QwtPlotCurve("");
    Compensation_Signal->setPen(QPen("red"));

    /* Plot the FFT at the wavelength selected by the user */
    FFT_oneWave = new QwtPlotCurve("");
    FFT_oneWave->setPen(QPen("magenta"));
    FFT_oneWave->setItemAttribute(QwtPlotItem::Legend, false);

    /* Plot the concentration prediction */
    predictionSignal = new QwtPlotCurve("");
    predictionSignal->setPen(QPen("black"));
    predictionSignal->setItemAttribute(QwtPlotItem::Legend, false);

    /* Create statistics plots */
    AverageDetSignalPlotter= new QwtPlotCurve("");
    AverageDetSignalPlotter->setPen(QPen("red"));
    AverageDetSignalPlotter->setItemAttribute(QwtPlotItem::Legend, false);

    /* Create statistics plots */
    DeviationVsMeasNumberPlot= new QwtPlotCurve("");
    DeviationVsMeasNumberPlot->setPen(QPen("blue"));
    DeviationVsMeasNumberPlot->setItemAttribute(QwtPlotItem::Legend, false);

    /* Inital Temperature STD */
    TempStandardDev = 0;
}


/**
 * @brief Adjust 3D plot.
 */
void Pol_Plot::adjust3DPlot(void){

    /* Adjust color painting */
    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::blue);
    gr.setColorAt(0.2, Qt::cyan);
    gr.setColorAt(0.4, Qt::green);
    gr.setColorAt(0.6, Qt::yellow);
    gr.setColorAt(0.8, Qt::red);
    gr.setColorAt(1.0, Qt::black);
    surface->seriesList().at(0)->setBaseGradient(gr);
    surface->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyle::ColorStyleRangeGradient);
    surface->seriesList().at(0)->setDrawMode(QSurface3DSeries::DrawSurface);

    /* Adjust color painting */
    QLinearGradient gr2;
    gr2.setColorAt(0.0, Qt::red);
    gr2.setColorAt(0.2, Qt::magenta);
    gr2.setColorAt(0.4, Qt::yellow);
    gr2.setColorAt(0.6, Qt::green);
    gr2.setColorAt(0.8, Qt::cyan);
    gr2.setColorAt(1.0, Qt::blue);
    surface_norm->seriesList().at(0)->setBaseGradient(gr2);
    surface_norm->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyle::ColorStyleRangeGradient);
    surface_norm->seriesList().at(0)->setDrawMode(QSurface3DSeries::DrawSurface);

    /* Adjust axes */
    surface->axisX()->setAutoAdjustRange(true);
    surface->axisY()->setAutoAdjustRange(true);
    surface->axisZ()->setAutoAdjustRange(true);
    surface->axisX()->setTitle(QStringLiteral("Wavelength (nm)"));
    surface->axisX()->setTitleVisible(true);
    surface->axisY()->setTitleVisible(true);
    surface->axisZ()->setTitleVisible(true);

    surface_norm->axisX()->setAutoAdjustRange(true);
    surface_norm->axisY()->setAutoAdjustRange(true);
    surface_norm->axisZ()->setAutoAdjustRange(true);
    surface_norm->axisX()->setTitle(QStringLiteral("Wavelength (nm)"));
    surface_norm->axisX()->setTitleVisible(true);
    surface_norm->axisY()->setTitleVisible(true);
    surface_norm->axisZ()->setTitleVisible(true);

    adjustSet3DPlots();

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
 * @brief Plot the line of expected predicted concentration.
 * @param[in] minimum and maximum concentration values
 */
void Pol_Plot::plotPredictionLine(double minConcentration, double maxConcentration){

    /* Expected curve of prediction with 20 points */
    for(int j=0; j<= 20; j++){
        linearR.append(minConcentration + j*(maxConcentration/20));
    }

    /* Set expected curve of prediction */
    predictionSignal->setSamples(linearR, linearR);
    predictionSignal->setItemAttribute(QwtPlotItem::Legend, false);
}

/**
 * @brief Plot W, DC and 2W averaged
 * @param[in] Vectors with the DC, W, 2W and ratio W/2W components, also the wavelengths. The parameter dataloaded prevents mixing of data.
 */
void Pol_Plot::plotAverages(bool dataloaded, QVector<double> FFTLfft_DC, QVector<double> FFTLfft_W, QVector<double> FFTLfft_2W, QVector<double> FFTLwavelengths,
                            bool measuring, int time, double temperature, double humidity){

    /* Initialize the average variables */
    double average_DC=0, average_W=0, average_2W = 0;

    /* Was there previously data loaded that may affect the new plotting? */
    if(!dataloaded){

        /* Sum all the FFT signal amplitudes */
        for ( int  i = 0; i < FFTLwavelengths.length(); i++ ){

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
        AverageRatio.append(0);

    }else{

        /* Now there is data to plot, so add the averages to the queue to plot */
        AverageDC.append(average_DC/FFTLwavelengths.length());
        AverageW.append(average_W/FFTLwavelengths.length());
        Average2W.append(average_2W/FFTLwavelengths.length());
        maxYValue =  ceil(*std::max_element(AverageDC.begin(), AverageDC.end()));

        /* If 2W is 0, then the ratio can't be calculated, add zeros instead */
        if(average_2W == 0){
            AverageRatio.append(0);
        }else{
            AverageRatio.append(average_W/average_2W);
        }
    }

    /* Is there a long measurement? */
    if(!measuring){
        /* The signal is plotted every defined time, so run it's own timer for plotting */
        counts_average_time = counts_average_time + 1;
    }else{
        counts_average_time = counts_average_time + time;
    }

    /* Add the time to the x axis of the plot */
    averaged_Signal_time.append(counts_average_time);

    /* DC, W and 2W plots */
    Average_DC_Signal->setSamples(averaged_Signal_time, AverageDC);
    Average_DC_Signal->setTitle(" Ī(DC) = " + QString().setNum(AverageDC.last(), 'f', 2) + " ");
    Average_W_Signal->setSamples(averaged_Signal_time, AverageW);
    Average_W_Signal->setTitle(" Ī(ω) = " + QString().setNum(AverageW.last(), 'f', 2) + " ");
    Average_2W_Signal->setSamples(averaged_Signal_time, Average2W);
    Average_2W_Signal->setTitle(" Ī(2ω) = " + QString().setNum(Average2W.last(), 'f', 2) + " ");
    Average_Ratio_Signal->setSamples(averaged_Signal_time, AverageRatio);
    Average_Ratio_Signal->setTitle(" Ī(ω)/Ī(2ω) = " + QString().setNum(AverageRatio.last(), 'f', 2) + " ");

    /* Temperature plot */
    Temperature_Values.append(temperature);

    /* Humidity plot */
    Humidity_Values.append(humidity);

    /* Add temperature and Humidity plot */
    Temperature_Plot->setSamples(averaged_Signal_time, Temperature_Values);
    Humidity_Plot->setSamples(averaged_Signal_time, Humidity_Values);

    /* Calculate the actual standard deviation */
    double meanTemp = 0;
    double meanHumidity = 0;

    /* Get the mean value */
    for(int k = 0; k < Temperature_Values.length(); k++){

        meanTemp = meanTemp + Temperature_Values.at(k);
        meanHumidity = meanHumidity + Humidity_Values.at(k);

        /* Handle events and update UI */
        Application::processEvents();
    }

    /* Mean temperature and humidity */
    meanTemp = meanTemp/Temperature_Values.length();
    meanHumidity = meanHumidity/Humidity_Values.length();
    double squareTempDif = 0;

    /* Get the square difference */
    for(int k = 0; k < Temperature_Values.length(); k++){

        squareTempDif = squareTempDif + ((Temperature_Values.at(k)-meanTemp)*(Temperature_Values.at(k)-meanTemp));

        /* Handle events and update UI */
        Application::processEvents();
    }

    /* Get the std */
    TempStandardDev = sqrt(squareTempDif/Temperature_Values.length());

    /* Show the actual temperature STD */
    Temperature_Plot->setTitle("Mean ± STD = " + QString().setNum(meanTemp, 'f', 3) + " ± " + QString().setNum(TempStandardDev, 'f', 6) + " °C");
    Humidity_Plot->setTitle("Mean Humidity = " + QString().setNum(meanHumidity, 'f', 3) + " %");

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
        Average_Ratio_Signal->detach();
        Compensation_Signal->detach();
        FFT_oneWave->detach();
        FFT_DC->detach();
        FFT_W->detach();
        FFT_2W->detach();
        predictionSignal->detach();
        Temperature_Plot->detach();
        Humidity_Plot->detach();
        AverageDetSignalPlotter->detach();
        DeviationVsMeasNumberPlot->detach();
    }

    /* Set all vectors to zero */
    averaged_Signal_time.resize(0);
    AverageDC.resize(0);
    AverageW.resize(0);
    Average2W.resize(0);
    AverageRatio.resize(0);
    Temperature_Values.resize(0);
    Humidity_Values.resize(0);
    counts_average_time = 0;

    TempStandardDev=0;
}

/**
 * @brief Clean the 3D plots.
 */
void Pol_Plot::restart3DPlots(void){

    surface->removeSeries(series);
    surface_norm->removeSeries(series_norm);
    surface->seriesList().clear();
    surface_norm->seriesList().clear();

    surface->axisX()->setTitle(QStringLiteral(""));
    surface_norm->axisX()->setTitle(QStringLiteral(""));
    surface->axisY()->setTitle(QStringLiteral(""));
    surface_norm->axisY()->setTitle(QStringLiteral(""));
    surface->axisZ()->setTitle(QStringLiteral(""));
    surface_norm->axisZ()->setTitle(QStringLiteral(""));

    surface_norm->axisX()->setRange(0,10);
    surface_norm->axisY()->setRange(0,10);
    surface_norm->axisZ()->setRange(0,10);

    surface->axisX()->setRange(0,10);
    surface->axisY()->setRange(0,10);
    surface->axisZ()->setRange(0,10);

    adjustSet3DPlots();

}


/**
 * @brief Adjust some axes and titles appearance
 */
void Pol_Plot::adjustSet3DPlots(void){

    surface->scene()->activeCamera()->setCameraPosition(45, 45, 80); // horizontal in °, vertikal in °, zoom in %
    surface->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow
                              | QAbstract3DGraph::SelectionSlice);

    surface_norm->scene()->activeCamera()->setCameraPosition(45, 45, 80); // horizontal in °, vertikal in °, zoom in %
    surface_norm->setSelectionMode(QAbstract3DGraph::SelectionItemAndRow
                                   | QAbstract3DGraph::SelectionSlice);

    surface->axisX()->setLabelFormat("%d");
    surface->axisY()->setLabelFormat("%.1f ");
    surface->axisZ()->setLabelFormat("%.1f");

    surface_norm->axisX()->setLabelFormat("%d");
    surface_norm->axisY()->setLabelFormat("%.3f ");
    surface_norm->axisZ()->setLabelFormat("%.1f");

    surface->activeTheme()->setLabelBorderEnabled(false);
    surface->activeTheme()->setLabelTextColor(QColor(QRgb(Qt::black)));
    surface->activeTheme()->setFont(QFont(QStringLiteral("Arial"), 40));

    surface_norm->activeTheme()->setLabelBorderEnabled(false);
    surface_norm->activeTheme()->setLabelTextColor(QColor(QRgb(Qt::black)));
    surface_norm->activeTheme()->setFont(QFont(QStringLiteral("Arial"), 40));
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

        Average_Ratio_Signal->detach();
        delete Average_Ratio_Signal;
        Average_Ratio_Signal= nullptr;

        Average_2W_Signal->detach();
        delete Average_2W_Signal;
        Average_2W_Signal= nullptr;

        Temperature_Plot->detach();
        delete Temperature_Plot;
        Temperature_Plot = nullptr;

        Humidity_Plot->detach();
        delete Humidity_Plot;
        Humidity_Plot = nullptr;

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

    delete AverageDetSignalPlotter;
    AverageDetSignalPlotter = nullptr;

    delete DeviationVsMeasNumberPlot;
    DeviationVsMeasNumberPlot = nullptr;

    delete series;
    series = nullptr;

    delete series_norm;
    series_norm = nullptr;

    delete surface;
    surface = nullptr;

    delete surface_norm;
    surface_norm = nullptr;

}
