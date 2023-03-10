#include "render_area.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent),
      image_(QSize(500, 500), QImage::Format_ARGB32),
      pacman_(QSize(500, 500), QImage::Format_ARGB32),
      cave_(QSize(500, 500), QImage::Format_ARGB32),
      timer_(new QTimer(this))

{
  left_click_ = false;
  right_click_ = false;
}

void RenderArea::ClearImage(QImage &image) {
  image.fill(QColor(0, 0, 0, 0));

  update();
}

void RenderArea::ClearArea() {
  ClearImage(image_);
  ClearImage(pacman_);
  ClearImage(cave_);
}

void RenderArea::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter render_area(this);
  QRect dirtyRect = event->rect();
  render_area.drawImage(dirtyRect, image_, dirtyRect);
  render_area.drawImage(dirtyRect, pacman_, dirtyRect);
  render_area.drawImage(dirtyRect, cave_, dirtyRect);
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
  ClearImage(pacman_);
  if (event->button() == Qt::LeftButton) {
    QPoint start_point_ = event->pos();
    start_pos_.first = start_point_.x() / NodeWidth_;
    start_pos_.second = start_point_.y() / NodeHeight_;
    left_click_ = true;

  } else if (event->button() == Qt::RightButton) {
    QPoint goal_point = event->pos();
    goal_.first = goal_point.x() / NodeWidth_;
    goal_.second = goal_point.y() / NodeHeight_;
    right_click_ = true;
  }

  if (left_click_ && right_click_) {
    DrawPacman();
    left_click_ = false;
    right_click_ = false;
  }
  update();
}

void RenderArea::Iterate() { CaveStep(); }

void RenderArea::CaveStep() {
  grotto_.SetLiveParametrs(birth_, death_);
  grotto_.ChangeGrotto();
  DrawCave();
}

void RenderArea::StartTimer(int ms) {
  timer_->start(ms);
  connect(timer_, SIGNAL(timeout()), this, SLOT(CaveStep()));
}

void RenderArea::Generate(int width, int height) {
  ClearArea();

  maze_.InitMaze(width, height);
  NodeWidth_ = 500.0 / maze_.getCols();
  NodeHeight_ = 500.0 / maze_.getRows();
  QString save_filename = QDir::homePath() + "/new_maze_1.txt";
  maze_.SaveMaze(save_filename.toStdString());
  DrawMaze();
}

void RenderArea::LoadGenerateMaze(std::string maze) {
  ClearArea();

  maze_.LoadMaze(maze);
  NodeWidth_ = 500.0 / maze_.getCols();
  NodeHeight_ = 500.0 / maze_.getRows();
  QString save_filename = QDir::homePath() + "/new_maze_1.txt";
  maze_.SaveMaze(save_filename.toStdString());
  DrawMaze();
}

void RenderArea::LoadGenerateCave(std::string cave) {
  ClearArea();
  grotto_.LoadGrotto(cave);
  NodeWidth_ = 500.0 / grotto_.GetCols();
  NodeHeight_ = 500.0 / grotto_.GetRows();
  DrawCave();
}

void RenderArea::DrawMaze() {
  QPainter painter(&image_);
  painter.setPen(QPen(Qt::black, 2));
  painter.drawLine(0, 0, 500, 0);
  painter.drawLine(0, 0, 0, 500);
  painter.drawLine(500, 0, 500, 500);
  painter.drawLine(0, 500, 500, 500);

  for (int i = 0; i < maze_.getRows(); i++) {
    for (int j = 0; j < maze_.getCols(); j++) {
      int x0 = NodeWidth_ * j;
      int y0 = NodeHeight_ * i;
      int x1 = NodeWidth_ * (j + 1);
      int y1 = NodeHeight_ * (i + 1);

      if (maze_.CheckRight(i, j)) {
        painter.drawLine(x1, y0, x1, y1);  // vert
      }

      if (maze_.CheckDown(i, j)) {
        painter.drawLine(x0, y1, x1, y1);  // hor
      }
    }
  }
  update();
}

void RenderArea::DrawPacman() {
  QString load_filename = QDir::homePath() + "/new_maze_1.txt";
  maze_walker_.GoToWalk(load_filename.toStdString(), start_pos_, goal_);
  std::vector<std::pair<int, int>> way_walker_ =
      maze_walker_.ClearWay(start_pos_, goal_);
  QPainter painter(&pacman_);
  painter.setPen(QPen(QColor(254, 130, 0), 2));

  for (unsigned i = 0; i < way_walker_.size() - 1; i++) {
    painter.drawLine(way_walker_[i].first * NodeWidth_ + NodeWidth_ / 2,
                     way_walker_[i].second * NodeHeight_ + NodeHeight_ / 2,
                     way_walker_[i + 1].first * NodeWidth_ + NodeWidth_ / 2,
                     way_walker_[i + 1].second * NodeHeight_ + NodeHeight_ / 2);
  }
  update();
}
void RenderArea::DrawCave() {
  QPainter painter(&cave_);
  painter.setPen(QPen(Qt::black, 2));
  painter.drawLine(0, 0, 500, 0);
  painter.drawLine(0, 0, 0, 500);
  painter.drawLine(500, 0, 500, 500);
  painter.drawLine(0, 500, 500, 500);

  for (int i = 0; i < grotto_.GetRows(); i++) {
    for (int j = 0; j < grotto_.GetCols(); j++) {
      int x0 = NodeWidth_ * j;
      int y0 = NodeHeight_ * i;

      if (grotto_.CheckCell(i, j)) {
        painter.fillRect(x0, y0, NodeWidth_, NodeHeight_, Qt::black);
      }
    }
  }
  update();
}

RenderArea::~RenderArea() { timer_->stop(); }
