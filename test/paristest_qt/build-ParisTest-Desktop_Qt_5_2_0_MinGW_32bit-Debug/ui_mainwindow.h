/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionExit;
    QWidget *centralWidget;
    QGroupBox *groupBoxRelay1;
    QPushButton *pushButtonRelayStatus1;
    QToolButton *toolButtonSettingsRelay1;
    QGroupBox *groupBoxRelay1_2;
    QPushButton *pushButtonRelayStatus1_2;
    QToolButton *toolButtonSettingsRelay1_2;
    QGroupBox *groupBoxRelay1_3;
    QPushButton *pushButtonRelayStatus1_3;
    QToolButton *toolButtonSettingsRelay1_3;
    QGroupBox *groupBoxRelay1_4;
    QPushButton *pushButtonRelayStatus1_4;
    QToolButton *toolButtonSettingsRelay1_4;
    QGroupBox *groupBoxRelay1_6;
    QPushButton *pushButtonRelayStatus1_6;
    QToolButton *toolButtonSettingsRelay1_6;
    QGroupBox *groupBoxRelay1_7;
    QPushButton *pushButtonRelayStatus1_7;
    QToolButton *toolButtonSettingsRelay1_7;
    QGroupBox *groupBoxRelay1_8;
    QPushButton *pushButtonRelayStatus1_8;
    QToolButton *toolButtonSettingsRelay1_8;
    QLabel *labelConnectionState;
    QMenuBar *menuBar;
    QMenu *menuParis_Relay_Test;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(532, 195);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBoxRelay1 = new QGroupBox(centralWidget);
        groupBoxRelay1->setObjectName(QStringLiteral("groupBoxRelay1"));
        groupBoxRelay1->setGeometry(QRect(10, 10, 121, 61));
        pushButtonRelayStatus1 = new QPushButton(groupBoxRelay1);
        pushButtonRelayStatus1->setObjectName(QStringLiteral("pushButtonRelayStatus1"));
        pushButtonRelayStatus1->setGeometry(QRect(10, 20, 75, 23));
        pushButtonRelayStatus1->setCheckable(true);
        pushButtonRelayStatus1->setFlat(false);
        toolButtonSettingsRelay1 = new QToolButton(groupBoxRelay1);
        toolButtonSettingsRelay1->setObjectName(QStringLiteral("toolButtonSettingsRelay1"));
        toolButtonSettingsRelay1->setGeometry(QRect(90, 20, 25, 21));
        groupBoxRelay1_2 = new QGroupBox(centralWidget);
        groupBoxRelay1_2->setObjectName(QStringLiteral("groupBoxRelay1_2"));
        groupBoxRelay1_2->setGeometry(QRect(140, 10, 121, 61));
        pushButtonRelayStatus1_2 = new QPushButton(groupBoxRelay1_2);
        pushButtonRelayStatus1_2->setObjectName(QStringLiteral("pushButtonRelayStatus1_2"));
        pushButtonRelayStatus1_2->setGeometry(QRect(10, 20, 75, 23));
        pushButtonRelayStatus1_2->setCheckable(true);
        pushButtonRelayStatus1_2->setFlat(false);
        toolButtonSettingsRelay1_2 = new QToolButton(groupBoxRelay1_2);
        toolButtonSettingsRelay1_2->setObjectName(QStringLiteral("toolButtonSettingsRelay1_2"));
        toolButtonSettingsRelay1_2->setGeometry(QRect(90, 20, 25, 21));
        groupBoxRelay1_3 = new QGroupBox(centralWidget);
        groupBoxRelay1_3->setObjectName(QStringLiteral("groupBoxRelay1_3"));
        groupBoxRelay1_3->setGeometry(QRect(270, 10, 121, 61));
        pushButtonRelayStatus1_3 = new QPushButton(groupBoxRelay1_3);
        pushButtonRelayStatus1_3->setObjectName(QStringLiteral("pushButtonRelayStatus1_3"));
        pushButtonRelayStatus1_3->setGeometry(QRect(10, 20, 75, 23));
        pushButtonRelayStatus1_3->setCheckable(true);
        pushButtonRelayStatus1_3->setFlat(false);
        toolButtonSettingsRelay1_3 = new QToolButton(groupBoxRelay1_3);
        toolButtonSettingsRelay1_3->setObjectName(QStringLiteral("toolButtonSettingsRelay1_3"));
        toolButtonSettingsRelay1_3->setGeometry(QRect(90, 20, 25, 21));
        groupBoxRelay1_4 = new QGroupBox(centralWidget);
        groupBoxRelay1_4->setObjectName(QStringLiteral("groupBoxRelay1_4"));
        groupBoxRelay1_4->setGeometry(QRect(400, 10, 121, 61));
        pushButtonRelayStatus1_4 = new QPushButton(groupBoxRelay1_4);
        pushButtonRelayStatus1_4->setObjectName(QStringLiteral("pushButtonRelayStatus1_4"));
        pushButtonRelayStatus1_4->setGeometry(QRect(10, 20, 75, 23));
        pushButtonRelayStatus1_4->setCheckable(true);
        pushButtonRelayStatus1_4->setFlat(false);
        toolButtonSettingsRelay1_4 = new QToolButton(groupBoxRelay1_4);
        toolButtonSettingsRelay1_4->setObjectName(QStringLiteral("toolButtonSettingsRelay1_4"));
        toolButtonSettingsRelay1_4->setGeometry(QRect(90, 20, 25, 21));
        groupBoxRelay1_6 = new QGroupBox(centralWidget);
        groupBoxRelay1_6->setObjectName(QStringLiteral("groupBoxRelay1_6"));
        groupBoxRelay1_6->setGeometry(QRect(10, 80, 121, 61));
        pushButtonRelayStatus1_6 = new QPushButton(groupBoxRelay1_6);
        pushButtonRelayStatus1_6->setObjectName(QStringLiteral("pushButtonRelayStatus1_6"));
        pushButtonRelayStatus1_6->setGeometry(QRect(10, 20, 75, 23));
        pushButtonRelayStatus1_6->setCheckable(true);
        pushButtonRelayStatus1_6->setFlat(false);
        toolButtonSettingsRelay1_6 = new QToolButton(groupBoxRelay1_6);
        toolButtonSettingsRelay1_6->setObjectName(QStringLiteral("toolButtonSettingsRelay1_6"));
        toolButtonSettingsRelay1_6->setGeometry(QRect(90, 20, 25, 21));
        groupBoxRelay1_7 = new QGroupBox(centralWidget);
        groupBoxRelay1_7->setObjectName(QStringLiteral("groupBoxRelay1_7"));
        groupBoxRelay1_7->setGeometry(QRect(140, 80, 121, 61));
        pushButtonRelayStatus1_7 = new QPushButton(groupBoxRelay1_7);
        pushButtonRelayStatus1_7->setObjectName(QStringLiteral("pushButtonRelayStatus1_7"));
        pushButtonRelayStatus1_7->setGeometry(QRect(10, 20, 75, 23));
        pushButtonRelayStatus1_7->setCheckable(true);
        pushButtonRelayStatus1_7->setFlat(false);
        toolButtonSettingsRelay1_7 = new QToolButton(groupBoxRelay1_7);
        toolButtonSettingsRelay1_7->setObjectName(QStringLiteral("toolButtonSettingsRelay1_7"));
        toolButtonSettingsRelay1_7->setGeometry(QRect(90, 20, 25, 21));
        groupBoxRelay1_8 = new QGroupBox(centralWidget);
        groupBoxRelay1_8->setObjectName(QStringLiteral("groupBoxRelay1_8"));
        groupBoxRelay1_8->setGeometry(QRect(270, 80, 121, 61));
        pushButtonRelayStatus1_8 = new QPushButton(groupBoxRelay1_8);
        pushButtonRelayStatus1_8->setObjectName(QStringLiteral("pushButtonRelayStatus1_8"));
        pushButtonRelayStatus1_8->setGeometry(QRect(10, 20, 75, 23));
        pushButtonRelayStatus1_8->setCheckable(true);
        pushButtonRelayStatus1_8->setFlat(false);
        toolButtonSettingsRelay1_8 = new QToolButton(groupBoxRelay1_8);
        toolButtonSettingsRelay1_8->setObjectName(QStringLiteral("toolButtonSettingsRelay1_8"));
        toolButtonSettingsRelay1_8->setGeometry(QRect(90, 20, 25, 21));
        labelConnectionState = new QLabel(centralWidget);
        labelConnectionState->setObjectName(QStringLiteral("labelConnectionState"));
        labelConnectionState->setGeometry(QRect(470, 80, 46, 51));
        labelConnectionState->setPixmap(QPixmap(QString::fromUtf8(":/icons/network-disconnected")));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 532, 21));
        menuParis_Relay_Test = new QMenu(menuBar);
        menuParis_Relay_Test->setObjectName(QStringLiteral("menuParis_Relay_Test"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuParis_Relay_Test->menuAction());
        menuParis_Relay_Test->addAction(actionConnect);
        menuParis_Relay_Test->addSeparator();
        menuParis_Relay_Test->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Paris Relay Module Test", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect...", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        groupBoxRelay1->setTitle(QApplication::translate("MainWindow", "Relay 1", 0));
#ifndef QT_NO_STATUSTIP
        pushButtonRelayStatus1->setStatusTip(QApplication::translate("MainWindow", "Status for relay", 0));
#endif // QT_NO_STATUSTIP
        pushButtonRelayStatus1->setText(QApplication::translate("MainWindow", "On", 0));
        toolButtonSettingsRelay1->setText(QApplication::translate("MainWindow", "...", 0));
        groupBoxRelay1_2->setTitle(QApplication::translate("MainWindow", "Relay 2", 0));
#ifndef QT_NO_STATUSTIP
        pushButtonRelayStatus1_2->setStatusTip(QApplication::translate("MainWindow", "Status for relay", 0));
#endif // QT_NO_STATUSTIP
        pushButtonRelayStatus1_2->setText(QApplication::translate("MainWindow", "On", 0));
        toolButtonSettingsRelay1_2->setText(QApplication::translate("MainWindow", "...", 0));
        groupBoxRelay1_3->setTitle(QApplication::translate("MainWindow", "Relay 3", 0));
#ifndef QT_NO_STATUSTIP
        pushButtonRelayStatus1_3->setStatusTip(QApplication::translate("MainWindow", "Status for relay", 0));
#endif // QT_NO_STATUSTIP
        pushButtonRelayStatus1_3->setText(QApplication::translate("MainWindow", "On", 0));
        toolButtonSettingsRelay1_3->setText(QApplication::translate("MainWindow", "...", 0));
        groupBoxRelay1_4->setTitle(QApplication::translate("MainWindow", "Relay 4", 0));
#ifndef QT_NO_STATUSTIP
        pushButtonRelayStatus1_4->setStatusTip(QApplication::translate("MainWindow", "Status for relay", 0));
#endif // QT_NO_STATUSTIP
        pushButtonRelayStatus1_4->setText(QApplication::translate("MainWindow", "On", 0));
        toolButtonSettingsRelay1_4->setText(QApplication::translate("MainWindow", "...", 0));
        groupBoxRelay1_6->setTitle(QApplication::translate("MainWindow", "Relay 5", 0));
#ifndef QT_NO_STATUSTIP
        pushButtonRelayStatus1_6->setStatusTip(QApplication::translate("MainWindow", "Status for relay", 0));
#endif // QT_NO_STATUSTIP
        pushButtonRelayStatus1_6->setText(QApplication::translate("MainWindow", "On", 0));
        toolButtonSettingsRelay1_6->setText(QApplication::translate("MainWindow", "...", 0));
        groupBoxRelay1_7->setTitle(QApplication::translate("MainWindow", "Relay 6", 0));
#ifndef QT_NO_STATUSTIP
        pushButtonRelayStatus1_7->setStatusTip(QApplication::translate("MainWindow", "Status for relay", 0));
#endif // QT_NO_STATUSTIP
        pushButtonRelayStatus1_7->setText(QApplication::translate("MainWindow", "On", 0));
        toolButtonSettingsRelay1_7->setText(QApplication::translate("MainWindow", "...", 0));
        groupBoxRelay1_8->setTitle(QApplication::translate("MainWindow", "Relay 7", 0));
#ifndef QT_NO_STATUSTIP
        pushButtonRelayStatus1_8->setStatusTip(QApplication::translate("MainWindow", "Status for relay", 0));
#endif // QT_NO_STATUSTIP
        pushButtonRelayStatus1_8->setText(QApplication::translate("MainWindow", "On", 0));
        toolButtonSettingsRelay1_8->setText(QApplication::translate("MainWindow", "...", 0));
        labelConnectionState->setText(QString());
        menuParis_Relay_Test->setTitle(QApplication::translate("MainWindow", "Paris Relay Test", 0));
        mainToolBar->setWindowTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
