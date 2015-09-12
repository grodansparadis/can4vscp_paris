/********************************************************************************
** Form generated from reading UI file 'dialogselectdriverlevel.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSELECTDRIVERLEVEL_H
#define UI_DIALOGSELECTDRIVERLEVEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DialogSelectDriverLevel
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *comboBoxSelectLevel;

    void setupUi(QDialog *DialogSelectDriverLevel)
    {
        if (DialogSelectDriverLevel->objectName().isEmpty())
            DialogSelectDriverLevel->setObjectName(QStringLiteral("DialogSelectDriverLevel"));
        DialogSelectDriverLevel->resize(233, 103);
        buttonBox = new QDialogButtonBox(DialogSelectDriverLevel);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 60, 161, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        comboBoxSelectLevel = new QComboBox(DialogSelectDriverLevel);
        comboBoxSelectLevel->setObjectName(QStringLiteral("comboBoxSelectLevel"));
        comboBoxSelectLevel->setGeometry(QRect(10, 20, 211, 22));

        retranslateUi(DialogSelectDriverLevel);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSelectDriverLevel, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSelectDriverLevel, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogSelectDriverLevel);
    } // setupUi

    void retranslateUi(QDialog *DialogSelectDriverLevel)
    {
        DialogSelectDriverLevel->setWindowTitle(QApplication::translate("DialogSelectDriverLevel", "Dialog", 0));
        comboBoxSelectLevel->clear();
        comboBoxSelectLevel->insertItems(0, QStringList()
         << QApplication::translate("DialogSelectDriverLevel", "Level I (CANAL) Driver", 0)
         << QApplication::translate("DialogSelectDriverLevel", "Level II Driver", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class DialogSelectDriverLevel: public Ui_DialogSelectDriverLevel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSELECTDRIVERLEVEL_H
