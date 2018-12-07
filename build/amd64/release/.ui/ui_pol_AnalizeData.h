/********************************************************************************
** Form generated from reading UI file 'pol_AnalizeData.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POL_ANALIZEDATA_H
#define UI_POL_ANALIZEDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_selectAnalizeData
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_18;
    QSpacerItem *verticalSpacer_3;
    QFrame *line;
    QLabel *label_5;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radiobutton_selectData;
    QWidget *SelectFiles;
    QVBoxLayout *verticalLayout_fileconf;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox_stepsSelec;
    QSpinBox *spinBox_stepsSelec;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_repselec;
    QSpinBox *spinBox_repselec;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox_SelecManual;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_8;
    QCheckBox *checkBox_RandomSort;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer_6;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QListWidget *listWidget_Calibration;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QListWidget *listWidget_Validation;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_11;
    ClickableLabel *label_switch;
    ClickableLabel *label_restart;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QRadioButton *radiobutton_selectSet;
    QWidget *SelectSet;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QSpinBox *spinBox_ValSet;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpinBox *spinBox_calSet;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_currentPath;
    QLineEdit *lineEdit_currentDataPath;
    QSpacerItem *verticalSpacer_5;
    QFrame *line_3;
    QLabel *label_6;
    QFrame *line_4;
    QWidget *PLS;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_17;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_maxWavel;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_detsignal;
    QComboBox *comboBox_DetSignal;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *horizontalSpacer_20;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBox_minWavel;
    QSpacerItem *horizontalSpacer_19;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_subs;
    QComboBox *comboBox_Substance;
    QSpacerItem *horizontalSpacer_16;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_applyLogarithm;
    QCheckBox *checkBox_applyLogarithm;
    QSpacerItem *horizontalSpacer_22;
    QSpacerItem *horizontalSpacer_21;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_9;
    QSpinBox *spinBox_PLSComponents;
    QSpacerItem *horizontalSpacer_23;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_select;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_Analize;

    void setupUi(QDialog *selectAnalizeData)
    {
        if (selectAnalizeData->objectName().isEmpty())
            selectAnalizeData->setObjectName(QStringLiteral("selectAnalizeData"));
        selectAnalizeData->resize(782, 761);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(selectAnalizeData->sizePolicy().hasHeightForWidth());
        selectAnalizeData->setSizePolicy(sizePolicy);
        selectAnalizeData->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(selectAnalizeData);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label_18 = new QLabel(selectAnalizeData);
        label_18->setObjectName(QStringLiteral("label_18"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_18->setFont(font);
        label_18->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_18);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        line = new QFrame(selectAnalizeData);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label_5 = new QLabel(selectAnalizeData);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_5->setFont(font1);

        verticalLayout->addWidget(label_5);

        line_2 = new QFrame(selectAnalizeData);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        radiobutton_selectData = new QRadioButton(selectAnalizeData);
        radiobutton_selectData->setObjectName(QStringLiteral("radiobutton_selectData"));
        radiobutton_selectData->setFont(font1);
        radiobutton_selectData->setAutoFillBackground(false);
        radiobutton_selectData->setInputMethodHints(Qt::ImhNone);
        radiobutton_selectData->setChecked(true);
        radiobutton_selectData->setAutoExclusive(true);

        horizontalLayout_2->addWidget(radiobutton_selectData);


        verticalLayout->addLayout(horizontalLayout_2);

        SelectFiles = new QWidget(selectAnalizeData);
        SelectFiles->setObjectName(QStringLiteral("SelectFiles"));
        SelectFiles->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(SelectFiles->sizePolicy().hasHeightForWidth());
        SelectFiles->setSizePolicy(sizePolicy1);
        SelectFiles->setMinimumSize(QSize(0, 0));
        verticalLayout_fileconf = new QVBoxLayout(SelectFiles);
        verticalLayout_fileconf->setObjectName(QStringLiteral("verticalLayout_fileconf"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        checkBox_stepsSelec = new QCheckBox(SelectFiles);
        checkBox_stepsSelec->setObjectName(QStringLiteral("checkBox_stepsSelec"));
        checkBox_stepsSelec->setMinimumSize(QSize(90, 0));
        checkBox_stepsSelec->setMaximumSize(QSize(90, 16777215));
        checkBox_stepsSelec->setChecked(false);

        horizontalLayout_10->addWidget(checkBox_stepsSelec);

        spinBox_stepsSelec = new QSpinBox(SelectFiles);
        spinBox_stepsSelec->setObjectName(QStringLiteral("spinBox_stepsSelec"));
        spinBox_stepsSelec->setEnabled(false);
        spinBox_stepsSelec->setMinimumSize(QSize(60, 0));
        spinBox_stepsSelec->setMaximumSize(QSize(60, 16777215));
        spinBox_stepsSelec->setMinimum(2);
        spinBox_stepsSelec->setMaximum(10000000);

        horizontalLayout_10->addWidget(spinBox_stepsSelec);

        horizontalSpacer_12 = new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_12);


        gridLayout_3->addLayout(horizontalLayout_10, 0, 2, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_repselec = new QLabel(SelectFiles);
        label_repselec->setObjectName(QStringLiteral("label_repselec"));
        label_repselec->setMinimumSize(QSize(90, 0));
        label_repselec->setMaximumSize(QSize(90, 16777215));

        horizontalLayout_5->addWidget(label_repselec);

        spinBox_repselec = new QSpinBox(SelectFiles);
        spinBox_repselec->setObjectName(QStringLiteral("spinBox_repselec"));
        spinBox_repselec->setMinimumSize(QSize(60, 0));
        spinBox_repselec->setMaximumSize(QSize(60, 16777215));
        spinBox_repselec->setMinimum(1);
        spinBox_repselec->setMaximum(1000);
        spinBox_repselec->setValue(1);

        horizontalLayout_5->addWidget(spinBox_repselec);

        horizontalSpacer_10 = new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);


        gridLayout_3->addLayout(horizontalLayout_5, 0, 6, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        checkBox_SelecManual = new QCheckBox(SelectFiles);
        checkBox_SelecManual->setObjectName(QStringLiteral("checkBox_SelecManual"));
        checkBox_SelecManual->setMinimumSize(QSize(150, 0));
        checkBox_SelecManual->setMaximumSize(QSize(150, 16777215));
        checkBox_SelecManual->setChecked(true);

        horizontalLayout_4->addWidget(checkBox_SelecManual);

        horizontalSpacer_13 = new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_13);


        gridLayout_3->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        checkBox_RandomSort = new QCheckBox(SelectFiles);
        checkBox_RandomSort->setObjectName(QStringLiteral("checkBox_RandomSort"));
        checkBox_RandomSort->setMinimumSize(QSize(150, 0));
        checkBox_RandomSort->setMaximumSize(QSize(150, 16777215));

        horizontalLayout_8->addWidget(checkBox_RandomSort);

        horizontalSpacer_11 = new QSpacerItem(20, 1, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_11);


        gridLayout_3->addLayout(horizontalLayout_8, 0, 5, 1, 1);


        verticalLayout_fileconf->addLayout(gridLayout_3);

        verticalSpacer_6 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_fileconf->addItem(verticalSpacer_6);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(SelectFiles);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        verticalLayout_3->addWidget(label);

        verticalSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        listWidget_Calibration = new QListWidget(SelectFiles);
        listWidget_Calibration->setObjectName(QStringLiteral("listWidget_Calibration"));
        listWidget_Calibration->setMinimumSize(QSize(0, 150));
        listWidget_Calibration->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        listWidget_Calibration->setContextMenuPolicy(Qt::CustomContextMenu);
        listWidget_Calibration->setFrameShape(QFrame::StyledPanel);
        listWidget_Calibration->setFrameShadow(QFrame::Sunken);
        listWidget_Calibration->setLineWidth(1);
        listWidget_Calibration->setMidLineWidth(0);
        listWidget_Calibration->setAutoScrollMargin(25);
        listWidget_Calibration->setEditTriggers(QAbstractItemView::SelectedClicked);
        listWidget_Calibration->setDragEnabled(false);
        listWidget_Calibration->setDefaultDropAction(Qt::MoveAction);
        listWidget_Calibration->setTextElideMode(Qt::ElideRight);
        listWidget_Calibration->setMovement(QListView::Static);
        listWidget_Calibration->setResizeMode(QListView::Fixed);
        listWidget_Calibration->setSpacing(2);
        listWidget_Calibration->setModelColumn(0);
        listWidget_Calibration->setUniformItemSizes(true);
        listWidget_Calibration->setSelectionRectVisible(true);

        verticalLayout_3->addWidget(listWidget_Calibration);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_2 = new QLabel(SelectFiles);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        verticalLayout_8->addWidget(label_2);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_2);

        listWidget_Validation = new QListWidget(SelectFiles);
        listWidget_Validation->setObjectName(QStringLiteral("listWidget_Validation"));
        listWidget_Validation->setEnabled(true);
        listWidget_Validation->setMinimumSize(QSize(0, 150));
        listWidget_Validation->viewport()->setProperty("cursor", QVariant(QCursor(Qt::PointingHandCursor)));
        listWidget_Validation->setAutoScrollMargin(25);
        listWidget_Validation->setEditTriggers(QAbstractItemView::SelectedClicked);
        listWidget_Validation->setDefaultDropAction(Qt::MoveAction);
        listWidget_Validation->setFlow(QListView::TopToBottom);
        listWidget_Validation->setSpacing(2);
        listWidget_Validation->setGridSize(QSize(0, 20));
        listWidget_Validation->setViewMode(QListView::ListMode);
        listWidget_Validation->setModelColumn(0);
        listWidget_Validation->setUniformItemSizes(true);
        listWidget_Validation->setSelectionRectVisible(true);

        verticalLayout_8->addWidget(listWidget_Validation);


        gridLayout_2->addLayout(verticalLayout_8, 0, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 1, 1, 1);


        verticalLayout_fileconf->addLayout(gridLayout_2);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_switch = new ClickableLabel(SelectFiles);
        label_switch->setObjectName(QStringLiteral("label_switch"));
        QFont font2;
        font2.setPointSize(7);
        label_switch->setFont(font2);
        label_switch->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_11->addWidget(label_switch);

        label_restart = new ClickableLabel(SelectFiles);
        label_restart->setObjectName(QStringLiteral("label_restart"));
        label_restart->setFont(font2);
        label_restart->setCursor(QCursor(Qt::PointingHandCursor));
        label_restart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_restart);


        verticalLayout_fileconf->addLayout(horizontalLayout_11);


        verticalLayout->addWidget(SelectFiles);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        radiobutton_selectSet = new QRadioButton(selectAnalizeData);
        radiobutton_selectSet->setObjectName(QStringLiteral("radiobutton_selectSet"));
        radiobutton_selectSet->setFont(font1);

        horizontalLayout_3->addWidget(radiobutton_selectSet);


        verticalLayout->addLayout(horizontalLayout_3);

        SelectSet = new QWidget(selectAnalizeData);
        SelectSet->setObjectName(QStringLiteral("SelectSet"));
        SelectSet->setEnabled(false);
        verticalLayout_6 = new QVBoxLayout(SelectSet);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_3 = new QLabel(SelectSet);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(100, 0));

        horizontalLayout_7->addWidget(label_3);

        spinBox_ValSet = new QSpinBox(SelectSet);
        spinBox_ValSet->setObjectName(QStringLiteral("spinBox_ValSet"));
        spinBox_ValSet->setMinimumSize(QSize(100, 0));
        spinBox_ValSet->setMaximumSize(QSize(100, 16777215));
        spinBox_ValSet->setMinimum(1);
        spinBox_ValSet->setMaximum(1000000);
        spinBox_ValSet->setValue(1);

        horizontalLayout_7->addWidget(spinBox_ValSet);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);


        gridLayout_7->addLayout(horizontalLayout_7, 0, 3, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(SelectSet);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(100, 0));

        horizontalLayout_6->addWidget(label_4);

        spinBox_calSet = new QSpinBox(SelectSet);
        spinBox_calSet->setObjectName(QStringLiteral("spinBox_calSet"));
        spinBox_calSet->setMinimumSize(QSize(100, 0));
        spinBox_calSet->setMaximumSize(QSize(100, 16777215));
        spinBox_calSet->setMinimum(1);
        spinBox_calSet->setMaximum(10000000);
        spinBox_calSet->setValue(1);

        horizontalLayout_6->addWidget(spinBox_calSet);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);


        gridLayout_7->addLayout(horizontalLayout_6, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_5, 0, 2, 1, 1);


        verticalLayout_6->addLayout(gridLayout_7);


        verticalLayout->addWidget(SelectSet);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_14 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_14);

        label_currentPath = new QLabel(selectAnalizeData);
        label_currentPath->setObjectName(QStringLiteral("label_currentPath"));
        label_currentPath->setMinimumSize(QSize(100, 0));
        label_currentPath->setMaximumSize(QSize(100, 16777215));
        QPalette palette;
        QBrush brush(QColor(0, 85, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_currentPath->setPalette(palette);

        horizontalLayout->addWidget(label_currentPath);

        lineEdit_currentDataPath = new QLineEdit(selectAnalizeData);
        lineEdit_currentDataPath->setObjectName(QStringLiteral("lineEdit_currentDataPath"));
        lineEdit_currentDataPath->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_currentDataPath);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_5 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);

        line_3 = new QFrame(selectAnalizeData);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        label_6 = new QLabel(selectAnalizeData);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);

        verticalLayout->addWidget(label_6);

        line_4 = new QFrame(selectAnalizeData);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        PLS = new QWidget(selectAnalizeData);
        PLS->setObjectName(QStringLiteral("PLS"));
        PLS->setMinimumSize(QSize(0, 110));
        verticalLayout_5 = new QVBoxLayout(PLS);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        horizontalSpacer_17 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_17, 0, 1, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_7 = new QLabel(PLS);
        label_7->setObjectName(QStringLiteral("label_7"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);
        label_7->setMinimumSize(QSize(150, 0));

        horizontalLayout_15->addWidget(label_7);

        doubleSpinBox_maxWavel = new QDoubleSpinBox(PLS);
        doubleSpinBox_maxWavel->setObjectName(QStringLiteral("doubleSpinBox_maxWavel"));
        doubleSpinBox_maxWavel->setMinimumSize(QSize(150, 0));
        doubleSpinBox_maxWavel->setMaximum(1e+24);
        doubleSpinBox_maxWavel->setSingleStep(0.01);
        doubleSpinBox_maxWavel->setValue(1100);

        horizontalLayout_15->addWidget(doubleSpinBox_maxWavel);

        horizontalSpacer_18 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_18);


        gridLayout_4->addLayout(horizontalLayout_15, 1, 2, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_detsignal = new QLabel(PLS);
        label_detsignal->setObjectName(QStringLiteral("label_detsignal"));
        label_detsignal->setMinimumSize(QSize(150, 0));

        horizontalLayout_12->addWidget(label_detsignal);

        comboBox_DetSignal = new QComboBox(PLS);
        comboBox_DetSignal->setObjectName(QStringLiteral("comboBox_DetSignal"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBox_DetSignal->sizePolicy().hasHeightForWidth());
        comboBox_DetSignal->setSizePolicy(sizePolicy3);
        comboBox_DetSignal->setMinimumSize(QSize(150, 0));

        horizontalLayout_12->addWidget(comboBox_DetSignal);

        horizontalSpacer_15 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_15);


        gridLayout_4->addLayout(horizontalLayout_12, 0, 0, 1, 1);

        horizontalSpacer_20 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_20, 1, 1, 1, 1);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_8 = new QLabel(PLS);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(150, 0));

        horizontalLayout_16->addWidget(label_8);

        doubleSpinBox_minWavel = new QDoubleSpinBox(PLS);
        doubleSpinBox_minWavel->setObjectName(QStringLiteral("doubleSpinBox_minWavel"));
        doubleSpinBox_minWavel->setMinimumSize(QSize(150, 0));
        doubleSpinBox_minWavel->setMaximum(1e+13);
        doubleSpinBox_minWavel->setSingleStep(0.01);
        doubleSpinBox_minWavel->setValue(277);

        horizontalLayout_16->addWidget(doubleSpinBox_minWavel);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_19);


        gridLayout_4->addLayout(horizontalLayout_16, 1, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_subs = new QLabel(PLS);
        label_subs->setObjectName(QStringLiteral("label_subs"));
        label_subs->setMinimumSize(QSize(150, 0));

        horizontalLayout_13->addWidget(label_subs);

        comboBox_Substance = new QComboBox(PLS);
        comboBox_Substance->setObjectName(QStringLiteral("comboBox_Substance"));
        sizePolicy3.setHeightForWidth(comboBox_Substance->sizePolicy().hasHeightForWidth());
        comboBox_Substance->setSizePolicy(sizePolicy3);
        comboBox_Substance->setMinimumSize(QSize(150, 0));

        horizontalLayout_13->addWidget(comboBox_Substance);

        horizontalSpacer_16 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_16);


        gridLayout_4->addLayout(horizontalLayout_13, 0, 2, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_applyLogarithm = new QLabel(PLS);
        label_applyLogarithm->setObjectName(QStringLiteral("label_applyLogarithm"));
        label_applyLogarithm->setMinimumSize(QSize(150, 0));

        horizontalLayout_14->addWidget(label_applyLogarithm);

        checkBox_applyLogarithm = new QCheckBox(PLS);
        checkBox_applyLogarithm->setObjectName(QStringLiteral("checkBox_applyLogarithm"));
        checkBox_applyLogarithm->setMinimumSize(QSize(150, 0));
        checkBox_applyLogarithm->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_14->addWidget(checkBox_applyLogarithm);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_22);


        gridLayout_4->addLayout(horizontalLayout_14, 2, 0, 1, 1);

        horizontalSpacer_21 = new QSpacerItem(5, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_21, 2, 1, 1, 1);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_9 = new QLabel(PLS);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(150, 0));

        horizontalLayout_17->addWidget(label_9);

        spinBox_PLSComponents = new QSpinBox(PLS);
        spinBox_PLSComponents->setObjectName(QStringLiteral("spinBox_PLSComponents"));
        spinBox_PLSComponents->setMinimumSize(QSize(150, 0));
        spinBox_PLSComponents->setMinimum(1);
        spinBox_PLSComponents->setMaximum(100000);

        horizontalLayout_17->addWidget(spinBox_PLSComponents);

        horizontalSpacer_23 = new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_23);


        gridLayout_4->addLayout(horizontalLayout_17, 2, 2, 1, 1);


        verticalLayout_5->addLayout(gridLayout_4);


        verticalLayout->addWidget(PLS);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        pushButton_cancel = new QPushButton(selectAnalizeData);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_cancel->sizePolicy().hasHeightForWidth());
        pushButton_cancel->setSizePolicy(sizePolicy4);
        pushButton_cancel->setMinimumSize(QSize(150, 30));
        pushButton_cancel->setAutoDefault(false);

        horizontalLayout_9->addWidget(pushButton_cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        horizontalSpacer_8 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);

        pushButton_select = new QPushButton(selectAnalizeData);
        pushButton_select->setObjectName(QStringLiteral("pushButton_select"));
        sizePolicy4.setHeightForWidth(pushButton_select->sizePolicy().hasHeightForWidth());
        pushButton_select->setSizePolicy(sizePolicy4);
        pushButton_select->setMinimumSize(QSize(150, 30));
        pushButton_select->setMaximumSize(QSize(16777215, 30));
        pushButton_select->setAutoDefault(false);

        horizontalLayout_9->addWidget(pushButton_select);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        pushButton_Analize = new QPushButton(selectAnalizeData);
        pushButton_Analize->setObjectName(QStringLiteral("pushButton_Analize"));
        pushButton_Analize->setEnabled(false);
        sizePolicy4.setHeightForWidth(pushButton_Analize->sizePolicy().hasHeightForWidth());
        pushButton_Analize->setSizePolicy(sizePolicy4);
        pushButton_Analize->setMinimumSize(QSize(150, 30));
        pushButton_Analize->setAutoDefault(false);

        horizontalLayout_9->addWidget(pushButton_Analize);


        verticalLayout->addLayout(horizontalLayout_9);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(selectAnalizeData);

        pushButton_select->setDefault(false);


        QMetaObject::connectSlotsByName(selectAnalizeData);
    } // setupUi

    void retranslateUi(QDialog *selectAnalizeData)
    {
        selectAnalizeData->setWindowTitle(QApplication::translate("selectAnalizeData", "Data Analizer", Q_NULLPTR));
        label_18->setText(QApplication::translate("selectAnalizeData", "PLS Data Analysis", Q_NULLPTR));
        label_5->setText(QApplication::translate("selectAnalizeData", "Data Selection", Q_NULLPTR));
        radiobutton_selectData->setText(QApplication::translate("selectAnalizeData", "Select Calibration and Validation Data:", Q_NULLPTR));
        checkBox_stepsSelec->setText(QApplication::translate("selectAnalizeData", "Sort in Steps:", Q_NULLPTR));
        label_repselec->setText(QApplication::translate("selectAnalizeData", "Select Repetition:", Q_NULLPTR));
        checkBox_SelecManual->setText(QApplication::translate("selectAnalizeData", "Manual", Q_NULLPTR));
        checkBox_RandomSort->setText(QApplication::translate("selectAnalizeData", "Sort Randomly", Q_NULLPTR));
        label->setText(QApplication::translate("selectAnalizeData", "Calibration Data:", Q_NULLPTR));
        label_2->setText(QApplication::translate("selectAnalizeData", "Validation Data:", Q_NULLPTR));
        label_switch->setText(QApplication::translate("selectAnalizeData", "Switch >>", Q_NULLPTR));
        label_restart->setText(QApplication::translate("selectAnalizeData", "Restart", Q_NULLPTR));
        radiobutton_selectSet->setText(QApplication::translate("selectAnalizeData", "Select a Set of Data or Repetition as Calibration and Validation", Q_NULLPTR));
        label_3->setText(QApplication::translate("selectAnalizeData", "Validation Set:", Q_NULLPTR));
        label_4->setText(QApplication::translate("selectAnalizeData", "Calibration Set:", Q_NULLPTR));
        label_currentPath->setText(QApplication::translate("selectAnalizeData", "Current Data Path:", Q_NULLPTR));
        lineEdit_currentDataPath->setText(QApplication::translate("selectAnalizeData", "Please Select a FFT Data Files Path", Q_NULLPTR));
        label_6->setText(QApplication::translate("selectAnalizeData", "PLS Settings", Q_NULLPTR));
        label_7->setText(QApplication::translate("selectAnalizeData", "Maximum Wavelength:", Q_NULLPTR));
        label_detsignal->setText(QApplication::translate("selectAnalizeData", "Determination Signal:", Q_NULLPTR));
        comboBox_DetSignal->clear();
        comboBox_DetSignal->insertItems(0, QStringList()
         << QApplication::translate("selectAnalizeData", "Ratio I(w)/I(2w)", Q_NULLPTR)
         << QApplication::translate("selectAnalizeData", "I(w)", Q_NULLPTR)
         << QApplication::translate("selectAnalizeData", "I(2w)", Q_NULLPTR)
         << QApplication::translate("selectAnalizeData", "I(DC)", Q_NULLPTR)
        );
        label_8->setText(QApplication::translate("selectAnalizeData", "Minimum Wavelength:", Q_NULLPTR));
        label_subs->setText(QApplication::translate("selectAnalizeData", "Substance:", Q_NULLPTR));
        label_applyLogarithm->setText(QApplication::translate("selectAnalizeData", "Apply Logarithm Function:", Q_NULLPTR));
        checkBox_applyLogarithm->setText(QString());
        label_9->setText(QApplication::translate("selectAnalizeData", "Number of PLS Components:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_cancel->setToolTip(QApplication::translate("selectAnalizeData", "Cancel Data Analysis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_cancel->setText(QApplication::translate("selectAnalizeData", "Cancel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_select->setToolTip(QApplication::translate("selectAnalizeData", "Load a Configuration File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_select->setText(QApplication::translate("selectAnalizeData", "Load Data", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_Analize->setToolTip(QApplication::translate("selectAnalizeData", "Generate Configuration File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_Analize->setText(QApplication::translate("selectAnalizeData", "Analize", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class selectAnalizeData: public Ui_selectAnalizeData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_ANALIZEDATA_H
