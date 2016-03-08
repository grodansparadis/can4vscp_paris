#ifndef DIALOGCANALSETUP_H
#define DIALOGCANALSETUP_H

#include <QDialog>

namespace Ui {
  class DialogCanalSetup;
}

class DialogCanalSetup : public QDialog
{
  Q_OBJECT

public:
  explicit DialogCanalSetup(QWidget *parent = 0);
  ~DialogCanalSetup();

private:
  Ui::DialogCanalSetup *ui;
};

#endif // DIALOGCANALSETUP_H
