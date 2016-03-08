/********************************************************************************
** Form generated from reading UI file 'dialoglevel2drvsetup.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLEVEL2DRVSETUP_H
#define UI_DIALOGLEVEL2DRVSETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_DialogLevel2DrvSetup
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QLabel *label_7;
    QLineEdit *lineEdit_6;
    QLabel *label_8;
    QPushButton *btnSetFilter;
    QPushButton *btnTestConnection;
    QToolButton *toolButton;

    void setupUi(QDialog *DialogLevel2DrvSetup)
    {
        if (DialogLevel2DrvSetup->objectName().isEmpty())
            DialogLevel2DrvSetup->setObjectName(QStringLiteral("DialogLevel2DrvSetup"));
        DialogLevel2DrvSetup->resize(400, 309);
        buttonBox = new QDialogButtonBox(DialogLevel2DrvSetup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 270, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(DialogLevel2DrvSetup);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(120, 10, 261, 20));
        label_2 = new QLabel(DialogLevel2DrvSetup);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(52, 40, 61, 20));
        lineEdit_2 = new QLineEdit(DialogLevel2DrvSetup);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(120, 40, 261, 20));
        label_3 = new QLabel(DialogLevel2DrvSetup);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 10, 61, 20));
        label_4 = new QLabel(DialogLevel2DrvSetup);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 70, 61, 20));
        lineEdit_3 = new QLineEdit(DialogLevel2DrvSetup);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(120, 70, 81, 20));
        label_5 = new QLabel(DialogLevel2DrvSetup);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(52, 100, 61, 20));
        lineEdit_4 = new QLineEdit(DialogLevel2DrvSetup);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(120, 100, 121, 20));
        label_6 = new QLabel(DialogLevel2DrvSetup);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(52, 130, 61, 20));
        lineEdit_5 = new QLineEdit(DialogLevel2DrvSetup);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(120, 130, 121, 20));
        label_7 = new QLabel(DialogLevel2DrvSetup);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 170, 371, 20));
        lineEdit_6 = new QLineEdit(DialogLevel2DrvSetup);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(118, 190, 241, 20));
        label_8 = new QLabel(DialogLevel2DrvSetup);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(40, 190, 71, 20));
        btnSetFilter = new QPushButton(DialogLevel2DrvSetup);
        btnSetFilter->setObjectName(QStringLiteral("btnSetFilter"));
        btnSetFilter->setGeometry(QRect(120, 230, 75, 23));
        btnTestConnection = new QPushButton(DialogLevel2DrvSetup);
        btnTestConnection->setObjectName(QStringLiteral("btnTestConnection"));
        btnTestConnection->setGeometry(QRect(200, 230, 101, 23));
        toolButton = new QToolButton(DialogLevel2DrvSetup);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(360, 190, 25, 19));

        retranslateUi(DialogLevel2DrvSetup);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogLevel2DrvSetup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogLevel2DrvSetup, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogLevel2DrvSetup);
    } // setupUi

    void retranslateUi(QDialog *DialogLevel2DrvSetup)
    {
        DialogLevel2DrvSetup->setWindowTitle(QApplication::translate("DialogLevel2DrvSetup", "Dialog", 0));
        label_2->setText(QApplication::translate("DialogLevel2DrvSetup", "Server URL : ", 0));
        lineEdit_2->setText(QApplication::translate("DialogLevel2DrvSetup", "localhost", 0));
        label_3->setText(QApplication::translate("DialogLevel2DrvSetup", "Description : ", 0));
        label_4->setText(QApplication::translate("DialogLevel2DrvSetup", "Server port : ", 0));
        lineEdit_3->setText(QApplication::translate("DialogLevel2DrvSetup", "9598", 0));
        label_5->setText(QApplication::translate("DialogLevel2DrvSetup", "Username :", 0));
        lineEdit_4->setText(QString());
        label_6->setText(QApplication::translate("DialogLevel2DrvSetup", "Password :", 0));
        lineEdit_5->setText(QString());
        label_7->setText(QApplication::translate("DialogLevel2DrvSetup", "Interface to use on server (leave blank to send events on all interfaces)", 0));
        lineEdit_6->setText(QString());
        label_8->setText(QApplication::translate("DialogLevel2DrvSetup", "Interface :", 0));
        btnSetFilter->setText(QApplication::translate("DialogLevel2DrvSetup", "Set Filter...", 0));
        btnTestConnection->setText(QApplication::translate("DialogLevel2DrvSetup", "Test Connection", 0));
        toolButton->setText(QApplication::translate("DialogLevel2DrvSetup", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogLevel2DrvSetup: public Ui_DialogLevel2DrvSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLEVEL2DRVSETUP_H
