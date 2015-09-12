#ifndef DIALOGSELECTDRIVERLEVEL_H
#define DIALOGSELECTDRIVERLEVEL_H

#include <QDialog>

namespace Ui {
  class DialogSelectDriverLevel;
}

class DialogSelectDriverLevel : public QDialog
{
  Q_OBJECT

public:
  explicit DialogSelectDriverLevel(QWidget *parent = 0);
  ~DialogSelectDriverLevel();

private:
  Ui::DialogSelectDriverLevel *ui;
};

#endif // DIALOGSELECTDRIVERLEVEL_H
