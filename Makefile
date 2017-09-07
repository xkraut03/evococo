SOURCE = src
BUILD = build
PROJECT = evococo
CXX = g++
CXXFLAGS = -std=c++17 -O3 -pedantic -Werror -c

LIBS = lib
OBJS = main.o EasyBMP.o ComponentEvolver.o MedianFilterEvolution.o

all: $(OBJS)
	$(CXX) $(OBJS) -o $(BUILD)/$(PROJECT)

main.o: $(SOURCE)/main.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE)/main.cpp -o main.o

EasyBMP.o: $(LIBS)/EasyBMP/EasyBMP.cpp $(LIBS)/EasyBMP/EasyBMP.h
	$(CXX) $(CXXFLAGS) $(LIBS)/EasyBMP/EasyBMP.cpp -o EasyBMP.o

ComponentEvolver.o: $(SOURCE)/ComponentEvolver.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE)/ComponentEvolver.cpp -o ComponentEvolver.o

MedianFilterEvolution.o: $(SOURCE)/MedianFilterEvolution.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE)/MedianFilterEvolution.cpp -o MedianFilterEvolution.o

clean:
	rm *.o
	rm $(BUILD)/$(PROJECT)
