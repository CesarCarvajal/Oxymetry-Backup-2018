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
    QSpacerItem *verticalSpacer_3;
    QLabel *label_message;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_count;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_cancel;

    void setupUi(QWidget *WaitingDialog)
    {
        if (WaitingDialog->objectName().isEmpty())
            WaitingDialog->setObjectName(QStringLiteral("WaitingDialog"));
        WaitingDialog->setWindowModality(Qt::WindowModal);
        WaitingDialog->resize(235, 136);
        verticalLayout_2 = new QVBoxLayout(WaitingDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        label_message = new QLabel(WaitingDialog);
        label_message->setObjectName(QStringLiteral("label_message"));

        verticalLayout->addWidget(label_message);

        verticalSpacer_2 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer_2);

        label_count = new QLabel(WaitingDialog);
        label_count->setObjectName(QStringLiteral("label_count"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_count->setFont(font);
        label_count->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_count);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_cancel = new QPushButton(WaitingDialog);
        pushButton_cancel->setObjectName(QStringLiteral("pushButton_cancel"));
        pushButton_cancel->setMinimumSize(QSize(120, 30));
        pushButton_cancel->setMaximumSize(QSize(120, 30));

        horizontalLayout->addWidget(pushButton_cancel);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(WaitingDialog);

        QMetaObject::connectSlotsByName(WaitingDialog);
    } // setupUi

    void retranslateUi(QWidget *WaitingDialog)
    {
        WaitingDialog->setWindowTitle(QApplication::translate("WaitingDialog", "Start Pumps", Q_NULLPTR));
        label_message->setText(QApplication::translate("WaitingDialog", "Please start running the pump scripts in:", Q_NULLPTR));
        label_count->setText(QApplication::translate("WaitingDialog", "5", Q_NULLPTR));
        pushButton_cancel->setText(QApplication::translate("WaitingDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WaitingDialog: public Ui_WaitingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_WAITINGDIALOG_H
