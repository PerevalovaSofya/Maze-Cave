#ifndef SRC_MODEL_GROTTO_H
#define SRC_MODEL_GROTTO_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Grotto {
 public:
  void LoadGrotto(const std::string filename);
  void InitGrotto();
  void ChangeGrotto();
  void PrintGrotto();
  void CountingNeighbors(int i, int j);
  void SetLiveParametrs(int born, int death);
  int GetRows() { return rows_; }
  int GetCols() { return cols_; }
  std::vector<std::vector<bool>> GetCave() { return cave_; }
  bool CheckCell(int rows, int cols) { return cave_[rows][cols]; }

 private:
  std::vector<std::vector<bool>> cave_;
  std::vector<std::vector<bool>> buffer_;
  int neighbors_{};
  int rows_{};
  int cols_{};
  int born_{};
  int death_{};
};

#endif  // SRC_MODEL_GROTTO_H
