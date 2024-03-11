CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC_FILES = main.cpp Game.cpp Graph.cpp HexBoard.cpp MonteCarlo.cpp State.cpp
TARGET = PlayHex

all: $(TARGET)

$(TARGET): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_FILES)

.PHONY: clean

clean:
	rm -f $(TARGET)
