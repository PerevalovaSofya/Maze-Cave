#ifndef THROUGHMAZE_H_
#define THROUGHMAZE_H_

#include <ostream>

#include "maze.h"

class Maze_Walker {
 public:
  class Node {
   public:
    bool right_border_{false};
    bool down_border_{false};
    bool left_border_{false};
    bool upper_border_{false};
    std::pair<int, int> coords;
    int value_{};
  };

  void LoadMaze(std::string maze);
  void InitMaze();
  void SetCoords();
  void SearchWay(std::pair<int, int> start_pos, std::pair<int, int> goal);
  void GoToWalk(const std::string filename, std::pair<int, int> start_pos,
                std::pair<int, int> goal);
  void PossibleWays(std::pair<int, int> cur);
  void SetLeftAndDown();
  std::vector<std::pair<int, int>> ClearWay(std::pair<int, int> start_pos,
                                            std::pair<int, int> goal);
  void CheckBorders(std::pair<int, int> cur);
  int getRows() { return rows_; }
  int getCols() { return cols_; }
  void ClearMaze();
  void SetNotNull();

 private:
  std::vector<std::vector<Node>> maze_;
  std::vector<std::pair<int, int>> way_{};
  std::vector<std::pair<int, int>> clear_way_{};
  std::pair<int, int> cur{};
  std::pair<int, int> prev{};
  int step{0};
  int rows_{};
  int cols_{};
  bool go_left{false};
  bool go_right{false};
  bool go_up{false};
  bool go_down{false};
};

#endif  // THROUGHMAZE_H_
