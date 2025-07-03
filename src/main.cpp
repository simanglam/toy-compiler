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
    Token t = {};
    BaseAST* ast = nullptr;

    while ((ast = p.parseLine()) != nullptr){
        cout << ast->result() << endl;
    }  
}