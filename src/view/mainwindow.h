#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>

#include "cave.h"
#include "model/maze.h"
#include "model/throughmaze.h"
#include "model/grotto.h"

#include "tangle.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);

  ~MainWindow();
 private slots:
  void on_maze_clicked();
  void on_cave_clicked();

 private:
  Ui::MainWindow *ui;
  Tangle *tangle;
  Cave *cave;
};

#endif  // MAINWINDOW_H
