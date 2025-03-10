CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic

SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LDFLAGS := $(shell sdl2-config --libs)

SRC := main.cpp snake.cpp game.cpp
OBJ := $(SRC:.cpp=.o)
EXEC := snake

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(SDL2_LDFLAGS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $< -o $@

clean:
	@rm -fv $(OBJ) $(EXEC)

.PHONY: all clean