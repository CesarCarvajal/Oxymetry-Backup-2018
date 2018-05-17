/********************************************************************************
** Form generated from reading UI file 'pol_panel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POL_PANEL_H
#define UI_POL_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <plot.h>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_PanelPolarimeter
{
public:
    QGridLayout *gridLayout;
    QFrame *line_5;
    QHBoxLayout *horizonalLayout_2;
    QVBoxLayout *verticalLayout_8;
    ClickableLabel *label_hideConf;
    QLabel *label_Set_Spec_Pol;
    QSpacerItem *verticalSpacer_2;
    QListWidget *list_devices_Pol;
    QSpacerItem *verticalSpacer;
    QFrame *line_c1;
    QHBoxLayout *horizontalLayout_2;
    ClickableLabel *FFT_label_Pol;
    ClickableLabel *waveToPlotFFT;
    QLabel *label_n;
    QSpacerItem *HSpaceX;
    QSpacerItem *verticalSpacer_6;
    Plot *qwtPlot_Pol_FFT;
    QFrame *line_c2;
    QSpacerItem *verticalSpacerX;
    ClickableLabel *label_Measurements_Pol;
    QSpacerItem *verticalSpacer_3;
    QTableWidget *Table_Measurements_Pol;
    QSpacerItem *verticalSpacer_16;
    ClickableLabel *label_Save_Pol;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_17;
    QCheckBox *checkBox_AutoSave_Pol_Raw;
    QCheckBox *checkBox_AutoSave_Pol;
    QSpacerItem *verticalSpacer_10;
    QFrame *line_m;
    QLabel *label_5_Pol_settings;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *button_Pol_ConfigureMeasurement;
    QPushButton *button_calibrate;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *button_Start_Meas_Pol;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_7;
    QFrame *line_6;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *Tabs_Plots;
    QWidget *liveData;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_10;
    ClickableLabel *label_raw;
    Plot *qwtPlot_Pol;
    QSpacerItem *horizontalSpacer_12;
    QFrame *line_9;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_11;
    ClickableLabel *label_compensation;
    Plot *qwtPlot_Pol_Compensation;
    QSpacerItem *horizontalSpacer_18;
    QFrame *line;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_19;
    QVBoxLayout *verticalLayout_13;
    ClickableLabel *label_fftprofile;
    Plot *qwtPlot_Pol_w_2w;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line_8;
    QSpacerItem *horizontalSpacer_13;
    QVBoxLayout *verticalLayout_14;
    ClickableLabel *label_average;
    Plot *qwtPlot_Pol_Average;
    QSpacerItem *horizontalSpacer_20;
    QWidget *MeasResults;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_14;
    QVBoxLayout *verticalLayout_5;
    ClickableLabel *label_prediction;
    Plot *qwtPlot_Pol_Prediction;
    QFrame *line_comp;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *button_LoadData;
    QPushButton *Button_Save_Graphs_Pol;
    QSpacerItem *horizontalSpacer_9;
    QFrame *line_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QProgressBar *currentProgressBar_Pol;
    QLabel *info;
    QSpacerItem *horizontalSpacer_Y;
    QLabel *label_totalM;
    QProgressBar *TotalProgressBar_Pol;
    QSpacerItem *horizontalSpacer;
    QLabel *label_remaining;
    QLabel *label_RemainingTime;
    QSpacerItem *horizontalSpacer_8;
    ClickableLabel *label_clearAll;
    QPushButton *help;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *PanelPolarimeter)
    {
        if (PanelPolarimeter->objectName().isEmpty())
            PanelPolarimeter->setObjectName(QStringLiteral("PanelPolarimeter"));
        PanelPolarimeter->resize(1210, 862);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PanelPolarimeter->sizePolicy().hasHeightForWidth());
        PanelPolarimeter->setSizePolicy(sizePolicy);
        PanelPolarimeter->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(PanelPolarimeter);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        line_5 = new QFrame(PanelPolarimeter);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_5, 0, 1, 1, 1);

        horizonalLayout_2 = new QHBoxLayout();
        horizonalLayout_2->setObjectName(QStringLiteral("horizonalLayout_2"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setSizeConstraint(QLayout::SetMinimumSize);
        label_hideConf = new ClickableLabel(PanelPolarimeter);
        label_hideConf->setObjectName(QStringLiteral("label_hideConf"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_hideConf->sizePolicy().hasHeightForWidth());
        label_hideConf->setSizePolicy(sizePolicy1);
        label_hideConf->setMinimumSize(QSize(290, 7));
        label_hideConf->setMaximumSize(QSize(290, 7));
        QFont font;
        font.setPointSize(6);
        font.setUnderline(true);
        label_hideConf->setFont(font);
        label_hideConf->setCursor(QCursor(Qt::PointingHandCursor));
        label_hideConf->setAcceptDrops(false);
        label_hideConf->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_8->addWidget(label_hideConf);

        label_Set_Spec_Pol = new QLabel(PanelPolarimeter);
        label_Set_Spec_Pol->setObjectName(QStringLiteral("label_Set_Spec_Pol"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_Set_Spec_Pol->sizePolicy().hasHeightForWidth());
        label_Set_Spec_Pol->setSizePolicy(sizePolicy2);
        label_Set_Spec_Pol->setMinimumSize(QSize(0, 0));
        label_Set_Spec_Pol->setMaximumSize(QSize(16777215, 15));
        QFont font1;
        font1.setBold(true);
        font1.setUnderline(true);
        font1.setWeight(75);
        label_Set_Spec_Pol->setFont(font1);

        verticalLayout_8->addWidget(label_Set_Spec_Pol);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_2);

        list_devices_Pol = new QListWidget(PanelPolarimeter);
        list_devices_Pol->setObjectName(QStringLiteral("list_devices_Pol"));
        sizePolicy2.setHeightForWidth(list_devices_Pol->sizePolicy().hasHeightForWidth());
        list_devices_Pol->setSizePolicy(sizePolicy2);
        list_devices_Pol->setMinimumSize(QSize(290, 0));
        list_devices_Pol->setMaximumSize(QSize(290, 189));
        list_devices_Pol->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        list_devices_Pol->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        list_devices_Pol->setAutoScroll(true);
        list_devices_Pol->setAutoScrollMargin(18);
        list_devices_Pol->setProperty("isWrapping", QVariant(false));
        list_devices_Pol->setResizeMode(QListView::Adjust);

        verticalLayout_8->addWidget(list_devices_Pol);

        verticalSpacer = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer);

        line_c1 = new QFrame(PanelPolarimeter);
        line_c1->setObjectName(QStringLiteral("line_c1"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(line_c1->sizePolicy().hasHeightForWidth());
        line_c1->setSizePolicy(sizePolicy3);
        line_c1->setFrameShape(QFrame::HLine);
        line_c1->setFrameShadow(QFrame::Sunken);

        verticalLayout_8->addWidget(line_c1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        FFT_label_Pol = new ClickableLabel(PanelPolarimeter);
        FFT_label_Pol->setObjectName(QStringLiteral("FFT_label_Pol"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(FFT_label_Pol->sizePolicy().hasHeightForWidth());
        FFT_label_Pol->setSizePolicy(sizePolicy4);
        FFT_label_Pol->setMinimumSize(QSize(130, 0));
        FFT_label_Pol->setMaximumSize(QSize(95, 100));
        QFont font2;
        font2.setPointSize(8);
        font2.setBold(true);
        font2.setUnderline(true);
        font2.setWeight(75);
        FFT_label_Pol->setFont(font2);
        FFT_label_Pol->setCursor(QCursor(Qt::PointingHandCursor));
        FFT_label_Pol->setLayoutDirection(Qt::LeftToRight);
        FFT_label_Pol->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(FFT_label_Pol);

        waveToPlotFFT = new ClickableLabel(PanelPolarimeter);
        waveToPlotFFT->setObjectName(QStringLiteral("waveToPlotFFT"));
        sizePolicy4.setHeightForWidth(waveToPlotFFT->sizePolicy().hasHeightForWidth());
        waveToPlotFFT->setSizePolicy(sizePolicy4);
        waveToPlotFFT->setMinimumSize(QSize(50, 0));
        waveToPlotFFT->setMaximumSize(QSize(50, 100));
        QFont font3;
        font3.setPointSize(10);
        font3.setUnderline(true);
        waveToPlotFFT->setFont(font3);
        waveToPlotFFT->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(waveToPlotFFT);

        label_n = new QLabel(PanelPolarimeter);
        label_n->setObjectName(QStringLiteral("label_n"));
        sizePolicy1.setHeightForWidth(label_n->sizePolicy().hasHeightForWidth());
        label_n->setSizePolicy(sizePolicy1);
        label_n->setMinimumSize(QSize(20, 0));
        label_n->setMaximumSize(QSize(25, 16777215));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setWeight(75);
        label_n->setFont(font4);

        horizontalLayout_2->addWidget(label_n);

        HSpaceX = new QSpacerItem(80, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(HSpaceX);


        verticalLayout_8->addLayout(horizontalLayout_2);

        verticalSpacer_6 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_6);

        qwtPlot_Pol_FFT = new Plot(PanelPolarimeter);
        qwtPlot_Pol_FFT->setObjectName(QStringLiteral("qwtPlot_Pol_FFT"));
        sizePolicy1.setHeightForWidth(qwtPlot_Pol_FFT->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol_FFT->setSizePolicy(sizePolicy1);
        qwtPlot_Pol_FFT->setMinimumSize(QSize(280, 130));
        qwtPlot_Pol_FFT->setMaximumSize(QSize(280, 130));
        qwtPlot_Pol_FFT->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_FFT->setFrameShadow(QFrame::Raised);

        verticalLayout_8->addWidget(qwtPlot_Pol_FFT);

        line_c2 = new QFrame(PanelPolarimeter);
        line_c2->setObjectName(QStringLiteral("line_c2"));
        sizePolicy3.setHeightForWidth(line_c2->sizePolicy().hasHeightForWidth());
        line_c2->setSizePolicy(sizePolicy3);
        line_c2->setFrameShape(QFrame::HLine);
        line_c2->setFrameShadow(QFrame::Sunken);

        verticalLayout_8->addWidget(line_c2);

        verticalSpacerX = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacerX);

        label_Measurements_Pol = new ClickableLabel(PanelPolarimeter);
        label_Measurements_Pol->setObjectName(QStringLiteral("label_Measurements_Pol"));
        sizePolicy.setHeightForWidth(label_Measurements_Pol->sizePolicy().hasHeightForWidth());
        label_Measurements_Pol->setSizePolicy(sizePolicy);
        label_Measurements_Pol->setMinimumSize(QSize(0, 0));
        label_Measurements_Pol->setMaximumSize(QSize(16777215, 15));
        label_Measurements_Pol->setFont(font1);
        label_Measurements_Pol->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_8->addWidget(label_Measurements_Pol);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_3);

        Table_Measurements_Pol = new QTableWidget(PanelPolarimeter);
        if (Table_Measurements_Pol->columnCount() < 2)
            Table_Measurements_Pol->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        Table_Measurements_Pol->setObjectName(QStringLiteral("Table_Measurements_Pol"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(Table_Measurements_Pol->sizePolicy().hasHeightForWidth());
        Table_Measurements_Pol->setSizePolicy(sizePolicy5);
        Table_Measurements_Pol->setMinimumSize(QSize(0, 50));
        Table_Measurements_Pol->setMaximumSize(QSize(290, 16777215));
        Table_Measurements_Pol->setLineWidth(1);
        Table_Measurements_Pol->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        Table_Measurements_Pol->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        Table_Measurements_Pol->setAutoScroll(true);
        Table_Measurements_Pol->setAutoScrollMargin(10);
        Table_Measurements_Pol->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Table_Measurements_Pol->setSelectionMode(QAbstractItemView::NoSelection);
        Table_Measurements_Pol->setSelectionBehavior(QAbstractItemView::SelectItems);
        Table_Measurements_Pol->setTextElideMode(Qt::ElideRight);
        Table_Measurements_Pol->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        Table_Measurements_Pol->setShowGrid(true);
        Table_Measurements_Pol->setRowCount(0);
        Table_Measurements_Pol->setColumnCount(2);
        Table_Measurements_Pol->horizontalHeader()->setCascadingSectionResizes(false);
        Table_Measurements_Pol->horizontalHeader()->setDefaultSectionSize(81);
        Table_Measurements_Pol->horizontalHeader()->setMinimumSectionSize(31);
        Table_Measurements_Pol->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        Table_Measurements_Pol->horizontalHeader()->setStretchLastSection(true);
        Table_Measurements_Pol->verticalHeader()->setCascadingSectionResizes(false);
        Table_Measurements_Pol->verticalHeader()->setDefaultSectionSize(30);
        Table_Measurements_Pol->verticalHeader()->setHighlightSections(true);
        Table_Measurements_Pol->verticalHeader()->setMinimumSectionSize(39);
        Table_Measurements_Pol->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        Table_Measurements_Pol->verticalHeader()->setStretchLastSection(false);

        verticalLayout_8->addWidget(Table_Measurements_Pol);

        verticalSpacer_16 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_16);

        label_Save_Pol = new ClickableLabel(PanelPolarimeter);
        label_Save_Pol->setObjectName(QStringLiteral("label_Save_Pol"));
        label_Save_Pol->setMaximumSize(QSize(16777215, 15));
        QFont font5;
        font5.setBold(true);
        font5.setUnderline(true);
        font5.setWeight(75);
        font5.setKerning(false);
        label_Save_Pol->setFont(font5);
        label_Save_Pol->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_8->addWidget(label_Save_Pol);

        verticalSpacer_5 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalSpacer_17 = new QSpacerItem(10, 15, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_17);

        checkBox_AutoSave_Pol_Raw = new QCheckBox(PanelPolarimeter);
        checkBox_AutoSave_Pol_Raw->setObjectName(QStringLiteral("checkBox_AutoSave_Pol_Raw"));
        checkBox_AutoSave_Pol_Raw->setEnabled(true);
        checkBox_AutoSave_Pol_Raw->setMinimumSize(QSize(110, 28));
        checkBox_AutoSave_Pol_Raw->setMaximumSize(QSize(110, 28));
        checkBox_AutoSave_Pol_Raw->setChecked(false);

        horizontalLayout->addWidget(checkBox_AutoSave_Pol_Raw);

        checkBox_AutoSave_Pol = new QCheckBox(PanelPolarimeter);
        checkBox_AutoSave_Pol->setObjectName(QStringLiteral("checkBox_AutoSave_Pol"));
        checkBox_AutoSave_Pol->setMinimumSize(QSize(110, 28));
        checkBox_AutoSave_Pol->setMaximumSize(QSize(110, 28));
        checkBox_AutoSave_Pol->setIconSize(QSize(16, 16));
        checkBox_AutoSave_Pol->setChecked(true);

        horizontalLayout->addWidget(checkBox_AutoSave_Pol);


        verticalLayout_8->addLayout(horizontalLayout);

        verticalSpacer_10 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_10);

        line_m = new QFrame(PanelPolarimeter);
        line_m->setObjectName(QStringLiteral("line_m"));
        line_m->setFrameShape(QFrame::HLine);
        line_m->setFrameShadow(QFrame::Sunken);

        verticalLayout_8->addWidget(line_m);

        label_5_Pol_settings = new QLabel(PanelPolarimeter);
        label_5_Pol_settings->setObjectName(QStringLiteral("label_5_Pol_settings"));
        sizePolicy1.setHeightForWidth(label_5_Pol_settings->sizePolicy().hasHeightForWidth());
        label_5_Pol_settings->setSizePolicy(sizePolicy1);
        label_5_Pol_settings->setMinimumSize(QSize(0, 0));
        label_5_Pol_settings->setMaximumSize(QSize(16777215, 15));
        label_5_Pol_settings->setFont(font1);

        verticalLayout_8->addWidget(label_5_Pol_settings);

        verticalSpacer_4 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setSizeConstraint(QLayout::SetMinimumSize);
        button_Pol_ConfigureMeasurement = new QPushButton(PanelPolarimeter);
        button_Pol_ConfigureMeasurement->setObjectName(QStringLiteral("button_Pol_ConfigureMeasurement"));
        sizePolicy1.setHeightForWidth(button_Pol_ConfigureMeasurement->sizePolicy().hasHeightForWidth());
        button_Pol_ConfigureMeasurement->setSizePolicy(sizePolicy1);
        button_Pol_ConfigureMeasurement->setMinimumSize(QSize(120, 30));
        button_Pol_ConfigureMeasurement->setMaximumSize(QSize(120, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/polarimeter/Configure.ico"), QSize(), QIcon::Normal, QIcon::Off);
        button_Pol_ConfigureMeasurement->setIcon(icon);
        button_Pol_ConfigureMeasurement->setIconSize(QSize(20, 20));

        horizontalLayout_9->addWidget(button_Pol_ConfigureMeasurement);

        button_calibrate = new QPushButton(PanelPolarimeter);
        button_calibrate->setObjectName(QStringLiteral("button_calibrate"));
        sizePolicy1.setHeightForWidth(button_calibrate->sizePolicy().hasHeightForWidth());
        button_calibrate->setSizePolicy(sizePolicy1);
        button_calibrate->setMinimumSize(QSize(120, 30));
        button_calibrate->setMaximumSize(QSize(120, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/polarimeter/Calibrate.ico"), QSize(), QIcon::Normal, QIcon::Off);
        button_calibrate->setIcon(icon1);
        button_calibrate->setIconSize(QSize(20, 20));

        horizontalLayout_9->addWidget(button_calibrate);


        verticalLayout_8->addLayout(horizontalLayout_9);

        verticalSpacer_8 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_15 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_15);

        button_Start_Meas_Pol = new QPushButton(PanelPolarimeter);
        button_Start_Meas_Pol->setObjectName(QStringLiteral("button_Start_Meas_Pol"));
        sizePolicy1.setHeightForWidth(button_Start_Meas_Pol->sizePolicy().hasHeightForWidth());
        button_Start_Meas_Pol->setSizePolicy(sizePolicy1);
        button_Start_Meas_Pol->setMinimumSize(QSize(260, 55));
        button_Start_Meas_Pol->setMaximumSize(QSize(120, 55));
        QFont font6;
        font6.setBold(true);
        font6.setWeight(75);
        button_Start_Meas_Pol->setFont(font6);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/polarimeter/Run.ico"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QStringLiteral(":/Run.ico"), QSize(), QIcon::Normal, QIcon::On);
        icon2.addFile(QStringLiteral(":/Run.ico"), QSize(), QIcon::Active, QIcon::Off);
        icon2.addFile(QStringLiteral(":/Run.ico"), QSize(), QIcon::Active, QIcon::On);
        button_Start_Meas_Pol->setIcon(icon2);
        button_Start_Meas_Pol->setIconSize(QSize(23, 23));

        horizontalLayout_6->addWidget(button_Start_Meas_Pol);

        horizontalSpacer_11 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_11);


        verticalLayout_8->addLayout(horizontalLayout_6);

        verticalSpacer_7 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_7);


        horizonalLayout_2->addLayout(verticalLayout_8);

        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizonalLayout_2->addItem(horizontalSpacer_2);

        line_2 = new QFrame(PanelPolarimeter);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizonalLayout_2->addWidget(line_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        line_6 = new QFrame(PanelPolarimeter);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line_6);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        Tabs_Plots = new QTabWidget(PanelPolarimeter);
        Tabs_Plots->setObjectName(QStringLiteral("Tabs_Plots"));
        Tabs_Plots->setEnabled(true);
        Tabs_Plots->setTabPosition(QTabWidget::North);
        Tabs_Plots->setTabShape(QTabWidget::Rounded);
        Tabs_Plots->setIconSize(QSize(16, 16));
        Tabs_Plots->setElideMode(Qt::ElideNone);
        Tabs_Plots->setUsesScrollButtons(true);
        Tabs_Plots->setDocumentMode(false);
        Tabs_Plots->setTabsClosable(false);
        Tabs_Plots->setMovable(false);
        Tabs_Plots->setTabBarAutoHide(false);
        liveData = new QWidget();
        liveData->setObjectName(QStringLiteral("liveData"));
        verticalLayout_3 = new QVBoxLayout(liveData);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalSpacer_10 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_10);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_raw = new ClickableLabel(liveData);
        label_raw->setObjectName(QStringLiteral("label_raw"));
        sizePolicy1.setHeightForWidth(label_raw->sizePolicy().hasHeightForWidth());
        label_raw->setSizePolicy(sizePolicy1);
        label_raw->setMinimumSize(QSize(0, 14));
        label_raw->setMaximumSize(QSize(16777213, 14));
        QFont font7;
        font7.setPointSize(9);
        font7.setBold(true);
        font7.setUnderline(true);
        font7.setWeight(75);
        label_raw->setFont(font7);
        label_raw->setCursor(QCursor(Qt::PointingHandCursor));
        label_raw->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label_raw);

        qwtPlot_Pol = new Plot(liveData);
        qwtPlot_Pol->setObjectName(QStringLiteral("qwtPlot_Pol"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(qwtPlot_Pol->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol->setSizePolicy(sizePolicy6);
        qwtPlot_Pol->setMinimumSize(QSize(0, 0));
        qwtPlot_Pol->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol->setFrameShadow(QFrame::Raised);

        verticalLayout_10->addWidget(qwtPlot_Pol);


        horizontalLayout_13->addLayout(verticalLayout_10);

        horizontalSpacer_12 = new QSpacerItem(2, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);

        line_9 = new QFrame(liveData);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setFrameShape(QFrame::VLine);
        line_9->setFrameShadow(QFrame::Sunken);

        horizontalLayout_13->addWidget(line_9);

        horizontalSpacer_6 = new QSpacerItem(2, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_6);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_compensation = new ClickableLabel(liveData);
        label_compensation->setObjectName(QStringLiteral("label_compensation"));
        label_compensation->setFont(font7);
        label_compensation->setCursor(QCursor(Qt::PointingHandCursor));
        label_compensation->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_compensation);

        qwtPlot_Pol_Compensation = new Plot(liveData);
        qwtPlot_Pol_Compensation->setObjectName(QStringLiteral("qwtPlot_Pol_Compensation"));
        sizePolicy6.setHeightForWidth(qwtPlot_Pol_Compensation->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol_Compensation->setSizePolicy(sizePolicy6);
        qwtPlot_Pol_Compensation->setMinimumSize(QSize(0, 0));
        qwtPlot_Pol_Compensation->setMaximumSize(QSize(16777215, 16777215));
        qwtPlot_Pol_Compensation->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_Compensation->setFrameShadow(QFrame::Raised);

        verticalLayout_11->addWidget(qwtPlot_Pol_Compensation);


        horizontalLayout_13->addLayout(verticalLayout_11);

        horizontalSpacer_18 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_18);


        verticalLayout_3->addLayout(horizontalLayout_13);

        line = new QFrame(liveData);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_19 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_19);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        label_fftprofile = new ClickableLabel(liveData);
        label_fftprofile->setObjectName(QStringLiteral("label_fftprofile"));
        sizePolicy.setHeightForWidth(label_fftprofile->sizePolicy().hasHeightForWidth());
        label_fftprofile->setSizePolicy(sizePolicy);
        label_fftprofile->setFont(font7);
        label_fftprofile->setCursor(QCursor(Qt::PointingHandCursor));
        label_fftprofile->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_fftprofile);

        qwtPlot_Pol_w_2w = new Plot(liveData);
        qwtPlot_Pol_w_2w->setObjectName(QStringLiteral("qwtPlot_Pol_w_2w"));
        sizePolicy6.setHeightForWidth(qwtPlot_Pol_w_2w->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol_w_2w->setSizePolicy(sizePolicy6);
        qwtPlot_Pol_w_2w->setMinimumSize(QSize(0, 0));
        qwtPlot_Pol_w_2w->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_w_2w->setFrameShadow(QFrame::Raised);

        verticalLayout_13->addWidget(qwtPlot_Pol_w_2w);


        horizontalLayout_10->addLayout(verticalLayout_13);

        horizontalSpacer_3 = new QSpacerItem(2, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);

        line_8 = new QFrame(liveData);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        horizontalLayout_10->addWidget(line_8);

        horizontalSpacer_13 = new QSpacerItem(2, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_13);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        label_average = new ClickableLabel(liveData);
        label_average->setObjectName(QStringLiteral("label_average"));
        sizePolicy.setHeightForWidth(label_average->sizePolicy().hasHeightForWidth());
        label_average->setSizePolicy(sizePolicy);
        label_average->setFont(font7);
        label_average->setCursor(QCursor(Qt::PointingHandCursor));
        label_average->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(label_average);

        qwtPlot_Pol_Average = new Plot(liveData);
        qwtPlot_Pol_Average->setObjectName(QStringLiteral("qwtPlot_Pol_Average"));
        sizePolicy6.setHeightForWidth(qwtPlot_Pol_Average->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol_Average->setSizePolicy(sizePolicy6);
        qwtPlot_Pol_Average->setMinimumSize(QSize(0, 0));
        qwtPlot_Pol_Average->setMaximumSize(QSize(16777215, 16777215));
        qwtPlot_Pol_Average->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_Average->setFrameShadow(QFrame::Raised);

        verticalLayout_14->addWidget(qwtPlot_Pol_Average);


        horizontalLayout_10->addLayout(verticalLayout_14);

        horizontalSpacer_20 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_20);


        verticalLayout_3->addLayout(horizontalLayout_10);

        Tabs_Plots->addTab(liveData, QString());
        MeasResults = new QWidget();
        MeasResults->setObjectName(QStringLiteral("MeasResults"));
        verticalLayout_4 = new QVBoxLayout(MeasResults);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_14 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_14);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_prediction = new ClickableLabel(MeasResults);
        label_prediction->setObjectName(QStringLiteral("label_prediction"));
        label_prediction->setFont(font7);
        label_prediction->setCursor(QCursor(Qt::PointingHandCursor));
        label_prediction->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_prediction);

        qwtPlot_Pol_Prediction = new Plot(MeasResults);
        qwtPlot_Pol_Prediction->setObjectName(QStringLiteral("qwtPlot_Pol_Prediction"));
        sizePolicy6.setHeightForWidth(qwtPlot_Pol_Prediction->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol_Prediction->setSizePolicy(sizePolicy6);
        qwtPlot_Pol_Prediction->setMinimumSize(QSize(0, 0));
        qwtPlot_Pol_Prediction->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_Prediction->setFrameShadow(QFrame::Raised);

        verticalLayout_5->addWidget(qwtPlot_Pol_Prediction);


        horizontalLayout_3->addLayout(verticalLayout_5);

        line_comp = new QFrame(MeasResults);
        line_comp->setObjectName(QStringLiteral("line_comp"));
        line_comp->setFrameShape(QFrame::VLine);
        line_comp->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_comp);

        horizontalSpacer_7 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout_4->addLayout(horizontalLayout_3);

        Tabs_Plots->addTab(MeasResults, QString());

        verticalLayout_2->addWidget(Tabs_Plots);


        verticalLayout_7->addLayout(verticalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(450, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        button_LoadData = new QPushButton(PanelPolarimeter);
        button_LoadData->setObjectName(QStringLiteral("button_LoadData"));
        button_LoadData->setMinimumSize(QSize(120, 30));
        button_LoadData->setMaximumSize(QSize(120, 30));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/polarimeter/Load.ico"), QSize(), QIcon::Normal, QIcon::Off);
        button_LoadData->setIcon(icon3);
        button_LoadData->setIconSize(QSize(20, 20));

        horizontalLayout_5->addWidget(button_LoadData);

        Button_Save_Graphs_Pol = new QPushButton(PanelPolarimeter);
        Button_Save_Graphs_Pol->setObjectName(QStringLiteral("Button_Save_Graphs_Pol"));
        Button_Save_Graphs_Pol->setMinimumSize(QSize(120, 30));
        Button_Save_Graphs_Pol->setMaximumSize(QSize(100, 30));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/polarimeter/PDF.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Button_Save_Graphs_Pol->setIcon(icon4);
        Button_Save_Graphs_Pol->setIconSize(QSize(20, 20));

        horizontalLayout_5->addWidget(Button_Save_Graphs_Pol);

        horizontalSpacer_9 = new QSpacerItem(10, 15, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_9);


        verticalLayout_7->addLayout(horizontalLayout_5);

        line_4 = new QFrame(PanelPolarimeter);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        currentProgressBar_Pol = new QProgressBar(PanelPolarimeter);
        currentProgressBar_Pol->setObjectName(QStringLiteral("currentProgressBar_Pol"));
        sizePolicy4.setHeightForWidth(currentProgressBar_Pol->sizePolicy().hasHeightForWidth());
        currentProgressBar_Pol->setSizePolicy(sizePolicy4);
        currentProgressBar_Pol->setMaximumSize(QSize(50, 12));
        currentProgressBar_Pol->setAutoFillBackground(false);
        currentProgressBar_Pol->setValue(0);
        currentProgressBar_Pol->setTextVisible(false);
        currentProgressBar_Pol->setOrientation(Qt::Horizontal);
        currentProgressBar_Pol->setInvertedAppearance(false);

        horizontalLayout_4->addWidget(currentProgressBar_Pol);

        info = new QLabel(PanelPolarimeter);
        info->setObjectName(QStringLiteral("info"));
        sizePolicy4.setHeightForWidth(info->sizePolicy().hasHeightForWidth());
        info->setSizePolicy(sizePolicy4);
        info->setMinimumSize(QSize(160, 0));
        info->setMaximumSize(QSize(250, 12));
        QFont font8;
        font8.setPointSize(7);
        info->setFont(font8);

        horizontalLayout_4->addWidget(info);

        horizontalSpacer_Y = new QSpacerItem(40, 12, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_Y);

        label_totalM = new QLabel(PanelPolarimeter);
        label_totalM->setObjectName(QStringLiteral("label_totalM"));
        sizePolicy4.setHeightForWidth(label_totalM->sizePolicy().hasHeightForWidth());
        label_totalM->setSizePolicy(sizePolicy4);
        label_totalM->setMaximumSize(QSize(16777215, 15));
        QFont font9;
        font9.setPointSize(7);
        font9.setBold(false);
        font9.setWeight(50);
        label_totalM->setFont(font9);

        horizontalLayout_4->addWidget(label_totalM);

        TotalProgressBar_Pol = new QProgressBar(PanelPolarimeter);
        TotalProgressBar_Pol->setObjectName(QStringLiteral("TotalProgressBar_Pol"));
        sizePolicy4.setHeightForWidth(TotalProgressBar_Pol->sizePolicy().hasHeightForWidth());
        TotalProgressBar_Pol->setSizePolicy(sizePolicy4);
        TotalProgressBar_Pol->setMinimumSize(QSize(140, 0));
        TotalProgressBar_Pol->setMaximumSize(QSize(240, 12));
        TotalProgressBar_Pol->setValue(0);

        horizontalLayout_4->addWidget(TotalProgressBar_Pol);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        label_remaining = new QLabel(PanelPolarimeter);
        label_remaining->setObjectName(QStringLiteral("label_remaining"));
        label_remaining->setMinimumSize(QSize(70, 0));
        label_remaining->setMaximumSize(QSize(70, 16777215));
        label_remaining->setFont(font8);

        horizontalLayout_4->addWidget(label_remaining);

        label_RemainingTime = new QLabel(PanelPolarimeter);
        label_RemainingTime->setObjectName(QStringLiteral("label_RemainingTime"));
        label_RemainingTime->setMaximumSize(QSize(100, 12));
        label_RemainingTime->setSizeIncrement(QSize(100, 0));
        label_RemainingTime->setFont(font8);

        horizontalLayout_4->addWidget(label_RemainingTime);

        horizontalSpacer_8 = new QSpacerItem(70, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        label_clearAll = new ClickableLabel(PanelPolarimeter);
        label_clearAll->setObjectName(QStringLiteral("label_clearAll"));
        sizePolicy4.setHeightForWidth(label_clearAll->sizePolicy().hasHeightForWidth());
        label_clearAll->setSizePolicy(sizePolicy4);
        label_clearAll->setMinimumSize(QSize(70, 18));
        label_clearAll->setMaximumSize(QSize(70, 18));
        QFont font10;
        font10.setPointSize(8);
        font10.setUnderline(true);
        label_clearAll->setFont(font10);
        label_clearAll->setCursor(QCursor(Qt::PointingHandCursor));
        label_clearAll->setLayoutDirection(Qt::LeftToRight);
        label_clearAll->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_clearAll);

        help = new QPushButton(PanelPolarimeter);
        help->setObjectName(QStringLiteral("help"));
        sizePolicy4.setHeightForWidth(help->sizePolicy().hasHeightForWidth());
        help->setSizePolicy(sizePolicy4);
        help->setMinimumSize(QSize(18, 16));
        help->setMaximumSize(QSize(18, 16));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/polarimeter/Help.ico"), QSize(), QIcon::Normal, QIcon::Off);
        help->setIcon(icon5);
        help->setIconSize(QSize(20, 20));

        horizontalLayout_4->addWidget(help);

        horizontalSpacer_4 = new QSpacerItem(20, 18, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_7->addLayout(verticalLayout);


        horizonalLayout_2->addLayout(verticalLayout_7);


        gridLayout->addLayout(horizonalLayout_2, 0, 0, 1, 1);


        retranslateUi(PanelPolarimeter);

        Tabs_Plots->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PanelPolarimeter);
    } // setupUi

    void retranslateUi(QWidget *PanelPolarimeter)
    {
        PanelPolarimeter->setWindowTitle(QApplication::translate("PanelPolarimeter", "Form", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_hideConf->setToolTip(QApplication::translate("PanelPolarimeter", "Hide/Show Lateral Panel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_hideConf->setText(QApplication::translate("PanelPolarimeter", "<< Hide Panel", Q_NULLPTR));
        label_Set_Spec_Pol->setText(QApplication::translate("PanelPolarimeter", "Spectrometer:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        list_devices_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Spectrometer Settings", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        FFT_label_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Hide/Show FFT Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        FFT_label_Pol->setText(QApplication::translate("PanelPolarimeter", "Maximum Intensity at", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        waveToPlotFFT->setToolTip(QApplication::translate("PanelPolarimeter", "Change Wavelength", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        waveToPlotFFT->setText(QString());
        label_n->setText(QApplication::translate("PanelPolarimeter", "nm:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol_FFT->setToolTip(QApplication::translate("PanelPolarimeter", "FFT Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_Measurements_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Hide/Show Measurement Profile", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_Measurements_Pol->setText(QApplication::translate("PanelPolarimeter", "Measurement List:", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = Table_Measurements_Pol->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PanelPolarimeter", "Time (h:m:s)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem->setToolTip(QApplication::translate("PanelPolarimeter", "Time Intervals", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem1 = Table_Measurements_Pol->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PanelPolarimeter", "File Name", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem1->setToolTip(QApplication::translate("PanelPolarimeter", "File Name", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        Table_Measurements_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Measurement Profile", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_Save_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Hide/Show Saving Options", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_Save_Pol->setText(QApplication::translate("PanelPolarimeter", "Saving Options:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_AutoSave_Pol_Raw->setToolTip(QApplication::translate("PanelPolarimeter", "Save Raw Data", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_AutoSave_Pol_Raw->setText(QApplication::translate("PanelPolarimeter", "Raw Data", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_AutoSave_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Save FFT Profile", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_AutoSave_Pol->setText(QApplication::translate("PanelPolarimeter", "FFT Profiles", Q_NULLPTR));
        label_5_Pol_settings->setText(QApplication::translate("PanelPolarimeter", "Settings:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_Pol_ConfigureMeasurement->setToolTip(QApplication::translate("PanelPolarimeter", "Configure Measurements", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_Pol_ConfigureMeasurement->setText(QApplication::translate("PanelPolarimeter", " Configure", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_calibrate->setToolTip(QApplication::translate("PanelPolarimeter", "Start/Stop Calibration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_calibrate->setText(QApplication::translate("PanelPolarimeter", " Calibrate", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_Start_Meas_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Start/Stop Measurements", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_Start_Meas_Pol->setText(QApplication::translate("PanelPolarimeter", " Start Measurement", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_raw->setToolTip(QApplication::translate("PanelPolarimeter", "Hide/Show Raw Signal Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_raw->setText(QApplication::translate("PanelPolarimeter", "Raw Signal", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Raw Signal Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_compensation->setToolTip(QApplication::translate("PanelPolarimeter", "Hide/Show Compensation Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_compensation->setText(QApplication::translate("PanelPolarimeter", "W/2W", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol_Compensation->setToolTip(QApplication::translate("PanelPolarimeter", "Compensation Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_fftprofile->setToolTip(QApplication::translate("PanelPolarimeter", "Hide/Show FFT Profile Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_fftprofile->setText(QApplication::translate("PanelPolarimeter", "FFT Profile", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol_w_2w->setToolTip(QApplication::translate("PanelPolarimeter", "FFT Profile Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_average->setToolTip(QApplication::translate("PanelPolarimeter", "Hide/Show Average Signal Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_average->setText(QApplication::translate("PanelPolarimeter", "Average Signal", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol_Average->setToolTip(QApplication::translate("PanelPolarimeter", "Average Signal Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        Tabs_Plots->setTabText(Tabs_Plots->indexOf(liveData), QApplication::translate("PanelPolarimeter", "Live Data", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_prediction->setToolTip(QApplication::translate("PanelPolarimeter", "Hide/Show Prediction Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_prediction->setText(QApplication::translate("PanelPolarimeter", "Prediction", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol_Prediction->setToolTip(QApplication::translate("PanelPolarimeter", "Prediction Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        Tabs_Plots->setTabText(Tabs_Plots->indexOf(MeasResults), QApplication::translate("PanelPolarimeter", "Measurement Results", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_LoadData->setToolTip(QApplication::translate("PanelPolarimeter", "Load Data from Files", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_LoadData->setText(QApplication::translate("PanelPolarimeter", " Load Data", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        Button_Save_Graphs_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Save Graphs as PDF", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        Button_Save_Graphs_Pol->setText(QApplication::translate("PanelPolarimeter", " Save Graphs", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        currentProgressBar_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Current Progress", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        info->setToolTip(QApplication::translate("PanelPolarimeter", "Status Bar", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        info->setText(QString());
        label_totalM->setText(QApplication::translate("PanelPolarimeter", "Total:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        TotalProgressBar_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Total Progress", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_remaining->setText(QApplication::translate("PanelPolarimeter", "Remaining Time:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_RemainingTime->setToolTip(QApplication::translate("PanelPolarimeter", "Remainig time", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_RemainingTime->setText(QApplication::translate("PanelPolarimeter", "0 hours", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_clearAll->setToolTip(QApplication::translate("PanelPolarimeter", "Clear All Configurations", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_clearAll->setText(QApplication::translate("PanelPolarimeter", "Clear All", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        help->setToolTip(QApplication::translate("PanelPolarimeter", "Do you need Help?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        help->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PanelPolarimeter: public Ui_PanelPolarimeter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_PANEL_H
