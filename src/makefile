includePath = -Iinclude/

SRC = $(wildcard *.cpp)
SRC += $(wildcard asts/*.cpp)
SRC += $(wildcard parser/*.cpp)
EXE = $(patsubst %.cpp, %.o, $(SRC))

extraFlag = --debug

main: $(EXE)
	g++ `llvm-config --ldflags --system-libs --libs core native` $(extraFlag) -o $@ $^


.PHONY: asts

%.o: %.cpp
	g++ `llvm-config --cxxflags` --debug $(includePath) $(extraFlag) -c -o $@ $<

clean:
	- rm *.o
	- rm asts/*.o
	- rm main
.PHONY: clean