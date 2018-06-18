/********************************************************************************
** Form generated from reading UI file 'pol_waitingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POL_WAITINGDIALOG_H
#define UI_POL_WAITINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaitingDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_message;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_count;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_skip;

    void setupUi(QWidget *WaitingDialog)
    {
        if (WaitingDialog->objectName().isEmpty())
            WaitingDialog->setObjectName(QStringLiteral("WaitingDialog"));
        WaitingDialog->setWindowModality(Qt::WindowModal);
        WaitingDialog->resize(268, 216);
        verticalLayout_2 = new QVBoxLayout(WaitingDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_3 = new QLabel(WaitingDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        label_message = new QLabel(WaitingDialog);
        label_message->setObjectName(QStringLiteral("label_message"));

        verticalLayout->addWidget(label_message);

        label = new QLabel(WaitingDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(WaitingDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_4 = new QLabel(WaitingDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        verticalSpacer_2 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        label_count = new QLabel(WaitingDialog);
        label_count->setObjectName(QStringLiteral("label_count"));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_count->setFont(font1);
        label_count->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_count);

        verticalSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_cancel = new QPushButton(WaitingDialog);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setMinimumSize(QSize(120, 30));
        pushButton_cancel->setMaximumSize(QSize(120, 30));

        horizontalLayout->addWidget(pushButton_cancel);

        pushButton_skip = new QPushButton(WaitingDialog);
        pushButton_skip->setObjectName(QStringLiteral("pushButton_skip"));
        pushButton_skip->setMinimumSize(QSize(120, 30));
        pushButton_skip->setMaximumSize(QSize(120, 30));

        horizontalLayout->addWidget(pushButton_skip);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(WaitingDialog);

        QMetaObject::connectSlotsByName(WaitingDialog);
    } // setupUi

    void retranslateUi(QWidget *WaitingDialog)
    {
        WaitingDialog->setWindowTitle(QApplication::translate("WaitingDialog", "Start Pumps", Q_NULLPTR));
        label_3->setText(QApplication::translate("WaitingDialog", "Syncronize Start", Q_NULLPTR));
        label_message->setText(QApplication::translate("WaitingDialog", "1)  Open the Nemesys Pump Software.", Q_NULLPTR));
        label->setText(QApplication::translate("WaitingDialog", "2)  Select Sync. Start.", Q_NULLPTR));
        label_2->setText(QApplication::translate("WaitingDialog", "3)  Select the needed Syringes.", Q_NULLPTR));
        label_4->setText(QApplication::translate("WaitingDialog", "4)  Press OK in:", Q_NULLPTR));
        label_count->setText(QApplication::translate("WaitingDialog", "10", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("WaitingDialog", "Cancel", Q_NULLPTR));
        pushButton_skip->setText(QApplication::translate("WaitingDialog", "Skip", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WaitingDialog: public Ui_WaitingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_WAITINGDIALOG_H
