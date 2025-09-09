#include "Parser.h"
#include "asts/ArrayDeclare.h"
#include "asts/DeclareNode.h"
#include "asts/GlobalDeclareNode.h"
#include "asts/PrototypeAST.h"
#include "asts/FunctionAST.h"
#include "asts/ReturnStatement.h"
#include "asts/IfStatement.h"
#include "asts/ErrorExpr.h"
#include "asts/DeclareStatement.h"
#include "asts/DeclareNodeStrategy.h"

#include "types/TypeInfo.h"
#include "types/DoubleTypeInfo.h"
#include "types/SignedInt32Type.h"
#include "types/MemoryType.h"

Statement* Parser::parseReturn() {
    s.getToken();
    Statement* node = new ReturnStatement(parseExpression());
    assert(s.currentToken.type == TOK_SEMI);
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
    TypeInfo* type = nullptr;

    switch (s.currentToken.type) {
        case TOK_TYPE_INT:
            type = new SignedInt32Type();
            break;
        case TOK_TYPE_DOUBLE:
            type = new DoubleTypeInfo();
            break;
    }

    s.getToken();
    DeclareStatement* node = new DeclareStatement();
    if (s.currentToken.type == TOK_COMMA || s.currentToken.type == TOK_OP_RIGHTPAR) {
        return node;
    }

    string name = s.currentToken.strLiteral;
    s.getToken();

    if (s.currentToken.type == TOK_OP_ASSIGN) {
        s.getToken();
        node->pushNode(new DeclareNode(type, name, DeclareNodeStrategy::getStrategy(DeclareType::LOCAL), parseExpression()));
    }
    else if (s.currentToken.type == TOK_OP_LEFTBRA) {
        s.getToken();
        TypeInfo* baseType = type;
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
            node->pushNode(new DeclareNode(new MemoryType(baseType, 1), name, DeclareNodeStrategy::getStrategy(DeclareType::LOCAL), nullptr, arraySizeExpr, initVals));
        }
        else
            node->pushNode(new DeclareNode(type, name, DeclareNodeStrategy::getStrategy(DeclareType::LOCAL), nullptr, arraySizeExpr));
    }
    else {
        node->pushNode(new DeclareNode(type, name, DeclareNodeStrategy::getStrategy(DeclareType::LOCAL)));
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