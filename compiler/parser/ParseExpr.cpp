#include "Parser.h"
#include "asts/ErrorExpr.h"
#include "asts/FunctionCallExpr.h"
#include "asts/BinaryOpNode.h"
#include "asts/ConstExpr.h"
#include "asts/VariableNode.h"
#include "asts/UnaryExpr.h"

static int getTokenPrec(const Token& t) {
    switch (t.type){
        case TOK_SEMI:
            return -1;
        case TOK_OP_AND:
        case TOK_OP_OR:
            return 5;
        case TOK_OP_EQUAL:
        case TOK_OP_UNEQUAL:
        case TOK_OP_GE:
        case TOK_OP_GT:
        case TOK_OP_LE:
        case TOK_OP_LT:
            return 10;
        case TOK_OP_ASSIGN:
            return 15;
        case TOK_OP_ADD:
        case TOK_OP_MINUS:
            return 20;
        case TOK_OP_DIVIDE:
        case TOK_OP_TIMES:
            return 25;
        case TOK_OP_LEFTBRA:
            return 30;
        default:
            return -1;
    }

}

Expression* Parser::parseExpression() {
    Expression* lhs = parsePrimary();
    Expression* node = parseBinOpRhs(0, lhs);
    return node;
}

Expression* Parser::parseIndExpression() {
    string name = s.currentToken.strLiteral;
    if (s.nextToken.type != TOK_OP_LEFTPAR){
        Expression* node = new VariableNode(name);
        s.getToken();
        Expression* expr = parseBinOpRhs(0, node);
        return expr;
    }
    vector<Expression*> args;
    s.getToken();
    while (s.currentToken.type != TOK_OP_RIGHTPAR) {
        s.getToken();
        if (s.currentToken.type == TOK_OP_RIGHTPAR) break;
        args.push_back(parseExpression());
    }
    s.getToken();
    return new FunctionCallExpr(name, args);
    
    return new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing id expr");
}

Expression* Parser::parseParExpression() {
    s.getToken();
    Expression* lhs = parsePrimary();
    Expression* node = parseBinOpRhs(0, lhs);
    if (s.currentToken.type != TOK_OP_RIGHTPAR) {
        delete node;
        delete lhs;
        return new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing par expr");
    }
    s.getToken();
    return node;
};

Expression* Parser::parseBinOpRhs(int minPrec, Expression* lhs){
    while (true){
        int tokPrec = getTokenPrec(s.currentToken);
        if (tokPrec < minPrec)
            return lhs;
        
        TOKENS op = s.currentToken.type;
        s.getToken();
        
        Expression* rhs = parsePrimary();

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
        if (op == TOK_OP_LEFTBRA)
            s.getToken();
    }
}

Expression* Parser::parseUnary() {
    TOKENS op = s.currentToken.type;
    s.getToken();
    return new UnaryExpr(parsePrimary(), op);
}

Expression* Parser::parseInteger() {
    Expression* node = new IntegerExpr(s.currentToken.intVal);
    s.getToken();
    return node;
}

Expression* Parser::parseDouble() {
    Expression* node = new DoubleExpr(s.currentToken.floatVal);
    s.getToken();
    return node;
}