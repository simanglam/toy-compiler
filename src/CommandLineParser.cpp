#include <string>
#include <iostream>
#include "CommandLineParser.h"

using namespace std;

void parseCommandLine(char** commandLineArgs, int argsNum, CommandLineOptions& options){
    int i = 1;
    while (i < argsNum) {
        string arg(commandLineArgs[i]);
        if (arg[0] == '-') {
            if (i + 1 > argsNum)
                break;
            if (arg.substr(1, arg.size()) == "O0") {
                options.optimizationLevel = 0;
            }
            else if (arg.substr(1, arg.size()) == "O1") {
                options.optimizationLevel = 1;
            }
            else if (arg.substr(1, arg.size()) == "O2") {
                options.optimizationLevel = 2;
            }
            else if (arg.substr(1, arg.size()) == "O3") {
                options.optimizationLevel = 3;
            }
            else if (arg.substr(1, arg.size()) == "S") {
                options.outputFileType = ASM;
            }
            else if (arg.substr(1, arg.size()) == "C") {
                options.outputFileType = OBJECT_FILE;
            }
            else if (arg.substr(1, arg.size()) == "I") {
                options.outputFileType = LLVM_IR;
            }
        }
        else {
            options.inputs.push_back(arg);
        }
        ++i;
    }
}