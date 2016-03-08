#include "dialogselectdriverlevel.h"
#include "ui_dialogselectdriverlevel.h"

DialogSelectDriverLevel::DialogSelectDriverLevel(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogSelectDriverLevel)
{
  ui->setupUi(this);
}

DialogSelectDriverLevel::~DialogSelectDriverLevel()
{
  delete ui;
}
