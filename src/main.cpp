#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "include/Scanner.h"
#include "include/Token.h"
#include "include/Parser.h"


static map<int, int> opTable;

int main(int argc, char ** argv){
    string filename = "./test.txt";
    Scanner s(filename);
    Parser p(s);
    Compiler c(p);
    Token t = {};
    BaseExpr* ast = nullptr;

    while ((ast = p.parseLine()) != nullptr){
        ast->codegen(c);
        delete ast;
    }
    c.TheModule.get()->print(outs(), nullptr);
}