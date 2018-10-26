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

#ifndef POL_TEMP_CONNECT_H
#define POL_TEMP_CONNECT_H

/* ID's for auto-connect functionality */
#define TEENSY_VENDOR_ID 0x16C0
#define TEENSY_DEVICE_ID 0x0483

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QList>
#include <QSerialPortInfo>

namespace Ui {
    class ConnectFluidic;
}

/**
 * @brief The 'ConnectFluidic' class
 */
class ConnectTemperature : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit ConnectTemperature(QWidget *parent = 0);

    /* Save teensy status */
    bool TeensyConnected;

    /* Destructor */
    ~ConnectTemperature(void);

private slots:

    /* Button 'refresh' clicked */
    void refresh(void);

private:

    /* Structure for port information */
    QList<QSerialPortInfo> USBports;

};

#endif // POL_TEMP_CONNECT_H
