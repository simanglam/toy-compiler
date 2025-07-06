includePath = -Iinclude/

SRC = $(wildcard *.cpp)
SRC += $(wildcard asts/*.cpp)
EXE = $(patsubst %.cpp, %.o, $(SRC))

main: $(EXE)
	g++ `llvm-config --ldflags --system-libs --libs core native` --debug -o $@ $^


.PHONY: asts

%.o: %.cpp
	g++ `llvm-config --cxxflags` --debug $(includePath) -c -o $@ $<

clean:
	- rm *.o
	- rm asts/*.o
	- rm main
.PHONY: clean