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
#include "application.h"

/* Internal includes */
#include "pol_waitingDialog.h"
#include "ui_pol_waitingDialog.h"

/**
 * @brief Constructor of 'Waiting Dialog' class
 * @param parent
 */
WaitingDialog::WaitingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WaitingDialog)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Set window flags */
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint);

    /* Count the seconds */
    timerS = 0;

}

/**
* @brief  Give the user 5 seconds to press the start button in the syringe pump software
*/
void WaitingDialog::setCount(void){

    /* Start a timer */
    timerMS.start();

    /* Run until the time is complete or the user cancel the measurement */
    while(timerS < 7){

        /* Count seconds */
        if(timerMS.elapsed()/1000 > timerS){

            /* Time in seconds */
            timerS = timerS + 1;

            countDown = 6 - timerS;

            if(countDown != 0){
            /* Show the counter back */
            ui->label_count->setText(QString::number(countDown));
            }else{
                ui->label_count->setText("PRESS OK");
            }
        }

        /* Don't lock the user interface */
        Application::processEvents();
    }

    accept();

}

/**
 * @brief Destructor of 'Waiting Dialog' class
 */
WaitingDialog::~WaitingDialog(void)
{
    /* Delete user interface */
    delete ui;
}
