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
#include <QList>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

/* Internal includes */
#include "messages.h"
#include "pol_temp_connect.h"

/* Global variables */
QSerialPort serials;

/**
 * @brief Constructor 'ConnectTemperature' class
 * @param parent
 */
ConnectTemperature::ConnectTemperature(QWidget *parent) :
    QDialog(parent)
{

    /* Get list of available ports */
    USBports = QSerialPortInfo::availablePorts();

    /* Loop through serial ports (COMxx) */
    foreach (const QSerialPortInfo &info, USBports)
    {
        /* Check if we have the fluidic circuit connected */
        if ((TEENSY_VENDOR_ID == info.vendorIdentifier()) &&
            (TEENSY_DEVICE_ID == info.productIdentifier()))
        {
            /* Configure serial connection */
            serials.setPortName(info.portName());
            serials.setBaudRate(QSerialPort::Baud115200);
            serials.setDataBits(QSerialPort::Data8);
            serials.setParity(QSerialPort::NoParity);
            serials.setStopBits(QSerialPort::OneStop);
            serials.setFlowControl(QSerialPort::NoFlowControl);

            /* Try to establish serial connection */
            if (serials.open(QIODevice::ReadWrite))
            {
               TeensyConnected = true;
            }else{

                TeensyConnected = false;
            }
        }
    }
}

/**
 * @brief Button 'refresh' clicked
 */
void ConnectTemperature::refresh(void)
{

    /* Get list of available ports */
    USBports = QSerialPortInfo::availablePorts();
}

/**
 * @brief Destructor of 'ConnectTemperature' class
 */
ConnectTemperature::~ConnectTemperature(void)
{
}
