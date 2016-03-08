#include "comsettings.h"
#include "ui_comsettings.h"

ComSettings::ComSettings(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ComSettings)
{
  ui->setupUi(this);
}

ComSettings::~ComSettings()
{
  delete ui;
}
