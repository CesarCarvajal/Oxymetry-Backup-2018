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

/* Panel stuff */
#include <QWidget>

/* Qwt library */
#include "qwt_plot_curve.h"
#include "math_helper.h"

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
#include "pol_measurements.h"

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

private:

    /* Load configuration class */
    configurePolMeasure *ConfigureMeasurement;

    /* Help Dialog object */
    PanelPolHelp* helpDialog;

    /* Measurements Object */
    Pol_Measurements *Runner = nullptr;

    /* Connected devices */
    PanelItem_Pol * PolarimetrySpectrometer;
    QwtPlotCurve * curve_Pol;

    /* Signal mapper */
    QSignalMapper *signalMapper;

    /* FFT Object */
    fft FFTL;

    /* Plot Objetct */
    Pol_Plot *PolPlotter = nullptr;

    /* Widget container for 3D plot */
    QWidget *container, *container_norm;

    /* Start measurement button color */
    QString greenButton = "color: rgb(0,128,0)", RedButton = "color: rgb(250,0,0)", grayButton = "color: rgb(211,211,211)";

    /* The configuration was edited during the calibration?*/
    bool editedConf;

private:

    /* Get current path to executable */
    QString currentWorkingPath;

    /* If this changes, then quit everything */
    bool abort_everything;

    /* The number of the spectrometer in use for polarimeter */
    int SpectrometerNumber;

    /* Distinguish between raw and fft data */
    bool isFFTData;

    /* Was there data loaded? */
    bool dataloaded;

    /* Since there is a lot of data to handle, we use files to save it temporarily */
    QFileInfo fileInfoSaving;

    /* Elapsed time for the measurements */
    int totalMeasuretime;

    /* File information for the temporal file of calibration */
    QFileInfo fileInfoCalibration;

    /* File loading information */
    QFileInfo fileInfoLoad;

    /* Path given by the user to load files */
    QString UserLoadDataPath;

    /* Folder where the data will be saved */
    QString folderForData;

    /* Fix the X axis zoom problem */
    double minXAverage, maxXAverage, maxYRaw, maxYAverage;

public:

    /* Updates user interface */
    void update();

    /* Disable/enable polarimeter */
    void enable_Polarimeter_Measurement(bool activate);

    /* Destructor */
    ~PanelPolarimeter(void);

private slots:

    /* Show needed items of UI */
    void showUI_Item(bool UIstatus);

    /* Get the number of the current spectrometer in Polarimeter */
    void selected_Spectrometer_Pol(void);

    /* Open help dialog */
    void help_Pol(void);

    /* Change Nr of averages during calibration */
    void change_Number_Averages_Pol(void);

    /* Change the Frequency during calibration */
    void change_Frequency_Pol(void);

    /* Change the Number of Spectra during calibration */
    void change_Number_Spectra_Pol(void);

    /* Change the wavelength to show in the FFT */
    void change_Wavelength_FFT_Pol(void);

    /* Change the Integration time from the auto adjusted during calibration */
    void change_Auto_Integration_Time_Pol(void);

    /* Load measurement summary */
    void Load_Summary(void);

    /* Write measurement summary */
    void write_Summary();

    /* Change the Integration time manually during calibration */
    void change_Integration_Time_Pol(void);

    /* Show initial plots UI */
    void showAllPlots();

    /* Clean all the configuration, plots, etc */
    void clean_All_Pol(void);

    /* Initialize the Calibration */
    void initialize_Calibration(void);

    /* Display the progress on measurement */
    void pol_Measurement_Progress(unsigned int i);

    /* Do calibration routine */
    void pol_Calibrate(void);

    /* Do Measurement routine */
    void pol_Measure(void);

    /* Initialize a calibration without a configuration file loaded */
    void initialize_Default_Calibration(void);

    /* Adjust time plotting in live averages */
    void adjust_Average_Plot_Time(void);

    /* Adjust the Integration Time */
    void adjust_Integration_Time_Pol(void);

    /* Functions for spectrometer items */
    void handle_Click_Event(QWidget *widget);

    /* Called if new data signal arrived */
    void receive_Data_Pol(int WParam, int LParam);

    /* Select start or stop a measurement */
    void toggle_Pol_Measurement(void);

    /* Change file names for measurement */
    void change_File_Name(void);

    /* Write the raw data counts to a file */
    void write_To_File(FILE *file, double *a_pSpectrum, int WParam);

    /* Close any open loop in the polarimeter tab */
    void quit_Oxymetry(void);

    /* FFT file to load and visualize */
    void Load_From_FFT(void);

    /* Raw Data file to load and visualize */
    void Load_From_Raw_Data(void);

    /* Configuration of Measurements for Polarimeter */
    void conf_Setup_Pol_Measurement(void);

    /* Select the data to be analized */
    void select_Analize_Pol_Measurement(void);

    /* The user wants to calibrate before to start the measurement */
    void toggle_Pol_Calibration(void);

    /* Run the spectrometer */
    void run_Polarimetry(short runType);

    /* Stop running the spectrometer */
    void stop_Run_Polarimetry(void);

    /* Select what kind of data should be loaded */
    void toggle_Load_Data(void);

    /* Plot FFT */
    void plot_FFT(void);

    /* Clear Plots */
    void clear_Plot(void);

    /* Save graphs as PDF in Polarimeter */
    void save_Graph_Pol(void);

    /* Plot Averages */
    void plot_Average(void);

    /* Adjust the polarimeter tab running start */
    void adjust_Run_Start(short int typeRun);

    /* Adjust the polarimeter tab running End */
    void adjust_Run_End(void);

    /* Adjust the folder where the measurments data is going to be saved */
    void adjust_Measurements_Saving_Folder(void);

    /* Process the received data from the spectrometer */
    void process_Received_Data_Pol(QString Path);

    /* Delay the measurememts */
    void delay_Pol_Measurements(void);

    /* Change the wavelengths range according to the user selection */
    void update_Wavelength_Range(void);

    /* Adjust the wavelengths range */
    void adjust_Wavelength_Range(void);

    /* Normalize Counts */
    void normalizeCounts(void);

    /* Save instant spectra from calibration */
    void saveFFTcalibration(void);

public slots:

    /* Enable Help Non Modal Window */
    void enable_Help_Pol();

    /* Set configured values */
    void setConfiguration(void);

signals:

    /* Signal to update other tabs */
    void updateTabs();

    /* If there is a polarimeter measurement or calibration, disable other measurement buttons */
    void DisEnablePreview(bool);

};

#endif // POL_PANEL_H
