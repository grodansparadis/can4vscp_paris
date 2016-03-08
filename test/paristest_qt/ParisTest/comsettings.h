#ifndef COMSETTINGS_H
#define COMSETTINGS_H

#include <QDialog>

namespace Ui {
  class ComSettings;
}

class ComSettings : public QDialog
{
  Q_OBJECT

public:
  explicit ComSettings(QWidget *parent = 0);
  ~ComSettings();

private:
  Ui::ComSettings *ui;
};

#endif // COMSETTINGS_H
