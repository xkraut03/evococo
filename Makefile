SOURCE_FOLDER = src
BUILD_FOLDER = build
PROJECT_NAME = evococo
CXX = g++
CXXFLAGS = -std=c++17 -O3 -pedantic -Werror -c

LIBS_FOLDER = lib
OBJS = main.o EasyBMP.o ComponentEvolver.o MedianFilterEvolution.o CGPcircuit.o

all: $(OBJS)
	$(CXX) $(OBJS) -o $(BUILD_FOLDER)/$(PROJECT_NAME)

main.o: $(SOURCE_FOLDER)/main.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/main.cpp -o main.o

EasyBMP.o: $(LIBS_FOLDER)/EasyBMP/EasyBMP.cpp $(LIBS_FOLDER)/EasyBMP/EasyBMP.h
	$(CXX) $(CXXFLAGS) $(LIBS_FOLDER)/EasyBMP/EasyBMP.cpp -o EasyBMP.o

ComponentEvolver.o: $(SOURCE_FOLDER)/ComponentEvolver.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/ComponentEvolver.cpp -o ComponentEvolver.o

MedianFilterEvolution.o: $(SOURCE_FOLDER)/MedianFilterEvolution.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/MedianFilterEvolution.cpp -o MedianFilterEvolution.o

CGPcircuit.o: $(SOURCE_FOLDER)/CGPcircuit.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/CGPcircuit.cpp -o CGPcircuit.o

clean:
	rm *.o
	rm $(BUILD_FOLDER)/$(PROJECT_NAME)
