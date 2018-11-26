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

#ifndef POL_CHANGEWAVEORFREQ_H
#define POL_CHANGEWAVEORFREQ_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QTimer>

/* Header for Change the FFT Wavelength or Measurement Frequency */

namespace Ui {
    class PanelChangeWaveOrFreq;
}

/**
 * @brief The 'PanelChangeWaveFFT' class
 */
class PanelChangeWaveOrFreq : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit PanelChangeWaveOrFreq(QWidget *parent = 0);

    /* User Interface */
    Ui::PanelChangeWaveOrFreq *ui;

    /* Get or set wavelength */
    int getValue(void);
    void setValue(double value);

    /* Show/Hide the frequency spinbox */
    void ShowFrequency(bool value);

    /* Show/Hide the list of wavelengths */
    void ShowWavelengthsList(bool value);

    /* Get or set the frequency */
    int getFrequency(void);
    void setFrequency(int value);

    /* Set Units */
    void setUnits(QString unit);

    /* Destructor */
    ~PanelChangeWaveOrFreq(void);

public slots:
    /* Brings the window to foreground at creation */
    void activateWindow(void)
    {
        QDialog::activateWindow();
    }

private slots:
    /* User pressed 'apply' button */
    void applyButton(void);

};

#endif // POL_CHANGEWAVEORFREQ_H
