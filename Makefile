SOURCE_FOLDER = src
BUILD_FOLDER = build
PROJECT_NAME = evococo
# CXX = g++
CXX = clang++
CXXFLAGS = -g -std=c++1z -O3 -pedantic -Wall -Werror -c
LIBS_FOLDER = lib
# LD = g++
LD = clang++
LDFLAGS = -g # /usr/lib64/libprofiler.so.0.4.16

OBJS = main.o lib/libEasyBMP.a ComponentEvolver.o NoiseFilterEvolver.o CGPCircuit.o Image.o

all: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(BUILD_FOLDER)/$(PROJECT_NAME)

$(LIBS_FOLDER)/libEasyBMP.a: $(LIBS_FOLDER)/EasyBMP/EasyBMP.cpp $(LIBS_FOLDER)/EasyBMP/EasyBMP.h
	$(CXX) -g -std=c++1z -O3 -pedantic -c $(LIBS_FOLDER)/EasyBMP/EasyBMP.cpp -o EasyBMP.o; \
	ar rcs $(LIBS_FOLDER)/libEasyBMP.a EasyBMP.o

main.o: $(SOURCE_FOLDER)/main.cpp \
	 $(SOURCE_FOLDER)/ComponentEvolver.hpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/main.cpp -o main.o

ComponentEvolver.o: $(SOURCE_FOLDER)/ComponentEvolver.cpp \
	 $(SOURCE_FOLDER)/ComponentEvolver.hpp \
	 $(SOURCE_FOLDER)/NoiseFilterEvolver.hpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/ComponentEvolver.cpp -o ComponentEvolver.o

NoiseFilterEvolver.o: $(SOURCE_FOLDER)/NoiseFilterEvolver.cpp \
	 $(SOURCE_FOLDER)/NoiseFilterEvolver.hpp \
	 $(SOURCE_FOLDER)/CGPCircuit.hpp
	$(CXX) $(CXXFLAGS) $(SOURCE_FOLDER)/NoiseFilterEvolver.cpp -o NoiseFilterEvolver.o

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
	cd $(BUILD_FOLDER) && CPUPROFILE=prof.out ./$(PROJECT_NAME) ../images/barbara.bmp ../images/barbara_noise.bmp
