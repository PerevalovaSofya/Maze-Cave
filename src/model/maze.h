#ifndef MAZE_H_
#define MAZE_H_

#include <fstream>
#include <iostream>
#include <random>
#include <vector>


class Maze {
 public:
  class Node {
   public:
    bool right_border_{false};
    bool down_border_{false};
  };

  Maze();
  Maze(int rows, int cols);

  void CreateLine();
  void InitMaze(int rows, int cols);
  bool Boolean();
  void SetRightBorder(int r_ind_);
  void Merge(int n_ind_, int value);
  void SetDownBorder(int r_ind_);
  int CalculateDownBorders(int r_ind_, int value);
  int CalculateUnique(int value);
  void CheckDownBorders(int r_ind_);
  void NewLine(int r_ind_);
  void EndLine();
  void CheckEndLine();
  bool CheckRight(int rows, int cols);
  bool CheckDown(int rows, int cols);
  int getRows() { return rows_; }
  int getCols() { return cols_; }
  void CleanMaze();
  void SaveMaze(std::string maze);
  void ClearMaze();
  void LoadMaze(std::string maze);

  std::vector<std::vector<Node>> ReturnMaze() { return maze_; }

 private:
  std::vector<std::vector<Node>> maze_;
  std::vector<int> line_;
  int rows_{};
  int cols_{};
  int counter_{1};
};


#endif  // MAZE_H_
