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

/* External includes */
#include <QWidget>
#include <QString>

/* Internal includes */
#include "pol_panelItem.h"
#include "ui_pol_panelItem.h"

/**
 * @brief Constructor of 'PanelItem_Pol' class
 * @param parent
 * @param name
 * @param color
 */
PanelItem_Pol::PanelItem_Pol(QWidget *parent, QString name) :
    QWidget(parent),
    ui(new Ui::PanelItem_Pol)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Set to default, adjust progress bar */
    ui->lineEdit_name->setText(name);
    ui->lineEdit_name->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    ui->label_integrationTime->setStyleSheet("QLabel { color: blue; }");
    ui->label_setWranges->setStyleSheet("QLabel { color: blue; }");
    ui->label_frequency->setStyleSheet("QLabel { color: blue; }");
    ui->label_Nspectra->setStyleSheet("QLabel { color: blue }");
    ui->label_autoAdjust->setStyleSheet("QLabel { color: blue; }");
    ui->label_numberOfAverages->setStyleSheet("QLabel { color: blue; }");
    ui->label_saturatedPixels->setText(QString("Not saturated"));
    ui->label_saturatedPixels->setStyleSheet(QString("color: green; font: bold;"));
    ui->label_ActiveSpec_Pol->setText(QString("Active Spectrometer:"));
    ui->label_ActiveSpec_Pol->setStyleSheet(QString("color: green; font: bold;"));
}

/**
 * @brief Sets name of panel item
 * @param name Name of panel item
 */
void PanelItem_Pol::setName(QString name)
{
    ui->lineEdit_name->setText(name);
}

/**
 * @brief Gets integration time
 * @return Integration time in milliseconds
 */
float PanelItem_Pol::getIntegrationTime(void)
{
    return integrationTime;
}

/**
 * @brief Sets the wavelength range
 * @param[in] String with the range as text
 */
void PanelItem_Pol::setWavelengthRange(double min, double max)
{
    /* minimum */
    minimumWavelength = min;

    /* maximum */
    maximumWavelength = max;

    /* Set label text */
    ui->label_setWranges->setText(QString::number(minimumWavelength) + " - " + QString::number(maximumWavelength));
}


/**
 * @brief Sets the number of Spectra
 * @param[in] Integer with the number of spectra
 */
void PanelItem_Pol::setNumberOfSpectra(int NSpectra){

    numberOfSpectra = NSpectra;

    /* Set number of Spectra label value */
    ui->label_Nspectra->setText(QString::number(numberOfSpectra));

}

/**
 * @brief Sets the frequency for the measurements
 * @param[in] Integer with the frequency
 */
void PanelItem_Pol::setFrequency(int Frequency){

    frequency = Frequency;

    /* Set number of Spectra label value */
    ui->label_frequency->setText(QString::number(frequency));

}

/**
 * @brief Enable components
 * @param[in] Bool enable or not
 */
void PanelItem_Pol::enableComponents(bool value)
{
    /* Enable device parameters */
    ui->label_autoAdjust->setEnabled(value);
    ui->label_integrationTime->setEnabled(value);
    ui->label_setWranges->setEnabled(value);
    ui->label_numberOfAverages->setEnabled(value);
    ui->label_frequency->setEnabled(value);
    ui->label_Nspectra->setEnabled(value);
    ui->checkBox_normalize->setEnabled(value);

    /* Change how they look for editing */
    if(value){

        /* Change to editable */
        ui->label_integrationTime->setFrameShape(QFrame::StyledPanel);
        ui->label_setWranges->setFrameShape(QFrame::StyledPanel);
        ui->label_numberOfAverages->setFrameShape(QFrame::StyledPanel);
        ui->label_frequency->setFrameShape(QFrame::StyledPanel);
        ui->label_Nspectra->setFrameShape(QFrame::StyledPanel);

    }
    else{

        /* Change to non editable */
        ui->label_integrationTime->setFrameShape(QFrame::NoFrame);
        ui->label_setWranges->setFrameShape(QFrame::NoFrame);
        ui->label_numberOfAverages->setFrameShape(QFrame::NoFrame);
        ui->label_frequency->setFrameShape(QFrame::NoFrame);
        ui->label_Nspectra->setFrameShape(QFrame::NoFrame);
    }
}

/**
 * @brief Sets integration time
 * @param[in] value Integration time in milliseconds
 */
void PanelItem_Pol::setIntegrationTime(float value)
{
    /* Remember integration time */
    integrationTime = value;

    /* Is our integration time less than one millisecond? */
    if (value <= 1.0f)
    {
        /* Convert from ms to µs */
        value *= 1000.0f;

        /* Update time base to µs */
        ui->label_timeBase->setText(QString("µs"));
    }
    /* Is our integration time greater than one second? */
    else if (value >= 1000.0f)
    {
        /* Convert from ms to s */
        value /= 1000.0f;

        /* Update time base to s */
        ui->label_timeBase->setText(QString("s"));
    }
    else
    {
        /* Ensure time base is set to ms */
        ui->label_timeBase->setText(QString("ms"));
    }

    /* Update adjusted integration time */
    ui->label_integrationTime->setText(QString::number(value));
}

/**
 * @brief Gets number of averages
 * @return Number of averages
 */
int PanelItem_Pol::getNumberOfAverages(void)
{
    return numberOfAverages;
}

/**
 * @brief Gets the minimum wavelength
 * @return Minimum wavelength
 */
double PanelItem_Pol::getMinimumWavelength(void)
{
    return minimumWavelength;
}

/**
 * @brief Gets the maximum wavelength
 * @return Maximum wavelength
 */
double PanelItem_Pol::getMaximumWavelength(void)
{
    return maximumWavelength;
}

/**
 * @brief Gets number of Spectra
 * @return Number of Spectra
 */
int PanelItem_Pol::getNumberOfSpectra(void)
{
    return numberOfSpectra;
}

/**
 * @brief Gets frequency
 * @return Frequency
 */
int PanelItem_Pol::getFrequency(void)
{
    return frequency;
}

/**
 * @brief Sets number of averages
 * @param[in] value Number of averages
 */
void PanelItem_Pol::setNumberOfAverages(int value)
{
    numberOfAverages = value;

    /* Update label */
    ui->label_numberOfAverages->setText(QString::number(value));
}

/**
 * @brief Gets saturated status
 * @return TRUE if saturated, else FALSE
 */
bool PanelItem_Pol::getIsSaturated(void)
{
    return isSaturated;
}

/**
 * @brief Sets saturated status
 * @param value TRUE if saturated, else FALSE
 */
void PanelItem_Pol::setIsSaturated(bool value)
{
    /* Only update if necessary */
    if (isSaturated != value)
    {
        /* Change value */
        isSaturated = value;

        /* Update label */
        ui->label_saturatedPixels->setText(QString(value ? "Saturated" : "Not saturated"));
        ui->label_saturatedPixels->setStyleSheet(QString(value ? "color: red; font: bold;" : "color: green; font: bold;"));
    }
}

/**
 * @brief Gets enabled status
 * @return TRUE if enabled, else FALSE
 */
bool PanelItem_Pol::getIsEnabled(void)
{
    return isEnabled;
}

/**
 * @brief Sets enabled status
 * @param value TRUE if enabled, else FALSE
 */
void PanelItem_Pol::setIsEnabled(bool value)
{
    /* Value has changed? */
    if (isEnabled != value)
    {
        /* Update GUI elements */
        ui->lineEdit_name->setEnabled(value);

        /* Remember new value */
        isEnabled = value;
    }
}

/**
 * @brief Enable clickable labels
 * @param[in] value TRUE enables labels, FALSE disables labels
 */
void PanelItem_Pol::setClickableLabelsEnabled(bool value)
{
    /* Enable/disable labels */
    ui->label_integrationTime->setEnabled(value);
    ui->label_numberOfAverages->setEnabled(value);
    ui->label_setWranges->setEnabled(value);
    ui->label_frequency->setEnabled(value);
    ui->label_Nspectra->setEnabled(value);

    /* Set label stylesheets */
    ui->label_integrationTime->setStyleSheet(value ? "QLabel { color: blue; }" : "QLabel { color: grey; }");
    ui->label_numberOfAverages->setStyleSheet(value ? "QLabel { color: blue; }" : "QLabel { color: grey; }");
    ui->label_setWranges->setStyleSheet(value ? "QLabel { color: blue; }" : "QLabel { color: grey; }");
    ui->label_frequency->setStyleSheet(value ? "QLabel { color: blue; }" : "QLabel { color: grey; }");
    ui->label_Nspectra->setStyleSheet(value ? "QLabel { color: blue; }" : "QLabel { color: grey; }");

    ui->label_ActiveSpec_Pol->setText(QString(value ? "Active Spectrometer:" : "Select a Spectrometer from Preview List"));
    ui->lineEdit_name->setVisible(value ? true : false);
    ui->label_ActiveSpec_Pol->setStyleSheet(QString(value ? "color: green; font: bold;" : "color: red; font: bold;"));
    ui->label_saturatedPixels->setVisible(value);
    ui->label_Status->setVisible(value);
    ui->label_integrationTime->setVisible(value);
    ui->label_setWrange->setVisible(value);
    ui->label_setWrange2->setVisible(value);
    ui->label_setWranges->setVisible(value);
    ui->label_numberOfAverages->setVisible(value);
    ui->label_autoAdjust->setVisible(value);
    ui->label->setVisible(value);
    ui->label_2->setVisible(value);
    ui->label_timeBase->setVisible(value);
    ui->checkBox_normalize->setVisible(value);
    ui->label_normalize->setVisible(value);
    ui->label_frequency->setVisible(value);
    ui->label_freq2->setVisible(value);
    ui->label_freq3->setVisible(value);
    ui->label_Nspectra->setVisible(value);
    ui->label_Nspectra2->setVisible(value);

}

/**
 * @brief Destructor of 'PanelItem_Pol' class
 */
PanelItem_Pol::~PanelItem_Pol(void)
{
    /* Delete user interface */
    delete ui;
}
