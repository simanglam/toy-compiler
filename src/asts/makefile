includePath = -I../include/

SRC = $(wildcard *.cpp)
EXE = $(patsubst %.cpp, %.o, $(SRC))

all: $(EXE)

%.o: %.cpp
	g++ `llvm-config --cxxflags --ldflags --system-libs --libs core native` $(includePath) -c -o $@ $<

clean:
	rm *.o
.PHONY: clean