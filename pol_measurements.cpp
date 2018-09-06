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

/* Qwt library */

/* Internal includes */
#include "pol_measurements.h"

/**
 * @brief Constructor of 'Pol_Measurements' class
 */
Pol_Measurements::Pol_Measurements()
{

    /* No measurement running */
    PolMeasuring = false;

    /* No calibration running */
    PolCalibrating = false;

    /* No configuration loaded */
    PolConfigured = false;

    /* Any change in parameters yet */
    AcceptChanges = false;

    /* Not necessary to show raw signal yet */
    showRaw = false;

    /* Not delayed stop */
    delayStop = false;

    /* Any measurement interrupted */
    Stopped = false;

    /* When doing changes, we have to know when it's busy doing the live FFT */
    doingLiveFFT = false;

    /* When running Measurements, raw signal is also available and autoadjust it */
    maxRawCounts = -1;

    /* Temporal File Name for Calibration */
    TempFileName = "Pol_tmp.tmp";

    /* Analize data after the measurement */
    automaticData = false;

    /* General Timer in seconds */
    Timer_In_Seconds=0;

    /* Intervals between plots of average during the measurements */
    measurementPlotTimeInterval = 0;

    /* Time busy with FFT */
    liveFFT_Time = 0;

    /* Elapsed time in between measurements during live FFT */
    Calibration_Progress = 0;

    /* Start the time index in 0 */
    Timeindex = 0;

    /* Start the  vector index in -1 */
    vectorIndex = -1;
}

/**
 * @brief Restart important parameters as counters for calibration
 */
void Pol_Measurements::restart_CalibrationPol(void){

    /* Restart the routine of calibration counters */
    liveFFT_Time = 0;
    Calibration_Progress = 0;

    /* Start timers */
    RestartTimers();

    /* Allow the calibration routine to run again */
    AcceptChanges = false;
}

/**
 * @brief Restart timer
 */
void Pol_Measurements::RestartTimers(void){

    /* Restart timer */
    timerMS.start();

    /* Restart second Timer */
    Timer_In_Seconds=0;
}

/**
 * @brief Is the measurement running?
 * @param[in] value TRUE to remember the measurement is running, FALSE to stop it.
 *
 */
void Pol_Measurements::setMeasurementRunning(bool runningM){

    /* Set the measurement status */
    PolMeasuring = runningM;

}

/**
 * @brief Is the Calibration running?
 * @param[in] value TRUE to remember the calibration is running, FALSE to stop it.
 */
void Pol_Measurements::setCalibrationRunning(bool runningC){

    /* Set the measurement status */
    PolCalibrating = runningC;

}

/**
 * @brief Is the configuration loaded?
 * @param[in] value TRUE to remember the interface is configured, FALSE its not configured yet.
 */
void Pol_Measurements::setConfigured(bool configured){

    /* Set the measurement status */
    PolConfigured = configured;

}

/**
 * @brief accept changes from parameters like integration time, etc.
 */
void Pol_Measurements::AcceptParameterChanges(){

    /* Set the measurement status */
    AcceptChanges = true;

}

/**
 * @brief Destructor of 'Pol_Measurements' class
 */
Pol_Measurements::~Pol_Measurements(void)
{

}
