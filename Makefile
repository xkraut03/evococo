SOURCE_FOLDER = src
BUILD_FOLDER = build
PROJECT_NAME = evococo
# CXX = g++
CXX = clang++
CXXFLAGS = -g -std=c++1z -O3 -pedantic -Wall -Werror -c
LIBS_FOLDER = lib
# LD = g++
LD = clang++
LDFLAGS = -g

OBJS = main.o lib/libEasyBMP.a ComponentEvolver.o MedianFilterEvolution.o CGPCircuit.o Image.o

all: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(BUILD_FOLDER)/$(PROJECT_NAME)

$(LIBS_FOLDER)/libEasyBMP.a: $(LIBS_FOLDER)/EasyBMP/EasyBMP.cpp $(LIBS_FOLDER)/EasyBMP/EasyBMP.h
	$(CXX) -g -std=c++1z -O3 -pedantic -c $(LIBS_FOLDER)/EasyBMP/EasyBMP.cpp -o EasyBMP.o; \
	ar rcs $(LIBS_FOLDER)/libEasyBMP.a EasyBMP.o

main.o: $(SOURCE_FOLDER)/main.cpp \
	 $(SOURCE_FOLDER)/ComponentEvolver.hpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/main.cpp -o main.o

ComponentEvolver.o: $(SOURCE_FOLDER)/ComponentEvolver.cpp \
	 $(SOURCE_FOLDER)/ComponentEvolver.hpp \
	 $(SOURCE_FOLDER)/MedianFilterEvolution.hpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/ComponentEvolver.cpp -o ComponentEvolver.o

MedianFilterEvolution.o: $(SOURCE_FOLDER)/MedianFilterEvolution.cpp \
	 $(SOURCE_FOLDER)/MedianFilterEvolution.hpp \
	 $(SOURCE_FOLDER)/CGPCircuit.hpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/MedianFilterEvolution.cpp -o MedianFilterEvolution.o

CGPCircuit.o: $(SOURCE_FOLDER)/CGPCircuit.cpp $(SOURCE_FOLDER)/CGPCircuit.hpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/CGPCircuit.cpp -o CGPCircuit.o

Image.o: $(SOURCE_FOLDER)/Image.cpp \
		 $(SOURCE_FOLDER)/Image.hpp \
		 $(LIBS_FOLDER)/EasyBMP/EasyBMP.h
		$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/Image.cpp -o Image.o


clean:
	rm *.o
	rm $(BUILD_FOLDER)/$(PROJECT_NAME)

run: all
	cd $(BUILD_FOLDER) && ./$(PROJECT_NAME) ../images/barbara.bmp ../images/barbara_noise.bmp

profile: all
	cd $(BUILD_FOLDER) && valgrind --tool=callgrind ./$(PROJECT_NAME) ../images/barbara.bmp ../images/barbara_noise.bmp
