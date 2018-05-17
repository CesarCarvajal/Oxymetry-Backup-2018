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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WaitingDialog
{
public:
    QLabel *label_message;
    QLabel *label_count;

    void setupUi(QWidget *WaitingDialog)
    {
        if (WaitingDialog->objectName().isEmpty())
            WaitingDialog->setObjectName(QStringLiteral("WaitingDialog"));
        WaitingDialog->setWindowModality(Qt::WindowModal);
        WaitingDialog->resize(233, 98);
        label_message = new QLabel(WaitingDialog);
        label_message->setObjectName(QStringLiteral("label_message"));
        label_message->setGeometry(QRect(20, 10, 191, 31));
        label_count = new QLabel(WaitingDialog);
        label_count->setObjectName(QStringLiteral("label_count"));
        label_count->setGeometry(QRect(40, 50, 151, 31));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_count->setFont(font);
        label_count->setAlignment(Qt::AlignCenter);

        retranslateUi(WaitingDialog);

        QMetaObject::connectSlotsByName(WaitingDialog);
    } // setupUi

    void retranslateUi(QWidget *WaitingDialog)
    {
        WaitingDialog->setWindowTitle(QApplication::translate("WaitingDialog", "Start Pumps", Q_NULLPTR));
        label_message->setText(QApplication::translate("WaitingDialog", "Please start running the pump scripts in:", Q_NULLPTR));
        label_count->setText(QApplication::translate("WaitingDialog", "5", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WaitingDialog: public Ui_WaitingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POL_WAITINGDIALOG_H
