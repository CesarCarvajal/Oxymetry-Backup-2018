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
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
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
    QFrame *line_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radiobutton_selectData;
    QWidget *SelectFiles;
    QVBoxLayout *verticalLayout_fileconf;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QListWidget *listWidget_2;
    QSpacerItem *horizontalSpacer_4;
    ClickableLabel *label_restart;
    QFrame *line_6;
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
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_cancel;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_select;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_generate;

    void setupUi(QDialog *selectAnalizeData)
    {
        if (selectAnalizeData->objectName().isEmpty())
            selectAnalizeData->setObjectName(QStringLiteral("selectAnalizeData"));
        selectAnalizeData->resize(573, 487);
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

        line_2 = new QFrame(selectAnalizeData);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        radiobutton_selectData = new QRadioButton(selectAnalizeData);
        radiobutton_selectData->setObjectName(QStringLiteral("radiobutton_selectData"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
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
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(SelectFiles->sizePolicy().hasHeightForWidth());
        SelectFiles->setSizePolicy(sizePolicy1);
        SelectFiles->setMinimumSize(QSize(0, 0));
        verticalLayout_fileconf = new QVBoxLayout(SelectFiles);
        verticalLayout_fileconf->setObjectName(QStringLiteral("verticalLayout_fileconf"));
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

        listWidget = new QListWidget(SelectFiles);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout_3->addWidget(listWidget);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_2 = new QLabel(SelectFiles);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        verticalLayout_8->addWidget(label_2);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_2);

        listWidget_2 = new QListWidget(SelectFiles);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setEnabled(true);

        verticalLayout_8->addWidget(listWidget_2);


        gridLayout_2->addLayout(verticalLayout_8, 0, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 0, 1, 1, 1);


        verticalLayout_fileconf->addLayout(gridLayout_2);

        label_restart = new ClickableLabel(SelectFiles);
        label_restart->setObjectName(QStringLiteral("label_restart"));
        QFont font2;
        font2.setPointSize(7);
        label_restart->setFont(font2);
        label_restart->setCursor(QCursor(Qt::PointingHandCursor));
        label_restart->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_fileconf->addWidget(label_restart);


        verticalLayout->addWidget(SelectFiles);

        line_6 = new QFrame(selectAnalizeData);
        line_6->setObjectName(QStringLiteral("line_6"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line_6->sizePolicy().hasHeightForWidth());
        line_6->setSizePolicy(sizePolicy2);
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_6);

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

        verticalSpacer_4 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        pushButton_cancel = new QPushButton(selectAnalizeData);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        sizePolicy2.setHeightForWidth(pushButton_cancel->sizePolicy().hasHeightForWidth());
        pushButton_cancel->setSizePolicy(sizePolicy2);
        pushButton_cancel->setMinimumSize(QSize(150, 30));
        pushButton_cancel->setAutoDefault(false);

        horizontalLayout_9->addWidget(pushButton_cancel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);

        horizontalSpacer_8 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);

        pushButton_select = new QPushButton(selectAnalizeData);
        pushButton_select->setObjectName(QStringLiteral("pushButton_select"));
        sizePolicy2.setHeightForWidth(pushButton_select->sizePolicy().hasHeightForWidth());
        pushButton_select->setSizePolicy(sizePolicy2);
        pushButton_select->setMinimumSize(QSize(150, 30));
        pushButton_select->setMaximumSize(QSize(16777215, 30));
        pushButton_select->setAutoDefault(false);

        horizontalLayout_9->addWidget(pushButton_select);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        pushButton_generate = new QPushButton(selectAnalizeData);
        pushButton_generate->setObjectName(QStringLiteral("pushButton_generate"));
        pushButton_generate->setEnabled(true);
        sizePolicy2.setHeightForWidth(pushButton_generate->sizePolicy().hasHeightForWidth());
        pushButton_generate->setSizePolicy(sizePolicy2);
        pushButton_generate->setMinimumSize(QSize(150, 30));
        pushButton_generate->setAutoDefault(false);

        horizontalLayout_9->addWidget(pushButton_generate);


        verticalLayout->addLayout(horizontalLayout_9);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(selectAnalizeData);

        pushButton_select->setDefault(false);


        QMetaObject::connectSlotsByName(selectAnalizeData);
    } // setupUi

    void retranslateUi(QDialog *selectAnalizeData)
    {
        selectAnalizeData->setWindowTitle(QApplication::translate("selectAnalizeData", "Data Analizer", Q_NULLPTR));
        label_18->setText(QApplication::translate("selectAnalizeData", "Data Analysis", Q_NULLPTR));
        radiobutton_selectData->setText(QApplication::translate("selectAnalizeData", "Select Calibration and Validation Data:", Q_NULLPTR));
        label->setText(QApplication::translate("selectAnalizeData", "Calibration Data:", Q_NULLPTR));
        label_2->setText(QApplication::translate("selectAnalizeData", "Validation Data:", Q_NULLPTR));
        label_restart->setText(QApplication::translate("selectAnalizeData", "Restart", Q_NULLPTR));
        radiobutton_selectSet->setText(QApplication::translate("selectAnalizeData", "Select a Set of Data or Repetition as Calibration and Validation", Q_NULLPTR));
        label_3->setText(QApplication::translate("selectAnalizeData", "Validation Set:", Q_NULLPTR));
        label_4->setText(QApplication::translate("selectAnalizeData", "Calibration Set:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_cancel->setToolTip(QApplication::translate("selectAnalizeData", "Cancel Data Analysis", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_cancel->setText(QApplication::translate("selectAnalizeData", "Cancel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_select->setToolTip(QApplication::translate("selectAnalizeData", "Load a Configuration File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_select->setText(QApplication::translate("selectAnalizeData", "Load Data", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_generate->setToolTip(QApplication::translate("selectAnalizeData", "Generate Configuration File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_generate->setText(QApplication::translate("selectAnalizeData", "Analize", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class selectAnalizeData: public Ui_selectAnalizeData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_ANALIZEDATA_H
