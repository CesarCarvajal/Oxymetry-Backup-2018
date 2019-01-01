/*
 * Hemoxymetrie in non-hemolyzed human whole blood
 * Copyright (C) 2016-2017 Benjamin Redmer, ... ?
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
#include "pol_set_wavelength_ranges.h"
#include "ui_pol_set_wavelength_ranges.h"

/**
 * @brief Constructor of 'PanelSetWavelengthRanges' class
 * @param parent
 *
 * In this class:   - The minimum and maximum measurement wavelengths can be set.
 *                  - A dialog is opened when the corresponding setting is clicked.
 *                  - The minimum and maximum wavelengths for the measurements are also returned.
 *
 */
PanelSetWavelengthRanges::PanelSetWavelengthRanges(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PanelSetWavelengthRanges)
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

    /* Update limits of the spin boxes */
    connect(ui->doubleSpinBox_maxWset, SIGNAL(valueChanged(double)), this, SLOT(setLimits()));
    connect(ui->doubleSpinBox_minWset, SIGNAL(valueChanged(double)), this, SLOT(setLimits()));

}

/**
 * @brief Get minimum wavelength
 * @return the value of the wavelength
 */
double PanelSetWavelengthRanges::getMinValue(void)
{
    /* Get the min value of the wavelength */
    return ui->doubleSpinBox_minWset->value();
}

/**
 * @brief Get maximum wavelength
 * @return the value of the wavelength
 */
double PanelSetWavelengthRanges::getMaxValue(void)
{
    /* Get the min value of the wavelength */
    return ui->doubleSpinBox_maxWset->value();
}

/**
 * @brief Set ranges of wavelengths
 * @param[in] wavelength value
 */
void PanelSetWavelengthRanges::setValues(double minW, double maxW, double actualMin, double actualMax)
{
    /* Add wavelenghts to ranges */
   ui->doubleSpinBox_minWset->setMinimum(minW);
   ui->doubleSpinBox_maxWset->setMaximum(maxW);

   /* Set actual range */
   ui->doubleSpinBox_minWset->setValue(actualMin);
   ui->doubleSpinBox_maxWset->setValue(actualMax);

   /* Change upper and lower limits */
   setLimits();
}

/**
 * @brief Set Limits for the ranges
 */
void PanelSetWavelengthRanges::setLimits(void){

    /* Dependency between both parameters */
    ui->doubleSpinBox_minWset->setMaximum(ui->doubleSpinBox_maxWset->value());
    ui->doubleSpinBox_maxWset->setMinimum(ui->doubleSpinBox_minWset->value());

}

/**
 * @brief Accepts changed value
 */
void PanelSetWavelengthRanges::applyButton(void)
{
    /* All fine */
    accept();
}

/**
 * @brief Destructor of 'PanelSetWavelengthRanges' class
 */
PanelSetWavelengthRanges::~PanelSetWavelengthRanges(void)
{
    /* Delete user interface */
    delete ui;
}
