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
#include "qwt_plot_renderer.h"
#include <QTimer>
#include <QApplication>
#include <QSignalMapper>
#include <QCloseEvent>
#include <QSizePolicy>
#include <qprocess.h>

/*
 * Internal includes
 */

/* Qt library */

/* General stuff */
#include "application.h"
#include "messages.h"
#include "timer.h"
#include "math_helper.h"

/* Panel stuff */
#include "pol_plot.h"
#include "pol_panel.h"
#include "pol_fft.h"
#include "pol_panelHelp.h"
#include "pol_ConfigureMeasurement.h"
#include "pol_changeWave_FFT.h"
#include "pol_panelItem.h"
#include "panel_change_averages.h"
#include "panel_change_time.h"
#include "panel.h"
#include "ui_pol_panelItem.h"
#include "ui_pol_panel.h"
#include "plot.h"
#include "pol_measurements.h"
#include "ui_pol_ConfigureMeasurement.h"

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

    /* Configuration */
    ConfigureMeasurement = new configurePolMeasure();

    /* Creat plotter object */
    pol_plot = new Pol_Plot();

    /* Create signal mapper for panel */
    signalMapper = new QSignalMapper(this);

    /* Create Measurements Object */
    Runner = new Pol_Measurements();

    /* Not everything from the UI has to be shown at the beginning */
    showUI_Item(false);

    /* Get current path to executable */
    current = QDir::currentPath();

    /* Remove 'binary/[platform]' part from string */
    current = current.left(current.lastIndexOf("binary"));

    /* Hide some elements */
    ui->TotalProgressBar_Pol->setVisible(false);
    ui->label_totalM->setVisible(false);
    ui->horizontalSpacer_Y->changeSize(20,12,QSizePolicy::Expanding,QSizePolicy::Fixed);
    ui->currentProgressBar_Pol->setVisible(false);
    ui->label_prediction->setVisible(false);
    ui->line_comp->setVisible(false);

    /* Set window flags */
    this->setWindowFlags(Qt::Window);

    /* Create new item in Polarimeter Spectrometer List */
    QListWidgetItem *item_Pol = new QListWidgetItem(0);

    /* If we have at least one device selected from the list or available */
    if (m_NrDevices > 0)
    {
        /* The purpose of this list is to inform which spectrometer is in use for the Polarimetry Tab. Be able to see
        its name and change its parameters as the Integration time, number of averages, name and set the Auto Adjust */

        /* By Default, use the First Device checked on the List of Spectrometers from Preview Tab */

        /* Does the first spectrometer already have a readable name assigned? */
        if (ptrSpectrometers[SpectrometerNumber]->hasReadableName())
        {
            /* Yes. Add the spectrometer to the list using the readable name. */
            devices2.append(new PanelItem_Pol(0, ptrSpectrometers[SpectrometerNumber]->getReadableName()));
        }
        else
        {
            /* No. Add the spectrometer to the list using the serial number. */
            devices2.append(new PanelItem_Pol(0, ptrSpectrometers[SpectrometerNumber]->getSerialNumber()));
        }

        /* Polarimeter Setup Device Initialization */
        devices2[0]->setIntegrationTime(ptrSpectrometers[SpectrometerNumber]->getIntegrationTime());
        devices2[0]->setNumberOfAverages(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages());
        devices2[0]->setIsSaturated(ptrSpectrometers[SpectrometerNumber]->isSaturated());
        devices2[0]->setIsEnabled(true);

        /* Don't allow resize of item */
        item_Pol->setSizeHint(devices2[0]->size());

        /* Polarimeter List Item */
        ui->list_devices_Pol->addItem(item_Pol);
        ui->list_devices_Pol->setItemWidget(item_Pol, devices2[0]);

        /* Set the label clear all as clickable */
        ui->label_clearAll->setStyleSheet("QLabel { color: blue; }");

        /* Does the first spectrometer already have a readable name assigned? */
        if (ptrSpectrometers[SpectrometerNumber]->hasReadableName())
        {
            /* Polarimeter Plot of Raw Signal */
            curves_Pol.append(new QwtPlotCurve(ptrSpectrometers[SpectrometerNumber]->getReadableName()));
            curves_Pol[0]->setItemAttribute(QwtPlotItem::Legend, false);
        }
        else
        {
            /* Polarimeter Plot of Raw Signal */
            curves_Pol.append(new QwtPlotCurve(ptrSpectrometers[SpectrometerNumber]->getSerialNumber()));
            curves_Pol[0]->setItemAttribute(QwtPlotItem::Legend, false);
        }

        /* Polarimeter Plot of Raw Signal Color and attachment */
        curves_Pol[0]->setPen(QPen(defaultColors[SpectrometerNumber % 5]));
        curves_Pol[0]->attach(ui->qwtPlot_Pol);

        /* Polarimeter buttons and labels signal mapper */
        connect(devices2[0]->ui->label_integrationTime, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices2[0]->ui->label_numberOfAverages, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(devices2[0]->ui->label_autoAdjust, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(ui->checkBox_AutoSave_Pol_Raw, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(ui->checkBox_AutoSave_Pol, SIGNAL(clicked()), signalMapper, SLOT(map()));
        connect(ColumnSpectra, SIGNAL(returnPressed()), signalMapper, SLOT(map()));
        connect(ColumnFreq, SIGNAL(returnPressed()), signalMapper, SLOT(map()));

        /* Polarimeter set mapping for buttons and labels */
        signalMapper->setMapping(devices2[0]->ui->label_integrationTime, devices2[0]->ui->label_integrationTime);
        signalMapper->setMapping(devices2[0]->ui->label_numberOfAverages, devices2[0]->ui->label_numberOfAverages);
        signalMapper->setMapping(devices2[0]->ui->label_autoAdjust, devices2[0]->ui->label_autoAdjust);
        signalMapper->setMapping(ui->checkBox_AutoSave_Pol_Raw, ui->checkBox_AutoSave_Pol_Raw);
        signalMapper->setMapping(ui->checkBox_AutoSave_Pol, ui->checkBox_AutoSave_Pol);
        signalMapper->setMapping(ColumnSpectra, ColumnSpectra);
        signalMapper->setMapping(ColumnFreq, ColumnFreq);
        signalMapper->setMapping(ui->label_clearAll, ui->label_clearAll);
        signalMapper->setMapping(ui->label_raw, ui->label_raw);
        signalMapper->setMapping(ui->label_compensation, ui->label_compensation);
        signalMapper->setMapping(ui->label_fftprofile, ui->label_fftprofile);
        signalMapper->setMapping(ui->label_average, ui->label_average);
        signalMapper->setMapping(ui->label_prediction, ui->label_prediction);
        signalMapper->setMapping(ui->FFT_label_Pol, ui->FFT_label_Pol);
        signalMapper->setMapping(ui->label_Measurements_Pol, ui->label_Measurements_Pol);
        signalMapper->setMapping(ui->label_Save_Pol, ui->label_Save_Pol);
        signalMapper->setMapping(ui->label_hideConf, ui->label_hideConf);

        /* Connect event handler */
        connect(qApp, SIGNAL(DataPolIsHere(int, int)), this, SLOT(ReceiveDataIsHerePol(int, int)));
        connect(qApp,SIGNAL(lastWindowClosed()),this,SLOT(quitOxymetry()));
    }

    /* Connect signal mapper action */
    connect(signalMapper, SIGNAL(mapped(QWidget *)), this, SLOT(handleClickEvent(QWidget *)));

    /* Connect buttons in Polarimeter Tab */
    connect(ui->button_Start_Meas_Pol, SIGNAL(clicked()), this, SLOT(toggle_Pol_Measurement()));
    ui->button_Start_Meas_Pol->setStyleSheet(greenButton);
    connect(ui->button_LoadData, SIGNAL(clicked()), this, SLOT(toggle_LoadData()));
    connect(ui->help, SIGNAL(clicked()), this, SLOT(help()));
    connect(ui->waveToPlotFFT, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_clearAll, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_raw, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_compensation, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->Button_Save_Graphs_Pol, SIGNAL(clicked()), this, SLOT(saveGraph_Pol()));
    connect(ui->button_calibrate, SIGNAL(clicked()), this, SLOT(toggle_Pol_Calibration()));
    connect(ui->button_Pol_ConfigureMeasurement, SIGNAL(clicked()), this, SLOT(ConfSetup_Pol_Measurement()));
    connect(ui->label_fftprofile, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_average, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_prediction, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->FFT_label_Pol, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_Measurements_Pol, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_Save_Pol, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->label_hideConf, SIGNAL(clicked()), signalMapper, SLOT(map()));

    /* If there are spectrometers connected, allow Polarimetry Measurement */
    ui->button_Start_Meas_Pol->setDisabled((!m_NrDevices) ? true : false);
    ui->button_Start_Meas_Pol->setStyleSheet((!m_NrDevices) ? grayButton : greenButton);
    ui->button_calibrate->setDisabled((!m_NrDevices) ? true : false);
    ui->button_calibrate->setStyleSheet((!m_NrDevices) ? grayButton : "black");
    ui->checkBox_AutoSave_Pol->setDisabled((!m_NrDevices) ? true : false);
    ui->checkBox_AutoSave_Pol_Raw->setDisabled((!m_NrDevices) ? true : false);
    ui->button_Pol_ConfigureMeasurement->setDisabled((!m_NrDevices) ? true : false);
    ui->label_clearAll->setDisabled((!m_NrDevices) ? true : false);

    /* Set axis and title of Raw Signal plot for Polarimeter */
    ui->qwtPlot_Pol->setXAxisTitle("Wavelength (nm)");
    ui->qwtPlot_Pol->setYAxisTitle("ADC counts");
    ui->qwtPlot_Pol->setYAxis(0.0, 65535.0);

    /* Set axis and title of Compensated Signal plot for Polarimeter */
    ui->qwtPlot_Pol_Compensation->setXAxisTitle("Wavelength (nm)");
    ui->qwtPlot_Pol_Compensation->setYAxisTitle("Intensity");
    ui->qwtPlot_Pol_Compensation->setYAxis(0.0, 3);

    /* Set axis and title of w/2w plot for Polarimeter */
    ui->qwtPlot_Pol_w_2w->setXAxisTitle("Wavelength (nm)");
    ui->qwtPlot_Pol_w_2w->setYAxisTitle("Intensity");
    ui->qwtPlot_Pol_w_2w->setYAxis(0.0, 40000);

    /* Set axis and title of Average over all Wavelenths plot for Polarimeter */
    ui->qwtPlot_Pol_Average->setXAxisTitle("Time (sec)");
    ui->qwtPlot_Pol_Average->setYAxisTitle("Intensity");
    ui->qwtPlot_Pol_Average->setYAxis(0.0, ceil(2000*1.1));
    ui->qwtPlot_Pol_Average->setXAxis(0.0, pol_plot->time_plot);

    /* Set axis and title of Prediction Curve, now in use to show the FFT */
    ui->qwtPlot_Pol_FFT->setXAxis(0.0, 21);
    ui->qwtPlot_Pol_FFT->setYAxis(0.0, 3000);

    QwtText bottomTitle = QString("Frequency (Hz)");
    ui->qwtPlot_Pol_FFT->axisFont.setPointSize(8);

    /* Set font and update title */
    bottomTitle.setFont(ui->qwtPlot_Pol_FFT->axisFont);
    ui->qwtPlot_Pol_FFT->setAxisTitle(QwtPlot::xBottom, bottomTitle);

    ui->qwtPlot_Pol_FFT->grid->enableX(false);
    ui->qwtPlot_Pol_FFT->setAxisScale(QwtPlot::xBottom, 0, 21, 7);
    ui->qwtPlot_Pol_FFT->setAxisScale(QwtPlot::yLeft, 0, 3000, 1000);
    ui->qwtPlot_Pol_FFT->updateAxes();

    /* Set axis and title of Prediction Curve, now in use to show the FFT */
    ui->qwtPlot_Pol_Prediction->setXAxisTitle("Reference (mg/dL)");
    ui->qwtPlot_Pol_Prediction->setYAxisTitle("Predicted (mg/dL)");
    ui->qwtPlot_Pol_Prediction->setXAxis(0.0, 500);
    ui->qwtPlot_Pol_Prediction->setYAxis(0.0, 500);

    /* Reference concentration */
    ui->qwtPlot_Pol_Prediction->setVisible(false);

    /* Defaults values for x-axis are 400 to 1000 nm */
    unsigned int i = 0;

    /* Are there any spectrometers connected? */
    if (m_NrDevices > 0)
    {
        double startWavelengths[m_NrDevices], stopWavelengths[m_NrDevices];

        /* Loop through spectrometers */
        for (i = 0; i < m_NrDevices; i++)
        {
            /* Get start and stop wavelengths for current spectrometer */
            startWavelengths[i] = ptrSpectrometers[i]->getStartWavelength();
            stopWavelengths[i] = ptrSpectrometers[i]->getStopWavelength();
        }
        /* Find minimum and maximum wavelengths in array */
        minWavelength = getMinimum(startWavelengths, m_NrDevices);
        maxWavelength = getMaximum(stopWavelengths, m_NrDevices);

        /* Which wavelentgth would you like to see the FFT? */
        signalMapper->setMapping(ui->waveToPlotFFT, ui->waveToPlotFFT);

        /* Disable edition of Spectrometer Data until there is a calibration running */
        devices2[0]->ui->label_autoAdjust->setEnabled(false);
        devices2[0]->ui->label_integrationTime->setEnabled(false);
        devices2[0]->ui->label_numberOfAverages->setEnabled(false);

    }

    /* Update x-axis of graphs depending on Wavelengths */
    ui->qwtPlot_Pol->setXAxis(minWavelength, maxWavelength);
    ui->qwtPlot_Pol_Compensation->setXAxis(minWavelength, maxWavelength);
    ui->qwtPlot_Pol_w_2w->setXAxis(minWavelength, maxWavelength);

    /* Set size of columns for measurement profile table */
    ui->tableInfoMeasure->setColumnWidth(0,144);
    ui->tableInfoMeasure->setColumnWidth(1,144);
}

/**
 * @brief Update user interface
 */
void PanelPolarimeter::update()
{
    /* Update changes from other Tabs */
    devices2[0]->setIntegrationTime(ptrSpectrometers[SpectrometerNumber]->getIntegrationTime());
    devices2[0]->setNumberOfAverages(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages());
    devices2[0]->setName(ptrSpectrometers[SpectrometerNumber]->getReadableName());
    SelectedSpectrometer_Polarimeter();
}

/**
 * @brief User interface items
 */
void PanelPolarimeter::showUI_Item(bool UIstatus)
{
    /* Update items on UI */
    ui->label_Measurements_Pol->setVisible(UIstatus);
    ui->Table_Measurements_Pol->setVisible(UIstatus);
    ui->label_Save_Pol->setVisible(UIstatus);
    ui->checkBox_AutoSave_Pol->setVisible(UIstatus);
    ui->checkBox_AutoSave_Pol_Raw->setVisible(UIstatus);

    /* Make the items look nice */
    if(UIstatus){
        ui->verticalSpacerX->changeSize(20,13,QSizePolicy::Fixed,QSizePolicy::Fixed);
    }else{
        ui->verticalSpacerX->changeSize(20,13,QSizePolicy::Fixed,QSizePolicy::Expanding);
    }
}

/* RUN ------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Toggles Measurements of the Polarimeter
 */
void PanelPolarimeter::toggle_Pol_Measurement(void)
{
    /* Polarimeter Measurement running or not? */
    if(!Runner->PolMeasuring)
    {
        /* Is there a loaded profile? */
        if(Runner->PolConfigured){

            /* Allow to show the initial Raw data plot */
            Runner->showRaw = false;

            /* No Polarimeter Calibration running at the moment. Start it. */
            clearPlot();

            /* Add expected concentration prediction */
            pol_plot->predictionSignal->attach(ui->qwtPlot_Pol_Prediction);
            ui->qwtPlot_Pol_Prediction->update();

            /* Show total measurement bar and plots */
            ui->TotalProgressBar_Pol->setVisible(true);
            ui->label_totalM->setVisible(true);
            ui->horizontalSpacer_Y->changeSize(20,12,QSizePolicy::Fixed,QSizePolicy::Fixed);
            ui->qwtPlot_Pol_Prediction->setVisible(true);
            ui->label_prediction->setVisible(true);
            ui->line_comp->setVisible(true);
            ui->qwtPlot_Pol->setVisible(true);
            ui->qwtPlot_Pol_Average->setVisible(true);
            ui->qwtPlot_Pol_Compensation->setVisible(true);
            ui->qwtPlot_Pol_w_2w->setVisible(true);

            /* Restart the flag of interrupted measurement */
            Runner->Stopped = false;

            /* Run type measurement with 1 */
            Run_Polarimetry(1);

        }else{
            /* Show message if no configuration loaded */
            showCritical("Please load a Configuration Profile to Start the Measurement", "");
            return;
        }
    }
    else
    {
        /* Polarimeter Measurement running at the moment. Stop it. */
        Stop_Run_Polarimetry();
    }
}

/**
 * @brief Start to running Polarimeter
 */
void PanelPolarimeter::Run_Polarimetry(short int runType) {

    /* Adjust the start of measurements */
    AdjustRunStart(runType);

    /* Time measurement index */
    Timeindex = 0;

    /* Start Running Polarimetry */
    while (Runner->PolCalibrating || Runner->PolMeasuring)
    {
        /* User changes frequency and doesn't press enter */
        if(ColumnFreq->hasFocus() && OldFreqValue == ""){
            /* Get current text in cell */
            OldFreqValue = ColumnFreq->text();
        }

        /* User changes nr spectra and doesn't press enter */
        if(ColumnSpectra->hasFocus() && OldSpectraValue == ""){
            /* Get current text in cell */
            OldSpectraValue = ColumnSpectra->text();
        }

        /* Restart timer if there is too much time elapsed already */
        if(Runner->Timer_In_Seconds > 1000) {
            /* Start timers */
            Runner->RestartTimers();
        }

        /* The software was closed by the user abruptly */
        if(abort_everything){
            /* Stop running measurements */
            Stop_Run_Polarimetry();

            /* Break loop */
            break;
        }

        /* Calibration */
        if(Runner->PolCalibrating){

            /* Skip doing calibration routine because a change is in progress */
            if(!Runner->AcceptChanges){

                /* Do calibration routine */
                Pol_Calibrate();
            }
        }

        /* Long Time Measurement */
        if(Runner->PolMeasuring){

            /* Do Measurement routine */
            Pol_Measure();
        }

        /* Handle events and update UI */
        Application::processEvents();

        /* Wait 1 ms */
        Timer::msleep(1);
    }

    /* Adjust the End of measurements */
    AdjustRunEnd(runType);
}

/**
 * @brief Stop the Calibration of the Spectrometer Settings and the Polarimeter Setup
 */
void PanelPolarimeter::Stop_Run_Polarimetry() {

    /* If the user decides to stop when the system is busy */
    if(Runner->delayStop)
    {
        /* Set the button disabled since it was already pressed */
        ui->button_calibrate->setEnabled(false);

        /* Delay the stop of the calibration */
        Runner->delayedStop = true;
    }

    /* Is spectrometer disabled? */
    devices2[0]->setIsEnabled(true);

    /* Stop Calibrating */
    if(Runner->PolCalibrating){

        /* Update information bar */
        ui->info->setText("Calibrating... Stopping Spectrometer");

        /* No Polarimetric Calibration running anymore */
        Runner->setCalibrationRunning(false);

        /* This file has to be removed */
        QFile file(fileInfo.absoluteFilePath()+"/Pol_tmp.tmp");

        /* Does the File exists? If no do nothing */
        if(file.exists()){

            /* Remove the temporal file */
            file.remove();
        }

        /* Handle events and update UI */
        Application::processEvents();

        /* Disable edition of Spectrometer Data until there is a calibration running */
        devices2[0]->ui->label_autoAdjust->setEnabled(false);
        devices2[0]->ui->label_integrationTime->setEnabled(false);
        devices2[0]->ui->label_numberOfAverages->setEnabled(false);

        /* Enable Polarimeter Buttons */
        ui->button_Start_Meas_Pol->setEnabled(true);

        /* Disable the edition of columns of configuration */
        ColumnSpectra->setReadOnly(true);
        ColumnFreq->setReadOnly(true);
        ColumnSpectra->setStyleSheet("QLineEdit { color: black;  border: none}");
        ColumnFreq->setStyleSheet("QLineEdit { color: black; border: none}");

        /* Update pol meas button */
        ui->button_calibrate->setText("Calibrate");
        ui->button_calibrate->setStyleSheet("black");
        ui->button_calibrate->setEnabled(true);
        ui->button_Start_Meas_Pol->setStyleSheet(greenButton);

        /* Update information bar */
        ui->info->setText("");

    }

    /* Stop Long Term Measuring */
    if(Runner->PolMeasuring){

        /* Measurement interrupted */
        Runner->Stopped = true;

        /* Update information bar */
        ui->info->setText("Measuring... Stop");

        /* No Polarimetric Measurement running anymore */
        Runner->setMeasurementRunning(false);

        /* Handle events and update UI */
        Application::processEvents();

        /* Update Polarimeter Measurement button */
        ui->button_Start_Meas_Pol->setText("Start Measurement");
        ui->button_Start_Meas_Pol->setStyleSheet(greenButton);
        ui->button_Start_Meas_Pol->setEnabled(true);
        ui->button_calibrate->setEnabled(true);

        /* Update information bar */
        ui->info->setText("Measurement Finished");
    }

    /* Stop the measurement */
    if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){
        ptrSpectrometers[SpectrometerNumber]->stopMeasurement();
    }

    /* Enable buttons again */
    ui->checkBox_AutoSave_Pol->setEnabled(true);
    ui->checkBox_AutoSave_Pol_Raw->setEnabled(true);
    ui->button_Pol_ConfigureMeasurement->setEnabled(true);
    ui->button_LoadData->setEnabled(true);
    ui->label_clearAll->setEnabled(true);
    ui->label_clearAll->setStyleSheet("QLabel { color: blue;}");

    /* Emit signal to enable the preview buttons */
    DisEnablePreview(true);
}

/**
 * @brief Adjust the Running Start
 */
void PanelPolarimeter::AdjustRunStart(short int typeRun){

    /* Emit signal to disable preview buttons */
    DisEnablePreview(false);

    /* Show current progress bar*/
    ui->currentProgressBar_Pol->setVisible(true);

    /* Re- attach the raw signal plot in case it was removed for example in cleaning all */
    curves_Pol[0]->attach(ui->qwtPlot_Pol);

    /* Restart stop flags */
    Runner->delayedStop = false;
    Runner->delayStop = false;

    /* Disable buttons when running polarimetry */
    ui->button_LoadData->setEnabled(false);
    ui->button_Start_Meas_Pol->setEnabled(false);
    ui->checkBox_AutoSave_Pol->setEnabled(false);
    ui->checkBox_AutoSave_Pol_Raw->setEnabled(false);
    ui->button_calibrate->setEnabled(false);
    ui->button_Pol_ConfigureMeasurement->setEnabled(false);
    ui->label_clearAll->setEnabled(false);
    ui->label_clearAll->setStyleSheet("QLabel { color: gray;}");

    /* Is spectrometer enabled? */
    devices2[0]->setIsEnabled(false);

    /* Initialize the time for each type of run, calibrate: raw or FFT */
    Runner->liveFFT_Time = 0;
    Runner->Calibration_Progress = 0;
    ui->currentProgressBar_Pol->setValue(0);

    /* runType == 0 means Calibration and runType == 1 means Measuring */
    if(typeRun == 0){

        /* Initialize the calibration */
        initializeCalibration();

    }else{

        /* Remember Polarimeter Measurement is Running */
        Runner->setMeasurementRunning(true);

        /* Update pol meas button */
        ui->button_Start_Meas_Pol->setText("Stop Measurement");
        ui->button_Start_Meas_Pol->setStyleSheet(RedButton);
        ui->button_Start_Meas_Pol->setEnabled(true);

        /* Measurement progress bars */
        ui->currentProgressBar_Pol->setValue(0);
        ui->TotalProgressBar_Pol->setValue(0);
    }

    /* Start timers */
    Runner->RestartTimers();
}

/**
 * @brief Adjust the Running End
 */
void PanelPolarimeter::AdjustRunEnd(short int typeRunn){

    /* When a long term measurement is done, then stop everything */
    if(typeRunn == 1){

        /* When finish, give some time to plot the last data point */
        Runner->timerMS.start();
        int t = 3;

        ui->info->setText("Finishing Measurements");

        /* Keep plotting the average, so the last data point is visible */
        while(!Runner->Stopped){

            /* Count seconds */
            if(Runner->timerMS.elapsed()/1000 > t){

                /* Seconds */
                t = t+1;

                /* Plot the live average values */
                plotAverage();

                /* Handle events and update UI */
                Application::processEvents();
            }

            /* If closed, abort! */
            if(abort_everything || t > ConfigureMeasurement->timePoint[0]/2000){break;}
        }

        /* Reset selected row */
        ui->Table_Measurements_Pol->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->Table_Measurements_Pol->selectRow(0);
        ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::NoSelection);

        /* Set progress bars to 100 percent */
        ui->currentProgressBar_Pol->setValue(0);
        ui->TotalProgressBar_Pol->setValue(0);

        /* Set it to true, just to oficially stop the long term measurement */
        Runner->setMeasurementRunning(true);

        /* If the measurement is done, then just stop the measurement */
        Stop_Run_Polarimetry();
    }

    /* Stop the measurements */
    Runner->setMeasurementRunning(false);

    /* Stop the Calibration */
    Runner->setCalibrationRunning(false);
}

/**
 * @brief Run Measurements
 */
void PanelPolarimeter::Pol_Measure(void){

    /* Plot the averages on real time during the measurement */
    if(Runner->timerMS.elapsed()/1000 > Runner->Timer_In_Seconds){

        /*Time in seconds */
        Runner->Timer_In_Seconds = Runner->Timer_In_Seconds + 1;

        /* Plot the live average values */
        plotAverage();
    }

    /* Update information bar */
    if(!ptrSpectrometers[SpectrometerNumber]->isMeasuring()){
        ui->info->setText("Measuring... Waiting for Cuvette Flushing");
    }

    /* Generate absolute path for StoreToRAM files */
    fileInfo = QFileInfo(ConfigureMeasurement->path);
    QString path(fileInfo.absoluteDir().path() + "/");

    /* Check if we have more entries to do */
    if (Timeindex < (unsigned int)ConfigureMeasurement->timePoint.length())
    {
        /* Next measurement starts now? */
        if (Runner->timerMS.elapsed() >= ConfigureMeasurement->timePoint[Timeindex])
        {
            /* Save the raw data as .CS file */
            path.append(ConfigureMeasurement->fileName[Timeindex] + ".CS");

            /* Check if spectrometer is still measuring */
            if (ptrSpectrometers[SpectrometerNumber]->isMeasuring())
            {
                ptrSpectrometers[SpectrometerNumber]->stopMeasurement();
            }

            /* Configure spectrometer */
            ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(ConfigureMeasurement->integrationTime);
            ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(ConfigureMeasurement->numberOfAverages);

            /* Prepare StoreToRAM measurement */
            ptrSpectrometers[SpectrometerNumber]->forceStoreToRAM(path, ConfigureMeasurement->numSpectra);
            if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
            {
                ui->info->setText("Measuring... Saving/Plotting Data");
                /* Start measurement */
                ptrSpectrometers[SpectrometerNumber]->startMeasurement(2);
            }

            /* Select the row that belongs to the measurement */
            ui->Table_Measurements_Pol->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->Table_Measurements_Pol->selectRow(Timeindex);
            ui->Table_Measurements_Pol->setSelectionMode(QAbstractItemView::NoSelection);

            /* Go to next entry */
            Timeindex++;

            Runner->showRaw = false;
        }

        if(!ptrSpectrometers[SpectrometerNumber]->isMeasuring()){

            /* When no raw signal anymore, then do the measurement */
            if(!Runner->showRaw){
                if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
                {
                    /* Start measurement */
                    ptrSpectrometers[SpectrometerNumber]->startMeasurement(-2);
                    ui->info->setText("Measuring... Adjusting Sample, See Live Raw Data");
                }
                Runner->showRaw = true;
            }
        }
    }

    Pol_MeasurementProgress(Timeindex);

}

/* CONFIGURATION ------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Configuration of Measurments
 */
void PanelPolarimeter::ConfSetup_Pol_Measurement(void) {

    /* Update information bar */
    ui->info->setText("Loading... Configuration File");

    /* Did the user cancel the configuration? */
    ConfigureMeasurement->Conf_canceled = false;

    /* Run the configuration window */
    ConfigureMeasurement->exec();

    /* Was there a configuration loaded? */
    if(ConfigureMeasurement->configured && !ConfigureMeasurement->Conf_canceled){

        /* Show needed UI items */
        showUI_Item(true);

        /* Save if the measurement has been configured */
        Runner->setConfigured(true);

        /* Prevent user from resizing the header */
        ui->Table_Measurements_Pol->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        ui->tableInfoMeasure->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

        /* Left align column titles */
        ui->Table_Measurements_Pol->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
        ui->tableInfoMeasure->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);

        /* Prevent user from editing the cells */
        ui->Table_Measurements_Pol->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableInfoMeasure->setEditTriggers(QAbstractItemView::NoEditTriggers);

        /* Adjust table widget */
        ui->Table_Measurements_Pol->setColumnWidth(0, 60);
        ui->Table_Measurements_Pol->setColumnWidth(1, 150);

        /* Zero row count of measurement list */
        ui->Table_Measurements_Pol->setRowCount(0);

        unsigned int i = 0;

        /* Loop through elements */
        for (i = 0; i < (unsigned int) ConfigureMeasurement->timePoint.length(); i++)
        {
            /* At least second entry? */
            if (i > 0)
            {
                /* Calculate duration of entry before current entry */
                double duration =  ConfigureMeasurement->numSpectra *  ConfigureMeasurement->integrationTime *  ConfigureMeasurement->numberOfAverages;

                /* Check if there's a time overlap between last and current entry */
                if (( ConfigureMeasurement->timePoint[i - 1] + duration) >  ConfigureMeasurement->timePoint[i])
                {
                    /* Zero row count */
                    ui->Table_Measurements_Pol->setRowCount(0);
                    return;
                }
            }

            /* Increase current row count */
            ui->Table_Measurements_Pol->setRowCount(ui->Table_Measurements_Pol->rowCount() + 1);

            /* Create label for time point */
            QLabel *nt2 = new QLabel();
            nt2->setText(QString::number(ConfigureMeasurement->timePoint.at(i)/1000));
            nt2->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->Table_Measurements_Pol->setCellWidget(i, 0, nt2);

            /* Create label for file name */
            QLabel *nt3 = new QLabel();
            nt3->setText(ConfigureMeasurement->fileName.at(i));
            nt3->setStyleSheet("QLabel { margin-left: 2px; }");
            ui->Table_Measurements_Pol->setCellWidget(i, 1, nt3);
        }

        /* Label for number of spectra */
        ColumnSpectra->setText(QString::number(ConfigureMeasurement->numSpectra));
        ColumnSpectra->setStyleSheet("QLineEdit { border: none }");
        ui->tableInfoMeasure->setCellWidget(0, 0, ColumnSpectra);
        ColumnSpectra->setReadOnly(true);
        ColumnSpectra->setStyleSheet("QLineEdit { color: black;  border: none}");
        FFTL.NrSpectra = ConfigureMeasurement->numSpectra;

        /* Label for Frequency Measurement */
        ColumnFreq->setText(QString::number(ConfigureMeasurement->freqToMeasure));
        ColumnFreq->setStyleSheet("QLineEdit { border: none }");
        ui->tableInfoMeasure->setCellWidget(0, 1, ColumnFreq);
        ColumnFreq->setReadOnly(true);
        ColumnFreq->setStyleSheet("QLineEdit { color: black;  border: none}");
        FFTL.FrequencyF = ConfigureMeasurement->freqToMeasure;

        /* Change the Spectrometer Integration Time according to the loaded configuration */
        ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(ConfigureMeasurement->integrationTime);
        devices2[0]->ui->label_integrationTime->setText(QString::number(ptrSpectrometers[SpectrometerNumber]->getIntegrationTime()));
        FFTL.IntTime = ConfigureMeasurement->integrationTime;

        /* Change the Spectrometer Number of Averages according to the loaded configuration */
        ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(ConfigureMeasurement->numberOfAverages);
        devices2[0]->ui->label_numberOfAverages->setText(QString::number(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages()));
        FFTL.NrAverages = ConfigureMeasurement->numberOfAverages;

        /* Select first row */
        ui->Table_Measurements_Pol->selectRow(0);

        /* Emit signal to update changes in preview tab */
        updateTabs();

        /* Update information bar */
        ui->info->setText("Configuration ready");

    }else{

        /* Update information bar */
        ui->info->setText("");
    }
}

/**
 * @brief If a configuration file was loaded and changes were made during calibration, then cahnge file names
 */
void PanelPolarimeter::changeFileName(void){

    /* When configuration loaded and changes are made, then update the files */
    if(Runner->PolConfigured){

        /* Get first name on list */
        QString changeFileName = ConfigureMeasurement->fileName.at(0);
        QString NewFileName = "";

        /* Iterate through the name and find the "_" on it */
        for(int i=0; i < changeFileName.length();i++){

            /* Save the first part of the file name */
            NewFileName = NewFileName + changeFileName.at(i);

            /* When reading C2_ then rewrite with new information */
            if (changeFileName[i] == "2" && changeFileName[i+1] == "_"){
                break;
            }
        }

        /* For each file in the list */
        for(int j = 0; j < ConfigureMeasurement->fileName.length(); j++){

            /* Change the name by the first part plus the new information */
            ConfigureMeasurement->fileName.replace(j, NewFileName + "_" + QString::number(ConfigureMeasurement->integrationTime) + "ms_" + QString::number(ConfigureMeasurement->freqToMeasure) + "Hz_" + QString::number(j+1));

            /* Remove the actual data on table */
            ui->Table_Measurements_Pol->removeCellWidget(j, 1);

            /* Update label for file name */
            QLabel *newt3 = new QLabel();
            newt3->setText(ConfigureMeasurement->fileName.at(j));
            newt3->setStyleSheet("QLabel { margin-left: 2px; }");

            /* Add new data to table */
            ui->Table_Measurements_Pol->setCellWidget(j, 1, newt3);
        }
    }
}

/* HANDLE EVENTS ------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Data from spectrometer has arrived
 * @param WParam
 * @param LParam
 */
void PanelPolarimeter::ReceiveDataIsHerePol(int WParam, int LParam)
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
                devices2[0]->setIsSaturated(ptrSpectrometers[SpectrometerNumber]->isSaturated());

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
                    /* Did the current spectrometer in polarimeter sent the data? */
                    if ((LParam == ptrSpectrometers[SpectrometerNumber]->getHandle()) && (ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() > 0))
                    {
                        /* Handle event */
                        ptrSpectrometers[SpectrometerNumber]->handleEvent();

                        /* Update saturation status */
                        devices2[0]->setIsSaturated(ptrSpectrometers[SpectrometerNumber]->isSaturated());

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

                /*
             * Got all StoreToRAM data, save it to disk now!
             */

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
                writeToFile(file, a_pSpectrum, WParam);

                /* Close file */
                fclose(file);
                file = nullptr;

                /* Free memory */
                delete[] a_pSpectrum;
                a_pSpectrum = nullptr;

                /* If the system is busy doing the live FFT analisys */
                Runner->doingLiveFFT = true;

                /* Do the FFT to the received data */
                isFFTData = false;

                /* Is the FFT for measurement or calibration purposes? */
                if(!Runner->PolCalibrating){
                    /* path for measurements */
                    fileInfo = QFileInfo(path);
                }else{

                    /* Use the temporal file if calibrating */
                    fileInfo = QFileInfo(fileInfo.absoluteDir().path() + "/" + Runner->TempFileName);
                }

                if(Runner->delayedStop){
                    /* Was there a delayed stop of the calibration? */
                    Runner->delayStop = false;
                    Runner->delayedStop = false;
                }else{

                    /* Data Analysis by FFT from the just written file */
                    FFTL.getFFTfromRawData(fileInfo, Runner->PolCalibrating, maxWavelength);

                    /* Update information bar */
                    ui->info->setText("Calibrating... Waiting for Spectrometer");

                    /* Clear all the plots for a new loaded data */
                    clearPlot();

                    /* Plot the FFT Signals */
                    Plot_FFT();
                    ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths.at(FFTL.SelectedWaveL)));

                    /* Don't combine loaded data with calibrated data regarding the averages */
                    if(dataloaded){
                        dataloaded = false;
                    }
                }

                /* Is there an automatic saving of FFT Data selected by the user? */
                if(ui->checkBox_AutoSave_Pol->isChecked() && Runner->PolMeasuring && !Runner->PolCalibrating){
                    /* Save FFT value to file */
                    FFTL.saveFFTtoFile(fileInfo);
                }

                /* Is there an automatic saving of Raw Data?, if not just remove the file with the Raw Data */
                if(!ui->checkBox_AutoSave_Pol_Raw->isChecked()&& !Runner->PolCalibrating){
                    /* Remove temporal file */
                    remove(path.toLatin1().data());
                }

                /* Spectrometer finished measurement */
                ptrSpectrometers[SpectrometerNumber]->bMeasuring = false;

                if(Runner->PolCalibrating){
                    Runner->Calibration_Progress = 0;
                    ui->currentProgressBar_Pol->setValue(0);
                }
            }

            /* Update curve of raw data */
            curves_Pol[0]->setSamples(ptrSpectrometers[SpectrometerNumber]->getWavelengths(), ptrSpectrometers[SpectrometerNumber]->getCounts(),
                                      ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels());

            /* Is there a maximum amount of counts to change the Y axis on plot? */
            if(Runner->maxRawCounts==-1 || Runner->maxRawCounts < ptrSpectrometers[SpectrometerNumber]->getMaxCounts()){

                /* If so, adjust the Y axis */
                ui->qwtPlot_Pol->setYAxis(0.0, ceil(ptrSpectrometers[SpectrometerNumber]->getMaxCounts()+ ptrSpectrometers[SpectrometerNumber]->getMaxCounts()/2));

                /* Save the maximum amount of counts registered */
                Runner->maxRawCounts = ptrSpectrometers[SpectrometerNumber]->getMaxCounts();
            }

        }

        /* Does the graph needs a update? */
        if (needUpdate)
        {
            /* Update the graph */
            ui->qwtPlot_Pol->update();
            ui->qwtPlot_Pol_Average->update();
        }
    }

    /* I'm not busy anymore */
    Runner->doingLiveFFT = false;

}

/**
 * @brief Called if a widget on a spectrometer item in list got clicked,
 *        e.g. Integration time label.
 * @param widget Widget which has been clicked
 */
void PanelPolarimeter::handleClickEvent(QWidget *widget)
{
    QLabel *label = qobject_cast<QLabel *>(widget);
    QLineEdit *LineLabel = qobject_cast<QLineEdit *>(widget);

    /* The integration time label has been clicked */
    if (label == devices2[0]->ui->label_integrationTime && Runner->PolCalibrating && !Runner->doingLiveFFT)
    {
        /* Change integration time */
        change_IntegrationTimePol();
    }

    /* The auto-adjust label has been clicked */
    else if (label == devices2[0]->ui->label_autoAdjust && Runner->PolCalibrating && !Runner->doingLiveFFT)
    {
        /* Apply changes from the autoadjusted integration time */
        change_AutoIntegrationTimePol();
    }

    /* The number of averages label has been clicked */
    else if (label == devices2[0]->ui->label_numberOfAverages && !Runner->doingLiveFFT && Runner->PolCalibrating)
    {
        /* Change number of averages during calibration */
        change_NrAveragesPol();

        /* The wavelength to show the FFT label has been clicked */
    } else if(label == ui->waveToPlotFFT){

        /* Change the Wavelength to plot */
        change_WaveFFTPol();

        /* The label of clear all was clicked */
    }else if(label == ui->label_clearAll){

        /* Update information bar */
        ui->info->setText("Restart all?");

        /* Do you want to clean all? */
        if (QMessageBox::Yes == QMessageBox::question(this, "Clean All", "Are you sure that you want to clean all? \n \n This option will remove all loaded settings and plotted data.",
                                                      QMessageBox::Yes | QMessageBox::No))
        {
            /* Button 'yes' pressed; Clean all */
            clean_AllPol();
        }

        /* Update information bar */
        ui->info->setText("");
    }else if(label == ui->label_raw){

        /* Is the plot visible? */
        if(ui->qwtPlot_Pol->isVisible()){
            /* Hide it if clicked */
            ui->qwtPlot_Pol->setVisible(false);
        }else{
            /* Show it again */
            ui->qwtPlot_Pol->setVisible(true);
        }
    }else if(label == ui->label_compensation){

        /* Is the plot visible? */
        if(ui->qwtPlot_Pol_Compensation->isVisible()){
            /* Hide it if clicked */
            ui->qwtPlot_Pol_Compensation->setVisible(false);
        }else{
            /* Show it again */
            ui->qwtPlot_Pol_Compensation->setVisible(true);
        }
    }else if(label == ui->label_fftprofile){

        /* Is the plot visible? */
        if(ui->qwtPlot_Pol_w_2w->isVisible()){
            /* Hide it if clicked */
            ui->qwtPlot_Pol_w_2w->setVisible(false);
        }else{
            /* Show it again */
            ui->qwtPlot_Pol_w_2w->setVisible(true);
        }
    }else if(label == ui->label_average){

        /* Is the plot visible? */
        if(ui->qwtPlot_Pol_Average->isVisible()){
            /* Hide it if clicked */
            ui->qwtPlot_Pol_Average->setVisible(false);
        }else{
            /* Show it again */
            ui->qwtPlot_Pol_Average->setVisible(true);
        }
    }else if(label == ui->label_prediction){

        /* Is the plot visible? */
        if(ui->qwtPlot_Pol_Prediction->isVisible()){
            /* Hide it if clicked */
            ui->qwtPlot_Pol_Prediction->setVisible(false);
        }else{
            /* Show it again */
            ui->qwtPlot_Pol_Prediction->setVisible(true);
        }

    }else if(label == ui->FFT_label_Pol){

        /* Is the plot visible? */
        if(ui->qwtPlot_Pol_FFT->isVisible()){
            /* Hide it if clicked */
            ui->qwtPlot_Pol_FFT->setVisible(false);
        }else{
            /* Show it again */
            ui->qwtPlot_Pol_FFT->setVisible(true);
        }
    }else if(label == ui->label_Measurements_Pol){

        /* Is the plot visible? */
        if(ui->Table_Measurements_Pol->isVisible()){
            /* Hide it if clicked */
            ui->Table_Measurements_Pol->setVisible(false);
        }else{
            /* Show it again */
            ui->Table_Measurements_Pol->setVisible(true);
        }
    }else if(label == ui->label_Save_Pol){

        /* Is the plot visible? */
        if(ui->checkBox_AutoSave_Pol->isVisible()){
            /* Hide it if clicked */
            ui->checkBox_AutoSave_Pol->setVisible(false);
            ui->checkBox_AutoSave_Pol_Raw->setVisible(false);

        }else{
            /* Show it again */
            ui->checkBox_AutoSave_Pol->setVisible(true);
            ui->checkBox_AutoSave_Pol_Raw->setVisible(true);
        }
    }else if(label == ui->label_hideConf){

        /* Is the plot visible? */
        if(ui->list_devices_Pol->isVisible()){

            /* Change label to show lateral panel */
            ui->label_hideConf->setText("Show >>");
            ui->label_hideConf->setMinimumWidth(40);

            /* Hide it if clicked */
            ui->label_Set_Spec_Pol->hide();
            ui->list_devices_Pol->hide();
            ui->tableInfoMeasure->hide();
            ui->FFT_label_Pol->hide();
            ui->waveToPlotFFT->hide();
            ui->qwtPlot_Pol_FFT->hide();
            ui->line_c1->hide();
            ui->line_c2->hide();
            ui->label_n->hide();
            ui->label_5_Pol_settings->hide();
            ui->button_calibrate->hide();
            ui->button_Pol_ConfigureMeasurement->hide();
            ui->button_Start_Meas_Pol->hide();
            ui->HSpaceX->changeSize(20,5,QSizePolicy::Fixed,QSizePolicy::Fixed);

            /* Hide thus GUI elements if they are already visible */
            if(Runner->PolConfigured){
                ui->Table_Measurements_Pol->hide();
                ui->checkBox_AutoSave_Pol->hide();
                ui->checkBox_AutoSave_Pol_Raw->hide();
                ui->label_Measurements_Pol->hide();
                ui->label_Save_Pol->hide();
            }

        }else{

            /* Now the user can hide the lateral panel */
            ui->label_hideConf->setText("<< Hide");
            ui->label_hideConf->setMinimumWidth(290);

            /* Show it again */
            ui->label_Set_Spec_Pol->show();
            ui->list_devices_Pol->show();
            ui->tableInfoMeasure->show();
            ui->FFT_label_Pol->show();
            ui->waveToPlotFFT->show();
            ui->qwtPlot_Pol_FFT->show();
            ui->line_c1->show();
            ui->line_c2->show();
            ui->label_5_Pol_settings->show();
            ui->button_calibrate->show();
            ui->button_Pol_ConfigureMeasurement->show();
            ui->button_Start_Meas_Pol->show();
            ui->label_n->show();

            if(Runner->PolConfigured){
                ui->label_Measurements_Pol->show();
                ui->Table_Measurements_Pol->show();
                ui->checkBox_AutoSave_Pol->show();
                ui->label_Save_Pol->show();
                ui->checkBox_AutoSave_Pol_Raw->show();
            }
            ui->HSpaceX->changeSize(120,5,QSizePolicy::Fixed,QSizePolicy::Fixed);
        }
    }

    /* The user decide to change the number of Spectra for the measurement during the calibration */
    if (LineLabel == ColumnSpectra && ColumnSpectra->text().toInt() > 0 && Runner->PolCalibrating && !Runner->doingLiveFFT)
    {
        /* Change the Nr of Spectra */
        change_NrSpectraPol();
    }

    /* The user decide to change the frequency for the measurement during the calibration */
    if (LineLabel == ColumnFreq && ColumnFreq->text().toDouble() > 0 && Runner->PolCalibrating && !Runner->doingLiveFFT)
    {
        /* Change frequency */
        change_FrequencyPol();
    }

    /* The user doesn't have any saving option selected for the measurement, are you sure that you don't want to save the data? */
    if(!ui->checkBox_AutoSave_Pol->isChecked() && !ui->checkBox_AutoSave_Pol_Raw->isChecked()){

        /* Show message */
        ui->info->setText("Saving... One type of file should be selected");
        showWarning("Data might not be saved during the Measurement, FFT Data will be selected by default!", "");

        /* Select FFT data saving for default */
        ui->checkBox_AutoSave_Pol->setChecked(true);
        ui->info->setText("");
        return;
    }

    if((!ui->qwtPlot_Pol_FFT->isVisible() || (!ui->Table_Measurements_Pol->isVisible() || !ui->checkBox_AutoSave_Pol->isVisible())) && Runner->PolConfigured){
        ui->verticalSpacerX->changeSize(20,13,QSizePolicy::Fixed,QSizePolicy::Expanding);
    }else{
        if(Runner->PolConfigured){
            ui->verticalSpacerX->changeSize(20,13,QSizePolicy::Fixed,QSizePolicy::Fixed);
        }
    }

    if(ui->Table_Measurements_Pol->isVisible() && Runner->PolConfigured){
        ui->verticalSpacerX->changeSize(20,13,QSizePolicy::Fixed,QSizePolicy::Fixed);
    }

    /* Emit signal to update changes in preview tab */
    updateTabs();
}

/**
 * @brief Automatic adjustment of integration time
 */
void PanelPolarimeter::adjustIntegrationTimePol()
{
    /* Is the spectrometer measuring? */
    if (ptrSpectrometers[SpectrometerNumber]->isMeasuring())
    {
        /* Yes, so stop the measurement */
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
            float intTime = devices2[SpectrometerNumber]->getIntegrationTime();

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
            devices2[0]->setIntegrationTime(intTime);
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
    ConfigureMeasurement->integrationTime = ptrSpectrometers[SpectrometerNumber]->getIntegrationTime();
    FFTL.IntTime = ConfigureMeasurement->integrationTime;

    /* Is the spectrometer measuring? */
    if (ptrSpectrometers[SpectrometerNumber]->isMeasuring())
    {
        /* Yes, so stop the measurement */
        ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

        /* Handle events and update UI */
        Application::processEvents();

        /* Wait 1 ms */
        Timer::msleep(1);

    }
}

/**
 * @brief Change the Integration time by the user during calibration
 */
void PanelPolarimeter::change_IntegrationTimePol(void){

    /* Update Information bar */
    ui->info->setText("Calibrating... Setting Integration Time");

    /* Skip running the calibration routine */
    Runner->AcceptParameterChanges();

    /* Open the integration time panel to change it */
    PanelChangeTime changeDialog(this);

    /* Get the actual integration time */
    changeDialog.setValue(devices2[0]->getIntegrationTime());

    /* User pressed 'ok' */
    if (QDialog::Accepted == changeDialog.exec())
    {

        /* Stop the measurement */
        if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){
            /* Stop the Spectrometer */
            ptrSpectrometers[SpectrometerNumber]->stopMeasurement();
        }

        /* Get new integration time */
        float intTime = changeDialog.getValue();

        /* Is it an aceptable integration time? */
        double Timeresolution = 1000/(4*ConfigureMeasurement->freqToMeasure);

        /* Too large integration time for the actual settings? */
        if( intTime > Timeresolution){
            /* Show message */
            QString messenger = "Your actual settings allow a maximum integration time of " + QString::number(Timeresolution) + " ms ";
            showCritical(messenger, "");
            return;
        }

        /* Set panel item and device integration time */
        devices2[0]->setIntegrationTime(intTime);
        ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(intTime);

        /* Save changes everywhere */
        FFTL.IntTime = intTime;
        ConfigureMeasurement->integrationTime = intTime;


        /* If there is a configuration loaded, then change the file names */
        changeFileName();

        /* Ajust X axis of time plotting */
        Adjust_AveragePlotTime();

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
    ui->info->setText("Calibrating... Waiting for Spectrometer");

    /* Restart the calibration */
    Runner->restart_CalibrationPol();
}

/**
 * @brief Change the integration time from the auto adjusting during calibration
 */
void PanelPolarimeter::change_AutoIntegrationTimePol(void){

    /* Update information bar */
    ui->info->setText("Calibrating... Auto Adjusting Integration Time (This might take some time)");

    /* Stop Calibration */
    Runner->AcceptParameterChanges();

    /* Stop the measurement */
    if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){
        /* If so, then stop */
        ptrSpectrometers[SpectrometerNumber]->stopMeasurement();
    }

    /* Give it some time to process */
    Timer::msleep(10);

    /* Run automatic adjustment of integration time */
    adjustIntegrationTimePol();

    /* If the new value is consistent with the frequency */
    double Freqresolution = 1000/ConfigureMeasurement->integrationTime;

    /* Is there a frequency resolution lower than 1 Hz? */
    if(Freqresolution/4 < 1){

        /* If yes, then use 1 Hz as the minimum frequency resolution */
        ConfigureMeasurement->freqToMeasure = 1;
        ColumnFreq->setText(QString::number(ConfigureMeasurement->freqToMeasure));
        FFTL.FrequencyF = ConfigureMeasurement->freqToMeasure;

        /* To resolve 1 Hz it only makes sense to use a maximum int time of 250 ms */
        devices2[0]->setIntegrationTime(250);
        ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(250);
        ConfigureMeasurement->integrationTime = 250;
        FFTL.IntTime = 250;

        /* Ajust X axis of time plotting */
        Adjust_AveragePlotTime();

        /* Show message */
        showWarning("With your actual settings the resolution of integration time is maximum 250 ms with 1 Hz for W ", "");

        /* If not, set the maximum automatically */
    }else if(ColumnFreq->text().toDouble() > Freqresolution/4){

        /* Set frequency to the maximum allowed with actual settings */
        ConfigureMeasurement->freqToMeasure = Freqresolution/4;
        ColumnFreq->setText(QString::number(ConfigureMeasurement->freqToMeasure));
        FFTL.FrequencyF = ConfigureMeasurement->freqToMeasure;

        /* Ajust X axis of time plotting */
        Adjust_AveragePlotTime();

        /* Auto adjusted frequency */
        QString messenger = "Frequency was adjusted to " + QString::number(ConfigureMeasurement->freqToMeasure) + " Hz becuase it's the maximum resolution ";
        showCritical(messenger, "");

        /* If the new int time is ok, then continue normally */
    }else{
        /* Save automatic changes on integration time */
        FFTL.IntTime = ptrSpectrometers[SpectrometerNumber]->getIntegrationTime();
        ConfigureMeasurement->integrationTime = ptrSpectrometers[SpectrometerNumber]->getIntegrationTime();

        /* Ajust X axis of time plotting */
        Adjust_AveragePlotTime();

    }

    /* If there is a configuration loaded, then change the file names */
    changeFileName();

    /* Restart Y axis plot */
    Runner->maxRawCounts=-1;

    /* Current progress bar restart */
    ui->currentProgressBar_Pol->setValue(0);

    /* Update information bar */
    ui->info->setText("Calibrating... Waiting for Spectrometer");

    /* Restart the calibration */
    Runner->restart_CalibrationPol();
}

/**
 * @brief Change the wavelength to show in the FFT plot
 */
void PanelPolarimeter::change_WaveFFTPol(void){

    /* Update the information bar */
    ui->info->setText("FFT Plot... Setting Wavelength");

    /* Open dialog to change the wavelength */
    PanelChangeWaveFFT changeDialog(this);

    /* Is there loaded information to be shown already? */
    if(pol_plot->FFT_DC != nullptr){
        for (int i =0; i<FFTL.wavelengths.length();i++){
            changeDialog.setValue(FFTL.wavelengths.at(i));
        }
    }else{
        /* If there no information to show, add just a zero to the list */
        changeDialog.setValue(0);
    }

    /* If there is information to show, then ask for the wavelength to show the FFT */
    if (QDialog::Accepted == changeDialog.exec() && pol_plot->FFT_DC != nullptr)
    {
        /* Get the needed information at the frequencies DC, W and 2W */
        if(!FFTL.wavelengths.isEmpty()){

            /* Get the wavelength */
            FFTL.SelectedWaveL = changeDialog.getValue();

            /* Full of zeros those other frequencies of non interest */
            for ( int  i = 0; i < FFTL.NrSpectra/2; i++ )
            {
                FFTL.fft_data.append(0);
            }

            /* Add the frequency amplitudes of interest */
            FFTL.fft_data.replace(0, FFTL.fft_DC.at(FFTL.SelectedWaveL));
            FFTL.fft_data.replace(FFTL.f_w, FFTL.fft_W.at(FFTL.SelectedWaveL));
            FFTL.fft_data.replace(2*FFTL.f_w, FFTL.fft_2W.at(FFTL.SelectedWaveL));

            /* Show the selected wavelength of FFT */
            ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths.at(FFTL.SelectedWaveL)));

            /* Plot the FFT Signals */
            pol_plot->plotFFTatSelectedWave(FFTL.fft_data, FFTL.time);
            ui->waveToPlotFFT->setStyleSheet("QLabel { color: blue; }");

            /* Change the axis according to the new data */
            ui->qwtPlot_Pol_FFT->setXAxis(0.0,  3*FFTL.FrequencyF);
            ui->qwtPlot_Pol_FFT->setAxisScale(ui->qwtPlot_Pol_FFT->xBottom,0, 3*FFTL.FrequencyF, FFTL.FrequencyF);
            int maximum = *std::max_element(FFTL.fft_data.begin(), FFTL.fft_data.end());
            ui->qwtPlot_Pol_FFT->setYAxis(0.0,maximum);
            ui->qwtPlot_Pol_FFT->setAxisScale(ui->qwtPlot_Pol_FFT->yLeft, 0, maximum, maximum/3);
            ui->qwtPlot_Pol_FFT->updateAxes();

            /* Plot Selected Wavelength */
            pol_plot->FFT_oneWave->attach(ui->qwtPlot_Pol_FFT);

            /* Update Plot */
            ui->qwtPlot_Pol_FFT->update();
            ui->qwtPlot_Pol_FFT->updateLayout();
        }
    }
    /* Update the information bar */
    ui->info->setText("");
}

/**
 * @brief Change the number of spectra during calibration
 */
void PanelPolarimeter::change_NrSpectraPol(void){

    /* Update information bar */
    ui->info->setText("Calibrating... Setting Number of Spectra");

    /* Stop running calibration */
    Runner->AcceptParameterChanges();

    /* Stop the measurement */
    if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){
        /* If so, then stop */
        ptrSpectrometers[SpectrometerNumber]->stopMeasurement();
    }

    /* More than 2000 is a high load for the spectrometer */
    if(ColumnSpectra->text().toInt() > 2000){
        /* Show message */
        showWarning("Please consider that large amounts of spectra may need longer the time of Data processing.", "");
    }

    /* Save changes on number of spectra */
    FFTL.NrSpectra = ColumnSpectra->text().toInt();
    ConfigureMeasurement->numSpectra = ColumnSpectra->text().toInt();
    ColumnSpectra->clearFocus();

    /* If user decides to write something on line edit, but doesn't accept the changes */
    OldSpectraValue = "";

    /* Ajust X axis of time plotting */
    Adjust_AveragePlotTime();

    /* Current progress bar restart */
    ui->currentProgressBar_Pol->setValue(0);

    /* Update information bar */
    ui->info->setText("Calibrating... Waiting for Spectrometer");

    /* Restart the calibration */
    Runner->restart_CalibrationPol();
}

/**
 * @brief Change the frequency during calibration
 */
void PanelPolarimeter::change_FrequencyPol(void){

    /* Update information bar */
    ui->info->setText("Calibrating... Setting Frequency Modulation");

    /* Stop running calibration */
    Runner->AcceptParameterChanges();

    /* Stop the measurement */
    if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){
        /* If so, stop */
        ptrSpectrometers[SpectrometerNumber]->stopMeasurement();
    }

    /* What's the largest frequency that can be resolved? */
    double Freqresolution = 1000/ConfigureMeasurement->integrationTime;

    /* Is the new frequency greater than the maximum resolution? */
    if(ColumnFreq->text().toDouble() > Freqresolution/4){
        /* Show message */
        QString messenger = "Your actual settings allow a maximum resolution for W of " + QString::number(Freqresolution/4) + " Hz ";
        showCritical(messenger, "");
        return;
    }

    /* Save changes everywhere */
    FFTL.FrequencyF = ColumnFreq->text().toDouble();
    ConfigureMeasurement->freqToMeasure = ColumnFreq->text().toDouble();
    ColumnFreq->clearFocus();

    /* If user decides to write something on line edit, but doesn't accept the changes */
    OldFreqValue = "";

    /* Change name of files if there is a configuration loaded */
    changeFileName();

    /* Current progress bar restart */
    ui->currentProgressBar_Pol->setValue(0);

    /* Update information bar */
    ui->info->setText("Calibrating... Waiting for Spectrometer");

    /* Restart the calibration */
    Runner->restart_CalibrationPol();
}

/**
 * @brief Change the Nr of Averages during calibration
 */
void PanelPolarimeter::change_NrAveragesPol(void){

    /* Update information bar */
    ui->info->setText("Calibrating... Setting Number of Averages");

    /* Stop Calibration */
    Runner->AcceptParameterChanges();

    /* Open the dialog to change the number of averages */
    PanelChangeAverages changeDialog(this);

    /* Get actual number of averages */
    changeDialog.setValue(devices2[0]->getNumberOfAverages());

    /* User pressed 'ok' */
    if (QDialog::Accepted == changeDialog.exec())
    {
        /* Stop the measurement */
        if(ptrSpectrometers[SpectrometerNumber]->isMeasuring()){
            /* If so, then stop */
            ptrSpectrometers[SpectrometerNumber]->stopMeasurement();
        }

        /* Get new number of averages */
        int numberOfAverages = changeDialog.getValue();

        /* Set panel item and device number of averages */
        devices2[0]->setNumberOfAverages(numberOfAverages);
        ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(numberOfAverages);

        /* Save changes on the number of averages */
        ConfigureMeasurement->numberOfAverages = numberOfAverages;
        FFTL.NrAverages = numberOfAverages;

        /* Ajust X axis of time plotting */
        Adjust_AveragePlotTime();
    }

    /* Restart Y axis plot */
    Runner->maxRawCounts= -1;

    /* Current progress bar restart */
    ui->currentProgressBar_Pol->setValue(0);

    /* Update information bar */
    ui->info->setText("Calibrating... Waiting for Spectrometer");

    /* Restart the calibration */
    Runner->restart_CalibrationPol();
}


/* DATA HANDLE ------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Load Data from the FFT, Polarimeter Setup
 */
void PanelPolarimeter::LoadFromFFT(void) {

    /* Update information bar */
    ui->info->setText("Loading... FFT Data");

    /* What kind of data are we loading? */
    isFFTData = true;

    /* Load Data Path */
    DataPath = QFileDialog::getOpenFileName(this, QString("Open FFT Data file"), ".", QString("*.TXT"));

    /* File selected by user? */
    if (NULL == DataPath)
    {
        /* No file selected. Dialog aborted. */
        ui->info->setText("");
        return;
    }else{
        /* Where is the file located? */
        fileInfo = DataPath;
    }

    /* Check format of file; we need at least 4 _ in name */
    if (fileInfo.completeBaseName().count(QLatin1Char('_')) != 5 || fileInfo.completeBaseName().at(fileInfo.completeBaseName().length()-1) !="T")
    {
        /* Show message */
        showWarning("Non valid File for FFT Analysis Loading! \n\n Please check Name and Content of the FFT File", "");
        return;
    }

    /* Show the analyzed data from FFT */
    FFTL.getFFTfromFFTData(fileInfo);

    /* Clean the plots for a new plotting */
    clearPlot();

    /* Plot the FFT Signals */
    Plot_FFT();

    /* There was data loaded */
    dataloaded = true;

    /* By default show the wavelength 516,41 nm */
    ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths.at(404)));

    /* Update information bar */
    ui->info->setText("");
}

/**
 * @brief Load Data and Perform FFT from Raw Data, Polarimeter Setup
 */
void PanelPolarimeter::LoadFromRawData(void) {

    /* Update information bar */
    ui->info->setText("Loading... Raw Data");

    /* What type of file are we loading? Not FFT here */
    isFFTData = false;

    /* Load Data Path */
    DataPath = QFileDialog::getOpenFileName(this, QString("Open Raw Data file"), ".", QString("*.CS;*.TXT"));

    /* File selected by user? */
    if (NULL == DataPath)
    {
        ui->info->setText("");
        /* No file selected. Dialog aborted. */
        return;
    }else{
        /* Where is the file located? */
        fileInfo = DataPath;
    }

    /* Check format of file; we need at least 4 _ in name */
    if (fileInfo.completeBaseName().count(QLatin1Char('_')) != 4 || !fileInfo.completeBaseName().at(fileInfo.completeBaseName().length()-1).isNumber())
    {
        /* Show message */
        showWarning("Non valid File for Raw Data Analysis! \n\n Please check Name and Content of the Raw Data File", "");
        return;
    }

    /* Data Analysis by FFT */
    FFTL.getFFTfromRawData(fileInfo, false, maxWavelength);

    /* Clear all the plots for a new load of data */
    clearPlot();

    /* Plot the FFT Signals */
    Plot_FFT();

    /* There was data loaded */
    dataloaded = true;

    /* By default show the wavelength 516,41 nm */
    ui->waveToPlotFFT->setText(QString::number(FFTL.wavelengths.at(404)));

    /* Update information bar */
    ui->info->setText("");
}

/**
 * @brief Write the Raw Data to a File
 */
void PanelPolarimeter::writeToFile(FILE *file, double *a_pSpectrum, int WParam) {

    /* Write on file the header if it's not the temporal file used for calibration */
    if(!Runner->PolCalibrating){
        /* Write the Header with name/serial number */
        if (ptrSpectrometers[SpectrometerNumber]->hasReadableName()){
            fprintf(file, "Serial number and name: %s", ptrSpectrometers[SpectrometerNumber]->getSerialNumber().toLatin1().data());
            fprintf(file, ", %s\n", ptrSpectrometers[SpectrometerNumber]->getReadableName().toLatin1().data());
        }else{
            fprintf(file, "Serial number: %s\n", ptrSpectrometers[SpectrometerNumber]->getSerialNumber().toLatin1().data());
        }

        /* Write some useful data on file */
        fprintf(file, "Integration time: %.2f ms\n", ptrSpectrometers[SpectrometerNumber]->getIntegrationTime());
        fprintf(file, "Number of averages: %i\n", ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages());
        fprintf(file, "Number of Spectra: %i\n\n", ConfigureMeasurement->numSpectra);
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

        for (k = 0; k < (unsigned int)WParam; k++)
        {
            fprintf(file, "\t\t%.2f", *(a_pSpectrum + ptrSpectrometers[SpectrometerNumber]->getNumberOfPixels() * k + j));
        }
        fprintf(file, "\n");
    }
}

/**
 * @brief Toggles Load Data Button
 */
void PanelPolarimeter::toggle_LoadData(void)
{

    /* Is there something already analyzed by FFT? */
    if(pol_plot->FFT_DC != nullptr && isFFTData == false){

        /* File doens't exists. Did we ask the user to save the analyzed data from raw data? */
        if (QMessageBox::Yes == QMessageBox::question(this, "Save FFT File", "Would you like to save the FFT from Raw Data?",
                                                      QMessageBox::Yes | QMessageBox::No))
        {
            /* Button 'yes' pressed; Save the FFT data to the folder on redist */
            FFTL.saveFFTtoFile(fileInfo);
        }
    }

    /* Update Information bar */
    ui->info->setText("Loading... Select the type of File to load");

    /* Use a dialog to select the kind of data to be loaded */
    QMessageBox msgBox;
    QPushButton *Raw = msgBox.addButton(tr("Raw Data"),QMessageBox::ActionRole);
    QPushButton *FFT = msgBox.addButton(tr("FFT Data"), QMessageBox::ActionRole);

    /* Set tool tips */
    Raw->setToolTip("Load Raw Data");
    Raw->setToolTipDuration(-1);
    FFT->setToolTip("Load FFT Data");
    FFT->setToolTipDuration(-1);

    /* Adjust the dialog window */
    msgBox.addButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("Loading Data File ...                                                                             ");
    msgBox.setInformativeText("Please select the type of data that you would like to load?");
    msgBox.setWindowTitle("Load Data");

    /* Run the dialog */
    msgBox.exec();

    /* If user select FFT type data, then run load from FFT function */
    if (msgBox.clickedButton() == FFT) {
        /* Load FFT */
        LoadFromFFT();

        /* If user select raw data, then load it */
    } else if (msgBox.clickedButton() == Raw) {
        /* Load and analyze raw data */
        LoadFromRawData();
    }

    if (msgBox.clickedButton() == Raw || msgBox.clickedButton() == FFT ) {
        /* Remove some items from the GUI loaded when needed */
        showUI_Item(false);

        /* Don't show total measurement bar */
        ui->TotalProgressBar_Pol->setVisible(false);
        ui->label_totalM->setVisible(false);
        ui->horizontalSpacer_Y->changeSize(20,12,QSizePolicy::Expanding,QSizePolicy::Fixed);
        ui->qwtPlot_Pol_Prediction->setVisible(false);
        ui->label_prediction->setVisible(false);
        ui->line_comp->setVisible(false);
        ui->qwtPlot_Pol->setVisible(false);
        ui->qwtPlot_Pol_Average->setVisible(false);
        ui->qwtPlot_Pol_Compensation->setVisible(true);
        ui->qwtPlot_Pol_w_2w->setVisible(true);

        /* Show current progress bar*/
        ui->currentProgressBar_Pol->setVisible(false);
    }

    /* Update Information bar */
    ui->info->setText("");

    /* Free allocated memory */
    delete Raw;
    Raw = nullptr;
    delete FFT;
    FFT = nullptr;
}


/* PLOTS ------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Adjust plotting time in live averages.
 */
void PanelPolarimeter::Adjust_AveragePlotTime(){

    /* How long does take a measurement? */
    int measuringTime = (ConfigureMeasurement->integrationTime*ConfigureMeasurement->numSpectra*ConfigureMeasurement->numberOfAverages/1000);

    /* Plot always 20 measurements per refresh */
    pol_plot->time_plot = (measuringTime + measuringTime/3 + 12)*20;
    ui->qwtPlot_Pol_Average->setXAxis(pol_plot->averaged_Signal_time.at(0),pol_plot->averaged_Signal_time.at(0)+ pol_plot->time_plot);
}

/**
 * @brief Plot FFT.
 */
void PanelPolarimeter::Plot_FFT(){

    /* Plot FFT function on object Pol Plot */
    pol_plot->Plot_FFT_Graphs(FFTL.wavelengths, FFTL.time, FFTL.fft_data, FFTL.fft_DC, FFTL.fft_W, FFTL.fft_2W, FFTL.fft_Compensation_Signal);

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
    pol_plot->FFT_oneWave->attach(ui->qwtPlot_Pol_FFT);

    /* Set plotting axis */
    ui->qwtPlot_Pol_w_2w->setYAxis(0.0, ceil(*std::max_element(FFTL.fft_DC.begin(), FFTL.fft_DC.end())*1.1));

    /* Assign the values to the plots */
    pol_plot->FFT_DC->attach(ui->qwtPlot_Pol_w_2w);
    pol_plot->FFT_W->attach(ui->qwtPlot_Pol_w_2w);
    pol_plot->FFT_2W->attach(ui->qwtPlot_Pol_w_2w);

    /* Set axis */
    ui->qwtPlot_Pol_Compensation->setYAxis(0.0, ceil(*std::max_element(FFTL.fft_Compensation_Signal.begin(), FFTL.fft_Compensation_Signal.end())*1));

    /* Assign values to plot */
    pol_plot->Compensation_Signal->attach(ui->qwtPlot_Pol_Compensation);

    /* Update the Plots and Labels */
    ui->qwtPlot_Pol_w_2w->update();
    ui->qwtPlot_Pol_Compensation->update();
    ui->qwtPlot_Pol_Compensation->updateLayout();
    ui->qwtPlot_Pol_w_2w->updateLayout();
    ui->qwtPlot_Pol_FFT->update();
    ui->qwtPlot_Pol_FFT->updateLayout();
    ui->qwtPlot_Pol_Prediction->update();
}

/**
 * @brief Remove all plots of the Interface before to load any other plots.
 */
void PanelPolarimeter::clearPlot(void) {

    if(dataloaded){
        /* Detach FFT plots */
        pol_plot->FFT_DC->detach();
        pol_plot->FFT_W->detach();
        pol_plot->FFT_2W->detach();
        pol_plot->FFT_oneWave->detach();
        pol_plot->Compensation_Signal->detach();
        pol_plot->predictionSignal->detach();
    }

    /* Update plots */
    ui->qwtPlot_Pol_w_2w->update();
    ui->qwtPlot_Pol_Compensation->update();
    ui->qwtPlot_Pol_FFT->update();
    ui->qwtPlot_Pol_Prediction->update();
    ui->qwtPlot_Pol_FFT->updateLayout();
    ui->waveToPlotFFT->setText("");
}

/**
 * @brief Save All graphs from the Polarimeter Setup
 */
void PanelPolarimeter::saveGraph_Pol(void) {

    /* Update information bar */
    ui->info->setText("Saving... Graphs to file");

    /* Get the folder to save the different PDF files with the plots */
    QString pathPDF =QFileDialog::getSaveFileName(this, tr("Save plots as PDF files"), "", "Text files (*.pdf)");

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

        if(ui->qwtPlot_Pol_Prediction->isVisible()){
            renderer.renderDocument(ui->qwtPlot_Pol_Prediction, pathPDF + "_Prediction.pdf" , "pdf",QSizeF(300, 200));
        }
    }

    /* Update information bar */
    ui->info->setText("");
}

/**
 * @brief Plot W, DC and 2W averaged
 */
void PanelPolarimeter::plotAverage(){

    /* Plot Averages */
    pol_plot->plotAverages(dataloaded, FFTL.fft_DC, FFTL.fft_W, FFTL.fft_2W, FFTL.wavelengths);

    /* Attach graphs */
    pol_plot->Average_DC_Signal->attach(ui->qwtPlot_Pol_Average);
    pol_plot->Average_W_Signal->attach(ui->qwtPlot_Pol_Average);
    pol_plot->Average_2W_Signal->attach(ui->qwtPlot_Pol_Average);

    /* Is there a new maximum value for the Y axis to resize it? Usually DC is the largest of all three */
    if(dataloaded){
        ui->qwtPlot_Pol_Average->setYAxis(0.0, ceil((2000)*1.1));
    }else{
        ui->qwtPlot_Pol_Average->setYAxis(0.0, ceil((pol_plot->maxYValue)*1.1));
    }

    /* Update plots */
    ui->qwtPlot_Pol_Average->update();

    /* If we have more than certain amount of values in the plot, change the X axis */
    if(pol_plot->averaged_Signal_time.length() >= pol_plot->time_plot){

        /* Change axis according to the running time */
        ui->qwtPlot_Pol_Average->setXAxis(pol_plot->maxXtime, pol_plot->maxXtime + pol_plot->time_plot);

        /* Restart all vector to don't overload them with too many information */
        pol_plot->averaged_Signal_time.resize(0);
        pol_plot->AverageDC.resize(0);
        pol_plot->AverageW.resize(0);
        pol_plot->Average2W.resize(0);
    }

    /* This QT function doesn't work properly for a live plot */
    ui->qwtPlot_Pol_Average->disableZoom();
}

/* CALIBRATION ------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Toggles Calibration of the Polarimeter
 */
void PanelPolarimeter::toggle_Pol_Calibration(void)
{

    bool run = true;

    /* Polarimeter Calibration running or not? */
    if(!Runner->PolCalibrating)
    {
        /* No Polarimeter Measurement running at the moment. Start it. */
        if(!Runner->PolConfigured){

            /* Use a dialog to select the kind of Calibration */
            QMessageBox msgBoxCal;
            QPushButton *FreeCalib = msgBoxCal.addButton(tr("Free Calibration"),QMessageBox::ActionRole);
            QPushButton *LoadConf = msgBoxCal.addButton(tr("Load Configuration"), QMessageBox::ActionRole);

            /* Set tool tips */
            FreeCalib->setToolTip("Start a default free calibration");
            LoadConf->setToolTip("Load or generate a configuration file");
            FreeCalib->setToolTipDuration(-1);
            LoadConf->setToolTipDuration(-1);

            /* Adjust the dialog window */
            msgBoxCal.addButton(QMessageBox::Cancel);
            msgBoxCal.setIcon(QMessageBox::Question);
            msgBoxCal.setText("Would you like to load a Configuration Profile or start a free calibration?                                                                            ");
            msgBoxCal.setInformativeText("If you don't load a configuration profile, changes on parameters here won't change the measurement configuration. \n\n");
            msgBoxCal.setWindowTitle("Calibration");

            /* Run the dialog */
            msgBoxCal.exec();

            /* No Configuration loaded for calibration, better ask the user if wants to continue or edit a configuration file. */
            if (msgBoxCal.clickedButton() == LoadConf) {

                /* Button 'Load Configuration' pressed; Load a Configuration Profile */
                ConfSetup_Pol_Measurement();

                /* Free calibration runs then! */
            }else if(msgBoxCal.clickedButton() == FreeCalib){

                /* Initialize a defalut calibration */
                initializeDefaultCalibration();

            }else{
                run = false;
            }

            /* Free Memory */
            delete FreeCalib;
            FreeCalib = nullptr;
            delete LoadConf;
            LoadConf = nullptr;
        }

        if(run){
            /* No Polarimeter Calibration running at the moment. Start it. */
            clearPlot();

            /* Hide total measurement bar */
            ui->TotalProgressBar_Pol->setVisible(false);
            ui->label_totalM->setVisible(false);
            ui->horizontalSpacer_Y->changeSize(20,12,QSizePolicy::Expanding,QSizePolicy::Fixed);
            ui->qwtPlot_Pol_Prediction->setVisible(false);
            ui->label_prediction->setVisible(false);
            ui->line_comp->setVisible(false);

            /* Show needed plots */
            ui->qwtPlot_Pol->setVisible(true);
            ui->qwtPlot_Pol_Average->setVisible(true);
            ui->qwtPlot_Pol_Compensation->setVisible(true);
            ui->qwtPlot_Pol_w_2w->setVisible(true);

            /* Run type calibration with 0 */
            Run_Polarimetry(0);
        }
    }
    else
    {
        /* Polarimeter Calibration running at the moment. Stop it. */
        Stop_Run_Polarimetry();

        /* Show current progress bar*/
        ui->currentProgressBar_Pol->setVisible(false);
    }

}

/**
 * @brief Initialize the calibration
 */
void PanelPolarimeter::initializeCalibration(void){

    /* Now the calibration is running, remember that! */
    Runner->setCalibrationRunning(true);

    /* Update information bar */
    ui->info->setText("Calibrating... Initializing Spectrometer");

    /* Enable edition of Spectrometer Data until there is no calibration running */
    devices2[0]->ui->label_autoAdjust->setEnabled(true);
    devices2[0]->ui->label_integrationTime->setEnabled(true);
    devices2[0]->ui->label_numberOfAverages->setEnabled(true);

    /* Set the coulmns style of the tables editable */
    ColumnSpectra->setStyleSheet("QLineEdit { border}");
    ColumnFreq->setStyleSheet("QLineEdit { border}");

    /* Set editable the columns of the table */
    ColumnSpectra->setReadOnly(false);
    ColumnFreq->setReadOnly(false);
    ColumnSpectra->setStyleSheet("QLineEdit { color: blue}");
    ColumnFreq->setStyleSheet("QLineEdit { color: blue}");

    /* Update Polarimeter Calibration buttons */
    ui->button_calibrate->setText("Stop Calibration");
    ui->button_calibrate->setStyleSheet(RedButton);
    ui->button_calibrate->setEnabled(true);
    ui->button_Start_Meas_Pol->setStyleSheet(grayButton);

    /* Ajust X axis of time plotting */
    Adjust_AveragePlotTime();
}

/**
 * @brief Initialize the calibration with default values
 */
void PanelPolarimeter::initializeDefaultCalibration(void){

    /* Default values for the calibration purpose */
    double defaultSpectra = 1000, defaultFreq = 7;

    /* Assign the default number of spectra and frequency to calibrate without a configuration file */
    ColumnSpectra->setText(QString::number(defaultSpectra));
    ui->tableInfoMeasure->setCellWidget(0, 0, ColumnSpectra);
    ColumnFreq->setText(QString::number(defaultFreq));
    ui->tableInfoMeasure->setCellWidget(0, 1, ColumnFreq);

    /* If there is a value in the spectrometer, then adjust the frequency according to the resolution */
    double Freqresolution = 1000/ptrSpectrometers[SpectrometerNumber]->getIntegrationTime();

    /* Are the actual settings giving a frequency resolution lower than 1 Hz? */
    if(Freqresolution/4 < 1){

        /* Use 1 Hz as the minimum frequency to resolve */
        ConfigureMeasurement->freqToMeasure = 1;
        ColumnFreq->setText(QString::number(ConfigureMeasurement->freqToMeasure));
        FFTL.FrequencyF = ConfigureMeasurement->freqToMeasure;

        /* To resolve 1 Hz it only makes sense to use a maximum of 250 ms */
        devices2[0]->setIntegrationTime(250);
        ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(250);
        ConfigureMeasurement->integrationTime = 250;
        FFTL.IntTime = 250;

        /* Show message */
        showWarning("With your actual settings the resolution of integration time is maximum 250 ms with 1 Hz for W ", "");

    }else{

        /* Is the actual frequncy resolution lower than the default 4 Hz resolution? */
        if(Freqresolution/4 < 4){

            ConfigureMeasurement->freqToMeasure = Freqresolution/4;
            ColumnFreq->setText(QString::number(ConfigureMeasurement->freqToMeasure));
            FFTL.FrequencyF = ConfigureMeasurement->freqToMeasure;
        }else{

            /* If 4 Hz is ok according to the actual settings, then use this value */
            ConfigureMeasurement->freqToMeasure = defaultFreq;
            FFTL.FrequencyF = defaultFreq;
        }
    }

    /* Set all the variables to a defined value since there isn't configuration loaded */
    ConfigureMeasurement->numSpectra = defaultSpectra;
    ConfigureMeasurement->integrationTime = ptrSpectrometers[SpectrometerNumber]->getIntegrationTime();
    ConfigureMeasurement->numberOfAverages = ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages();

    /* For the class FFT, we also need this information to be updated from here (saves time) */
    FFTL.NrSpectra = defaultSpectra;
    FFTL.IntTime = ConfigureMeasurement->integrationTime;
    FFTL.ConcentrationC1 = 0;
    FFTL.ConcentrationC2 = 0;
}

/**
 * @brief Calibration Routine
 */
void PanelPolarimeter::Pol_Calibrate(void){

    /* How long takes the data acquisition? */
    int measuringTime = (ConfigureMeasurement->integrationTime*ConfigureMeasurement->numSpectra*ConfigureMeasurement->numberOfAverages/1000);

    /* What's the minimum time available for the spectrometer to measure and plot the data? plus a window for live raw data */
    int minimumLiveTime = measuringTime + measuringTime/3 + 12;

    /* Always plot at 10 measurement values */
    pol_plot->time_plot = minimumLiveTime*20;

    /* Change from ms on timer to just seconds of running the calibration */
    if(Runner->timerMS.elapsed()/1000 > Runner->Timer_In_Seconds){

        /* If user didn't change the frequency at all, then show old frequency value */
        if(!ColumnFreq->hasFocus() && OldFreqValue.toInt() == ConfigureMeasurement->freqToMeasure){

            /* Set back old value if there was any change */
            ColumnFreq->setText(OldFreqValue);
            OldFreqValue = "";
        }

        /* If user didn't change the frequency at all, then show old frequency value */
        if(!ColumnSpectra->hasFocus() && OldSpectraValue.toInt() == ConfigureMeasurement->numSpectra){

            /* Set back old value if there was any change */
            ColumnSpectra->setText(OldSpectraValue);
            OldSpectraValue = "";
        }


        /* Time in seconds */
        Runner->Timer_In_Seconds = Runner->Timer_In_Seconds + 1;

        /* Plot the Live averages */
        plotAverage();

        /* Count the time steps for measuring during the Live FFT calibration */
        Runner->liveFFT_Time = Runner->liveFFT_Time + 1;

        /* Progress of calibration */
        Runner->Calibration_Progress = Runner->Calibration_Progress + 1;

        ui->currentProgressBar_Pol->setValue(Runner->Calibration_Progress*100/(minimumLiveTime)); // Not 3, but then which number?

        /* Time break to do live Raw data plot */
        if (Runner->liveFFT_Time == minimumLiveTime-8 && !ptrSpectrometers[SpectrometerNumber]->isMeasuring()){

            /* Prepare for new measurement */
            if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
            {
                Runner->maxRawCounts =-1;
                /* If successful, start measurement */
                ptrSpectrometers[SpectrometerNumber]->startMeasurement(-2);

                /* Update information bar */
                ui->info->setText("Calibrating... Live Raw Signal");
            }
        }

        /* Is time to run the Live measurements for the calibration? */
        if (Runner->liveFFT_Time == minimumLiveTime-2 && Runner->liveFFT_Time!=0 && ptrSpectrometers[SpectrometerNumber]->isMeasuring())
        {

            /* Stop the raw data plotting */
            ptrSpectrometers[SpectrometerNumber]->stopMeasurement();

            /* Update information bar */
            ui->info->setText("Calibrating... Waiting for Spectrometer");
        }
    }

    /* Path to be in the search for the files; is always a subdirectory in the application path */
    QString path(QString("%1%2").arg(current, "data_polarimeter/"));

    fileInfo = QFileInfo(path);

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
            FFTL.NrSpectra = ConfigureMeasurement->numSpectra;
            FFTL.FrequencyF = ConfigureMeasurement->freqToMeasure;
            FFTL.IntTime = ConfigureMeasurement->integrationTime;
            FFTL.ConcentrationC1 = 0;
            FFTL.ConcentrationC2 = 0;

            /* Configure spectrometer */
            ptrSpectrometers[SpectrometerNumber]->setIntegrationTime(ptrSpectrometers[SpectrometerNumber]->getIntegrationTime());
            ptrSpectrometers[SpectrometerNumber]->setNumberOfAverages(ptrSpectrometers[SpectrometerNumber]->getNumberOfAverages());

            /* Prepare StoreToRAM measurement */
            ptrSpectrometers[SpectrometerNumber]->forceStoreToRAM(path, ConfigureMeasurement->numSpectra);
            if (ptrSpectrometers[SpectrometerNumber]->prepareMeasurement())
            {
                /* If the system is busy and the user stops the calibration, wait until it finishes what it's doing and then stop. */
                Runner->delayStop = true;

                /* Start the calibration similar as measuring for long time */
                ptrSpectrometers[SpectrometerNumber]->startMeasurement(2);

                /* Update information bar */
                ui->info->setText("Calibrating... Measuring Spectra");
            }
        }

        /* Reset the time for next Live FFT Measurement */
        Runner->liveFFT_Time = 0;
    }
}

/* OTHERS -------------------------------------------------------------------------------------------------------------------*/

/**
 * @brief Add to the List of Spectrometers in Polarimeter Tab the First Checked Spectrometer of the Preview List.
 * This function is called in Panel.cpp
 */
void PanelPolarimeter::SelectedSpectrometer_Polarimeter(void){

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
        devices2[0]->setClickableLabelsEnabled(false);
        devices2[0]->setName("");

    }else{
        /* Loop through devices */
        for (i = 0; i < m_NrDevices; i++)
        {
            if( ptrSpectrometers[i]->isEnabled()){

                /* Enable labels if there is any spectrometer */
                devices2[0]->setIsEnabled(true);
                devices2[0]->setClickableLabelsEnabled(true);
                devices2[0]->setIntegrationTime(ptrSpectrometers[i]->getIntegrationTime());
                devices2[0]->setNumberOfAverages(ptrSpectrometers[i]->getNumberOfAverages());

                /* Save the spectrometer in use if it's not the first*/
                SpectrometerNumber = i;

                /* Get the new spectrometer details */
                if (ptrSpectrometers[i]->hasReadableName())
                {
                    devices2[0]->setName(ptrSpectrometers[i]->getReadableName());
                }else{
                    devices2[0]->setName(ptrSpectrometers[i]->getSerialNumber());
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
 * @brief Enable polarimeter: If there is a selected spectrometer, then it´s added to the list of Polarimeter Tab.
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

    /* Enable labels from the spectrometer list */
    devices2[0]->ui->label_autoAdjust->setEnabled(activate);
    devices2[0]->ui->label_integrationTime->setEnabled(activate);
    devices2[0]->ui->label_numberOfAverages->setEnabled(activate);
    devices2[0]->ui->lineEdit_name->setEnabled(activate);
}

/**
 * @brief Closes everything when closing the app
 */
void PanelPolarimeter::quitOxymetry(){

    /* Just close all the running loops if the app was closed unexpected */
    if(m_NrDevices > 0 ){
        /* Abort everything */
        abort_everything = true;
    }
}

/**
 * @brief Measurement progress routine
 */
void PanelPolarimeter::Pol_MeasurementProgress(unsigned int i){

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
 * @brief Clean all the configuration, plots, everyhting restarted.
 */
void PanelPolarimeter::clean_AllPol(void){

    /* To run clearPlot function */
    dataloaded = true;

    /* Remove some items from the GUI loaded when needed */
    showUI_Item(false);

    /* Don't show total measurement bar */
    ui->TotalProgressBar_Pol->setVisible(false);
    ui->label_totalM->setVisible(false);
    ui->horizontalSpacer_Y->changeSize(20,12,QSizePolicy::Expanding,QSizePolicy::Fixed);
    ui->qwtPlot_Pol_Prediction->setVisible(false);
    ui->label_prediction->setVisible(false);
    ui->line_comp->setVisible(false);

    /* Restart FFT intensities plot */
    ui->qwtPlot_Pol_FFT->setAxisScale(QwtPlot::xBottom, 0, 21, 7);
    ui->qwtPlot_Pol_FFT->setAxisScale(QwtPlot::yLeft, 0, 3000, 1000);
    ui->qwtPlot_Pol_FFT->updateAxes();

    /* Show starting plots */
    ui->qwtPlot_Pol->setVisible(true);
    ui->qwtPlot_Pol_Average->setVisible(true);
    ui->qwtPlot_Pol_Compensation->setVisible(true);
    ui->qwtPlot_Pol_w_2w->setVisible(true);

    /* Show current progress bar*/
    ui->currentProgressBar_Pol->setVisible(false);

    /* Is there any information ploted already? */
    if(pol_plot->Average_DC_Signal!=nullptr)
    {
        curves_Pol[0]->detach();
    }

    /* Clear all other plots too */
    pol_plot->clean_AllPlots();

    ConfigureMeasurement->path = "";
    ConfigureMeasurement->ui->lineEdit_path->setText("Please select a configuration file");
    ConfigureMeasurement->cleanAll();
    ConfigureMeasurement->configured = false;

    /* Clear FFT plots */
    clearPlot();

    /* Clear Tables on display */
    ColumnFreq ->clear();
    ColumnSpectra->clear();

    /* Clear the configuration files profile table */
    for(int z =0; z<ConfigureMeasurement->fileName.length(); z++){
        ui->Table_Measurements_Pol->removeRow(0);
    }

    /* Nothing is running */
    Runner->setMeasurementRunning(false);
    Runner->setCalibrationRunning(false);

    /* Set all vectors to zero */
    FFTL.InitializeFFTArrays();

    /* Also restart plotting variables */
    pol_plot->time_plot = 300;
    ui->qwtPlot_Pol_Average->setXAxis(0, pol_plot->time_plot);

    /* Restart configuration */
    Runner->setConfigured(false);

    /* There is no data loaded anymore or any FFT data in UI */
    dataloaded = false;
    isFFTData = true;

    /* Update plots */
    ui->qwtPlot_Pol_Average->update();
    ui->qwtPlot_Pol_Average->updateLayout();
    ui->qwtPlot_Pol->update();

    /* General Timer in seconds */
    Runner->Timer_In_Seconds=0;

    /* Time busy with FFT */
    Runner->liveFFT_Time = 0;
    ui->currentProgressBar_Pol->setValue(0);
    Runner->Calibration_Progress = 0;

    /* Any saved values restarted */
    OldFreqValue = "";
    OldSpectraValue = "";

    /* Update information bar */
    ui->info->setText("");
}

/**
 * @brief Open help dialog
 */
void PanelPolarimeter::help(void){

    /* Disable push button of Non Modal window */
    ui->help->setEnabled(false);

    /* Open help dialog */
    helpDialog = new PanelPolHelp(this);

    /* Execute dialog */
    helpDialog->show();

    /* Was the windows closed already? */
    connect(helpDialog,SIGNAL(accepted()),this,SLOT(enableHelp()));
}

/**
 * @brief Enable Help: Slot for comunication with helpDialog
 */
void PanelPolarimeter::enableHelp(void){

    /* Enable push button of Non Modal window */
    ui->help->setEnabled(true);

    /* Free memory */
    delete helpDialog;
    helpDialog = nullptr;
}

/**
 * @brief Destructor of 'Polarimeter' class
 */
PanelPolarimeter::~PanelPolarimeter(void)
{

    /* Check handle */
    if (nullptr != curves_Pol[0])
    {
        /* Detach curve */
        curves_Pol[0]->detach();

        /* Free memory */
        delete curves_Pol[0];
        curves_Pol[0] = nullptr;
    }

    /* Free objects memory */
    delete pol_plot;
    pol_plot = nullptr;

    delete ColumnSpectra;
    ColumnSpectra = nullptr;

    delete ConfigureMeasurement;
    ConfigureMeasurement = nullptr;

    delete ColumnFreq ;
    ColumnFreq = nullptr;

    /* Delete user interface */
    delete ui;
}
