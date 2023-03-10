#include <gtest/gtest.h>

#include <iostream>

#include "../src/model/maze.h"
#include "../src/model/throughmaze.h"

TEST(maze_case, generate_test) {
  Maze maze_(7, 3);

  ASSERT_EQ(maze_.getRows(), 7);
  ASSERT_EQ(maze_.getCols(), 3);
}

TEST(maze_case, open_test) {
  Maze maze_;
  maze_.LoadMaze("../src/model/example/Maze/new_maze.txt");
  ASSERT_EQ(maze_.getRows(), 5);
  ASSERT_EQ(maze_.getCols(), 5);
}

TEST(maze_case, find_test) {
  std::vector<std::pair<int, int>> test_walker_ = {
      {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 4}, {3, 4}, {3, 3}};
  Maze maze_;
  Maze_Walker maze_walker_;
  maze_.LoadMaze("../src/model/example/Maze/new_maze.txt");
  maze_walker_.GoToWalk("../src/model/example/Maze/new_maze.txt",
                        std::pair<int, int>(0, 0), std::pair<int, int>(3, 3));
  std::vector<std::pair<int, int>> way_walker_ = maze_walker_.ClearWay(
      std::pair<int, int>(0, 0), std::pair<int, int>(3, 3));

  for (size_t i = 0; i < way_walker_.size(); i++) {
    ASSERT_EQ(way_walker_[i].first, test_walker_[i].first);
    ASSERT_EQ(way_walker_[i].second, test_walker_[i].second);
  }
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
