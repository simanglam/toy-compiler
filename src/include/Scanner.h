#ifndef __SCANNER_HEADER__
#define __SCANNER_HEADER__

#include "Token.h"

class Scanner{
private:
    fstream& file;
    int currentLine;
    char currentChar;
    char nextChar;
public:
    Token currentToken;
    Token nextToken;
    Scanner(fstream&);
    ~Scanner();
    Token getToken();
    Token peekToken();
    int getCurrentLine() const;
};

#endif