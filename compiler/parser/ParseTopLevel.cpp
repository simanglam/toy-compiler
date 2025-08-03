
#include "Parser.h"
#include "asts/DeclareNode.h"
#include "asts/GlobalDeclareNode.h"
#include "asts/PrototypeAST.h"
#include "asts/FunctionAST.h"
#include "asts/ReturnStatement.h"
#include "asts/IfExpr.h"
#include "asts/ErrorExpr.h"
#include "asts/ConstExpr.h"
#include <string>

Parser::Parser(Scanner& _s): s(_s) {}

Parser::~Parser() {}

Expression* Parser::parseLine() {
    switch (s.getToken().type){
    case TOK_EOF:
        return nullptr;
        break;
    case TOK_SEMI:
        s.getToken();
        return parseLine();
        break;
    case TOK_TYPE_DOUBLE:
    case TOK_TYPE_INT:
        return parseGlobalDeclare();
    default:
        break;
    }
    return new ErrorExpr("Unexpect Token: " + s.currentToken.strLiteral + " when parsing line");
}

Expression* Parser::parseGlobalDeclare() {
    TOKENS type = s.currentToken.type;
    if (s.getToken().type != TOK_IND) {
        s.getToken();
        return new ErrorExpr("Expect identifier at line: " + to_string(s.getCurrentLine()) + " but get " + s.currentToken.strLiteral + " instead.");
    }

    string name = s.currentToken.strLiteral;
    s.getToken();
    Expression* node = nullptr;

    if (s.currentToken.type == TOK_OP_ASSIGN) {
        s.getToken();
        node = new GlobalDeclareNode(name, type, s.currentToken.intVal, s.currentToken.floatVal);
        s.getToken();
    }
    else if (s.currentToken.type == TOK_SEMI){
        node = new GlobalDeclareNode(name, type);
    }
    else if (s.currentToken.type == TOK_OP_LEFTPAR){
        node = parseFunction(name, type);
        return node;
    }

    if (s.currentToken.type != TOK_SEMI) {
        s.getToken();
        return new ErrorExpr("Expect semi-colon at line: " + to_string(s.getCurrentLine()));
    }
    else {
        return node;
    }

    return new ErrorExpr("Unexpect token at line: " + to_string(s.getCurrentLine()) + " " + s.currentToken.strLiteral);
}


BlockNode* Parser::parseBlock() {
    vector<Expression *> exps;
    while (s.getToken().type != TOK_CUR_RIGHT && s.currentToken.type != TOK_EOF) {
        exps.push_back(parsePrimary());
    }
    return new BlockNode(exps);
}

ASTNode* Parser::parsePrimary() {
    switch (s.currentToken.type){
        case TOK_OP_NOT:
        case TOK_OP_MINUS:
            return parseUnary();
        case TOK_IF:
            return parseIf();
        case TOK_TYPE_INT:
        case TOK_TYPE_DOUBLE:
            return parseDeclare();
        case TOK_INT:
            return parseInteger();
        case TOK_FLOAT:
            return parseDouble();
        case TOK_RETURN:
            return parseReturn();
        case TOK_IND:
            return parseIndExpression();
        case TOK_OP_LEFTPAR:
            return parseParExpression();
        case TOK_CUR_RIGHT:
            return new IntegerExpr(0);
        default:
            return new ErrorExpr("Unexpect token: " + s.currentToken.strLiteral + " when parsing primary");
    }
}