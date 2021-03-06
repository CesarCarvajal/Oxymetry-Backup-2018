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

#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

/* External includes */
#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

/**
 * @brief The 'ClickableLabel' class
 */
class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    /* Constructor */
    explicit ClickableLabel(QWidget* parent = 0);

    /* Destructor */
    ~ClickableLabel(void);

signals:
    /* Signal when label is clicked */
    void clicked(void);

protected:
    /* Event when mouse is pressed */
    void mousePressEvent(QMouseEvent *event);
};

#endif // CLICKABLELABEL_H
