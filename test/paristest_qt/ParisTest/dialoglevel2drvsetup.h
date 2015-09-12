#ifndef DIALOGLEVEL2DRVSETUP_H
#define DIALOGLEVEL2DRVSETUP_H

#include <QDialog>

namespace Ui {
  class DialogLevel2DrvSetup;
}

class DialogLevel2DrvSetup : public QDialog
{
  Q_OBJECT

public:
  explicit DialogLevel2DrvSetup(QWidget *parent = 0);
  ~DialogLevel2DrvSetup();

private:
  Ui::DialogLevel2DrvSetup *ui;
};

#endif // DIALOGLEVEL2DRVSETUP_H
