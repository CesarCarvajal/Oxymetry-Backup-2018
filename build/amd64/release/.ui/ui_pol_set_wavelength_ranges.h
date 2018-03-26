/********************************************************************************
** Form generated from reading UI file 'pol_set_wavelength_ranges.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POL_SET_WAVELENGTH_RANGES_H
#define UI_POL_SET_WAVELENGTH_RANGES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PanelSetWavelengthRanges
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *button_apply;
    QSpacerItem *horizontalSpacer_2;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *doubleSpinBox_minWset;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *doubleSpinBox_maxWset;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QWidget *PanelSetWavelengthRanges)
    {
        if (PanelSetWavelengthRanges->objectName().isEmpty())
            PanelSetWavelengthRanges->setObjectName(QStringLiteral("PanelSetWavelengthRanges"));
        PanelSetWavelengthRanges->resize(367, 95);
        horizontalLayoutWidget = new QWidget(PanelSetWavelengthRanges);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 50, 351, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        button_apply = new QPushButton(horizontalLayoutWidget);
        button_apply->setObjectName(QStringLiteral("button_apply"));
        button_apply->setMinimumSize(QSize(100, 0));
        button_apply->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(button_apply);

        horizontalSpacer_2 = new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        gridLayoutWidget = new QWidget(PanelSetWavelengthRanges);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 0, 351, 52));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        doubleSpinBox_minWset = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinBox_minWset->setObjectName(QStringLiteral("doubleSpinBox_minWset"));
        doubleSpinBox_minWset->setMinimumSize(QSize(100, 0));
        doubleSpinBox_minWset->setDecimals(1);
        doubleSpinBox_minWset->setMaximum(1000);
        doubleSpinBox_minWset->setSingleStep(0.1);
        doubleSpinBox_minWset->setValue(400);

        horizontalLayout_2->addWidget(doubleSpinBox_minWset);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(30, 0));

        horizontalLayout_2->addWidget(label);


        gridLayout->addLayout(horizontalLayout_2, 0, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        doubleSpinBox_maxWset = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinBox_maxWset->setObjectName(QStringLiteral("doubleSpinBox_maxWset"));
        doubleSpinBox_maxWset->setMinimumSize(QSize(100, 0));
        doubleSpinBox_maxWset->setDecimals(1);
        doubleSpinBox_maxWset->setMaximum(2000);
        doubleSpinBox_maxWset->setSingleStep(0.1);
        doubleSpinBox_maxWset->setValue(750);

        horizontalLayout_3->addWidget(doubleSpinBox_maxWset);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(30, 0));

        horizontalLayout_3->addWidget(label_2);


        gridLayout->addLayout(horizontalLayout_3, 1, 2, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 1, 1, 1);


        retranslateUi(PanelSetWavelengthRanges);

        QMetaObject::connectSlotsByName(PanelSetWavelengthRanges);
    } // setupUi

    void retranslateUi(QWidget *PanelSetWavelengthRanges)
    {
        PanelSetWavelengthRanges->setWindowTitle(QApplication::translate("PanelSetWavelengthRanges", "Select a Wavelength", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        button_apply->setToolTip(QApplication::translate("PanelSetWavelengthRanges", "Set Wavelength", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        button_apply->setText(QApplication::translate("PanelSetWavelengthRanges", "Set", Q_NULLPTR));
        label->setText(QApplication::translate("PanelSetWavelengthRanges", "nm", Q_NULLPTR));
        label_2->setText(QApplication::translate("PanelSetWavelengthRanges", "nm", Q_NULLPTR));
        label_3->setText(QApplication::translate("PanelSetWavelengthRanges", "Min. Wavelength:", Q_NULLPTR));
        label_4->setText(QApplication::translate("PanelSetWavelengthRanges", "Max. Wavelength:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PanelSetWavelengthRanges: public Ui_PanelSetWavelengthRanges {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_SET_WAVELENGTH_RANGES_H
