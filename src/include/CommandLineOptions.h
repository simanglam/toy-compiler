#ifndef __CommandLineOptions_Header__
#define __CommandLineOptions_Header__

#include <fstream>
#include <map>

using namespace std;

enum outputType {
    ASM,
    LLVM_IR,
    OBJECT_FILE
};

class CommandLineOptions {
public:
    vector<string> inputs;
    outputType outputFileType = LLVM_IR;
    int optimizationLevel = 0;
     
};

#endif