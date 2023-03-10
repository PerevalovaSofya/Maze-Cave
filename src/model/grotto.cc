#include "grotto.h"


void Grotto::LoadGrotto(std::string const filename) {
  std::ifstream getgrotto(filename, std::ios::in);
  if (getgrotto.good()) {
    std::string line;
    getline(getgrotto, line);

    rows_ = (atof(&line[0]));
    int ind = line.find(' ');
    cols_ = (atof(&line[ind + 1]));

    InitGrotto();
    for (int i = 0; i < rows_; i++) {
      getline(getgrotto, line);
      for (int j = 0, d = 0; (size_t)j < line.size(); j += 2, d++) {
        if (atof(&line[j]) == 0) {
          cave_[i][d] = false;
        } else {
          cave_[i][d] = true;
        }
      }
    }
  }
}

void Grotto::InitGrotto() {
  cave_.resize(rows_);
  buffer_.resize(rows_);
  for (int i = 0; i < rows_; i++) {
    cave_[i].resize(cols_);
    buffer_[i].resize(cols_);
  }
}

void Grotto::ChangeGrotto() {
  buffer_ = cave_;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      neighbors_ = 0;
      CountingNeighbors(i, j);
      if (neighbors_ < death_ && cave_[i][j] == true) {
        buffer_[i][j] = false;
      }
      if (neighbors_ > born_ && cave_[i][j] == false) buffer_[i][j] = true;
    }
  }
  cave_ = buffer_;
}

void Grotto::CountingNeighbors(int i, int j) {
  for (int row = i - 1; row < i + 2; row++) {
    for (int col = j - 1; col < j + 2; col++) {
      if (!(row == i && col == j) && (row >= 0 && row < rows_) &&
          (col >= 0 && col < cols_) && cave_[row][col] == true) {
        neighbors_++;
      } else if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        neighbors_++;
      }
    }
  }
}

void Grotto::SetLiveParametrs(int born, int death) {
  born_ = born;
  death_ = death;
}

void Grotto::PrintGrotto() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (cave_[i][j] == true) {
        std::cout << "1 ";
      } else {
        std::cout << "_ ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

