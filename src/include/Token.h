#ifndef __TOKEN_HEADER__
#define __TOKEN_HEADER__
#include <iostream>
#include <fstream>
#include <string>

enum TOKENS {
    TOK_EOF,

    TOK_TYPE_INT, TOK_TYPE_DOUBLE,
    TOK_IF, TOK_ELSE,
    TOK_DO, TOK_WHILE,
    TOK_RETURN,
    

    TOK_OP_ADD, TOK_OP_MINUS, TOK_OP_TIMES, TOK_OP_DIVIDE, TOK_OP_LEFTPAR, TOK_OP_RIGHTPAR, TOK_OP_EQUAL, TOK_DOT,
    TOK_SEMI, TOK_COMMA, TOK_CUR_LEFT, TOK_CUR_RIGHT,

    TOK_NUM, TOK_FLOAT, TOK_CHAR, TOK_IND,
    TOK_ERROR
};

using namespace std;

struct Token{
    TOKENS type;
    string strLiteral;
    int numVal;
};

#endif