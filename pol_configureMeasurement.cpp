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
#include <QElapsedTimer>
#include <QFile>

/* Internal includes */
#include "application.h"
#include "messages.h"
#include "spectrometer.h"
#include "timer.h"
#include "pol_configureMeasurement.h"
#include "ui_pol_configureMeasurement.h"

/*
 * Global variables
 */
extern Spectrometer** ptrSpectrometers;
extern unsigned int m_NrDevices;

/**
 * @brief Constructor of 'configure Pol Measure' class
 * @param[in] parent Parent widget
 */
configurePolMeasure::configurePolMeasure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configurePolMeasure)
{
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);

    /* Connect buttons to signal mapper */
    connect(ui->pushButton_select, SIGNAL(clicked()), this, SLOT(selectPath()));

}

/**
 * @brief Select path for StoreToRAM files
 */
void configurePolMeasure::selectPath(void)
{
    /* No directory chosen until now? */
    if (!ui->lineEdit_path->isEnabled())
    {
        /* Get path of configuration file */
        path = QFileDialog::getOpenFileName(this, "Configuration file", QDir::currentPath(), "Text files (*.txt)");

    }
    else
    {
        /* Get path of configuration file */
        path = QFileDialog::getOpenFileName(this, "Configuration file", path, "Text files (*.txt)");
    }

    /* Did the user select a new path? */
    if (path != ui->lineEdit_path->text() && !path.isEmpty() && ui->lineEdit_path->text() != "Please select a configuration file")
    {
        /* If a new file was loaded, clear all the configuration */
        cleanAll();
    }

    /* Save rows in file */
    QStringList wordList;

    /* Did user select a path? */
    if (!path.isEmpty())
    {
        /* File Path */
        QFile file(path);

        /* Save that a configuration file was loaded */
        configured = true;

        /* Open configuration file */
        if (!file.open(QIODevice::ReadOnly))
        {
            /* Show message */
            showCritical("Unable to open configuration file!", "");
            return;
        }

        /* Loop through lines in file */
        while (!file.atEnd())
        {
            /* Get row in file */
            wordList.append(file.readLine().split(',').first());
        }

        /* Close file */
        file.close();

        /* Clear lists */
        cleanAll();

        /* Check format of configuration file; we need at least 5 semicolons per line */
        if (wordList[0].count(QLatin1Char(';')) != 5)
        {
            /* Show message */
            showWarning("Malformed configuration file!", "");
            configured = false;
            return;
        }

        unsigned int i = 0;

        /* Loop through elements */
        for (i = 0; i < (unsigned int)wordList.length(); i++)
        {
            QStringList list = wordList[i].split(';');

            /* Copy entries to lists */
            timePoint.append(list[0].toInt());
            fileName.append(list[1]);
            numSpectra = list[2].toInt();
            integrationTime = list[3].toFloat();
            numberOfAverages = list[4].toInt();
            freqToMeasure = list[5].toInt();

            /* At least second entry? */
            if (i > 0)
            {
                /* Calculate duration of entry before current entry */
                double duration = numSpectra * integrationTime * numberOfAverages;

                /* Check if there's a time overlap between last and current entry */
                if ((timePoint[i - 1] + duration) > timePoint[i])
                {
                    /* Clear lists */
                    cleanAll();

                    /* Create message */
                    QString message;
                    message = QString("Error in configuration file! Time overlap between entries %1 and %2.").arg(QString::number(i - 1),
                                                                                                                  QString::number(i));
                    /* Show message */
                    showCritical(message, "");
                    return;
                }
            }
        }

        /* Copy path into line edit */
        ui->lineEdit_path->setText(path);

        /* Enable directory field and 'start' button */
        ui->lineEdit_path->setEnabled(true);
    }

    /* Finish the window */
    accept();
}

/**
 * @brief Clean all the configuration if a different file was loaded.
 */
void configurePolMeasure::cleanAll(void)
{
    /* Clear lists */
    timePoint.clear();
    fileName.clear();
    numSpectra=0;
    integrationTime=0;
    numberOfAverages=0;
    freqToMeasure =0;
    ui->lineEdit_path->setEnabled(false);

}

/**
 * @brief Destructor of 'configurePolMeasure' class
 */
configurePolMeasure::~configurePolMeasure(void)
{
    delete ui;
}
