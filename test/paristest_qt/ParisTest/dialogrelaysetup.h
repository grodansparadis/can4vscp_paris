#ifndef DIALOGRELAYSETUP_H
#define DIALOGRELAYSETUP_H

#include <QDialog>

namespace Ui {
  class DialogRelaySetup;
}

class DialogRelaySetup : public QDialog
{
  Q_OBJECT

public:
  explicit DialogRelaySetup(QWidget *parent = 0);
  ~DialogRelaySetup();

private:
  Ui::DialogRelaySetup *ui;
};

#endif // DIALOGRELAYSETUP_H
