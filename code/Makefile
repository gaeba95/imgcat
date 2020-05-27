CC=gcc
CXX=g++

IMGCAT_CFLAGS= -O3 -g -Wall -fopenmp
BENCHMARK_CXXFLAGS= -O3 -g -Wall -Ilib/benchmark/include -DNDEBUG
IFS_LDFLAGS= -ljpeg -lpng
BENCHMARK_LDFLAGS= -Llib/benchmark/build/src -lbenchmark -lpthread -lm -ljpeg -lpng

IMGCAT=imgcat
BENCHMARK=imgcat-bm
BENCHMARK_CREATE=imgcat-create-bm 

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
CPP_OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

.PHONY: default all clean 

default: all

all: $(IMGCAT) $(BENCHMARK) $(BENCHMARK_CREATE)

$(IMGCAT): $(OBJECTS)
	$(CC) -fopenmp $(OBJECTS) $(IFS_LDFLAGS) -o $@ 

$(BENCHMARK): gbench.o environment.o convert.o
	$(CXX) -fopenmp $^ $(BENCHMARK_LDFLAGS) -o $@ 

$(BENCHMARK_CREATE): gbench-create.o environment.o convert.o
	$(CXX) -fopenmp $^ $(BENCHMARK_LDFLAGS) -o $@ 

%.o: %.c 
	$(CC) -fopenmp -c $^ $(IFS_CFLAGS) -o $@ 

%.o: %.cpp
	$(CXX) -fopenmp -c $^ $(BENCHMARK_CXXFLAGS) -o $@ 

clean:
	rm -f $(BENCHMARK)
	rm -f $(IMGCAT)
	rm -f $(BENCHMARK_CREATE)
	rm -f $(OBJECTS)
	rm -f $(CPP_OBJECTS)
