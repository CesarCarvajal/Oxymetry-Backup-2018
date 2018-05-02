/********************************************************************************
** Form generated from reading UI file 'pol_configureMeasurement.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POL_CONFIGUREMEASUREMENT_H
#define UI_POL_CONFIGUREMEASUREMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_configurePolMeasure
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    ClickableLabel *label_load;
    QWidget *LoadWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_filename;
    QLineEdit *lineEdit_path;
    QPushButton *pushButton_select;
    QSpacerItem *verticalSpacer_9;
    ClickableLabel *label_basicConf;
    QWidget *ConfigurationLayout;
    QVBoxLayout *verticalLayout_fileconf;
    QFrame *line;
    QLabel *label_Spectrometer;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_BIntTime;
    QDoubleSpinBox *doubleSpinBox_intTime;
    QLabel *label_BIntTime2;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_BNSpec;
    QSpinBox *spinBox_BNSpec;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_BNAve;
    QSpinBox *spinBox_BNAve;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout;
    QLabel *label_maxW1;
    QDoubleSpinBox *doubleSpinBox_maxW;
    QLabel *label_maxW2;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_BNMeas;
    QSpinBox *spinBox_BNMeas;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_BFreq;
    QSpinBox *spinBox_BFreq;
    QLabel *label_BFreq2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_27;
    QLabel *label_minW1;
    QDoubleSpinBox *doubleSpinBox_minW;
    QLabel *label_minW2;
    QSpacerItem *verticalSpacer_13;
    QFrame *line_2;
    QLabel *label_SolConc;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_32;
    QLabel *label_VolGl1;
    QLineEdit *lineEdit_VolG;
    QLabel *label_VolG2;
    QSpacerItem *horizontalSpacer_17;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_MinImp1;
    QLineEdit *lineEdit_MinImp1;
    QLabel *label_MinImp1_2;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_StockImp1;
    QLineEdit *lineEdit_StockImp1;
    QLabel *label_StockImp1_2;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_MaxGluc;
    QLineEdit *lineEdit_MaxGluc;
    QLabel *label_MaxGluc2;
    QSpacerItem *horizontalSpacer_15;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_StockGluc;
    QLineEdit *lineEdit_StockGluc;
    QLabel *label_StockGluc2;
    QSpacerItem *horizontalSpacer_16;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_MinGluc;
    QLineEdit *lineEdit_Mingluc;
    QLabel *label_MinGluc2;
    QSpacerItem *horizontalSpacer_14;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_MaxImp1;
    QLineEdit *lineEdit_MaxImp1;
    QLabel *label_MaxImp1_2;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_MinImp2;
    QLineEdit *lineEdit_MinImp2;
    QLabel *label_MinImp2_2;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_MaxImp2;
    QLineEdit *lineEdit_MaxImp2;
    QLabel *label_MaxImp2_2;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_StockImp2;
    QLineEdit *lineEdit_StockImp2;
    QLabel *label_StockImp2_2;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_33;
    QLabel *label_VolI2;
    QLineEdit *lineEdit_VolI2;
    QLabel *label_VolI22;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_VolI1;
    QLineEdit *lineEdit_VolI1;
    QLabel *label_VolI12;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *checkBox_Glucose;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox_Imp1;
    QSpacerItem *horizontalSpacer_19;
    QHBoxLayout *horizontalLayout_20;
    QCheckBox *checkBox_Imp2;
    QSpacerItem *horizontalSpacer_20;
    QSpacerItem *verticalSpacer_6;
    QFrame *line_3;
    QLabel *label_PumpFlow;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_34;
    QLabel *label_AbsFlow;
    QDoubleSpinBox *doubleSpinBox_AbsFlow;
    QLabel *label_AbsFlow2;
    QHBoxLayout *horizontalLayout_36;
    QLabel *label_NSteps;
    QSpinBox *spinBox_NSteps;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_35;
    QLabel *label_AbsVol;
    QSpinBox *spinBox_AbsVol;
    QLabel *label_AbsVol_2;
    QSpacerItem *verticalSpacer_12;
    QFrame *line_4;
    QLabel *label_MeasurementTime;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_38;
    QLabel *label_Idle;
    QCheckBox *checkBox;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_ShortBreak;
    QSpinBox *spinBox_ShortBreak;
    QLabel *label_ShortBreak2;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_startDelay;
    QDoubleSpinBox *doubleSpinBox_startDelay;
    QLabel *label_startDelay2;
    QHBoxLayout *horizontalLayout_37;
    QLabel *label_LongBreak;
    QSpinBox *spinBox_LongBreak;
    QLabel *label_longBreak2;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_NRepet;
    QSpinBox *spinBox_Nrepet;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_41;
    QSpacerItem *horizontalSpacer_23;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_BtimeInt;
    QLineEdit *lineEdit_BtimeInterval;
    QLabel *label_BtimeInt2;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_timebetweenM;
    QLineEdit *lineEdit_timebetweenM;
    QLabel *label2_timebetweenM;
    QHBoxLayout *horizontalLayout_42;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *timeLayout;
    QLabel *label_timeLabel;
    QLineEdit *timeEdit_timeLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_BFileNamePrev;
    QLineEdit *lineEdit_BFileNamePrev;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_generate;

    void setupUi(QDialog *configurePolMeasure)
    {
        if (configurePolMeasure->objectName().isEmpty())
            configurePolMeasure->setObjectName(QStringLiteral("configurePolMeasure"));
        configurePolMeasure->resize(922, 760);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(configurePolMeasure->sizePolicy().hasHeightForWidth());
        configurePolMeasure->setSizePolicy(sizePolicy);
        configurePolMeasure->setMinimumSize(QSize(922, 760));
        gridLayout = new QGridLayout(configurePolMeasure);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label_load = new ClickableLabel(configurePolMeasure);
        label_load->setObjectName(QStringLiteral("label_load"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_load->sizePolicy().hasHeightForWidth());
        label_load->setSizePolicy(sizePolicy1);
        label_load->setMinimumSize(QSize(15, 0));
        label_load->setMaximumSize(QSize(16777215, 15));
        QFont font;
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label_load->setFont(font);
        label_load->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(label_load);

        LoadWidget = new QWidget(configurePolMeasure);
        LoadWidget->setObjectName(QStringLiteral("LoadWidget"));
        sizePolicy1.setHeightForWidth(LoadWidget->sizePolicy().hasHeightForWidth());
        LoadWidget->setSizePolicy(sizePolicy1);
        horizontalLayout_2 = new QHBoxLayout(LoadWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_filename = new QLabel(LoadWidget);
        label_filename->setObjectName(QStringLiteral("label_filename"));
        sizePolicy1.setHeightForWidth(label_filename->sizePolicy().hasHeightForWidth());
        label_filename->setSizePolicy(sizePolicy1);
        label_filename->setMinimumSize(QSize(0, 15));
        label_filename->setMaximumSize(QSize(16777215, 15));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        label_filename->setFont(font1);

        horizontalLayout_2->addWidget(label_filename);

        lineEdit_path = new QLineEdit(LoadWidget);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));
        lineEdit_path->setEnabled(true);
        lineEdit_path->setMinimumSize(QSize(0, 20));
        lineEdit_path->setMaximumSize(QSize(16777215, 20));
        lineEdit_path->setFrame(false);
        lineEdit_path->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_path);

        pushButton_select = new QPushButton(LoadWidget);
        pushButton_select->setObjectName(QStringLiteral("pushButton_select"));
        pushButton_select->setMinimumSize(QSize(150, 25));
        pushButton_select->setMaximumSize(QSize(16777215, 25));
        pushButton_select->setAutoDefault(false);

        horizontalLayout_2->addWidget(pushButton_select);


        verticalLayout->addWidget(LoadWidget);

        verticalSpacer_9 = new QSpacerItem(10, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_9);

        label_basicConf = new ClickableLabel(configurePolMeasure);
        label_basicConf->setObjectName(QStringLiteral("label_basicConf"));
        sizePolicy1.setHeightForWidth(label_basicConf->sizePolicy().hasHeightForWidth());
        label_basicConf->setSizePolicy(sizePolicy1);
        label_basicConf->setMinimumSize(QSize(0, 15));
        label_basicConf->setMaximumSize(QSize(16777215, 15));
        label_basicConf->setFont(font);
        label_basicConf->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(label_basicConf);

        ConfigurationLayout = new QWidget(configurePolMeasure);
        ConfigurationLayout->setObjectName(QStringLiteral("ConfigurationLayout"));
        sizePolicy1.setHeightForWidth(ConfigurationLayout->sizePolicy().hasHeightForWidth());
        ConfigurationLayout->setSizePolicy(sizePolicy1);
        verticalLayout_fileconf = new QVBoxLayout(ConfigurationLayout);
        verticalLayout_fileconf->setObjectName(QStringLiteral("verticalLayout_fileconf"));
        line = new QFrame(ConfigurationLayout);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_fileconf->addWidget(line);

        label_Spectrometer = new QLabel(ConfigurationLayout);
        label_Spectrometer->setObjectName(QStringLiteral("label_Spectrometer"));
        sizePolicy1.setHeightForWidth(label_Spectrometer->sizePolicy().hasHeightForWidth());
        label_Spectrometer->setSizePolicy(sizePolicy1);
        label_Spectrometer->setMinimumSize(QSize(0, 15));
        label_Spectrometer->setMaximumSize(QSize(16777215, 15));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        label_Spectrometer->setFont(font2);

        verticalLayout_fileconf->addWidget(label_Spectrometer);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        label_BIntTime = new QLabel(ConfigurationLayout);
        label_BIntTime->setObjectName(QStringLiteral("label_BIntTime"));
        label_BIntTime->setMinimumSize(QSize(100, 0));

        horizontalLayout_24->addWidget(label_BIntTime);

        doubleSpinBox_intTime = new QDoubleSpinBox(ConfigurationLayout);
        doubleSpinBox_intTime->setObjectName(QStringLiteral("doubleSpinBox_intTime"));
        doubleSpinBox_intTime->setMinimumSize(QSize(100, 0));
        doubleSpinBox_intTime->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_intTime->setDecimals(1);
        doubleSpinBox_intTime->setMinimum(1);
        doubleSpinBox_intTime->setMaximum(20000);
        doubleSpinBox_intTime->setSingleStep(0.1);
        doubleSpinBox_intTime->setValue(6);

        horizontalLayout_24->addWidget(doubleSpinBox_intTime);

        label_BIntTime2 = new QLabel(ConfigurationLayout);
        label_BIntTime2->setObjectName(QStringLiteral("label_BIntTime2"));
        label_BIntTime2->setMinimumSize(QSize(30, 0));

        horizontalLayout_24->addWidget(label_BIntTime2);


        gridLayout_2->addLayout(horizontalLayout_24, 1, 1, 1, 1);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        label_BNSpec = new QLabel(ConfigurationLayout);
        label_BNSpec->setObjectName(QStringLiteral("label_BNSpec"));
        label_BNSpec->setMinimumSize(QSize(100, 0));
        label_BNSpec->setFrameShape(QFrame::NoFrame);
        label_BNSpec->setFrameShadow(QFrame::Plain);
        label_BNSpec->setMidLineWidth(0);

        horizontalLayout_26->addWidget(label_BNSpec);

        spinBox_BNSpec = new QSpinBox(ConfigurationLayout);
        spinBox_BNSpec->setObjectName(QStringLiteral("spinBox_BNSpec"));
        spinBox_BNSpec->setMinimumSize(QSize(100, 0));
        spinBox_BNSpec->setMaximumSize(QSize(100, 16777215));
        spinBox_BNSpec->setFont(font1);
        spinBox_BNSpec->setWrapping(false);
        spinBox_BNSpec->setFrame(true);
        spinBox_BNSpec->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBox_BNSpec->setAccelerated(false);
        spinBox_BNSpec->setProperty("showGroupSeparator", QVariant(false));
        spinBox_BNSpec->setMinimum(1);
        spinBox_BNSpec->setMaximum(100000);
        spinBox_BNSpec->setSingleStep(100);
        spinBox_BNSpec->setValue(1000);

        horizontalLayout_26->addWidget(spinBox_BNSpec);

        label_10 = new QLabel(ConfigurationLayout);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(30, 0));

        horizontalLayout_26->addWidget(label_10);


        gridLayout_2->addLayout(horizontalLayout_26, 2, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_BNAve = new QLabel(ConfigurationLayout);
        label_BNAve->setObjectName(QStringLiteral("label_BNAve"));
        label_BNAve->setMinimumSize(QSize(100, 0));

        horizontalLayout_11->addWidget(label_BNAve);

        spinBox_BNAve = new QSpinBox(ConfigurationLayout);
        spinBox_BNAve->setObjectName(QStringLiteral("spinBox_BNAve"));
        spinBox_BNAve->setMinimumSize(QSize(100, 0));
        spinBox_BNAve->setMaximumSize(QSize(100, 16777215));
        spinBox_BNAve->setMinimum(1);
        spinBox_BNAve->setMaximum(1000);

        horizontalLayout_11->addWidget(spinBox_BNAve);

        label_11 = new QLabel(ConfigurationLayout);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(30, 0));

        horizontalLayout_11->addWidget(label_11);


        gridLayout_2->addLayout(horizontalLayout_11, 2, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_maxW1 = new QLabel(ConfigurationLayout);
        label_maxW1->setObjectName(QStringLiteral("label_maxW1"));
        label_maxW1->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(label_maxW1);

        doubleSpinBox_maxW = new QDoubleSpinBox(ConfigurationLayout);
        doubleSpinBox_maxW->setObjectName(QStringLiteral("doubleSpinBox_maxW"));
        doubleSpinBox_maxW->setEnabled(true);
        doubleSpinBox_maxW->setMinimumSize(QSize(100, 0));
        doubleSpinBox_maxW->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_maxW->setDecimals(1);
        doubleSpinBox_maxW->setMaximum(10000);
        doubleSpinBox_maxW->setSingleStep(0.1);
        doubleSpinBox_maxW->setValue(750);

        horizontalLayout->addWidget(doubleSpinBox_maxW);

        label_maxW2 = new QLabel(ConfigurationLayout);
        label_maxW2->setObjectName(QStringLiteral("label_maxW2"));
        label_maxW2->setMinimumSize(QSize(30, 0));

        horizontalLayout->addWidget(label_maxW2);


        gridLayout_2->addLayout(horizontalLayout, 3, 1, 1, 1);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        label_BNMeas = new QLabel(ConfigurationLayout);
        label_BNMeas->setObjectName(QStringLiteral("label_BNMeas"));
        label_BNMeas->setMinimumSize(QSize(100, 0));
        label_BNMeas->setToolTipDuration(-1);

        horizontalLayout_23->addWidget(label_BNMeas);

        spinBox_BNMeas = new QSpinBox(ConfigurationLayout);
        spinBox_BNMeas->setObjectName(QStringLiteral("spinBox_BNMeas"));
        spinBox_BNMeas->setMinimumSize(QSize(100, 0));
        spinBox_BNMeas->setMaximumSize(QSize(60, 16777215));
        spinBox_BNMeas->setMinimum(1);
        spinBox_BNMeas->setMaximum(100000);
        spinBox_BNMeas->setValue(51);

        horizontalLayout_23->addWidget(spinBox_BNMeas);

        label_9 = new QLabel(ConfigurationLayout);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(30, 0));
        label_9->setSizeIncrement(QSize(0, 0));

        horizontalLayout_23->addWidget(label_9);


        gridLayout_2->addLayout(horizontalLayout_23, 1, 0, 1, 1);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        label_BFreq = new QLabel(ConfigurationLayout);
        label_BFreq->setObjectName(QStringLiteral("label_BFreq"));
        label_BFreq->setMinimumSize(QSize(100, 0));

        horizontalLayout_25->addWidget(label_BFreq);

        spinBox_BFreq = new QSpinBox(ConfigurationLayout);
        spinBox_BFreq->setObjectName(QStringLiteral("spinBox_BFreq"));
        spinBox_BFreq->setMinimumSize(QSize(100, 0));
        spinBox_BFreq->setMaximumSize(QSize(100, 16777215));
        spinBox_BFreq->setMaximum(50000);
        spinBox_BFreq->setValue(7);

        horizontalLayout_25->addWidget(spinBox_BFreq);

        label_BFreq2 = new QLabel(ConfigurationLayout);
        label_BFreq2->setObjectName(QStringLiteral("label_BFreq2"));
        label_BFreq2->setMinimumSize(QSize(30, 0));

        horizontalLayout_25->addWidget(label_BFreq2);


        gridLayout_2->addLayout(horizontalLayout_25, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(235, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 3, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(235, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 2, 2, 1, 1);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        label_minW1 = new QLabel(ConfigurationLayout);
        label_minW1->setObjectName(QStringLiteral("label_minW1"));
        label_minW1->setMinimumSize(QSize(100, 0));

        horizontalLayout_27->addWidget(label_minW1);

        doubleSpinBox_minW = new QDoubleSpinBox(ConfigurationLayout);
        doubleSpinBox_minW->setObjectName(QStringLiteral("doubleSpinBox_minW"));
        doubleSpinBox_minW->setEnabled(true);
        doubleSpinBox_minW->setMinimumSize(QSize(100, 0));
        doubleSpinBox_minW->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_minW->setDecimals(1);
        doubleSpinBox_minW->setMaximum(10000);
        doubleSpinBox_minW->setSingleStep(0.1);
        doubleSpinBox_minW->setValue(400);

        horizontalLayout_27->addWidget(doubleSpinBox_minW);

        label_minW2 = new QLabel(ConfigurationLayout);
        label_minW2->setObjectName(QStringLiteral("label_minW2"));
        label_minW2->setMinimumSize(QSize(30, 0));

        horizontalLayout_27->addWidget(label_minW2);


        gridLayout_2->addLayout(horizontalLayout_27, 3, 0, 1, 1);


        verticalLayout_fileconf->addLayout(gridLayout_2);

        verticalSpacer_13 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_13);

        line_2 = new QFrame(ConfigurationLayout);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_fileconf->addWidget(line_2);

        label_SolConc = new QLabel(ConfigurationLayout);
        label_SolConc->setObjectName(QStringLiteral("label_SolConc"));
        sizePolicy1.setHeightForWidth(label_SolConc->sizePolicy().hasHeightForWidth());
        label_SolConc->setSizePolicy(sizePolicy1);
        label_SolConc->setMinimumSize(QSize(0, 15));
        label_SolConc->setMaximumSize(QSize(16777215, 15));
        label_SolConc->setFont(font2);

        verticalLayout_fileconf->addWidget(label_SolConc);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setObjectName(QStringLiteral("horizontalLayout_32"));
        label_VolGl1 = new QLabel(ConfigurationLayout);
        label_VolGl1->setObjectName(QStringLiteral("label_VolGl1"));
        label_VolGl1->setMinimumSize(QSize(100, 0));

        horizontalLayout_32->addWidget(label_VolGl1);

        lineEdit_VolG = new QLineEdit(ConfigurationLayout);
        lineEdit_VolG->setObjectName(QStringLiteral("lineEdit_VolG"));
        lineEdit_VolG->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_VolG->sizePolicy().hasHeightForWidth());
        lineEdit_VolG->setSizePolicy(sizePolicy2);
        lineEdit_VolG->setMinimumSize(QSize(100, 0));
        lineEdit_VolG->setMaximumSize(QSize(100, 16777215));
        lineEdit_VolG->setFrame(false);
        lineEdit_VolG->setReadOnly(true);

        horizontalLayout_32->addWidget(lineEdit_VolG);

        label_VolG2 = new QLabel(ConfigurationLayout);
        label_VolG2->setObjectName(QStringLiteral("label_VolG2"));
        label_VolG2->setMinimumSize(QSize(30, 0));

        horizontalLayout_32->addWidget(label_VolG2);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_32->addItem(horizontalSpacer_17);


        gridLayout_3->addLayout(horizontalLayout_32, 4, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_MinImp1 = new QLabel(ConfigurationLayout);
        label_MinImp1->setObjectName(QStringLiteral("label_MinImp1"));
        label_MinImp1->setMinimumSize(QSize(100, 0));

        horizontalLayout_4->addWidget(label_MinImp1);

        lineEdit_MinImp1 = new QLineEdit(ConfigurationLayout);
        lineEdit_MinImp1->setObjectName(QStringLiteral("lineEdit_MinImp1"));
        sizePolicy2.setHeightForWidth(lineEdit_MinImp1->sizePolicy().hasHeightForWidth());
        lineEdit_MinImp1->setSizePolicy(sizePolicy2);
        lineEdit_MinImp1->setMinimumSize(QSize(100, 0));
        lineEdit_MinImp1->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(lineEdit_MinImp1);

        label_MinImp1_2 = new QLabel(ConfigurationLayout);
        label_MinImp1_2->setObjectName(QStringLiteral("label_MinImp1_2"));
        label_MinImp1_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_4->addWidget(label_MinImp1_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        gridLayout_3->addLayout(horizontalLayout_4, 1, 2, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_StockImp1 = new QLabel(ConfigurationLayout);
        label_StockImp1->setObjectName(QStringLiteral("label_StockImp1"));
        label_StockImp1->setMinimumSize(QSize(100, 0));

        horizontalLayout_12->addWidget(label_StockImp1);

        lineEdit_StockImp1 = new QLineEdit(ConfigurationLayout);
        lineEdit_StockImp1->setObjectName(QStringLiteral("lineEdit_StockImp1"));
        sizePolicy2.setHeightForWidth(lineEdit_StockImp1->sizePolicy().hasHeightForWidth());
        lineEdit_StockImp1->setSizePolicy(sizePolicy2);
        lineEdit_StockImp1->setMinimumSize(QSize(100, 0));
        lineEdit_StockImp1->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_12->addWidget(lineEdit_StockImp1);

        label_StockImp1_2 = new QLabel(ConfigurationLayout);
        label_StockImp1_2->setObjectName(QStringLiteral("label_StockImp1_2"));
        label_StockImp1_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_12->addWidget(label_StockImp1_2);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_9);


        gridLayout_3->addLayout(horizontalLayout_12, 3, 2, 1, 1);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_MaxGluc = new QLabel(ConfigurationLayout);
        label_MaxGluc->setObjectName(QStringLiteral("label_MaxGluc"));
        label_MaxGluc->setMinimumSize(QSize(100, 0));

        horizontalLayout_17->addWidget(label_MaxGluc);

        lineEdit_MaxGluc = new QLineEdit(ConfigurationLayout);
        lineEdit_MaxGluc->setObjectName(QStringLiteral("lineEdit_MaxGluc"));
        sizePolicy2.setHeightForWidth(lineEdit_MaxGluc->sizePolicy().hasHeightForWidth());
        lineEdit_MaxGluc->setSizePolicy(sizePolicy2);
        lineEdit_MaxGluc->setMinimumSize(QSize(100, 0));
        lineEdit_MaxGluc->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_17->addWidget(lineEdit_MaxGluc);

        label_MaxGluc2 = new QLabel(ConfigurationLayout);
        label_MaxGluc2->setObjectName(QStringLiteral("label_MaxGluc2"));
        label_MaxGluc2->setMinimumSize(QSize(30, 0));

        horizontalLayout_17->addWidget(label_MaxGluc2);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_15);


        gridLayout_3->addLayout(horizontalLayout_17, 2, 0, 1, 1);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_StockGluc = new QLabel(ConfigurationLayout);
        label_StockGluc->setObjectName(QStringLiteral("label_StockGluc"));
        label_StockGluc->setMinimumSize(QSize(100, 0));

        horizontalLayout_18->addWidget(label_StockGluc);

        lineEdit_StockGluc = new QLineEdit(ConfigurationLayout);
        lineEdit_StockGluc->setObjectName(QStringLiteral("lineEdit_StockGluc"));
        sizePolicy2.setHeightForWidth(lineEdit_StockGluc->sizePolicy().hasHeightForWidth());
        lineEdit_StockGluc->setSizePolicy(sizePolicy2);
        lineEdit_StockGluc->setMinimumSize(QSize(100, 0));
        lineEdit_StockGluc->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_18->addWidget(lineEdit_StockGluc);

        label_StockGluc2 = new QLabel(ConfigurationLayout);
        label_StockGluc2->setObjectName(QStringLiteral("label_StockGluc2"));
        label_StockGluc2->setMinimumSize(QSize(30, 0));

        horizontalLayout_18->addWidget(label_StockGluc2);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_16);


        gridLayout_3->addLayout(horizontalLayout_18, 3, 0, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_MinGluc = new QLabel(ConfigurationLayout);
        label_MinGluc->setObjectName(QStringLiteral("label_MinGluc"));
        label_MinGluc->setMinimumSize(QSize(100, 0));

        horizontalLayout_15->addWidget(label_MinGluc);

        lineEdit_Mingluc = new QLineEdit(ConfigurationLayout);
        lineEdit_Mingluc->setObjectName(QStringLiteral("lineEdit_Mingluc"));
        sizePolicy2.setHeightForWidth(lineEdit_Mingluc->sizePolicy().hasHeightForWidth());
        lineEdit_Mingluc->setSizePolicy(sizePolicy2);
        lineEdit_Mingluc->setMinimumSize(QSize(100, 0));
        lineEdit_Mingluc->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_15->addWidget(lineEdit_Mingluc);

        label_MinGluc2 = new QLabel(ConfigurationLayout);
        label_MinGluc2->setObjectName(QStringLiteral("label_MinGluc2"));
        label_MinGluc2->setMinimumSize(QSize(30, 0));

        horizontalLayout_15->addWidget(label_MinGluc2);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_14);


        gridLayout_3->addLayout(horizontalLayout_15, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_MaxImp1 = new QLabel(ConfigurationLayout);
        label_MaxImp1->setObjectName(QStringLiteral("label_MaxImp1"));
        label_MaxImp1->setMinimumSize(QSize(100, 0));

        horizontalLayout_6->addWidget(label_MaxImp1);

        lineEdit_MaxImp1 = new QLineEdit(ConfigurationLayout);
        lineEdit_MaxImp1->setObjectName(QStringLiteral("lineEdit_MaxImp1"));
        sizePolicy2.setHeightForWidth(lineEdit_MaxImp1->sizePolicy().hasHeightForWidth());
        lineEdit_MaxImp1->setSizePolicy(sizePolicy2);
        lineEdit_MaxImp1->setMinimumSize(QSize(100, 0));
        lineEdit_MaxImp1->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(lineEdit_MaxImp1);

        label_MaxImp1_2 = new QLabel(ConfigurationLayout);
        label_MaxImp1_2->setObjectName(QStringLiteral("label_MaxImp1_2"));
        label_MaxImp1_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_6->addWidget(label_MaxImp1_2);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        gridLayout_3->addLayout(horizontalLayout_6, 2, 2, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_MinImp2 = new QLabel(ConfigurationLayout);
        label_MinImp2->setObjectName(QStringLiteral("label_MinImp2"));
        label_MinImp2->setMinimumSize(QSize(100, 0));

        horizontalLayout_14->addWidget(label_MinImp2);

        lineEdit_MinImp2 = new QLineEdit(ConfigurationLayout);
        lineEdit_MinImp2->setObjectName(QStringLiteral("lineEdit_MinImp2"));
        lineEdit_MinImp2->setEnabled(true);
        sizePolicy2.setHeightForWidth(lineEdit_MinImp2->sizePolicy().hasHeightForWidth());
        lineEdit_MinImp2->setSizePolicy(sizePolicy2);
        lineEdit_MinImp2->setMinimumSize(QSize(100, 0));
        lineEdit_MinImp2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_14->addWidget(lineEdit_MinImp2);

        label_MinImp2_2 = new QLabel(ConfigurationLayout);
        label_MinImp2_2->setObjectName(QStringLiteral("label_MinImp2_2"));
        label_MinImp2_2->setEnabled(true);
        label_MinImp2_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_14->addWidget(label_MinImp2_2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_5);


        gridLayout_3->addLayout(horizontalLayout_14, 1, 3, 1, 1);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_MaxImp2 = new QLabel(ConfigurationLayout);
        label_MaxImp2->setObjectName(QStringLiteral("label_MaxImp2"));
        label_MaxImp2->setEnabled(true);
        label_MaxImp2->setMinimumSize(QSize(100, 0));

        horizontalLayout_16->addWidget(label_MaxImp2);

        lineEdit_MaxImp2 = new QLineEdit(ConfigurationLayout);
        lineEdit_MaxImp2->setObjectName(QStringLiteral("lineEdit_MaxImp2"));
        lineEdit_MaxImp2->setEnabled(true);
        sizePolicy2.setHeightForWidth(lineEdit_MaxImp2->sizePolicy().hasHeightForWidth());
        lineEdit_MaxImp2->setSizePolicy(sizePolicy2);
        lineEdit_MaxImp2->setMinimumSize(QSize(100, 0));
        lineEdit_MaxImp2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_16->addWidget(lineEdit_MaxImp2);

        label_MaxImp2_2 = new QLabel(ConfigurationLayout);
        label_MaxImp2_2->setObjectName(QStringLiteral("label_MaxImp2_2"));
        label_MaxImp2_2->setEnabled(true);
        label_MaxImp2_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_16->addWidget(label_MaxImp2_2);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_11);


        gridLayout_3->addLayout(horizontalLayout_16, 2, 3, 1, 1);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_StockImp2 = new QLabel(ConfigurationLayout);
        label_StockImp2->setObjectName(QStringLiteral("label_StockImp2"));
        label_StockImp2->setEnabled(true);
        label_StockImp2->setMinimumSize(QSize(100, 0));

        horizontalLayout_19->addWidget(label_StockImp2);

        lineEdit_StockImp2 = new QLineEdit(ConfigurationLayout);
        lineEdit_StockImp2->setObjectName(QStringLiteral("lineEdit_StockImp2"));
        lineEdit_StockImp2->setEnabled(true);
        sizePolicy2.setHeightForWidth(lineEdit_StockImp2->sizePolicy().hasHeightForWidth());
        lineEdit_StockImp2->setSizePolicy(sizePolicy2);
        lineEdit_StockImp2->setMinimumSize(QSize(100, 0));
        lineEdit_StockImp2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_19->addWidget(lineEdit_StockImp2);

        label_StockImp2_2 = new QLabel(ConfigurationLayout);
        label_StockImp2_2->setObjectName(QStringLiteral("label_StockImp2_2"));
        label_StockImp2_2->setEnabled(true);
        label_StockImp2_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_19->addWidget(label_StockImp2_2);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_12);


        gridLayout_3->addLayout(horizontalLayout_19, 3, 3, 1, 1);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setObjectName(QStringLiteral("horizontalLayout_33"));
        label_VolI2 = new QLabel(ConfigurationLayout);
        label_VolI2->setObjectName(QStringLiteral("label_VolI2"));
        label_VolI2->setMinimumSize(QSize(100, 0));

        horizontalLayout_33->addWidget(label_VolI2);

        lineEdit_VolI2 = new QLineEdit(ConfigurationLayout);
        lineEdit_VolI2->setObjectName(QStringLiteral("lineEdit_VolI2"));
        lineEdit_VolI2->setEnabled(true);
        sizePolicy2.setHeightForWidth(lineEdit_VolI2->sizePolicy().hasHeightForWidth());
        lineEdit_VolI2->setSizePolicy(sizePolicy2);
        lineEdit_VolI2->setMinimumSize(QSize(100, 0));
        lineEdit_VolI2->setMaximumSize(QSize(100, 16777215));
        lineEdit_VolI2->setFrame(false);
        lineEdit_VolI2->setReadOnly(true);

        horizontalLayout_33->addWidget(lineEdit_VolI2);

        label_VolI22 = new QLabel(ConfigurationLayout);
        label_VolI22->setObjectName(QStringLiteral("label_VolI22"));
        label_VolI22->setMinimumSize(QSize(30, 0));

        horizontalLayout_33->addWidget(label_VolI22);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_33->addItem(horizontalSpacer_13);


        gridLayout_3->addLayout(horizontalLayout_33, 4, 3, 1, 1);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        label_VolI1 = new QLabel(ConfigurationLayout);
        label_VolI1->setObjectName(QStringLiteral("label_VolI1"));
        label_VolI1->setMinimumSize(QSize(100, 0));

        horizontalLayout_30->addWidget(label_VolI1);

        lineEdit_VolI1 = new QLineEdit(ConfigurationLayout);
        lineEdit_VolI1->setObjectName(QStringLiteral("lineEdit_VolI1"));
        lineEdit_VolI1->setEnabled(true);
        sizePolicy2.setHeightForWidth(lineEdit_VolI1->sizePolicy().hasHeightForWidth());
        lineEdit_VolI1->setSizePolicy(sizePolicy2);
        lineEdit_VolI1->setMinimumSize(QSize(100, 0));
        lineEdit_VolI1->setMaximumSize(QSize(100, 16777215));
        lineEdit_VolI1->setFrame(false);
        lineEdit_VolI1->setReadOnly(true);

        horizontalLayout_30->addWidget(lineEdit_VolI1);

        label_VolI12 = new QLabel(ConfigurationLayout);
        label_VolI12->setObjectName(QStringLiteral("label_VolI12"));
        label_VolI12->setMinimumSize(QSize(30, 0));

        horizontalLayout_30->addWidget(label_VolI12);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_30->addItem(horizontalSpacer_10);


        gridLayout_3->addLayout(horizontalLayout_30, 4, 2, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        checkBox_Glucose = new QCheckBox(ConfigurationLayout);
        checkBox_Glucose->setObjectName(QStringLiteral("checkBox_Glucose"));
        checkBox_Glucose->setMinimumSize(QSize(240, 0));
        checkBox_Glucose->setMaximumSize(QSize(230, 16777215));
        checkBox_Glucose->setLayoutDirection(Qt::LeftToRight);
        checkBox_Glucose->setAutoFillBackground(false);
        checkBox_Glucose->setChecked(true);
        checkBox_Glucose->setTristate(false);

        horizontalLayout_5->addWidget(checkBox_Glucose);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_18);


        gridLayout_3->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        checkBox_Imp1 = new QCheckBox(ConfigurationLayout);
        checkBox_Imp1->setObjectName(QStringLiteral("checkBox_Imp1"));
        checkBox_Imp1->setMinimumSize(QSize(240, 0));
        checkBox_Imp1->setMaximumSize(QSize(230, 16777215));
        checkBox_Imp1->setChecked(true);

        horizontalLayout_10->addWidget(checkBox_Imp1);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_19);


        gridLayout_3->addLayout(horizontalLayout_10, 0, 2, 1, 1);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        checkBox_Imp2 = new QCheckBox(ConfigurationLayout);
        checkBox_Imp2->setObjectName(QStringLiteral("checkBox_Imp2"));
        checkBox_Imp2->setEnabled(true);
        checkBox_Imp2->setMinimumSize(QSize(240, 0));
        checkBox_Imp2->setMaximumSize(QSize(230, 16777215));

        horizontalLayout_20->addWidget(checkBox_Imp2);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_20);


        gridLayout_3->addLayout(horizontalLayout_20, 0, 3, 1, 1);


        verticalLayout_fileconf->addLayout(gridLayout_3);

        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_6);

        line_3 = new QFrame(ConfigurationLayout);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_fileconf->addWidget(line_3);

        label_PumpFlow = new QLabel(ConfigurationLayout);
        label_PumpFlow->setObjectName(QStringLiteral("label_PumpFlow"));
        sizePolicy1.setHeightForWidth(label_PumpFlow->sizePolicy().hasHeightForWidth());
        label_PumpFlow->setSizePolicy(sizePolicy1);
        label_PumpFlow->setMinimumSize(QSize(0, 15));
        label_PumpFlow->setMaximumSize(QSize(16777215, 15));
        label_PumpFlow->setSizeIncrement(QSize(0, 0));
        label_PumpFlow->setFont(font2);

        verticalLayout_fileconf->addWidget(label_PumpFlow);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setObjectName(QStringLiteral("horizontalLayout_34"));
        label_AbsFlow = new QLabel(ConfigurationLayout);
        label_AbsFlow->setObjectName(QStringLiteral("label_AbsFlow"));
        label_AbsFlow->setMinimumSize(QSize(100, 0));

        horizontalLayout_34->addWidget(label_AbsFlow);

        doubleSpinBox_AbsFlow = new QDoubleSpinBox(ConfigurationLayout);
        doubleSpinBox_AbsFlow->setObjectName(QStringLiteral("doubleSpinBox_AbsFlow"));
        sizePolicy2.setHeightForWidth(doubleSpinBox_AbsFlow->sizePolicy().hasHeightForWidth());
        doubleSpinBox_AbsFlow->setSizePolicy(sizePolicy2);
        doubleSpinBox_AbsFlow->setMinimumSize(QSize(100, 0));
        doubleSpinBox_AbsFlow->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_AbsFlow->setMaximum(500);
        doubleSpinBox_AbsFlow->setSingleStep(0.05);
        doubleSpinBox_AbsFlow->setValue(18.75);

        horizontalLayout_34->addWidget(doubleSpinBox_AbsFlow);

        label_AbsFlow2 = new QLabel(ConfigurationLayout);
        label_AbsFlow2->setObjectName(QStringLiteral("label_AbsFlow2"));
        label_AbsFlow2->setMinimumSize(QSize(30, 0));

        horizontalLayout_34->addWidget(label_AbsFlow2);


        gridLayout_4->addLayout(horizontalLayout_34, 1, 0, 1, 1);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setObjectName(QStringLiteral("horizontalLayout_36"));
        label_NSteps = new QLabel(ConfigurationLayout);
        label_NSteps->setObjectName(QStringLiteral("label_NSteps"));
        label_NSteps->setMinimumSize(QSize(100, 0));

        horizontalLayout_36->addWidget(label_NSteps);

        spinBox_NSteps = new QSpinBox(ConfigurationLayout);
        spinBox_NSteps->setObjectName(QStringLiteral("spinBox_NSteps"));
        spinBox_NSteps->setMinimumSize(QSize(100, 0));
        spinBox_NSteps->setMaximumSize(QSize(100, 16777215));
        spinBox_NSteps->setMinimum(1);
        spinBox_NSteps->setMaximum(30);
        spinBox_NSteps->setValue(5);

        horizontalLayout_36->addWidget(spinBox_NSteps);

        label_2 = new QLabel(ConfigurationLayout);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_36->addWidget(label_2);


        gridLayout_4->addLayout(horizontalLayout_36, 1, 2, 1, 1);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName(QStringLiteral("horizontalLayout_35"));
        label_AbsVol = new QLabel(ConfigurationLayout);
        label_AbsVol->setObjectName(QStringLiteral("label_AbsVol"));
        label_AbsVol->setMinimumSize(QSize(100, 0));

        horizontalLayout_35->addWidget(label_AbsVol);

        spinBox_AbsVol = new QSpinBox(ConfigurationLayout);
        spinBox_AbsVol->setObjectName(QStringLiteral("spinBox_AbsVol"));
        sizePolicy2.setHeightForWidth(spinBox_AbsVol->sizePolicy().hasHeightForWidth());
        spinBox_AbsVol->setSizePolicy(sizePolicy2);
        spinBox_AbsVol->setMinimumSize(QSize(100, 0));
        spinBox_AbsVol->setMaximumSize(QSize(100, 16777215));
        spinBox_AbsVol->setMaximum(100000);
        spinBox_AbsVol->setValue(25);

        horizontalLayout_35->addWidget(spinBox_AbsVol);

        label_AbsVol_2 = new QLabel(ConfigurationLayout);
        label_AbsVol_2->setObjectName(QStringLiteral("label_AbsVol_2"));
        label_AbsVol_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_35->addWidget(label_AbsVol_2);


        gridLayout_4->addLayout(horizontalLayout_35, 1, 1, 1, 1);


        verticalLayout_fileconf->addLayout(gridLayout_4);

        verticalSpacer_12 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_12);

        line_4 = new QFrame(ConfigurationLayout);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_fileconf->addWidget(line_4);

        label_MeasurementTime = new QLabel(ConfigurationLayout);
        label_MeasurementTime->setObjectName(QStringLiteral("label_MeasurementTime"));
        sizePolicy1.setHeightForWidth(label_MeasurementTime->sizePolicy().hasHeightForWidth());
        label_MeasurementTime->setSizePolicy(sizePolicy1);
        label_MeasurementTime->setMinimumSize(QSize(0, 15));
        label_MeasurementTime->setMaximumSize(QSize(16777215, 15));
        label_MeasurementTime->setFont(font2);

        verticalLayout_fileconf->addWidget(label_MeasurementTime);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setObjectName(QStringLiteral("horizontalLayout_38"));
        label_Idle = new QLabel(ConfigurationLayout);
        label_Idle->setObjectName(QStringLiteral("label_Idle"));
        label_Idle->setMinimumSize(QSize(100, 0));

        horizontalLayout_38->addWidget(label_Idle);

        checkBox = new QCheckBox(ConfigurationLayout);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy3);
        checkBox->setMinimumSize(QSize(100, 0));
        checkBox->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_38->addWidget(checkBox);

        label_3 = new QLabel(ConfigurationLayout);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(30, 0));

        horizontalLayout_38->addWidget(label_3);


        gridLayout_5->addLayout(horizontalLayout_38, 1, 3, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_ShortBreak = new QLabel(ConfigurationLayout);
        label_ShortBreak->setObjectName(QStringLiteral("label_ShortBreak"));
        label_ShortBreak->setMinimumSize(QSize(100, 0));

        horizontalLayout_7->addWidget(label_ShortBreak);

        spinBox_ShortBreak = new QSpinBox(ConfigurationLayout);
        spinBox_ShortBreak->setObjectName(QStringLiteral("spinBox_ShortBreak"));
        spinBox_ShortBreak->setMinimumSize(QSize(100, 0));
        spinBox_ShortBreak->setMaximumSize(QSize(100, 16777215));
        spinBox_ShortBreak->setMaximum(1000000);
        spinBox_ShortBreak->setValue(1);

        horizontalLayout_7->addWidget(spinBox_ShortBreak);

        label_ShortBreak2 = new QLabel(ConfigurationLayout);
        label_ShortBreak2->setObjectName(QStringLiteral("label_ShortBreak2"));
        label_ShortBreak2->setMinimumSize(QSize(30, 0));

        horizontalLayout_7->addWidget(label_ShortBreak2);


        gridLayout_5->addLayout(horizontalLayout_7, 1, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_startDelay = new QLabel(ConfigurationLayout);
        label_startDelay->setObjectName(QStringLiteral("label_startDelay"));
        label_startDelay->setMinimumSize(QSize(100, 0));

        horizontalLayout_13->addWidget(label_startDelay);

        doubleSpinBox_startDelay = new QDoubleSpinBox(ConfigurationLayout);
        doubleSpinBox_startDelay->setObjectName(QStringLiteral("doubleSpinBox_startDelay"));
        doubleSpinBox_startDelay->setMinimumSize(QSize(100, 0));
        doubleSpinBox_startDelay->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_startDelay->setDecimals(3);
        doubleSpinBox_startDelay->setMaximum(1e+7);
        doubleSpinBox_startDelay->setSingleStep(0.001);

        horizontalLayout_13->addWidget(doubleSpinBox_startDelay);

        label_startDelay2 = new QLabel(ConfigurationLayout);
        label_startDelay2->setObjectName(QStringLiteral("label_startDelay2"));
        label_startDelay2->setMinimumSize(QSize(30, 0));
        label_startDelay2->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_13->addWidget(label_startDelay2);


        gridLayout_5->addLayout(horizontalLayout_13, 2, 0, 1, 1);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setObjectName(QStringLiteral("horizontalLayout_37"));
        label_LongBreak = new QLabel(ConfigurationLayout);
        label_LongBreak->setObjectName(QStringLiteral("label_LongBreak"));
        label_LongBreak->setMinimumSize(QSize(100, 0));

        horizontalLayout_37->addWidget(label_LongBreak);

        spinBox_LongBreak = new QSpinBox(ConfigurationLayout);
        spinBox_LongBreak->setObjectName(QStringLiteral("spinBox_LongBreak"));
        spinBox_LongBreak->setMinimumSize(QSize(100, 0));
        spinBox_LongBreak->setMaximumSize(QSize(100, 16777215));
        spinBox_LongBreak->setMaximum(10000000);
        spinBox_LongBreak->setValue(30);

        horizontalLayout_37->addWidget(spinBox_LongBreak);

        label_longBreak2 = new QLabel(ConfigurationLayout);
        label_longBreak2->setObjectName(QStringLiteral("label_longBreak2"));
        label_longBreak2->setMinimumSize(QSize(30, 0));

        horizontalLayout_37->addWidget(label_longBreak2);


        gridLayout_5->addLayout(horizontalLayout_37, 1, 1, 1, 1);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setObjectName(QStringLiteral("horizontalLayout_39"));
        label_NRepet = new QLabel(ConfigurationLayout);
        label_NRepet->setObjectName(QStringLiteral("label_NRepet"));
        label_NRepet->setMinimumSize(QSize(100, 0));

        horizontalLayout_39->addWidget(label_NRepet);

        spinBox_Nrepet = new QSpinBox(ConfigurationLayout);
        spinBox_Nrepet->setObjectName(QStringLiteral("spinBox_Nrepet"));
        spinBox_Nrepet->setEnabled(false);
        spinBox_Nrepet->setMinimumSize(QSize(100, 0));
        spinBox_Nrepet->setMaximumSize(QSize(100, 16777215));
        spinBox_Nrepet->setMaximum(1000);

        horizontalLayout_39->addWidget(spinBox_Nrepet);

        label_4 = new QLabel(ConfigurationLayout);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(30, 0));

        horizontalLayout_39->addWidget(label_4);


        gridLayout_5->addLayout(horizontalLayout_39, 2, 1, 1, 1);

        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setObjectName(QStringLiteral("horizontalLayout_41"));
        horizontalSpacer_23 = new QSpacerItem(235, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_41->addItem(horizontalSpacer_23);


        gridLayout_5->addLayout(horizontalLayout_41, 2, 3, 1, 1);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setObjectName(QStringLiteral("horizontalLayout_44"));
        label_BtimeInt = new QLabel(ConfigurationLayout);
        label_BtimeInt->setObjectName(QStringLiteral("label_BtimeInt"));
        label_BtimeInt->setMinimumSize(QSize(100, 0));
        label_BtimeInt->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_44->addWidget(label_BtimeInt);

        lineEdit_BtimeInterval = new QLineEdit(ConfigurationLayout);
        lineEdit_BtimeInterval->setObjectName(QStringLiteral("lineEdit_BtimeInterval"));
        lineEdit_BtimeInterval->setEnabled(true);
        lineEdit_BtimeInterval->setMinimumSize(QSize(100, 0));
        lineEdit_BtimeInterval->setMaximumSize(QSize(100, 16777215));
        lineEdit_BtimeInterval->setFrame(false);
        lineEdit_BtimeInterval->setReadOnly(true);

        horizontalLayout_44->addWidget(lineEdit_BtimeInterval);

        label_BtimeInt2 = new QLabel(ConfigurationLayout);
        label_BtimeInt2->setObjectName(QStringLiteral("label_BtimeInt2"));
        label_BtimeInt2->setMinimumSize(QSize(30, 0));

        horizontalLayout_44->addWidget(label_BtimeInt2);


        gridLayout_5->addLayout(horizontalLayout_44, 3, 0, 1, 1);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setObjectName(QStringLiteral("horizontalLayout_45"));
        label_timebetweenM = new QLabel(ConfigurationLayout);
        label_timebetweenM->setObjectName(QStringLiteral("label_timebetweenM"));
        label_timebetweenM->setMinimumSize(QSize(100, 0));
        label_timebetweenM->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_45->addWidget(label_timebetweenM);

        lineEdit_timebetweenM = new QLineEdit(ConfigurationLayout);
        lineEdit_timebetweenM->setObjectName(QStringLiteral("lineEdit_timebetweenM"));
        lineEdit_timebetweenM->setEnabled(true);
        lineEdit_timebetweenM->setMinimumSize(QSize(100, 0));
        lineEdit_timebetweenM->setMaximumSize(QSize(100, 16777215));
        lineEdit_timebetweenM->setFrame(false);
        lineEdit_timebetweenM->setReadOnly(true);
        lineEdit_timebetweenM->setClearButtonEnabled(false);

        horizontalLayout_45->addWidget(lineEdit_timebetweenM);

        label2_timebetweenM = new QLabel(ConfigurationLayout);
        label2_timebetweenM->setObjectName(QStringLiteral("label2_timebetweenM"));
        label2_timebetweenM->setMinimumSize(QSize(30, 0));

        horizontalLayout_45->addWidget(label2_timebetweenM);


        gridLayout_5->addLayout(horizontalLayout_45, 3, 1, 1, 1);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setObjectName(QStringLiteral("horizontalLayout_42"));
        horizontalSpacer_3 = new QSpacerItem(235, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_42->addItem(horizontalSpacer_3);


        gridLayout_5->addLayout(horizontalLayout_42, 3, 3, 1, 1);


        verticalLayout_fileconf->addLayout(gridLayout_5);

        verticalSpacer_5 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_5);

        timeLayout = new QHBoxLayout();
        timeLayout->setObjectName(QStringLiteral("timeLayout"));
        label_timeLabel = new QLabel(ConfigurationLayout);
        label_timeLabel->setObjectName(QStringLiteral("label_timeLabel"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_timeLabel->sizePolicy().hasHeightForWidth());
        label_timeLabel->setSizePolicy(sizePolicy4);
        label_timeLabel->setMinimumSize(QSize(150, 0));

        timeLayout->addWidget(label_timeLabel);

        timeEdit_timeLabel = new QLineEdit(ConfigurationLayout);
        timeEdit_timeLabel->setObjectName(QStringLiteral("timeEdit_timeLabel"));
        sizePolicy3.setHeightForWidth(timeEdit_timeLabel->sizePolicy().hasHeightForWidth());
        timeEdit_timeLabel->setSizePolicy(sizePolicy3);
        timeEdit_timeLabel->setMinimumSize(QSize(0, 0));
        timeEdit_timeLabel->setMaximumSize(QSize(16777215, 16777215));
        timeEdit_timeLabel->setFrame(false);
        timeEdit_timeLabel->setReadOnly(true);

        timeLayout->addWidget(timeEdit_timeLabel);


        verticalLayout_fileconf->addLayout(timeLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_BFileNamePrev = new QLabel(ConfigurationLayout);
        label_BFileNamePrev->setObjectName(QStringLiteral("label_BFileNamePrev"));
        sizePolicy4.setHeightForWidth(label_BFileNamePrev->sizePolicy().hasHeightForWidth());
        label_BFileNamePrev->setSizePolicy(sizePolicy4);
        label_BFileNamePrev->setMinimumSize(QSize(150, 0));

        horizontalLayout_3->addWidget(label_BFileNamePrev);

        lineEdit_BFileNamePrev = new QLineEdit(ConfigurationLayout);
        lineEdit_BFileNamePrev->setObjectName(QStringLiteral("lineEdit_BFileNamePrev"));
        lineEdit_BFileNamePrev->setEnabled(true);
        lineEdit_BFileNamePrev->setFrame(false);
        lineEdit_BFileNamePrev->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_BFileNamePrev);


        verticalLayout_fileconf->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(ConfigurationLayout);

        verticalSpacer_4 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer = new QSpacerItem(252, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        pushButton_cancel = new QPushButton(configurePolMeasure);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setMinimumSize(QSize(150, 25));
        pushButton_cancel->setAutoDefault(false);

        horizontalLayout_9->addWidget(pushButton_cancel);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        pushButton_generate = new QPushButton(configurePolMeasure);
        pushButton_generate->setObjectName(QStringLiteral("pushButton_generate"));
        pushButton_generate->setEnabled(true);
        pushButton_generate->setMinimumSize(QSize(150, 25));
        pushButton_generate->setAutoDefault(false);

        horizontalLayout_9->addWidget(pushButton_generate);


        verticalLayout->addLayout(horizontalLayout_9);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(configurePolMeasure);

        pushButton_select->setDefault(false);


        QMetaObject::connectSlotsByName(configurePolMeasure);
    } // setupUi

    void retranslateUi(QDialog *configurePolMeasure)
    {
        configurePolMeasure->setWindowTitle(QApplication::translate("configurePolMeasure", "Polarimeter Measurement Configuration", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_load->setToolTip(QApplication::translate("configurePolMeasure", "Hide/Show Loading Configuration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_load->setText(QApplication::translate("configurePolMeasure", "< Load Configuration:", Q_NULLPTR));
        label_filename->setText(QApplication::translate("configurePolMeasure", "Filename:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_path->setToolTip(QApplication::translate("configurePolMeasure", "Configuration File URL", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_path->setText(QApplication::translate("configurePolMeasure", "Please select a configuration file", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_select->setToolTip(QApplication::translate("configurePolMeasure", "Load a Configuration File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_select->setText(QApplication::translate("configurePolMeasure", "Load", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_basicConf->setToolTip(QApplication::translate("configurePolMeasure", "Hide/Show Create Configuration File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_basicConf->setText(QApplication::translate("configurePolMeasure", "< Create Configuration:", Q_NULLPTR));
        label_Spectrometer->setText(QApplication::translate("configurePolMeasure", "Spectrometer:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_BIntTime->setToolTip(QApplication::translate("configurePolMeasure", "What's the Integration Time?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BIntTime->setText(QApplication::translate("configurePolMeasure", "Integration Time: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        doubleSpinBox_intTime->setToolTip(QApplication::translate("configurePolMeasure", "Insert integration time", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BIntTime2->setText(QApplication::translate("configurePolMeasure", "ms", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_BNSpec->setToolTip(QApplication::translate("configurePolMeasure", "How many spectra?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BNSpec->setText(QApplication::translate("configurePolMeasure", "Nr. Spectra: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        spinBox_BNSpec->setToolTip(QApplication::translate("configurePolMeasure", "Insert number of spectra", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_10->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_BNAve->setToolTip(QApplication::translate("configurePolMeasure", "How many averages?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BNAve->setText(QApplication::translate("configurePolMeasure", "Nr. Averages: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        spinBox_BNAve->setToolTip(QApplication::translate("configurePolMeasure", "Insert number of averages", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_11->setText(QString());
        label_maxW1->setText(QApplication::translate("configurePolMeasure", "Max. Wavelength:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        doubleSpinBox_maxW->setToolTip(QApplication::translate("configurePolMeasure", "Insert maximum wavelength", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_maxW2->setText(QApplication::translate("configurePolMeasure", "nm", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_BNMeas->setToolTip(QApplication::translate("configurePolMeasure", "How many Concentrations to Measure?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        label_BNMeas->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        label_BNMeas->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        label_BNMeas->setText(QApplication::translate("configurePolMeasure", "Nr. Measurements:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        spinBox_BNMeas->setToolTip(QApplication::translate("configurePolMeasure", "Insert number of concentrations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_9->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_BFreq->setToolTip(QApplication::translate("configurePolMeasure", "What's the Modulation Frequency?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BFreq->setText(QApplication::translate("configurePolMeasure", "Frequency: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        spinBox_BFreq->setToolTip(QApplication::translate("configurePolMeasure", "Insert modulation frequency", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        spinBox_BFreq->setSuffix(QString());
        label_BFreq2->setText(QApplication::translate("configurePolMeasure", "Hz", Q_NULLPTR));
        label_minW1->setText(QApplication::translate("configurePolMeasure", "Min. Wavelength:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        doubleSpinBox_minW->setToolTip(QApplication::translate("configurePolMeasure", "Insert minimum wavelength", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_minW2->setText(QApplication::translate("configurePolMeasure", "nm", Q_NULLPTR));
        label_SolConc->setText(QApplication::translate("configurePolMeasure", "Solutions Concentration:", Q_NULLPTR));
        label_VolGl1->setText(QApplication::translate("configurePolMeasure", "Volume Glucose:", Q_NULLPTR));
        lineEdit_VolG->setText(QApplication::translate("configurePolMeasure", "318.75", Q_NULLPTR));
        label_VolG2->setText(QApplication::translate("configurePolMeasure", "ml", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_MinImp1->setToolTip(QApplication::translate("configurePolMeasure", "Minimum Impurity 1 Concentration?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_MinImp1->setText(QApplication::translate("configurePolMeasure", "Min. Impurity 1: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_MinImp1->setToolTip(QApplication::translate("configurePolMeasure", "Minimum Impurity 1 Concentration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_MinImp1->setText(QApplication::translate("configurePolMeasure", "0", Q_NULLPTR));
        label_MinImp1_2->setText(QApplication::translate("configurePolMeasure", "g/l", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_StockImp1->setToolTip(QApplication::translate("configurePolMeasure", "Which concentration of impurity 1 is in stock?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_StockImp1->setText(QApplication::translate("configurePolMeasure", "Stock Impurity 1:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_StockImp1->setToolTip(QApplication::translate("configurePolMeasure", "Concentration of Impurity 1 in Stock", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_StockImp1->setText(QApplication::translate("configurePolMeasure", "4", Q_NULLPTR));
        label_StockImp1_2->setText(QApplication::translate("configurePolMeasure", "g/l", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_MaxGluc->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Glucose Concentration?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_MaxGluc->setText(QApplication::translate("configurePolMeasure", "Max. Glucose: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_MaxGluc->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Glucose Concentration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_MaxGluc->setText(QApplication::translate("configurePolMeasure", "500", Q_NULLPTR));
        label_MaxGluc2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_StockGluc->setToolTip(QApplication::translate("configurePolMeasure", "Which concentration of glucose is in stock?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_StockGluc->setText(QApplication::translate("configurePolMeasure", "Stock Glucose:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_StockGluc->setToolTip(QApplication::translate("configurePolMeasure", "Concentration of Glucose in Stock", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_StockGluc->setText(QApplication::translate("configurePolMeasure", "1000", Q_NULLPTR));
        label_StockGluc2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_MinGluc->setToolTip(QApplication::translate("configurePolMeasure", "Minimum Glucose Concentration?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_MinGluc->setText(QApplication::translate("configurePolMeasure", "Min. Glucose:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_Mingluc->setToolTip(QApplication::translate("configurePolMeasure", "Minimum Glucose Concentration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_Mingluc->setText(QApplication::translate("configurePolMeasure", "0", Q_NULLPTR));
        label_MinGluc2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_MaxImp1->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Impurity 1 Concentration?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_MaxImp1->setText(QApplication::translate("configurePolMeasure", "Max. Impurity 1: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_MaxImp1->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Impurity 1 Concentration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_MaxImp1->setText(QApplication::translate("configurePolMeasure", "2", Q_NULLPTR));
        label_MaxImp1_2->setText(QApplication::translate("configurePolMeasure", "g/l", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_MinImp2->setToolTip(QApplication::translate("configurePolMeasure", "Minimum Impurity 2 Concentration?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_MinImp2->setText(QApplication::translate("configurePolMeasure", "Min. Impurity 2: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_MinImp2->setToolTip(QApplication::translate("configurePolMeasure", "Minimum Impurity 2 Concentration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_MinImp2->setText(QApplication::translate("configurePolMeasure", "0", Q_NULLPTR));
        label_MinImp2_2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_MaxImp2->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Impurity 2 Concentration?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_MaxImp2->setText(QApplication::translate("configurePolMeasure", "Max. Impurity 2:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_MaxImp2->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Impurity 2 Concentration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_MaxImp2->setText(QApplication::translate("configurePolMeasure", "500", Q_NULLPTR));
        label_MaxImp2_2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_StockImp2->setToolTip(QApplication::translate("configurePolMeasure", "Which concentration of impurity 2 is in stock?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_StockImp2->setText(QApplication::translate("configurePolMeasure", "Stock Impurity 2:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_StockImp2->setToolTip(QApplication::translate("configurePolMeasure", "Concentration of Impurity 2 in Stock", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_StockImp2->setText(QApplication::translate("configurePolMeasure", "0", Q_NULLPTR));
        label_StockImp2_2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
        label_VolI2->setText(QApplication::translate("configurePolMeasure", "Volume Impurity 2:", Q_NULLPTR));
        lineEdit_VolI2->setText(QApplication::translate("configurePolMeasure", "0", Q_NULLPTR));
        label_VolI22->setText(QApplication::translate("configurePolMeasure", "ml", Q_NULLPTR));
        label_VolI1->setText(QApplication::translate("configurePolMeasure", "Volume Impurity 1:", Q_NULLPTR));
        lineEdit_VolI1->setText(QApplication::translate("configurePolMeasure", "318.75", Q_NULLPTR));
        label_VolI12->setText(QApplication::translate("configurePolMeasure", "ml", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_Glucose->setToolTip(QApplication::translate("configurePolMeasure", "Include/Remove Glucose", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_Glucose->setText(QApplication::translate("configurePolMeasure", "Glucose", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_Imp1->setToolTip(QApplication::translate("configurePolMeasure", "Include/Remove Impurity 1", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_Imp1->setText(QApplication::translate("configurePolMeasure", "Impurity 1", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_Imp2->setToolTip(QApplication::translate("configurePolMeasure", "Include/Remove Impurity 2", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_Imp2->setText(QApplication::translate("configurePolMeasure", "Impurity 2", Q_NULLPTR));
        label_PumpFlow->setText(QApplication::translate("configurePolMeasure", "Pumps Flow:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_AbsFlow->setToolTip(QApplication::translate("configurePolMeasure", "Absolute Flow for Cuvette Filling", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_AbsFlow->setText(QApplication::translate("configurePolMeasure", "Absolute Flow:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        doubleSpinBox_AbsFlow->setToolTip(QApplication::translate("configurePolMeasure", "Set aboslute flow", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_AbsFlow2->setText(QApplication::translate("configurePolMeasure", "ml/min", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_NSteps->setToolTip(QApplication::translate("configurePolMeasure", "Steps of cuvette flushing", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_NSteps->setText(QApplication::translate("configurePolMeasure", "Nr. Steps:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        spinBox_NSteps->setToolTip(QApplication::translate("configurePolMeasure", "Set number of steps", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_2->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_AbsVol->setToolTip(QApplication::translate("configurePolMeasure", "Fill Refill Absolute Volume", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_AbsVol->setText(QApplication::translate("configurePolMeasure", "Absolute Volume: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        spinBox_AbsVol->setToolTip(QApplication::translate("configurePolMeasure", "Set absolute volume", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_AbsVol_2->setText(QApplication::translate("configurePolMeasure", "ml", Q_NULLPTR));
        label_MeasurementTime->setText(QApplication::translate("configurePolMeasure", "Measurement Time:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_Idle->setToolTip(QApplication::translate("configurePolMeasure", "Activating syringe idle to ensure constant temperature 0=normal, 1=idle", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_Idle->setText(QApplication::translate("configurePolMeasure", "Idle Mode:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox->setToolTip(QApplication::translate("configurePolMeasure", "Activating syringe idle to ensure constant temperature 0=normal, 1=idle", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox->setText(QString());
        label_3->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_ShortBreak->setToolTip(QApplication::translate("configurePolMeasure", "Short Break in Seconds", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_ShortBreak->setText(QApplication::translate("configurePolMeasure", "Short Break: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        spinBox_ShortBreak->setToolTip(QApplication::translate("configurePolMeasure", "Set short break time", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_ShortBreak2->setText(QApplication::translate("configurePolMeasure", "sec", Q_NULLPTR));
        label_startDelay->setText(QApplication::translate("configurePolMeasure", "Start Delay:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        doubleSpinBox_startDelay->setToolTip(QApplication::translate("configurePolMeasure", "Add start delay in hours", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_startDelay2->setText(QApplication::translate("configurePolMeasure", "hours", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_LongBreak->setToolTip(QApplication::translate("configurePolMeasure", "Calculation for time required for stable fluid", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_LongBreak->setText(QApplication::translate("configurePolMeasure", "Add. Long Break:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        spinBox_LongBreak->setToolTip(QApplication::translate("configurePolMeasure", "Set long break time", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_longBreak2->setText(QApplication::translate("configurePolMeasure", "sec", Q_NULLPTR));
        label_NRepet->setText(QApplication::translate("configurePolMeasure", "Nr. of Repetitions", Q_NULLPTR));
        label_4->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_BtimeInt->setToolTip(QApplication::translate("configurePolMeasure", "Time Interval between measurements", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BtimeInt->setText(QApplication::translate("configurePolMeasure", "Total Time:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_BtimeInterval->setToolTip(QApplication::translate("configurePolMeasure", "Total measurement time", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_BtimeInterval->setText(QApplication::translate("configurePolMeasure", "5.703", Q_NULLPTR));
        label_BtimeInt2->setText(QApplication::translate("configurePolMeasure", "hours", Q_NULLPTR));
        label_timebetweenM->setText(QApplication::translate("configurePolMeasure", "Intervals:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_timebetweenM->setToolTip(QApplication::translate("configurePolMeasure", "Time between measurements", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_timebetweenM->setText(QApplication::translate("configurePolMeasure", "6.32", Q_NULLPTR));
        label2_timebetweenM->setText(QApplication::translate("configurePolMeasure", "min", Q_NULLPTR));
        label_timeLabel->setText(QApplication::translate("configurePolMeasure", "Starting from now at:  ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        timeEdit_timeLabel->setToolTip(QApplication::translate("configurePolMeasure", "Time starting the measurement...", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_BFileNamePrev->setToolTip(QApplication::translate("configurePolMeasure", "File Name Preview", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BFileNamePrev->setText(QApplication::translate("configurePolMeasure", "File Name Preview:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_BFileNamePrev->setToolTip(QApplication::translate("configurePolMeasure", "File Name Preview", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_BFileNamePrev->setText(QApplication::translate("configurePolMeasure", "500C1_0C2_6ms_7Hz_1", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_cancel->setToolTip(QApplication::translate("configurePolMeasure", "Cancel configuration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_cancel->setText(QApplication::translate("configurePolMeasure", "Cancel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_generate->setToolTip(QApplication::translate("configurePolMeasure", "Generate Configuration File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_generate->setText(QApplication::translate("configurePolMeasure", "Create", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class configurePolMeasure: public Ui_configurePolMeasure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_CONFIGUREMEASUREMENT_H
