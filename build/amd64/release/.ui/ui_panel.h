/********************************************************************************
** Form generated from reading UI file 'panel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEL_H
#define UI_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_Panel
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QListWidget *list_devices;
    QSpacerItem *verticalSpacer_6;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_preview;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_storeToRam;
    QPushButton *pushButton_timePattern;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_5;
    Plot *qwtPlot;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_legend;
    QPushButton *pushButton_exportData;
    QPushButton *pushButton_saveGraph;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_about;

    void setupUi(QDialog *Panel)
    {
        if (Panel->objectName().isEmpty())
            Panel->setObjectName(QStringLiteral("Panel"));
        Panel->resize(1200, 800);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Panel->sizePolicy().hasHeightForWidth());
        Panel->setSizePolicy(sizePolicy);
        Panel->setMinimumSize(QSize(1200, 800));
        gridLayout = new QGridLayout(Panel);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(Panel);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setFrameShape(QFrame::NoFrame);
        label->setMidLineWidth(2);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_2->addWidget(label);

        list_devices = new QListWidget(tab);
        list_devices->setObjectName(QStringLiteral("list_devices"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(list_devices->sizePolicy().hasHeightForWidth());
        list_devices->setSizePolicy(sizePolicy2);
        list_devices->setMinimumSize(QSize(230, 540));
        list_devices->setMaximumSize(QSize(230, 16777215));
        list_devices->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        list_devices->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        list_devices->setAutoScroll(false);

        verticalLayout_2->addWidget(list_devices);

        verticalSpacer_6 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_6);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_2->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_preview = new QPushButton(tab);
        pushButton_preview->setObjectName(QStringLiteral("pushButton_preview"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_preview->sizePolicy().hasHeightForWidth());
        pushButton_preview->setSizePolicy(sizePolicy3);
        pushButton_preview->setMinimumSize(QSize(110, 66));
        pushButton_preview->setMaximumSize(QSize(100, 66));

        horizontalLayout->addWidget(pushButton_preview);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButton_storeToRam = new QPushButton(tab);
        pushButton_storeToRam->setObjectName(QStringLiteral("pushButton_storeToRam"));
        pushButton_storeToRam->setEnabled(true);
        sizePolicy3.setHeightForWidth(pushButton_storeToRam->sizePolicy().hasHeightForWidth());
        pushButton_storeToRam->setSizePolicy(sizePolicy3);
        pushButton_storeToRam->setMinimumSize(QSize(110, 30));
        pushButton_storeToRam->setMaximumSize(QSize(100, 30));

        verticalLayout_4->addWidget(pushButton_storeToRam);

        pushButton_timePattern = new QPushButton(tab);
        pushButton_timePattern->setObjectName(QStringLiteral("pushButton_timePattern"));
        pushButton_timePattern->setEnabled(true);
        sizePolicy3.setHeightForWidth(pushButton_timePattern->sizePolicy().hasHeightForWidth());
        pushButton_timePattern->setSizePolicy(sizePolicy3);
        pushButton_timePattern->setMinimumSize(QSize(110, 30));
        pushButton_timePattern->setMaximumSize(QSize(100, 30));

        verticalLayout_4->addWidget(pushButton_timePattern);


        horizontalLayout->addLayout(verticalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_5 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_5);

        qwtPlot = new Plot(tab);
        qwtPlot->setObjectName(QStringLiteral("qwtPlot"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(qwtPlot->sizePolicy().hasHeightForWidth());
        qwtPlot->setSizePolicy(sizePolicy4);
        qwtPlot->setMinimumSize(QSize(0, 0));

        verticalLayout_3->addWidget(qwtPlot);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_4);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        verticalLayout_3->addWidget(label_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        pushButton_legend = new QPushButton(tab);
        pushButton_legend->setObjectName(QStringLiteral("pushButton_legend"));
        pushButton_legend->setMinimumSize(QSize(80, 30));
        pushButton_legend->setMaximumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(pushButton_legend);

        pushButton_exportData = new QPushButton(tab);
        pushButton_exportData->setObjectName(QStringLiteral("pushButton_exportData"));
        QSizePolicy sizePolicy5(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pushButton_exportData->sizePolicy().hasHeightForWidth());
        pushButton_exportData->setSizePolicy(sizePolicy5);
        pushButton_exportData->setMinimumSize(QSize(80, 30));
        pushButton_exportData->setMaximumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(pushButton_exportData);

        pushButton_saveGraph = new QPushButton(tab);
        pushButton_saveGraph->setObjectName(QStringLiteral("pushButton_saveGraph"));
        sizePolicy5.setHeightForWidth(pushButton_saveGraph->sizePolicy().hasHeightForWidth());
        pushButton_saveGraph->setSizePolicy(sizePolicy5);
        pushButton_saveGraph->setMinimumSize(QSize(80, 30));
        pushButton_saveGraph->setMaximumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(pushButton_saveGraph);

        horizontalSpacer = new QSpacerItem(100, 23, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_about = new QPushButton(tab);
        pushButton_about->setObjectName(QStringLiteral("pushButton_about"));
        sizePolicy5.setHeightForWidth(pushButton_about->sizePolicy().hasHeightForWidth());
        pushButton_about->setSizePolicy(sizePolicy5);
        pushButton_about->setMinimumSize(QSize(80, 30));
        pushButton_about->setMaximumSize(QSize(80, 30));

        horizontalLayout_3->addWidget(pushButton_about);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout_3);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Panel);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Panel);
    } // setupUi

    void retranslateUi(QDialog *Panel)
    {
        Panel->setWindowTitle(QApplication::translate("Panel", "Optical blood analysis toolkit", Q_NULLPTR));
        label->setText(QApplication::translate("Panel", "Spectrometers", Q_NULLPTR));
        label_2->setText(QApplication::translate("Panel", "Capture modes", Q_NULLPTR));
        pushButton_preview->setText(QApplication::translate("Panel", "Start preview", Q_NULLPTR));
        pushButton_storeToRam->setText(QApplication::translate("Panel", "Store to RAM", Q_NULLPTR));
        pushButton_timePattern->setText(QApplication::translate("Panel", "Time pattern", Q_NULLPTR));
        label_4->setText(QApplication::translate("Panel", "Display options", Q_NULLPTR));
        pushButton_legend->setText(QApplication::translate("Panel", "Legend", Q_NULLPTR));
        pushButton_exportData->setText(QApplication::translate("Panel", "Export data", Q_NULLPTR));
        pushButton_saveGraph->setText(QApplication::translate("Panel", "Save graph", Q_NULLPTR));
        pushButton_about->setText(QApplication::translate("Panel", "About", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Panel", "Preview", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Panel: public Ui_Panel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEL_H
