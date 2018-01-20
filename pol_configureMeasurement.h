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

#ifndef POL_CONFIGUREMEASUREMENT_H
#define POL_CONFIGUREMEASUREMENT_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QList>
#include <QStringList>

namespace Ui {
class configurePolMeasure;
}

/**
 * @brief The 'configurePolMeasure' class
 */
class configurePolMeasure : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit configurePolMeasure(QWidget *parent = 0);

    /* Configurable Variables */
    int numSpectra;
    float integrationTime;
    int numberOfAverages;
    int freqToMeasure;
    QList<double> timePoint;

    /* Save if there was a configuration loaded */
    bool configured = false;

    /* Path for Store to RAM */
    QString path;

    /* Build the name of the Raw Data */
    QStringList fileName;

    /* Clean all the loaded configuration */
    void cleanAll(void);

    /* Destructor */
    ~configurePolMeasure(void);

private slots:
    /* Select path */
    void selectPath(void);

private:
    /* User interface */
    Ui::configurePolMeasure *ui;

    /* Abort run if set to FALSE */
    bool bRunTimePattern = false;

};

#endif // POL_CONFIGUREMEASUREMENT_H
