CXX = g++
CXXFLAGS = -g3 -Wall -Wextra -Wconversion -Wcast-align -g -fsanitize=address

.PHONY: all clean format

all: 131sh

format:
	clang-format -style=Google -i *.cpp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

131sh: sh.o builtin.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f 131sh *.o
