#include "Parser.h"
#include "asts/BinaryOpNode.h"
#include "asts/NumberNode.h"
#include "asts/VariableNode.h"

static int getTokenPrec(const Token& t){
    switch (t.type){
        case TOK_SEMI:
            return -1;
        case TOK_OP_EQUAL:
            return 5;
        case TOK_OP_ADD:
        case TOK_OP_MINUS:
            return 10;
        case TOK_OP_DIVIDE:
        case TOK_OP_TIMES:
            return 20;
        default:
            return -1;
    }

}

Parser::Parser(Scanner& _s): s(_s) {}

Parser::~Parser(){}

BaseAST* Parser::parseLine(){
    switch (s.getToken().type){
    case TOK_EOF:
        break;
    case TOK_SEMI:
        s.getToken();
        break;
    default:
        BaseAST* node = parseExpression();
        if (!node) cerr << "WTF!" << endl;
        if (s.currentToken.type != TOK_SEMI) cerr << "Expect ';'" << endl;
        return node;
        break;
    }
    return nullptr;
}

BaseAST* Parser::parseExpression(){
    BaseAST* lhs = parsePrimary();
    BaseAST* node = parseBinOpRhs(0, lhs);
    return node;
}

BaseAST* Parser::parsePrimary(){

    switch (s.currentToken.type){
    case TOK_NUM:
        return parseNumber();
    case TOK_IND:
        return parseIndExpression();
    case TOK_OP_LEFTPAR:
        return parseParExpression();
    default:
        break;
    }
}


BaseAST* Parser::parseIndExpression(){
    if (s.nextToken.type != TOK_OP_LEFTPAR){
        BaseAST* node = new VariableNode(s.currentToken.strLiteral);
        s.getToken();
        BaseAST* expr = parseBinOpRhs(0, node);
        return expr;
    };
    return nullptr;
}

BaseAST* Parser::parseParExpression() {
    s.getToken();
    BaseAST* lhs = parsePrimary();
    BaseAST* node = parseBinOpRhs(0, lhs);
    if (!node) cerr << "Error when parsing par expression" << endl;
    if (s.currentToken.type != TOK_OP_RIGHTPAR) {
        cerr << "Missing right par" << endl;
        return nullptr;
    }
    s.getToken();
    return node;
};

BaseAST* Parser::parseBinOpRhs(int minPrec, BaseAST* lhs){
    while (true){
        int tokPrec = getTokenPrec(s.currentToken);
        if (tokPrec < minPrec)
            return lhs;
        
        char op = s.currentToken.strLiteral[0];
        s.getToken();
        
        BaseAST* rhs = parsePrimary();

        if (!rhs){
            cerr << "Error when Parsing Token: " << s.currentToken.strLiteral << endl;
            return nullptr;
        }

        if (tokPrec < getTokenPrec(s.currentToken)){
            rhs = parseBinOpRhs(tokPrec + 1, rhs);
            if (!rhs){
                cerr << "Error when Parsing Token: " << s.currentToken.strLiteral << endl;
                return nullptr;
            }
        }
        lhs = new BinaryOpNode(lhs, op, rhs);
    }
}

BaseAST* Parser::parseNumber(){
    BaseAST* node = new NumberNode(s.currentToken.numVal);
    s.getToken();
    return node;
}