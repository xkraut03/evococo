SOURCE = src
BUILD = build
PROJECT = evococo
CXX = g++
CXXFLAGS = -std=c++17 -O3 -pedantic -Werror -c

LIBS = lib
OBJS = main.o EasyBMP.o

all: $(OBJS)
	$(CXX) $(OBJS) -o $(BUILD)/$(PROJECT)

main.o: $(SOURCE)/main.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE)/main.cpp -o main.o

EasyBMP.o: $(LIBS)/EasyBMP/EasyBMP.cpp $(LIBS)/EasyBMP/EasyBMP.h
	$(CXX) $(CXXFLAGS) $(LIBS)/EasyBMP/EasyBMP.cpp -o EasyBMP.o

clean:
	rm *.o
	rm $(BUILD)/$(PROJECT)
