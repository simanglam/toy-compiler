#include "Parser.h"
#include "asts/ArrayDeclare.h"
#include "asts/DeclareNode.h"
#include "asts/GlobalDeclareNode.h"
#include "asts/PrototypeAST.h"
#include "asts/FunctionAST.h"
#include "asts/ReturnStatement.h"
#include "asts/IfStatement.h"
#include "asts/ErrorExpr.h"

Statement* Parser::parseReturn() {
    s.getToken();
    Statement* node = new ReturnStatement(parseExpression());
    return node;
}

Statement* Parser::parseIf() {
    assert(s.getToken().type == TOK_OP_LEFTPAR);
    Expression* cond = parseParExpression();

    if (!cond) {
        return (Statement*) new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing cond");
    }

    BlockNode* ifBody = nullptr;    
    if (s.currentToken.type != TOK_CUR_LEFT) {        
        vector<ASTNode*> expr;
        expr.push_back(parseLinePrimary());

        if (!expr.back()) {
            delete cond;
            return (Statement*) new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing if Body");
        }
        ifBody = new BlockNode(expr);
    }
    else {
        ifBody = parseBlock();
    }

    if (s.nextToken.type != TOK_ELSE) {
        return new IfStatement(cond, ifBody, nullptr);
    }
    s.getToken();

    if (s.getToken().type != TOK_CUR_LEFT) {
        vector<ASTNode*> expr;
        expr.reserve(1);
        expr.push_back(parseLinePrimary());
        return new IfStatement(cond, ifBody, new BlockNode(expr));
    }
    else {
        Statement* node = new IfStatement(cond, ifBody, parseBlock());
        return node;
    }
    return (Statement*) new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing par expr");

}

Statement* Parser::parseDeclare() {
    TOKENS type = s.currentToken.type;
    s.getToken();
    if (s.currentToken.type == TOK_COMMA || s.currentToken.type == TOK_OP_RIGHTPAR) {
        return new DeclareNode("", type);
    }

    string name = s.currentToken.strLiteral;
    s.getToken();
    Statement* node = nullptr;

    if (s.currentToken.type == TOK_OP_ASSIGN) {
        s.getToken();
        node = new DeclareNode(name, type, parseExpression());
    }
    else if (s.currentToken.type == TOK_OP_LEFTBRA) {
        s.getToken();
        Expression* arraySizeExpr = nullptr;
        if (s.currentToken.type != TOK_OP_RIGHTPAR)
            arraySizeExpr = parsePrimary();

        vector<Expression*> initVals;
        if (s.getToken().type == TOK_OP_ASSIGN) {
            assert(s.getToken().type == TOK_CUR_LEFT);
            do{
                s.getToken();
                initVals.push_back(parsePrimary());
            } while (s.currentToken.type != TOK_CUR_RIGHT);
            assert(s.getToken().type == TOK_SEMI);
            node = new ArrayDeclare(type, initVals, arraySizeExpr, name);
        }
        else
            node = new ArrayDeclare(type, initVals, arraySizeExpr, name);
    }
    else {
        node = new DeclareNode(name, type);
    }

    if (s.currentToken.type == TOK_COMMA || s.currentToken.type == TOK_OP_RIGHTPAR){
        return node;
    }

    if (s.currentToken.type != TOK_SEMI) {
        s.getToken();
        return (Statement*) new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing par expr");
    }
    return node;
}