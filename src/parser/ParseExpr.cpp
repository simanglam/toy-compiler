#include "Parser.h"
#include "asts/ErrorExpr.h"
#include "asts/FunctionCallExpr.h"
#include "asts/BinaryOpNode.h"
#include "asts/ConstExpr.h"
#include "asts/VariableNode.h"

static int getTokenPrec(const Token& t) {
    switch (t.type){
        case TOK_SEMI:
            return -1;
        case TOK_OP_EQUAL:
        case TOK_OP_UNEQUAL:
        case TOK_OP_GE:
        case TOK_OP_GT:
        case TOK_OP_LE:
        case TOK_OP_LT:
            return 5;
        case TOK_OP_ASSIGN:
            return 10;
        case TOK_OP_ADD:
        case TOK_OP_MINUS:
            return 15;
        case TOK_OP_DIVIDE:
        case TOK_OP_TIMES:
            return 20;
        default:
            return -1;
    }

}

BaseExpr* Parser::parseExpression() {
    BaseExpr* lhs = parsePrimary();
    BaseExpr* node = parseBinOpRhs(0, lhs);
    return node;
}

BaseExpr* Parser::parseIndExpression() {
    string name = s.currentToken.strLiteral;
    if (s.nextToken.type != TOK_OP_LEFTPAR){
        BaseExpr* node = new VariableNode(name);
        s.getToken();
        BaseExpr* expr = parseBinOpRhs(0, node);
        return expr;
    }
    vector<BaseExpr*> args;
    s.getToken();
    while (s.currentToken.type != TOK_OP_RIGHTPAR) {
        s.getToken();
        args.push_back(parseExpression());
    }
    s.getToken();
    return new FunctionCallExpr(name, args);
    
    return new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing id expr");
}

BaseExpr* Parser::parseParExpression() {
    s.getToken();
    BaseExpr* lhs = parsePrimary();
    BaseExpr* node = parseBinOpRhs(0, lhs);
    if (s.currentToken.type != TOK_OP_RIGHTPAR) {
        delete node;
        delete lhs;
        return new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing par expr");
    }
    s.getToken();
    return node;
};

BaseExpr* Parser::parseBinOpRhs(int minPrec, BaseExpr* lhs){
    while (true){
        int tokPrec = getTokenPrec(s.currentToken);
        if (tokPrec < minPrec)
            return lhs;
        
        TOKENS op = s.currentToken.type;
        s.getToken();
        
        BaseExpr* rhs = parsePrimary();

        if (!rhs){
            return new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing bin rhs");
        }

        if (tokPrec < getTokenPrec(s.currentToken)){
            rhs = parseBinOpRhs(tokPrec + 1, rhs);
            if (!rhs){
                return new ErrorExpr("Error when Parsing Token: " + s.currentToken.strLiteral + " when parsing bin rhs");
            }
        }
        
        lhs = new BinaryOpNode(lhs, op, rhs);
    }
}

BaseExpr* Parser::parseNumber() {
    BaseExpr* node = new IntegerExpr(s.currentToken.numVal);
    s.getToken();
    return node;
}