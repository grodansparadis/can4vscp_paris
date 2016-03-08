/********************************************************************************
** Form generated from reading UI file 'dialogrelaysetup.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGRELAYSETUP_H
#define UI_DIALOGRELAYSETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DialogRelaySetup
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogRelaySetup)
    {
        if (DialogRelaySetup->objectName().isEmpty())
            DialogRelaySetup->setObjectName(QStringLiteral("DialogRelaySetup"));
        DialogRelaySetup->resize(400, 357);
        buttonBox = new QDialogButtonBox(DialogRelaySetup);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 310, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(DialogRelaySetup);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogRelaySetup, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogRelaySetup, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogRelaySetup);
    } // setupUi

    void retranslateUi(QDialog *DialogRelaySetup)
    {
        DialogRelaySetup->setWindowTitle(QApplication::translate("DialogRelaySetup", "Relay Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogRelaySetup: public Ui_DialogRelaySetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGRELAYSETUP_H
