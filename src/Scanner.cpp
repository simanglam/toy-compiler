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

Scanner::Scanner(istream& _file): file(_file), nextChar(' '), currentChar(' '), currentLine(1){
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
            if (nextChar == '='){
                nextToken.type = TOK_OP_EQUAL;
                nextToken.strLiteral = "==";
                currentChar = nextChar;
                file >> nextChar;
            }
            else {
                nextToken.type = TOK_OP_ASSIGN;
                nextToken.strLiteral = "=";
            }
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '>':
            if (nextChar == '='){
                nextToken.type = TOK_OP_GE;
                nextToken.strLiteral = ">=";
                currentChar = nextChar;
                file >> nextChar;
            }
            else {
                nextToken.type = TOK_OP_GT;
                nextToken.strLiteral = ">";
            }
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '<':
            if (nextChar == '='){
                nextToken.type = TOK_OP_LE;
                nextToken.strLiteral = "==";
                currentChar = nextChar;
                file >> nextChar;
            }
            else {
                nextToken.type = TOK_OP_LT;
                nextToken.strLiteral = "=";
            }
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '!':
            if (nextChar == '='){
                nextToken.type = TOK_OP_UNEQUAL;
                nextToken.strLiteral = "!=";
                currentChar = nextChar;
                file >> nextChar;
            }
            else {
                nextToken.type = TOK_OP_NOT;
                nextToken.strLiteral = "!";
            }
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '&':
            if (nextChar == '&'){
                nextToken.type = TOK_OP_AND;
                nextToken.strLiteral = "&&";
                currentChar = nextChar;
                file >> nextChar;
            }
            else {
                nextToken.type = TOK_ERROR;
                nextToken.strLiteral = "&";
            }
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '|':
            if (nextChar == '|'){
                nextToken.type = TOK_OP_OR;
                nextToken.strLiteral = "||";
                currentChar = nextChar;
                file >> nextChar;
            }
            else {
                nextToken.type = TOK_ERROR;
                nextToken.strLiteral = "|";
            }
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
        case ',':
            nextToken.type = TOK_COMMA;
            nextToken.strLiteral = ",";
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '{':
            nextToken.type = TOK_CUR_LEFT;
            nextToken.strLiteral = "{";
            currentChar = nextChar;
            file >> nextChar;
            break;
        case '}':
            nextToken.type = TOK_CUR_RIGHT;
            nextToken.strLiteral = "}";
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
                if (currentChar == '.') {
                    file >> nextChar;
                    do {
                        buffString += currentChar;
                        currentChar = nextChar;
                        file >> nextChar;
                    } while (isNum(currentChar) && file.good());
                    nextToken.type = TOK_FLOAT;
                    nextToken.floatVal = stod(buffString);
                    nextToken.strLiteral = buffString;
                }
                else {
                    nextToken.type = TOK_INT;
                    nextToken.intVal = atoi(buffString.c_str());
                    nextToken.strLiteral = buffString;
                }
            }
            else if (isAlpha(currentChar)){
                do {
                    buffString += currentChar;
                    currentChar = nextChar;
                    file >> nextChar;
                } while ((isAlpha(currentChar) || isNum(currentChar)) && file.good());
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

    if (nextToken.strLiteral == "int")
        nextToken.type = TOK_TYPE_INT;
    else if (nextToken.strLiteral == "double")
        nextToken.type = TOK_TYPE_DOUBLE;
    else if (nextToken.strLiteral == "if")
        nextToken.type = TOK_IF;
    else if (nextToken.strLiteral == "else")
        nextToken.type = TOK_ELSE;
    else if (nextToken.strLiteral == "return")
        nextToken.type = TOK_RETURN;

    return currentToken;
}

Token Scanner::peekToken(){
    return nextToken;
}

Scanner::~Scanner(){

}