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
#include <QCloseEvent>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QBitArray>

/* Qwt library */
#include "qwt_plot_curve.h"

/* Internal includes */
#include "messages.h"
#include "fluidic_connect.h"
#include "fluidic_control.h"
#include "ui_fluidic_control.h"

/* Global variables */
extern QSerialPort serial;

/**
 * @brief Constructor of 'ControlFluidic' class
 * @param parent
 */
ControlFluidic::ControlFluidic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlFluidic)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Adjust window geometry and set window flags */
    this->setGeometry(20, 50, this->width(), this->height());
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);

    unsigned char i = 0;

    /* Loop through valves */
    for (i = 0; i < 8; i++)
    {
        checkBox_valve[i] = new QCheckBox(ui->tab_2);
        checkBox_valve[i]->setGeometry(10 + 20 * i, 31, 16, 21);
        checkBox_valve[i]->show();
    }

    /* Connect functions to buttons */
    connect(ui->pushButton_connect, SIGNAL(clicked()), this, SLOT(connectCOM()));
    connect(ui->pushButton_apply, SIGNAL(clicked(bool)), this, SLOT(apply()));
    connect(ui->pushButton_flush, SIGNAL(clicked(bool)), this, SLOT(flush()));
    connect(ui->pushButton_sample, SIGNAL(clicked(bool)), this, SLOT(sample()));
    connect(&serial, SIGNAL(readyRead()), this, SLOT(readData()));

    /* Set axis and title of preview plot */
    ui->qwtPlot_stats->setXAxisTitle("time in s");
    ui->qwtPlot_stats->setXAxis(0.0, 60.0);
    ui->qwtPlot_stats->axisAutoScale(QwtPlot::yLeft);
    ui->qwtPlot_stats->enableAxis(QwtPlot::yLeft, false);
    ui->qwtPlot_stats->hideGrid();
    ui->qwtPlot_stats->disableZoom();

    /* Add curve for voltage */
    rpm = new QwtPlotCurve("RPM");
    rpm->setPen(QPen("blue"));
    rpm->attach(ui->qwtPlot_stats);

    /* Remember: Is not connected */
    isConnected = false;

    /* Update GUI elements */
    ui->label_status->setText("Not connected");
    ui->label_status->setStyleSheet("color: red;");
}

/**
 * @brief Close event of 'ControlFluidic' class
 * @param event
 */
void ControlFluidic::closeEvent(QCloseEvent *event) {
    Q_UNUSED(event);

    /* Serial connection established? */
    if (serial.isOpen())
    {
        /* Close connection */
        serial.close();
    }
}

/**
 * @brief Button 'connect' clicked
 */
void ControlFluidic::connectCOM(void)
{
    /* Disable button */
    ui->pushButton_connect->setEnabled(false);

    /* Check if already connected */
    if (!isConnected)
    {
        ConnectFluidic setup;

        /* Execute connection dialog */
        if (QDialog::Accepted == setup.exec())
        {
            /* Successfully connected! Change button text from 'Connect' to 'Disconnect' */
            ui->pushButton_connect->setText("Disconnect");
            ui->pushButton_apply->setEnabled(true);
            ui->pushButton_flush->setEnabled(true);
            ui->pushButton_sample->setEnabled(true);

            /* Apply settings */
            apply();

            /* Remember: Is connected */
            isConnected = true;
        }
    }
    else
    {
        /* Close connection */
        serial.close();

        /* Connection failed! Set button text to 'Connect' */
        ui->pushButton_connect->setText("Connect");
        ui->pushButton_apply->setEnabled(false);
        ui->pushButton_flush->setEnabled(false);
        ui->pushButton_sample->setEnabled(false);

        /* Remember: Is not connected */
        isConnected = false;
    }

    /* Update GUI elements */
    ui->label_status->setText(isConnected ? QString("Connected") : QString("Not connected"));
    ui->label_status->setStyleSheet(isConnected ? "color: green;" : "color: red;");

    /* Enable button */
    ui->pushButton_connect->setEnabled(true);
}

/**
 * @brief Button 'apply' clicked
 */
void ControlFluidic::apply(void)
{
    /* Serial connection established? */
    if (!serial.isOpen())
    {
        return;
    }

    unsigned char valveBits = 0;

    unsigned char i = 0;

    /* Set bits for valves */
    for (i = 0; i < 8; i++)
    {
        if (checkBox_valve[i]->isChecked())
        {
            valveBits = valveBits | (int)pow(2, i);
        }
    }

    /* Output byte */
    serial.write((const char *)&valveBits, 1);

    unsigned short rpmBits = (unsigned short)(ui->doubleSpinBox_rpm->value() * 100.0f);

    /* Output bytes */
    serial.write((const char *)&rpmBits, 2);

    unsigned char controlBits = 0;

    /* Set bit for pulsation reduction algorithm */
    if (ui->checkBox_pulsationReduction->isChecked())
    {
        controlBits = controlBits | 4;
    }

    /* Set bit for direction */
    if (ui->checkBox_direction->isChecked())
    {
        controlBits = controlBits | 2;
    }

    /* Set bit for brake */
    if (ui->checkBox_brake->isChecked())
    {
        controlBits = controlBits | 1;
    }

    /* Output byte */
    serial.write((const char *)&controlBits, 1);
}

/**
 * @brief Converts revolutions per minute (RPM) to a pair of microstepping and delay between steps
 * @param[in] rpm Revolutions per minute
 */
void ControlFluidic::setRPM(float flow)
{
    //Steigung:
    float m = (RPM_HIGH_VALUE - RPM_LOW_VALUE) / (RPM_HIGH_FLOW - RPM_LOW_FLOW);

    //Achsenabschnitt:
    float b = RPM_LOW_VALUE - m * RPM_LOW_FLOW;

    float rpm = m * flow + b;

    // Set RPM
    ui->doubleSpinBox_rpm->setValue(rpm);
}

/**
 * @brief Button 'flush' clicked
 */
void ControlFluidic::flush(void)
{
    unsigned char i = 0;

    /* Loop through valves */
    for (i = 0; i < 8; i++)
    {
        /* Disable every valve */
        checkBox_valve[i]->setChecked(false);
    }

    /* Already running in 'flush' mode? */
    if (ui->pushButton_flush->text() == "Flush")
    {
        /* Is Hellmanex III checked? */
        if (ui->checkBox_hellmanex->isChecked())
        {
            /* Enable detergent valve */
            checkBox_valve[VALVE_DETERGENT - 1]->setChecked(true);
        }
        else
        {
            /* Enable water valve */
            checkBox_valve[VALVE_WATER - 1]->setChecked(true);
        }

        /* Avoid control loose by disconnecting */
        ui->pushButton_connect->setEnabled(false);

        /* Disable manual settings */
        ui->tab_2->setEnabled(false);

        /* Disable 'sample' mode and 'flush' settings */
        ui->horizontalSlider_flush->setEnabled(false);
        ui->checkBox_hellmanex->setEnabled(false);
        ui->horizontalSlider_sample->setEnabled(false);
        ui->pushButton_sample->setEnabled(false);

        /* Change caption of button to 'stop' */
        ui->pushButton_flush->setText("Stop");

        ui->checkBox_brake->setChecked(false);
        setRPM(ui->horizontalSlider_flush->value());
    }
    else
    {
        /* Re-enable manual settings */
        ui->tab_2->setEnabled(true);

        /* Allow disconnecting again */
        ui->pushButton_connect->setEnabled(true);

        /* Re-enable 'sample' mode and 'flush' settings */
        ui->horizontalSlider_flush->setEnabled(true);
        ui->checkBox_hellmanex->setEnabled(true);
        ui->horizontalSlider_sample->setEnabled(true);
        ui->pushButton_sample->setEnabled(true);

        /* Change caption of button to 'flush' */
        ui->pushButton_flush->setText("Flush");

        ui->checkBox_brake->setChecked(true);
    }

    apply();
}

/**
 * @brief Button 'sample' clicked
 */
void ControlFluidic::sample(void)
{
    unsigned char i = 0;

    /* Loop through valves */
    for (i = 0; i < 8; i++)
    {
        /* Disable every valve */
        checkBox_valve[i]->setChecked(false);
    }

    /* Already running in 'sample' mode? */
    if (ui->pushButton_sample->text() == "Sample")
    {
        /* Enable sample valve */
        checkBox_valve[VALVE_SAMPLE - 1]->setChecked(true);

        /* Avoid control loose by disconnecting */
        ui->pushButton_connect->setEnabled(false);

        /* Disable manual settings */
        ui->tab_2->setEnabled(false);

        /* Disable 'flush' mode and 'sample' settings */
        ui->horizontalSlider_flush->setEnabled(false);
        ui->checkBox_hellmanex->setEnabled(false);
        ui->horizontalSlider_sample->setEnabled(false);
        ui->pushButton_flush->setEnabled(false);

        /* Change caption of button to 'stop' */
        ui->pushButton_sample->setText("Stop");

        ui->checkBox_brake->setChecked(false);
        setRPM(ui->horizontalSlider_sample->value());
    }
    else
    {
        /* Re-enable manual settings */
        ui->tab_2->setEnabled(true);

        /* Allow disconnecting again */
        ui->pushButton_connect->setEnabled(true);

        /* Re-enable 'flush' mode and 'sample' settings */
        ui->horizontalSlider_flush->setEnabled(true);
        ui->checkBox_hellmanex->setEnabled(true);
        ui->horizontalSlider_sample->setEnabled(true);
        ui->pushButton_flush->setEnabled(true);

        /* Change caption of button to 'sample' */
        ui->pushButton_sample->setText("Sample");

        ui->checkBox_brake->setChecked(true);
    }

    apply();
}

/**
 * @brief Called if new data arrived at serial port
 */
void ControlFluidic::readData(void)
{
    /* Only continue if pump is connected */
    if (!isConnected) { return; }

    /* Only update graph once */
    bool updateNeeded = false;

    /* Do we have at least one data paket? */
    while (serial.bytesAvailable() >= 4)
    {
        QByteArray data = serial.read(4);

        /* End of buffer reached? */
        if (valueIndex > UPDATE_RATE * MAX_TIME_FRAME - 1)
        {
            unsigned int i = 0;

            /* Loop through buffer elements */
            for (i = 1; i < UPDATE_RATE * MAX_TIME_FRAME; i++)
            {
                rpm_values[i - 1] = rpm_values[i];
            }

            /* Decrease buffer pointer */
            valueIndex--;
        }

        /* Get voltage and current */
        rpm_values[valueIndex] = *(float *)((char *)data.data());
        time_values[valueIndex] = (double)valueIndex / UPDATE_RATE;

        /* Update graph values */
        rpm->setSamples(time_values, rpm_values, valueIndex);

        double mean_rpm = 0.0;

        unsigned char i = 0;

        /* Calculate mean RPM over a period of one second */
        for (i = 0; i < ((valueIndex >= UPDATE_RATE) ? UPDATE_RATE : valueIndex); i++)
        {
            mean_rpm += rpm_values[valueIndex + i];
        }

        /* Show RPM to user */
        ui->label_rpm->setText(QString::number(mean_rpm, 'f', 2) + " RPM");

        /* End of buffer not reached yet? */
        if (valueIndex < UPDATE_RATE * MAX_TIME_FRAME)
        {
            /* Increase buffer pointer */
            valueIndex++;
        }

        /* Graph needs update */
        updateNeeded = true;
    }

    /* Graph needs update? */
    if (updateNeeded)
    {
        /* Update graph */
        ui->qwtPlot_stats->replot();
    }
}

/**
 * @brief Destructor of 'ControlFluidic' class
 */
ControlFluidic::~ControlFluidic(void)
{
    /* Serial connection established? */
    if (serial.isOpen())
    {
        /* Close connection */
        serial.close();
    }

    /* Delete user interface */
    delete ui;
}
