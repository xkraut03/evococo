SOURCE_FOLDER = src
BUILD_FOLDER = build
PROJECT_NAME = evococo
CXX = clang++
CXXFLAGS = -g -std=c++1z -O3 -pedantic -Wall -Werror -c
LIBS_FOLDER = lib
LD = clang++
LDFLAGS = -g

OBJS = main.o libEasyBMP.a ComponentEvolver.o MedianFilterEvolution.o CGPCircuit.o

all: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(BUILD_FOLDER)/$(PROJECT_NAME)

libEasyBMP.a: $(LIBS_FOLDER)/EasyBMP/EasyBMP.cpp $(LIBS_FOLDER)/EasyBMP/EasyBMP.h
	$(CXX) -g -std=c++1z -O3 -pedantic -c $(LIBS_FOLDER)/EasyBMP/EasyBMP.cpp -o EasyBMP.o; \
	ar rcs libEasyBMP.a EasyBMP.o

main.o: $(SOURCE_FOLDER)/main.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/main.cpp -o main.o

ComponentEvolver.o: $(SOURCE_FOLDER)/ComponentEvolver.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/ComponentEvolver.cpp -o ComponentEvolver.o

MedianFilterEvolution.o: $(SOURCE_FOLDER)/MedianFilterEvolution.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/MedianFilterEvolution.cpp -o MedianFilterEvolution.o

CGPCircuit.o: $(SOURCE_FOLDER)/CGPCircuit.cpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/CGPCircuit.cpp -o CGPCircuit.o

clean:
	rm *.o
	rm $(BUILD_FOLDER)/$(PROJECT_NAME)

run:
	cd $(BUILD_FOLDER) && ./$(PROJECT_NAME) ../images/barbara.bmp ../images/barbara_noise.bmp
