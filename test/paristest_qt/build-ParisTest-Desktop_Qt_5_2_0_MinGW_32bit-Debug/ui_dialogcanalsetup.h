/********************************************************************************
** Form generated from reading UI file 'dialogcanalsetup.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCANALSETUP_H
#define UI_DIALOGCANALSETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_DialogCanalSetup
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *descriptionLineEdit;
    QLabel *descriptionLabel;
    QLineEdit *pathToDriverLineEdit;
    QLabel *deviceConfigurationStringLabel;
    QLabel *flagsLabel;
    QLabel *pathToDriverLabel;
    QLineEdit *flagsLineEdit;
    QLineEdit *deviceConfigurationStringLineEdit;
    QToolButton *toolButton;
    QToolButton *toolButton_2;

    void setupUi(QDialog *DialogCanalSetup)
    {
        if (DialogCanalSetup->objectName().isEmpty())
            DialogCanalSetup->setObjectName(QStringLiteral("DialogCanalSetup"));
        DialogCanalSetup->resize(472, 177);
        buttonBox = new QDialogButtonBox(DialogCanalSetup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(70, 140, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        descriptionLineEdit = new QLineEdit(DialogCanalSetup);
        descriptionLineEdit->setObjectName(QStringLiteral("descriptionLineEdit"));
        descriptionLineEdit->setGeometry(QRect(150, 20, 261, 20));
        descriptionLabel = new QLabel(DialogCanalSetup);
        descriptionLabel->setObjectName(QStringLiteral("descriptionLabel"));
        descriptionLabel->setGeometry(QRect(50, 20, 101, 20));
        descriptionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pathToDriverLineEdit = new QLineEdit(DialogCanalSetup);
        pathToDriverLineEdit->setObjectName(QStringLiteral("pathToDriverLineEdit"));
        pathToDriverLineEdit->setGeometry(QRect(150, 50, 235, 20));
        deviceConfigurationStringLabel = new QLabel(DialogCanalSetup);
        deviceConfigurationStringLabel->setObjectName(QStringLiteral("deviceConfigurationStringLabel"));
        deviceConfigurationStringLabel->setGeometry(QRect(-20, 80, 171, 16));
        deviceConfigurationStringLabel->setLayoutDirection(Qt::LeftToRight);
        flagsLabel = new QLabel(DialogCanalSetup);
        flagsLabel->setObjectName(QStringLiteral("flagsLabel"));
        flagsLabel->setGeometry(QRect(80, 110, 71, 20));
        flagsLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pathToDriverLabel = new QLabel(DialogCanalSetup);
        pathToDriverLabel->setObjectName(QStringLiteral("pathToDriverLabel"));
        pathToDriverLabel->setGeometry(QRect(40, 50, 111, 20));
        pathToDriverLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        flagsLineEdit = new QLineEdit(DialogCanalSetup);
        flagsLineEdit->setObjectName(QStringLiteral("flagsLineEdit"));
        flagsLineEdit->setGeometry(QRect(150, 110, 51, 20));
        deviceConfigurationStringLineEdit = new QLineEdit(DialogCanalSetup);
        deviceConfigurationStringLineEdit->setObjectName(QStringLiteral("deviceConfigurationStringLineEdit"));
        deviceConfigurationStringLineEdit->setGeometry(QRect(150, 80, 235, 20));
        toolButton = new QToolButton(DialogCanalSetup);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(390, 50, 25, 19));
        toolButton_2 = new QToolButton(DialogCanalSetup);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setGeometry(QRect(390, 80, 25, 19));

        retranslateUi(DialogCanalSetup);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogCanalSetup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogCanalSetup, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogCanalSetup);
    } // setupUi

    void retranslateUi(QDialog *DialogCanalSetup)
    {
        DialogCanalSetup->setWindowTitle(QApplication::translate("DialogCanalSetup", "Level I (CANAL) driver", 0));
        descriptionLabel->setText(QApplication::translate("DialogCanalSetup", "Description : ", 0));
        deviceConfigurationStringLabel->setText(QApplication::translate("DialogCanalSetup", "<html><head/><body><p align=\"right\">Device configuration string : </p></body></html>", 0));
        flagsLabel->setText(QApplication::translate("DialogCanalSetup", "Flags : ", 0));
        pathToDriverLabel->setText(QApplication::translate("DialogCanalSetup", "Path to driver : ", 0));
        toolButton->setText(QApplication::translate("DialogCanalSetup", "...", 0));
        toolButton_2->setText(QApplication::translate("DialogCanalSetup", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogCanalSetup: public Ui_DialogCanalSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCANALSETUP_H
