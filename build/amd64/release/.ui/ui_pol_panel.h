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
#include "qwt_thermo.h"

QT_BEGIN_NAMESPACE

class Ui_PanelPolarimeter
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizonalLayout_2;
    QVBoxLayout *verticalLayout_8;
    ClickableLabel *label_hideConf;
    QLabel *label_Set_Spec_Pol;
    QSpacerItem *verticalSpacer_2;
    QListWidget *list_devices_Pol;
    QFrame *line_c1;
    QHBoxLayout *horizontalLayout_2;
    ClickableLabel *label_temp1;
    QLabel *label_Temperature;
    QSpacerItem *verticalSpacer;
    QwtThermo *Pol_Thermo;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_30;
    QLabel *label_hum1;
    QLabel *label_hum;
    QSpacerItem *verticalSpacer_6;
    QFrame *line_10;
    QLabel *label_Measurements_Pol;
    QSpacerItem *verticalSpacer_3;
    QTableWidget *Table_Measurements_Pol;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_S1;
    QLabel *label_S2;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_S3;
    QLabel *label_S4;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_S5;
    QLabel *label_S6;
    QSpacerItem *verticalSpacerX;
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
    QVBoxLayout *verticalLayout_2;
    QTabWidget *Tabs_Plots;
    QWidget *liveData;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_22;
    QHBoxLayout *horizontalLayout_8;
    ClickableLabel *label_hideLiveRaw;
    QLabel *label_RS;
    QSpacerItem *horizontalSpacer_26;
    QFrame *line_3;
    QSpacerItem *horizontalSpacer_27;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_Rat;
    ClickableLabel *label_HideRatio;
    QSpacerItem *horizontalSpacer_24;
    QFrame *line_HLiveRatio;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_raw;
    QLabel *label_PlotSaturated;
    Plot *qwtPlot_Pol;
    QSpacerItem *horizontalSpacer_12;
    QFrame *line_rawratio;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_compensation;
    Plot *qwtPlot_Pol_Compensation;
    QSpacerItem *horizontalSpacer_18;
    QFrame *line_HLive;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_19;
    QVBoxLayout *verticalLayout_13;
    ClickableLabel *label_fftprofile;
    Plot *qwtPlot_Pol_w_2w;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line_FFT;
    QSpacerItem *horizontalSpacer_13;
    QVBoxLayout *verticalLayout_14;
    ClickableLabel *label_average;
    Plot *qwtPlot_Pol_Average;
    QSpacerItem *horizontalSpacer_20;
    QFrame *line_HFFTAverage;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_16;
    QHBoxLayout *horizontalLayout_15;
    ClickableLabel *label_HideFFTProfile;
    QLabel *label_HProf;
    QSpacerItem *horizontalSpacer_21;
    QFrame *line_9;
    QSpacerItem *horizontalSpacer_23;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_HAver;
    ClickableLabel *label_HIdeLiveAverage;
    QSpacerItem *horizontalSpacer_25;
    QWidget *tab;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_29;
    QSpacerItem *horizontalSpacer_37;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_TemperaturePlot;
    QLabel *label_NoComTeensy;
    Plot *qwtPlot_Pol_Temperature;
    QSpacerItem *horizontalSpacer_38;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_28;
    QSpacerItem *horizontalSpacer_39;
    QVBoxLayout *verticalLayout_18;
    ClickableLabel *waveToPlotFFT;
    Plot *qwtPlot_Pol_FFT;
    QSpacerItem *horizontalSpacer_40;
    QWidget *MeasResults;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_17;
    QHBoxLayout *horizontalLayout_16;
    ClickableLabel *label_hideSpectra;
    QLabel *label_SP;
    QSpacerItem *horizontalSpacer_28;
    QFrame *line_7;
    QSpacerItem *horizontalSpacer_29;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_PSNS;
    ClickableLabel *label_hidePrediction;
    QSpacerItem *horizontalSpacer_30;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_32;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_spectra;
    QWidget *widget_Spectra;
    QHBoxLayout *horizontalLayout_22;
    QHBoxLayout *VLP;
    QFrame *line_SpeNormSpec;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_Nspectra;
    QWidget *widget_NormSpectra;
    QHBoxLayout *horizontalLayout_23;
    QHBoxLayout *VLP_norm;
    QSpacerItem *horizontalSpacer_14;
    QFrame *line_pred;
    QSpacerItem *horizontalSpacer_31;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_prediction;
    QWidget *widget_errorBar;
    QHBoxLayout *horizontalLayout_27;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_PredictionError;
    QLabel *label_PError;
    QLabel *label_R2_1;
    QLabel *label_R2;
    Plot *qwtPlot_Pol_Prediction;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_21;
    QSpacerItem *horizontalSpacer_34;
    QHBoxLayout *horizontalLayout_24;
    ClickableLabel *label_hideNSpectra;
    QLabel *label_NSP;
    QSpacerItem *horizontalSpacer_36;
    QFrame *line_6;
    QSpacerItem *horizontalSpacer_35;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_P1;
    QLabel *label_P2;
    QSpacerItem *horizontalSpacer_33;
    QWidget *MeasStadistics;
    QVBoxLayout *verticalLayout_9;
    QFrame *line_8;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *button_AnalizeData;
    QPushButton *button_LoadData;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *button_SaveInstantFFT;
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
        PanelPolarimeter->resize(1157, 862);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PanelPolarimeter->sizePolicy().hasHeightForWidth());
        PanelPolarimeter->setSizePolicy(sizePolicy);
        PanelPolarimeter->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(PanelPolarimeter);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
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
        label_hideConf->setMinimumSize(QSize(300, 0));
        label_hideConf->setMaximumSize(QSize(300, 16777215));
        QFont font;
        font.setPointSize(7);
        font.setUnderline(false);
        label_hideConf->setFont(font);
        label_hideConf->setCursor(QCursor(Qt::PointingHandCursor));
        label_hideConf->setAcceptDrops(false);
        label_hideConf->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_8->addWidget(label_hideConf);

        label_Set_Spec_Pol = new QLabel(PanelPolarimeter);
        label_Set_Spec_Pol->setObjectName(QStringLiteral("label_Set_Spec_Pol"));
        sizePolicy1.setHeightForWidth(label_Set_Spec_Pol->sizePolicy().hasHeightForWidth());
        label_Set_Spec_Pol->setSizePolicy(sizePolicy1);
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
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(list_devices_Pol->sizePolicy().hasHeightForWidth());
        list_devices_Pol->setSizePolicy(sizePolicy2);
        list_devices_Pol->setMinimumSize(QSize(300, 180));
        list_devices_Pol->setMaximumSize(QSize(300, 221));
        list_devices_Pol->setBaseSize(QSize(0, 221));
        list_devices_Pol->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        list_devices_Pol->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        list_devices_Pol->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        list_devices_Pol->setAutoScroll(true);
        list_devices_Pol->setAutoScrollMargin(18);
        list_devices_Pol->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        list_devices_Pol->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        list_devices_Pol->setProperty("isWrapping", QVariant(false));
        list_devices_Pol->setResizeMode(QListView::Adjust);
        list_devices_Pol->setViewMode(QListView::ListMode);

        verticalLayout_8->addWidget(list_devices_Pol);

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
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_temp1 = new ClickableLabel(PanelPolarimeter);
        label_temp1->setObjectName(QStringLiteral("label_temp1"));
        sizePolicy1.setHeightForWidth(label_temp1->sizePolicy().hasHeightForWidth());
        label_temp1->setSizePolicy(sizePolicy1);
        label_temp1->setMaximumSize(QSize(120, 16777215));
        label_temp1->setFont(font1);
        label_temp1->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(label_temp1);

        label_Temperature = new QLabel(PanelPolarimeter);
        label_Temperature->setObjectName(QStringLiteral("label_Temperature"));
        sizePolicy1.setHeightForWidth(label_Temperature->sizePolicy().hasHeightForWidth());
        label_Temperature->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        label_Temperature->setFont(font2);

        horizontalLayout_2->addWidget(label_Temperature);


        verticalLayout_8->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer);

        Pol_Thermo = new QwtThermo(PanelPolarimeter);
        Pol_Thermo->setObjectName(QStringLiteral("Pol_Thermo"));
        sizePolicy3.setHeightForWidth(Pol_Thermo->sizePolicy().hasHeightForWidth());
        Pol_Thermo->setSizePolicy(sizePolicy3);
        Pol_Thermo->setMinimumSize(QSize(300, 0));
        Pol_Thermo->setMaximumSize(QSize(300, 16777215));
        QPalette palette;
        QBrush brush(QColor(0, 170, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        Pol_Thermo->setPalette(palette);
        QFont font3;
        font3.setPointSize(8);
        Pol_Thermo->setFont(font3);
        Pol_Thermo->setLowerBound(27);
        Pol_Thermo->setUpperBound(37);
        Pol_Thermo->setScaleMaxMajor(5);
        Pol_Thermo->setScaleMaxMinor(5);
        Pol_Thermo->setScaleStepSize(1);
        Pol_Thermo->setOrientation(Qt::Horizontal);
        Pol_Thermo->setScalePosition(QwtThermo::TrailingScale);
        Pol_Thermo->setOriginMode(QwtThermo::OriginMinimum);
        Pol_Thermo->setAlarmEnabled(false);
        Pol_Thermo->setOrigin(0);
        Pol_Thermo->setSpacing(2);
        Pol_Thermo->setPipeWidth(8);
        Pol_Thermo->setValue(0);

        verticalLayout_8->addWidget(Pol_Thermo);

        verticalSpacer_9 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_9);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setObjectName(QStringLiteral("horizontalLayout_30"));
        label_hum1 = new QLabel(PanelPolarimeter);
        label_hum1->setObjectName(QStringLiteral("label_hum1"));
        sizePolicy1.setHeightForWidth(label_hum1->sizePolicy().hasHeightForWidth());
        label_hum1->setSizePolicy(sizePolicy1);
        label_hum1->setMaximumSize(QSize(100, 16777215));
        label_hum1->setFont(font1);

        horizontalLayout_30->addWidget(label_hum1);

        label_hum = new QLabel(PanelPolarimeter);
        label_hum->setObjectName(QStringLiteral("label_hum"));
        sizePolicy1.setHeightForWidth(label_hum->sizePolicy().hasHeightForWidth());
        label_hum->setSizePolicy(sizePolicy1);
        label_hum->setFont(font2);

        horizontalLayout_30->addWidget(label_hum);


        verticalLayout_8->addLayout(horizontalLayout_30);

        verticalSpacer_6 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_6);

        line_10 = new QFrame(PanelPolarimeter);
        line_10->setObjectName(QStringLiteral("line_10"));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);

        verticalLayout_8->addWidget(line_10);

        label_Measurements_Pol = new QLabel(PanelPolarimeter);
        label_Measurements_Pol->setObjectName(QStringLiteral("label_Measurements_Pol"));
        sizePolicy1.setHeightForWidth(label_Measurements_Pol->sizePolicy().hasHeightForWidth());
        label_Measurements_Pol->setSizePolicy(sizePolicy1);
        label_Measurements_Pol->setMinimumSize(QSize(0, 0));
        label_Measurements_Pol->setMaximumSize(QSize(16777215, 15));
        label_Measurements_Pol->setFont(font1);
        label_Measurements_Pol->setCursor(QCursor(Qt::ArrowCursor));

        verticalLayout_8->addWidget(label_Measurements_Pol);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_3);

        Table_Measurements_Pol = new QTableWidget(PanelPolarimeter);
        if (Table_Measurements_Pol->columnCount() < 8)
            Table_Measurements_Pol->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setBackground(QColor(255, 255, 255));
        Table_Measurements_Pol->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setBackground(QColor(255, 255, 255));
        Table_Measurements_Pol->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        Table_Measurements_Pol->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        Table_Measurements_Pol->setObjectName(QStringLiteral("Table_Measurements_Pol"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(Table_Measurements_Pol->sizePolicy().hasHeightForWidth());
        Table_Measurements_Pol->setSizePolicy(sizePolicy4);
        Table_Measurements_Pol->setMinimumSize(QSize(300, 50));
        Table_Measurements_Pol->setMaximumSize(QSize(300, 530));
        Table_Measurements_Pol->setLineWidth(1);
        Table_Measurements_Pol->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        Table_Measurements_Pol->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        Table_Measurements_Pol->setAutoScroll(true);
        Table_Measurements_Pol->setAutoScrollMargin(10);
        Table_Measurements_Pol->setEditTriggers(QAbstractItemView::NoEditTriggers);
        Table_Measurements_Pol->setSelectionMode(QAbstractItemView::NoSelection);
        Table_Measurements_Pol->setSelectionBehavior(QAbstractItemView::SelectItems);
        Table_Measurements_Pol->setTextElideMode(Qt::ElideRight);
        Table_Measurements_Pol->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        Table_Measurements_Pol->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
        Table_Measurements_Pol->setShowGrid(true);
        Table_Measurements_Pol->setRowCount(0);
        Table_Measurements_Pol->setColumnCount(8);
        Table_Measurements_Pol->horizontalHeader()->setCascadingSectionResizes(false);
        Table_Measurements_Pol->horizontalHeader()->setDefaultSectionSize(78);
        Table_Measurements_Pol->horizontalHeader()->setMinimumSectionSize(31);
        Table_Measurements_Pol->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        Table_Measurements_Pol->horizontalHeader()->setStretchLastSection(true);
        Table_Measurements_Pol->verticalHeader()->setVisible(false);
        Table_Measurements_Pol->verticalHeader()->setCascadingSectionResizes(false);
        Table_Measurements_Pol->verticalHeader()->setDefaultSectionSize(30);
        Table_Measurements_Pol->verticalHeader()->setHighlightSections(true);
        Table_Measurements_Pol->verticalHeader()->setMinimumSectionSize(39);
        Table_Measurements_Pol->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        Table_Measurements_Pol->verticalHeader()->setStretchLastSection(false);

        verticalLayout_8->addWidget(Table_Measurements_Pol);

        verticalSpacer_5 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_5);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_S1 = new QLabel(PanelPolarimeter);
        label_S1->setObjectName(QStringLiteral("label_S1"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_S1->sizePolicy().hasHeightForWidth());
        label_S1->setSizePolicy(sizePolicy5);
        label_S1->setMinimumSize(QSize(95, 0));
        label_S1->setMaximumSize(QSize(95, 16777215));
        label_S1->setSizeIncrement(QSize(150, 0));
        QPalette palette1;
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        QBrush brush3(QColor(255, 255, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        QBrush brush4(QColor(240, 240, 240, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        label_S1->setPalette(palette1);
        QFont font4;
        font4.setPointSize(8);
        font4.setBold(true);
        font4.setWeight(75);
        label_S1->setFont(font4);
        label_S1->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_17->addWidget(label_S1);

        label_S2 = new QLabel(PanelPolarimeter);
        label_S2->setObjectName(QStringLiteral("label_S2"));
        sizePolicy5.setHeightForWidth(label_S2->sizePolicy().hasHeightForWidth());
        label_S2->setSizePolicy(sizePolicy5);
        label_S2->setMinimumSize(QSize(95, 0));
        label_S2->setMaximumSize(QSize(95, 16777215));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        label_S2->setPalette(palette2);
        label_S2->setFont(font4);
        label_S2->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_17->addWidget(label_S2);


        verticalLayout_8->addLayout(horizontalLayout_17);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_S3 = new QLabel(PanelPolarimeter);
        label_S3->setObjectName(QStringLiteral("label_S3"));
        sizePolicy5.setHeightForWidth(label_S3->sizePolicy().hasHeightForWidth());
        label_S3->setSizePolicy(sizePolicy5);
        label_S3->setMinimumSize(QSize(95, 0));
        label_S3->setMaximumSize(QSize(95, 16777215));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        label_S3->setPalette(palette3);
        label_S3->setFont(font4);
        label_S3->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_19->addWidget(label_S3);

        label_S4 = new QLabel(PanelPolarimeter);
        label_S4->setObjectName(QStringLiteral("label_S4"));
        sizePolicy5.setHeightForWidth(label_S4->sizePolicy().hasHeightForWidth());
        label_S4->setSizePolicy(sizePolicy5);
        label_S4->setMinimumSize(QSize(95, 0));
        label_S4->setMaximumSize(QSize(95, 16777215));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        label_S4->setPalette(palette4);
        label_S4->setFont(font4);
        label_S4->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_19->addWidget(label_S4);


        verticalLayout_8->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_S5 = new QLabel(PanelPolarimeter);
        label_S5->setObjectName(QStringLiteral("label_S5"));
        sizePolicy5.setHeightForWidth(label_S5->sizePolicy().hasHeightForWidth());
        label_S5->setSizePolicy(sizePolicy5);
        label_S5->setMinimumSize(QSize(95, 0));
        label_S5->setMaximumSize(QSize(95, 16777215));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        label_S5->setPalette(palette5);
        label_S5->setFont(font4);
        label_S5->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_20->addWidget(label_S5);

        label_S6 = new QLabel(PanelPolarimeter);
        label_S6->setObjectName(QStringLiteral("label_S6"));
        sizePolicy5.setHeightForWidth(label_S6->sizePolicy().hasHeightForWidth());
        label_S6->setSizePolicy(sizePolicy5);
        label_S6->setMinimumSize(QSize(95, 0));
        label_S6->setMaximumSize(QSize(95, 16777215));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette6.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush4);
        label_S6->setPalette(palette6);
        label_S6->setFont(font4);
        label_S6->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);

        horizontalLayout_20->addWidget(label_S6);


        verticalLayout_8->addLayout(horizontalLayout_20);

        verticalSpacerX = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacerX);

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
        label_5_Pol_settings->setMaximumSize(QSize(16777215, 20));
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
        button_Start_Meas_Pol->setMinimumSize(QSize(260, 50));
        button_Start_Meas_Pol->setMaximumSize(QSize(260, 50));
        button_Start_Meas_Pol->setFont(font2);
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
        line_2->setFrameShadow(QFrame::Sunken);
        line_2->setLineWidth(1);
        line_2->setMidLineWidth(0);
        line_2->setFrameShape(QFrame::VLine);

        horizonalLayout_2->addWidget(line_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        Tabs_Plots = new QTabWidget(PanelPolarimeter);
        Tabs_Plots->setObjectName(QStringLiteral("Tabs_Plots"));
        Tabs_Plots->setEnabled(true);
        Tabs_Plots->setTabPosition(QTabWidget::North);
        Tabs_Plots->setTabShape(QTabWidget::Rounded);
        Tabs_Plots->setIconSize(QSize(14, 14));
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
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_22 = new QSpacerItem(5, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_22);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_hideLiveRaw = new ClickableLabel(liveData);
        label_hideLiveRaw->setObjectName(QStringLiteral("label_hideLiveRaw"));
        label_hideLiveRaw->setMinimumSize(QSize(100, 0));
        label_hideLiveRaw->setFont(font);
        label_hideLiveRaw->setCursor(QCursor(Qt::PointingHandCursor));
        label_hideLiveRaw->setFrameShape(QFrame::NoFrame);
        label_hideLiveRaw->setFrameShadow(QFrame::Plain);

        horizontalLayout_8->addWidget(label_hideLiveRaw);

        label_RS = new QLabel(liveData);
        label_RS->setObjectName(QStringLiteral("label_RS"));
        QSizePolicy sizePolicy6(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(label_RS->sizePolicy().hasHeightForWidth());
        label_RS->setSizePolicy(sizePolicy6);
        label_RS->setMinimumSize(QSize(0, 0));
        label_RS->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_8->addWidget(label_RS);


        horizontalLayout_7->addLayout(horizontalLayout_8);

        horizontalSpacer_26 = new QSpacerItem(2, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_26);

        line_3 = new QFrame(liveData);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_7->addWidget(line_3);

        horizontalSpacer_27 = new QSpacerItem(2, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_27);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_Rat = new QLabel(liveData);
        label_Rat->setObjectName(QStringLiteral("label_Rat"));
        sizePolicy6.setHeightForWidth(label_Rat->sizePolicy().hasHeightForWidth());
        label_Rat->setSizePolicy(sizePolicy6);

        horizontalLayout_11->addWidget(label_Rat);

        label_HideRatio = new ClickableLabel(liveData);
        label_HideRatio->setObjectName(QStringLiteral("label_HideRatio"));
        label_HideRatio->setMinimumSize(QSize(100, 0));
        label_HideRatio->setFont(font);
        label_HideRatio->setCursor(QCursor(Qt::PointingHandCursor));
        label_HideRatio->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_HideRatio);


        horizontalLayout_7->addLayout(horizontalLayout_11);

        horizontalSpacer_24 = new QSpacerItem(5, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_24);


        verticalLayout_3->addLayout(horizontalLayout_7);

        line_HLiveRatio = new QFrame(liveData);
        line_HLiveRatio->setObjectName(QStringLiteral("line_HLiveRatio"));
        line_HLiveRatio->setFrameShape(QFrame::HLine);
        line_HLiveRatio->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_HLiveRatio);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalSpacer_10 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_10);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_raw = new QLabel(liveData);
        label_raw->setObjectName(QStringLiteral("label_raw"));
        sizePolicy1.setHeightForWidth(label_raw->sizePolicy().hasHeightForWidth());
        label_raw->setSizePolicy(sizePolicy1);
        label_raw->setMinimumSize(QSize(0, 14));
        label_raw->setMaximumSize(QSize(16777213, 14));
        QPalette palette7;
        QBrush brush5(QColor(0, 0, 255, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette7.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_raw->setPalette(palette7);
        QFont font5;
        font5.setPointSize(10);
        font5.setBold(true);
        font5.setUnderline(false);
        font5.setWeight(75);
        label_raw->setFont(font5);
        label_raw->setCursor(QCursor(Qt::ArrowCursor));
        label_raw->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(label_raw);

        label_PlotSaturated = new QLabel(liveData);
        label_PlotSaturated->setObjectName(QStringLiteral("label_PlotSaturated"));
        sizePolicy.setHeightForWidth(label_PlotSaturated->sizePolicy().hasHeightForWidth());
        label_PlotSaturated->setSizePolicy(sizePolicy);
        QPalette palette8;
        QBrush brush6(QColor(255, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_PlotSaturated->setPalette(palette8);
        QFont font6;
        font6.setPointSize(12);
        font6.setBold(true);
        font6.setItalic(false);
        font6.setUnderline(false);
        font6.setWeight(75);
        font6.setStrikeOut(false);
        label_PlotSaturated->setFont(font6);
        label_PlotSaturated->setLayoutDirection(Qt::LeftToRight);
        label_PlotSaturated->setFrameShape(QFrame::NoFrame);
        label_PlotSaturated->setFrameShadow(QFrame::Plain);
        label_PlotSaturated->setTextFormat(Qt::AutoText);
        label_PlotSaturated->setScaledContents(false);
        label_PlotSaturated->setAlignment(Qt::AlignCenter);
        label_PlotSaturated->setWordWrap(false);
        label_PlotSaturated->setMargin(0);
        label_PlotSaturated->setIndent(-1);

        verticalLayout_10->addWidget(label_PlotSaturated);

        qwtPlot_Pol = new Plot(liveData);
        qwtPlot_Pol->setObjectName(QStringLiteral("qwtPlot_Pol"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(qwtPlot_Pol->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol->setSizePolicy(sizePolicy7);
        qwtPlot_Pol->setMinimumSize(QSize(0, 0));
        qwtPlot_Pol->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol->setFrameShadow(QFrame::Raised);

        verticalLayout_10->addWidget(qwtPlot_Pol);


        horizontalLayout_13->addLayout(verticalLayout_10);

        horizontalSpacer_12 = new QSpacerItem(2, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);

        line_rawratio = new QFrame(liveData);
        line_rawratio->setObjectName(QStringLiteral("line_rawratio"));
        line_rawratio->setLineWidth(1);
        line_rawratio->setMidLineWidth(0);
        line_rawratio->setFrameShape(QFrame::VLine);
        line_rawratio->setFrameShadow(QFrame::Sunken);

        horizontalLayout_13->addWidget(line_rawratio);

        horizontalSpacer_6 = new QSpacerItem(2, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_6);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_compensation = new QLabel(liveData);
        label_compensation->setObjectName(QStringLiteral("label_compensation"));
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette9.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette9.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_compensation->setPalette(palette9);
        label_compensation->setFont(font5);
        label_compensation->setCursor(QCursor(Qt::ArrowCursor));
        label_compensation->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_compensation);

        qwtPlot_Pol_Compensation = new Plot(liveData);
        qwtPlot_Pol_Compensation->setObjectName(QStringLiteral("qwtPlot_Pol_Compensation"));
        sizePolicy7.setHeightForWidth(qwtPlot_Pol_Compensation->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol_Compensation->setSizePolicy(sizePolicy7);
        qwtPlot_Pol_Compensation->setMinimumSize(QSize(0, 0));
        qwtPlot_Pol_Compensation->setMaximumSize(QSize(16777215, 16777215));
        qwtPlot_Pol_Compensation->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_Compensation->setFrameShadow(QFrame::Raised);

        verticalLayout_11->addWidget(qwtPlot_Pol_Compensation);


        horizontalLayout_13->addLayout(verticalLayout_11);

        horizontalSpacer_18 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_18);


        verticalLayout_3->addLayout(horizontalLayout_13);

        line_HLive = new QFrame(liveData);
        line_HLive->setObjectName(QStringLiteral("line_HLive"));
        line_HLive->setLineWidth(1);
        line_HLive->setMidLineWidth(0);
        line_HLive->setFrameShape(QFrame::HLine);
        line_HLive->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_HLive);

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
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette10.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette10.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_fftprofile->setPalette(palette10);
        label_fftprofile->setFont(font5);
        label_fftprofile->setCursor(QCursor(Qt::ArrowCursor));
        label_fftprofile->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_fftprofile);

        qwtPlot_Pol_w_2w = new Plot(liveData);
        qwtPlot_Pol_w_2w->setObjectName(QStringLiteral("qwtPlot_Pol_w_2w"));
        sizePolicy7.setHeightForWidth(qwtPlot_Pol_w_2w->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol_w_2w->setSizePolicy(sizePolicy7);
        qwtPlot_Pol_w_2w->setMinimumSize(QSize(0, 0));
        qwtPlot_Pol_w_2w->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_w_2w->setFrameShadow(QFrame::Raised);

        verticalLayout_13->addWidget(qwtPlot_Pol_w_2w);


        horizontalLayout_10->addLayout(verticalLayout_13);

        horizontalSpacer_3 = new QSpacerItem(2, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);

        line_FFT = new QFrame(liveData);
        line_FFT->setObjectName(QStringLiteral("line_FFT"));
        line_FFT->setLineWidth(1);
        line_FFT->setMidLineWidth(0);
        line_FFT->setFrameShape(QFrame::VLine);
        line_FFT->setFrameShadow(QFrame::Sunken);

        horizontalLayout_10->addWidget(line_FFT);

        horizontalSpacer_13 = new QSpacerItem(2, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_13);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        label_average = new ClickableLabel(liveData);
        label_average->setObjectName(QStringLiteral("label_average"));
        sizePolicy.setHeightForWidth(label_average->sizePolicy().hasHeightForWidth());
        label_average->setSizePolicy(sizePolicy);
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette11.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette11.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_average->setPalette(palette11);
        label_average->setFont(font5);
        label_average->setCursor(QCursor(Qt::ArrowCursor));
        label_average->setAlignment(Qt::AlignCenter);
        label_average->setWordWrap(false);
        label_average->setMargin(0);
        label_average->setIndent(-1);

        verticalLayout_14->addWidget(label_average);

        qwtPlot_Pol_Average = new Plot(liveData);
        qwtPlot_Pol_Average->setObjectName(QStringLiteral("qwtPlot_Pol_Average"));
        sizePolicy7.setHeightForWidth(qwtPlot_Pol_Average->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol_Average->setSizePolicy(sizePolicy7);
        qwtPlot_Pol_Average->setMinimumSize(QSize(0, 0));
        qwtPlot_Pol_Average->setMaximumSize(QSize(16777215, 16777215));
        qwtPlot_Pol_Average->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_Average->setFrameShadow(QFrame::Raised);

        verticalLayout_14->addWidget(qwtPlot_Pol_Average);


        horizontalLayout_10->addLayout(verticalLayout_14);

        horizontalSpacer_20 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_20);


        verticalLayout_3->addLayout(horizontalLayout_10);

        line_HFFTAverage = new QFrame(liveData);
        line_HFFTAverage->setObjectName(QStringLiteral("line_HFFTAverage"));
        line_HFFTAverage->setFrameShape(QFrame::HLine);
        line_HFFTAverage->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_HFFTAverage);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalSpacer_16 = new QSpacerItem(5, 5, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_16);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_HideFFTProfile = new ClickableLabel(liveData);
        label_HideFFTProfile->setObjectName(QStringLiteral("label_HideFFTProfile"));
        label_HideFFTProfile->setMinimumSize(QSize(100, 0));
        QFont font7;
        font7.setPointSize(7);
        font7.setItalic(false);
        font7.setUnderline(false);
        label_HideFFTProfile->setFont(font7);
        label_HideFFTProfile->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_15->addWidget(label_HideFFTProfile);

        label_HProf = new QLabel(liveData);
        label_HProf->setObjectName(QStringLiteral("label_HProf"));
        sizePolicy6.setHeightForWidth(label_HProf->sizePolicy().hasHeightForWidth());
        label_HProf->setSizePolicy(sizePolicy6);

        horizontalLayout_15->addWidget(label_HProf);


        horizontalLayout_12->addLayout(horizontalLayout_15);

        horizontalSpacer_21 = new QSpacerItem(2, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_21);

        line_9 = new QFrame(liveData);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setFrameShape(QFrame::VLine);
        line_9->setFrameShadow(QFrame::Sunken);

        horizontalLayout_12->addWidget(line_9);

        horizontalSpacer_23 = new QSpacerItem(2, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_23);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_HAver = new QLabel(liveData);
        label_HAver->setObjectName(QStringLiteral("label_HAver"));
        sizePolicy6.setHeightForWidth(label_HAver->sizePolicy().hasHeightForWidth());
        label_HAver->setSizePolicy(sizePolicy6);

        horizontalLayout_14->addWidget(label_HAver);

        label_HIdeLiveAverage = new ClickableLabel(liveData);
        label_HIdeLiveAverage->setObjectName(QStringLiteral("label_HIdeLiveAverage"));
        label_HIdeLiveAverage->setMinimumSize(QSize(100, 0));
        label_HIdeLiveAverage->setFont(font);
        label_HIdeLiveAverage->setCursor(QCursor(Qt::PointingHandCursor));
        label_HIdeLiveAverage->setLayoutDirection(Qt::LeftToRight);
        label_HIdeLiveAverage->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_HIdeLiveAverage);


        horizontalLayout_12->addLayout(horizontalLayout_14);

        horizontalSpacer_25 = new QSpacerItem(5, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_25);


        verticalLayout_3->addLayout(horizontalLayout_12);

        QIcon icon3;
        icon3.addFile(QStringLiteral(":/polarimeter/Run.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Tabs_Plots->addTab(liveData, icon3, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_16 = new QVBoxLayout(tab);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setObjectName(QStringLiteral("horizontalLayout_29"));
        horizontalSpacer_37 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_37);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        label_TemperaturePlot = new QLabel(tab);
        label_TemperaturePlot->setObjectName(QStringLiteral("label_TemperaturePlot"));
        sizePolicy1.setHeightForWidth(label_TemperaturePlot->sizePolicy().hasHeightForWidth());
        label_TemperaturePlot->setSizePolicy(sizePolicy1);
        label_TemperaturePlot->setMinimumSize(QSize(0, 14));
        label_TemperaturePlot->setMaximumSize(QSize(16777215, 14));
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette12.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette12.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_TemperaturePlot->setPalette(palette12);
        QFont font8;
        font8.setPointSize(10);
        font8.setBold(true);
        font8.setWeight(75);
        label_TemperaturePlot->setFont(font8);
        label_TemperaturePlot->setAlignment(Qt::AlignCenter);

        verticalLayout_17->addWidget(label_TemperaturePlot);

        label_NoComTeensy = new QLabel(tab);
        label_NoComTeensy->setObjectName(QStringLiteral("label_NoComTeensy"));
        sizePolicy.setHeightForWidth(label_NoComTeensy->sizePolicy().hasHeightForWidth());
        label_NoComTeensy->setSizePolicy(sizePolicy);
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        palette13.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette13.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_NoComTeensy->setPalette(palette13);
        QFont font9;
        font9.setPointSize(12);
        font9.setBold(true);
        font9.setWeight(75);
        label_NoComTeensy->setFont(font9);
        label_NoComTeensy->setAlignment(Qt::AlignCenter);

        verticalLayout_17->addWidget(label_NoComTeensy);

        qwtPlot_Pol_Temperature = new Plot(tab);
        qwtPlot_Pol_Temperature->setObjectName(QStringLiteral("qwtPlot_Pol_Temperature"));
        sizePolicy7.setHeightForWidth(qwtPlot_Pol_Temperature->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol_Temperature->setSizePolicy(sizePolicy7);

        verticalLayout_17->addWidget(qwtPlot_Pol_Temperature);


        horizontalLayout_29->addLayout(verticalLayout_17);

        horizontalSpacer_38 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_38);


        verticalLayout_16->addLayout(horizontalLayout_29);

        line_5 = new QFrame(tab);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout_16->addWidget(line_5);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QStringLiteral("horizontalLayout_28"));
        horizontalSpacer_39 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_39);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        waveToPlotFFT = new ClickableLabel(tab);
        waveToPlotFFT->setObjectName(QStringLiteral("waveToPlotFFT"));
        sizePolicy1.setHeightForWidth(waveToPlotFFT->sizePolicy().hasHeightForWidth());
        waveToPlotFFT->setSizePolicy(sizePolicy1);
        waveToPlotFFT->setMinimumSize(QSize(0, 14));
        waveToPlotFFT->setMaximumSize(QSize(16777215, 14));
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette14.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette14.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        waveToPlotFFT->setPalette(palette14);
        waveToPlotFFT->setFont(font8);
        waveToPlotFFT->setCursor(QCursor(Qt::PointingHandCursor));
        waveToPlotFFT->setAlignment(Qt::AlignCenter);

        verticalLayout_18->addWidget(waveToPlotFFT);

        qwtPlot_Pol_FFT = new Plot(tab);
        qwtPlot_Pol_FFT->setObjectName(QStringLiteral("qwtPlot_Pol_FFT"));
        sizePolicy7.setHeightForWidth(qwtPlot_Pol_FFT->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol_FFT->setSizePolicy(sizePolicy7);
        qwtPlot_Pol_FFT->setMinimumSize(QSize(0, 0));
        qwtPlot_Pol_FFT->setMaximumSize(QSize(16777215, 16777215));
        qwtPlot_Pol_FFT->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_FFT->setFrameShadow(QFrame::Raised);

        verticalLayout_18->addWidget(qwtPlot_Pol_FFT);


        horizontalLayout_28->addLayout(verticalLayout_18);

        horizontalSpacer_40 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_40);


        verticalLayout_16->addLayout(horizontalLayout_28);

        Tabs_Plots->addTab(tab, icon1, QString());
        MeasResults = new QWidget();
        MeasResults->setObjectName(QStringLiteral("MeasResults"));
        verticalLayout_4 = new QVBoxLayout(MeasResults);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_17 = new QSpacerItem(5, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_17);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_hideSpectra = new ClickableLabel(MeasResults);
        label_hideSpectra->setObjectName(QStringLiteral("label_hideSpectra"));
        label_hideSpectra->setMinimumSize(QSize(100, 0));
        QFont font10;
        font10.setPointSize(7);
        label_hideSpectra->setFont(font10);
        label_hideSpectra->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_16->addWidget(label_hideSpectra);

        label_SP = new QLabel(MeasResults);
        label_SP->setObjectName(QStringLiteral("label_SP"));
        sizePolicy6.setHeightForWidth(label_SP->sizePolicy().hasHeightForWidth());
        label_SP->setSizePolicy(sizePolicy6);

        horizontalLayout_16->addWidget(label_SP);


        horizontalLayout->addLayout(horizontalLayout_16);

        horizontalSpacer_28 = new QSpacerItem(2, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_28);

        line_7 = new QFrame(MeasResults);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_7);

        horizontalSpacer_29 = new QSpacerItem(2, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_29);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_PSNS = new QLabel(MeasResults);
        label_PSNS->setObjectName(QStringLiteral("label_PSNS"));
        sizePolicy6.setHeightForWidth(label_PSNS->sizePolicy().hasHeightForWidth());
        label_PSNS->setSizePolicy(sizePolicy6);

        horizontalLayout_18->addWidget(label_PSNS);

        label_hidePrediction = new ClickableLabel(MeasResults);
        label_hidePrediction->setObjectName(QStringLiteral("label_hidePrediction"));
        label_hidePrediction->setMinimumSize(QSize(70, 0));
        label_hidePrediction->setFont(font10);
        label_hidePrediction->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_18->addWidget(label_hidePrediction);


        horizontalLayout->addLayout(horizontalLayout_18);

        horizontalSpacer_30 = new QSpacerItem(5, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_30);


        verticalLayout_4->addLayout(horizontalLayout);

        line = new QFrame(MeasResults);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_32 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_32);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        label_spectra = new QLabel(MeasResults);
        label_spectra->setObjectName(QStringLiteral("label_spectra"));
        label_spectra->setMinimumSize(QSize(0, 14));
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette15.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette15.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_spectra->setPalette(palette15);
        QFont font11;
        font11.setPointSize(9);
        font11.setBold(true);
        font11.setUnderline(false);
        font11.setWeight(75);
        label_spectra->setFont(font11);
        label_spectra->setCursor(QCursor(Qt::ArrowCursor));
        label_spectra->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(label_spectra);

        widget_Spectra = new QWidget(MeasResults);
        widget_Spectra->setObjectName(QStringLiteral("widget_Spectra"));
        sizePolicy7.setHeightForWidth(widget_Spectra->sizePolicy().hasHeightForWidth());
        widget_Spectra->setSizePolicy(sizePolicy7);
        horizontalLayout_22 = new QHBoxLayout(widget_Spectra);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        VLP = new QHBoxLayout();
        VLP->setObjectName(QStringLiteral("VLP"));

        horizontalLayout_22->addLayout(VLP);


        verticalLayout_12->addWidget(widget_Spectra);


        verticalLayout_6->addLayout(verticalLayout_12);

        line_SpeNormSpec = new QFrame(MeasResults);
        line_SpeNormSpec->setObjectName(QStringLiteral("line_SpeNormSpec"));
        line_SpeNormSpec->setFrameShape(QFrame::HLine);
        line_SpeNormSpec->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_SpeNormSpec);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        label_Nspectra = new QLabel(MeasResults);
        label_Nspectra->setObjectName(QStringLiteral("label_Nspectra"));
        label_Nspectra->setMinimumSize(QSize(0, 14));
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette16.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette16.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_Nspectra->setPalette(palette16);
        QFont font12;
        font12.setPointSize(9);
        font12.setBold(true);
        font12.setWeight(75);
        label_Nspectra->setFont(font12);
        label_Nspectra->setAlignment(Qt::AlignCenter);

        verticalLayout_15->addWidget(label_Nspectra);

        widget_NormSpectra = new QWidget(MeasResults);
        widget_NormSpectra->setObjectName(QStringLiteral("widget_NormSpectra"));
        sizePolicy7.setHeightForWidth(widget_NormSpectra->sizePolicy().hasHeightForWidth());
        widget_NormSpectra->setSizePolicy(sizePolicy7);
        horizontalLayout_23 = new QHBoxLayout(widget_NormSpectra);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        VLP_norm = new QHBoxLayout();
        VLP_norm->setObjectName(QStringLiteral("VLP_norm"));

        horizontalLayout_23->addLayout(VLP_norm);


        verticalLayout_15->addWidget(widget_NormSpectra);


        verticalLayout_6->addLayout(verticalLayout_15);


        horizontalLayout_3->addLayout(verticalLayout_6);

        horizontalSpacer_14 = new QSpacerItem(2, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_14);

        line_pred = new QFrame(MeasResults);
        line_pred->setObjectName(QStringLiteral("line_pred"));
        line_pred->setFrameShape(QFrame::VLine);
        line_pred->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_pred);

        horizontalSpacer_31 = new QSpacerItem(2, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_31);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_prediction = new QLabel(MeasResults);
        label_prediction->setObjectName(QStringLiteral("label_prediction"));
        label_prediction->setMinimumSize(QSize(0, 14));
        QPalette palette17;
        palette17.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette17.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette17.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_prediction->setPalette(palette17);
        label_prediction->setFont(font11);
        label_prediction->setCursor(QCursor(Qt::ArrowCursor));
        label_prediction->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_prediction);

        widget_errorBar = new QWidget(MeasResults);
        widget_errorBar->setObjectName(QStringLiteral("widget_errorBar"));
        sizePolicy.setHeightForWidth(widget_errorBar->sizePolicy().hasHeightForWidth());
        widget_errorBar->setSizePolicy(sizePolicy);
        horizontalLayout_27 = new QHBoxLayout(widget_errorBar);
        horizontalLayout_27->setObjectName(QStringLiteral("horizontalLayout_27"));
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QStringLiteral("horizontalLayout_26"));
        label_PredictionError = new QLabel(widget_errorBar);
        label_PredictionError->setObjectName(QStringLiteral("label_PredictionError"));
        label_PredictionError->setMinimumSize(QSize(60, 0));
        label_PredictionError->setFont(font2);

        horizontalLayout_26->addWidget(label_PredictionError);

        label_PError = new QLabel(widget_errorBar);
        label_PError->setObjectName(QStringLiteral("label_PError"));
        sizePolicy6.setHeightForWidth(label_PError->sizePolicy().hasHeightForWidth());
        label_PError->setSizePolicy(sizePolicy6);
        label_PError->setMinimumSize(QSize(100, 0));

        horizontalLayout_26->addWidget(label_PError);

        label_R2_1 = new QLabel(widget_errorBar);
        label_R2_1->setObjectName(QStringLiteral("label_R2_1"));
        label_R2_1->setMinimumSize(QSize(60, 0));
        label_R2_1->setFont(font2);

        horizontalLayout_26->addWidget(label_R2_1);

        label_R2 = new QLabel(widget_errorBar);
        label_R2->setObjectName(QStringLiteral("label_R2"));
        sizePolicy6.setHeightForWidth(label_R2->sizePolicy().hasHeightForWidth());
        label_R2->setSizePolicy(sizePolicy6);
        label_R2->setMinimumSize(QSize(100, 0));

        horizontalLayout_26->addWidget(label_R2);


        horizontalLayout_27->addLayout(horizontalLayout_26);


        verticalLayout_5->addWidget(widget_errorBar);

        qwtPlot_Pol_Prediction = new Plot(MeasResults);
        qwtPlot_Pol_Prediction->setObjectName(QStringLiteral("qwtPlot_Pol_Prediction"));
        qwtPlot_Pol_Prediction->setEnabled(true);
        sizePolicy7.setHeightForWidth(qwtPlot_Pol_Prediction->sizePolicy().hasHeightForWidth());
        qwtPlot_Pol_Prediction->setSizePolicy(sizePolicy7);
        qwtPlot_Pol_Prediction->setMinimumSize(QSize(0, 0));
        qwtPlot_Pol_Prediction->setFrameShape(QFrame::StyledPanel);
        qwtPlot_Pol_Prediction->setFrameShadow(QFrame::Raised);

        verticalLayout_5->addWidget(qwtPlot_Pol_Prediction);


        horizontalLayout_3->addLayout(verticalLayout_5);

        horizontalSpacer_7 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        horizontalSpacer_34 = new QSpacerItem(5, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_34);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QStringLiteral("horizontalLayout_24"));
        label_hideNSpectra = new ClickableLabel(MeasResults);
        label_hideNSpectra->setObjectName(QStringLiteral("label_hideNSpectra"));
        label_hideNSpectra->setMinimumSize(QSize(100, 0));
        label_hideNSpectra->setFont(font10);
        label_hideNSpectra->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_24->addWidget(label_hideNSpectra);

        label_NSP = new QLabel(MeasResults);
        label_NSP->setObjectName(QStringLiteral("label_NSP"));
        sizePolicy6.setHeightForWidth(label_NSP->sizePolicy().hasHeightForWidth());
        label_NSP->setSizePolicy(sizePolicy6);

        horizontalLayout_24->addWidget(label_NSP);


        horizontalLayout_21->addLayout(horizontalLayout_24);

        horizontalSpacer_36 = new QSpacerItem(2, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_36);

        line_6 = new QFrame(MeasResults);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout_21->addWidget(line_6);

        horizontalSpacer_35 = new QSpacerItem(2, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_35);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QStringLiteral("horizontalLayout_25"));
        label_P1 = new QLabel(MeasResults);
        label_P1->setObjectName(QStringLiteral("label_P1"));
        label_P1->setMinimumSize(QSize(100, 0));

        horizontalLayout_25->addWidget(label_P1);

        label_P2 = new QLabel(MeasResults);
        label_P2->setObjectName(QStringLiteral("label_P2"));
        sizePolicy6.setHeightForWidth(label_P2->sizePolicy().hasHeightForWidth());
        label_P2->setSizePolicy(sizePolicy6);

        horizontalLayout_25->addWidget(label_P2);


        horizontalLayout_21->addLayout(horizontalLayout_25);

        horizontalSpacer_33 = new QSpacerItem(5, 7, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_33);


        verticalLayout_4->addLayout(horizontalLayout_21);

        QIcon icon4;
        icon4.addFile(QStringLiteral(":/polarimeter/Load.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Tabs_Plots->addTab(MeasResults, icon4, QString());
        MeasStadistics = new QWidget();
        MeasStadistics->setObjectName(QStringLiteral("MeasStadistics"));
        verticalLayout_9 = new QVBoxLayout(MeasStadistics);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        line_8 = new QFrame(MeasStadistics);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);

        verticalLayout_9->addWidget(line_8);

        QIcon icon5;
        icon5.addFile(QStringLiteral(":/polarimeter/PC.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Tabs_Plots->addTab(MeasStadistics, icon5, QString());

        verticalLayout_2->addWidget(Tabs_Plots);


        verticalLayout_7->addLayout(verticalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        button_AnalizeData = new QPushButton(PanelPolarimeter);
        button_AnalizeData->setObjectName(QStringLiteral("button_AnalizeData"));
        button_AnalizeData->setEnabled(true);
        button_AnalizeData->setMinimumSize(QSize(120, 30));
        button_AnalizeData->setMaximumSize(QSize(120, 30));
        button_AnalizeData->setIcon(icon5);
        button_AnalizeData->setIconSize(QSize(20, 20));

        horizontalLayout_5->addWidget(button_AnalizeData);

        button_LoadData = new QPushButton(PanelPolarimeter);
        button_LoadData->setObjectName(QStringLiteral("button_LoadData"));
        button_LoadData->setMinimumSize(QSize(120, 30));
        button_LoadData->setMaximumSize(QSize(120, 30));
        button_LoadData->setIcon(icon4);
        button_LoadData->setIconSize(QSize(20, 20));

        horizontalLayout_5->addWidget(button_LoadData);

        horizontalSpacer_5 = new QSpacerItem(450, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        button_SaveInstantFFT = new QPushButton(PanelPolarimeter);
        button_SaveInstantFFT->setObjectName(QStringLiteral("button_SaveInstantFFT"));
        button_SaveInstantFFT->setEnabled(true);
        button_SaveInstantFFT->setMinimumSize(QSize(120, 30));
        button_SaveInstantFFT->setMaximumSize(QSize(120, 30));
        button_SaveInstantFFT->setIcon(icon4);
        button_SaveInstantFFT->setIconSize(QSize(20, 20));

        horizontalLayout_5->addWidget(button_SaveInstantFFT);

        Button_Save_Graphs_Pol = new QPushButton(PanelPolarimeter);
        Button_Save_Graphs_Pol->setObjectName(QStringLiteral("Button_Save_Graphs_Pol"));
        Button_Save_Graphs_Pol->setMinimumSize(QSize(120, 30));
        Button_Save_Graphs_Pol->setMaximumSize(QSize(100, 30));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/polarimeter/PDF.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Button_Save_Graphs_Pol->setIcon(icon6);
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
        sizePolicy5.setHeightForWidth(currentProgressBar_Pol->sizePolicy().hasHeightForWidth());
        currentProgressBar_Pol->setSizePolicy(sizePolicy5);
        currentProgressBar_Pol->setMaximumSize(QSize(50, 12));
        currentProgressBar_Pol->setAutoFillBackground(false);
        currentProgressBar_Pol->setValue(0);
        currentProgressBar_Pol->setTextVisible(false);
        currentProgressBar_Pol->setOrientation(Qt::Horizontal);
        currentProgressBar_Pol->setInvertedAppearance(false);

        horizontalLayout_4->addWidget(currentProgressBar_Pol);

        info = new QLabel(PanelPolarimeter);
        info->setObjectName(QStringLiteral("info"));
        sizePolicy5.setHeightForWidth(info->sizePolicy().hasHeightForWidth());
        info->setSizePolicy(sizePolicy5);
        info->setMinimumSize(QSize(200, 0));
        info->setMaximumSize(QSize(16777215, 12));
        QFont font13;
        font13.setPointSize(7);
        font13.setBold(true);
        font13.setItalic(false);
        font13.setUnderline(false);
        font13.setWeight(75);
        info->setFont(font13);
        info->setScaledContents(true);

        horizontalLayout_4->addWidget(info);

        horizontalSpacer_Y = new QSpacerItem(30, 12, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_Y);

        label_totalM = new QLabel(PanelPolarimeter);
        label_totalM->setObjectName(QStringLiteral("label_totalM"));
        sizePolicy5.setHeightForWidth(label_totalM->sizePolicy().hasHeightForWidth());
        label_totalM->setSizePolicy(sizePolicy5);
        label_totalM->setMaximumSize(QSize(16777215, 15));
        QFont font14;
        font14.setPointSize(7);
        font14.setBold(true);
        font14.setWeight(75);
        label_totalM->setFont(font14);

        horizontalLayout_4->addWidget(label_totalM);

        TotalProgressBar_Pol = new QProgressBar(PanelPolarimeter);
        TotalProgressBar_Pol->setObjectName(QStringLiteral("TotalProgressBar_Pol"));
        sizePolicy5.setHeightForWidth(TotalProgressBar_Pol->sizePolicy().hasHeightForWidth());
        TotalProgressBar_Pol->setSizePolicy(sizePolicy5);
        TotalProgressBar_Pol->setMinimumSize(QSize(140, 0));
        TotalProgressBar_Pol->setMaximumSize(QSize(240, 12));
        TotalProgressBar_Pol->setFont(font14);
        TotalProgressBar_Pol->setValue(0);

        horizontalLayout_4->addWidget(TotalProgressBar_Pol);

        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        label_remaining = new QLabel(PanelPolarimeter);
        label_remaining->setObjectName(QStringLiteral("label_remaining"));
        label_remaining->setMinimumSize(QSize(82, 0));
        label_remaining->setMaximumSize(QSize(82, 16777215));
        label_remaining->setFont(font14);

        horizontalLayout_4->addWidget(label_remaining);

        label_RemainingTime = new QLabel(PanelPolarimeter);
        label_RemainingTime->setObjectName(QStringLiteral("label_RemainingTime"));
        label_RemainingTime->setMaximumSize(QSize(100, 12));
        label_RemainingTime->setSizeIncrement(QSize(100, 0));
        label_RemainingTime->setFont(font14);

        horizontalLayout_4->addWidget(label_RemainingTime);

        horizontalSpacer_8 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        label_clearAll = new ClickableLabel(PanelPolarimeter);
        label_clearAll->setObjectName(QStringLiteral("label_clearAll"));
        sizePolicy5.setHeightForWidth(label_clearAll->sizePolicy().hasHeightForWidth());
        label_clearAll->setSizePolicy(sizePolicy5);
        label_clearAll->setMinimumSize(QSize(70, 18));
        label_clearAll->setMaximumSize(QSize(70, 18));
        QFont font15;
        font15.setPointSize(8);
        font15.setUnderline(true);
        label_clearAll->setFont(font15);
        label_clearAll->setCursor(QCursor(Qt::PointingHandCursor));
        label_clearAll->setLayoutDirection(Qt::LeftToRight);
        label_clearAll->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_clearAll);

        help = new QPushButton(PanelPolarimeter);
        help->setObjectName(QStringLiteral("help"));
        sizePolicy5.setHeightForWidth(help->sizePolicy().hasHeightForWidth());
        help->setSizePolicy(sizePolicy5);
        help->setMinimumSize(QSize(18, 16));
        help->setMaximumSize(QSize(18, 16));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/polarimeter/Help.ico"), QSize(), QIcon::Normal, QIcon::Off);
        help->setIcon(icon7);
        help->setIconSize(QSize(20, 20));

        horizontalLayout_4->addWidget(help);

        horizontalSpacer_4 = new QSpacerItem(10, 18, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_7->addLayout(verticalLayout);


        horizonalLayout_2->addLayout(verticalLayout_7);


        gridLayout->addLayout(horizonalLayout_2, 0, 0, 1, 1);


        retranslateUi(PanelPolarimeter);

        list_devices_Pol->setCurrentRow(-1);
        Tabs_Plots->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(PanelPolarimeter);
    } // setupUi

    void retranslateUi(QWidget *PanelPolarimeter)
    {
        PanelPolarimeter->setWindowTitle(QApplication::translate("PanelPolarimeter", "Form", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_hideConf->setToolTip(QApplication::translate("PanelPolarimeter", "Hide Lateral Panel", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_hideConf->setText(QApplication::translate("PanelPolarimeter", "<< Hide Panel", Q_NULLPTR));
        label_Set_Spec_Pol->setText(QApplication::translate("PanelPolarimeter", "Spectrometer:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        list_devices_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Spectrometer Settings", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_temp1->setToolTip(QApplication::translate("PanelPolarimeter", "Actual setup temperature", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_temp1->setText(QApplication::translate("PanelPolarimeter", "Setup Temperature:", Q_NULLPTR));
        label_Temperature->setText(QApplication::translate("PanelPolarimeter", "- \302\260C", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        Pol_Thermo->setToolTip(QApplication::translate("PanelPolarimeter", "Setup temperature in \302\260C", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_hum1->setToolTip(QApplication::translate("PanelPolarimeter", "Actual setup humidity", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_hum1->setText(QApplication::translate("PanelPolarimeter", "Setup Humidity:", Q_NULLPTR));
        label_hum->setText(QApplication::translate("PanelPolarimeter", "- %", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_Measurements_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Measurement Profile", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_Measurements_Pol->setText(QApplication::translate("PanelPolarimeter", "Measurement Information:", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = Table_Measurements_Pol->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PanelPolarimeter", "Nr.", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem->setToolTip(QApplication::translate("PanelPolarimeter", "Measurement Number", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem1 = Table_Measurements_Pol->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PanelPolarimeter", "Time ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem1->setToolTip(QApplication::translate("PanelPolarimeter", "Time Intervals", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem2 = Table_Measurements_Pol->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PanelPolarimeter", "C1 (mg/dl)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem2->setToolTip(QApplication::translate("PanelPolarimeter", "Glucose", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem3 = Table_Measurements_Pol->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("PanelPolarimeter", "C2 (mg/dl)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem3->setToolTip(QApplication::translate("PanelPolarimeter", "C2", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem4 = Table_Measurements_Pol->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("PanelPolarimeter", "C3 (mg/dl)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem4->setToolTip(QApplication::translate("PanelPolarimeter", "C3", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem5 = Table_Measurements_Pol->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("PanelPolarimeter", "C4 (mg/dl)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem5->setToolTip(QApplication::translate("PanelPolarimeter", "C4", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem6 = Table_Measurements_Pol->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("PanelPolarimeter", "C5 (mg/dl)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem6->setToolTip(QApplication::translate("PanelPolarimeter", "C5", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        QTableWidgetItem *___qtablewidgetitem7 = Table_Measurements_Pol->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("PanelPolarimeter", "C6 (mg/dl)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        ___qtablewidgetitem7->setToolTip(QApplication::translate("PanelPolarimeter", "C6", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        Table_Measurements_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Measurement Profile", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_S1->setText(QApplication::translate("PanelPolarimeter", "C1 - Glucose", Q_NULLPTR));
        label_S2->setText(QApplication::translate("PanelPolarimeter", "C2 - Impurity 1", Q_NULLPTR));
        label_S3->setText(QApplication::translate("PanelPolarimeter", "C3 - Impurity 2", Q_NULLPTR));
        label_S4->setText(QApplication::translate("PanelPolarimeter", "C4 - Impurity 3", Q_NULLPTR));
        label_S5->setText(QApplication::translate("PanelPolarimeter", "C5 - Impurity 4", Q_NULLPTR));
        label_S6->setText(QApplication::translate("PanelPolarimeter", "C6 - Impurity 5", Q_NULLPTR));
        label_5_Pol_settings->setText(QApplication::translate("PanelPolarimeter", "Measurement Settings:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_Pol_ConfigureMeasurement->setToolTip(QApplication::translate("PanelPolarimeter", "Configure Measurements", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_Pol_ConfigureMeasurement->setText(QApplication::translate("PanelPolarimeter", " Configure", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_calibrate->setToolTip(QApplication::translate("PanelPolarimeter", "Start Calibration", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_calibrate->setText(QApplication::translate("PanelPolarimeter", " Calibrate", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_Start_Meas_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Start Measurements", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_Start_Meas_Pol->setText(QApplication::translate("PanelPolarimeter", " Start Measurement", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        Tabs_Plots->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_hideLiveRaw->setToolTip(QApplication::translate("PanelPolarimeter", "Hide live Raw Signal", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_hideLiveRaw->setText(QApplication::translate("PanelPolarimeter", "<< Hide Live Raw Signal", Q_NULLPTR));
        label_RS->setText(QString());
        label_Rat->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_HideRatio->setToolTip(QApplication::translate("PanelPolarimeter", "Hide Ratio", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_HideRatio->setText(QApplication::translate("PanelPolarimeter", ">> Hide Ratio I(\317\211)/I(2\317\211)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_raw->setToolTip(QApplication::translate("PanelPolarimeter", "Raw Signal Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_raw->setText(QApplication::translate("PanelPolarimeter", "Live Raw Signal", Q_NULLPTR));
        label_PlotSaturated->setText(QApplication::translate("PanelPolarimeter", "Saturated!", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol->setToolTip(QApplication::translate("PanelPolarimeter", "Raw Signal Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_compensation->setToolTip(QApplication::translate("PanelPolarimeter", "Compensation Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_compensation->setText(QApplication::translate("PanelPolarimeter", "Ratio I(\317\211)/I(2\317\211)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol_Compensation->setToolTip(QApplication::translate("PanelPolarimeter", "Compensation Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_fftprofile->setToolTip(QApplication::translate("PanelPolarimeter", "FFT Profile Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_fftprofile->setText(QApplication::translate("PanelPolarimeter", "FFT Profile", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol_w_2w->setToolTip(QApplication::translate("PanelPolarimeter", "FFT Profile Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_average->setToolTip(QApplication::translate("PanelPolarimeter", "Average Signal Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_average->setText(QApplication::translate("PanelPolarimeter", "Live Average Signal", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol_Average->setToolTip(QApplication::translate("PanelPolarimeter", "Average Signal Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_HideFFTProfile->setToolTip(QApplication::translate("PanelPolarimeter", "Hide FFT Profile", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_HideFFTProfile->setText(QApplication::translate("PanelPolarimeter", "<< Hide FFT Profile", Q_NULLPTR));
        label_HProf->setText(QString());
        label_HAver->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_HIdeLiveAverage->setToolTip(QApplication::translate("PanelPolarimeter", "Hide Live Average Signal", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_HIdeLiveAverage->setText(QApplication::translate("PanelPolarimeter", ">> Hide Live Average", Q_NULLPTR));
        Tabs_Plots->setTabText(Tabs_Plots->indexOf(liveData), QApplication::translate("PanelPolarimeter", "Live Data", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_TemperaturePlot->setToolTip(QApplication::translate("PanelPolarimeter", "Temperature plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_TemperaturePlot->setText(QApplication::translate("PanelPolarimeter", "Setup Temperature", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_NoComTeensy->setToolTip(QApplication::translate("PanelPolarimeter", "Connection with Teensy failed!", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_NoComTeensy->setText(QApplication::translate("PanelPolarimeter", "Check Connection with Teensy", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol_Temperature->setToolTip(QApplication::translate("PanelPolarimeter", "Live setup temperature", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        waveToPlotFFT->setToolTip(QApplication::translate("PanelPolarimeter", "Change FFT wavelength", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        waveToPlotFFT->setText(QApplication::translate("PanelPolarimeter", "FFT Intensity at - nm", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol_FFT->setToolTip(QApplication::translate("PanelPolarimeter", "FFT Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        Tabs_Plots->setTabText(Tabs_Plots->indexOf(tab), QApplication::translate("PanelPolarimeter", "Setup Status", Q_NULLPTR));
        label_hideSpectra->setText(QApplication::translate("PanelPolarimeter", "<< Hide Spectra", Q_NULLPTR));
        label_SP->setText(QString());
        label_PSNS->setText(QString());
        label_hidePrediction->setText(QApplication::translate("PanelPolarimeter", ">> Hide Prediction", Q_NULLPTR));
        label_spectra->setText(QApplication::translate("PanelPolarimeter", "Spectra", Q_NULLPTR));
        label_Nspectra->setText(QApplication::translate("PanelPolarimeter", "Normalized Spectra", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_prediction->setToolTip(QApplication::translate("PanelPolarimeter", "Hide/Show Prediction Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_prediction->setText(QApplication::translate("PanelPolarimeter", "Prediction", Q_NULLPTR));
        label_PredictionError->setText(QApplication::translate("PanelPolarimeter", "SEP:", Q_NULLPTR));
        label_PError->setText(QString());
        label_R2_1->setText(QApplication::translate("PanelPolarimeter", "R^2:", Q_NULLPTR));
        label_R2->setText(QString());
#ifndef QT_NO_TOOLTIP
        qwtPlot_Pol_Prediction->setToolTip(QApplication::translate("PanelPolarimeter", "Prediction Plot", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_hideNSpectra->setText(QApplication::translate("PanelPolarimeter", "<< Hide Normalized Spectra", Q_NULLPTR));
        label_NSP->setText(QString());
        label_P1->setText(QString());
        label_P2->setText(QString());
        Tabs_Plots->setTabText(Tabs_Plots->indexOf(MeasResults), QApplication::translate("PanelPolarimeter", "Measurement Results", Q_NULLPTR));
        Tabs_Plots->setTabText(Tabs_Plots->indexOf(MeasStadistics), QApplication::translate("PanelPolarimeter", "Measurement Stadistics", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_AnalizeData->setToolTip(QApplication::translate("PanelPolarimeter", "Analize Data", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_AnalizeData->setText(QApplication::translate("PanelPolarimeter", "Analize Data", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_LoadData->setToolTip(QApplication::translate("PanelPolarimeter", "Load Data from Files", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_LoadData->setText(QApplication::translate("PanelPolarimeter", " Load Data", Q_NULLPTR));
        button_SaveInstantFFT->setText(QApplication::translate("PanelPolarimeter", "Save Spectra", Q_NULLPTR));
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
