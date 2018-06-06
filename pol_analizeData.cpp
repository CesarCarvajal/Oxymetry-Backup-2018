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
#include <QApplication>
#include <QDialog>
#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include <QLineEdit>
#include <QList>
#include <QTimer>
#include <QDateTime>
#include <QElapsedTimer>
#include <QFile>
#include <QMessageBox>

/* Internal includes */
#include "application.h"
#include "messages.h"
#include "spectrometer.h"
#include "timer.h"
#include "pol_analizeData.h"
#include "ui_pol_AnalizeData.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Constructor of 'Select Analize Data' class
 * @param[in] parent Parent widget
 */
selectAnalizeData::selectAnalizeData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectAnalizeData)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Create signal mapper for configuration window */
    signalMapperC = new QSignalMapper(this);

    /* Connect Button of cancel */
    connect(ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(cancel()));

    /* Connect signals */
    connect(ui->radiobutton_selectData, SIGNAL(clicked()), signalMapperC, SLOT(map()));
    connect(ui->radiobutton_selectSet, SIGNAL(clicked()), signalMapperC, SLOT(map()));

    signalMapperC->setMapping(ui->radiobutton_selectData, ui->radiobutton_selectData);
    signalMapperC->setMapping(ui->radiobutton_selectSet, ui->radiobutton_selectSet);

    /* Connect signal mapper action */
    connect(signalMapperC, SIGNAL(mapped(QWidget *)), this, SLOT(handleClickEvent(QWidget *)));

    /* Set window flags */
    this->setWindowFlags(Qt::Window | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    /* Set restart label color */
    ui->label_restart->setStyleSheet("QLabel { color: blue; }");


}


/**
 * @brief Called if a widget option was clicked,
 *        e.g. Integration time label.
 * @param widget Widget which has been clicked
 */
void selectAnalizeData::handleClickEvent(QWidget *widget)
{
    QRadioButton *radioBox = qobject_cast<QRadioButton *>(widget);

    /* Check which option is active */
    if(radioBox == ui->radiobutton_selectData){

        /* Enable the type of data selection */
        ui->SelectFiles->setEnabled(ui->radiobutton_selectData->isChecked());
        ui->SelectSet->setEnabled(ui->radiobutton_selectSet->isChecked());

    }

    /* Check which option is active */
    if(radioBox == ui->radiobutton_selectSet){

        /* Enable the type of data selection */
        ui->SelectFiles->setEnabled(ui->radiobutton_selectData->isChecked());
        ui->SelectSet->setEnabled(ui->radiobutton_selectSet->isChecked());

    }

}


/**
 * @brief Loading a configuration has been canceled
 */
void selectAnalizeData::cancel(void)
{

    /* Close dialog */
    reject();
}

/**
 * @brief Destructor of 'analize data' class
 */
selectAnalizeData::~selectAnalizeData(void)
{
    delete ui;

}
