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

/* External includes */
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPixmap>

/* Internal includes */
#include "pol_panelHelp.h"
#include "ui_pol_panelHelp.h"

/**
 * @brief Contructor of the 'PanelPolHelp' class
 * @param parent Parent widget
 *
 * In this class:   - The help window is created as non modal: Can remain open with other windows.
 *
 */
PanelPolHelp::PanelPolHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PanelPolHelp)
{   
    /* Set up user interface */
    ui->setupUi(this);

    /* Set window flags */
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint);

    /* This is not a modal window */
    this->setModal(false);

    /* Disable resize of elements */
    this->setFixedSize(this->size());

    /* Create Labels for icons */
    logoOxymetry = new QLabel(this);
    helpIcon = new QLabel(this);

    /* Create label for icon Oxymetry */
    logoOxymetry->setObjectName(QString("imageLabel"));
    logoOxymetry->setGeometry(QRect(40, 10, 50, 50));
    logoOxymetry->setScaledContents(true);

    /* Create label for icon Help */
    helpIcon->setObjectName(QString("imageHelpLabel"));
    helpIcon->setGeometry(QRect(410, 10, 50, 50));
    helpIcon->setScaledContents(true);

    /* Create pixel map of logos */
    QPixmap logo = QPixmap(QString(":/laboratory.ico"));
    QPixmap helplogo = QPixmap(QString(":/polarimeter/Help.ico"));

    /* Load and show icon */
    logo.scaled(100, 100);
    logoOxymetry->setPixmap(logo);

    /* Load and show icon */
    helplogo.scaled(100, 100);
    helpIcon->setPixmap(helplogo);

    /* Connect close button signals from different possible sources (Non Modal Window) */
    connect(ui->button_polhelp_close, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(qApp,SIGNAL(lastWindowClosed()),this,SLOT(close()));
    connect(this,SIGNAL(rejected()),this,SLOT(close()));
}

/**
 * @brief Close the Polarimeter help Dialog
 */
void PanelPolHelp::close(void)
{
    /* All fine */
    accept();
}

/**
 * @brief Destructor of the 'PanelPolHelp' class
 */
PanelPolHelp::~PanelPolHelp(void)
{
    /* Check handle */
    if (nullptr != logoOxymetry)
    {
        /* Free memory */
        delete logoOxymetry;
        logoOxymetry = nullptr;

        delete helpIcon;
        helpIcon = nullptr;
    }

    /* Delete user interface */
    delete ui;
}
