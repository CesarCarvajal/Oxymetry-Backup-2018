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

#ifndef POL_MEASUREMENTS_H
#define POL_MEASUREMENTS_H

/* External includes */
#include "qobject.h"
#include "timer.h"
#include <QElapsedTimer>

/**
 * @brief The 'pol_measurements' class
 */
class Pol_Measurements : public QObject
{
    Q_OBJECT

public:
    /* Constructor */
    explicit Pol_Measurements();

    /* Are we measuring or calibrating? */
    bool PolMeasuring;
    bool PolCalibrating;

    /* Did the user stop the measurement? */
    bool Stopped;

    /* Was there a configuration profile for the measurement loaded? */
    bool PolConfigured;

    /* When to show the raw signal */
    bool showRaw;

    /* Stop the calibration in the right time */
    bool delayStop;

    /* Stop calibration and restart it after any change */
    bool AcceptChanges;

    /* Load the data after the measurement */
    bool automaticData;

    /* Show raw signal also when long term measuring running */
    double maxRawCounts;

    /* Intervals between plots of average during the measurements */
    int measurementPlotTimeInterval;

    /* When calibrating we don't need to save all this data, so just use a temporal file deleted at the end of the calibration */
    QString TempFileName;

    /* When doing changes, we have to know when it's busy doing the live FFT */
    bool doingLiveFFT;

    /* General Timer in seconds */
    int Timer_In_Seconds;

    /* Calibration progress */
    int Calibration_Progress;

    /* Local Timer */
    QElapsedTimer timerMS;

    /* Time busy with FFT */
    int liveFFT_Time;

public:

    /* Is the measurement running? */
    void setMeasurementRunning(bool runningM);

    /* Is the calibration running? */
    void setCalibrationRunning(bool runningC);

    /* Is there a configuration loaded? */
    void setConfigured(bool configured);

    /* Accept parameter changes */
    void AcceptParameterChanges();

    /* Restar timers */
    void RestartTimers(void);

    /* Restart important calibration parameters */
    void restart_CalibrationPol(void);

    /* Destructor */
    ~Pol_Measurements(void);

};

#endif  // POL_MEASUREMENTS_H
