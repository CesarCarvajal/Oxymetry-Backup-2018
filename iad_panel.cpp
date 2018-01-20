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

/* Needed for Avantes AvaSpec library */
#define USE_POSTMESSAGE

/*
 * External includes
 */

/* Qt libraries */
#include <QSettings>
#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSignalMapper>
#include <QApplication>
#include <QMessageBox>
#include <QFileInfo>
#include <QCheckBox>
#include <QIcon>
#include <QElapsedTimer>
#include <QDateTime>
#include <QFileDialog>
#include <QTimer>
#include <QThread>
#include <QStringRef>
#include <QDir.h>

/* Avantes AvaSpec library */
#include "avaspec.h"

/* Qwt library */
#include "qwt_plot_curve.h"

/*
 * Internal includes
 */

/* General stuff */
#include "application.h"
#include "messages.h"
#include "math_helper.h"

/* Inverse Adding-Doubling */
#include "iad_configure.h"
#include "iad_calibrate.h"
#include "iad_measure.h"

/* Panel elements */
#include "iad_panel.h"

/* Spectrometer control */
#include "spectrometer.h"

/* User interface */
#include "ui_iad_panel.h"


/*
 * Global variables
 */
extern QSettings *settings;
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;


/**
 * @brief Constructor of 'Panel' class
 */
PanelIAD::PanelIAD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PanelIAD)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Window);

    /* Set axis and title of the normalized intensity plots */
    ui->qwtPlot_reflection->setXAxisTitle("Wavelength in nm");
    ui->qwtPlot_reflection->setYAxisTitle("Normalized intensity");
    ui->qwtPlot_reflection->setCaption("Normalized reflection");
    ui->qwtPlot_reflection->setYAxis(0.0, 1.0);
    ui->qwtPlot_transmission->setXAxisTitle("Wavelength in nm");
    ui->qwtPlot_transmission->setYAxisTitle("Normalized intensity");
    ui->qwtPlot_transmission->setCaption("Normalized transmission");
    ui->qwtPlot_transmission->setYAxis(0.0, 1.0);

    /* Defaults values for x-axis are 400 to 1000 nm */
    double minWavelength = 400.0, maxWavelength = 1000.0;

    /* Are there any spectrometers connected? */
    if (m_NrDevices > 0)
    {
        double startWavelengths[m_NrDevices], stopWavelengths[m_NrDevices];

        unsigned int i = 0;

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
    }

    /* Update x-axis of graphs */
    ui->qwtPlot_reflection->setXAxis(minWavelength, maxWavelength);
    ui->qwtPlot_transmission->setXAxis(minWavelength, maxWavelength);

    /* Create curves for normalized intensities */
    M_R = new QwtPlotCurve("Diffuse reflection");
    M_T = new QwtPlotCurve("Diffuse transmission");
    M_U = new QwtPlotCurve("Unscattered transmission");

    /* Configure curves */
    M_R->setPen(QPen("blue"));
    M_R->attach(ui->qwtPlot_reflection);
    M_T->setPen(QPen("red"));
    M_T->attach(ui->qwtPlot_transmission);
    M_U->setPen(QPen("green"));
    M_U->attach(ui->qwtPlot_transmission);

    /*
     * Connect and configure the Inverse Adding-Doubling stuff
     */

    /* Connect buttons in Inverse Adding-Doubling tab */
    connect(ui->button_iad_newConfiguration, SIGNAL(clicked()), this, SLOT(newConfigurationIAD()));
    connect(ui->button_iad_openConfiguration, SIGNAL(clicked()), this, SLOT(openConfigurationIAD()));
    connect(ui->button_iad_calibrate, SIGNAL(clicked()), this, SLOT(calibrateIAD()));
    connect(ui->button_iad_measure, SIGNAL(clicked()), this, SLOT(measureIAD()));
    connect(ui->checkBox_iad_liveView, SIGNAL(clicked(bool)), this, SLOT(liveViewIAD()));

    /* No configuration file loaded by default */
    ui->label_iad_configurationName->setText(QString("No configuration loaded"));
    ui->label_iad_configurationName->setStyleSheet("QLabel { color: red; text-decoration: none; }");
    ui->label_iad_configurationName->setCursor(QCursor(Qt::ArrowCursor));

    //ui->table_iad_measurements->setup();
}

/**
 * @brief Updates user interface
 */
void PanelIAD::update(void)
{
    // To do
}

/**
 * @brief Updates the graph
 */
void PanelIAD::updateGraphs(void)
{
    /* Update the graphs */
    ui->qwtPlot_reflection->update();
    ui->qwtPlot_transmission->update();
}

/**
 * @brief Creates new configuration for IAD method
 */
void PanelIAD::newConfigurationIAD(void)
{
    /*
     * Runs the IAD configuration assistant. No file name will be delivered, so all settings
     * are set to default values. Finally these settings are saved in a configuration file.
     */
    ConfigureIAD assistant(NULL);

    /* Checks if IAD configuration was successful */
    if (assistant.getIsConfigured())
    {
        /* Get path and name of configuration file */
        configPath = assistant.getConfigurationName();
        QFileInfo fileInfo = configPath;
        QString fileName = fileInfo.baseName();

        unsigned int i = 0;

        /* Loop through devices */
        for (i = 0; i < m_NrDevices; i++)
        {
            /* Update name in preview from serial number to readable name */
//            devices[i]->setName(ptrSpectrometers[i]->getReadableName());
        }

        /* Process configuration data and update buttons */
        ui->label_iad_configurationName->setText(fileName);
        ui->label_iad_configurationName->setStyleSheet("QLabel { color: blue; text-decoration: underline; }");
        ui->label_iad_configurationName->setCursor(QCursor(Qt::PointingHandCursor));

        /* Enable IAD calibration */
        ui->button_iad_calibrate->setEnabled(true);
        ui->button_iad_measure->setEnabled(false);

        /* Mouse click on label should show IAD configuration */
        connect(ui->label_iad_configurationName, SIGNAL(clicked()), this, SLOT(showConfigurationIAD()));
    }
    else
    {
        /* Process configuration data and update buttons */
        ui->label_iad_configurationName->setText(QString("No configuration loaded"));
        ui->label_iad_configurationName->setStyleSheet("QLabel { color: red; text-decoration: none; }");
        ui->label_iad_configurationName->setCursor(QCursor(Qt::ArrowCursor));

        /* Disable IAD calibration */
        ui->button_iad_calibrate->setEnabled(false);
        ui->button_iad_measure->setEnabled(false);

        /* Mouse click on label should not result in any action */
        disconnect(ui->label_iad_configurationName, SIGNAL(clicked()), this, 0);
    }
}

/**
 * @brief Opens configuration for IAD method
 */
void PanelIAD::openConfigurationIAD(void)
{
    /* Let the user choose the configuration file */
    configPath = QFileDialog::getOpenFileName(this, QString("Open Raw Data file"), "./config", QString("Configuration file (*.cfg)"));

    /* File selected by user? */
    if (NULL == configPath)
    {
        /* No file selected. Dialog aborted. */
        return;
    }

    /*
     * Runs the IAD configuration assistant. The file name of the selected configuration file
     * will be delivered; all settings are loaded from the configuration file. Any changes will
     * be saved into the configuration file.
     */
    ConfigureIAD assistant(configPath);

    /* Checks if IAD configuration was successful */
    if (assistant.getIsConfigured())
    {
        /* Get path and name of configuration file */
        QFileInfo fileInfo = configPath;
        QString fileName = fileInfo.baseName();

        unsigned int i = 0;

        /* Loop through devices */
        for (i = 0; i < m_NrDevices; i++)
        {
            /* Update name in preview from serial number to readable name */
//            devices[i]->setName(ptrSpectrometers[i]->getReadableName());
        }

        /* Process configuration data and update buttons */
        ui->label_iad_configurationName->setText(fileName);
        ui->label_iad_configurationName->setStyleSheet("QLabel { color: blue; text-decoration: underline; }");
        ui->label_iad_configurationName->setCursor(QCursor(Qt::PointingHandCursor));

        /* Enable IAD calibration */
        ui->button_iad_calibrate->setEnabled(true);
        ui->button_iad_measure->setEnabled(false);

        /* Mouse click on label should show IAD configuration */
        connect(ui->label_iad_configurationName, SIGNAL(clicked()), this, SLOT(showConfigurationIAD()));
    }
    else
    {
        /* Process configuration data and update buttons */
        ui->label_iad_configurationName->setText(QString("No configuration loaded"));
        ui->label_iad_configurationName->setStyleSheet("QLabel { color: red; text-decoration: none; }");
        ui->label_iad_configurationName->setCursor(QCursor(Qt::ArrowCursor));

        /* Disable IAD calibration */
        ui->button_iad_calibrate->setEnabled(false);
        ui->button_iad_measure->setEnabled(false);

        /* Mouse click on label should not result in any action */
        disconnect(ui->label_iad_configurationName, SIGNAL(clicked()), this, 0);
    }
}

/**
 * @brief Shows configuration for IAD method
 */
void PanelIAD::showConfigurationIAD(void)
{
    /*
     * Runs the IAD configuration assistant. The file name of the currently loaded configuration
     * file will be delivered; all settings are loaded from the configuration file. Any changes will
     * be saved into the configuration file.
     */
    ConfigureIAD assistant(configPath);
}

/**
 * @brief Do calibration for IAD method
 */
void PanelIAD::calibrateIAD(void)
{
    /* Stop preview and disable buttons */

    CalibrateIAD assistant(Rd_factor, Td_factor, Tu_factor);

    /* Get status of calibration */
    bool isCalibrated = assistant.getIsCalibrated();

    /* Process assistant data and update buttons */
    ui->button_iad_measure->setEnabled(isCalibrated);
    ui->checkBox_iad_liveView->setEnabled(isCalibrated);
    ui->lineEdit_iad_name->setEnabled(isCalibrated);
    ui->plainTextEdit_iad_description->setEnabled(isCalibrated);

    /* Re-enable buttons */
}

/**
 * @brief Do measurement for IAD method
 */
void PanelIAD::measureIAD(void)
{
    /* Check for measurement name */
    if (ui->lineEdit_iad_name->text().isEmpty())
    {
        /* Show message */
        showWarning(QString("You have to enter a name for the measurement."), QString(""));
        return;
    }

    /* Disable 'Measure' button */
    ui->button_iad_measure->setEnabled(false);

    /* Stop preview and disable buttons */

    MeasureIAD assistant;

    /* Set measurement name and description */
    assistant.setName(ui->lineEdit_iad_name->text());
    assistant.setDescription(ui->plainTextEdit_iad_description->toPlainText());

    /* Run measurement */
    if (assistant.measure())
    {
        /* Measurement successful */
        assistant.save(NULL);

        /* Add current measurement to list of measurements */
        ui->table_iad_measurements->add(assistant.getName(), ui->lineEdit_iad_name->text(),
                                        assistant.getDate(), assistant.getTime());
    }

    /* Re-enable buttons */
}

void PanelIAD::liveViewIAD(void)
{
    if (ui->checkBox_iad_liveView->isChecked())
    {
        //startPreview();
    }
    else
    {
        //stopPreview();
    }
}

/**
 * @brief Destructor of 'PanelIAD' class
 */
PanelIAD::~PanelIAD(void)
{
    /* Does M_R curve exists? */
    if (nullptr != M_R)
    {
        /* Detach curve */
        M_R->detach();

        /* Free memory */
        delete M_R;
        M_R = nullptr;
    }

    /* Does M_T curve exists? */
    if (nullptr != M_T)
    {
        /* Detach curve */
        M_T->detach();

        /* Free memory */
        delete M_T;
        M_T = nullptr;
    }

    /* Does M_U curve exists? */
    if (nullptr != M_U)
    {
        /* Detach curve */
        M_U->detach();

        /* Free memory */
        delete M_U;
        M_U = nullptr;
    }

    /* Delete user interface */
    delete ui;
}
