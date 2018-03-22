/********************************************************************************
** Form generated from reading UI file 'initial_setup.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIAL_SETUP_H
#define UI_INITIAL_SETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InitialSetup
{
public:
    QLabel *label;
    QCheckBox *checkBox_modules_iad;
    QCheckBox *checkBox_modules_polarimeter;
    QPushButton *pushButton_continue;
    QLabel *label_2;
    QLabel *label_3;
    QCheckBox *checkBox_toolkits_fluidic;
    QCheckBox *checkBox_toolkits_light;
    QCheckBox *checkBox_connection_usb;
    QCheckBox *checkBox_connection_ethernet;
    QLabel *label_4;

    void setupUi(QWidget *InitialSetup)
    {
        if (InitialSetup->objectName().isEmpty())
            InitialSetup->setObjectName(QStringLiteral("InitialSetup"));
        InitialSetup->resize(500, 200);
        label = new QLabel(InitialSetup);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 490, 20));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        checkBox_modules_iad = new QCheckBox(InitialSetup);
        checkBox_modules_iad->setObjectName(QStringLiteral("checkBox_modules_iad"));
        checkBox_modules_iad->setGeometry(QRect(10, 70, 140, 20));
        checkBox_modules_polarimeter = new QCheckBox(InitialSetup);
        checkBox_modules_polarimeter->setObjectName(QStringLiteral("checkBox_modules_polarimeter"));
        checkBox_modules_polarimeter->setGeometry(QRect(10, 100, 140, 20));
        pushButton_continue = new QPushButton(InitialSetup);
        pushButton_continue->setObjectName(QStringLiteral("pushButton_continue"));
        pushButton_continue->setGeometry(QRect(420, 170, 75, 25));
        label_2 = new QLabel(InitialSetup);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 80, 20));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_3 = new QLabel(InitialSetup);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(300, 40, 80, 20));
        label_3->setFont(font1);
        checkBox_toolkits_fluidic = new QCheckBox(InitialSetup);
        checkBox_toolkits_fluidic->setObjectName(QStringLiteral("checkBox_toolkits_fluidic"));
        checkBox_toolkits_fluidic->setGeometry(QRect(300, 70, 140, 20));
        checkBox_toolkits_light = new QCheckBox(InitialSetup);
        checkBox_toolkits_light->setObjectName(QStringLiteral("checkBox_toolkits_light"));
        checkBox_toolkits_light->setGeometry(QRect(300, 100, 140, 20));
        checkBox_connection_usb = new QCheckBox(InitialSetup);
        checkBox_connection_usb->setObjectName(QStringLiteral("checkBox_connection_usb"));
        checkBox_connection_usb->setGeometry(QRect(10, 170, 60, 20));
        checkBox_connection_usb->setChecked(true);
        checkBox_connection_ethernet = new QCheckBox(InitialSetup);
        checkBox_connection_ethernet->setObjectName(QStringLiteral("checkBox_connection_ethernet"));
        checkBox_connection_ethernet->setGeometry(QRect(70, 170, 80, 20));
        label_4 = new QLabel(InitialSetup);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 140, 80, 20));
        label_4->setFont(font1);

        retranslateUi(InitialSetup);

        QMetaObject::connectSlotsByName(InitialSetup);
    } // setupUi

    void retranslateUi(QWidget *InitialSetup)
    {
        InitialSetup->setWindowTitle(QApplication::translate("InitialSetup", "Initial setup", Q_NULLPTR));
        label->setText(QApplication::translate("InitialSetup", "No configuration file has been found. Please customize your application front-end:", Q_NULLPTR));
        checkBox_modules_iad->setText(QApplication::translate("InitialSetup", "Inverse Adding-Doubling", Q_NULLPTR));
        checkBox_modules_polarimeter->setText(QApplication::translate("InitialSetup", "Polarimeter", Q_NULLPTR));
        pushButton_continue->setText(QApplication::translate("InitialSetup", "Continue", Q_NULLPTR));
        label_2->setText(QApplication::translate("InitialSetup", "Modules", Q_NULLPTR));
        label_3->setText(QApplication::translate("InitialSetup", "Toolkits", Q_NULLPTR));
        checkBox_toolkits_fluidic->setText(QApplication::translate("InitialSetup", "Fluidic circuit", Q_NULLPTR));
        checkBox_toolkits_light->setText(QApplication::translate("InitialSetup", "Light source", Q_NULLPTR));
        checkBox_connection_usb->setText(QApplication::translate("InitialSetup", "USB", Q_NULLPTR));
        checkBox_connection_ethernet->setText(QApplication::translate("InitialSetup", "Ethernet", Q_NULLPTR));
        label_4->setText(QApplication::translate("InitialSetup", "Connection", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InitialSetup: public Ui_InitialSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIAL_SETUP_H
