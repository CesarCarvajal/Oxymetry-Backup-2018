/********************************************************************************
** Form generated from reading UI file 'iad_panel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IAD_PANEL_H
#define UI_IAD_PANEL_H

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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "clickablelabel.h"
#include "measurementstable.h"
#include "plot.h"

QT_BEGIN_NAMESPACE

class Ui_PanelIAD
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_iad_configuration;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *button_iad_newConfiguration;
    QPushButton *button_iad_openConfiguration;
    QSpacerItem *horizontalSpacer_6;
    ClickableLabel *label_iad_configurationName;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_iad_calibration;
    QPushButton *button_iad_calibrate;
    QSpacerItem *verticalSpacer;
    QLabel *label_iad_measurement;
    QLabel *label_iad_name;
    QLineEdit *lineEdit_iad_name;
    QLabel *label_iad_description;
    QPlainTextEdit *plainTextEdit_iad_description;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *button_iad_measure;
    QCheckBox *checkBox_iad_liveView;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_iad_analysis;
    MeasurementsTable *table_iad_measurements;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_5;
    Plot *qwtPlot_reflection;
    Plot *qwtPlot_transmission;

    void setupUi(QDialog *PanelIAD)
    {
        if (PanelIAD->objectName().isEmpty())
            PanelIAD->setObjectName(QStringLiteral("PanelIAD"));
        PanelIAD->resize(1200, 800);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PanelIAD->sizePolicy().hasHeightForWidth());
        PanelIAD->setSizePolicy(sizePolicy);
        PanelIAD->setMinimumSize(QSize(1200, 800));
        gridLayout = new QGridLayout(PanelIAD);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_iad_configuration = new QLabel(PanelIAD);
        label_iad_configuration->setObjectName(QStringLiteral("label_iad_configuration"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_iad_configuration->setFont(font);

        verticalLayout_6->addWidget(label_iad_configuration);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 0, -1, -1);
        button_iad_newConfiguration = new QPushButton(PanelIAD);
        button_iad_newConfiguration->setObjectName(QStringLiteral("button_iad_newConfiguration"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(button_iad_newConfiguration->sizePolicy().hasHeightForWidth());
        button_iad_newConfiguration->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(button_iad_newConfiguration);

        button_iad_openConfiguration = new QPushButton(PanelIAD);
        button_iad_openConfiguration->setObjectName(QStringLiteral("button_iad_openConfiguration"));
        sizePolicy1.setHeightForWidth(button_iad_openConfiguration->sizePolicy().hasHeightForWidth());
        button_iad_openConfiguration->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(button_iad_openConfiguration);

        horizontalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        label_iad_configurationName = new ClickableLabel(PanelIAD);
        label_iad_configurationName->setObjectName(QStringLiteral("label_iad_configurationName"));
        label_iad_configurationName->setMinimumSize(QSize(0, 0));
        label_iad_configurationName->setMaximumSize(QSize(340, 23));
        label_iad_configurationName->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_6->addWidget(label_iad_configurationName);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_6->addLayout(horizontalLayout_6);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_3);

        label_iad_calibration = new QLabel(PanelIAD);
        label_iad_calibration->setObjectName(QStringLiteral("label_iad_calibration"));
        label_iad_calibration->setFont(font);
        label_iad_calibration->setMargin(0);

        verticalLayout_6->addWidget(label_iad_calibration);

        button_iad_calibrate = new QPushButton(PanelIAD);
        button_iad_calibrate->setObjectName(QStringLiteral("button_iad_calibrate"));
        button_iad_calibrate->setEnabled(false);
        sizePolicy1.setHeightForWidth(button_iad_calibrate->sizePolicy().hasHeightForWidth());
        button_iad_calibrate->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(button_iad_calibrate);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer);

        label_iad_measurement = new QLabel(PanelIAD);
        label_iad_measurement->setObjectName(QStringLiteral("label_iad_measurement"));
        label_iad_measurement->setFont(font);

        verticalLayout_6->addWidget(label_iad_measurement);

        label_iad_name = new QLabel(PanelIAD);
        label_iad_name->setObjectName(QStringLiteral("label_iad_name"));

        verticalLayout_6->addWidget(label_iad_name);

        lineEdit_iad_name = new QLineEdit(PanelIAD);
        lineEdit_iad_name->setObjectName(QStringLiteral("lineEdit_iad_name"));
        lineEdit_iad_name->setEnabled(false);
        sizePolicy1.setHeightForWidth(lineEdit_iad_name->sizePolicy().hasHeightForWidth());
        lineEdit_iad_name->setSizePolicy(sizePolicy1);
        lineEdit_iad_name->setMinimumSize(QSize(540, 20));
        lineEdit_iad_name->setMaximumSize(QSize(16777215, 20));

        verticalLayout_6->addWidget(lineEdit_iad_name);

        label_iad_description = new QLabel(PanelIAD);
        label_iad_description->setObjectName(QStringLiteral("label_iad_description"));

        verticalLayout_6->addWidget(label_iad_description);

        plainTextEdit_iad_description = new QPlainTextEdit(PanelIAD);
        plainTextEdit_iad_description->setObjectName(QStringLiteral("plainTextEdit_iad_description"));
        plainTextEdit_iad_description->setEnabled(false);
        sizePolicy1.setHeightForWidth(plainTextEdit_iad_description->sizePolicy().hasHeightForWidth());
        plainTextEdit_iad_description->setSizePolicy(sizePolicy1);
        plainTextEdit_iad_description->setMinimumSize(QSize(540, 120));

        verticalLayout_6->addWidget(plainTextEdit_iad_description);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        button_iad_measure = new QPushButton(PanelIAD);
        button_iad_measure->setObjectName(QStringLiteral("button_iad_measure"));
        button_iad_measure->setEnabled(false);
        sizePolicy1.setHeightForWidth(button_iad_measure->sizePolicy().hasHeightForWidth());
        button_iad_measure->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(button_iad_measure);

        checkBox_iad_liveView = new QCheckBox(PanelIAD);
        checkBox_iad_liveView->setObjectName(QStringLiteral("checkBox_iad_liveView"));
        checkBox_iad_liveView->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBox_iad_liveView->sizePolicy().hasHeightForWidth());
        checkBox_iad_liveView->setSizePolicy(sizePolicy2);

        horizontalLayout_5->addWidget(checkBox_iad_liveView);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout_6->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_6->addItem(verticalSpacer_2);

        label_iad_analysis = new QLabel(PanelIAD);
        label_iad_analysis->setObjectName(QStringLiteral("label_iad_analysis"));
        label_iad_analysis->setFont(font);

        verticalLayout_6->addWidget(label_iad_analysis);

        table_iad_measurements = new MeasurementsTable(PanelIAD);
        if (table_iad_measurements->columnCount() < 5)
            table_iad_measurements->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_iad_measurements->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_iad_measurements->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table_iad_measurements->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table_iad_measurements->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        table_iad_measurements->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        table_iad_measurements->setObjectName(QStringLiteral("table_iad_measurements"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(table_iad_measurements->sizePolicy().hasHeightForWidth());
        table_iad_measurements->setSizePolicy(sizePolicy3);
        table_iad_measurements->setMinimumSize(QSize(540, 320));
        table_iad_measurements->setMaximumSize(QSize(540, 16777215));
        table_iad_measurements->setFocusPolicy(Qt::NoFocus);
        table_iad_measurements->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table_iad_measurements->setAutoScroll(false);
        table_iad_measurements->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_iad_measurements->setSelectionMode(QAbstractItemView::SingleSelection);
        table_iad_measurements->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_iad_measurements->horizontalHeader()->setHighlightSections(false);
        table_iad_measurements->verticalHeader()->setVisible(false);
        table_iad_measurements->verticalHeader()->setHighlightSections(false);

        verticalLayout_6->addWidget(table_iad_measurements);


        horizontalLayout_4->addLayout(verticalLayout_6);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        qwtPlot_reflection = new Plot(PanelIAD);
        qwtPlot_reflection->setObjectName(QStringLiteral("qwtPlot_reflection"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(qwtPlot_reflection->sizePolicy().hasHeightForWidth());
        qwtPlot_reflection->setSizePolicy(sizePolicy4);

        verticalLayout_5->addWidget(qwtPlot_reflection);

        qwtPlot_transmission = new Plot(PanelIAD);
        qwtPlot_transmission->setObjectName(QStringLiteral("qwtPlot_transmission"));
        sizePolicy4.setHeightForWidth(qwtPlot_transmission->sizePolicy().hasHeightForWidth());
        qwtPlot_transmission->setSizePolicy(sizePolicy4);

        verticalLayout_5->addWidget(qwtPlot_transmission);


        horizontalLayout_4->addLayout(verticalLayout_5);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);


        retranslateUi(PanelIAD);

        QMetaObject::connectSlotsByName(PanelIAD);
    } // setupUi

    void retranslateUi(QDialog *PanelIAD)
    {
        PanelIAD->setWindowTitle(QApplication::translate("PanelIAD", "Optical blood analysis toolkit", Q_NULLPTR));
        label_iad_configuration->setText(QApplication::translate("PanelIAD", "1. Configuration", Q_NULLPTR));
        button_iad_newConfiguration->setText(QApplication::translate("PanelIAD", "New", Q_NULLPTR));
        button_iad_openConfiguration->setText(QApplication::translate("PanelIAD", "Open", Q_NULLPTR));
        label_iad_configurationName->setText(QApplication::translate("PanelIAD", "<configuration loaded>", Q_NULLPTR));
        label_iad_calibration->setText(QApplication::translate("PanelIAD", "2. Calibration", Q_NULLPTR));
        button_iad_calibrate->setText(QApplication::translate("PanelIAD", "Calibrate", Q_NULLPTR));
        label_iad_measurement->setText(QApplication::translate("PanelIAD", "3. Measurement", Q_NULLPTR));
        label_iad_name->setText(QApplication::translate("PanelIAD", "Name", Q_NULLPTR));
        label_iad_description->setText(QApplication::translate("PanelIAD", "Description", Q_NULLPTR));
        button_iad_measure->setText(QApplication::translate("PanelIAD", "Measure", Q_NULLPTR));
        checkBox_iad_liveView->setText(QApplication::translate("PanelIAD", "Live view", Q_NULLPTR));
        label_iad_analysis->setText(QApplication::translate("PanelIAD", "4. Analysis", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = table_iad_measurements->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PanelIAD", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = table_iad_measurements->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PanelIAD", "Date", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = table_iad_measurements->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("PanelIAD", "Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = table_iad_measurements->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("PanelIAD", "Status", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelIAD: public Ui_PanelIAD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IAD_PANEL_H
