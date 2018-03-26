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

#ifndef POL_PANELHELP_H
#define POL_PANELHELP_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>

namespace Ui {
    class PanelPolHelp;
}

/**
 * @brief The 'PanelPolHelp' class
 */
class PanelPolHelp : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelPolHelp(QWidget *parent = 0);

    /* Destructor */
    ~PanelPolHelp(void);

private slots:

    /* Alles gut? Then close */
    void close(void);

private:

    /* UI */
    Ui::PanelPolHelp *ui;

    /* Label for application icon */
    QLabel *logoOxymetry = nullptr;
    QLabel *helpIcon = nullptr;

};

#endif // POL_PANELHELP_H
