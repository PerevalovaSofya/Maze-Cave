#include "tangle.h"

#include "ui_tangle.h"

Tangle::Tangle(QWidget *parent) : QWidget(parent), ui(new Ui::Tangle) {
  ui->setupUi(this);
}

Tangle::~Tangle() { delete ui; }
void Tangle::on_btn_generate_clicked() {
  ui->render_area->Generate(ui->width_box->value(), ui->height_box->value());
}

void Tangle::on_btn_load_clicked() {
  QString FileName = QFileDialog::getOpenFileName(
      this, "Open a file", QDir::homePath(), "txt (*.txt)");

  ui->render_area->LoadGenerateMaze(FileName.toStdString());
  ui->width_box->setValue(ui->render_area->GetMazeCols());
  ui->height_box->setValue(ui->render_area->GetMazeRows());
}
