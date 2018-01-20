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

#define USE_POSTMESSAGE

/* External includes */
#include <QSettings>
#include <QApplication>
#include <QFile>
#include <QString>

/* Avantes AvaSpec library */
#include "avaspec.h"

/* Internal includes */
#include "messages.h"
#include "application.h"

/*
 * Global variables
 */
QSettings *settings = nullptr;

/**
 * @brief Constructor of 'Application' class
 */
Application::Application(int &argc, char *argv[])
    : QApplication(argc, argv)
{
    QString fileName("../../oxymetry.ini");

    /* Create configuration file handle */
    settings = new QSettings(fileName, QSettings::IniFormat, this);

    /* Check handle */
    if (nullptr == settings)
    {
        /* Show error message */
        showCritical("Unable to handle configuration file.", QString("%1").arg(fileName));
    }
}

void Application::emitsignal(int WParam, int LParam)
{
    emit DataIsHere(WParam, LParam);
}

void Application::emitPolsignal(int WParam, int LParam)
{
    emit DataPolIsHere(WParam, LParam);
}

void Application::callback(AvsHandle *handle, int *result)
{
    if (0 <= *result)
    {
        Application *m = static_cast<Application*>(qApp);

        /* Check handle */
        if (nullptr != m)
        {
            m->emitsignal(*result, *handle);
        }
    }
}

void Application::callPolback(AvsHandle *handle, int *result)
{
    if (0 <= *result)
    {
        Application *m1 = static_cast<Application*>(qApp);

        /* Check handle */
        if (nullptr != m1)
        {
            m1->emitPolsignal(*result, *handle);
        }
    }
}

/**
 * @brief Destructor of 'Application' class
 */
Application::~Application(void)
{
    /* Check handle */
    if (nullptr != settings)
    {
        /* Free memory */
        delete settings;
        settings = nullptr;
    }
}
