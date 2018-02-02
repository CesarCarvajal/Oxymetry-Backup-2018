/********************************************************************************
** Form generated from reading UI file 'fluidic_control.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLUIDIC_CONTROL_H
#define UI_FLUIDIC_CONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_ControlFluidic
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_connect;
    QTabWidget *tabWidget;
    QWidget *tab;
    QSlider *horizontalSlider_flush;
    QSlider *horizontalSlider_sample;
    QPushButton *pushButton_sample;
    QPushButton *pushButton_flush;
    QLabel *label_2;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QCheckBox *checkBox_hellmanex;
    QWidget *tab_2;
    QLabel *label_10;
    QLabel *label_7;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_9;
    QLabel *label;
    QCheckBox *checkBox_direction;
    QCheckBox *checkBox_brake;
    QLabel *label_12;
    QPushButton *pushButton_apply;
    QLabel *label_status_3;
    QLabel *label_status_4;
    QDoubleSpinBox *doubleSpinBox_rpm;
    QCheckBox *checkBox_pulsationReduction;
    Plot *qwtPlot_stats;
    QLabel *label_rpm;
    QLabel *label_status;

    void setupUi(QMainWindow *ControlFluidic)
    {
        if (ControlFluidic->objectName().isEmpty())
            ControlFluidic->setObjectName(QStringLiteral("ControlFluidic"));
        ControlFluidic->resize(240, 410);
        centralWidget = new QWidget(ControlFluidic);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_connect = new QPushButton(centralWidget);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setGeometry(QRect(150, 10, 75, 25));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 20, 220, 210));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalSlider_flush = new QSlider(tab);
        horizontalSlider_flush->setObjectName(QStringLiteral("horizontalSlider_flush"));
        horizontalSlider_flush->setGeometry(QRect(80, 40, 120, 25));
        horizontalSlider_flush->setMinimum(2000);
        horizontalSlider_flush->setMaximum(4000);
        horizontalSlider_flush->setSingleStep(200);
        horizontalSlider_flush->setPageStep(200);
        horizontalSlider_flush->setSliderPosition(3500);
        horizontalSlider_flush->setOrientation(Qt::Horizontal);
        horizontalSlider_flush->setTickPosition(QSlider::TicksAbove);
        horizontalSlider_flush->setTickInterval(200);
        horizontalSlider_sample = new QSlider(tab);
        horizontalSlider_sample->setObjectName(QStringLiteral("horizontalSlider_sample"));
        horizontalSlider_sample->setGeometry(QRect(80, 150, 120, 25));
        horizontalSlider_sample->setMinimum(300);
        horizontalSlider_sample->setMaximum(1500);
        horizontalSlider_sample->setSingleStep(100);
        horizontalSlider_sample->setPageStep(100);
        horizontalSlider_sample->setValue(900);
        horizontalSlider_sample->setOrientation(Qt::Horizontal);
        horizontalSlider_sample->setTickPosition(QSlider::TicksAbove);
        horizontalSlider_sample->setTickInterval(100);
        pushButton_sample = new QPushButton(tab);
        pushButton_sample->setObjectName(QStringLiteral("pushButton_sample"));
        pushButton_sample->setEnabled(false);
        pushButton_sample->setGeometry(QRect(10, 150, 60, 25));
        pushButton_flush = new QPushButton(tab);
        pushButton_flush->setObjectName(QStringLiteral("pushButton_flush"));
        pushButton_flush->setEnabled(false);
        pushButton_flush->setGeometry(QRect(10, 40, 60, 25));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(80, 30, 120, 5));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/fluidic/colorbar_flush.png")));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(80, 140, 120, 5));
        label_11->setPixmap(QPixmap(QString::fromUtf8(":/fluidic/colorbar_sample.png")));
        label_13 = new QLabel(tab);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(80, 10, 50, 15));
        label_14 = new QLabel(tab);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(150, 10, 50, 15));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_15 = new QLabel(tab);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(80, 105, 50, 15));
        label_16 = new QLabel(tab);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(150, 105, 50, 15));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_17 = new QLabel(tab);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(80, 120, 50, 15));
        label_18 = new QLabel(tab);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(150, 120, 50, 15));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        checkBox_hellmanex = new QCheckBox(tab);
        checkBox_hellmanex->setObjectName(QStringLiteral("checkBox_hellmanex"));
        checkBox_hellmanex->setGeometry(QRect(80, 70, 130, 20));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 10, 20, 21));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(70, 10, 20, 21));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(150, 10, 20, 21));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(130, 10, 20, 21));
        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(50, 10, 20, 21));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(90, 10, 20, 21));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(110, 10, 20, 21));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(30, 10, 20, 21));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 10, 41, 21));
        checkBox_direction = new QCheckBox(tab_2);
        checkBox_direction->setObjectName(QStringLiteral("checkBox_direction"));
        checkBox_direction->setGeometry(QRect(10, 155, 60, 25));
        checkBox_brake = new QCheckBox(tab_2);
        checkBox_brake->setObjectName(QStringLiteral("checkBox_brake"));
        checkBox_brake->setGeometry(QRect(80, 155, 50, 25));
        checkBox_brake->setChecked(true);
        label_12 = new QLabel(tab_2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(170, 30, 41, 21));
        pushButton_apply = new QPushButton(tab_2);
        pushButton_apply->setObjectName(QStringLiteral("pushButton_apply"));
        pushButton_apply->setEnabled(false);
        pushButton_apply->setGeometry(QRect(135, 155, 75, 25));
        label_status_3 = new QLabel(tab_2);
        label_status_3->setObjectName(QStringLiteral("label_status_3"));
        label_status_3->setGeometry(QRect(10, 60, 150, 15));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label_status_3->setFont(font);
        label_status_4 = new QLabel(tab_2);
        label_status_4->setObjectName(QStringLiteral("label_status_4"));
        label_status_4->setGeometry(QRect(90, 80, 30, 25));
        label_status_4->setFont(font);
        doubleSpinBox_rpm = new QDoubleSpinBox(tab_2);
        doubleSpinBox_rpm->setObjectName(QStringLiteral("doubleSpinBox_rpm"));
        doubleSpinBox_rpm->setGeometry(QRect(10, 80, 70, 25));
        doubleSpinBox_rpm->setMaximum(100);
        doubleSpinBox_rpm->setValue(20);
        checkBox_pulsationReduction = new QCheckBox(tab_2);
        checkBox_pulsationReduction->setObjectName(QStringLiteral("checkBox_pulsationReduction"));
        checkBox_pulsationReduction->setGeometry(QRect(10, 125, 200, 25));
        tabWidget->addTab(tab_2, QString());
        qwtPlot_stats = new Plot(centralWidget);
        qwtPlot_stats->setObjectName(QStringLiteral("qwtPlot_stats"));
        qwtPlot_stats->setGeometry(QRect(15, 260, 210, 140));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qwtPlot_stats->sizePolicy().hasHeightForWidth());
        qwtPlot_stats->setSizePolicy(sizePolicy);
        label_rpm = new QLabel(qwtPlot_stats);
        label_rpm->setObjectName(QStringLiteral("label_rpm"));
        label_rpm->setGeometry(QRect(142, 8, 60, 15));
        label_rpm->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);
        label_status = new QLabel(centralWidget);
        label_status->setObjectName(QStringLiteral("label_status"));
        label_status->setGeometry(QRect(10, 235, 220, 20));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_status->setFont(font1);
        label_status->setAlignment(Qt::AlignCenter);
        ControlFluidic->setCentralWidget(centralWidget);
        tabWidget->raise();
        pushButton_connect->raise();
        qwtPlot_stats->raise();
        label_status->raise();

        retranslateUi(ControlFluidic);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ControlFluidic);
    } // setupUi

    void retranslateUi(QMainWindow *ControlFluidic)
    {
        ControlFluidic->setWindowTitle(QApplication::translate("ControlFluidic", "Fluidic circuit", Q_NULLPTR));
        pushButton_connect->setText(QApplication::translate("ControlFluidic", "Connect", Q_NULLPTR));
        pushButton_sample->setText(QApplication::translate("ControlFluidic", "Sample", Q_NULLPTR));
        pushButton_flush->setText(QApplication::translate("ControlFluidic", "Flush", Q_NULLPTR));
        label_2->setText(QString());
        label_11->setText(QString());
        label_13->setText(QApplication::translate("ControlFluidic", "2 ml/min", Q_NULLPTR));
        label_14->setText(QApplication::translate("ControlFluidic", "4 ml/min", Q_NULLPTR));
        label_15->setText(QApplication::translate("ControlFluidic", "0.3 ml/min", Q_NULLPTR));
        label_16->setText(QApplication::translate("ControlFluidic", "1.5 ml/min", Q_NULLPTR));
        label_17->setText(QApplication::translate("ControlFluidic", "200 1/s", Q_NULLPTR));
        label_18->setText(QApplication::translate("ControlFluidic", "1000 1/s", Q_NULLPTR));
        checkBox_hellmanex->setText(QApplication::translate("ControlFluidic", "Flush w/ Hellmanex III", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ControlFluidic", "Auto", Q_NULLPTR));
        label_10->setText(QApplication::translate("ControlFluidic", "1", Q_NULLPTR));
        label_7->setText(QApplication::translate("ControlFluidic", "4", Q_NULLPTR));
        label_3->setText(QApplication::translate("ControlFluidic", "8", Q_NULLPTR));
        label_4->setText(QApplication::translate("ControlFluidic", "7", Q_NULLPTR));
        label_8->setText(QApplication::translate("ControlFluidic", "3", Q_NULLPTR));
        label_6->setText(QApplication::translate("ControlFluidic", "5", Q_NULLPTR));
        label_5->setText(QApplication::translate("ControlFluidic", "6", Q_NULLPTR));
        label_9->setText(QApplication::translate("ControlFluidic", "2", Q_NULLPTR));
        label->setText(QApplication::translate("ControlFluidic", "valve", Q_NULLPTR));
        checkBox_direction->setText(QApplication::translate("ControlFluidic", "direction", Q_NULLPTR));
        checkBox_brake->setText(QApplication::translate("ControlFluidic", "brake", Q_NULLPTR));
        label_12->setText(QApplication::translate("ControlFluidic", "on/off", Q_NULLPTR));
        pushButton_apply->setText(QApplication::translate("ControlFluidic", "Apply", Q_NULLPTR));
        label_status_3->setText(QApplication::translate("ControlFluidic", "Revolutions per minute (RPM)", Q_NULLPTR));
        label_status_4->setText(QApplication::translate("ControlFluidic", "RPM", Q_NULLPTR));
        checkBox_pulsationReduction->setText(QApplication::translate("ControlFluidic", "pulsation reduction", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ControlFluidic", "Manual", Q_NULLPTR));
        label_rpm->setText(QApplication::translate("ControlFluidic", "0.00 RPM", Q_NULLPTR));
        label_status->setText(QApplication::translate("ControlFluidic", "<is connected?>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ControlFluidic: public Ui_ControlFluidic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLUIDIC_CONTROL_H
