#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>

#include "include/Scanner.h"

inline bool isWhiteSpace(int c){
    return (c == ' ' || c == '\n');
}

inline bool isNum(int c){
    return (c >= '0' && c <= '9');
}

inline bool isAlpha(int c){
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

Scanner::Scanner(string _fileName): fileName(_fileName), nextChar(' '), currentChar(' '), currentLine(1){
    file = fstream(fileName, fstream::in);
    file.unsetf(ios_base::skipws);
    getToken();
}

int Scanner::getCurrentLine() const{
    return currentLine;
}

Token Scanner::getToken(){
    currentToken = nextToken;
    while (isWhiteSpace(currentChar) && file.good()){
        if (currentChar == '\n') ++currentLine;
        currentChar = nextChar;
        file >> nextChar;
    }

    if (!file.good()){
        if (currentToken.type == TOK_EOF) return currentToken;
        nextToken.type = TOK_EOF;
        nextToken.strLiteral = EOF;
        nextChar = 0;
    }

    switch (currentChar){
        case '*':
            nextToken.type = TOK_OP_TIMES;
            nextToken.strLiteral = "*";
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '+':
            nextToken.type = TOK_OP_ADD;
            nextToken.strLiteral = "+";
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '-':
            nextToken.type = TOK_OP_MINUS;
            nextToken.strLiteral = "-";
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '/':
            nextToken.type = TOK_OP_DIVIDE;
            nextToken.strLiteral = "/";
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '=':
            nextToken.type = TOK_OP_EQUAL;
            nextToken.strLiteral = "=";
            currentChar = nextChar;
            file >> nextChar;
            break;
        case ';':
            nextToken.type = TOK_SEMI;
            nextToken.strLiteral = ";";
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '(':
            nextToken.type = TOK_OP_LEFTPAR;
            nextToken.strLiteral = "(";
            currentChar = nextChar;
            file >> nextChar;
            break;
        case ')':
            nextToken.type = TOK_OP_RIGHTPAR;
            nextToken.strLiteral = ")";
            currentChar = nextChar;
            file >> nextChar;
            break;
        default:
            string buffString("");
            if (isNum(currentChar)){
                do {
                    buffString += currentChar;
                    currentChar = nextChar;
                    file >> nextChar;
                } while (isNum(currentChar) && file.good());
                if (!file.good()) buffString += nextChar;
                nextToken.type = TOK_NUM;
                nextToken.numVal = atoi(buffString.c_str());
                nextToken.strLiteral = buffString;
            }
            else if (isAlpha(currentChar)){
                do {
                    buffString += currentChar;
                    currentChar = nextChar;
                    file >> nextChar;
                } while (isAlpha(currentChar) && file.good());
                if (!file.good()) buffString += nextChar;
                nextToken.type = TOK_IND;
                nextToken.strLiteral = buffString;
            }
            else if (nextChar == 0) {}
            else {
                nextToken.type = TOK_ERROR;
                nextToken.strLiteral = nextChar;
                cerr << "Unknow Token: " << nextToken.strLiteral << endl;
            }
    }
    return currentToken;
}

Token Scanner::peekToken(){
    return nextToken;
}

Scanner::~Scanner(){

}