#include "view/mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  tangle = new Tangle;
  cave = new Cave;
  ui->stackedWidget->addWidget(tangle);
  ui->stackedWidget->addWidget(cave);
  ui->stackedWidget->setCurrentWidget(tangle);
}

MainWindow::~MainWindow() {
  delete ui;
  delete tangle;
  delete cave;
}

void MainWindow::on_maze_clicked() {
  ui->stackedWidget->setCurrentWidget(tangle);
  ui->maze->setStyleSheet(
      "QPushButton { border: 1px solid rgb(161, 172, 186); background-color: "
      "rgb(206, 218, 232); color: rgb(64, 69, 75); } QPushButton:pressed "
      "{background-color: rgb(166, 204, 221);}");
  ui->cave->setStyleSheet(
      "QPushButton { border: 1px solid rgb(161, 172, 186); background-color: "
      "rgb(123, 145, 163); color: rgb(64, 69, 75); } QPushButton:pressed "
      "{background-color: rgb(166, 204, 221);}");
}

void MainWindow::on_cave_clicked() {
  ui->stackedWidget->setCurrentWidget(cave);
  ui->maze->setStyleSheet(
      "QPushButton { border: 1px solid rgb(161, 172, 186); background-color: "
      "rgb(123, 145, 163); color: rgb(64, 69, 75); } QPushButton:pressed "
      "{background-color: rgb(166, 204, 221);}");
  ui->cave->setStyleSheet(
      "QPushButton { border: 1px solid rgb(161, 172, 186); background-color: "
      "rgb(206, 218, 232); color: rgb(64, 69, 75); } QPushButton:pressed "
      "{background-color: rgb(166, 204, 221);}");
}
