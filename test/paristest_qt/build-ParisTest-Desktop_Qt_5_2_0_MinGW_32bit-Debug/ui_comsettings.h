/********************************************************************************
** Form generated from reading UI file 'comsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMSETTINGS_H
#define UI_COMSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ComSettings
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ComSettings)
    {
        if (ComSettings->objectName().isEmpty())
            ComSettings->setObjectName(QStringLiteral("ComSettings"));
        ComSettings->resize(400, 300);
        buttonBox = new QDialogButtonBox(ComSettings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(ComSettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), ComSettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ComSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(ComSettings);
    } // setupUi

    void retranslateUi(QDialog *ComSettings)
    {
        ComSettings->setWindowTitle(QApplication::translate("ComSettings", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class ComSettings: public Ui_ComSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMSETTINGS_H
