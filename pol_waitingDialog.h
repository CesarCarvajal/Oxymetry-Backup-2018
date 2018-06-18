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

#ifndef POL_WAITINGDIALOG_H
#define POL_WAITINGDIALOG_H

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QElapsedTimer>

namespace Ui {
    class WaitingDialog;
}

/**
 * @brief The 'Waiting Dialog' class
 */
class WaitingDialog : public QDialog
{
    Q_OBJECT

public:
    /* Constructor */
    explicit WaitingDialog(QWidget *parent = 0);

    /* User Interface */
    Ui::WaitingDialog *ui;

    /* Timer in ms */
    QElapsedTimer  timerMS;

    /* time in seconds */
    int timerS;

    /* Count down seconds */
    int countDown;

    /* Canceled count? */
    bool cancelCountDown;

    /* Skipped the count? */
    bool skipCountDown;

    /* Destructor */
    ~WaitingDialog(void);

public slots:
    /* Brings the window to foreground at creation */
    void activateWindow(void)
    {
        QDialog::activateWindow();
    }

    /* Run the dialog */
    void run(void);

private slots:

    /* Cancel count down */
    void cancelCount(void);

    /* Skip the count down */
    void skipCount(void);

    /* Run the couter back */
    void setCount(void);

};

#endif // POL_WAITINGDIALOG_H
