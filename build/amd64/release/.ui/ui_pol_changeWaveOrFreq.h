/********************************************************************************
** Form generated from reading UI file 'pol_changeWaveOrFreq.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POL_CHANGEWAVEORFREQ_H
#define UI_POL_CHANGEWAVEORFREQ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelChangeWaveOrFreq
{
public:
    QPushButton *button_apply;
    QComboBox *WaveList;
    QLabel *label_unit;
    QSpinBox *spinBox_freq;

    void setupUi(QWidget *PanelChangeWaveOrFreq)
    {
        if (PanelChangeWaveOrFreq->objectName().isEmpty())
            PanelChangeWaveOrFreq->setObjectName(QStringLiteral("PanelChangeWaveOrFreq"));
        PanelChangeWaveOrFreq->resize(204, 36);
        button_apply = new QPushButton(PanelChangeWaveOrFreq);
        button_apply->setObjectName(QStringLiteral("button_apply"));
        button_apply->setGeometry(QRect(130, 10, 65, 22));
        WaveList = new QComboBox(PanelChangeWaveOrFreq);
        WaveList->setObjectName(QStringLiteral("WaveList"));
        WaveList->setGeometry(QRect(10, 10, 91, 22));
        label_unit = new QLabel(PanelChangeWaveOrFreq);
        label_unit->setObjectName(QStringLiteral("label_unit"));
        label_unit->setGeometry(QRect(110, 10, 20, 22));
        spinBox_freq = new QSpinBox(PanelChangeWaveOrFreq);
        spinBox_freq->setObjectName(QStringLiteral("spinBox_freq"));
        spinBox_freq->setGeometry(QRect(21, 10, 81, 22));
        spinBox_freq->setMinimum(1);
        spinBox_freq->setMaximum(10000);
        spinBox_freq->setValue(7);

        retranslateUi(PanelChangeWaveOrFreq);

        QMetaObject::connectSlotsByName(PanelChangeWaveOrFreq);
    } // setupUi

    void retranslateUi(QWidget *PanelChangeWaveOrFreq)
    {
        PanelChangeWaveOrFreq->setWindowTitle(QApplication::translate("PanelChangeWaveOrFreq", "Select a Wavelength", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_apply->setToolTip(QApplication::translate("PanelChangeWaveOrFreq", "Set Wavelength", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_apply->setText(QApplication::translate("PanelChangeWaveOrFreq", "Set", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        WaveList->setToolTip(QApplication::translate("PanelChangeWaveOrFreq", "Choose a Wavelength", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_unit->setText(QApplication::translate("PanelChangeWaveOrFreq", "nm", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelChangeWaveOrFreq: public Ui_PanelChangeWaveOrFreq {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_CHANGEWAVEORFREQ_H
