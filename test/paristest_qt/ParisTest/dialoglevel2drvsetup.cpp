#include "dialoglevel2drvsetup.h"
#include "ui_dialoglevel2drvsetup.h"

DialogLevel2DrvSetup::DialogLevel2DrvSetup(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogLevel2DrvSetup)
{
  ui->setupUi(this);
}

DialogLevel2DrvSetup::~DialogLevel2DrvSetup()
{
  delete ui;
}
