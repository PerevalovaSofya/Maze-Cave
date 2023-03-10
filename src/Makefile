all: clean build 

build: clean
	mkdir build
	cd build/; qmake ../Maze.pro
	make -C build/
	cd build/; rm -rf *.o *.cpp *.h Makefile

install: build
	mkdir $(HOME)/Desktop/Maze/
	cp -rf build/Maze.app $(HOME)/Desktop/Maze/
	cp -rf model/example $(HOME)


uninstall:
	rm -rf $(HOME)/Desktop/Maze/
	rm -rf $(HOME)/new_maze_1.txt


tests: clean
	g++ -Wall -Wextra -Werror -std=c++17 --coverage model/maze.cc model/throughmaze.cc tests.cc -o test -lstdc++ -lgtest -lgtest_main
	./test
	rm -rf *.o 

check:
	cppcheck --language=c++ --suppress=missingIncludeSystem model/*.cc model/*.h  view/*.h view/*.cpp

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n model/*.cc model/*.h
	rm -rf .clang-format

clean:
	rm -rf *.o *.a *.gcda *.gcno Maze test Maze.tar gcov_report build/ report/ test.info Dist/ *.out *.cfg $(HOME)/new_maze_1.txt
