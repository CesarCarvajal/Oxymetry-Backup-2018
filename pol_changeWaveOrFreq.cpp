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
#include <QDialog>
#include <QString>
#include <QTimer>

/* Internal includes */
#include "pol_changeWaveOrFreq.h"
#include "ui_pol_changeWaveOrFreq.h"

/**
 * @brief Constructor of 'PanelChangeWaveOrFreq' class
 * @param parent
 */
PanelChangeWaveOrFreq::PanelChangeWaveOrFreq(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PanelChangeWaveOrFreq)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Set window flags */
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);

    /* Get keyboard focus */
    QTimer::singleShot(0, this, SLOT(activateWindow()));

    /* Connect button signal handles */
    connect(ui->button_apply, SIGNAL(clicked(bool)), this, SLOT(applyButton()));
}

/**
 * @brief Get wavelength
 * @return index of the wavelength in array
 */
int PanelChangeWaveOrFreq::getValue(void)
{
    /* Get the value on list */
    return ui->WaveList->currentIndex();
}

/**
 * @brief Get frequency
 * @return the frequency value
 */
int PanelChangeWaveOrFreq::getFrequency(void)
{
    /* Get the value on spinbox */
    return ui->spinBox_freq->value();
}

/**
 * @brief Set the units
 * @in    Unit
 */
void PanelChangeWaveOrFreq::setUnits(QString unit)
{
    /* Get the value on list */
    ui->label_unit->setText(unit);
}

/**
 * @brief Hide/Show Frequency SpinBox
 */
void PanelChangeWaveOrFreq::ShowFrequency(bool value)
{
    /* Get the value on list */
    ui->spinBox_freq->setVisible(value);
}

/**
 * @brief Hide/Show Wavelengths List
 */
void PanelChangeWaveOrFreq::ShowWavelengthsList(bool value)
{
    /* Get the value on list */
    ui->WaveList->setVisible(value);
}

/**
 * @brief Set wavelength
 * @param[in] wavelength value
 */
void PanelChangeWaveOrFreq::setValue(double value)
{
    /* Add wavelenghts to list */
   ui->WaveList->addItem(QString::number(value));
}

/**
 * @brief Set frequency
 * @param[in] frequency
 */
void PanelChangeWaveOrFreq::setFrequency(int value)
{
    /* Add frequency to the spin box */
   ui->spinBox_freq->setValue(value);
}

/**
 * @brief Accepts changed value
 */
void PanelChangeWaveOrFreq::applyButton(void)
{
    /* All fine */
    accept();
}

/**
 * @brief Destructor of 'PanelChange' class
 */
PanelChangeWaveOrFreq::~PanelChangeWaveOrFreq(void)
{
    /* Delete user interface */
    delete ui;
}
