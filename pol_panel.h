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

#ifndef POL_PANEL_H
#define POL_PANEL_H

/*
 * External includes
 */

/* Qt includes */
#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSignalMapper>
#include <QList>
#include <QTimer>
#include <QLineEdit>
#include <QCloseEvent>
#include <QElapsedTimer>

/* Panel stuff */
#include <QWidget>

/* Qwt library */
#include "qwt_plot_curve.h"
#include "math_helper.h"
#include "timer.h"


/*
 * Internal includes
 */

/* General stuff */
#include "pol_plot.h"
#include "pol_panelItem.h"
#include "pol_configureMeasurement.h"
#include "ui_pol_panel.h"
#include "pol_fft.h"
#include "pol_panelHelp.h"

/*
 * Other stuff
 */

namespace Ui {
class PanelPolarimeter;
}

/**
 * @brief The 'Polarimeter' class
 */
class PanelPolarimeter : public QWidget
{
    Q_OBJECT

public:

    /* Constructor */
    explicit PanelPolarimeter(QWidget *parent = 0);

    /* User interface */
    Ui::PanelPolarimeter *ui;

    /* Updates user interface */
    void update();

    /* Disable/enable polarimeter */
    void enable_Polarimeter_Measurement(bool activate);

    /* Get the number of the current spectrometer in Polarimeter */
    void SelectedSpectrometer_Polarimeter(void);

    /* Show needed items of UI */
    void showUI_Item(bool UIstatus);

    /* Destructor */
    ~PanelPolarimeter(void);

private slots:

    /* Open help dialog */
    void help(void);

    /* Restart important calibration parameters */
    void restart_CalibrationPol(void);

    /* Change Nr of averages during calibration */
    void change_NrAveragesPol(void);

    /* Change the Frequency during calibration */
    void change_FrequencyPol(void);

    /* Change the Number of Spectra during calibration */
    void change_NrSpectraPol(void);

    /* Change the wavelength to show in the FFT */
    void change_WaveFFTPol(void);

    /* Change the Integration time from the auto adjusted during calibration */
    void change_AutoIntegrationTimePol(void);

    /* Change the Integration time manually during calibration */
    void change_IntegrationTimePol(void);

    /* Clean all the configuration, plots, etc */
    void clean_AllPol(void);

    /* Initialize the Calibration */
    void initializeCalibration(void);

    /* Display the progress on measurement */
    void Pol_MeasurementProgress(unsigned int i);

    /* Do calibration routine */
    void Pol_Calibrate(void);

    /* Initialize a calibration without a configuration file loaded */
    void initializeDefaultCalibration(void);

    /* Adjust time plotting in live averages */
    void Adjust_AveragePlotTime();

    /* Adjust the Integration Time */
    void adjustIntegrationTimePol();

    /* Functions for spectrometer items */
    void handleClickEvent(QWidget *widget);

    /* Called if new data signal arrived */
    void ReceiveDataIsHerePol(int WParam, int LParam);

    /* Select start or stop a measurement */
    void toggle_Pol_Measurement(void);

    /* Change file names for measurement */
    void changeFileName(void);

    /* Write the raw data counts to a file */
    void writeToFile(FILE *file, double *a_pSpectrum, int WParam);

    /* Close any open loop in the polarimeter tab */
    void quitOxymetry();

    /* FFT file to load and visualize */
    void LoadFromFFT(void);

    /* Raw Data file to load and visualize */
    void LoadFromRawData(void);

    /* Configuration of Measurements for Polarimeter */
    void ConfSetup_Pol_Measurement(void);

    /* The user wants to calibrate before to start the measurement */
    void toggle_Pol_Calibration(void);

    /* Run the spectrometer */
    void Run_Polarimetry(short runType);

    /* Stop running the spectrometer */
    void Stop_Run_Polarimetry();

    /* Select what kind of data should be loaded */
    void toggle_LoadData(void);

    /* Plot FFT */
    void Plot_FFT(void);

    /* Clear Plots */
    void clearPlot(void);

    /* Save graphs as PDF in Polarimeter */
    void saveGraph_Pol(void);

    /* Plot Averages */
    void plotAverage(void);

private:

    QSignalMapper *signalMapper;

    /* Since there is a lot of data to handle, we use files to save it temporarily */
    QFileInfo fileInfo;

    /* Path given by the user to load files */
    QString DataPath;

    /* Distinguish between raw and fft data */
    bool isFFTData = true;

    /* Was there data loaded? */
    bool dataloaded = false;

    /* Stop the calibration in the right time */
    bool delayStop, delayedStop = false;

    /* Stop calibration and restart it after any change */
    bool change = false;

    /* FFT Object */
    fft FFTL;

    /* Plot Objetct */
    Pol_Plot *pol_plot = nullptr;

    /* Variables to count time and plot the real time averages */
    int time_plot=300;

    /* General Timer in seconds */
    int time_seconds=0;

    /* Time busy with FFT */
    int doliveFFT = 0;

    /* Range of Wavelengths */
    double minWavelength = 400.0, maxWavelength = 1000.0;

    /* Show raw signal also when long term measuring running */
    bool showRaw = false;
    double maxCounts = -1;

    QString greenButton = "color: rgb(0,128,0)", RedButton = "color: rgb(250,0,0)", grayButton = "color: rgb(211,211,211)";

    /* Saves old values of frequency or Nr Spectra from labels in calibration */
    QString OldFreqValue, OldSpectraValue = "";

    /* Local Timer */
    QElapsedTimer timer;

public:

    QList<PanelItem_Pol *> devices2;
    QList<QwtPlotCurve *> curves_Pol;

    /* Are we measuring or calibrating? */
    bool PolMeasurementRunning = false;
    bool PolCalibrationRunning = false;

    /* The number of the spectrometer in use for polarimeter */
    int SpectrometerNumber = 0;

    /* Was there a configuration profile for the measurement loaded? */
    bool measurement_Pol_profileLoaded = false;

    /* When calibrating we don't need to save all this data, so just use a temporal file deleted at the end of the calibration */
    QString TempFileName;

    /* When doing changes, we have to know when it's busy doing the live FFT */
    bool doingLiveFFT = false;

    /* The user modifies this when calibrating */
    QLineEdit *ColumnSpectra = new QLineEdit();
    QLineEdit *ColumnFreq = new QLineEdit();

    /* Load configuration class */
    configurePolMeasure ConfigureMeasurement;

    /* If this changes, then quit everything */
    bool abort_everything = false;

    /* Calibration progress */
    int Cal_progress = 0;

    /* Help Dialog object */
    PanelPolHelp* helpDialog;

public slots:

    /* Enable Help Non Modal Window */
    void enableHelp();

signals:

    /* Signal to update other tabs */
    void updateTabs();

    /* If there is a polarimeter measurement or calibration, disable other measurement buttons */
    void DisEnablePreview(bool);

};

#endif // POL_PANEL_H