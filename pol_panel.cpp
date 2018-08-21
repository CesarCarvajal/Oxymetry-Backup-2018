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
#include <QSettings>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QApplication>
#include <QSignalMapper>
#include <QCloseEvent>
#include <QSizePolicy>
#include <QTime>
#include <QDate>

/*
 * Internal includes
 */

/* Qt library */

/* General stuff */
#include "application.h"
#include "messages.h"
#include "timer.h"
#include "math_helper.h"
#include <qprocess.h>
#include "qwt_plot.h"
#include "qwt_plot_renderer.h"

/* Polarimeter Panel stuff */
#include "pol_plot.h"
#include "pol_panel.h"
#include "pol_fft.h"
#include "pol_panelHelp.h"
#include "pol_ConfigureMeasurement.h"
#include "pol_changeWaveOrFreq.h"
#include "pol_set_wavelength_ranges.h"
#include "pol_panelItem.h"
#include "ui_pol_panelItem.h"
#include "ui_pol_panel.h"
#include "pol_measurements.h"
#include "pol_waitingDialog.h"
#include "ui_pol_ConfigureMeasurement.h"
#include "pol_analizeData.h"
#include "ui_pol_AnalizeData.h"

/* Panel stuff */
#include "panel_change_averages.h"
#include "panel_change_time.h"
#include "plot.h"

/* Spectrometer control */
#include "spectrometer.h"

/*
 * Global variables
 */
extern QSettings *settings;
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/* Colors for spectrometers */
extern QString defaultColors[];

/* SYSTEM ------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Constructor of 'Polarimeter' class
 */
PanelPolarimeter::PanelPolarimeter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanelPolarimeter)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Start the abort signal in false */
    abort_everything = false;

    /* No data loaded before */
    dataloaded = false;

    /* Start the time index in 0 */
    Timeindex = 0;

    /* Restart FFT flag */
    isFFTData = true;

    /* Restart the flag for edition of configuration during the calibration */
    editedConf = false;

    /* Default selected spectrometer is the first on the list */
    SpectrometerNumber = 0;

    /* Configuration Object */
    ConfigureMeasurement = new configurePolMeasure();

    /* Create Plotter Object */
    PolPlotter = new Pol_Plot();

    /* Create signal mapper for panel */
    signalMapper = new QSignalMapper(this);

    /* Create Measurements Runner Object */
    Runner = new Pol_Measurements();

    /* Create new item in Polarimeter Spectrometer List */
    QListWidgetItem *item_Pol = new QListWidgetItem(0);

    /* Not everything from the UI has to be shown at the beginning */
    showUI_Item(false);

    /* Get current path to executable */
    currentWorkingPath = QDir::currentPath();

    /* Remove 'binary/[platform]' part from string */
    currentWorkingPath = currentWorkingPath.left(currentWorkingPath.lastIndexOf("binary"));

    /* Hide Elements, they will be available by demand */
    ui->TotalProgressBar_Pol->setVisible(false);
    ui->label_totalM->setVisible(false);
    ui->label_remaining->setVisible(false);
    ui->horizontalSpacer_Y->changeSize(20,12,QSizePolicy::Expanding,QSizePolicy::Fixed);
    ui->currentProgressBar_Pol->setVisible(false);
    ui->qwtPlot_Pol_Prediction->setVisible(false);
    ui->Tabs_Plots->setTabEnabled(1,false);
    ui->Tabs_Plots->setTabEnabled(2,false);
    ui->label_PlotSaturated->setStyleSheet(QString("color: red; font: bold;"));
    ui->label_PlotSaturated->setVisible(false);

    /* Set window flags */
    this->setWindowFlags(Qt::Window);

    /* If we have at least one device selected from the list or available */
    if (m_NrDevices > 0)
    {
        /* The purpose of this list is to inform which spectrometer is in use for the Polarimetry Tab. Be able to see
        its name and change its parameters as the Integration time, number of averages, name and set the Auto Adjust */

        /* By Default, use the First Device checked on the List of Spectrometers from Preview Tab */

        /* Does the first spectrometer already have a readable name assigned? */
        if (ptrSpectrometers[SpectrometerNumber]->hasReadableName()){

            /* Yes. Add the spectrometer to the list using the readable name. */
            PolarimetrySpectrometer = new PanelItem_Pol(0, ptrSpectrometers[SpectrometerNumber]->getReadableName());
        }
        else{
            /* No. Add the spectrometer to the list using the serial number. */
            PolarimetrySpectrometer = new PanelItem_Pol(0, ptrSpectrometers[SpectrometerNumber]->getSerialNumber());
        }

        /* Polarimeter Setup Device Initialization */
        PolarimetrySpectrometer->setIntegrationTime(ptrSpectrometers[SpectrometerNumber]->getIntegrationTime());
        PolarimetrySpectrometer->setIsSaturated(ptrSpectrometers[SpectrometerNumber]->isSaturated());
        ui->label_PlotSaturated->setVisible(ptrSpectrometers[SpectrometerNumber]->isSaturated());
        PolarimetrySpectrometer->setIsEnabled(true);

        /* Set default values for the number of averages and frequency */
        PolarimetrySpectrometer->setNumberOfSpectra(1000);
        PolarimetrySpectrometer->setFrequency(7);

        /* If the number of averages is greater than the maximum for polarimeter then set the maximum possible */
        if(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages() > floor((1000)/(4*PolarimetrySpectrometer->getIntegrationTime()
                                                                                       *PolarimetrySpectrometer->getFrequency()))){
            /* Set maximum possible number of averages */
            PolarimetrySpectrometer->setNumberOfAverages(floor((1000)/(4*PolarimetrySpectrometer->getIntegrationTime()*PolarimetrySpectrometer->getFrequency())));

        }else{

            /* The actual value is still valid */
            PolarimetrySpectrometer->setNumberOfAverages(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages());
        }

        /* Don't allow resize of item */
        item_Pol->setSizeHint(PolarimetrySpectrometer->size());

        /* Polarimeter List Item */
        ui->list_devices_Pol->addItem(item_Pol);
        ui->list_devices_Pol->setItemWidget(item_Pol, PolarimetrySpectrometer);

        /* Set the label clear all as clickable */
        ui->label_clearAll->setStyleSheet("QLabel { color: blue; }");

        /* Does the first spectrometer already have a readable name assigned? */
        if (ptrSpectrometers[SpectrometerNumber]->hasReadableName())
        {
            /* Polarimeter Plot of Raw Signal */
            curve_Pol = new QwtPlotCurve(ptrSpectrometers[SpectrometerNumber]->getReadableName());

        }else{
            /* Polarimeter Plot of Raw Signal */
            curve_Pol = new QwtPlotCurve(ptrSpectrometers[SpectrometerNumber]->getSerialNumber());
        }

        /* Polarimeter Plot of Raw Signal Color and attachment */
        curve_Pol->setItemAttribute(QwtPlotItem::Legend, false);
        curve_Pol->setPen(QPen(defaultColors[SpectrometerNumber % 5]));
        curve_Pol->attach(ui->qwtPlot_Pol);

        /* Polarimeter buttons and labels signal mapper */
        connect(PolarimetrySpectrometer->ui->label_integrationTime, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(PolarimetrySpectrometer->ui->label_setWranges, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(PolarimetrySpectrometer->ui->label_Nspectra, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(PolarimetrySpectrometer->ui->label_frequency, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(PolarimetrySpectrometer->ui->label_numberOfAverages, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(PolarimetrySpectrometer->ui->label_autoAdjust, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(PolarimetrySpectrometer->ui->checkBox_normalize, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(PolarimetrySpectrometer->ui->lineEdit_name, SIGNAL(returnPressed()), signalMapper, SLOT(map()));

        /* Polarimeter set mapping for buttons and labels */
        signalMapper->setMapping(PolarimetrySpectrometer->ui->label_integrationTime, PolarimetrySpectrometer->ui->label_integrationTime);
        signalMapper->setMapping(PolarimetrySpectrometer->ui->label_setWranges, PolarimetrySpectrometer->ui->label_setWranges);
        signalMapper->setMapping(PolarimetrySpectrometer->ui->label_frequency, PolarimetrySpectrometer->ui->label_frequency);
        signalMapper->setMapping(PolarimetrySpectrometer->ui->label_Nspectra, PolarimetrySpectrometer->ui->label_Nspectra);
        signalMapper->setMapping(PolarimetrySpectrometer->ui->label_numberOfAverages, PolarimetrySpectrometer->ui->label_numberOfAverages);
        signalMapper->setMapping(PolarimetrySpectrometer->ui->label_autoAdjust, PolarimetrySpectrometer->ui->label_autoAdjust);
        signalMapper->setMapping(PolarimetrySpectrometer->ui->checkBox_normalize, PolarimetrySpectrometer->ui->checkBox_normalize);
        signalMapper->setMapping(PolarimetrySpectrometer->ui->lineEdit_name, PolarimetrySpectrometer->ui->lineEdit_name);
        signalMapper->setMapping(ui->label_clearAll, ui->label_clearAll);
        signalMapper->setMapping(ui->label_hideLiveRaw, ui->label_hideLiveRaw);
        signalMapper->setMapping(ui->label_HideRatio, ui->label_HideRatio);
        signalMapper->setMapping(ui->label_HideFFTProfile, ui->label_HideFFTProfile);
        signalMapper->setMapping(ui->label_HIdeLiveAverage, ui->label_HIdeLiveAverage);
        signalMapper->setMapping(ui->FFT_label_Pol, ui->FFT_label_Pol);
        signalMapper->setMapping(ui->label_Measurements_Pol, ui->label_Measurements_Pol);
        signalMapper->setMapping(ui->label_hideConf, ui->label_hideConf);

        /* Connect event handler */
        connect(qApp, SIGNAL(DataPolIsHere(int, int)), this, SLOT(receive_Data_Pol(int, int)));

        /* If the window is closed, then stop everything */
        connect(qApp,SIGNAL(lastWindowClosed()),this,SLOT(quit_Oxymetry()));
    }

    /* Connect signal mapper action */
    connect(signalMapper, SIGNAL(mapped(QWidget *)), this, SLOT(handle_Click_Event(QWidget *)));

    /* Connect buttons in Polarimeter Tab */
    connect(ui->button_Start_Meas_Pol, SIGNAL(clicked()), this, SLOT(toggle_Pol_Measurement()));
    connect(ui->button_SaveInstantFFT, SIGNAL(clicked()), this, SLOT(saveFFTcalibration()));
    connect(ui->button_LoadData, SIGNAL(clicked()), this, SLOT(toggle_Load_Data()));
    connect(ui->help, SIGNAL(clicked()), this, SLOT(help_Pol()));
    connect(ui->waveToPlotFFT, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_clearAll, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_hideLiveRaw, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_HideRatio, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->Button_Save_Graphs_Pol, SIGNAL(clicked()), this, SLOT(save_Graph_Pol()));
    connect(ui->button_calibrate, SIGNAL(clicked()), this, SLOT(toggle_Pol_Calibration()));
    connect(ui->button_Pol_ConfigureMeasurement, SIGNAL(clicked()), this, SLOT(conf_Setup_Pol_Measurement()));
    connect(ui->button_AnalizeData, SIGNAL(clicked()), this, SLOT(select_Analize_Pol_Measurement()));
    connect(ui->label_HideFFTProfile, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_HIdeLiveAverage, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->FFT_label_Pol, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_Measurements_Pol, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_hideConf, SIGNAL(clicked()), signalMapper, SLOT(map()));

    /* Set button styles */
    ui->button_Start_Meas_Pol->setStyleSheet(greenButton);
    ui->label_hideConf->setStyleSheet("QLabel { color: blue; }");

    /* If there are spectrometers connected, allow Polarimetry Measurement or Calibration */
    ui->button_Start_Meas_Pol->setDisabled((!m_NrDevices) ? true : false);
    ui->button_Start_Meas_Pol->setStyleSheet((!m_NrDevices) ? grayButton : greenButton);
    ui->button_calibrate->setDisabled((!m_NrDevices) ? true : false);
    ui->button_calibrate->setStyleSheet((!m_NrDevices) ? grayButton : "black");
    ui->button_Pol_ConfigureMeasurement->setDisabled((!m_NrDevices) ? true : false);
    ui->label_clearAll->setDisabled((!m_NrDevices) ? true : false);

    /* Plots */

    /* Raw Signal plot for Polarimeter */
    ui->qwtPlot_Pol->setXAxisTitle("Wavelength λ (nm)");
    ui->qwtPlot_Pol->setYAxisTitle("ADC (Counts)");
    maxYRaw = 65535.0;
    ui->qwtPlot_Pol->setYAxis(0.0, maxYRaw);

    /* Compensated Signal plot for Polarimeter */
    ui->qwtPlot_Pol_Compensation->setXAxisTitle("Wavelength λ (nm)");
    ui->qwtPlot_Pol_Compensation->setYAxisTitle("Ratio");
    ui->qwtPlot_Pol_Compensation->setYAxis(0.0, 3);

    /* FFT Profile plot for Polarimeter */
    ui->qwtPlot_Pol_w_2w->setXAxisTitle("Wavelength λ (nm)");
    ui->qwtPlot_Pol_w_2w->setYAxisTitle("FFT Intensity (Counts)");
    ui->qwtPlot_Pol_w_2w->setYAxis(0.0, 40000);

    /* Average over all Wavelengths plot for Polarimeter */
    ui->qwtPlot_Pol_Average->setXAxisTitle("Time (sec)");
    ui->qwtPlot_Pol_Average->setXAxisTopTitle("Measurement Number");
    ui->qwtPlot_Pol_Average->setYAxisTitle("Average FFT Intensity (Counts)");
    ui->qwtPlot_Pol_Average->setYAxis(0.0, ceil(2000*1.1));
    minXAverage = 0;
    maxXAverage = PolPlotter->time_plot;
    maxYAverage = 0;
    ui->qwtPlot_Pol_Average->setXAxis(minXAverage, maxXAverage);

    /* Set top axis with Measurement number for averages */
    ui->qwtPlot_Pol_Average->enableAxis(QwtPlot::xTop);
    ui->qwtPlot_Pol_Average->setXAxisTop(-0.8 , 20.3, 2);

    /* FFT Curve at a certain Wavelength */
    ui->qwtPlot_Pol_FFT->setXAxis(0.0, 21);
    ui->qwtPlot_Pol_FFT->setYAxis(0.0, 3000);
    QwtText bottomTitle = QString("Frequency ƒ (Hz)");
    ui->qwtPlot_Pol_FFT->axisFont.setPointSize(8);
    bottomTitle.setFont(ui->qwtPlot_Pol_FFT->axisFont);
    ui->qwtPlot_Pol_FFT->setAxisTitle(QwtPlot::xBottom, bottomTitle);
    ui->qwtPlot_Pol_FFT->grid->enableX(false);
    ui->qwtPlot_Pol_FFT->setAxisScale(QwtPlot::xBottom, 0, 21, 7);
    ui->qwtPlot_Pol_FFT->setAxisScale(QwtPlot::yLeft, 0, 3000, 1000);
    ui->qwtPlot_Pol_FFT->updateAxes();

    /* Prediction Curve, available during the measurements */
    ui->qwtPlot_Pol_Prediction->setXAxisTitle("Reference (mg/dL)");
    ui->qwtPlot_Pol_Prediction->setYAxisTitle("Predicted (mg/dL)");
    ui->qwtPlot_Pol_Prediction->setXAxis(0.0, 500);
    ui->qwtPlot_Pol_Prediction->setYAxis(0.0, 500);
    ui->label_RemainingTime->setVisible(false);

    /* Show and format all plots */
    showAllPlots();

    /* Are there any spectrometers connected? */
    if (m_NrDevices > 0)
    {
        /* Find minimum and maximum wavelengths in array */
        PolarimetrySpectrometer->setWavelengthRange(ptrSpectrometers[SpectrometerNumber]->getStartWavelength(), ptrSpectrometers[SpectrometerNumber]->getStopWavelength());

        /* Set limits for the wavelengths range */
        ConfigureMeasurement->ui->doubleSpinBox_minW->setMinimum(PolarimetrySpectrometer->getMinimumWavelength());
        ConfigureMeasurement->ui->doubleSpinBox_minW->setMaximum(PolarimetrySpectrometer->getMaximumWavelength());
        ConfigureMeasurement->ui->doubleSpinBox_maxW->setMinimum(PolarimetrySpectrometer->getMinimumWavelength());
        ConfigureMeasurement->ui->doubleSpinBox_maxW->setMaximum(PolarimetrySpectrometer->getMaximumWavelength());

        /* Which wavelentgth would you like to see the FFT? */
        signalMapper->setMapping(ui->waveToPlotFFT, ui->waveToPlotFFT);

        /* Disable edition of Spectrometer Data until there is a calibration running */
        PolarimetrySpectrometer->enableComponents(false);

        /* Update x-axis of graphs depending on Wavelengths */
        update_Wavelength_Range();
    }

    /* Hide Button for saving actual spectra */
    ui->button_SaveInstantFFT->setVisible(false);
    ui->Button_Save_Graphs_Pol->setVisible(false);

    container = QWidget::createWindowContainer(PolPlotter->surface);

    /* Add the 3D plot to the widget */
    ui->VLP->addWidget(container);

    //QWidget *container = QWidget::createWindowContainer(PolPlotter->scatter);

}

/**
 * @brief Adjust plotting time in live averages.
 */
void PanelPolarimeter::adjust_Average_Plot_Time(void){

    /* How long does take a measurement? */
    int measuringTime = (ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime
                         *ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra*
                         ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrAverages/1000);

    /* Plot always 20 measurements per refresh */
    PolPlotter->time_plot = (measuringTime + measuringTime/3 + 12)*20;

    /* Adjust axes according to the values */
    minXAverage = PolPlotter->averaged_Signal_time.at(0);
    maxXAverage = PolPlotter->averaged_Signal_time.at(0)+ PolPlotter->time_plot;
    ui->qwtPlot_Pol_Average->setXAxis(minXAverage,maxXAverage);
}

/**
 * @brief Automatic adjustment of integration time
 */
void PanelPolarimeter::adjust_Integration_Time_Pol(void)
{
    /* Is the spectrometer measuring? */
    if (ptrSpectrometers[SpectrometerNumber]->isMeasuring())
    {
        /* Yes, so stop the calibration */
        ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

        /* Handle events and update UI */
        Application::processEvents();

        /* Wait 1 ms */
        Timer::msleep(1);
    }

    /* If high-resolution ADC is enabled, try to reach 60000 counts; else 15000 */
    double targetCounts = ptrSpectrometers[SpectrometerNumber]->getUseHighResADC() ? 60000.0 : 15000.0;

    /* Remember whether the spectrometer has dynamic dark correction enabled or not */
    bool hadDynamicDarkCorrection = ptrSpectrometers[SpectrometerNumber]->getDynamicDarkCorrection();

    /* Remember current number of averages */
    int numberOfAverages = ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages();

    /* Enable dynamic dark correction */
    ptrSpectrometers[SpectrometerNumber]->setForgetPercentage(100);
    ptrSpectrometers[SpectrometerNumber]->setDynamicDarkCorrection(true);

    /* Reduce number of averages to minimum */
    ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(1);

    /* Maximum counts from last spectrum */
    double maxCounts = 0.0;

    /* Number of loops done for adjustment */
    unsigned char loopCounts = 0;

    do
    {
        /* Prepare measurement; only continue if successful */
        if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
        {
            /* Number of measurements done */
            unsigned long before = 0;

            /* Get current number of measurements done */
            before = ptrSpectrometers[SpectrometerNumber]->getMeasCount();

            /* Measure one spectra */
            if (ptrSpectrometers[SpectrometerNumber]->startMeasurement(2))
            {
                /* Wait until done; update event loop */
                do
                {
                    /* Handle events and update UI */
                    Application::processEvents();

                    /* Wait 1 ms */
                    Timer::msleep(1);
                }
                while (ptrSpectrometers[SpectrometerNumber]->getMeasCount() < before + 1);
            }
            else
            {
                /* Restore spectrometer settings */
                ptrSpectrometers[SpectrometerNumber]->setDynamicDarkCorrection(hadDynamicDarkCorrection);
                ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(numberOfAverages);

                /* Show warning */
                showWarning(QString("Unable to start measurement on spectrometer %1!").arg(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()), QString(""));
                break;
            }
        }
        else
        {
            /* Restore spectrometer settings */
            ptrSpectrometers[SpectrometerNumber]->setDynamicDarkCorrection(hadDynamicDarkCorrection);
            ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(numberOfAverages);

            /* Show warning */
            //showWarning(QString("Unable to prepare measurement on spectrometer %1!").arg(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()), QString(""));
            break;
        }

        /* Get maximum counts from last spectrum */
        maxCounts = ptrSpectrometers[SpectrometerNumber]->getMaxCounts();

        /* Do we have more than 5% deviation from target? */
        if ((maxCounts > (targetCounts + (targetCounts * 5 / 100))) ||
                (maxCounts < (targetCounts - (targetCounts * 5 / 100))))
        {
            /* Get current integration time */
            float intTime = PolarimetrySpectrometer->getIntegrationTime();

            double scaleFactor = 0.0;

            /* Is spectrometer saturated? */
            if (!ptrSpectrometers[SpectrometerNumber]->isSaturated())
            {
                /* Spectrometer is not saturated, so calculate scale factor by maximum counts */
                scaleFactor = targetCounts / maxCounts;
            }
            else
            {
                /* Spectrometer is saturated, so divide integration time by two */
                scaleFactor = 0.5;
            }

            /* Scale integration time with calculated factor; limit number to 2 decimal places */
            intTime = (float)(((int)(intTime * scaleFactor * 100)) / 100.0);

            /* New integration time greater than 10 seconds? */
            if (intTime > 250.0f)
            {
                /* Limit to 250 seconds */
                intTime = 250.0f;
            }

            /* Integration time smaller than 1.05 ms? */
            if (intTime < 1.05f)
            {
                /* Limit to 1.05 ms */
                intTime = 1.05f;
            }

            /* Set panel item and device new integration time */
            PolarimetrySpectrometer->setIntegrationTime(intTime);
            ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(intTime);
        }

        /* Increase loop counter */
        loopCounts++;

        /* Limit number of loops for adjustment to 10 */
        if (loopCounts >= 10)
        {
            /* Show warning */
            showWarning(QString("Unable to adjust integration time on spectrometer %1 within 10 iterations!").arg(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()), QString(""));
            break;
        }
    }
    /* Leave loop if counts have less than 5% deviation from target */
    while ((maxCounts > (targetCounts + (targetCounts * 5 / 100))) ||
           (maxCounts < (targetCounts - (targetCounts * 5 / 100))));

    /* Restore spectrometer settings */
    ptrSpectrometers[SpectrometerNumber]->setDynamicDarkCorrection(hadDynamicDarkCorrection);
    ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(numberOfAverages);

    /* Save changes on other objects variables */
    ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime = ptrSpectrometers[SpectrometerNumber]->getIntegrationTime();
    FFTL.IntTime = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime;

    /* Is the spectrometer measuring? */
    if (ptrSpectrometers[SpectrometerNumber]->isMeasuring())
    {
        /* Yes, so stop the calibration */
        ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

        /* Handle events and update UI */
        Application::processEvents();

        /* Wait 1 ms */
        Timer::msleep(1);

    }
}

/**
 * @brief Adjust the Folder to save the data for the measurements.
 */
void PanelPolarimeter::adjust_Measurements_Saving_Folder(void)
{
    /* Create a Folder with the actual date and a number */
    folderForData = "Measurement Data " + QDate::currentDate().toString("dd MM yyyy") + "_0";

    /* Check if the folder with that name already exists */
    if (!QDir(ConfigureMeasurement->pathDataMeasurements.absolutePath()).mkdir(folderForData))
    {
        /* Create a folder with the same name but add a different number to it */
        int i = 1;

        /* Depending on how many folders are there already, then create the next in the list */
        while(true){

            /* Change the folder's name to the next name in the list */
            folderForData = "Measurement Data " + QDate::currentDate().toString("dd MM yyyy") + "_" + QString::number(i);

            /* Handle events and update UI */
            Application::processEvents();

            /* The new name doesn't exists, so stop creating new folders */
            if(QDir(ConfigureMeasurement->pathDataMeasurements.absolutePath()).mkdir(folderForData))
            {
                /* Break creating folders */
                break;
            }

            /* Next folder number in case that it already exists with that number */
            i++;
        }
    }
}

/**
 * @brief Adjust the Running End
 * @param[in] Type 1 means Measurement, 0 means Calibration.
 */
void PanelPolarimeter::adjust_Run_End(){

    /* When finish, give some time to plot the last data point in the average during the Measurements */
    Runner->timerMS.start();

    /* Start plotting the averages at the end of the Measurements */
    int t = 0;

    /* Update information bar */
    ui->info->setText("Finishing Measurements... Please Wait");

    /* Set the stop of the measurement to true, so the long term Measurement can be stopped */
    Runner->setMeasurementRunning(true);

    /* Keep plotting the average signals, so the last data point is visible at the end of the Measurements */
    while(!Runner->Stopped && !abort_everything){

        /* Count some seconds */
        if(Runner->timerMS.elapsed()/1000 > t){

            /* Count seconds */
            t = t+1;

            /* The total time is reduced each second */
            totalMeasuretime = totalMeasuretime - 1;

            /* To avoid the use of ms, then when it's less than 1, means almost zero */
            if(totalMeasuretime < 1){

                /* Set to zero when waiting for milliseconds */
                totalMeasuretime = 0;
            }

            /* Handle events and update UI */
            Application::processEvents();

            /* Change time to the proper units */
            QStringList ConvertedTime = ConfigureMeasurement->externSoftware->TimeConverter(totalMeasuretime);

            /* In case of less than 1 day measuring */
            if(ConvertedTime.at(1)!="days"){
                ui->label_RemainingTime->setText(QDateTime::fromTime_t(totalMeasuretime).toUTC().toString("hh:mm:ss") + " " + ConvertedTime.at(1));
            }else{

                /* Show days in the remaining time */
                int nDays = ConvertedTime.at(0).toDouble();
                ui->label_RemainingTime->setText(QString::number(nDays) + ":" + QDateTime::fromTime_t(totalMeasuretime-(nDays*86400)).toUTC().toString("hh:mm:ss") + " "
                                                 + ConvertedTime.at(1));
            }

            /* Plot 300 points for all the measurements */
            if(t % Runner->measurementPlotTimeInterval == 0){

                /* Plot last entry */
                plot_Average();

                /* Handle events and update UI */
                Application::processEvents();
            }
        }

        /* If the window is closed or a certain time in seconds has elapsed then break the loop */
        if(totalMeasuretime == 0){break;}
    }

    /* If the measurement stopped by its own, then save the summary */
    if(!Runner->Stopped && !abort_everything){
        /* Save the summary */
        write_Summary();
    }

    /* Reset selection */
    ui->Table_Measurements_Pol->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->Table_Measurements_Pol->selectRow(0);
    ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::NoSelection);

    for(int i = 0; i < ui->Table_Measurements_Pol->rowCount(); i++){
        ui->Table_Measurements_Pol->cellWidget(i, 0)->setStyleSheet("qproperty-alignment: AlignCenter;" "background-color: rgb(255, 255, 255)");

        /* Handle events and update UI */
        Application::processEvents();
    }

    /* Set progress bars to 100 percent */
    ui->currentProgressBar_Pol->setValue(0);
    ui->currentProgressBar_Pol->hide();
    ui->TotalProgressBar_Pol->setValue(0);
    ui->TotalProgressBar_Pol->hide();
    ui->label_totalM->hide();
    ui->label_remaining->hide();
    ui->label_RemainingTime->hide();

    /* If the Measurement is done by no more entries, then just stop the measurement */
    stop_Run_Polarimetry();

    /* If the measurement stopped by itself */
    if(!Runner->Stopped && !ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->intervalMode){

        /* Allow the automatic loading of files to the analize data window after the measurement */
        Runner->automaticData = true;

        /* Open the data analizer window */
        select_Analize_Pol_Measurement();

        /* Show prediciton plot - NO YET */
        ui->Tabs_Plots->setTabEnabled(1, true);
    }
}

/**
 * @brief Adjust the Running Start
 * @param[in] Type 1 means Measurements, 0 means Calibration
 */
void PanelPolarimeter::adjust_Run_Start(short int typeRun){

    /* Emit signal to disable preview buttons */
    DisEnablePreview(false);

    /* Enable saving plots to PDF button*/
    ui->Button_Save_Graphs_Pol->setVisible(true);

    /* Show current progress bar for the Measurements and Calibration */
    ui->currentProgressBar_Pol->setVisible(true);

    /* Restart maximum Intensity measured */
    FFTL.MaximumIntensity = 0;

    /* Re-attach the raw signal plot in case it was removed for example when cleaning all */
    curve_Pol->attach(ui->qwtPlot_Pol);

    if(ConfigureMeasurement->configured){
        ui->Table_Measurements_Pol->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->Table_Measurements_Pol->selectRow(0);
        ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::NoSelection);
        ui->Table_Measurements_Pol->cellWidget(0, 0)->setStyleSheet("qproperty-alignment: AlignCenter;" "background-color: rgb(0, 153, 255)");
    }

    /* Restart delayed stop flags for Calibration */
    Runner->delayStop = false;

    /* Disable buttons and labels when running polarimetry */
    ui->button_LoadData->setEnabled(false);
    ui->button_LoadData->setVisible(false);
    ui->button_AnalizeData->setEnabled(false);
    ui->button_AnalizeData->setVisible(false);
    ui->button_Start_Meas_Pol->setEnabled(false);
    ui->button_calibrate->setEnabled(false);
    ui->button_Pol_ConfigureMeasurement->setEnabled(false);
    ui->label_clearAll->setEnabled(false);
    ui->label_clearAll->setVisible(false);
    ui->label_clearAll->setStyleSheet("QLabel { color: gray;}");

    /* Is the spectrometer enabled? */
    PolarimetrySpectrometer->setIsEnabled(false);

    /* Initialize the time for each type of run, Calibrate: raw or FFT */
    Runner->liveFFT_Time = 0;
    Runner->Calibration_Progress = 0;
    ui->currentProgressBar_Pol->setValue(0);

    /* runType == 0 means Calibration and runType == 1 means Measuring */
    if(typeRun == 0){

        /* Initialize the Calibration configuration and parameters */
        initialize_Calibration();
    }

    /* Then it's measuring */
    else{

        /* Remember Polarimeter Measurement is Running */
        Runner->setMeasurementRunning(true);

        /* Time measurement index for Measurements, restart to 0 when starting a measurement */
        Timeindex = 0;

        /* Update polarimetric Measurement button */
        ui->button_Start_Meas_Pol->setText("Stop Measurement");
        ui->button_Start_Meas_Pol->setToolTip("Stop Measurement");
        ui->button_Start_Meas_Pol->setStyleSheet(RedButton);
        ui->button_Start_Meas_Pol->setEnabled(true);

        /* Restart Measurement progress bars */
        ui->currentProgressBar_Pol->setValue(0);
        ui->TotalProgressBar_Pol->setValue(0);

        /* Show the remaining label */
        ui->label_remaining->setVisible(true);

        /* Calculate the total time length of the measurements */
        int measurementLength = ConfigureMeasurement->totalMtime;

        /* Adjust the intervals of averages plot during the measurements, to get 300 points */
        Runner->measurementPlotTimeInterval = int(ceil(ConfigureMeasurement->totalMtime/300));

        /* Adjust axis for the measurements */
        minXAverage = 0;
        maxXAverage = measurementLength + measurementLength*0.1;
        ui->qwtPlot_Pol_Average->setXAxis(minXAverage, maxXAverage);

        /* Adjust the measurement number plot in the averages */
        double lengthMeasNumber = 0;

        /*  Is this special mode active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->intervalMode){

            /* How many points this case? */
            lengthMeasNumber = maxXAverage / (ConfigureMeasurement->externSoftware->UserTimeInterval/1000);

        }else{

            /* How many measurement points are there? */
            lengthMeasNumber = maxXAverage  / (ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->PumpsCycle/1000);
        }

        /* Adjust the approximated measurement number in the x-top axis of the average */
        if(lengthMeasNumber < 25){

            /* If there are too many number, then just plot every two */
            ui->qwtPlot_Pol_Average->setXAxisTop(-0.5, lengthMeasNumber-0.5, 1);

        }else if(lengthMeasNumber > 500){

            /* If less points, then show all the measurement numbers */
            ui->qwtPlot_Pol_Average->setXAxisTop(-0.5, lengthMeasNumber-0.5, int(ceil(lengthMeasNumber/10)));

        }else{

            /* If there are too many number, then just plot every two */
            ui->qwtPlot_Pol_Average->setXAxisTop(-0.5, lengthMeasNumber-0.5, int(ceil(lengthMeasNumber/30)));
        }

        /* Clear all other plots too */
        PolPlotter->clean_AllPlots();

        /* Clear plots */
        clear_Plot();

        /* Activate the delayed measurmement */
        delay_Pol_Measurements();

        /* Load the length of the measurement */
        totalMeasuretime = ConfigureMeasurement->totalMtime;

        /* Change time to the proper units */
        QStringList ConvertedTime = ConfigureMeasurement->externSoftware->TimeConverter(totalMeasuretime);

        /* If there is less than 1 day measuring */
        if(ConvertedTime.at(1)!= "days"){
            ui->label_RemainingTime->setText(QDateTime::fromTime_t(totalMeasuretime).toUTC().toString("hh:mm:ss") + " " + ConvertedTime.at(1));
        }else{

            /* Show days in the remaining time */
            int nDays = ConvertedTime.at(0).toDouble();
            ui->label_RemainingTime->setText(QString::number(nDays) + ":" + QDateTime::fromTime_t(totalMeasuretime-(nDays*86400)).toUTC().toString("hh:mm:ss") + " " + ConvertedTime.at(1));
        }

        /* Show the remaining time */
        ui->label_RemainingTime->setVisible(true);

        /* Adjust the folder where the Measurement data is going to be saved */
        if(!Runner->Stopped){
            adjust_Measurements_Saving_Folder();
        }
    }

    /* Restart timers */
    Runner->RestartTimers();
}

/**
 * @brief Adjust the Wavelengths range
 */
void PanelPolarimeter::adjust_Wavelength_Range(void){

    /* Update information bar */
    ui->info->setText("Setting Wavelength Ranges...");

    /* Stop Calibration */
    Runner->AcceptParameterChanges();

    /* Open the dialog to change the number of averages */
    PanelSetWavelengthRanges changeDialog(this);

    /* Find minimum and maximum wavelengths in array */
    changeDialog.setValues(ptrSpectrometers[SpectrometerNumber]->getStartWavelength(), ptrSpectrometers[SpectrometerNumber]->getStopWavelength(),
                           PolarimetrySpectrometer->getMinimumWavelength(), PolarimetrySpectrometer->getMaximumWavelength());

    /* User pressed 'ok' */
    if (QDialog::Accepted == changeDialog.exec())
    {
        /* Stop the measurement */
        if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){

            /* If so, then stop */
            ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

            /* Handle events and update UI */
            Application::processEvents();

            /* Wait 1 ms */
            Timer::msleep(1);
        }

        /* Restart maximum Intensity measured */
        FFTL.MaximumIntensity = 0;

        /* Get and set new range */
        PolarimetrySpectrometer->setWavelengthRange(changeDialog.getMinValue(), changeDialog.getMaxValue());

        /* The value was changed*/
        editedConf = true;

        /* Update the wavelength range */
        update_Wavelength_Range();
    }

    /* Restart Y axis plot */
    Runner->maxRawCounts= -1;

    /* Current progress bar restart */
    ui->currentProgressBar_Pol->setValue(0);

    /* Update information bar */
    ui->info->setText("Setting Spectrometer... Please Wait");

    /* Update configuration */
    if(ConfigureMeasurement->configured){

        /* Update configuration values and form */
        ConfigureMeasurement->ui->doubleSpinBox_minW->setValue(PolarimetrySpectrometer->getMinimumWavelength());
        ConfigureMeasurement->ui->doubleSpinBox_maxW->setValue(PolarimetrySpectrometer->getMaximumWavelength());
        ConfigureMeasurement->updateConfigurationValues();
        ConfigureMeasurement->GetConfigurationData();
    }

    /* Restart the calibration */
    Runner->restart_CalibrationPol();

}

/**
 * @brief Change the integration time from the auto adjusting during calibration
 */
void PanelPolarimeter::change_Auto_Integration_Time_Pol(void){

    /* Update information bar */
    ui->info->setText("Auto Adjusting...");

    /* Stop Calibration */
    Runner->AcceptParameterChanges();

    /* Stop the measurement */
    if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){

        /* If so, then stop */
        ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

        /* Handle events and update UI */
        Application::processEvents();
    }

    /* Give it some time to process */
    Timer::msleep(10);

    /* Run automatic adjustment of integration time */
    adjust_Integration_Time_Pol();

    /* If the new value is consistent with the frequency */
    double Freqresolution = 1000/ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime;

    /* Is there a frequency resolution lower than 1 Hz? */
    if(Freqresolution/4 < 1){

        /* If yes, then use 1 Hz as the minimum frequency resolution */
        ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency = 1;
        PolarimetrySpectrometer->setFrequency(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency);
        FFTL.FrequencyF = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency;

        /* To resolve 1 Hz it only makes sense to use a maximum int time of 250 ms */
        PolarimetrySpectrometer->setIntegrationTime(250);
        ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(250);
        ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime = 250;
        FFTL.IntTime = 250;

        /* Ajust X axis of time plotting */
        adjust_Average_Plot_Time();

        /* Show message */
        showWarning("With your actual settings the resolution of integration time is maximum 250 ms with 1 Hz for W ", "");

        /* If not, set the maximum automatically */
    }else if(PolarimetrySpectrometer->getFrequency() > Freqresolution/4){

        /* Set frequency to the maximum allowed with actual settings */
        ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency = Freqresolution/4;
        PolarimetrySpectrometer->setFrequency(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency);
        FFTL.FrequencyF = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency;

        /* Ajust X axis of time plotting */
        adjust_Average_Plot_Time();

        /* Auto adjusted frequency */
        QString messenger = "Frequency was adjusted to " + QString::number(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency) + " Hz becuase it's the maximum resolution ";
        showCritical(messenger, "");

        /* If the new int time is ok, then continue normally */
    }else{

        /* Save automatic changes on integration time */
        FFTL.IntTime = ptrSpectrometers[SpectrometerNumber]->getIntegrationTime();
        ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime = ptrSpectrometers[SpectrometerNumber]->getIntegrationTime();

        /* Ajust X axis of time plotting */
        adjust_Average_Plot_Time();

    }

    /* If there is a configuration loaded, then change the file names */
    change_File_Name();

    /* The value was changed*/
    editedConf = true;

    /* Restart Y axis of raw data plot */
    Runner->maxRawCounts=-1;

    /* Current progress bar restart */
    ui->currentProgressBar_Pol->setValue(0);

    /* Update information bar */
    ui->info->setText("Setting Spectrometer... Please Wait");

    /* Update configuration */
    if(ConfigureMeasurement->configured){
        ConfigureMeasurement->ui->doubleSpinBox_intTime->setValue(PolarimetrySpectrometer->getIntegrationTime());
        ConfigureMeasurement->updateConfigurationValues();
        ConfigureMeasurement->GetConfigurationData();

    }

    /* Restart the calibration */
    Runner->restart_CalibrationPol();
}

/**
 * @brief Change the Integration time by the user during calibration
 */
void PanelPolarimeter::change_Integration_Time_Pol(void){

    /* Update Information bar */
    ui->info->setText("Setting Integration Time...");

    /* Skip running the calibration routine */
    Runner->AcceptParameterChanges();

    /* Open the integration time panel to change it */
    PanelChangeTime changeDialog(this);

    /* Get the actual integration time */
    changeDialog.setValue(PolarimetrySpectrometer->getIntegrationTime());

    /* User pressed 'ok' */
    if (QDialog::Accepted == changeDialog.exec())
    {
        /* Stop the measurement */
        if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){
            /* Stop the Spectrometer */
            ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

            /* Handle events and update UI */
            Application::processEvents();

            /* Wait 1 ms */
            Timer::msleep(1);
        }

        /* Get new integration time */
        float intTime = changeDialog.getValue();

        /* Is it an aceptable integration time? */
        double Timeresolution = 1000/(4*PolarimetrySpectrometer->getFrequency());

        /* Too large integration time for the actual settings? */
        if( intTime > Timeresolution){
            /* Show message */
            QString messenger = "Your actual settings allow a maximum integration time of " + QString::number(Timeresolution) + " ms ";
            showCritical(messenger, "");
            return;
        }

        /* Set panel item and device integration time */
        PolarimetrySpectrometer->setIntegrationTime(intTime);
        ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(intTime);

        /* Save changes everywhere */
        FFTL.IntTime = intTime;
        ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime = intTime;

        /* If there is a configuration loaded, then change the file names */
        change_File_Name();

        /* The value was changed*/
        editedConf = true;

        /* Ajust X axis of time plotting */
        adjust_Average_Plot_Time();

        /* Too large integration time? */
        if(intTime > 100){

            /* Show message */
            showWarning("Please consider that large integration times may require longer time of Data processing.", "");
        }
    }

    /* Restart Y axis plot */
    Runner->maxRawCounts=-1;

    /* Current progress bar restart */
    ui->currentProgressBar_Pol->setValue(0);

    /* Update information bar */
    ui->info->setText("Setting Spectrometer... Please Wait");

    /* Update configuration */
    if(ConfigureMeasurement->configured){

        /* Update the configuration values and form */
        ConfigureMeasurement->ui->doubleSpinBox_intTime->setValue(PolarimetrySpectrometer->getIntegrationTime());
        ConfigureMeasurement->updateConfigurationValues();
        ConfigureMeasurement->GetConfigurationData();
    }

    /* Restart the calibration */
    Runner->restart_CalibrationPol();
}

/**
 * @brief If a configuration file was loaded and changes were made during the Calibration, then change file names
 */
void PanelPolarimeter::change_File_Name(void){

    /* When a configuration is loaded and changes are made during the Calibration, then update the file names */
    if(Runner->PolConfigured){

        /* Get first name on the list */
        QString changeFileName, NewFileName = "";

        /* For each file in the list */
        for(int j = 0; j < ConfigureMeasurement->savingFilesNames.length(); j++){

            /* Get first name on the list */
            changeFileName = ConfigureMeasurement->savingFilesNames.at(j);
            NewFileName = changeFileName.left(changeFileName.lastIndexOf("C")+2);

            /* Change the name by the first part plus the new information */
            ConfigureMeasurement->savingFilesNames.replace(j, NewFileName + "_" + QString::number(PolarimetrySpectrometer->getIntegrationTime()) + "ms_"
                                                           + QString::number(PolarimetrySpectrometer->getFrequency()) + "Hz_" + QString::number(j+1));
        }
    }
}

/**
 * @brief Change the frequency during calibration
 */
void PanelPolarimeter::change_Frequency_Pol(void){

    /* Update information bar */
    ui->info->setText("Setting Frequency Modulation...");

    /* Stop running calibration */
    Runner->AcceptParameterChanges();

    /* Open dialog to change the wavelength */
    PanelChangeWaveOrFreq changeDialog(this);

    /* Hide the Frequency spinbox */
    changeDialog.ShowFrequency(true);
    changeDialog.ShowWavelengthsList(false);

    /* Set the change unit */
    changeDialog.setUnits("Hz");

    /* Change the dialog title */
    changeDialog.setWindowTitle("Change the Frequency");

    /* Set the actual frequency */
    changeDialog.setFrequency(PolarimetrySpectrometer->getFrequency());

    /* User pressed 'ok' */
    if (QDialog::Accepted == changeDialog.exec())
    {
        /* Stop the measurement */
        if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){
            /* If so, stop */
            ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

            /* Handle events and update UI */
            Application::processEvents();

            /* Wait 1 ms */
            Timer::msleep(1);
        }

        /* Get new number of averages */
        int Freq = changeDialog.getFrequency();

        /* What's the largest frequency that can be resolved? */
        double Freqresolution = 1000/PolarimetrySpectrometer->getIntegrationTime();

        /* Is the new frequency greater than the maximum resolution? */
        if(Freq > Freqresolution/4){

            /* Show message for the maximum resolution */
            QString messenger = "Your actual settings allow a maximum resolution for W of " + QString::number(Freqresolution/4) + " Hz ";
            showCritical(messenger, "");
            return;
        }

        /* Save changes everywhere */
        FFTL.FrequencyF = Freq;
        ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency = Freq;
        PolarimetrySpectrometer->setFrequency(Freq);

        /* The value was changed*/
        editedConf = true;

    }

    /* Change name of files if there is a configuration loaded */
    change_File_Name();

    /* Current progress bar restart */
    ui->currentProgressBar_Pol->setValue(0);

    /* Update information bar */
    ui->info->setText("Setting Spectrometer... Please Wait");

    /* Update configuration */
    if(ConfigureMeasurement->configured){

        /* Update configuration values and form */
        ConfigureMeasurement->ui->spinBox_BFreq->setValue(PolarimetrySpectrometer->getFrequency());
        ConfigureMeasurement->updateConfigurationValues();
        ConfigureMeasurement->GetConfigurationData();
    }

    /* Restart the calibration */
    Runner->restart_CalibrationPol();

}

/**
 * @brief Change the Nr of Averages during calibration
 */
void PanelPolarimeter::change_Number_Averages_Pol(void){

    /* Update information bar */
    ui->info->setText("Setting Number of Averages...");

    /* Stop Calibration */
    Runner->AcceptParameterChanges();

    /* Open the dialog to change the number of averages */
    PanelChangeAverages changeDialog(this);

    /* Get actual number of averages */
    changeDialog.setValue(PolarimetrySpectrometer->getNumberOfAverages());
    changeDialog.setUpperLimit(floor((1000)/(4*PolarimetrySpectrometer->getIntegrationTime()*PolarimetrySpectrometer->getFrequency())));

    /* User pressed 'ok' */
    if (QDialog::Accepted == changeDialog.exec())
    {
        /* Stop the measurement */
        if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){

            /* If so, then stop */
            ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

            /* Handle events and update UI */
            Application::processEvents();

            /* Wait 1 ms */
            Timer::msleep(1);
        }

        /* Get new number of averages */
        int numberOfAverages = changeDialog.getValue();

        /* Set panel item and device number of averages */
        PolarimetrySpectrometer->setNumberOfAverages(numberOfAverages);
        ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(numberOfAverages);

        /* Save changes on the number of averages */
        ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrAverages = numberOfAverages;
        FFTL.NrAverages = numberOfAverages;

        /* The value was changed*/
        editedConf = true;

        /* Ajust X axis of time plotting */
        adjust_Average_Plot_Time();
    }

    /* Restart Y axis plot */
    Runner->maxRawCounts= -1;

    /* Current progress bar restart */
    ui->currentProgressBar_Pol->setValue(0);

    /* Update information bar */
    ui->info->setText("Setting Spectrometer... Please Wait");

    /* Update configuration */
    if(ConfigureMeasurement->configured){

        /* Update configuration values and form */
        ConfigureMeasurement->ui->spinBox_BNAve->setValue(PolarimetrySpectrometer->getNumberOfAverages());
        ConfigureMeasurement->updateConfigurationValues();
        ConfigureMeasurement->GetConfigurationData();
    }

    /* Restart the calibration */
    Runner->restart_CalibrationPol();
}

/**
 * @brief Change the number of spectra during calibration
 */
void PanelPolarimeter::change_Number_Spectra_Pol(void){

    /* Update information bar */
    ui->info->setText("Setting Number of Spectra...");

    /* Stop Calibration */
    Runner->AcceptParameterChanges();

    int NumberSpectraStep = ConfigureMeasurement->NrSpectraSteps(PolarimetrySpectrometer->getIntegrationTime()*PolarimetrySpectrometer->getFrequency());

    /* Open the dialog to change the number of averages */
    PanelChangeAverages changeDialog(this);

    /* Get actual number of averages */
    changeDialog.setValue(PolarimetrySpectrometer->getNumberOfSpectra());

    /* Select the correct number of spectra according to the frequency resolution */
    changeDialog.setIntervals(NumberSpectraStep);
    changeDialog.setLowerLimit(NumberSpectraStep);

    /* Change the dialog title */
    changeDialog.setWindowTitle("Change Number of Spectra");

    /* User pressed 'ok' */
    if (QDialog::Accepted == changeDialog.exec())
    {
        /* Stop the measurement */
        if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){

            /* If so, then stop */
            ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

            /* Handle events and update UI */
            Application::processEvents();

            /* Wait 1 ms */
            Timer::msleep(1);
        }

        /* Get new number of averages */
        int NSpectra = changeDialog.getValue();

        /* Is the input of the user valid? */
        if(NSpectra % NumberSpectraStep !=0){

            /* Use old value */
            NSpectra = PolarimetrySpectrometer->getNumberOfSpectra();
        }

        /* Set panel item and device number of spectra */
        PolarimetrySpectrometer->setNumberOfSpectra(NSpectra);
        FFTL.NrSpectra = NSpectra;
        ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra = NSpectra;

        /* The value was changed*/
        editedConf = true;

        /* Ajust X axis of time plotting */
        adjust_Average_Plot_Time();
    }

    /* Restart Y axis plot */
    Runner->maxRawCounts= -1;

    /* Current progress bar restart */
    ui->currentProgressBar_Pol->setValue(0);

    /* Update information bar */
    ui->info->setText("Setting Spectrometer... Please Wait");

    /* Update configuration */
    if(ConfigureMeasurement->configured){

        /* Update configuration values and form */
        ConfigureMeasurement->ui->spinBox_BNSpec->setValue(PolarimetrySpectrometer->getNumberOfSpectra());
        ConfigureMeasurement->updateConfigurationValues();
        ConfigureMeasurement->GetConfigurationData();

    }

    /* Restart the calibration */
    Runner->restart_CalibrationPol();
}

/**
 * @brief Change the wavelength to show in the FFT plot
 */
void PanelPolarimeter::change_Wavelength_FFT_Pol(void){

    /* Update the information bar */
    ui->info->setText("Setting FFT Wavelength...");

    /* Open dialog to change the wavelength */
    PanelChangeWaveOrFreq changeDialog(this);

    /* Hide the Frequency spinbox */
    changeDialog.ShowFrequency(false);
    changeDialog.ShowWavelengthsList(true);

    /* Set the change unit */
    changeDialog.setUnits("nm");

    /* Change the dialog title */
    changeDialog.setWindowTitle("Change Wavelength to Plot FFT");

    /* Is there loaded information to be shown already? */
    if(PolPlotter->FFT_DC != nullptr){

        /* Go through all the wavelengths */
        for (int i =0; i<FFTL.wavelengths.length();i++){
            changeDialog.setValue(FFTL.wavelengths.at(i));
        }

    }else{

        /* If there no information to show, add just to zero the list */
        changeDialog.setValue(0);
    }

    /* If there is information to show, then ask for the wavelength to show the FFT */
    if (QDialog::Accepted == changeDialog.exec() && PolPlotter->FFT_DC != nullptr)
    {
        /* Get the needed information at the frequencies DC, W and 2W */
        if(!FFTL.wavelengths.isEmpty()){

            /* Get the user selected wavelength */
            FFTL.SelectedWaveL = changeDialog.getValue();

            /* Don't allow to find automatically the wavelength since the user changed it */
            FFTL.changeFFTwavelength = false;

            /* Full of zeros those other frequencies of non interest */
            for ( int  i = 0; i < FFTL.NrSpectra/2; i++ )
            {
                /* Add zeros */
                FFTL.fft_data.append(0);
            }

            /* Add the frequency amplitudes of interest */
            FFTL.fft_data.replace(0, FFTL.fft_DC.at(FFTL.SelectedWaveL));
            FFTL.fft_data.replace(FFTL.f_w, FFTL.fft_W.at(FFTL.SelectedWaveL));
            FFTL.fft_data.replace(2*FFTL.f_w, FFTL.fft_2W.at(FFTL.SelectedWaveL));

            /* Show the selected wavelength of FFT */
            ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths.at(FFTL.SelectedWaveL)));

            /* Plot the FFT Signals */
            PolPlotter->plotFFTatSelectedWave(FFTL.fft_data, FFTL.time);
            ui->waveToPlotFFT->setStyleSheet("QLabel { color: blue; }");

            /* Change the axis according to the new data */
            ui->qwtPlot_Pol_FFT->setXAxis(0.0,  3*FFTL.FrequencyF);
            ui->qwtPlot_Pol_FFT->setAxisScale(ui->qwtPlot_Pol_FFT->xBottom,0, 3*FFTL.FrequencyF, FFTL.FrequencyF);
            int maximum = *std::max_element(FFTL.fft_data.begin(), FFTL.fft_data.end());
            ui->qwtPlot_Pol_FFT->setYAxis(0.0,maximum);
            ui->qwtPlot_Pol_FFT->setAxisScale(ui->qwtPlot_Pol_FFT->yLeft, 0, maximum, maximum/3);
            ui->qwtPlot_Pol_FFT->updateAxes();

            /* Plot the Selected Wavelength */
            PolPlotter->FFT_oneWave->attach(ui->qwtPlot_Pol_FFT);

            /* Update Plots */
            ui->qwtPlot_Pol_FFT->update();
            ui->qwtPlot_Pol_FFT->updateLayout();
        }
    }

    /* Update the information bar */
    ui->info->setText("");
}

/**
 * @brief Clean all the configuration, plots, everyhting restarted.
 */
void PanelPolarimeter::clean_All_Pol(void){

    /* Local */
    Timeindex = 0;

    /* Data loaded */
    UserLoadDataPath = "";

    /* Show starting plots */
    showAllPlots();

    /* Restart total measurement time */
    totalMeasuretime = 0;

    /* Is there any information ploted already? */
    if(PolPlotter->Average_DC_Signal!=nullptr)
    {
        curve_Pol->detach();
    }

    /* To run clear_Plot function */
    dataloaded = true;

    /* Clear all other plots too */
    PolPlotter->clean_AllPlots();

    /* Clean the configuration */
    ConfigureMeasurement->cleanAll();

    /* Clear FFT plots */
    clear_Plot();

    /* Remove some items from the GUI loaded when needed */
    showUI_Item(false);

    /* Don't show total measurement bar */
    ui->TotalProgressBar_Pol->setVisible(false);
    ui->label_totalM->setVisible(false);
    ui->label_remaining->setVisible(false);
    ui->horizontalSpacer_Y->changeSize(20,12,QSizePolicy::Expanding,QSizePolicy::Fixed);
    ui->label_RemainingTime->setVisible(false);

    /* Show current progress bar*/
    ui->currentProgressBar_Pol->setVisible(false);
    ui->Button_Save_Graphs_Pol->setVisible(false);

    /* Restart FFT intensities plot */
    ui->qwtPlot_Pol_FFT->setAxisScale(QwtPlot::xBottom, 0, 21, 7);
    ui->qwtPlot_Pol_FFT->setAxisScale(QwtPlot::yLeft, 0, 3000, 1000);
    ui->qwtPlot_Pol_FFT->updateAxes();

    /* Clear the configuration files profile table */
    for(int z =0; z<ConfigureMeasurement->savingFilesNames.length(); z++){

        /* Remove rows in measurement profile table */
        ui->Table_Measurements_Pol->removeRow(0);
    }

    /* Set all vectors to zero */
    FFTL.InitializeFFTArrays();

    /* Restart the flag to select automatically the wavelength for the FFT plot */
    FFTL.changeFFTwavelength = true;

    /* Restart FFT parameters */
    FFTL.MaximumIntensity = 0;
    FFTL.NrSpectra = 1000;
    FFTL.NrAverages = 1;
    FFTL.IntTime = 8;
    FFTL.FrequencyF = 7;
    FFTL.f_w = FFTL.FrequencyF;
    FFTL.SelectedWaveL = -1;
    FFTL.ConcentrationC1 = FFTL.SelectedWaveL;
    FFTL.ConcentrationC2 = FFTL.SelectedWaveL;
    FFTL.ConcentrationC3 = FFTL.SelectedWaveL;
    FFTL.ConcentrationC4 = FFTL.SelectedWaveL;
    FFTL.ConcentrationC5 = FFTL.SelectedWaveL;
    FFTL.ConcentrationC6 = FFTL.SelectedWaveL;

    /* Also restart plotting variables */
    minXAverage = 0;
    maxXAverage = PolPlotter->time_plot;
    maxYRaw = 0;
    maxYAverage = 0;
    ui->qwtPlot_Pol_Average->setXAxis(minXAverage, maxXAverage);
    ui->qwtPlot_Pol_Average->setXAxisTop(-0.8 , 20.3, 2);

    /* Nothing is running */
    Runner = new Pol_Measurements();

    /* There is no data loaded anymore or any FFT data in UI */
    dataloaded = false;
    isFFTData = true;

    /* Update plots */
    ui->qwtPlot_Pol_Average->update();
    ui->qwtPlot_Pol_Average->updateLayout();
    ui->qwtPlot_Pol->update();

    /* Time busy with FFT */
    ui->currentProgressBar_Pol->setValue(0);

    /* Are there any spectrometers connected? */
    if (m_NrDevices > 0)
    {
        /* Find minimum and maximum wavelengths in array */
        PolarimetrySpectrometer->setWavelengthRange(ptrSpectrometers[SpectrometerNumber]->getStartWavelength(),  ptrSpectrometers[SpectrometerNumber]->getStopWavelength());

        /* Set limits for the wavelengths range */
        ConfigureMeasurement->ui->doubleSpinBox_minW->setMinimum(PolarimetrySpectrometer->getMinimumWavelength());
        ConfigureMeasurement->ui->doubleSpinBox_maxW->setMaximum(PolarimetrySpectrometer->getMaximumWavelength());

        /* Which wavelentgth would you like to see the FFT? */
        signalMapper->setMapping(ui->waveToPlotFFT, ui->waveToPlotFFT);

        /* Disable edition of Spectrometer Data until there is a calibration running */
        PolarimetrySpectrometer->enableComponents(false);

    }

    /* Update x-axis of graphs depending on Wavelengths */
    update_Wavelength_Range();

    /* Restart configurations */
    ConfigureMeasurement = new configurePolMeasure();

    /* Restart plots */
    PolPlotter = new Pol_Plot();

    /* Update information bar */
    ui->info->setText("");
}

/**
 * @brief Remove all plots of the Interface before to load any other plots.
 */
void PanelPolarimeter::clear_Plot(void) {

    /* Was there data loaded? */
    if(dataloaded){
        /* Detach FFT plots */
        PolPlotter->FFT_DC->detach();
        PolPlotter->FFT_W->detach();
        PolPlotter->FFT_2W->detach();
        PolPlotter->FFT_oneWave->detach();
        PolPlotter->Compensation_Signal->detach();
        PolPlotter->predictionSignal->detach();
    }

    /* Update plots */
    ui->qwtPlot_Pol_w_2w->update();
    ui->qwtPlot_Pol_Compensation->update();
    ui->qwtPlot_Pol_FFT->update();
    ui->qwtPlot_Pol_FFT->updateLayout();
    ui->waveToPlotFFT->setText("");

}

/**
 * @brief Configuration of Measurments
 */
void PanelPolarimeter::conf_Setup_Pol_Measurement(void) {

    /* Update information bar */
    ui->info->setText("Creating a configuration...");

    /* Initialize Configuration */
    ConfigureMeasurement->InitializeForm(PolarimetrySpectrometer);

    /* Run the configuration Window */
    ConfigureMeasurement->exec();

    /* Was there a configuration loaded? */
    if(ConfigureMeasurement->configured && !ConfigureMeasurement->Conf_canceled){

        /* Is there any information ploted already? */
        if(PolPlotter->Compensation_Signal!=nullptr)
        {
            /* Detach live curves */
            PolPlotter->Compensation_Signal->detach();
            PolPlotter-> FFT_oneWave->detach();
            PolPlotter->FFT_DC->detach();
            PolPlotter->FFT_W->detach();
            PolPlotter->FFT_2W->detach();
            PolPlotter->predictionSignal->detach();
        }

        /* Set the configured values */
        setConfiguration();

        /* Set some values in the configuration form */
        ConfigureMeasurement->ui->doubleSpinBox_intTime->setValue(PolarimetrySpectrometer->getIntegrationTime());
        ConfigureMeasurement->ui->spinBox_BNAve->setValue(PolarimetrySpectrometer->getNumberOfAverages());
        ConfigureMeasurement->ui->spinBox_BFreq->setValue(PolarimetrySpectrometer->getFrequency());
        ConfigureMeasurement->ui->spinBox_BNSpec->setValue(PolarimetrySpectrometer->getNumberOfSpectra());
        ConfigureMeasurement->ui->doubleSpinBox_minW->setValue(PolarimetrySpectrometer->getMinimumWavelength());
        ConfigureMeasurement->ui->doubleSpinBox_maxW->setValue(PolarimetrySpectrometer->getMaximumWavelength());

        /* Keep loaded and saved values despite canceled changes: alloes edition of previously loaded configuration */
        if(ConfigureMeasurement->configured){

            /* Update values in the configuration form */
            ConfigureMeasurement->updateForm();
        }

    }else{

        /* Update information bar */
        ui->info->setText("");
    }
}

/**
 * @brief Start the routine to delay the measurements
 */
void PanelPolarimeter::delay_Pol_Measurements(void){

    /* Start the Waiting dialog of 5 seconds to press the buttons in the syringe pumps software */
    WaitingDialog dialog(this);

    /* Run Waiting dialog */
    dialog.run();

    /* If canceled stop the measurement */
    if(dialog.cancelCountDown){

        /* Measurement canceled */
        Runner->Stopped = true;

        /* Abort running polarimetry */
        stop_Run_Polarimetry();

    }

    /* Is there a delay time on the measurement? */
    if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->startDelay != 0 && !dialog.cancelCountDown){

        /* Get the actual time and add the delay time */
        ConfigureMeasurement->startTime = QDateTime::currentDateTime().addSecs(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->startDelay);

        /* Tell the user that there is a delay in the start */
        ui->info->setText("Start " + ConfigureMeasurement->startTime.toString("dddd, d MMMM yy, hh:mm:ss ap"));

        /* Count the seconds */
        int timer = 0;

        /* Create the strings to save the remaining time */
        QStringList ConvertedTime1;

        /* Start a timer */
        Runner->timerMS.start();

        /* Run until the time is complete or the user cancel the measurement */
        while(timer < ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->startDelay && Runner->PolMeasuring && !abort_everything){

            /* Count seconds */
            if(Runner->timerMS.elapsed()/1000 > timer){

                /* Time in seconds */
                timer = timer + 1;

                /* Show remaining time */
                ConvertedTime1 = ConfigureMeasurement->externSoftware->TimeConverter(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->startDelay - timer);

                /* Is the remaining time in hours? */
                if(ConvertedTime1.at(1)!= "days"){
                    ui->label_RemainingTime->setText(QDateTime::fromTime_t(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->startDelay
                                                                           - timer).toUTC().toString("hh:mm:ss")+ " " + ConvertedTime1.at(1));
                }else{

                    /* If it's days, then get the number of days */
                    int nDays = (ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->startDelay - timer)/86400;
                    double remaining = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->startDelay -(nDays*86400)-timer;
                    if(remaining < 0){
                        remaining = 0;
                    }

                    /* Present the time including the days */
                    ui->label_RemainingTime->setText(QString::number(nDays) + ":" + QDateTime::fromTime_t(remaining).toUTC().toString("hh:mm:ss") + " " + ConvertedTime1.at(1));
                }

                ui->label_RemainingTime->setVisible(true);

                /* Show remaining time in loading bar */
                ui->currentProgressBar_Pol->setValue(100 - ((ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->startDelay - timer)*100)/
                                                     ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->startDelay);
            }

            /* Don't lock the user interface */
            Application::processEvents();
        }

        /* Restart progress bar */
        ui->currentProgressBar_Pol->setValue(0);
    }
}

/**
 * @brief Enable Help: Slot for comunication with helpDialog
 */
void PanelPolarimeter::enable_Help_Pol(void){

    /* Enable push button of Non Modal window */
    ui->help->setEnabled(true);

    /* Free memory */
    delete helpDialog;
    helpDialog = nullptr;
}

/**
 * @brief Enable polarimeter: If there is a selected spectrometer, then it´s added to the list of Polarimeter Tab.
 * @param[in] If TRUE then the labels and buttons are activated, if FALSE then they are disabled.
 */
void PanelPolarimeter::enable_Polarimeter_Measurement(bool activate)
{
    /* This function is connected to the class Panel */
    ui->button_Start_Meas_Pol->setEnabled(activate);

    /* Enable measurements and get the information of the current selected spectrometer */
    ui->button_Start_Meas_Pol->setStyleSheet(activate ? greenButton : grayButton);
    ui->button_calibrate->setEnabled(activate);
    ui->button_calibrate->setStyleSheet(activate ? "black" : grayButton);
    ui->button_Pol_ConfigureMeasurement->setEnabled(activate);

    /* Update information bar */
    if(!activate){

        /* Update information bar */
        ui->info->setText("Busy with Preview...");
    }else{

        /* Update information bar */
        ui->info->setText("");
    }

}

/**
 * @brief Called if a widget on a spectrometer item in list got clicked during the Calibration,
 *        e.g. Integration time label.
 * @param widget Widget which has been clicked
 */
void PanelPolarimeter::handle_Click_Event(QWidget *widget)
{
    /* Cast the events */
    QLabel *label = qobject_cast<QLabel *>(widget);
    QLineEdit *LineLabel = qobject_cast<QLineEdit *>(widget);
    QCheckBox *Checkbox = qobject_cast<QCheckBox *>(widget);

    /* The integration time label has been clicked during the Calibration */
    if (label == PolarimetrySpectrometer->ui->label_integrationTime && Runner->PolCalibrating && !Runner->doingLiveFFT)
    {
        /* Change integration time during the Calibration */
        change_Integration_Time_Pol();
    }
    /* The auto-adjust label has been clicked during the Calibration */
    else if (label == PolarimetrySpectrometer->ui->label_autoAdjust && Runner->PolCalibrating && !Runner->doingLiveFFT)
    {
        /* Apply changes from the autoadjusted integration time during the Calibration */
        change_Auto_Integration_Time_Pol();
    }
    /* The number of averages label has been clicked during the Calibration */
    else if (label == PolarimetrySpectrometer->ui->label_numberOfAverages && !Runner->doingLiveFFT && Runner->PolCalibrating)
    {
        /* Change number of averages during the Calibration */
        change_Number_Averages_Pol();
    }
    /* The wavelength to show the FFT label has been clicked */
    else if (label == PolarimetrySpectrometer->ui->label_setWranges && !Runner->doingLiveFFT && Runner->PolCalibrating)
    {
        /* Adjust wavelength range */
        adjust_Wavelength_Range();
    }
    /* The number of spectra label has been clicked */
    else if (label == PolarimetrySpectrometer->ui->label_Nspectra && !Runner->doingLiveFFT && Runner->PolCalibrating)
    {
        /* Change the number of spectra */
        change_Number_Spectra_Pol();
    }
    /* The frequency label has been clicked */
    else if (label == PolarimetrySpectrometer->ui->label_frequency && !Runner->doingLiveFFT && Runner->PolCalibrating)
    {
        /* Change frequency during the calibration */
        change_Frequency_Pol();
    }

    /* The change the wavelength in the plot was clicked */
    if(label == ui->waveToPlotFFT){
        /* Change the Wavelength to plot */
        change_Wavelength_FFT_Pol();
    }
    /* The label of clear all was clicked */
    else if(label == ui->label_clearAll){

        /* Update information bar */
        ui->info->setText("Restart all?...");

        /* Do you want to clean all? */
        if (QMessageBox::Yes == QMessageBox::question(this, "Clean All", "Are you sure that you want to clean all? \n \n This option will remove all "
                                                      "loaded settings and plotted data.",
                                                      QMessageBox::Yes | QMessageBox::No))
        {
            /* Button 'yes' pressed; Clean all */
            clean_All_Pol();
        }

        /* Update information bar */
        ui->info->setText("");

    }
    /* The label to show/Hide the plots have been clicked */
    else if(label == ui->label_hideLiveRaw){

        /* Is the raw data plot visible? */
        if(ui->qwtPlot_Pol->isVisible()){

            /* Hide raw data plot if clicked */
            ui->label_hideLiveRaw->setToolTip("Show Raw Signal Plot");
            ui->label_hideLiveRaw->setText(">> Show Live Raw Signal");
            ui->label_hideLiveRaw->setFrameShape(QFrame::Box);
            ui->label_hideLiveRaw->setStyleSheet("QLabel { color: red; }");
            ui->line_rawratio->setVisible(false);

        }else{

            /* Show raw data plot again */
            ui->label_hideLiveRaw->setToolTip("Hide Raw Signal Plot");
            ui->label_hideLiveRaw->setText("<< Hide Live Raw Signal");
            ui->label_hideLiveRaw->setStyleSheet("QLabel { color: blue; }");
            ui->label_hideLiveRaw->setFrameShape(QFrame::NoFrame);
            ui->line_rawratio->setVisible(ui->qwtPlot_Pol_Compensation->isVisible());
        }

        /* Show or Hide labels */
        ui->label_raw->setVisible(!ui->qwtPlot_Pol->isVisible());
        ui->label_RS->setVisible(!ui->qwtPlot_Pol->isVisible());

        /*  Show or Hide plot */
        ui->qwtPlot_Pol->setVisible(!ui->qwtPlot_Pol->isVisible());

    }
    /* Show/Hide Compensation Plot */
    else if(label == ui->label_HideRatio){

        /* Is the Compensation plot visible? */
        if(ui->qwtPlot_Pol_Compensation->isVisible()){

            /* Hide Compensation Plot if clicked */
            ui->label_HideRatio->setToolTip("Show Compensation Plot");
            ui->label_HideRatio->setText("<< Show Ratio I(ω)/I(2ω)");
            ui->label_HideRatio->setFrameShape(QFrame::Box);
            ui->label_HideRatio->setStyleSheet("QLabel { color: red; }");
            ui->line_rawratio->setVisible(false);

        }else{

            /* Show Compensation Plot again */
            ui->label_HideRatio->setToolTip("Hide Compensation Plot");
            ui->label_HideRatio->setText(">> Hide Ratio I(ω)/I(2ω)");
            ui->label_HideRatio->setFrameShape(QFrame::NoFrame);
            ui->label_HideRatio->setStyleSheet("QLabel { color: blue; }");
            ui->line_rawratio->setVisible(ui->qwtPlot_Pol->isVisible());
        }

        /* Show or Hide labels */
        ui->label_compensation->setVisible(!ui->qwtPlot_Pol_Compensation->isVisible());
        ui->label_Rat->setVisible(!ui->qwtPlot_Pol_Compensation->isVisible());

        /* Show or Hide plot */
        ui->qwtPlot_Pol_Compensation->setVisible(!ui->qwtPlot_Pol_Compensation->isVisible());
    }
    /* Show/Hide FFT profile Plot */
    else if(label == ui->label_HideFFTProfile){

        /* Is the FFT profile plot visible? */
        if(ui->qwtPlot_Pol_w_2w->isVisible()){

            /* Hide FFT profile plot if clicked */
            ui->label_HideFFTProfile->setToolTip("Show FFT Profile Plot");
            ui->label_HideFFTProfile->setText(">> Show FFT Profile");
            ui->label_HideFFTProfile->setFrameShape(QFrame::Box);
            ui->label_HideFFTProfile->setStyleSheet("QLabel { color: red; }");
            ui->line_FFT->setVisible(false);

        }else{

            /* Show FFT profile plot again */
            ui->label_HideFFTProfile->setToolTip("Hide FFT Profile Plot");
            ui->label_HideFFTProfile->setText("<< Hide FFT Profile");
            ui->label_HideFFTProfile->setFrameShape(QFrame::NoFrame);
            ui->label_HideFFTProfile->setStyleSheet("QLabel { color: blue; }");
            ui->line_FFT->setVisible(ui->qwtPlot_Pol_Average->isVisible());
        }

        /* Show or Hide labels */
        ui->label_fftprofile->setVisible(!ui->qwtPlot_Pol_w_2w->isVisible());
        ui->label_HProf->setVisible(!ui->qwtPlot_Pol_w_2w->isVisible());

        /* Show or Hide Plot */
        ui->qwtPlot_Pol_w_2w->setVisible(!ui->qwtPlot_Pol_w_2w->isVisible());

    }
    /* Show/Hide Average Plot */
    else if(label == ui->label_HIdeLiveAverage){

        /* Is the Average plot visible? */
        if(ui->qwtPlot_Pol_Average->isVisible()){

            /* Hide Average plot if clicked */
            ui->label_HIdeLiveAverage->setToolTip("Show Average Signal Plot");
            ui->label_HIdeLiveAverage->setText("<< Show Live Average");
            ui->label_HIdeLiveAverage->setFrameShape(QFrame::Box);
            ui->label_HIdeLiveAverage->setStyleSheet("QLabel { color: red; }");
            ui->line_FFT->setVisible(false);

        }else{

            /* Show  Average plot again */
            ui->label_HIdeLiveAverage->setToolTip("Hide Average Signal Plot");
            ui->label_HIdeLiveAverage->setText(">> Hide Live Average");
            ui->label_HIdeLiveAverage->setFrameShape(QFrame::NoFrame);
            ui->label_HIdeLiveAverage->setStyleSheet("QLabel { color: blue; }");
            ui->line_FFT->setVisible(ui->qwtPlot_Pol_w_2w->isVisible());
        }

        /* Show or hide labels */
        ui->label_average->setVisible(!ui->qwtPlot_Pol_Average->isVisible());
        ui->label_HAver->setVisible(!ui->qwtPlot_Pol_Average->isVisible());

        /* Show or Hide plot */
        ui->qwtPlot_Pol_Average->setVisible(!ui->qwtPlot_Pol_Average->isVisible());

    }
    /* Show/Hide the FFT Plot */
    else if(label == ui->FFT_label_Pol){

        /* Is the FFT Plot visible? */
        if(ui->qwtPlot_Pol_FFT->isVisible()){

            /* Hide FFT Plot if clicked */
            ui->FFT_label_Pol->setText("> Maximum DC Intensity at");
            ui->FFT_label_Pol->setToolTip("Show FFT Plot");
        }else{

            /* Show FFT Plot again */
            ui->FFT_label_Pol->setText("< Maximum DC Intensity at");
            ui->FFT_label_Pol->setToolTip("Hide FFT Plot");
        }

        /* Hide or Show plot */
        ui->qwtPlot_Pol_FFT->setVisible(!ui->qwtPlot_Pol_FFT->isVisible());

    }
    /* Show/Hide the Measurement profile Table */
    else if(label == ui->label_Measurements_Pol){

        /* Is the the Measurement profile Table visible? */
        if(ui->Table_Measurements_Pol->isVisible()){

            /* Hide the Measurement profile Table if clicked */
            ui->label_Measurements_Pol->setText("> Measurement List");
            ui->label_Measurements_Pol->setToolTip("Show Measurement Profile");
        }else{

            /* Show the Measurement profile Table again */
            ui->label_Measurements_Pol->setText("< Measurement List");
            ui->label_Measurements_Pol->setToolTip("Hide Measurement Profile");
        }

        /* Hide or Show plot */
        ui->Table_Measurements_Pol->setVisible(!ui->Table_Measurements_Pol->isVisible());
        ui->label_S1->setVisible(!ui->label_S1->isVisible());
        ui->label_S2->setVisible(!ui->label_S2->isVisible());
        ui->label_S3->setVisible(!ui->label_S3->isVisible());
        ui->label_S4->setVisible(!ui->label_S4->isVisible());
        ui->label_S5->setVisible(!ui->label_S5->isVisible());
        ui->label_S6->setVisible(!ui->label_S6->isVisible());
    }
    /* Show/Hide the lateral panel */
    else if(label == ui->label_hideConf){

        /* Hide or Show the lateral panel items if clicked */
        ui->label_Set_Spec_Pol->setVisible(!ui->list_devices_Pol->isVisible());
        ui->FFT_label_Pol->setVisible(!ui->list_devices_Pol->isVisible());
        ui->waveToPlotFFT->setVisible(!ui->list_devices_Pol->isVisible());
        ui->qwtPlot_Pol_FFT->setVisible(!ui->list_devices_Pol->isVisible());
        ui->line_c1->setVisible(!ui->list_devices_Pol->isVisible());
        ui->line_c2->setVisible(!ui->list_devices_Pol->isVisible());
        ui->line_m->setVisible(!ui->list_devices_Pol->isVisible());
        ui->label_n->setVisible(!ui->list_devices_Pol->isVisible());
        ui->label_5_Pol_settings->setVisible(!ui->list_devices_Pol->isVisible());
        ui->button_calibrate->setVisible(!ui->list_devices_Pol->isVisible());
        ui->button_Pol_ConfigureMeasurement->setVisible(!ui->list_devices_Pol->isVisible());
        ui->button_Start_Meas_Pol->setVisible(!ui->list_devices_Pol->isVisible());

        /* Hide or Show thus GUI elements if they are already visible */
        if(Runner->PolConfigured){
            ui->Table_Measurements_Pol->setVisible(!ui->list_devices_Pol->isVisible());
            ui->label_Measurements_Pol->setVisible(!ui->list_devices_Pol->isVisible());
            ui->label_S1->setVisible(!ui->list_devices_Pol->isVisible() && ui->label_S1->text()!="");
            ui->label_S2->setVisible(!ui->list_devices_Pol->isVisible() && ui->label_S2->text()!="");
            ui->label_S3->setVisible(!ui->list_devices_Pol->isVisible() && ui->label_S3->text()!="");
            ui->label_S4->setVisible(!ui->list_devices_Pol->isVisible() && ui->label_S4->text()!="");
            ui->label_S5->setVisible(!ui->list_devices_Pol->isVisible() && ui->label_S5->text()!="");
            ui->label_S6->setVisible(!ui->list_devices_Pol->isVisible() && ui->label_S6->text()!="");
        }

        /* Is the lateral panel visible? */
        if(ui->list_devices_Pol->isVisible()){

            /* Change label to show lateral panel */
            ui->label_hideConf->setText("Show Panel >>");
            ui->label_hideConf->setFrameShape(QFrame::Box);
            ui->label_hideConf->setMinimumWidth(80);
            ui->label_hideConf->setStyleSheet("QLabel { color: red; }");
            ui->label_hideConf->setToolTip("Show Lateral Panel");
            ui->HSpaceX->changeSize(20,5,QSizePolicy::Fixed,QSizePolicy::Fixed);

        }else{

            /* Now the user can hide the lateral panel */
            ui->label_hideConf->setText("<< Hide Panel");
            ui->label_hideConf->setMinimumWidth(300);
            ui->label_hideConf->setStyleSheet("QLabel { color: blue; }");
            ui->label_hideConf->setFrameShape(QFrame::NoFrame);
            ui->label_hideConf->setToolTip("Hide Lateral Panel");
            ui->HSpaceX->changeSize(60,5,QSizePolicy::Fixed,QSizePolicy::Fixed);
        }

        /* Show or Hide list */
        ui->list_devices_Pol->setVisible(!ui->list_devices_Pol->isVisible());

    }

    /* Hide Horizontal lines */
    ui->line_HLiveRatio->setVisible(!(!ui->qwtPlot_Pol->isVisible() && !ui->qwtPlot_Pol_Compensation->isVisible()));

    /* Hide line */
    ui->line_HFFTAverage->setVisible(!(!ui->qwtPlot_Pol_w_2w->isVisible() && !ui->qwtPlot_Pol_Average->isVisible()));

    /* Change the Spectrometer name */
    if(LineLabel == PolarimetrySpectrometer->ui->lineEdit_name){

        /* Get current readable name */
        QString readableName = PolarimetrySpectrometer->ui->lineEdit_name->text();

        /* Check length of readable name */
        if (!readableName.isEmpty())
        {
            /* If it's not empty, set text as new readable name */
            ptrSpectrometers[SpectrometerNumber]->setReadableName(readableName);
        }
    }

    /* This is another condition to change the spacing so it looks nice */
    if((ui->Table_Measurements_Pol->isVisible() && ui->qwtPlot_Pol_FFT->isVisible())
            && Runner->PolConfigured){
        ui->verticalSpacerX->changeSize(20,13,QSizePolicy::Fixed,QSizePolicy::Fixed);
    }else{

        /* In case some elements from the lateral panel are hidden or shown again, change the spacing so they look good */
        ui->verticalSpacerX->changeSize(20,13,QSizePolicy::Fixed,QSizePolicy::Expanding);
    }

    /* Catch check box event */
    if(Checkbox == PolarimetrySpectrometer->ui->checkBox_normalize && !Runner->doingLiveFFT && Runner->PolCalibrating){

        /* Set the normalize counts */
        ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->normalizedCounts = PolarimetrySpectrometer->ui->checkBox_normalize->isChecked();

        /* Normalize Counts */
        normalizeCounts();
    }

    /* Emit signal to update changes in preview tab */
    updateTabs();
}

/**
 * @brief Normalize the counts
 */
void PanelPolarimeter::normalizeCounts(void){

    /* Normalize counts? */
    FFTL.normalizeCounts = PolarimetrySpectrometer->ui->checkBox_normalize->isChecked();

    /* Change plots axes */
    if(FFTL.normalizeCounts){

        /* Change Y axis title */
        ui->qwtPlot_Pol_Average->setYAxisTitle("Average FFT Intensity (Counts / Second)");
        ui->qwtPlot_Pol_w_2w->setYAxisTitle("FFT Intensity (Counts / Second)");
    }
    else{

        /* Set back Y axes title */
        ui->qwtPlot_Pol_Average->setYAxisTitle("Average FFT Intensity (Counts)");
        ui->qwtPlot_Pol_w_2w->setYAxisTitle("FFT Intensity (Counts)");
    }

    /* The value was changed*/
    editedConf = true;
}

/**
 * @brief Open help dialog
 */
void PanelPolarimeter::help_Pol(void){

    /* Disable push button of Non Modal window */
    ui->help->setEnabled(false);

    /* Open help dialog */
    helpDialog = new PanelPolHelp(this);

    /* Execute dialog */
    helpDialog->show();

    /* Was the windows closed already? */
    connect(helpDialog,SIGNAL(accepted()),this,SLOT(enable_Help_Pol()));
}

/**
 * @brief Initialize the calibration
 */
void PanelPolarimeter::initialize_Calibration(void){

    /* Now the calibration is running, remember that! */
    Runner->setCalibrationRunning(true);

    /* Update information bar */
    ui->info->setText("Initializing Spectrometer... Please Wait");

    /* Enable edition of Spectrometer Data until there is no calibration running */
    PolarimetrySpectrometer->enableComponents(true);

    /* Update Polarimeter Calibration buttons */
    ui->button_calibrate->setText("Stop Calibration");
    ui->button_calibrate->setStyleSheet(RedButton);
    ui->button_calibrate->setToolTip("Stop Calibration");
    ui->button_calibrate->setEnabled(true);
    ui->button_Start_Meas_Pol->setStyleSheet(grayButton);

    /* Adjust top axis of averages */
    ui->qwtPlot_Pol_Average->setXAxisTop(-0.8 , 20.3, 2);

    /* Ajust X axis of time plotting */
    adjust_Average_Plot_Time();
}

/**
 * @brief Initialize the calibration with default values
 */
void PanelPolarimeter::initialize_Default_Calibration(void){

    /* If there is a value in the spectrometer, then adjust the frequency according to the resolution */
    double Freqresolution = 1000/ptrSpectrometers[SpectrometerNumber]->getIntegrationTime();

    /* Are the actual settings giving a frequency resolution lower than 1 Hz? */
    if(Freqresolution/4 < 1){

        /* Use 1 Hz as the minimum frequency to resolve */
        ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency = 1;
        PolarimetrySpectrometer->setFrequency(1);
        FFTL.FrequencyF = 1;

        /* To resolve 1 Hz it only makes sense to use a maximum of 250 ms */
        PolarimetrySpectrometer->setIntegrationTime(250);
        ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(250);
        ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime = 250;
        FFTL.IntTime = 250;

        /* Show message for the frequency resolution */
        showWarning("With your actual settings the resolution of integration time is maximum 250 ms with 1 Hz for W ", "");

    }else{

        /* Is the actual frequncy resolution lower than the default 4 Hz resolution? */
        if(Freqresolution/4 < 4){

            /* Set the frequency */
            ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency = Freqresolution/4;
            PolarimetrySpectrometer->setFrequency(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency);
        }else{

            /* If  Hz is ok according to the actual settings, then use this value */
            ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency = PolarimetrySpectrometer->getFrequency();
        }
    }

    /* Set all the variables to a defined value since there isn't configuration loaded */
    ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra = PolarimetrySpectrometer->getNumberOfSpectra();
    ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime = ptrSpectrometers[SpectrometerNumber]->getIntegrationTime();
    ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrAverages = ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages();

    /* For the class FFT, we also need this information to be updated from here (saves time) */
    FFTL.NrSpectra = PolarimetrySpectrometer->getNumberOfSpectra();
    FFTL.IntTime = PolarimetrySpectrometer->getIntegrationTime();
    FFTL.NrAverages = PolarimetrySpectrometer->getNumberOfSpectra();
    FFTL.FrequencyF = PolarimetrySpectrometer->getFrequency();
    FFTL.f_w = PolarimetrySpectrometer->getFrequency();
    FFTL.ConcentrationC1 = 0;
    FFTL.ConcentrationC2 = 0;
    FFTL.ConcentrationC3 = 0;
    FFTL.ConcentrationC4 = 0;
    FFTL.ConcentrationC5 = 0;
    FFTL.ConcentrationC6 = 0;
}

/**
 * @brief Load Summary of the measurement, Polarimeter Setup
 */
void PanelPolarimeter::Load_Summary(void) {

    /* Update information bar */
    ui->info->setText("Loading Measurement Summary...");

    /* Load Data Path */
    QString DataPath = QFileDialog::getOpenFileName(this, QString("Open Measurement Summary"), ".", QString("*.sum"));

    /* File selected by user? */
    if (NULL == DataPath)
    {
        /* No file selected. Dialog aborted. */
        ui->info->setText("");
        return;
    }

    /* Restart vectors */
    PolPlotter->averaged_Signal_time.resize(0);
    PolPlotter->AverageDC.resize(0);
    PolPlotter->AverageW.resize(0);
    PolPlotter->Average2W.resize(0);

    /* Enroute File */
    QFile file(DataPath);

    /* Does the File exists? */
    if(!file.exists()){
        /* If not, tell the user that it coulnd't be found */
        showWarning("File not Found!", "");
        return;
    }

    /* Create the readed row */
    QString Row;

    /* Number of rows */
    int NrMeas = -1;
    double value = -1;

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

                /* Get actual readed value */
                if(value != Readed_Row.at(1).toDouble()){
                    /* Count measurement numbers */
                    NrMeas = NrMeas + 1;
                }

                /* Save the time */
                PolPlotter->averaged_Signal_time.append(Readed_Row.at(0).toDouble());

                /* Save the DC - Position 1 */
                PolPlotter->AverageDC.append(Readed_Row.at(1).toDouble());

                /* Save W - Position 2 */
                PolPlotter->AverageW.append(Readed_Row.at(2).toDouble());

                /* Save 2W - Position 3 */
                PolPlotter->Average2W.append(Readed_Row.at(3).toDouble());

                /* Get the actual value */
                value = Readed_Row.at(1).toDouble();
            }
        }
    }

    /* Close file */
    file.close();

    /* Add signals to the plots */
    PolPlotter->Average_DC_Signal->setSamples(PolPlotter->averaged_Signal_time, PolPlotter->AverageDC);
    PolPlotter->Average_DC_Signal->setTitle(" Ī(DC)");
    PolPlotter->Average_W_Signal->setSamples(PolPlotter->averaged_Signal_time, PolPlotter->AverageW);
    PolPlotter->Average_W_Signal->setTitle(" Ī(ω)");
    PolPlotter->Average_2W_Signal->setSamples(PolPlotter->averaged_Signal_time, PolPlotter->Average2W);
    PolPlotter->Average_2W_Signal->setTitle(" Ī(2ω)");

    /* Attach graphs */
    PolPlotter->Average_DC_Signal->attach(ui->qwtPlot_Pol_Average);
    PolPlotter->Average_W_Signal->attach(ui->qwtPlot_Pol_Average);
    PolPlotter->Average_2W_Signal->attach(ui->qwtPlot_Pol_Average);

    /* Just add a certain time to the plot */
    int maximal = *std::max_element(PolPlotter->averaged_Signal_time.begin(), PolPlotter->averaged_Signal_time.end());
    ui->qwtPlot_Pol_Average->setXAxis(0.0, maximal + maximal*0.1);

    /* Adjust the measurement number plot in the averages */
    double lengthMeasNumber = NrMeas + NrMeas*0.1;

    /* Adjust the approximated measurement number in the x-top axis of the average */
    if(lengthMeasNumber < 25){

        /* If there are too many number, then just plot every two */
        ui->qwtPlot_Pol_Average->setXAxisTop(-0.5, lengthMeasNumber+0.5, 1);

    }else if(lengthMeasNumber > 500){

        /* If less points, then show all the measurement numbers */
        ui->qwtPlot_Pol_Average->setXAxisTop(-0.5, lengthMeasNumber+0.5, int(ceil(lengthMeasNumber/10)));

    }else{

        /* If there are too many number, then just plot every two */
        ui->qwtPlot_Pol_Average->setXAxisTop(-0.5, lengthMeasNumber+0.5, int(ceil(lengthMeasNumber/30)));
    }

    /* Update plots */
    ui->qwtPlot_Pol_Average->update();

    /* Resize vectors */
    PolPlotter->averaged_Signal_time.resize(0);
    PolPlotter->AverageDC.resize(0);
    PolPlotter->AverageW.resize(0);
    PolPlotter->Average2W.resize(0);

    /* Update information bar */
    ui->info->setText("");
}

/**
 * @brief Load Data from the FFT, Polarimeter Setup
 */
void PanelPolarimeter::Load_From_FFT(void) {

    /* Update information bar */
    ui->info->setText("Loading FFT Data...");

    /* What kind of data are we loading? In this case FFT */
    isFFTData = true;

    /* Load Data Path */
    UserLoadDataPath = QFileDialog::getOpenFileName(this, QString("Open FFT Data file"), ".", QString("*.FFT"));

    /* File selected by user? */
    if (NULL == UserLoadDataPath)
    {
        /* No file selected. Dialog aborted. */
        ui->info->setText("");
        return;
    }else{

        /* Where is the file to be loaded located? */
        fileInfoLoad = UserLoadDataPath;
    }

    /* Show the analyzed data from FFT */
    FFTL.getFFTfromFFTData(fileInfoLoad);

    /* Clean the plots for a new plotting */
    clear_Plot();

    /* Plot the FFT Signals */
    plot_FFT();

    /* Remember that there was data loaded */
    dataloaded = true;

    /* By default show the wavelength 516,41 nm */
    ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths.at(FFTL.SelectedWaveL)));

    /* Update information bar */
    ui->info->setText("");
}

/**
 * @brief Load Data and Perform FFT from Raw Data, Polarimeter Setup
 */
void PanelPolarimeter::Load_From_Raw_Data(void) {

    /* Update information bar */
    ui->info->setText("Loading Raw Data...");

    /* What type of file are we loading? Not FFT here */
    isFFTData = false;

    /* Load Data Path */
    UserLoadDataPath = QFileDialog::getOpenFileName(this, QString("Open Raw Data file"), ".", QString("*.CS;*.TXT"));

    /* File selected by user? */
    if (NULL == UserLoadDataPath)
    {
        /* Update information bar */
        ui->info->setText("");

        /* No file selected. Dialog aborted. */
        return;
    }else{

        /* Where is the loaded file located? */
        fileInfoLoad = UserLoadDataPath;
    }

    /* Data Analysis by FFT */
    if(m_NrDevices > 0){

        /* Connected devices? Use it's wavelength range */
        FFTL.getFFTfromRawData(fileInfoLoad, false, PolarimetrySpectrometer->getMinimumWavelength(), PolarimetrySpectrometer->getMaximumWavelength());
    }else{
        /* If not, then use a default range */
        FFTL.getFFTfromRawData(fileInfoLoad, false, 200, 1100);
    }

    /* Clear all the plots for a new load of data */
    clear_Plot();

    /* Plot the FFT Signals */
    plot_FFT();

    /* Remember that there was data loaded */
    dataloaded = true;

    /* By default show the wavelength 516,41 nm */
    ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths.at(FFTL.SelectedWaveL)));

    /* Update information bar */
    ui->info->setText("");
}

/**
 * @brief Calibration Routine
 */
void PanelPolarimeter::pol_Calibrate(void){

    /* How long takes the data acquisition? */
    int measuringTime = (ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime
                         *ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra
                         *ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrAverages/1000);

    /* What's the minimum time available for the spectrometer to measure and plot the data? plus a window for live raw data */
    int minimumLiveTime = measuringTime + measuringTime/3 + 12;

    /* Always plot at 10 measurement values */
    PolPlotter->time_plot = minimumLiveTime*20;

    /* Change from ms on timer to just seconds of running the calibration */
    if(Runner->timerMS.elapsed()/1000 > Runner->Timer_In_Seconds){

        /* Time in seconds */
        Runner->Timer_In_Seconds = Runner->Timer_In_Seconds + 1;

        /* Plot the Live averages */
        plot_Average();

        /* Count the time steps for measuring during the Live FFT calibration */
        Runner->liveFFT_Time = Runner->liveFFT_Time + 1;

        /* Progress of calibration */
        Runner->Calibration_Progress = Runner->Calibration_Progress + 1;
        ui->currentProgressBar_Pol->setValue(Runner->Calibration_Progress*100/(minimumLiveTime));

        /* Time break to do live Raw data plot */
        if (Runner->liveFFT_Time == minimumLiveTime-8 && !ptrSpectrometers[SpectrometerNumber]->isMeasuring()){

            /* Prepare for new measurement */
            if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
            {
                Runner->maxRawCounts =-1;
                /* If successful, start measurement */
                ptrSpectrometers[SpectrometerNumber]->startMeasurement(-2);

                /* Update information bar */
                ui->info->setText("Live Raw Signal...");
            }
        }

        /* Is time to run the Live measurements for the calibration? */
        if (Runner->liveFFT_Time == minimumLiveTime-2 && Runner->liveFFT_Time!=0 && ptrSpectrometers[SpectrometerNumber]->isMeasuring())
        {

            /* Stop the raw data plotting */
            ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

            /* Handle events and update UI */
            Application::processEvents();

            /* Wait 1 ms */
            Timer::msleep(1);

            /* Update information bar */
            ui->info->setText("Preparing Spectrometer... Please Wait");
        }
    }

    /* Path to be in the search for the files; is always a subdirectory in the application path */
    QString path(QString("%1%2").arg(currentWorkingPath, "data_polarimeter/"));

    /* Info of the calibration file */
    fileInfoCalibration = QFileInfo(path);

    /* The temporal file to save the raw data of calibration */
    path.append(Runner->TempFileName);

    /* Is time to run the Live FFT measurements for the calibration? */
    if ((Runner->liveFFT_Time== minimumLiveTime && Runner->liveFFT_Time!=0 && !ptrSpectrometers[SpectrometerNumber]->isMeasuring()))
    {
        /* Check if spectrometer is still measuring */
        if (ptrSpectrometers[SpectrometerNumber]->isMeasuring())
        {
            /* Show message */
            showWarning("Spectrometer is still measuring! Too small time steps?", "");
        }
        else
        {
            /* Set all the variables from class FFT here, to save time */
            FFTL.NrSpectra = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra;
            FFTL.FrequencyF = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency;
            FFTL.IntTime = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime;
            FFTL.NrAverages = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrAverages;
            FFTL.ConcentrationC1 = 0;
            FFTL.ConcentrationC2 = 0;
            FFTL.ConcentrationC3 = 0;
            FFTL.ConcentrationC4 = 0;
            FFTL.ConcentrationC5 = 0;
            FFTL.ConcentrationC6 = 0;

            /* Configure spectrometer */
            ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(ptrSpectrometers[SpectrometerNumber]->getIntegrationTime());
            ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages());

            /* If the system is busy and the user stops the calibration, Wait until it finishes what it's doing and then stop. */
            if(Runner->delayStop){
                return;
            }

            /* Prepare StoreToRAM measurement */
            ptrSpectrometers[SpectrometerNumber]->forceStoreToRAM(path, ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra);
            if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
            {
                /* Start the calibration similar as measuring for long time */
                ptrSpectrometers[SpectrometerNumber]->startMeasurement(2);

                /* Update information bar */
                ui->info->setText("Getting the Spectra...");
            }
        }

        /* Reset the time for next Live FFT Measurement */
        Runner->liveFFT_Time = 0;
    }
}

/**
 * @brief Plot W, DC and 2W averaged
 */
void PanelPolarimeter::plot_Average(void){

    /* Plot Averages */
    PolPlotter->plotAverages(dataloaded, FFTL.fft_DC, FFTL.fft_W, FFTL.fft_2W, FFTL.wavelengths, Runner->PolMeasuring, Runner->measurementPlotTimeInterval);

    /* Attach graphs */
    PolPlotter->Average_DC_Signal->attach(ui->qwtPlot_Pol_Average);
    PolPlotter->Average_W_Signal->attach(ui->qwtPlot_Pol_Average);
    PolPlotter->Average_2W_Signal->attach(ui->qwtPlot_Pol_Average);

    /* Is there a new maximum value for the Y axis to resize it? Usually DC is the largest of all three */
    if(maxYAverage < ceil((PolPlotter->maxYValue)*1.1)){

        /* Save the actual maximum value of Y plot of averages */
        maxYAverage = ceil((PolPlotter->maxYValue)*1.1);
        ui->qwtPlot_Pol_Average->setYAxis(0.0, maxYAverage);
        ui->qwtPlot_Pol_Average->setXAxis(minXAverage, maxXAverage);
    }

    /* Update plots */
    ui->qwtPlot_Pol_Average->update();

    /* If we have more than certain amount of values in the plot, change the X axis */
    if(PolPlotter->averaged_Signal_time.length() > PolPlotter->time_plot){

        /* Change axis according to the running type 0: Calibrating */
        if(Runner->PolCalibrating){

            /* Set limits for x axis of averages */
            minXAverage = PolPlotter->maxXtime;
            maxXAverage = PolPlotter->maxXtime + PolPlotter->time_plot;

            /* Just add a certain time to the plot */
            ui->qwtPlot_Pol_Average->setXAxis(minXAverage, maxXAverage);

            /* Get the actual maximum average value */
            PolPlotter->maxYValue = PolPlotter->AverageDC.at(PolPlotter->AverageDC.length()-1);

            /* Save the actual maximum value of Y plot of averages */
            maxYAverage = ceil((PolPlotter->maxYValue)*1.1);
            ui->qwtPlot_Pol_Average->setYAxis(0.0, maxYAverage);
        }

        /* Restart all vector to don't overload them with too many information */
        PolPlotter->averaged_Signal_time.resize(0);
        PolPlotter->AverageDC.resize(0);
        PolPlotter->AverageW.resize(0);
        PolPlotter->Average2W.resize(0);
    }
}

/**
 * @brief Run Measurements
 */
void PanelPolarimeter::pol_Measure(void){

    /* Plot the averages on real time during the Measurement */
    if(Runner->timerMS.elapsed()/1000 > Runner->Timer_In_Seconds){

        /* Time in seconds */
        Runner->Timer_In_Seconds = Runner->Timer_In_Seconds + 1;

        /* Show remaining time */
        totalMeasuretime = totalMeasuretime -1;

        /* Change time to the proper units */
        QStringList ConvertedTime = ConfigureMeasurement->externSoftware->TimeConverter(totalMeasuretime);
        if(ConvertedTime.at(1)!= "days"){
            ui->label_RemainingTime->setText(QDateTime::fromTime_t(totalMeasuretime).toUTC().toString("hh:mm:ss") + " " + ConvertedTime.at(1));
        }else{
            int nDays = ConvertedTime.at(0).toDouble();
            ui->label_RemainingTime->setText(QString::number(nDays) + ":" + QDateTime::fromTime_t(totalMeasuretime-(nDays*86400)).toUTC().toString("hh:mm:ss")
                                             + " " + ConvertedTime.at(1));
        }

        /* Plot 300 points for all the measurements */
        if(Runner->Timer_In_Seconds % Runner->measurementPlotTimeInterval == 0){

            /* Plot the live average values of intensities */
            plot_Average();
        }
    }

    /* During the Measurements if the spectrometer isn't measuring then it's Waiting for the pumps */
    if(!ptrSpectrometers[SpectrometerNumber]->isMeasuring()){

        /* Update information bar */
        ui->info->setText("Waiting for Flushing...");
    }

    /* Re asign the folder path to save the measurement files */
    QString path2(ConfigureMeasurement->pathDataMeasurements.absoluteDir().path() + "/" + folderForData + "/");
    fileInfoSaving = QFileInfo(path2);

    /* Create the path for StoreToRam */
    QString path(fileInfoSaving.absoluteDir().path() + "/");

    /* Check if we have more entries to do */
    if (Timeindex < (unsigned int)ConfigureMeasurement->timePoint.length())
    {
        /* Next Measurement starts now? */
        if (Runner->timerMS.elapsed() >= ConfigureMeasurement->timePoint[Timeindex])
        {
            /* Save the raw data as .CS file */
            path.append(ConfigureMeasurement->savingFilesNames[Timeindex] + ".CS");

            /* Check if spectrometer is still measuring */
            if (ptrSpectrometers[SpectrometerNumber]->isMeasuring())
            {
                ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

                /* Handle events and update UI */
                Application::processEvents();

                /* Wait 1 ms */
                Timer::msleep(1);
            }

            /* Configure spectrometer */
            ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime);
            ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrAverages);

            /* Prepare StoreToRAM measurement */
            ptrSpectrometers[SpectrometerNumber]->forceStoreToRAM(path, ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra);
            if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
            {
                /* Update information bar */
                ui->info->setText("Saving/Plotting Data...");

                /* Start the Measurement */
                ptrSpectrometers[SpectrometerNumber]->startMeasurement(2);
            }

            /* Select the row that belongs to the measurement */
            ui->Table_Measurements_Pol->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->Table_Measurements_Pol->selectRow(Timeindex);
            ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::NoSelection);
            ui->Table_Measurements_Pol->cellWidget(Timeindex, 0)->setStyleSheet("qproperty-alignment: AlignCenter;" "background-color: rgb(0, 153, 255)");

            /* Go to next entry */
            Timeindex++;

            /* The spectrometer is busy with the Measurements */
            Runner->showRaw = false;
        }

        /* is the spectrometer free? */
        if(!ptrSpectrometers[SpectrometerNumber]->isMeasuring()){

            /* When no raw signal anymore, then do the Measurement */
            if(!Runner->showRaw){
                if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
                {
                    /* Show the raw data */
                    ptrSpectrometers[SpectrometerNumber]->startMeasurement(-2);

                    /* Update information bar */
                    ui->info->setText("Adjusting Sample...");
                }

                /* The raw data can be displayed now */
                Runner->showRaw = true;
            }
        }
    }

    /* Show the progress of the Measurements */
    pol_Measurement_Progress(Timeindex);
}

/**
 * @brief Measurement progress routine
 * @param[in] The variable i is the entry number of the current time interval.
 */
void PanelPolarimeter::pol_Measurement_Progress(unsigned int i){

    /* Progress of the measurements */
    int progress = 0;

    /* Calculate progress for first entry? */
    if (i == 0)
    {
        progress = 100 - (ConfigureMeasurement->timePoint[0] - Runner->timerMS.elapsed()) / ConfigureMeasurement->timePoint[0] * 100;
    }
    /* Calculate progress for last entry? */
    else if (i >= (unsigned int)ConfigureMeasurement->timePoint.length())
    {
        /* Abort while loop if no measurement is running anymore */
        Runner->setMeasurementRunning(ptrSpectrometers[SpectrometerNumber]->isMeasuring());

        /* Progress done */
        progress = 100;
    }
    /* Calculate progress for any other entry? */
    else
    {
        /* Current progress is calculated by the difference between actual time and next measurement */
        progress = 100 - (ConfigureMeasurement->timePoint[i] - Runner->timerMS.elapsed()) / (ConfigureMeasurement->timePoint[i] - ConfigureMeasurement->timePoint[i-1]) * 100;
    }

    /* Update progress bars */
    ui->currentProgressBar_Pol->setValue(progress);
    ui->TotalProgressBar_Pol->setValue((i) * 100 / ConfigureMeasurement->timePoint.count());
}

/**
 * @brief Plot FFT.
 */
void PanelPolarimeter::plot_FFT(void){

    /* Plot FFT function on object Pol Plot */
    PolPlotter->Plot_FFT_Graphs(FFTL.wavelengths, FFTL.time, FFTL.fft_data, FFTL.fft_DC, FFTL.fft_W, FFTL.fft_2W, FFTL.fft_Compensation_Signal);

    /* Set editable the FFT wavelength label */
    ui->waveToPlotFFT->setStyleSheet("QLabel { color: blue; }");

    /* Change the axis according to the new data */
    ui->qwtPlot_Pol_FFT->setXAxis(0.0,  3*FFTL.FrequencyF);
    ui->qwtPlot_Pol_FFT->setAxisScale(ui->qwtPlot_Pol_FFT->xBottom,0, 3*FFTL.FrequencyF, FFTL.FrequencyF);
    int maximum = *std::max_element(FFTL.fft_data.begin(), FFTL.fft_data.end());
    ui->qwtPlot_Pol_FFT->setYAxis(0.0,maximum);
    ui->qwtPlot_Pol_FFT->setAxisScale(QwtPlot::yLeft, 0, maximum, maximum/3);
    ui->qwtPlot_Pol_FFT->updateAxes();

    /* Plot Selected Wavelength */
    PolPlotter->FFT_oneWave->attach(ui->qwtPlot_Pol_FFT);

    /* Set plotting axis */
    ui->qwtPlot_Pol_w_2w->setYAxis(0.0, ceil(*std::max_element(FFTL.fft_DC.begin(), FFTL.fft_DC.end())*1.1));

    /* Assign the values to the plots */
    PolPlotter->FFT_DC->attach(ui->qwtPlot_Pol_w_2w);
    PolPlotter->FFT_W->attach(ui->qwtPlot_Pol_w_2w);
    PolPlotter->FFT_2W->attach(ui->qwtPlot_Pol_w_2w);

    /* Set axis */
    ui->qwtPlot_Pol_Compensation->setYAxis(0.0, ceil(*std::max_element(FFTL.fft_Compensation_Signal.begin(), FFTL.fft_Compensation_Signal.end())*1));

    /* Assign values to plot */
    PolPlotter->Compensation_Signal->attach(ui->qwtPlot_Pol_Compensation);

    /* Update the Plots and Labels */
    ui->qwtPlot_Pol_w_2w->update();
    ui->qwtPlot_Pol_Compensation->update();
    ui->qwtPlot_Pol_Compensation->updateLayout();
    ui->qwtPlot_Pol_w_2w->updateLayout();
    ui->qwtPlot_Pol_FFT->update();
    ui->qwtPlot_Pol_FFT->updateLayout();
}

/**
 * @brief Process the received data from the spectrometer
 * @param[in] The path where the data will be saved.
 */
void PanelPolarimeter::process_Received_Data_Pol(QString Path)
{
    /* Save if the system is busy doing the live FFT analisys */
    Runner->doingLiveFFT = true;

    /* Do the FFT to the received data */
    isFFTData = false;

    /* Is the FFT for Measurement or Calibration purposes? */
    if(!Runner->PolCalibrating){

        /* Path for Measurements */
        fileInfoSaving = QFileInfo(Path);

    }else{

        /* Use the temporal file if Calibrating */
        fileInfoCalibration = QFileInfo(fileInfoCalibration.absoluteDir().path() + "/" + Runner->TempFileName);
    }

    /* The user decided to stop the calibration while the system was busy then skip the data analysis */
    if(!Runner->delayStop){

        /* If calibrating, use the path for the temporal file */
        if(Runner->PolCalibrating){
            /* Data Analysis by FFT from the just written file */
            FFTL.getFFTfromRawData(fileInfoCalibration, true, PolarimetrySpectrometer->getMinimumWavelength(), PolarimetrySpectrometer->getMaximumWavelength());
        }

        /* If measuring, use the path given by the user */
        if(Runner->PolMeasuring){
            /* Data Analysis by FFT from the just written file */
            FFTL.getFFTfromRawData(fileInfoSaving, false, PolarimetrySpectrometer->getMinimumWavelength(), PolarimetrySpectrometer->getMaximumWavelength());
        }

        /* Update information bar */
        ui->info->setText("Preparing Spectrometer... Please Wait");

        /* Clear all the plots for a new loaded data */
        clear_Plot();

        /* Plot the FFT Signals */
        plot_FFT();
        ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths.at(FFTL.SelectedWaveL)));

        /* Don't combine loaded data with calibrated data regarding the averages */
        dataloaded = false;
    }

    /* Restart the flags */
    Runner->delayStop = false;

    /* Is there an automatic saving of FFT Data selected by the user? */
    if(ConfigureMeasurement->ui->checkBox_saveFFT->isChecked() && Runner->PolMeasuring && !Runner->PolCalibrating){
        /* Save FFT value to file */
        FFTL.saveFFTtoFile(fileInfoSaving, false, ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->substancesNames);
    }

    /* Is there an automatic saving of Raw Data?, if not just remove the file with the Raw Data */
    if(!ConfigureMeasurement->ui->checkBox_saveRaw->isChecked()&& !Runner->PolCalibrating){
        /* Remove temporal file */
        remove(Path.toLatin1().data());
    }

    /* Spectrometer finished measurement */
    ptrSpectrometers[SpectrometerNumber]->bMeasuring = false;

    /* If the Calibration is running, then restart the progress bar each time it finishes one cycle of Calibration */
    if(Runner->PolCalibrating){

        /* Restart progress */
        Runner->Calibration_Progress = 0;
        ui->currentProgressBar_Pol->setValue(0);
    }
}

/**
 * @brief Closes everything when closing the app
 */
void PanelPolarimeter::quit_Oxymetry(void){

    /* Just close all the running loops if the app was closed unexpected */
    if(m_NrDevices > 0 ){

        /* Abort everything */
        abort_everything = true;
    }
}

/**
 * @brief Data from spectrometer has arrived
 * @param WParam
 * @param LParam
 */
void PanelPolarimeter::receive_Data_Pol(int WParam, int LParam)
{
    /* Successful gained data */
    if (WParam >= ERR_SUCCESS)
    {
        /* Graph needs update? */
        bool needUpdate = false;

        /* Did the current spectrometer for polarimeter sent the data? */
        if ((LParam == ptrSpectrometers[SpectrometerNumber]->getHandle()) && (ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() > 0))
        {
            /* Normal measurement? */
            if (ERR_SUCCESS == WParam)
            {
                /* Handle event */
                ptrSpectrometers[SpectrometerNumber]->handleEvent();

                /* Update saturation status */
                PolarimetrySpectrometer->setIsSaturated(ptrSpectrometers[SpectrometerNumber]->isSaturated());
                ui->label_PlotSaturated->setVisible(ptrSpectrometers[SpectrometerNumber]->isSaturated());

                /* Graph needs update */
                needUpdate = true;
            }
            /* Start Store to RAM measurement */
            else
            {
                /* Get StoreToRAM path */
                QString path = ptrSpectrometers[SpectrometerNumber]->getStoreToRAMPath();

                /* Show error if no path is choosen */
                if (path.isEmpty())
                {
                    /* Show critical error */
                    showCritical(QString("No path for StoreToRAM file specified!"), QString(""));
                    return;
                }

                /* Allocate memory for spectra (number of pixel elements multiplied with the number of measurements) */
                double *a_pSpectrum = new double[ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() * (unsigned int)WParam];

                /* Not able to allocate memory? */
                if (nullptr == a_pSpectrum)
                {
                    /* Show critical error */
                    showCritical(QString("Not enough memory for StoreToRAM data!"), QString(""));
                    return;
                }

                unsigned int j = 1;

                /* Loop through number of measurements */
                for (j = 1; j <= (unsigned int)WParam; j++)
                {
                    /* Avoid this if the user stopped the calibration */
                    if(Runner->delayStop){
                        break;
                    }

                    /* Did the current spectrometer in polarimeter sent the data? */
                    if ((LParam == ptrSpectrometers[SpectrometerNumber]->getHandle()) && (ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() > 0))
                    {
                        /* Handle event */
                        ptrSpectrometers[SpectrometerNumber]->handleEvent();

                        /* Update saturation status */
                        PolarimetrySpectrometer->setIsSaturated(ptrSpectrometers[SpectrometerNumber]->isSaturated());
                        ui->label_PlotSaturated->setVisible(ptrSpectrometers[SpectrometerNumber]->isSaturated());

                        /* Save counts */
                        double *temp = ptrSpectrometers[SpectrometerNumber]->getCounts();

                        unsigned int k = 0;

                        /* Loop through pixel values */
                        for (k = 0; k < ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels(); k++)
                        {
                            *(a_pSpectrum + (ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() * (j - 1)) + k) = *(temp + k);
                        }
                    }
                }

                /* Graph needs update */
                needUpdate = true;

                /* Got all StoreToRAM data, save it to disk now */
                FILE *file = fopen(path.toLatin1().data(), "wt");

                /* Check file handle */
                if (nullptr == file)
                {
                    /* Free memory */
                    delete[] a_pSpectrum;
                    a_pSpectrum = nullptr;

                    /* Show message */
                    showCritical(QString("Unable to create file '%1'.").arg(ptrSpectrometers[SpectrometerNumber]->getStoreToRAMPath()), QString(""));
                    return;
                }

                /* Write header and data to file */
                write_To_File(file, a_pSpectrum, WParam);

                /* Close file */
                fclose(file);
                file = nullptr;

                /* Free memory */
                delete[] a_pSpectrum;
                a_pSpectrum = nullptr;

                /* Process the received data */
                process_Received_Data_Pol(path);
            }

            /* Update curve of raw data */
            curve_Pol->setSamples(ptrSpectrometers[SpectrometerNumber]->getWavelengths(), ptrSpectrometers[SpectrometerNumber]->getCounts(),
                                  ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels());

            /* Is there a maximum amount of counts to change the Y axis on raw data plot? */
            if(Runner->maxRawCounts==-1 || Runner->maxRawCounts < ptrSpectrometers[SpectrometerNumber]->getMaxCounts()){

                /* Maximum counts to plot */
                maxYRaw = ceil(ptrSpectrometers[SpectrometerNumber]->getMaxCounts()+ ptrSpectrometers[SpectrometerNumber]->getMaxCounts()/2);

                /* If so, adjust the Y axis */
                ui->qwtPlot_Pol->setAxisScale(QwtPlot::yLeft, 0.0, maxYRaw);

                /* Save the maximum amount of counts registered */
                Runner->maxRawCounts = ptrSpectrometers[SpectrometerNumber]->getMaxCounts();
            }
        }

        /* Does the graph need an update? */
        if (needUpdate)
        {
            /* Update the graph */
            ui->qwtPlot_Pol->update();
            ui->qwtPlot_Pol_Average->update();
        }
    }

    /* The data is not busy anymore */
    Runner->doingLiveFFT = false;

}

/**
 * @brief Start to run Polarimeter
 * @param[in] Type 1 means Measurements, 0 means Calibration
 */
void PanelPolarimeter::run_Polarimetry(short int runType) {

    /* Adjust buttons, labels, configurations and GUI to start the Measurements or Calibration */
    adjust_Run_Start(runType);

    /* Start Running Polarimetry: Measuring or Calibrating? */
    while (Runner->PolCalibrating || Runner->PolMeasuring)
    {
        /* The software was closed by the user abruptly */
        if(abort_everything){

            /* Stop running Measurements or Calibration */
            stop_Run_Polarimetry();

            /* Break the loop */
            break;
        }

        /* Calibration */
        if(Runner->PolCalibrating){

            /* Restart timer if there is too much time elapsed already during the Calibration */
            if(Runner->Timer_In_Seconds > 1000) {

                /* Restart timers */
                Runner->RestartTimers();
            }

            /* Skip doing calibration routine because a change is in progress during the Calibration */
            if(!Runner->AcceptChanges){

                /* When there is no changes going on, then do the Calibration routine normally */
                pol_Calibrate();
            }
        }

        /* Long Time Measurement */
        if(Runner->PolMeasuring){

            /* Do the Measurement routine */
            pol_Measure();
        }

        /* Handle events and update UI */
        Application::processEvents();

        /* Wait 1 ms */
        Timer::msleep(1);
    }

    /* Adjust the end of the Measurements */
    if(runType == 1){

        /* Plot some values after the measurements */
        adjust_Run_End();
    }

    /* Stop the measurements */
    Runner->setMeasurementRunning(false);

    /* Stop the Calibration */
    Runner->setCalibrationRunning(false);
}

/**
 * @brief Save All graphs from the Polarimeter Setup
 */
void PanelPolarimeter::save_Graph_Pol(void) {

    /* Save the old status of the information bar */
    QString oldstatus = ui->info->text();

    /* Update information bar */
    ui->info->setText("Saving graphs to file...");

    /* Get the folder to save the different PDF files with the plots */
    QString pathPDF =QFileDialog::getSaveFileName(this, tr("Save plots as PDF files"), "Plots", "Text files (*.pdf)");

    /* Get name from user */
    pathPDF = pathPDF.left(pathPDF.lastIndexOf(".pdf"));

    /* Check export path */
    if (!pathPDF.isEmpty())
    {
        QwtPlotRenderer renderer;
        /* Save to disk one PDF for each plot */
        renderer.renderDocument(ui->qwtPlot_Pol_w_2w, pathPDF + "_DC_W_2W.pdf" , "pdf",QSizeF(300, 200));
        renderer.renderDocument(ui->qwtPlot_Pol_Compensation, pathPDF + "_W_Over_2W.pdf" , "pdf",QSizeF(300, 200));
        renderer.renderDocument(ui->qwtPlot_Pol_Average, pathPDF + "_AverageSignal.pdf" , "pdf",QSizeF(300, 200));
        renderer.renderDocument(ui->qwtPlot_Pol, pathPDF + "_RawSignal.pdf" , "pdf",QSizeF(300, 200));

        /* If there was a prediction plot, then include it in the PDF */
        if(ui->qwtPlot_Pol_Prediction->isVisible()){
            renderer.renderDocument(ui->qwtPlot_Pol_Prediction, pathPDF + "_Prediction.pdf" , "pdf",QSizeF(300, 200));
        }
    }

    /* Update information bar to the previous information */
    ui->info->setText(oldstatus);
}

/**
 * @brief Add to the List of Spectrometers in Polarimeter Tab the First Checked Spectrometer of the Preview List.
 * This function is called in Panel.cpp
 */
void PanelPolarimeter::selected_Spectrometer_Pol(void){

    /* Start with no devices connected */
    bool devicesEnabled = false;

    unsigned int i = 0;

    /* Loop through devices */
    for (i = 0; i < m_NrDevices; i++)
    {
        devicesEnabled = devicesEnabled || ptrSpectrometers[i]->isEnabled();
    }

    if(devicesEnabled == false){
        /* Blank the List of spectrometers and ask to choose one from the preview list. */
        PolarimetrySpectrometer->setClickableLabelsEnabled(false);
        PolarimetrySpectrometer->setName("");

    }else{
        /* Loop through devices */
        for (i = 0; i < m_NrDevices; i++)
        {
            if( ptrSpectrometers[i]->isEnabled()){

                /* Enable labels if there is any spectrometer */
                PolarimetrySpectrometer->setIsEnabled(true);
                PolarimetrySpectrometer->setClickableLabelsEnabled(true);
                PolarimetrySpectrometer->setIntegrationTime(ptrSpectrometers[i]->getIntegrationTime());
                PolarimetrySpectrometer->setNumberOfAverages(ptrSpectrometers[i]->getNumberOfAverages());

                /* Save the spectrometer in use if it's not the first*/
                SpectrometerNumber = i;

                /* Get the new spectrometer details */
                if (ptrSpectrometers[i]->hasReadableName())
                {
                    PolarimetrySpectrometer->setName(ptrSpectrometers[i]->getReadableName());
                }else{
                    PolarimetrySpectrometer->setName(ptrSpectrometers[i]->getSerialNumber());
                }
                /* Just use the first spectrometer checked from the list */
                break;
            }
        }
    }

    /* Update buttons, except when the function is called for a different function */
    if(!Runner->PolCalibrating && !Runner->PolMeasuring && !ptrSpectrometers[SpectrometerNumber]->isMeasuring()){
        ui->button_Start_Meas_Pol->setEnabled((devicesEnabled) ? true : false);
        ui->button_Start_Meas_Pol->setStyleSheet((devicesEnabled) ? greenButton : grayButton);
        ui->button_calibrate->setEnabled((devicesEnabled) ? true : false);
        ui->button_calibrate->setStyleSheet((devicesEnabled) ? "black" : grayButton);
        ui->button_Pol_ConfigureMeasurement->setEnabled((devicesEnabled) ? true : false);
    }
}

/**
 * @brief Set all the parameters according to the configured values
 */
void PanelPolarimeter::setConfiguration(void){

    /* Show needed UI items */
    showUI_Item(true);

    /* Save if the Measurement has been configured */
    Runner->setConfigured(true);

    /* Left align column titles */
    ui->Table_Measurements_Pol->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    /* Prevent user from editing the cells */
    ui->Table_Measurements_Pol->setEditTriggers(QAbstractItemView::NoEditTriggers);

    /* Zero row count of measurement list */
    ui->Table_Measurements_Pol->setRowCount(0);

    QStringList substances;

    /* Show or hide the columns of the substances */
    if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(0)){
        ui->Table_Measurements_Pol->hideColumn(2);
    }else{
        ui->Table_Measurements_Pol->showColumn(2);
        substances.append(" C1 - Glucose");
    }
    if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(1)){
        ui->Table_Measurements_Pol->hideColumn(3);
    }else{
        ui->Table_Measurements_Pol->showColumn(3);
        substances.append(" C2 - " + ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->substancesNames.at(0));
    }
    if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(2)){
        ui->Table_Measurements_Pol->hideColumn(4);
    }else{
        ui->Table_Measurements_Pol->showColumn(4);
        substances.append(" C3 - " + ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->substancesNames.at(1));
    }
    if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(3)){
        ui->Table_Measurements_Pol->hideColumn(5);
    }else{
        ui->Table_Measurements_Pol->showColumn(5);
        substances.append(" C4 - " + ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->substancesNames.at(2));
    }
    if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(4)){
        ui->Table_Measurements_Pol->hideColumn(6);
    }else{
        ui->Table_Measurements_Pol->showColumn(6);
        substances.append(" C5 - " + ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->substancesNames.at(3));
    }
    if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(5)){
        ui->Table_Measurements_Pol->hideColumn(7);
    }else{
        ui->Table_Measurements_Pol->showColumn(7);
        substances.append(" C6 - " + ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->substancesNames.at(4));
    }

    /* Add names */
    for(int k=substances.length()-1; k < 6; k++){
        substances.append("");
    }

    /* Set text for substances names */
    ui->label_S1->setText(substances.at(0));
    ui->label_S2->setText(substances.at(1));
    ui->label_S3->setText(substances.at(2));
    ui->label_S4->setText(substances.at(3));
    ui->label_S5->setText(substances.at(4));
    ui->label_S6->setText(substances.at(5));

    ui->label_S1->setVisible(ui->label_S1->text()!="");
    ui->label_S2->setVisible(ui->label_S2->text()!="");
    ui->label_S3->setVisible(ui->label_S3->text()!="");
    ui->label_S4->setVisible(ui->label_S4->text()!="");
    ui->label_S5->setVisible(ui->label_S5->text()!="");
    ui->label_S6->setVisible(ui->label_S6->text()!="");

    /* Set columns size */
    ui->Table_Measurements_Pol->setColumnWidth(2, 70);
    ui->Table_Measurements_Pol->setColumnWidth(3, 70);
    ui->Table_Measurements_Pol->setColumnWidth(4, 70);
    ui->Table_Measurements_Pol->setColumnWidth(5, 70);
    ui->Table_Measurements_Pol->setColumnWidth(6, 70);
    ui->Table_Measurements_Pol->setColumnWidth(7, 70);

    /*  Count rows */
    int rowcounter = 0;
    int repetitions = 1;

    unsigned int i = 0;

    /* Loop through elements */
    for (i = 0; i < (unsigned int) ConfigureMeasurement->timePoint.length(); i++)
    {
        /* At least second entry? */
        if (i > 0)
        {
            /* Calculate duration of entry before current entry */
            double duration =  ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra
                    *  ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime
                    *  ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrAverages;

            /* Check if there's a time overlap between last and current entry */
            if (( ConfigureMeasurement->timePoint[i - 1] + duration) >  ConfigureMeasurement->timePoint[i])
            {
                /* Zero row count */
                ui->Table_Measurements_Pol->setRowCount(0);
                return;
            }
        }

        /* Count measurement number */
        rowcounter = rowcounter + 1;

        /* Set rows */
        ui->Table_Measurements_Pol->setRowCount(i+1);

        /* Create label for measurement number */
        QLabel *ntn = new QLabel();

        /* Are there repetitions? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->repetition > 1){
            ntn->setText("R" + QString::number(repetitions) + " - " + QString::number(ui->Table_Measurements_Pol->rowCount()));

            /* Adjust table widget */
            ui->Table_Measurements_Pol->setColumnWidth(0, 55);
            ui->Table_Measurements_Pol->setColumnWidth(1, 80);

        }else{
            ntn->setText(QString::number(ui->Table_Measurements_Pol->rowCount()));

            /* Adjust table widget */
            ui->Table_Measurements_Pol->setColumnWidth(0, 25);
            ui->Table_Measurements_Pol->setColumnWidth(1, 90);
        }
        ntn->setStyleSheet("QLabel { margin-left: 2px; }");
        ui->Table_Measurements_Pol->setCellWidget(i, 0, ntn);
        ui->Table_Measurements_Pol->cellWidget(i, 0)->setStyleSheet("qproperty-alignment: AlignCenter;" "background-color: rgb(255, 255, 255)");

        /* Create label for time point */
        QLabel *nt2 = new QLabel();

        /* Change time to the proper units */
        QStringList ConvertedTime = ConfigureMeasurement->externSoftware->TimeConverter(ConfigureMeasurement->timePoint.at(i)/1000);

        /* In case of less than 1 day measuring */
        if(ConvertedTime.at(1)=="hours"){
            nt2->setText(QDateTime::fromTime_t(ConfigureMeasurement->timePoint.at(i)/1000).toUTC().toString("hh:mm:ss"));
            ui->Table_Measurements_Pol->horizontalHeaderItem(1)->setText("Time (h:m:s)");
        }
        else if (ConvertedTime.at(1)=="min"){
            nt2->setText(QDateTime::fromTime_t(ConfigureMeasurement->timePoint.at(i)/1000).toUTC().toString("mm:ss"));
            ui->Table_Measurements_Pol->horizontalHeaderItem(1)->setText("Time (m:s)");
        }else if (ConvertedTime.at(1)=="sec"){
            nt2->setText(QDateTime::fromTime_t(ConfigureMeasurement->timePoint.at(i)/1000).toUTC().toString("ss"));
            ui->Table_Measurements_Pol->horizontalHeaderItem(1)->setText("Time (s)");

        }else{
            ui->Table_Measurements_Pol->horizontalHeaderItem(1)->setText("Time (d:h:m:s)");
            int nDays = ConvertedTime.at(0).toDouble();
            nt2->setText(QString::number(nDays) + ":" +QDateTime::fromTime_t((ConfigureMeasurement->timePoint.at(i)/1000)-86400*nDays).toUTC().toString("hh:mm:ss"));
        }

        nt2->setStyleSheet("QLabel { margin-left: 2px; }");
        ui->Table_Measurements_Pol->setCellWidget(i, 1, nt2);

        /* Is C1 active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(0)){

            /* Create label for C1 */
            QLabel *ntC1 = new QLabel();
            if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->intervalMode){
                ntC1->setText(QString::number(ConfigureMeasurement->externSoftware->GlucoseConcentration.at(rowcounter-1)));
            }else{
                ntC1->setText(QString::number(*std::max_element(ConfigureMeasurement->externSoftware->GlucoseConcentration.begin(),
                                                                ConfigureMeasurement->externSoftware->GlucoseConcentration.end())));
            }
            ntC1->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->Table_Measurements_Pol->setCellWidget(i, 2, ntC1);
        }

        /* Is C2 active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(1)){

            /* Create label for C2 */
            QLabel *ntC2 = new QLabel();
            if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->intervalMode){
                ntC2->setText(QString::number(ConfigureMeasurement->externSoftware->Impurity1Concentration.at(rowcounter-1)));
            }else{
                ntC2->setText(QString::number(*std::max_element(ConfigureMeasurement->externSoftware->Impurity1Concentration.begin(),
                                                                ConfigureMeasurement->externSoftware->Impurity1Concentration.end())));
            }
            ntC2->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->Table_Measurements_Pol->setCellWidget(i, 3, ntC2);
        }

        /* Is C3 active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(2)){

            /* Create label for C3 */
            QLabel *ntC3 = new QLabel();
            if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->intervalMode){
                ntC3->setText(QString::number(ConfigureMeasurement->externSoftware->Impurity2Concentration.at(rowcounter-1)));
            }else{
                ntC3->setText(QString::number(*std::max_element(ConfigureMeasurement->externSoftware->Impurity2Concentration.begin(),
                                                                ConfigureMeasurement->externSoftware->Impurity2Concentration.end())));
            }
            ntC3->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->Table_Measurements_Pol->setCellWidget(i, 4, ntC3);
        }

        /* Is C4 active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(3)){

            /* Create label for C4 */
            QLabel *ntC4 = new QLabel();
            if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->intervalMode){
                ntC4->setText(QString::number(ConfigureMeasurement->externSoftware->Impurity3Concentration.at(rowcounter-1)));
            }else{
                ntC4->setText(QString::number(*std::max_element(ConfigureMeasurement->externSoftware->Impurity3Concentration.begin(),
                                                                ConfigureMeasurement->externSoftware->Impurity3Concentration.end())));
            }
            ntC4->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->Table_Measurements_Pol->setCellWidget(i, 5, ntC4);
        }

        /* Is C5 active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(4)){

            /* Create label for C5 */
            QLabel *ntC5 = new QLabel();
            if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->intervalMode){
                ntC5->setText(QString::number(ConfigureMeasurement->externSoftware->Impurity4Concentration.at(rowcounter-1)));
            }else{
                ntC5->setText(QString::number(*std::max_element(ConfigureMeasurement->externSoftware->Impurity4Concentration.begin(),
                                                                ConfigureMeasurement->externSoftware->Impurity4Concentration.end())));
            }
            ntC5->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->Table_Measurements_Pol->setCellWidget(i, 6, ntC5);
        }

        /* Is C6 active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(5)){

            /* Create label for C6 */
            QLabel *ntC6 = new QLabel();
            if(!ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->intervalMode){
                ntC6->setText(QString::number(ConfigureMeasurement->externSoftware->Impurity5Concentration.at(rowcounter-1)));
            }else{
                ntC6->setText(QString::number(*std::max_element(ConfigureMeasurement->externSoftware->Impurity5Concentration.begin(),
                                                                ConfigureMeasurement->externSoftware->Impurity5Concentration.end())));
            }
            ntC6->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->Table_Measurements_Pol->setCellWidget(i, 7, ntC6);
        }

        /* Are there repetitions? */
        if((i+1) % (unsigned int) ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NConcentrations == 0){
            rowcounter = 0;
            repetitions = repetitions + 1;
        }
    }

    /* Label for number of spectra */
    PolarimetrySpectrometer->setNumberOfSpectra(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra);
    FFTL.NrSpectra = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra;

    /* Label for Frequency Measurement */
    PolarimetrySpectrometer->setFrequency(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency);
    FFTL.FrequencyF = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->Frequency;

    /* Change the Spectrometer Integration Time according to the loaded configuration */
    ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime);
    PolarimetrySpectrometer->ui->label_integrationTime->setText(QString::number(ptrSpectrometers[SpectrometerNumber]->getIntegrationTime()));
    FFTL.IntTime = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->IntegrationTime;

    /* Change the Wavelength range according to the loaded configuration */
    PolarimetrySpectrometer->setWavelengthRange(ConfigureMeasurement->externSoftware->minWavelength,
                                                ConfigureMeasurement->externSoftware->maxWavelength);
    /* Update Wavelengths Range */
    update_Wavelength_Range();

    /* Change the Spectrometer Number of Averages according to the loaded configuration */
    ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrAverages);
    PolarimetrySpectrometer->ui->label_numberOfAverages->setText(QString::number(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages()));
    FFTL.NrAverages = ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrAverages;

    /* Set normalized counts */
    PolarimetrySpectrometer->ui->checkBox_normalize->setChecked(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->normalizedCounts);
    normalizeCounts();

    /* Select the first row */
    ui->Table_Measurements_Pol->selectRow(0);

    /* Emit signal to update changes in preview tab */
    updateTabs();

    /* Update information bar */
    ui->info->setText("Configured... Please Load Files to the Pumps Software");
}

/**
 * @brief User interface items
 * @param[in] TRUE means the GUI elements are shown, FALSE the elements are hidden.
 */
void PanelPolarimeter::showUI_Item(bool UIstatus)
{
    /* Update items on UI */
    ui->label_Measurements_Pol->setVisible(UIstatus);
    ui->Table_Measurements_Pol->setVisible(UIstatus);
    ui->label_S1->setVisible(UIstatus);
    ui->label_S2->setVisible(UIstatus);
    ui->label_S3->setVisible(UIstatus);
    ui->label_S4->setVisible(UIstatus);
    ui->label_S5->setVisible(UIstatus);
    ui->label_S6->setVisible(UIstatus);

    /* Make the items to look nicer */
    if(UIstatus){
        ui->verticalSpacerX->changeSize(20,13,QSizePolicy::Fixed,QSizePolicy::Fixed);
    }else{
        ui->verticalSpacerX->changeSize(20,13,QSizePolicy::Fixed,QSizePolicy::Expanding);
    }
}

/**
 * @brief Stop the Calibration of the Spectrometer Settings and the Polarimeter Setup
 */
void PanelPolarimeter::stop_Run_Polarimetry(void) {

    /* Is the spectrometer disabled? */
    PolarimetrySpectrometer->setIsEnabled(true);

    /* Stop Calibrating */
    if(Runner->PolCalibrating){

        /* Set the Calibration button disabled since it was already pressed */
        ui->button_calibrate->setEnabled(false);

        /* Delay the stop of the Calibration */
        Runner->delayStop = true;

        /* Update information bar */
        ui->info->setText("Busy Stopping the Spectrometer... Please Wait");

        /* This temporal file for the calibration has to be removed */
        QFile file(fileInfoCalibration.absoluteFilePath()+"/Pol_tmp.tmp");

        /* Does the calibration temporal File exists? If yes remove it */
        if(file.exists()){

            /* Remove the temporal file */
            file.remove();
        }

        /* Handle events and update UI */
        Application::processEvents();

        /* Disable edition of Spectrometer Data until there is a Calibration running */
        PolarimetrySpectrometer->enableComponents(false);

        /* No polarimetric Calibration running anymore */
        Runner->setCalibrationRunning(false);

        /* Enable Polarimeter Buttons */
        ui->button_Start_Meas_Pol->setEnabled(true);

        /* Update pol meas button */
        ui->button_calibrate->setText("Calibrate");
        ui->button_calibrate->setStyleSheet("black");
        ui->button_calibrate->setToolTip("Stat Calibration");
        ui->button_calibrate->setEnabled(true);
        ui->button_Start_Meas_Pol->setStyleSheet(greenButton);

        /* Update information bar */
        ui->info->setText("");
    }

    /* Stop Long Term Measurement */
    if(Runner->PolMeasuring){

        /* Update information bar */
        ui->info->setText("Stopping the Measurement... Please Wait");

        /* No polarimetric Measurement running anymore */
        Runner->setMeasurementRunning(false);

        /* Handle events and update UI */
        Application::processEvents();

        /* Update Polarimeter Measurement button */
        ui->button_Start_Meas_Pol->setText("Start Measurement");
        ui->button_Start_Meas_Pol->setToolTip("Start Measurement");
        ui->button_Start_Meas_Pol->setStyleSheet(greenButton);
        ui->button_Start_Meas_Pol->setEnabled(true);
        ui->button_calibrate->setEnabled(true);

        /* Look for the directory where the files were going to be saved */
        QDir Direc(fileInfoSaving.absolutePath());

        /* If the directory is empty and exists, then remove it (the user canceled the measurement) */
        if((Direc.exists() && Direc.isEmpty())){
            Direc.removeRecursively();
        }

        /* Update information bar */
        ui->info->setText("Measurement Finished");
    }

    /* Stop the measurement */
    if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){

        /* Stop the spectrometer */
        ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

        /* Handle events and update UI */
        Application::processEvents();

        /* Wait 1 ms */
        Timer::msleep(1);
    }

    /* Enable buttons again */
    ui->button_Pol_ConfigureMeasurement->setEnabled(true);
    ui->button_LoadData->setEnabled(true);
    ui->button_LoadData->setVisible(true);
    ui->button_AnalizeData->setEnabled(true);
    ui->button_AnalizeData->setVisible(true);
    ui->label_clearAll->setEnabled(true);
    ui->label_clearAll->setVisible(true);
    ui->label_clearAll->setStyleSheet("QLabel { color: blue;}");

    /* Emit signal to enable the preview buttons */
    DisEnablePreview(true);
}

/**
 * @brief Toggles Load Data Button
 */
void PanelPolarimeter::toggle_Load_Data(void)
{
    /* Is there something already analyzed by FFT? */
    if(PolPlotter->FFT_DC != nullptr && !FFTL.fft_DC.isEmpty() && isFFTData == false){

        /* File doens't exists. Did we ask the user to save the analyzed data from raw data? */
        if (QMessageBox::Yes == QMessageBox::question(this, "Save FFT File", "Would you like to save the FFT from Raw Data?",
                                                      QMessageBox::Yes | QMessageBox::No))
        {
            /* Save the substances names */
            QStringList substancesNames;

            for(int k = 0; k < 4; k++){
                substancesNames.append("");
            }

            /* Button 'yes' pressed; Save the FFT data where the user decides */
            FFTL.saveFFTtoFile(fileInfoLoad, true, substancesNames);
        }
    }

    /* Update Information bar */
    ui->info->setText("Select the type of File to load...");

    /* Restart maximum Intensity measured */
    FFTL.MaximumIntensity = 0;

    /* Use a dialog to select the kind of data to be loaded */
    QMessageBox msgBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QPushButton *Summary = msgBox.addButton(tr("Measurement Summary"), QMessageBox::ActionRole);
    QPushButton *Raw = msgBox.addButton(tr("Raw Data File"),QMessageBox::ActionRole);
    QPushButton *FFT = msgBox.addButton(tr("FFT Data File"), QMessageBox::ActionRole);

    /* Set tool tips */
    Raw->setToolTip("Load Raw Data");
    Raw->setToolTipDuration(-1);
    FFT->setToolTip("Load FFT Data");
    FFT->setToolTipDuration(-1);
    Summary->setToolTip("Load Measurement Summary");
    Summary->setToolTipDuration(-1);

    /* Adjust the dialog window */
    msgBox.addButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("Loading Data File ...                                                                             ");
    msgBox.setInformativeText("Please select the type of data that you would like to load?");
    msgBox.setWindowTitle("Load Data");

    QGridLayout* layout = (QGridLayout*)msgBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

    /* Run the dialog */
    msgBox.exec();

    /* If user select FFT type data, then run load from FFT function */
    if (msgBox.clickedButton() == FFT) {

        /* If loaded clean all */
        if(m_NrDevices > 0){

            /* Restart all to load the data */
            clean_All_Pol();
        }

        /* Load FFT */
        Load_From_FFT();
    }

    /* If user select raw data, then load it */
    else if (msgBox.clickedButton() == Raw) {

        /* If loaded clean all */
        if(m_NrDevices > 0){

            /* Restart all to load the data */
            clean_All_Pol();
        }

        /* Load and analyze raw data */
        Load_From_Raw_Data();
    }

    /* If user select the measurement summary, then load it */
    else if (msgBox.clickedButton() == Summary) {

        /* If loaded clean all */
        if(m_NrDevices > 0){

            /* Restart all to load the data */
            clean_All_Pol();
        }

        /* Load and analyze raw data */
        Load_Summary();
        ui->Button_Save_Graphs_Pol->setVisible(true);

    }

    /* Which button was pressed? */
    if ((msgBox.clickedButton() == Raw || msgBox.clickedButton() == FFT) && dataloaded) {

        /* Remove some items from the GUI loaded when needed */
        showUI_Item(false);

        /* Don't show total measurement bar and hide some unnecessary plots */
        ui->TotalProgressBar_Pol->setVisible(false);
        ui->label_totalM->setVisible(false);
        ui->label_remaining->setVisible(false);
        ui->horizontalSpacer_Y->changeSize(20,12,QSizePolicy::Expanding,QSizePolicy::Fixed);
        ui->label_RemainingTime->setVisible(false);

        ui->qwtPlot_Pol->setVisible(false);
        ui->label_raw->setVisible(false);
        ui->label_hideLiveRaw->setText(">> Show Live Raw Signal");
        ui->label_hideLiveRaw->setFrameShape(QFrame::Box);
        ui->label_hideLiveRaw->setStyleSheet("QLabel { color: red; }");
        ui->line_rawratio->setVisible(false);

        ui->qwtPlot_Pol_Average->setVisible(false);
        ui->label_average->setVisible(false);
        ui->label_HIdeLiveAverage->setText("<< Show Live Average");
        ui->label_HIdeLiveAverage->setFrameShape(QFrame::Box);
        ui->label_HIdeLiveAverage->setStyleSheet("QLabel { color: red; }");
        ui->line_HLiveRatio->setVisible(false);

        ui->qwtPlot_Pol_Compensation->setVisible(true);
        ui->label_compensation->setVisible(true);
        ui->label_HideRatio->setText(">> Hide Ratio I(ω)/I(2ω)");
        ui->label_HideRatio->setFrameShape(QFrame::NoFrame);
        ui->label_HideRatio->setStyleSheet("QLabel { color: blue; }");

        ui->qwtPlot_Pol_w_2w->setVisible(true);
        ui->label_fftprofile->setVisible(true);
        ui->label_HideFFTProfile->setText("<< Hide FFT Profile");
        ui->label_HideFFTProfile->setFrameShape(QFrame::NoFrame);
        ui->label_HideFFTProfile->setStyleSheet("QLabel { color: blue; }");

        ui->line_HLiveRatio->setVisible(true);
        ui->line_HFFTAverage->setVisible(true);

        /* Show current progress bar*/
        ui->currentProgressBar_Pol->setVisible(false);
        ui->Button_Save_Graphs_Pol->setVisible(true);
    }

    /* Update Information bar */
    ui->info->setText("");

    /* Free allocated memory */
    delete Raw;
    Raw = nullptr;
    delete FFT;
    FFT = nullptr;
    delete Summary;
    Summary = nullptr;
}

/**
 * @brief Toggles Calibration of the Polarimeter
 */
void PanelPolarimeter::toggle_Pol_Calibration(void)
{
    /* Polarimeter Calibration running or not? */
    if(!Runner->PolCalibrating)
    {
        /* Is there any configuration to calibrate? */
        if(!Runner->PolConfigured){

            /* Initialize a defalut calibration */
            initialize_Default_Calibration();
        }

        /* Clear all plots */
        clear_Plot();

        /* Is there any information ploted already? */
        if(PolPlotter->Compensation_Signal!=nullptr)
        {
            /* Detach live curves */
            PolPlotter->Compensation_Signal->detach();
            PolPlotter-> FFT_oneWave->detach();
            PolPlotter->FFT_DC->detach();
            PolPlotter->FFT_W->detach();
            PolPlotter->FFT_2W->detach();
            PolPlotter->predictionSignal->detach();
        }

        /* Hide total measurement bar */
        ui->TotalProgressBar_Pol->setVisible(false);
        ui->label_totalM->setVisible(false);
        ui->label_remaining->setVisible(false);
        ui->horizontalSpacer_Y->changeSize(20,12,QSizePolicy::Expanding,QSizePolicy::Fixed);
        ui->label_RemainingTime->setVisible(false);

        /* Restart flag for edition of configuration during the calibration */
        editedConf = false;

        /* Show starting plots */
        showAllPlots();

        /* Show Button for saving actual spectra */
        ui->button_SaveInstantFFT->setVisible(true);

        /* Run type calibration with 0: Calibrating */
        run_Polarimetry(0);
    }
    else
    {
        /* Polarimeter Calibration running at the moment. Stop it. */
        stop_Run_Polarimetry();

        /* Show current progress bar */
        ui->currentProgressBar_Pol->setVisible(false);

        /* Hide Button for saving actual spectra */
        ui->button_SaveInstantFFT->setVisible(false);

        /* If a configuration was loaded then, get the changes */
        if(Runner->PolConfigured && editedConf){

            /* Do you want to save the changes */
            if (QMessageBox::Yes == QMessageBox::question(this, "Save Changes", "Would you like to save the changes in the loaded configuration file?",
                                                          QMessageBox::Yes | QMessageBox::No)){
                /* Button 'yes' pressed; save */
                ConfigureMeasurement->externSoftware->writeScripts();
            }

            /* Load Configuration */
            ConfigureMeasurement->loadConfiguration();

            /* Reset parameters */
            setConfiguration();
        }
    }
}

/**
 * @brief Toggles Measurements of the Polarimeter
 */
void PanelPolarimeter::toggle_Pol_Measurement(void)
{
    /* Polarimeter Measurement running or not? */
    if(!Runner->PolMeasuring){

        /* Is there a loaded configuration profile? */
        if(Runner->PolConfigured){

            /* Allow to show the initial Raw data plot */
            Runner->showRaw = false;

            /* Clear all plots */
            clear_Plot();

            /* Add expected concentration prediction */
            PolPlotter->predictionSignal->attach(ui->qwtPlot_Pol_Prediction);
            ui->qwtPlot_Pol_Prediction->update();

            /* Show total measurement bars and lines */
            ui->TotalProgressBar_Pol->setVisible(true);
            ui->label_totalM->setVisible(true);

            /* Show starting plots */
            showAllPlots();

            /* Restart the flag of interrupted measurement */
            Runner->Stopped = false;

            /* Run type measurement with 1: Measuring */
            run_Polarimetry(1);

        }else{

            /* Show message if no configuration has been loaded */
            showCritical("Please load a Configuration Profile to Start the Measurement", "");
            return;
        }

    }else{
        /* Polarimeter Measurement running at the moment. Stop it. */
        stop_Run_Polarimetry();

        /* Measurement interrupted */
        Runner->Stopped = true;
    }
}

/**
 * @brief Update user interface
 */
void PanelPolarimeter::update()
{
    /* Is there a new spectrometer selected to be used in Polarimetry? */
    selected_Spectrometer_Pol();

    /* Update parameters changes from other Tabs */
    PolarimetrySpectrometer->setIntegrationTime(ptrSpectrometers[SpectrometerNumber]->getIntegrationTime());
    PolarimetrySpectrometer->setName(ptrSpectrometers[SpectrometerNumber]->getReadableName());

    /* If the number of averages is greater than the maximum for polarimeter then set the maximum possible */
    if(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages() > floor((1000)/(4*PolarimetrySpectrometer->getIntegrationTime()*PolarimetrySpectrometer->getFrequency()))){
        PolarimetrySpectrometer->setNumberOfAverages(floor((1000)/(4*PolarimetrySpectrometer->getIntegrationTime()*PolarimetrySpectrometer->getFrequency())));
    }else{
        PolarimetrySpectrometer->setNumberOfAverages(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages());
    }
}

/**
 * @brief Set the range of wavelengths according to the user
 */
void PanelPolarimeter::update_Wavelength_Range(void){

    /* Update x-axis of graphs depending on Wavelengths */
    ui->qwtPlot_Pol->setXAxis(PolarimetrySpectrometer->getMinimumWavelength(), PolarimetrySpectrometer->getMaximumWavelength());
    ui->qwtPlot_Pol_Compensation->setXAxis(PolarimetrySpectrometer->getMinimumWavelength(), PolarimetrySpectrometer->getMaximumWavelength());
    ui->qwtPlot_Pol_w_2w->setXAxis(PolarimetrySpectrometer->getMinimumWavelength(), PolarimetrySpectrometer->getMaximumWavelength());
}

/**
 * @brief Write the Raw Data to a File
 * @param[in] File where the information will be written.
 * @param[in] The spectra.
 * @param[in] W Parameter
 */
void PanelPolarimeter::write_To_File(FILE *file, double *a_pSpectrum, int WParam) {

    /* Write on file the header if it's not the temporal file used for calibration */
    if(!Runner->PolCalibrating){

        /* Write the Header with name/serial number */
        if (ptrSpectrometers[SpectrometerNumber]->hasReadableName()){
            fprintf(file, "Serial Number: %s \n", ptrSpectrometers[SpectrometerNumber]->getSerialNumber().toLatin1().data());
            fprintf(file, "Spectrometer Name: %s \n", ptrSpectrometers[SpectrometerNumber]->getReadableName().toLatin1().data());
        }else{
            fprintf(file, "Serial Number: %s\n", ptrSpectrometers[SpectrometerNumber]->getSerialNumber().toLatin1().data());
        }

        /* Write some useful data on file */
        fprintf(file, "Integration Time: %.2f ms\n", ptrSpectrometers[SpectrometerNumber]->getIntegrationTime());
        fprintf(file, "Nr. of Spectra: %i\n", ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra);
        fprintf(file, "Nr. of Averages: %i\n", ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages());
        fprintf(file, "Frequency: %.2f Hz\n", FFTL.FrequencyF);

        /* Include the concentrations in the file */
        QString concentrations, conc = "";

        /* Is glucose active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(0)){

            /* Write C1 */
            FFTL.ConcentrationC1 = ConfigureMeasurement->externSoftware->GlucoseConcentration.at(Timeindex-1);
            concentrations.append(QString::number(FFTL.ConcentrationC1));
            conc.append("C1/");
        }

        /* Is Impurity 1 active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(1)){

            /* Write C2 */
            FFTL.ConcentrationC2 = ConfigureMeasurement->externSoftware->Impurity1Concentration.at(Timeindex-1);
            concentrations.append("," + QString::number(FFTL.ConcentrationC2));
            conc.append("C2/");
        }

        /* Is Impurity 2 active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(2)){

            /* Write C3 */
            FFTL.ConcentrationC3 = ConfigureMeasurement->externSoftware->Impurity2Concentration.at(Timeindex-1);
            concentrations.append("," + QString::number(FFTL.ConcentrationC3));
            conc.append("C3/");
        }

        /* Is Impurity 3 active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(3)){

            /* Write C4 */
            FFTL.ConcentrationC4 = ConfigureMeasurement->externSoftware->Impurity3Concentration.at(Timeindex-1);
            concentrations.append("," + QString::number(FFTL.ConcentrationC4));
            conc.append("C4/");
        }

        /* Is Impurity 4 active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(4)){

            /* Write C5 */
            FFTL.ConcentrationC5 = ConfigureMeasurement->externSoftware->Impurity4Concentration.at(Timeindex-1);
            concentrations.append("," + QString::number(FFTL.ConcentrationC5));
            conc.append("C5/");
        }

        /* Is Impurity 5 active? */
        if(ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->activeSubstances.at(5)){

            /* Write C6 */
            FFTL.ConcentrationC6 = ConfigureMeasurement->externSoftware->Impurity5Concentration.at(Timeindex-1);
            concentrations.append("," + QString::number(FFTL.ConcentrationC6));
            conc.append("C6/");
        }

        fprintf(file, "Concentrations: %s: %s\n\n", conc.toLatin1().data() ,concentrations.toLatin1().data());
    }

    /* Save wavelengths */
    double *a_pWavelength = ptrSpectrometers[SpectrometerNumber]->getWavelengths();
    unsigned int j = 1;

    /* Loop through pixel values */
    for (j = 0; j < ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels(); j++)
    {
        unsigned int k = 0;

        /* write counts header, also it's not needed when writing temporal file for calibration */
        if (j == 0 && !Runner->PolCalibrating)
        {
            fprintf(file, "Wavelength\t# 00001");

            /* Write number of spectrum */
            for (k = 2; k <= (unsigned int)WParam; k++)
            {
                fprintf(file, "\t\t# %05u", k);
            }

            fprintf(file, "\n");
        }

        /* Write wavelength and counts */
        fprintf(file, "%.2f", *(a_pWavelength+j));

        /* Write counts */
        for (k = 0; k < (unsigned int)WParam; k++)
        {
            fprintf(file, "\t\t%.2f", *(a_pSpectrum + ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() * k + j));
        }
        fprintf(file, "\n");
    }
}

/**
 * @brief Write the Measurement Summary to a file
 */
void PanelPolarimeter::write_Summary() {

    /* Re asign the folder path to save the measurement files */
    QString path2(ConfigureMeasurement->pathDataMeasurements.absoluteDir().path() + "/" + folderForData + "/");
    fileInfoSaving = QFileInfo(path2);

    /* Create the path for StoreToRam */
    QString path(fileInfoSaving.absoluteDir().path() + "/Measurement_Summary.sum");

    /* Got all StoreToRAM data, save it to disk now */
    FILE *file = fopen(path.toLatin1().data(), "wt");

    /* Check file handle */
    if (nullptr == file){
        return;
    }

    /* Write the Header with name/serial number */
    if (ptrSpectrometers[SpectrometerNumber]->hasReadableName()){
        fprintf(file, "Serial Number: %s \n", ptrSpectrometers[SpectrometerNumber]->getSerialNumber().toLatin1().data());
        fprintf(file, "Spectrometer Name: %s \n", ptrSpectrometers[SpectrometerNumber]->getReadableName().toLatin1().data());
    }else{
        fprintf(file, "Serial Number: %s\n", ptrSpectrometers[SpectrometerNumber]->getSerialNumber().toLatin1().data());
    }

    /* Write some useful data on file */
    fprintf(file, "Integration Time: %.2f ms\n", ptrSpectrometers[SpectrometerNumber]->getIntegrationTime());
    fprintf(file, "Nr. of Spectra: %i\n", ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->NrSpectra);
    fprintf(file, "Nr. of Averages: %i\n", ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages());
    fprintf(file, "Frequency: %.2f\n\n", FFTL.FrequencyF);

    /* Loop through the time */
    for (int z = 0; z < PolPlotter->averaged_Signal_time.length(); z++){

        /* Write FFT data headers */
        if (z == 0){
            fprintf(file, "Time \t \t");
            fprintf(file, "Average DC Amplitude \t \t");
            fprintf(file, "Average W Amplitude \t");
            fprintf(file, "Average 2W Amplitude \n");
        }

        /* Write wavelengths and amplitudes */
        fprintf(file, "%.1f\t\t", PolPlotter->averaged_Signal_time.at(z));
        fprintf(file, "%.4f\t\t", PolPlotter->AverageDC.at(z));
        fprintf(file, "%.4f\t\t", PolPlotter->AverageW.at(z));
        fprintf(file, "%.4f\t\t", PolPlotter->Average2W.at(z));

        fprintf(file, "\n");
    }

    /* Close the file */
    fclose(file);

    /* Free pointer */
    file = nullptr;

    /* Restart vectors */
    PolPlotter->averaged_Signal_time.resize(0);
    PolPlotter->AverageDC.resize(0);
    PolPlotter->AverageW.resize(0);
    PolPlotter->Average2W.resize(0);
}

/**
 * @brief Show All the initial UI of plots
 */
void PanelPolarimeter::showAllPlots() {

    /* Hide or Show plot items */
    ui->qwtPlot_Pol->setVisible(true);
    ui->qwtPlot_Pol_Average->setVisible(true);
    ui->qwtPlot_Pol_Compensation->setVisible(true);
    ui->qwtPlot_Pol_w_2w->setVisible(true);
    ui->label_raw->setVisible(true);
    ui->label_average->setVisible(true);
    ui->label_compensation->setVisible(true);
    ui->label_fftprofile->setVisible(true);
    ui->label_RS->setVisible(true);
    ui->label_HAver->setVisible(true);
    ui->label_HProf->setVisible(true);
    ui->label_Rat->setVisible(true);
    ui->line_rawratio->setVisible(true);
    ui->line_FFT->setVisible(true);
    ui->line_HLiveRatio->setVisible(true);
    ui->line_HFFTAverage->setVisible(true);
    ui->label_HideFFTProfile->setText("<< Hide FFT Profile");
    ui->label_HideFFTProfile->setStyleSheet("QLabel { color: blue; }");
    ui->label_HideFFTProfile->setFrameShape(QFrame::NoFrame);
    ui->label_HIdeLiveAverage->setText(">> Hide Live Average");
    ui->label_HIdeLiveAverage->setStyleSheet("QLabel { color: blue; }");
    ui->label_HIdeLiveAverage->setFrameShape(QFrame::NoFrame);
    ui->label_hideLiveRaw->setText("<< Hide Live Raw Signal");
    ui->label_hideLiveRaw->setStyleSheet("QLabel { color: blue; }");
    ui->label_hideLiveRaw->setFrameShape(QFrame::NoFrame);
    ui->label_HideRatio->setText(">> Hide Ratio I(ω)/I(2ω)");
    ui->label_HideRatio->setStyleSheet("QLabel { color: blue; }");
    ui->label_HideRatio->setFrameShape(QFrame::NoFrame);
}

/**
 * @brief Show the Analize data dialog
 */
void PanelPolarimeter::select_Analize_Pol_Measurement() {

    /* Create the analize data window */
    selectAnalizeData *DataSelector = new selectAnalizeData();

    /* After the measurement, open the analize data window automatically */
    if(Runner->automaticData && !fileInfoSaving.absolutePath().isEmpty()){

        /* Automatic loading of the data from here */
        QString PathAuto = fileInfoSaving.absolutePath() + "/FFT Data/";

        /* Analize data after finishing the measurements */
        DataSelector->automaticAnalize(PathAuto);
    }

    /* Adjust the wavelengths range for the PLS */
    DataSelector->ui->doubleSpinBox_minWavel->setMinimum(ptrSpectrometers[SpectrometerNumber]->getStartWavelength());
    DataSelector->ui->doubleSpinBox_minWavel->setMaximum(ptrSpectrometers[SpectrometerNumber]->getStopWavelength());
    DataSelector->ui->doubleSpinBox_maxWavel->setMinimum(ptrSpectrometers[SpectrometerNumber]->getStartWavelength());
    DataSelector->ui->doubleSpinBox_maxWavel->setMaximum(ptrSpectrometers[SpectrometerNumber]->getStopWavelength());
    DataSelector->ui->doubleSpinBox_maxWavel->setValue(PolarimetrySpectrometer->getMaximumWavelength());
    DataSelector->ui->doubleSpinBox_minWavel->setValue(PolarimetrySpectrometer->getMinimumWavelength());

    /* Show the window */
    DataSelector->exec();

    ui->Button_Save_Graphs_Pol->setVisible(true);

    ui->Tabs_Plots->setTabEnabled(1,true);
    ui->Tabs_Plots->setTabEnabled(2,true);

    PolPlotter->series->dataProxy()->resetArray(DataSelector->data3D);
    PolPlotter->surface->addSeries(PolPlotter->series);
    PolPlotter->surface->show();

    PolPlotter->surface->scene()->activeCamera()->setCameraPosition(45, 45, 100); // horizontal in °, vertikal in °, zoom in %

    QLinearGradient gr;
    gr.setColorAt(0.0, Qt::blue);
    gr.setColorAt(0.2, Qt::cyan);
    gr.setColorAt(0.4, Qt::green);
    gr.setColorAt(0.6, Qt::yellow);
    gr.setColorAt(0.8, Qt::red);
    gr.setColorAt(1.0, Qt::black);

    PolPlotter->surface->seriesList().at(0)->setBaseGradient(gr);
    PolPlotter->surface->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

    //scatter->seriesList().at(0)->setBaseGradient(gr);
    //scatter->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

}

/**
 * @brief Save the actual FFT from the calibration
 */
void PanelPolarimeter::saveFFTcalibration(){

    /* If there is calibration running */
    if(Runner->PolCalibrating){

        /* Here the user selects the file path and name */
        QString text = "";

        /* Was the calibration configured? */
        if(ConfigureMeasurement->configured){

            /* Then save the FFT with the actual information */
            FFTL.saveFFTtoFile(text, true, ConfigureMeasurement->externSoftware->ConfigurationFileGenerator->substancesNames);

        }else{

            /* Substance names doesn't make sense here, since no configuration has been created */
            QStringList substancesNames;

            /* Fill vector with nothing */
            for(int k = 0; k < 4; k++){
                substancesNames.append("");
            }

            /* Initialize some variables with the actual values, since no configuration has been created */
            FFTL.IntTime = PolarimetrySpectrometer->getIntegrationTime();
            FFTL.NrAverages = PolarimetrySpectrometer->getNumberOfAverages();
            FFTL.NrSpectra = PolarimetrySpectrometer->getNumberOfSpectra();
            FFTL.FrequencyF = PolarimetrySpectrometer->getFrequency();
            FFTL.changeFFTwavelength = true;
            FFTL.ConcentrationC1 = -1;
            FFTL.ConcentrationC2 = -1;
            FFTL.ConcentrationC3 = -1;
            FFTL.ConcentrationC4 = -1;
            FFTL.ConcentrationC5 = -1;
            FFTL.ConcentrationC6 = -1;
            FFTL.MaximumIntensity = 0;
            FFTL.normalizeCounts = PolarimetrySpectrometer->ui->checkBox_normalize->isChecked();

            /* Save the actual FFT shown in the calibration */
            FFTL.saveFFTtoFile(text, true, substancesNames);

        }
    }
}

/**
 * @brief Destructor of 'Polarimeter' class
 */
PanelPolarimeter::~PanelPolarimeter(void)
{
    /* Check handle */
    if (nullptr != curve_Pol)
    {
        /* Detach curve */
        curve_Pol->detach();

        /* Free memory */
        delete curve_Pol;
        curve_Pol = nullptr;
    }

    /* Free objects memory */
    delete PolPlotter;
    PolPlotter = nullptr;

    delete ConfigureMeasurement;
    ConfigureMeasurement = nullptr;

    delete Runner;
    Runner = nullptr;

    /* Delete user interface */
    delete ui;
}
