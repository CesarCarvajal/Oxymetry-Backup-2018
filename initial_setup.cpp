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
#include <QDialog>
#include <QString>
#include <QStringList>

/* Internal includes */
#include "initial_setup.h"
#include "ui_initial_setup.h"

/**
 * @brief Constructor of 'InitialSetup' class
 */
InitialSetup::InitialSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitialSetup)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Connect buttons */
    connect(ui->pushButton_continue, SIGNAL(clicked(bool)), this, SLOT(apply()));
}

/**
 * @brief Button 'continue' clicked
 */
void InitialSetup::apply(void)
{
    /* All fine */
    accept();
}

/**
 * @brief Returns list of selected modules
 * @return QString with comma-separated names of selected modules
 */
QString InitialSetup::getModuleList(void)
{
    QStringList modules;

    /* Check whether modules are selected or not */
    if (ui->checkBox_modules_iad->isChecked()) { modules.append("iad"); }
    if (ui->checkBox_modules_polarimeter->isChecked()) { modules.append("pol"); }

    /* Return 'none' if no modules are selected, otherweise list of modules */
    return modules.empty() ? "none" : modules.join(",");
}

/**
 * @brief Returns list of selected toolkits
 * @return QString with comma-separated names of selected toolkits
 */
QString InitialSetup::getToolkitList(void)
{
    QStringList toolkits;

    /* Check whether toolkits are selected or not */
    if (ui->checkBox_toolkits_fluidic->isChecked()) { toolkits.append("fluidic"); }
    if (ui->checkBox_toolkits_light->isChecked()) { toolkits.append("light"); }

    /* Return 'none' if no toolkits are selected, otherweise list of toolkits */
    return toolkits.empty() ? "none" : toolkits.join(",");
}

/**
 * @brief Returns whether USB devices should be connected
 * @return TRUE if USB devices should be connected, else FALSE
 */
bool InitialSetup::getConnectUSB(void)
{
    return ui->checkBox_connection_usb->isChecked();
}

/**
 * @brief Returns whether ethernet devices should be connected
 * @return TRUE if ethernet devices should be connected, else FALSE
 */
bool InitialSetup::getConnectEthernet(void)
{
    return ui->checkBox_connection_ethernet->isChecked();
}

/**
 * @brief Destructor of 'InitialSetup' class
 */
InitialSetup::~InitialSetup(void)
{
    /* Delete user interface */
    delete ui;
}
