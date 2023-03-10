#include "cave.h"

#include "ui_cave.h"

Cave::Cave(QWidget *parent) : QWidget(parent), ui(new Ui::Cave) {
  ui->setupUi(this);
}

Cave::~Cave() { delete ui; }

void Cave::on_btn_load_clicked() {
  QString FileName = QFileDialog::getOpenFileName(
      this, "Open a file", QDir::homePath(), "txt (*.txt)");
  ui->render_area->LoadGenerateCave(FileName.toStdString());
}

void Cave::on_next_step_clicked()
{
    ui->render_area->SetBirth(ui->birth->value());
    ui->render_area->SetDeath(ui->death->value());
    ui->render_area->Iterate();
}


void Cave::on_start_timer_clicked()
{
    ui->render_area->SetBirth(ui->birth->value());
    ui->render_area->SetDeath(ui->death->value());
    ui->render_area->StartTimer(ui->timer_count->value());
}


void Cave::on_stop_timer_clicked()
{
    ui->render_area->StopTimer();
}

