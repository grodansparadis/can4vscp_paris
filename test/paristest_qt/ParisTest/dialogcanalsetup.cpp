#include "dialogcanalsetup.h"
#include "ui_dialogcanalsetup.h"

DialogCanalSetup::DialogCanalSetup(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogCanalSetup)
{
  ui->setupUi(this);
}

DialogCanalSetup::~DialogCanalSetup()
{
  delete ui;
}
