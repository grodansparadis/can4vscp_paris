#include "dialogrelaysetup.h"
#include "ui_dialogrelaysetup.h"

DialogRelaySetup::DialogRelaySetup(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogRelaySetup)
{
  ui->setupUi(this);
}

DialogRelaySetup::~DialogRelaySetup()
{
  delete ui;
}
