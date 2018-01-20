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

#ifndef IAD_PANEL_H
#define IAD_PANEL_H

/*
 * External includes
 */

/* Qt library */
#include <QDialog>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSignalMapper>
#include <QList>
#include <QTimer>

/* Qwt library */
#include "qwt_plot_curve.h"


/*
 * Other stuff
 */

namespace Ui {
    class PanelIAD;
}

/**
 * @brief The 'PanelIAD' class
 */
class PanelIAD : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelIAD(QWidget *parent = 0);

    /* Updates user interface */
    void update();

    /* Destructor */
    ~PanelIAD(void);

private slots:
    void updateGraphs(void);

    /* Functions for Inverse Adding-Doubling */
    void newConfigurationIAD(void);
    void openConfigurationIAD(void);
    void showConfigurationIAD(void);
    void calibrateIAD(void);
    void measureIAD(void);
    void liveViewIAD(void);

private:
    /* User interface */
    Ui::PanelIAD *ui;

    /* Inverse Adding-Doubling stuff */
    QString configPath;

    double *Rd_factor = nullptr;
    double *Td_factor = nullptr;
    double *Tu_factor = nullptr;

    QwtPlotCurve *M_R = nullptr;
    QwtPlotCurve *M_T = nullptr;
    QwtPlotCurve *M_U = nullptr;
};

#endif // IAD_PANEL_H
