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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_configurePolMeasure
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_11;
    ClickableLabel *label_load;
    QSpacerItem *verticalSpacer_10;
    QWidget *LoadWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_filename;
    QLineEdit *lineEdit_path;
    QPushButton *pushButton_select;
    QSpacerItem *verticalSpacer_9;
    ClickableLabel *label_basicConf;
    QSpacerItem *verticalSpacer;
    QWidget *ConfigurationLayout;
    QVBoxLayout *verticalLayout_fileconf;
    QLabel *label_Spectrometer;
    QSpacerItem *verticalSpacer_16;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_BNMeas;
    QLineEdit *lineEdit_BNMeas;
    QSpacerItem *horizontalSpacer_21;
    QLabel *label_BIntTime;
    QLineEdit *lineEdit_BIntTime;
    QLabel *label_BIntTime2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_BFreq;
    QLineEdit *lineEdit_BFreq;
    QLabel *label_BFreq2;
    QSpacerItem *verticalSpacer_19;
    QHBoxLayout *horizontalLayout;
    QLabel *label_BNSpec;
    QLineEdit *lineEdit_BNSpec;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_BNAve;
    QLineEdit *lineEdit_BNAve;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_13;
    QLabel *label_SolConc;
    QSpacerItem *verticalSpacer_17;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox_Glucose;
    QSpacerItem *horizontalSpacer_10;
    QCheckBox *checkBox_Imp1;
    QSpacerItem *horizontalSpacer_13;
    QCheckBox *checkBox_Imp2;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_StockGluc;
    QLineEdit *lineEdit_StockGluc;
    QLabel *label_StockGluc2;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_StockImp1;
    QLineEdit *lineEdit_StockImp1;
    QLabel *label_StockImp1_2;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_StockImp2;
    QLineEdit *lineEdit_StockImp2;
    QLabel *label_StockImp2_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_MinGluc;
    QLineEdit *lineEdit_Mingluc;
    QLabel *label_MinGluc2;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_MinImp1;
    QLineEdit *lineEdit_MinImp1;
    QLabel *label_MinImp1_2;
    QSpacerItem *horizontalSpacer_15;
    QLabel *label_MinImp2;
    QLineEdit *lineEdit_MinImp2;
    QLabel *label_MinImp2_2;
    QSpacerItem *verticalSpacer_18;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_MaxGluc;
    QLineEdit *lineEdit_MaxGluc;
    QLabel *label_MaxGluc2;
    QSpacerItem *horizontalSpacer_19;
    QLabel *label_MaxImp1;
    QLineEdit *lineEdit_MaxImp1;
    QLabel *label_MaxImp1_2;
    QSpacerItem *horizontalSpacer_18;
    QLabel *label_MaxImp2;
    QLineEdit *lineEdit_MaxImp2;
    QLabel *label_MaxImp2_2;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_PumpFlow;
    QSpacerItem *verticalSpacer_20;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_AbsFlow;
    QLineEdit *lineEdit_AbsFlow;
    QLabel *label_AbsFlow2;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_AbsVol;
    QLineEdit *lineEdit_AbsVol;
    QLabel *label_AbsVol_2;
    QSpacerItem *horizontalSpacer_22;
    QLabel *label_NSteps;
    QLineEdit *lineEdit_NSteps;
    QSpacerItem *verticalSpacer_12;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_BtimeInt;
    QLineEdit *lineEdit_BtimeInterval;
    QLabel *label_BtimeInt2;
    QSpacerItem *horizontalSpacer_23;
    QLabel *label_ShortBreak;
    QLineEdit *lineEdit_ShortBreak;
    QLabel *label_ShortBreak2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_LongBreak;
    QLineEdit *lineEdit_LongBreak;
    QLabel *label_longBreak2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_Idle;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_BFileNamePrev;
    QLineEdit *lineEdit_BFileNamePrev;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_generate;
    QSpacerItem *verticalSpacer_8;

    void setupUi(QDialog *configurePolMeasure)
    {
        if (configurePolMeasure->objectName().isEmpty())
            configurePolMeasure->setObjectName(QStringLiteral("configurePolMeasure"));
        configurePolMeasure->resize(786, 797);
        gridLayout = new QGridLayout(configurePolMeasure);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_11 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_11);

        label_load = new ClickableLabel(configurePolMeasure);
        label_load->setObjectName(QStringLiteral("label_load"));
        label_load->setMaximumSize(QSize(16777215, 20));
        QFont font;
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label_load->setFont(font);
        label_load->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(label_load);

        verticalSpacer_10 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_10);

        LoadWidget = new QWidget(configurePolMeasure);
        LoadWidget->setObjectName(QStringLiteral("LoadWidget"));
        horizontalLayout_2 = new QHBoxLayout(LoadWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_filename = new QLabel(LoadWidget);
        label_filename->setObjectName(QStringLiteral("label_filename"));
        label_filename->setMaximumSize(QSize(16777215, 43));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        label_filename->setFont(font1);

        horizontalLayout_2->addWidget(label_filename);

        lineEdit_path = new QLineEdit(LoadWidget);
        lineEdit_path->setObjectName(QStringLiteral("lineEdit_path"));
        lineEdit_path->setEnabled(false);
        lineEdit_path->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_path);

        pushButton_select = new QPushButton(LoadWidget);
        pushButton_select->setObjectName(QStringLiteral("pushButton_select"));
        pushButton_select->setMinimumSize(QSize(150, 30));
        pushButton_select->setAutoDefault(false);

        horizontalLayout_2->addWidget(pushButton_select);


        verticalLayout->addWidget(LoadWidget);

        verticalSpacer_9 = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_9);

        label_basicConf = new ClickableLabel(configurePolMeasure);
        label_basicConf->setObjectName(QStringLiteral("label_basicConf"));
        label_basicConf->setFont(font);
        label_basicConf->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout->addWidget(label_basicConf);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        ConfigurationLayout = new QWidget(configurePolMeasure);
        ConfigurationLayout->setObjectName(QStringLiteral("ConfigurationLayout"));
        verticalLayout_fileconf = new QVBoxLayout(ConfigurationLayout);
        verticalLayout_fileconf->setObjectName(QStringLiteral("verticalLayout_fileconf"));
        label_Spectrometer = new QLabel(ConfigurationLayout);
        label_Spectrometer->setObjectName(QStringLiteral("label_Spectrometer"));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        label_Spectrometer->setFont(font2);

        verticalLayout_fileconf->addWidget(label_Spectrometer);

        verticalSpacer_16 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_16);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(2);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_BNMeas = new QLabel(ConfigurationLayout);
        label_BNMeas->setObjectName(QStringLiteral("label_BNMeas"));
        label_BNMeas->setMinimumSize(QSize(100, 0));
        label_BNMeas->setToolTipDuration(-1);

        horizontalLayout_11->addWidget(label_BNMeas);

        lineEdit_BNMeas = new QLineEdit(ConfigurationLayout);
        lineEdit_BNMeas->setObjectName(QStringLiteral("lineEdit_BNMeas"));
        lineEdit_BNMeas->setMinimumSize(QSize(130, 0));
        lineEdit_BNMeas->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_11->addWidget(lineEdit_BNMeas);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_21);

        label_BIntTime = new QLabel(ConfigurationLayout);
        label_BIntTime->setObjectName(QStringLiteral("label_BIntTime"));
        label_BIntTime->setMinimumSize(QSize(100, 0));

        horizontalLayout_11->addWidget(label_BIntTime);

        lineEdit_BIntTime = new QLineEdit(ConfigurationLayout);
        lineEdit_BIntTime->setObjectName(QStringLiteral("lineEdit_BIntTime"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_BIntTime->sizePolicy().hasHeightForWidth());
        lineEdit_BIntTime->setSizePolicy(sizePolicy);
        lineEdit_BIntTime->setMinimumSize(QSize(100, 0));
        lineEdit_BIntTime->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_11->addWidget(lineEdit_BIntTime);

        label_BIntTime2 = new QLabel(ConfigurationLayout);
        label_BIntTime2->setObjectName(QStringLiteral("label_BIntTime2"));
        label_BIntTime2->setMinimumSize(QSize(30, 0));

        horizontalLayout_11->addWidget(label_BIntTime2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_2);

        label_BFreq = new QLabel(ConfigurationLayout);
        label_BFreq->setObjectName(QStringLiteral("label_BFreq"));
        label_BFreq->setMinimumSize(QSize(100, 0));

        horizontalLayout_11->addWidget(label_BFreq);

        lineEdit_BFreq = new QLineEdit(ConfigurationLayout);
        lineEdit_BFreq->setObjectName(QStringLiteral("lineEdit_BFreq"));
        lineEdit_BFreq->setMinimumSize(QSize(100, 0));
        lineEdit_BFreq->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_11->addWidget(lineEdit_BFreq);

        label_BFreq2 = new QLabel(ConfigurationLayout);
        label_BFreq2->setObjectName(QStringLiteral("label_BFreq2"));
        label_BFreq2->setMinimumSize(QSize(30, 0));

        horizontalLayout_11->addWidget(label_BFreq2);


        verticalLayout_fileconf->addLayout(horizontalLayout_11);

        verticalSpacer_19 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_19);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_BNSpec = new QLabel(ConfigurationLayout);
        label_BNSpec->setObjectName(QStringLiteral("label_BNSpec"));
        label_BNSpec->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(label_BNSpec);

        lineEdit_BNSpec = new QLineEdit(ConfigurationLayout);
        lineEdit_BNSpec->setObjectName(QStringLiteral("lineEdit_BNSpec"));
        lineEdit_BNSpec->setMinimumSize(QSize(130, 0));
        lineEdit_BNSpec->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(lineEdit_BNSpec);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_BNAve = new QLabel(ConfigurationLayout);
        label_BNAve->setObjectName(QStringLiteral("label_BNAve"));
        label_BNAve->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(label_BNAve);

        lineEdit_BNAve = new QLineEdit(ConfigurationLayout);
        lineEdit_BNAve->setObjectName(QStringLiteral("lineEdit_BNAve"));
        lineEdit_BNAve->setMinimumSize(QSize(130, 0));
        lineEdit_BNAve->setMaximumSize(QSize(130, 16777215));

        horizontalLayout->addWidget(lineEdit_BNAve);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_11);

        horizontalSpacer_7 = new QSpacerItem(235, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        verticalLayout_fileconf->addLayout(horizontalLayout);

        verticalSpacer_13 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_13);

        label_SolConc = new QLabel(ConfigurationLayout);
        label_SolConc->setObjectName(QStringLiteral("label_SolConc"));
        label_SolConc->setFont(font2);

        verticalLayout_fileconf->addWidget(label_SolConc);

        verticalSpacer_17 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_17);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        checkBox_Glucose = new QCheckBox(ConfigurationLayout);
        checkBox_Glucose->setObjectName(QStringLiteral("checkBox_Glucose"));
        checkBox_Glucose->setMinimumSize(QSize(230, 0));
        checkBox_Glucose->setMaximumSize(QSize(230, 16777215));
        checkBox_Glucose->setLayoutDirection(Qt::LeftToRight);
        checkBox_Glucose->setAutoFillBackground(false);
        checkBox_Glucose->setChecked(true);
        checkBox_Glucose->setTristate(false);

        horizontalLayout_4->addWidget(checkBox_Glucose);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        checkBox_Imp1 = new QCheckBox(ConfigurationLayout);
        checkBox_Imp1->setObjectName(QStringLiteral("checkBox_Imp1"));
        checkBox_Imp1->setMinimumSize(QSize(230, 0));
        checkBox_Imp1->setMaximumSize(QSize(230, 16777215));
        checkBox_Imp1->setChecked(true);

        horizontalLayout_4->addWidget(checkBox_Imp1);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_13);

        checkBox_Imp2 = new QCheckBox(ConfigurationLayout);
        checkBox_Imp2->setObjectName(QStringLiteral("checkBox_Imp2"));
        checkBox_Imp2->setEnabled(true);
        checkBox_Imp2->setMinimumSize(QSize(230, 0));
        checkBox_Imp2->setMaximumSize(QSize(230, 16777215));

        horizontalLayout_4->addWidget(checkBox_Imp2);


        verticalLayout_fileconf->addLayout(horizontalLayout_4);

        verticalSpacer_7 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(2);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_StockGluc = new QLabel(ConfigurationLayout);
        label_StockGluc->setObjectName(QStringLiteral("label_StockGluc"));
        label_StockGluc->setMinimumSize(QSize(100, 0));

        horizontalLayout_8->addWidget(label_StockGluc);

        lineEdit_StockGluc = new QLineEdit(ConfigurationLayout);
        lineEdit_StockGluc->setObjectName(QStringLiteral("lineEdit_StockGluc"));
        lineEdit_StockGluc->setMinimumSize(QSize(100, 0));
        lineEdit_StockGluc->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_8->addWidget(lineEdit_StockGluc);

        label_StockGluc2 = new QLabel(ConfigurationLayout);
        label_StockGluc2->setObjectName(QStringLiteral("label_StockGluc2"));
        label_StockGluc2->setMinimumSize(QSize(30, 0));

        horizontalLayout_8->addWidget(label_StockGluc2);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_12);

        label_StockImp1 = new QLabel(ConfigurationLayout);
        label_StockImp1->setObjectName(QStringLiteral("label_StockImp1"));
        label_StockImp1->setMinimumSize(QSize(100, 0));

        horizontalLayout_8->addWidget(label_StockImp1);

        lineEdit_StockImp1 = new QLineEdit(ConfigurationLayout);
        lineEdit_StockImp1->setObjectName(QStringLiteral("lineEdit_StockImp1"));
        lineEdit_StockImp1->setMinimumSize(QSize(100, 0));
        lineEdit_StockImp1->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_8->addWidget(lineEdit_StockImp1);

        label_StockImp1_2 = new QLabel(ConfigurationLayout);
        label_StockImp1_2->setObjectName(QStringLiteral("label_StockImp1_2"));
        label_StockImp1_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_8->addWidget(label_StockImp1_2);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_9);

        label_StockImp2 = new QLabel(ConfigurationLayout);
        label_StockImp2->setObjectName(QStringLiteral("label_StockImp2"));
        label_StockImp2->setEnabled(false);
        label_StockImp2->setMinimumSize(QSize(100, 0));

        horizontalLayout_8->addWidget(label_StockImp2);

        lineEdit_StockImp2 = new QLineEdit(ConfigurationLayout);
        lineEdit_StockImp2->setObjectName(QStringLiteral("lineEdit_StockImp2"));
        lineEdit_StockImp2->setEnabled(false);
        lineEdit_StockImp2->setMinimumSize(QSize(100, 0));
        lineEdit_StockImp2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_8->addWidget(lineEdit_StockImp2);

        label_StockImp2_2 = new QLabel(ConfigurationLayout);
        label_StockImp2_2->setObjectName(QStringLiteral("label_StockImp2_2"));
        label_StockImp2_2->setEnabled(false);
        label_StockImp2_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_8->addWidget(label_StockImp2_2);


        verticalLayout_fileconf->addLayout(horizontalLayout_8);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(2);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_MinGluc = new QLabel(ConfigurationLayout);
        label_MinGluc->setObjectName(QStringLiteral("label_MinGluc"));
        label_MinGluc->setMinimumSize(QSize(100, 0));

        horizontalLayout_6->addWidget(label_MinGluc);

        lineEdit_Mingluc = new QLineEdit(ConfigurationLayout);
        lineEdit_Mingluc->setObjectName(QStringLiteral("lineEdit_Mingluc"));
        sizePolicy.setHeightForWidth(lineEdit_Mingluc->sizePolicy().hasHeightForWidth());
        lineEdit_Mingluc->setSizePolicy(sizePolicy);
        lineEdit_Mingluc->setMinimumSize(QSize(100, 0));
        lineEdit_Mingluc->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(lineEdit_Mingluc);

        label_MinGluc2 = new QLabel(ConfigurationLayout);
        label_MinGluc2->setObjectName(QStringLiteral("label_MinGluc2"));
        label_MinGluc2->setMinimumSize(QSize(30, 0));

        horizontalLayout_6->addWidget(label_MinGluc2);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_14);

        label_MinImp1 = new QLabel(ConfigurationLayout);
        label_MinImp1->setObjectName(QStringLiteral("label_MinImp1"));
        label_MinImp1->setMinimumSize(QSize(100, 0));

        horizontalLayout_6->addWidget(label_MinImp1);

        lineEdit_MinImp1 = new QLineEdit(ConfigurationLayout);
        lineEdit_MinImp1->setObjectName(QStringLiteral("lineEdit_MinImp1"));
        lineEdit_MinImp1->setMinimumSize(QSize(100, 0));
        lineEdit_MinImp1->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(lineEdit_MinImp1);

        label_MinImp1_2 = new QLabel(ConfigurationLayout);
        label_MinImp1_2->setObjectName(QStringLiteral("label_MinImp1_2"));
        label_MinImp1_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_6->addWidget(label_MinImp1_2);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_15);

        label_MinImp2 = new QLabel(ConfigurationLayout);
        label_MinImp2->setObjectName(QStringLiteral("label_MinImp2"));
        label_MinImp2->setEnabled(false);
        label_MinImp2->setMinimumSize(QSize(100, 0));

        horizontalLayout_6->addWidget(label_MinImp2);

        lineEdit_MinImp2 = new QLineEdit(ConfigurationLayout);
        lineEdit_MinImp2->setObjectName(QStringLiteral("lineEdit_MinImp2"));
        lineEdit_MinImp2->setEnabled(false);
        lineEdit_MinImp2->setMinimumSize(QSize(100, 0));
        lineEdit_MinImp2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(lineEdit_MinImp2);

        label_MinImp2_2 = new QLabel(ConfigurationLayout);
        label_MinImp2_2->setObjectName(QStringLiteral("label_MinImp2_2"));
        label_MinImp2_2->setEnabled(false);
        label_MinImp2_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_6->addWidget(label_MinImp2_2);


        verticalLayout_fileconf->addLayout(horizontalLayout_6);

        verticalSpacer_18 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_18);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(2);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_MaxGluc = new QLabel(ConfigurationLayout);
        label_MaxGluc->setObjectName(QStringLiteral("label_MaxGluc"));
        label_MaxGluc->setMinimumSize(QSize(100, 0));

        horizontalLayout_12->addWidget(label_MaxGluc);

        lineEdit_MaxGluc = new QLineEdit(ConfigurationLayout);
        lineEdit_MaxGluc->setObjectName(QStringLiteral("lineEdit_MaxGluc"));
        lineEdit_MaxGluc->setMinimumSize(QSize(100, 0));
        lineEdit_MaxGluc->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_12->addWidget(lineEdit_MaxGluc);

        label_MaxGluc2 = new QLabel(ConfigurationLayout);
        label_MaxGluc2->setObjectName(QStringLiteral("label_MaxGluc2"));
        label_MaxGluc2->setMinimumSize(QSize(30, 0));

        horizontalLayout_12->addWidget(label_MaxGluc2);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_19);

        label_MaxImp1 = new QLabel(ConfigurationLayout);
        label_MaxImp1->setObjectName(QStringLiteral("label_MaxImp1"));
        label_MaxImp1->setMinimumSize(QSize(100, 0));

        horizontalLayout_12->addWidget(label_MaxImp1);

        lineEdit_MaxImp1 = new QLineEdit(ConfigurationLayout);
        lineEdit_MaxImp1->setObjectName(QStringLiteral("lineEdit_MaxImp1"));
        lineEdit_MaxImp1->setMinimumSize(QSize(100, 0));
        lineEdit_MaxImp1->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_12->addWidget(lineEdit_MaxImp1);

        label_MaxImp1_2 = new QLabel(ConfigurationLayout);
        label_MaxImp1_2->setObjectName(QStringLiteral("label_MaxImp1_2"));
        label_MaxImp1_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_12->addWidget(label_MaxImp1_2);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_18);

        label_MaxImp2 = new QLabel(ConfigurationLayout);
        label_MaxImp2->setObjectName(QStringLiteral("label_MaxImp2"));
        label_MaxImp2->setEnabled(false);
        label_MaxImp2->setMinimumSize(QSize(100, 0));

        horizontalLayout_12->addWidget(label_MaxImp2);

        lineEdit_MaxImp2 = new QLineEdit(ConfigurationLayout);
        lineEdit_MaxImp2->setObjectName(QStringLiteral("lineEdit_MaxImp2"));
        lineEdit_MaxImp2->setEnabled(false);
        lineEdit_MaxImp2->setMinimumSize(QSize(100, 0));
        lineEdit_MaxImp2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_12->addWidget(lineEdit_MaxImp2);

        label_MaxImp2_2 = new QLabel(ConfigurationLayout);
        label_MaxImp2_2->setObjectName(QStringLiteral("label_MaxImp2_2"));
        label_MaxImp2_2->setEnabled(false);
        label_MaxImp2_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_12->addWidget(label_MaxImp2_2);


        verticalLayout_fileconf->addLayout(horizontalLayout_12);

        verticalSpacer_6 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_6);

        label_PumpFlow = new QLabel(ConfigurationLayout);
        label_PumpFlow->setObjectName(QStringLiteral("label_PumpFlow"));
        label_PumpFlow->setFont(font2);

        verticalLayout_fileconf->addWidget(label_PumpFlow);

        verticalSpacer_20 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_20);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(2);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_AbsFlow = new QLabel(ConfigurationLayout);
        label_AbsFlow->setObjectName(QStringLiteral("label_AbsFlow"));
        label_AbsFlow->setMinimumSize(QSize(100, 0));

        horizontalLayout_7->addWidget(label_AbsFlow);

        lineEdit_AbsFlow = new QLineEdit(ConfigurationLayout);
        lineEdit_AbsFlow->setObjectName(QStringLiteral("lineEdit_AbsFlow"));
        lineEdit_AbsFlow->setMinimumSize(QSize(100, 0));
        lineEdit_AbsFlow->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_7->addWidget(lineEdit_AbsFlow);

        label_AbsFlow2 = new QLabel(ConfigurationLayout);
        label_AbsFlow2->setObjectName(QStringLiteral("label_AbsFlow2"));
        label_AbsFlow2->setMinimumSize(QSize(30, 0));

        horizontalLayout_7->addWidget(label_AbsFlow2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        label_AbsVol = new QLabel(ConfigurationLayout);
        label_AbsVol->setObjectName(QStringLiteral("label_AbsVol"));
        label_AbsVol->setMinimumSize(QSize(100, 0));

        horizontalLayout_7->addWidget(label_AbsVol);

        lineEdit_AbsVol = new QLineEdit(ConfigurationLayout);
        lineEdit_AbsVol->setObjectName(QStringLiteral("lineEdit_AbsVol"));
        lineEdit_AbsVol->setMinimumSize(QSize(100, 0));
        lineEdit_AbsVol->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_7->addWidget(lineEdit_AbsVol);

        label_AbsVol_2 = new QLabel(ConfigurationLayout);
        label_AbsVol_2->setObjectName(QStringLiteral("label_AbsVol_2"));
        label_AbsVol_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_7->addWidget(label_AbsVol_2);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_22);

        label_NSteps = new QLabel(ConfigurationLayout);
        label_NSteps->setObjectName(QStringLiteral("label_NSteps"));
        label_NSteps->setMinimumSize(QSize(100, 0));

        horizontalLayout_7->addWidget(label_NSteps);

        lineEdit_NSteps = new QLineEdit(ConfigurationLayout);
        lineEdit_NSteps->setObjectName(QStringLiteral("lineEdit_NSteps"));
        lineEdit_NSteps->setEnabled(true);
        lineEdit_NSteps->setMinimumSize(QSize(130, 0));
        lineEdit_NSteps->setMaximumSize(QSize(130, 16777215));

        horizontalLayout_7->addWidget(lineEdit_NSteps);


        verticalLayout_fileconf->addLayout(horizontalLayout_7);

        verticalSpacer_12 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(2);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_BtimeInt = new QLabel(ConfigurationLayout);
        label_BtimeInt->setObjectName(QStringLiteral("label_BtimeInt"));
        label_BtimeInt->setMinimumSize(QSize(100, 0));

        horizontalLayout_13->addWidget(label_BtimeInt);

        lineEdit_BtimeInterval = new QLineEdit(ConfigurationLayout);
        lineEdit_BtimeInterval->setObjectName(QStringLiteral("lineEdit_BtimeInterval"));
        lineEdit_BtimeInterval->setMinimumSize(QSize(100, 0));
        lineEdit_BtimeInterval->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_13->addWidget(lineEdit_BtimeInterval);

        label_BtimeInt2 = new QLabel(ConfigurationLayout);
        label_BtimeInt2->setObjectName(QStringLiteral("label_BtimeInt2"));
        label_BtimeInt2->setMinimumSize(QSize(30, 0));

        horizontalLayout_13->addWidget(label_BtimeInt2);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_23);

        label_ShortBreak = new QLabel(ConfigurationLayout);
        label_ShortBreak->setObjectName(QStringLiteral("label_ShortBreak"));
        label_ShortBreak->setMinimumSize(QSize(100, 0));

        horizontalLayout_13->addWidget(label_ShortBreak);

        lineEdit_ShortBreak = new QLineEdit(ConfigurationLayout);
        lineEdit_ShortBreak->setObjectName(QStringLiteral("lineEdit_ShortBreak"));
        lineEdit_ShortBreak->setMinimumSize(QSize(100, 0));
        lineEdit_ShortBreak->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_13->addWidget(lineEdit_ShortBreak);

        label_ShortBreak2 = new QLabel(ConfigurationLayout);
        label_ShortBreak2->setObjectName(QStringLiteral("label_ShortBreak2"));
        label_ShortBreak2->setMinimumSize(QSize(30, 0));

        horizontalLayout_13->addWidget(label_ShortBreak2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_4);

        label_LongBreak = new QLabel(ConfigurationLayout);
        label_LongBreak->setObjectName(QStringLiteral("label_LongBreak"));
        label_LongBreak->setMinimumSize(QSize(100, 0));

        horizontalLayout_13->addWidget(label_LongBreak);

        lineEdit_LongBreak = new QLineEdit(ConfigurationLayout);
        lineEdit_LongBreak->setObjectName(QStringLiteral("lineEdit_LongBreak"));
        lineEdit_LongBreak->setMinimumSize(QSize(100, 0));
        lineEdit_LongBreak->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_13->addWidget(lineEdit_LongBreak);

        label_longBreak2 = new QLabel(ConfigurationLayout);
        label_longBreak2->setObjectName(QStringLiteral("label_longBreak2"));
        label_longBreak2->setMinimumSize(QSize(30, 0));

        horizontalLayout_13->addWidget(label_longBreak2);


        verticalLayout_fileconf->addLayout(horizontalLayout_13);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_Idle = new QLabel(ConfigurationLayout);
        label_Idle->setObjectName(QStringLiteral("label_Idle"));
        label_Idle->setMinimumSize(QSize(100, 0));

        horizontalLayout_5->addWidget(label_Idle);

        checkBox = new QCheckBox(ConfigurationLayout);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setMinimumSize(QSize(130, 0));
        checkBox->setMaximumSize(QSize(130, 16777215));

        horizontalLayout_5->addWidget(checkBox);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);


        verticalLayout_fileconf->addLayout(horizontalLayout_5);

        verticalSpacer_5 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_BFileNamePrev = new QLabel(ConfigurationLayout);
        label_BFileNamePrev->setObjectName(QStringLiteral("label_BFileNamePrev"));

        horizontalLayout_3->addWidget(label_BFileNamePrev);

        lineEdit_BFileNamePrev = new QLineEdit(ConfigurationLayout);
        lineEdit_BFileNamePrev->setObjectName(QStringLiteral("lineEdit_BFileNamePrev"));
        lineEdit_BFileNamePrev->setEnabled(false);

        horizontalLayout_3->addWidget(lineEdit_BFileNamePrev);


        verticalLayout_fileconf->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(ConfigurationLayout);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer = new QSpacerItem(252, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        pushButton_cancel = new QPushButton(configurePolMeasure);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setMinimumSize(QSize(150, 30));
        pushButton_cancel->setAutoDefault(false);

        horizontalLayout_9->addWidget(pushButton_cancel);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        pushButton_generate = new QPushButton(configurePolMeasure);
        pushButton_generate->setObjectName(QStringLiteral("pushButton_generate"));
        pushButton_generate->setEnabled(true);
        pushButton_generate->setMinimumSize(QSize(150, 30));
        pushButton_generate->setAutoDefault(false);

        horizontalLayout_9->addWidget(pushButton_generate);


        verticalLayout->addLayout(horizontalLayout_9);

        verticalSpacer_8 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_8);


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
        label_load->setText(QApplication::translate("configurePolMeasure", "< Load a Spectrometer Configuration File:", Q_NULLPTR));
        label_filename->setText(QApplication::translate("configurePolMeasure", "Filename:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_path->setToolTip(QApplication::translate("configurePolMeasure", "Configuration File URL", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_path->setText(QApplication::translate("configurePolMeasure", "Please select a configuration file", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_select->setToolTip(QApplication::translate("configurePolMeasure", "Load a Configuration File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_select->setText(QApplication::translate("configurePolMeasure", "Load Configuration", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_basicConf->setToolTip(QApplication::translate("configurePolMeasure", "Hide/Show Create Configuration File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_basicConf->setText(QApplication::translate("configurePolMeasure", "< Create Configuration File:", Q_NULLPTR));
        label_Spectrometer->setText(QApplication::translate("configurePolMeasure", "Spectrometer:", Q_NULLPTR));
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
        lineEdit_BNMeas->setToolTip(QApplication::translate("configurePolMeasure", "Insert Number of Concentrations to Measure", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_BNMeas->setText(QApplication::translate("configurePolMeasure", "51", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_BIntTime->setToolTip(QApplication::translate("configurePolMeasure", "What's the Integration Time?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BIntTime->setText(QApplication::translate("configurePolMeasure", "Integration Time: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_BIntTime->setToolTip(QApplication::translate("configurePolMeasure", "Insert Integration Time", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_BIntTime->setText(QApplication::translate("configurePolMeasure", "6", Q_NULLPTR));
        label_BIntTime2->setText(QApplication::translate("configurePolMeasure", "ms", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_BFreq->setToolTip(QApplication::translate("configurePolMeasure", "What's the Modulation Frequency?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BFreq->setText(QApplication::translate("configurePolMeasure", "Frequency: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_BFreq->setToolTip(QApplication::translate("configurePolMeasure", "Insert Modulation Frequency", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_BFreq->setText(QApplication::translate("configurePolMeasure", "4", Q_NULLPTR));
        label_BFreq2->setText(QApplication::translate("configurePolMeasure", "Hz", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_BNSpec->setToolTip(QApplication::translate("configurePolMeasure", "How many spectra?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BNSpec->setText(QApplication::translate("configurePolMeasure", "Nr. Spectra: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_BNSpec->setToolTip(QApplication::translate("configurePolMeasure", "Insert Number of Spectra", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_BNSpec->setText(QApplication::translate("configurePolMeasure", "1000", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_BNAve->setToolTip(QApplication::translate("configurePolMeasure", "How many averages?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BNAve->setText(QApplication::translate("configurePolMeasure", "Nr. Averages: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_BNAve->setToolTip(QApplication::translate("configurePolMeasure", "Insert Number of Averages", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_BNAve->setText(QApplication::translate("configurePolMeasure", "1", Q_NULLPTR));
        label_SolConc->setText(QApplication::translate("configurePolMeasure", "Solutions Concentration:", Q_NULLPTR));
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
        label_StockImp1->setToolTip(QApplication::translate("configurePolMeasure", "Which concentration of impurity 1 is in stock?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_StockImp1->setText(QApplication::translate("configurePolMeasure", "Stock Impurity 1:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_StockImp1->setToolTip(QApplication::translate("configurePolMeasure", "Concentration of Impurity 1 in Stock", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_StockImp1->setText(QApplication::translate("configurePolMeasure", "4", Q_NULLPTR));
        label_StockImp1_2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_StockImp2->setToolTip(QApplication::translate("configurePolMeasure", "Which concentration of impurity 2 is in stock?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_StockImp2->setText(QApplication::translate("configurePolMeasure", "Stock Impurity 2:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_StockImp2->setToolTip(QApplication::translate("configurePolMeasure", "Concentration of Impurity 2 in Stock", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_StockImp2->setText(QApplication::translate("configurePolMeasure", "0", Q_NULLPTR));
        label_StockImp2_2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
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
        label_MinImp1->setToolTip(QApplication::translate("configurePolMeasure", "Minimum Impurity 1 Concentration?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_MinImp1->setText(QApplication::translate("configurePolMeasure", "Min. Impurity 1: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_MinImp1->setToolTip(QApplication::translate("configurePolMeasure", "Minimum Impurity 1 Concentration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_MinImp1->setText(QApplication::translate("configurePolMeasure", "0", Q_NULLPTR));
        label_MinImp1_2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
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
        label_MaxGluc->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Glucose Concentration?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_MaxGluc->setText(QApplication::translate("configurePolMeasure", "Max. Glucose: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_MaxGluc->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Glucose Concentration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_MaxGluc->setText(QApplication::translate("configurePolMeasure", "500", Q_NULLPTR));
        label_MaxGluc2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_MaxImp1->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Impurity 1 Concentration?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_MaxImp1->setText(QApplication::translate("configurePolMeasure", "Max. Impurity 1: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_MaxImp1->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Impurity 1 Concentration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_MaxImp1->setText(QApplication::translate("configurePolMeasure", "2", Q_NULLPTR));
        label_MaxImp1_2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_MaxImp2->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Impurity 2 Concentration?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_MaxImp2->setText(QApplication::translate("configurePolMeasure", "Max. Impurity 2:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_MaxImp2->setToolTip(QApplication::translate("configurePolMeasure", "Maximum Impurity 2 Concentration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_MaxImp2->setText(QApplication::translate("configurePolMeasure", "500", Q_NULLPTR));
        label_MaxImp2_2->setText(QApplication::translate("configurePolMeasure", "mg/dl", Q_NULLPTR));
        label_PumpFlow->setText(QApplication::translate("configurePolMeasure", "Pumps Flow:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_AbsFlow->setToolTip(QApplication::translate("configurePolMeasure", "Absolute Flow for Cuvette Filling", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_AbsFlow->setText(QApplication::translate("configurePolMeasure", "Absolute Flow:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_AbsFlow->setToolTip(QApplication::translate("configurePolMeasure", "Absolute Flow for Cuvette Filling", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_AbsFlow->setText(QApplication::translate("configurePolMeasure", "18.75", Q_NULLPTR));
        label_AbsFlow2->setText(QApplication::translate("configurePolMeasure", "ml/min", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_AbsVol->setToolTip(QApplication::translate("configurePolMeasure", "Fill Refill Absolute Volume", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_AbsVol->setText(QApplication::translate("configurePolMeasure", "Absolute Volume: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_AbsVol->setToolTip(QApplication::translate("configurePolMeasure", "Fill Refill Absolut Volume", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_AbsVol->setText(QApplication::translate("configurePolMeasure", "25", Q_NULLPTR));
        label_AbsVol_2->setText(QApplication::translate("configurePolMeasure", "ml", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_NSteps->setToolTip(QApplication::translate("configurePolMeasure", "Steps of cuvette flushing", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_NSteps->setText(QApplication::translate("configurePolMeasure", "Nr. Steps:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_NSteps->setToolTip(QApplication::translate("configurePolMeasure", "Steps of cuvette flushing", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_NSteps->setText(QApplication::translate("configurePolMeasure", "5", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_BtimeInt->setToolTip(QApplication::translate("configurePolMeasure", "Time Interval between measurements", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BtimeInt->setText(QApplication::translate("configurePolMeasure", "Time Intervals:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_BtimeInterval->setToolTip(QApplication::translate("configurePolMeasure", "Time Interval between measurements", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_BtimeInterval->setText(QApplication::translate("configurePolMeasure", "120", Q_NULLPTR));
        label_BtimeInt2->setText(QApplication::translate("configurePolMeasure", "sec", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_ShortBreak->setToolTip(QApplication::translate("configurePolMeasure", "Short Break in Seconds", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_ShortBreak->setText(QApplication::translate("configurePolMeasure", "Short Break: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_ShortBreak->setToolTip(QApplication::translate("configurePolMeasure", "Short Break in Seconds", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_ShortBreak->setText(QApplication::translate("configurePolMeasure", "1", Q_NULLPTR));
        label_ShortBreak2->setText(QApplication::translate("configurePolMeasure", "sec", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_LongBreak->setToolTip(QApplication::translate("configurePolMeasure", "Calculation for time required for stable fluid", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_LongBreak->setText(QApplication::translate("configurePolMeasure", "Add. Long Break:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_LongBreak->setToolTip(QApplication::translate("configurePolMeasure", "Calculation for time required for stable fluid", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_LongBreak->setText(QApplication::translate("configurePolMeasure", "30", Q_NULLPTR));
        label_longBreak2->setText(QApplication::translate("configurePolMeasure", "sec", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_Idle->setToolTip(QApplication::translate("configurePolMeasure", "Activating syringe idle to ensure constant temperature 0=normal, 1=idle", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_Idle->setText(QApplication::translate("configurePolMeasure", "Idle Mode:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox->setToolTip(QApplication::translate("configurePolMeasure", "Activating syringe idle to ensure constant temperature 0=normal, 1=idle", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_BFileNamePrev->setToolTip(QApplication::translate("configurePolMeasure", "File Name Preview", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_BFileNamePrev->setText(QApplication::translate("configurePolMeasure", "File Name Preview:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_BFileNamePrev->setToolTip(QApplication::translate("configurePolMeasure", "File Name Preview", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_BFileNamePrev->setText(QApplication::translate("configurePolMeasure", "0C1_0C2_6ms_7Hz_1", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("configurePolMeasure", "Cancel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_generate->setToolTip(QApplication::translate("configurePolMeasure", "Generate Configuration File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_generate->setText(QApplication::translate("configurePolMeasure", "Generate Configuration", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class configurePolMeasure: public Ui_configurePolMeasure {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_CONFIGUREMEASUREMENT_H
