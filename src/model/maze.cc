#include "maze.h"

Maze::Maze() { InitMaze(50, 50); }

Maze::Maze(int rows, int cols) { InitMaze(rows, cols); }

bool Maze::Boolean() {
  std::mt19937 rng(std::random_device{}());
  return std::uniform_int_distribution<>{0, 1}(rng);
}

void Maze::CreateLine() {
  for (int n_ind_ = 0; n_ind_ < cols_; n_ind_++) {
    if (line_[n_ind_] == 0) {
      line_[n_ind_] = counter_;
      counter_++;
    }
  }
}

void Maze::Merge(int n_ind_, int value) {
  int set = line_[n_ind_ + 1];
  for (int n_ind_ = 0; n_ind_ < cols_; n_ind_++) {
    if (line_[n_ind_] == set) {
      line_[n_ind_] = value;
    }
  }
}

void Maze::SetRightBorder(int r_ind_) {
  for (int n_ind = 0; n_ind < cols_ - 1; n_ind++) {
    bool r_b = Boolean();
    if (r_b == true || line_[n_ind] == line_[n_ind + 1]) {
      maze_[r_ind_][n_ind].right_border_ = true;
    } else {
      Merge(n_ind, line_[n_ind]);
    }
  }
  maze_[r_ind_][cols_ - 1].right_border_ = true;
}

int Maze::CalculateUnique(int value) {
  int unique = 0;
  for (int n_ind_ = 0; n_ind_ < cols_; n_ind_++) {
    if (line_[n_ind_] == value) {
      unique++;
    }
  }
  return unique;
}

void Maze::SetDownBorder(int r_ind_) {
  for (int n_ind = 0; n_ind < cols_; n_ind++) {
    bool d_b = Boolean();
    if (d_b == true && CalculateUnique(line_[n_ind]) != 1) {
      maze_[r_ind_][n_ind].down_border_ = true;
    }
  }
}

int Maze::CalculateDownBorders(int r_ind_, int value) {
  int down_border = 0;
  for (int n_ind = 0; n_ind < cols_; n_ind++) {
    if (line_[n_ind] == value && maze_[r_ind_][n_ind].down_border_ == false) {
      down_border++;
    }
  }
  return down_border;
}

void Maze::CheckDownBorders(int r_ind_) {
  for (int n_ind = 0; n_ind < cols_; n_ind++) {
    if (CalculateDownBorders(r_ind_, line_[n_ind]) == 0) {
      maze_[r_ind_][n_ind].down_border_ = false;
    }
  }
}

void Maze::NewLine(int r_ind_) {
  for (int n_ind = 0; n_ind < cols_; n_ind++) {
    if (maze_[r_ind_][n_ind].down_border_ == true) {
      line_[n_ind] = 0;
    }
  }
}

void Maze::CheckEndLine() {
  for (int n_ind = 0; n_ind < cols_ - 1; n_ind++) {
    if (line_[n_ind] != line_[n_ind + 1]) {
      maze_[rows_ - 1][n_ind].right_border_ = false;
      Merge(n_ind, line_[n_ind]);
    }
    maze_[rows_ - 1][n_ind].down_border_ = true;
  }
  maze_[rows_ - 1][cols_ - 1].down_border_ = true;
}

void Maze::ClearMaze() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      maze_[i][j].down_border_ = false;
      maze_[i][j].right_border_ = false;
    }
  }
  line_.clear();
}

void Maze::EndLine() {
  CreateLine();
  SetRightBorder(rows_ - 1);
  CheckEndLine();
}

void Maze::SaveMaze(std::string maze) {
  std::fstream save;
  save.open(maze, std::ios::out);

  if (!save) {
    std::cerr << maze << " File couldn't be opened\n";
  }

  save << rows_ << " " << cols_;

  for (int i = 0; i < rows_; ++i) {
    save << "\n";
    for (int j = 0; j < cols_; ++j) {
      save << maze_[i][j].right_border_ << " ";
    }
  }

  save << "\n";

  for (int i = 0; i < rows_; ++i) {
    save << "\n";
    for (int j = 0; j < cols_; ++j) {
      save << maze_[i][j].down_border_ << " ";
    }
  }
}

void Maze::InitMaze(int rows, int cols) {
  ClearMaze();

  rows_ = rows;
  cols_ = cols;

  maze_.resize(rows);

  for (int i = 0; i < cols_; i++) {
    line_.push_back(0);
  }

  for (int i = 0; i < rows - 1; i++) {
    maze_[i].resize(cols);
    CreateLine();
    SetRightBorder(i);
    SetDownBorder(i);
    CheckDownBorders(i);
    NewLine(i);
  }
  maze_[rows - 1].resize(cols);
  EndLine();
  counter_ = 1;
}

bool Maze::CheckRight(int rows, int cols) {
  return maze_[rows][cols].right_border_;
}

bool Maze::CheckDown(int rows, int cols) {
  return maze_[rows][cols].down_border_;
}

void Maze::LoadMaze(std::string maze) {
  ClearMaze();
  std::ifstream getmaze(maze, std::ios::in);
  if (getmaze.good()) {
    std::string line;
    getline(getmaze, line);

    rows_ = (atof(&line[0]));
    int ind = line.find(' ');
    cols_ = (atof(&line[ind + 1]));

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
}
