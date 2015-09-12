#include "dialoginterfaceselect.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/////////////////////////////////////////////////////////////////////////////
/// on_actionExit_triggered
///
/// \brief Terminate application
///
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

////////////////////////////////////////////////////////////////////////////
/// on_actionConnect_triggered
///
/// \brief Open communication dilaog
///
///
void MainWindow::on_actionConnect_triggered()
{
    DialogInterfaceSelect dlg(this);
    dlg.setModal( true );
    dlg.exec();
}
