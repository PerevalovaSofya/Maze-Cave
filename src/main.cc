#include <QApplication>

#include "model/maze.h"
#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication qapp(argc, argv);

  MainWindow main_windom;
  main_windom.show();
  return qapp.exec();
}
