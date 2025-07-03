includePath = -Iinclude/

SRC = $(wildcard *.cpp)
SRC += $(wildcard asts/*.cpp)
EXE = $(patsubst %.cpp, %.o, $(SRC))

main: $(EXE)
	+ make -C asts
	g++ `llvm-config --ldflags --system-libs --libs core native` -o $@ $^


.PHONY: asts

%.o: %.cpp
	g++ `llvm-config --cxxflags --ldflags --system-libs --libs core native` $(includePath) -c -o $@ $<

clean:
	rm *.o
	+ make -C asts clean
.PHONY: clean