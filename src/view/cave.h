#ifndef CAVE_H
#define CAVE_H

#include <QWidget>

namespace Ui {
class Cave;
}

class Cave : public QWidget {
  Q_OBJECT

 public:
  explicit Cave(QWidget *parent = nullptr);
  ~Cave();

 private slots:
  void on_btn_load_clicked();
  void on_next_step_clicked();
  void on_start_timer_clicked();
  void on_stop_timer_clicked();

 private:
  Ui::Cave *ui;
};

#endif  // CAVE_H
