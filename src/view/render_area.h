#ifndef RENDER_AREA_H
#define RENDER_AREA_H

#include <QDir>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QWidget>
#include <fstream>
#include <iostream>
#include <vector>

#include "view/mainwindow.h"

class RenderArea : public QWidget {
  Q_OBJECT

 public:
  explicit RenderArea(QWidget *parent = nullptr);
  void ClearImage(QImage &image);
  void ClearArea();
  void Generate(int width, int height);
  void LoadGenerateMaze(std::string maze);
  void LoadGenerateCave(std::string cave);
  void DrawMaze();
  void DrawPacman();
  void DrawCave();
  int GetMazeRows() { return maze_.getRows(); }
  int GetMazeCols() { return maze_.getCols(); }
  void mousePressEvent(QMouseEvent *event) override;
  void SetBirth(int birth) { birth_ = birth; }
  void SetDeath(int death) { death_ = death; }
  void Iterate();
  void StartTimer(int ms);
  void StopTimer() { timer_->stop(); }

  ~RenderArea();

 protected:
  void paintEvent(QPaintEvent *event) override;

 private slots:
  void CaveStep();

 private:
  QImage image_;
  QImage pacman_;
  QImage cave_;
  QTimer *timer_;
  int birth_{};
  int death_{};
  Qt::MouseButton mBtn_;
  std::pair<int, int> start_pos_;
  std::pair<int, int> goal_;
  bool left_click_;
  bool right_click_;
  Maze maze_;
  Maze_Walker maze_walker_;
  Grotto grotto_;
  double NodeWidth_;
  double NodeHeight_;
};

#endif  // RENDER_AREA_H
