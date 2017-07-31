SOURCE = src
BUILD = build
CPPFLAGS = -std=c++14

all: $(SOURCE)/main.cpp
	g++ $(CPPFLAGS) $(SOURCE)/main.cpp -o $(BUILD)/evococo
