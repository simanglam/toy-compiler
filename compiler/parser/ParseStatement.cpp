#include "Parser.h"
#include "asts/ArrayDeclare.h"
#include "asts/DeclareNode.h"
#include "asts/GlobalDeclareNode.h"
#include "asts/PrototypeAST.h"
#include "asts/FunctionAST.h"
#include "asts/ReturnStatement.h"
#include "asts/IfExpr.h"
#include "asts/ErrorExpr.h"

BaseExpr* Parser::parseReturn() {
    s.getToken();
    BaseExpr* node = new ReturnStatement(parseExpression());
    return node;
}

BaseExpr* Parser::parseIf() {
    if (s.getToken().type != TOK_OP_LEFTPAR) {
        return new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing if");
    }
    BaseExpr* cond = parseParExpression();

    if (!cond) {
        return new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing cond");
    }

    BlockNode* ifBody = nullptr;    
    if (s.currentToken.type != TOK_CUR_LEFT) {        
        vector<BaseExpr*> expr;
        expr.push_back(parsePrimary());

        if (!expr.back()) {
            delete cond;
            return new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing if Body");
        }
        ifBody = new BlockNode(expr);
    }
    else {
        ifBody = parseBlock();
    }

    if (s.nextToken.type != TOK_ELSE) {
        return new IfExpr(cond, ifBody, nullptr);
    }
    s.getToken();

    if (s.getToken().type != TOK_CUR_LEFT) {
        vector<BaseExpr*> expr;
        expr.reserve(1);
        expr.push_back(parsePrimary());
        return new IfExpr(cond, ifBody, new BlockNode(expr));
    }
    else {
        BaseExpr* node = new IfExpr(cond, ifBody, parseBlock());
        return node;
    }
    return new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing par expr");

}

BaseExpr* Parser::parseDeclare() {
    TOKENS type = s.currentToken.type;
    s.getToken();
    if (s.currentToken.type == TOK_COMMA || s.currentToken.type == TOK_OP_RIGHTPAR) {
        return new DeclareNode("", type);
    }

    string name = s.currentToken.strLiteral;
    s.getToken();
    BaseExpr* node = nullptr;

    if (s.currentToken.type == TOK_OP_ASSIGN) {
        s.getToken();
        node = new DeclareNode(name, type, parseExpression());
    }
    else if (s.currentToken.type == TOK_OP_LEFTBRA) {
        s.getToken();
        BaseExpr* arraySizeExpr = nullptr;
        if (s.currentToken.type != TOK_OP_RIGHTPAR)
            arraySizeExpr = parsePrimary();

        // cerr << "An array with size: " << arraySize << endl;

        vector<BaseExpr*> initVals;
        if (s.getToken().type == TOK_OP_ASSIGN) {
            assert(s.getToken().type == TOK_CUR_LEFT);
            while (s.getToken().type != TOK_CUR_RIGHT){
                initVals.push_back(parsePrimary());
                assert(s.currentToken.type == TOK_COMMA);
            }
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
        return new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing par expr");
    }
    return node;
}