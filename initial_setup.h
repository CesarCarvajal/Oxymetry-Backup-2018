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

#ifndef INITIAL_SETUP_H
#define INITIAL_SETUP_H

/* External includes */
#include <QDialog>

namespace Ui {
    class InitialSetup;
}

/**
 * @brief The 'InitialSetup' class
 */
class InitialSetup : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit InitialSetup(QWidget *parent = 0);

    /* Returns list of selected modules */
    QString getModuleList(void);

    /* Returns list of selected toolkits */
    QString getToolkitList(void);

    /* Returns whether USB devices should be connected */
    bool getConnectUSB(void);

    /* Returns whether ethernet devices should be connected */
    bool getConnectEthernet(void);

    /* Destructor */
    ~InitialSetup(void);

private slots:
    /* Button 'continue' clicked */
    void apply(void);

private:
    /* User interface */
    Ui::InitialSetup *ui;
};

#endif // INITIAL_SETUP_H
