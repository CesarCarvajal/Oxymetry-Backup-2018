/********************************************************************************
** Form generated from reading UI file 'pol_panelItem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POL_PANELITEM_H
#define UI_POL_PANELITEM_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_PanelItem_Pol
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_ActiveSpec_Pol;
    QLineEdit *lineEdit_name;
    QSpacerItem *horizontalSpacer_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_7;
    ClickableLabel *label_integrationTime;
    QLabel *label_timeBase;
    QSpacerItem *horizontalSpacer_6;
    ClickableLabel *label_autoAdjust;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_setWrange;
    QHBoxLayout *horizontalLayout_12;
    ClickableLabel *label_numberOfAverages;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    ClickableLabel *label_Nspectra;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_freq2;
    QHBoxLayout *horizontalLayout_9;
    ClickableLabel *label_frequency;
    QLabel *label_freq3;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_Status;
    QHBoxLayout *horizontalLayout_11;
    ClickableLabel *label_setWranges;
    QLabel *label_setWrange2;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_saturatedPixels;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_Nspectra2;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox_normalize;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_normalize;
    QFrame *line;

    void setupUi(QWidget *PanelItem_Pol)
    {
        if (PanelItem_Pol->objectName().isEmpty())
            PanelItem_Pol->setObjectName(QStringLiteral("PanelItem_Pol"));
        PanelItem_Pol->resize(284, 216);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PanelItem_Pol->sizePolicy().hasHeightForWidth());
        PanelItem_Pol->setSizePolicy(sizePolicy);
        PanelItem_Pol->setMinimumSize(QSize(0, 0));
        horizontalLayoutWidget = new QWidget(PanelItem_Pol);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 281, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_ActiveSpec_Pol = new QLabel(horizontalLayoutWidget);
        label_ActiveSpec_Pol->setObjectName(QStringLiteral("label_ActiveSpec_Pol"));
        label_ActiveSpec_Pol->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_ActiveSpec_Pol);

        lineEdit_name = new QLineEdit(horizontalLayoutWidget);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_name->sizePolicy().hasHeightForWidth());
        lineEdit_name->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lineEdit_name->setFont(font);
        lineEdit_name->setMaxLength(24);
        lineEdit_name->setFrame(false);
        lineEdit_name->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(lineEdit_name);

        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        gridLayoutWidget = new QWidget(PanelItem_Pol);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 30, 281, 183));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_integrationTime = new ClickableLabel(gridLayoutWidget);
        label_integrationTime->setObjectName(QStringLiteral("label_integrationTime"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_integrationTime->sizePolicy().hasHeightForWidth());
        label_integrationTime->setSizePolicy(sizePolicy2);
        label_integrationTime->setMinimumSize(QSize(20, 0));
        label_integrationTime->setMaximumSize(QSize(50, 16777215));
        QFont font1;
        font1.setUnderline(false);
        label_integrationTime->setFont(font1);
        label_integrationTime->setCursor(QCursor(Qt::PointingHandCursor));
        label_integrationTime->setFrameShape(QFrame::StyledPanel);
        label_integrationTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_integrationTime);

        label_timeBase = new QLabel(gridLayoutWidget);
        label_timeBase->setObjectName(QStringLiteral("label_timeBase"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_timeBase->sizePolicy().hasHeightForWidth());
        label_timeBase->setSizePolicy(sizePolicy3);
        label_timeBase->setMinimumSize(QSize(20, 0));
        label_timeBase->setMaximumSize(QSize(20, 16777215));
        label_timeBase->setSizeIncrement(QSize(20, 0));
        label_timeBase->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_timeBase);

        horizontalSpacer_6 = new QSpacerItem(20, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);

        label_autoAdjust = new ClickableLabel(gridLayoutWidget);
        label_autoAdjust->setObjectName(QStringLiteral("label_autoAdjust"));
        QFont font2;
        font2.setUnderline(true);
        label_autoAdjust->setFont(font2);
        label_autoAdjust->setCursor(QCursor(Qt::PointingHandCursor));
        label_autoAdjust->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_autoAdjust);

        horizontalSpacer_13 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_13);


        gridLayout->addLayout(horizontalLayout_7, 1, 2, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(5, 18, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        label->setFont(font3);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label);


        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalSpacer_9 = new QSpacerItem(5, 18, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_9);

        label_setWrange = new QLabel(gridLayoutWidget);
        label_setWrange->setObjectName(QStringLiteral("label_setWrange"));
        label_setWrange->setFont(font1);
        label_setWrange->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_13->addWidget(label_setWrange);


        gridLayout->addLayout(horizontalLayout_13, 6, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_numberOfAverages = new ClickableLabel(gridLayoutWidget);
        label_numberOfAverages->setObjectName(QStringLiteral("label_numberOfAverages"));
        label_numberOfAverages->setFont(font1);
        label_numberOfAverages->setCursor(QCursor(Qt::PointingHandCursor));
        label_numberOfAverages->setFrameShape(QFrame::StyledPanel);
        label_numberOfAverages->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_12->addWidget(label_numberOfAverages);


        gridLayout->addLayout(horizontalLayout_12, 5, 2, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalSpacer_8 = new QSpacerItem(5, 18, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_8);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font3);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_2);


        gridLayout->addLayout(horizontalLayout_14, 5, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_Nspectra = new ClickableLabel(gridLayoutWidget);
        label_Nspectra->setObjectName(QStringLiteral("label_Nspectra"));
        label_Nspectra->setEnabled(true);
        label_Nspectra->setFont(font1);
        label_Nspectra->setCursor(QCursor(Qt::PointingHandCursor));
        label_Nspectra->setFrameShape(QFrame::NoFrame);
        label_Nspectra->setFrameShadow(QFrame::Plain);

        horizontalLayout_3->addWidget(label_Nspectra);


        gridLayout->addLayout(horizontalLayout_3, 3, 2, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_7 = new QSpacerItem(5, 18, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);

        label_freq2 = new QLabel(gridLayoutWidget);
        label_freq2->setObjectName(QStringLiteral("label_freq2"));

        horizontalLayout_8->addWidget(label_freq2);


        gridLayout->addLayout(horizontalLayout_8, 4, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_frequency = new ClickableLabel(gridLayoutWidget);
        label_frequency->setObjectName(QStringLiteral("label_frequency"));
        label_frequency->setEnabled(true);
        sizePolicy2.setHeightForWidth(label_frequency->sizePolicy().hasHeightForWidth());
        label_frequency->setSizePolicy(sizePolicy2);
        label_frequency->setMinimumSize(QSize(20, 0));
        label_frequency->setMaximumSize(QSize(50, 16777215));
        label_frequency->setFont(font1);
        label_frequency->setCursor(QCursor(Qt::PointingHandCursor));
        label_frequency->setFrameShape(QFrame::NoFrame);

        horizontalLayout_9->addWidget(label_frequency);

        label_freq3 = new QLabel(gridLayoutWidget);
        label_freq3->setObjectName(QStringLiteral("label_freq3"));

        horizontalLayout_9->addWidget(label_freq3);

        horizontalSpacer_10 = new QSpacerItem(20, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_10);


        gridLayout->addLayout(horizontalLayout_9, 4, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(5, 18, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        label_Status = new QLabel(gridLayoutWidget);
        label_Status->setObjectName(QStringLiteral("label_Status"));

        horizontalLayout_4->addWidget(label_Status);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_setWranges = new ClickableLabel(gridLayoutWidget);
        label_setWranges->setObjectName(QStringLiteral("label_setWranges"));
        label_setWranges->setFont(font1);
        label_setWranges->setCursor(QCursor(Qt::PointingHandCursor));
        label_setWranges->setFrameShape(QFrame::StyledPanel);

        horizontalLayout_11->addWidget(label_setWranges);

        label_setWrange2 = new QLabel(gridLayoutWidget);
        label_setWrange2->setObjectName(QStringLiteral("label_setWrange2"));

        horizontalLayout_11->addWidget(label_setWrange2);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);


        gridLayout->addLayout(horizontalLayout_11, 6, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_saturatedPixels = new QLabel(gridLayoutWidget);
        label_saturatedPixels->setObjectName(QStringLiteral("label_saturatedPixels"));
        label_saturatedPixels->setFont(font3);
        label_saturatedPixels->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_saturatedPixels);


        gridLayout->addLayout(horizontalLayout_2, 0, 2, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_4 = new QSpacerItem(5, 18, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        label_Nspectra2 = new QLabel(gridLayoutWidget);
        label_Nspectra2->setObjectName(QStringLiteral("label_Nspectra2"));

        horizontalLayout_6->addWidget(label_Nspectra2);


        gridLayout->addLayout(horizontalLayout_6, 3, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        checkBox_normalize = new QCheckBox(gridLayoutWidget);
        checkBox_normalize->setObjectName(QStringLiteral("checkBox_normalize"));
        checkBox_normalize->setAutoFillBackground(false);

        horizontalLayout_10->addWidget(checkBox_normalize);


        gridLayout->addLayout(horizontalLayout_10, 8, 2, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalSpacer_12 = new QSpacerItem(5, 18, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_12);

        label_normalize = new QLabel(gridLayoutWidget);
        label_normalize->setObjectName(QStringLiteral("label_normalize"));

        horizontalLayout_15->addWidget(label_normalize);


        gridLayout->addLayout(horizontalLayout_15, 8, 0, 1, 1);

        line = new QFrame(PanelItem_Pol);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(5, 28, 275, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(PanelItem_Pol);

        QMetaObject::connectSlotsByName(PanelItem_Pol);
    } // setupUi

    void retranslateUi(QWidget *PanelItem_Pol)
    {
        PanelItem_Pol->setWindowTitle(QApplication::translate("PanelItem_Pol", "Form", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_ActiveSpec_Pol->setToolTip(QApplication::translate("PanelItem_Pol", "Which spectrometer is active?", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_ActiveSpec_Pol->setText(QApplication::translate("PanelItem_Pol", "Active Spectrometer:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_name->setToolTip(QApplication::translate("PanelItem_Pol", "Change spectrometer Name", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        lineEdit_name->setText(QString());
#ifndef QT_NO_TOOLTIP
        label_integrationTime->setToolTip(QApplication::translate("PanelItem_Pol", "Change Integration Time", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_integrationTime->setText(QApplication::translate("PanelItem_Pol", "6", Q_NULLPTR));
        label_timeBase->setText(QApplication::translate("PanelItem_Pol", "ms", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_autoAdjust->setToolTip(QApplication::translate("PanelItem_Pol", "Auto Adjust Integration Time", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_autoAdjust->setText(QApplication::translate("PanelItem_Pol", "(Auto)", Q_NULLPTR));
        label->setText(QApplication::translate("PanelItem_Pol", "Integration Time:", Q_NULLPTR));
        label_setWrange->setText(QApplication::translate("PanelItem_Pol", "Wavelengths Range:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_numberOfAverages->setToolTip(QApplication::translate("PanelItem_Pol", "Change Number of Averages", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_numberOfAverages->setText(QString());
        label_2->setText(QApplication::translate("PanelItem_Pol", "Number of Averages:    ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_Nspectra->setToolTip(QApplication::translate("PanelItem_Pol", "Change Number of Spectra", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_Nspectra->setText(QApplication::translate("PanelItem_Pol", "1000", Q_NULLPTR));
        label_freq2->setText(QApplication::translate("PanelItem_Pol", "Frequency:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_frequency->setToolTip(QApplication::translate("PanelItem_Pol", "Change the Frequency to Measure", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_frequency->setText(QApplication::translate("PanelItem_Pol", "7", Q_NULLPTR));
        label_freq3->setText(QApplication::translate("PanelItem_Pol", "Hz", Q_NULLPTR));
        label_Status->setText(QApplication::translate("PanelItem_Pol", "Status:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_setWranges->setToolTip(QApplication::translate("PanelItem_Pol", "Set the wavelength range", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_setWranges->setText(QApplication::translate("PanelItem_Pol", "400,0 - 750,0", Q_NULLPTR));
        label_setWrange2->setText(QApplication::translate("PanelItem_Pol", "nm", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        label_saturatedPixels->setToolTip(QApplication::translate("PanelItem_Pol", "Spectrometer Status", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_saturatedPixels->setText(QApplication::translate("PanelItem_Pol", "<saturated pixels>", Q_NULLPTR));
        label_Nspectra2->setText(QApplication::translate("PanelItem_Pol", "Number of Spectra:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        checkBox_normalize->setToolTip(QApplication::translate("PanelItem_Pol", "Normalize the Counts", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        checkBox_normalize->setText(QString());
        label_normalize->setText(QApplication::translate("PanelItem_Pol", "Normalize Counts:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelItem_Pol: public Ui_PanelItem_Pol {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_PANELITEM_H
