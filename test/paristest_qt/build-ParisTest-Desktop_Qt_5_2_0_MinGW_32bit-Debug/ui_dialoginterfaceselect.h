/********************************************************************************
** Form generated from reading UI file 'dialoginterfaceselect.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGINTERFACESELECT_H
#define UI_DIALOGINTERFACESELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogInterfaceSelect
{
public:
    QDialogButtonBox *buttonBox;
    QTreeView *treeViewInterfaces;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QPushButton *btnClone;

    void setupUi(QDialog *DialogInterfaceSelect)
    {
        if (DialogInterfaceSelect->objectName().isEmpty())
            DialogInterfaceSelect->setObjectName(QStringLiteral("DialogInterfaceSelect"));
        DialogInterfaceSelect->resize(400, 300);
        DialogInterfaceSelect->setModal(true);
        buttonBox = new QDialogButtonBox(DialogInterfaceSelect);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(120, 260, 161, 32));
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        treeViewInterfaces = new QTreeView(DialogInterfaceSelect);
        treeViewInterfaces->setObjectName(QStringLiteral("treeViewInterfaces"));
        treeViewInterfaces->setGeometry(QRect(10, 10, 281, 241));
        treeViewInterfaces->setEditTriggers(QAbstractItemView::NoEditTriggers);
        treeViewInterfaces->setProperty("showDropIndicator", QVariant(true));
        treeViewInterfaces->setRootIsDecorated(true);
        treeViewInterfaces->header()->setVisible(false);
        verticalLayoutWidget = new QWidget(DialogInterfaceSelect);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(300, 10, 91, 131));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnAdd = new QPushButton(verticalLayoutWidget);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));

        verticalLayout->addWidget(btnAdd);

        btnEdit = new QPushButton(verticalLayoutWidget);
        btnEdit->setObjectName(QStringLiteral("btnEdit"));

        verticalLayout->addWidget(btnEdit);

        btnDelete = new QPushButton(verticalLayoutWidget);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));

        verticalLayout->addWidget(btnDelete);

        btnClone = new QPushButton(verticalLayoutWidget);
        btnClone->setObjectName(QStringLiteral("btnClone"));

        verticalLayout->addWidget(btnClone);


        retranslateUi(DialogInterfaceSelect);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogInterfaceSelect, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogInterfaceSelect, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogInterfaceSelect);
    } // setupUi

    void retranslateUi(QDialog *DialogInterfaceSelect)
    {
        DialogInterfaceSelect->setWindowTitle(QApplication::translate("DialogInterfaceSelect", "Select interface to use", 0));
#ifndef QT_NO_TOOLTIP
        btnAdd->setToolTip(QApplication::translate("DialogInterfaceSelect", "<html><head/><body><p>Add new interface</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnAdd->setText(QApplication::translate("DialogInterfaceSelect", "Add...", 0));
#ifndef QT_NO_TOOLTIP
        btnEdit->setToolTip(QApplication::translate("DialogInterfaceSelect", "<html><head/><body><p>Edit selected interface</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnEdit->setText(QApplication::translate("DialogInterfaceSelect", "Edit...", 0));
#ifndef QT_NO_TOOLTIP
        btnDelete->setToolTip(QApplication::translate("DialogInterfaceSelect", "<html><head/><body><p>Delete selected interface</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnDelete->setText(QApplication::translate("DialogInterfaceSelect", "Delete", 0));
#ifndef QT_NO_TOOLTIP
        btnClone->setToolTip(QApplication::translate("DialogInterfaceSelect", "<html><head/><body><p>Make a copy of the selected interface</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        btnClone->setText(QApplication::translate("DialogInterfaceSelect", "Clone", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogInterfaceSelect: public Ui_DialogInterfaceSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGINTERFACESELECT_H
