#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Compiler.h"
#include "CommandLineParser.h"

static map<int, int> opTable;

int main(int argc, char ** argv){
    string filename = "./test.txt";
    CommandLineOptions options;
    parseCommandLine(argv, argc, options);
    Compiler c(options);
    c.compile();
}