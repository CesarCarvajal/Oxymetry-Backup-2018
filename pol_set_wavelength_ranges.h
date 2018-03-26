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

#ifndef POL_SET_WAVELENGTH_RANGES_H
#define POL_SET_WAVELENGTH_RANGES_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QTimer>

namespace Ui {
    class PanelSetWavelengthRanges;
}

/**
 * @brief The 'PanelSetWavelengthRanges' class
 */
class PanelSetWavelengthRanges : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelSetWavelengthRanges(QWidget *parent = 0);

    /* Get or set wavelength ranges */
    double getMinValue(void);
    double getMaxValue(void);

    void setValues(double minW, double maxW);

    /* Destructor */
    ~PanelSetWavelengthRanges(void);

public slots:

    /* Brings the window to foreground at creation */
    void activateWindow(void)
    {
        QDialog::activateWindow();
    }

private slots:

    /* User pressed 'apply' button */
    void applyButton(void);

    /* Set limits of the range */
    void setLimits(void);

private:

    Ui::PanelSetWavelengthRanges *ui;
};

#endif // POL_SET_WAVELEGNTH_RANGES_H
