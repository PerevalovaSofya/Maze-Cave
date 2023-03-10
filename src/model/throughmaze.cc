#include "throughmaze.h"


void Maze_Walker::LoadMaze(std::string maze) {
  std::ifstream getmaze(maze, std::ios::in);
  if (getmaze.good()) {
    std::string line;
    getline(getmaze, line);

    rows_ = (atof(&line[0]));
    int ind = line.find(' ');
    cols_ = (atof(&line[ind + 1]));

    InitMaze();

    for (int i = 0; i < rows_; i++) {
      getline(getmaze, line);
      for (int j = 0, d = 0; (size_t)j < line.size(); j += 2, d++) {
        if (atof(&line[j]) == 0) maze_[i][d].right_border_ = false;
        if (atof(&line[j]) == 1) maze_[i][d].right_border_ = true;
      }
    }

    getline(getmaze, line);

    for (int i = 0; i < rows_; i++) {
      getline(getmaze, line);
      for (int j = 0, d = 0; (size_t)j < line.size(); j += 2, d++) {
        if (atof(&line[j]) == 0) maze_[i][d].down_border_ = false;
        if (atof(&line[j]) == 1) maze_[i][d].down_border_ = true;
      }
    }
  }
  SetLeftAndDown();
}

void Maze_Walker::InitMaze() {
  maze_.resize(rows_);
  for (int i = 0; i < rows_; i++) {
    maze_[i].resize(cols_);
    maze_[i][0].left_border_ = true;
  }

  for (int i = 0; i < cols_; i++) {
    maze_[0][i].upper_border_ = true;
  }
}

void Maze_Walker::SetLeftAndDown() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (j != 0 && maze_[i][j - 1].right_border_ == true) {
        maze_[i][j].left_border_ = true;
      }
      if (i != 0 && maze_[i - 1][j].down_border_ == true) {
        maze_[i][j].upper_border_ = true;
      }
    }
  }
}

void Maze_Walker::SetCoords() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      maze_[i][j].coords.first = j;
      maze_[i][j].coords.second = i;
      maze_[i][j].value_ = 0;
    }
  }
}

void Maze_Walker::SetNotNull() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (maze_[i][j].value_ == 0) {
        maze_[i][j].value_ = 99999;
      }
    }
  }
}

void Maze_Walker::SearchWay(std::pair<int, int> start_pos,
                            std::pair<int, int> goal) {
  cur = start_pos;
  maze_[cur.second][cur.first].value_ = -1;
  while (cur != goal) {
    PossibleWays(cur);
    cur = way_.back();
    way_.pop_back();
  }
}

void Maze_Walker::CheckBorders(std::pair<int, int> cur) {
  go_down = go_left = go_right = go_up = false;

  if (maze_[cur.second][cur.first].down_border_ == false) {
    go_down = true;
  }
  if (maze_[cur.second][cur.first].right_border_ == false) {
    go_right = true;
  }
  if (maze_[cur.second][cur.first].left_border_ == false) {
    go_left = true;
  }
  if (maze_[cur.second][cur.first].upper_border_ == false) {
    go_up = true;
  }
}

void Maze_Walker::PossibleWays(std::pair<int, int> cur) {
  CheckBorders(cur);
  if (go_down == true && maze_[cur.second + 1][cur.first].value_ == 0) {
    maze_[cur.second + 1][cur.first].value_ = step + 1;
    way_.push_back(maze_[cur.second + 1][cur.first].coords);
  }

  if (go_right == true && maze_[cur.second][cur.first + 1].value_ == 0) {
    maze_[cur.second][cur.first + 1].value_ = step + 1;
    way_.push_back(maze_[cur.second][cur.first + 1].coords);
  }

  if (go_left == true && maze_[cur.second][cur.first - 1].value_ == 0) {
    maze_[cur.second][cur.first - 1].value_ = step + 1;
    way_.push_back(maze_[cur.second][cur.first - 1].coords);
  }

  if (go_up == true && maze_[cur.second - 1][cur.first].value_ == 0) {
    maze_[cur.second - 1][cur.first].value_ = step + 1;
    way_.push_back(maze_[cur.second - 1][cur.first].coords);
  }
  step++;
}

std::vector<std::pair<int, int>> Maze_Walker::ClearWay(
    std::pair<int, int> start_pos, std::pair<int, int> goal) {
  way_.clear();
  clear_way_.clear();
  cur = goal;

  SetNotNull();

  while (cur != start_pos) {
    PossibleWays(cur);
    auto tmp = maze_[cur.second][cur.first].value_;

    if (go_down == true && tmp > maze_[cur.second + 1][cur.first].value_) {
      cur = maze_[cur.second + 1][cur.first].coords;
    } else if (go_right == true &&
               tmp > maze_[cur.second][cur.first + 1].value_) {
      cur = maze_[cur.second][cur.first + 1].coords;
    } else if (go_up == true && tmp > maze_[cur.second - 1][cur.first].value_) {
      cur = maze_[cur.second - 1][cur.first].coords;
    } else if (go_left == true &&
               tmp > maze_[cur.second][cur.first - 1].value_) {
      cur = maze_[cur.second][cur.first - 1].coords;
    }
    way_.push_back(cur);
  }

  for (int i = way_.size() - 1; i > -1; i--) {
    clear_way_.push_back(way_[i]);
  }
  clear_way_.push_back(goal);

  return clear_way_;
}

void Maze_Walker::GoToWalk(const std::string filename,
                           std::pair<int, int> start_pos,
                           std::pair<int, int> goal) {
  ClearMaze();
  LoadMaze(filename);
  SetCoords();
  SearchWay(start_pos, goal);
}

void Maze_Walker::ClearMaze() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      maze_[i][j].down_border_ = false;
      maze_[i][j].right_border_ = false;
      maze_[i][j].upper_border_ = false;
      maze_[i][j].left_border_ = false;
      maze_[i][j].coords.first = false;
      maze_[i][j].coords.second = false;
    }
  }
}
