
#include "Parser.h"
#include "asts/DeclareNode.h"
#include "asts/DeclareStatement.h"
#include "asts/GlobalDeclareNode.h"
#include "asts/PrototypeAST.h"
#include "asts/FunctionAST.h"
#include "asts/ReturnStatement.h"
#include "asts/IfStatement.h"
#include "asts/ErrorExpr.h"
#include "asts/ConstExpr.h"

#include "types/TypeInfo.h"
#include "types/SignedInt32Type.h"
#include "types/DoubleTypeInfo.h"

#include <string>

Parser::Parser(Scanner& _s): s(_s) {}

Parser::~Parser() {}

ASTNode* Parser::parseLine() {
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

Statement* Parser::parseGlobalDeclare() {
    TOKENS token_type = s.currentToken.type;
    TypeInfo* type = nullptr;

    switch (s.currentToken.type) {
        case TOK_TYPE_INT:
            type = new SignedInt32Type();
            break;
        case TOK_TYPE_DOUBLE:
            type = new DoubleTypeInfo();
            break;
    }
    
    if (s.getToken().type != TOK_IND) {
        s.getToken();
        return (Statement*) new ErrorExpr("Expect identifier at line: " + to_string(s.getCurrentLine()) + " but get " + s.currentToken.strLiteral + " instead.");
    }

    string name = s.currentToken.strLiteral;
    s.getToken();
    DeclareStatement* node = new DeclareStatement();

    if (s.currentToken.type == TOK_OP_ASSIGN) {
        s.getToken();
        node->pushNode(new DeclareNode(type, name, DeclareNodeStrategy::getStrategy(DeclareType::GLOBAL), parseExpression()));
        
    }
    else if (s.currentToken.type == TOK_SEMI){
        node->pushNode(new DeclareNode(type, name, DeclareNodeStrategy::getStrategy(DeclareType::GLOBAL)));
    }
    else if (s.currentToken.type == TOK_OP_LEFTPAR){
        return parseFunction(name, type);
    }

    if (s.currentToken.type != TOK_SEMI) {
        s.getToken();
        return (Statement*) new ErrorExpr("Expect semi-colon at line: " + to_string(s.getCurrentLine()));
    }
    else {
        return node;
    }

    return (Statement*) new ErrorExpr("Unexpect token at line: " + to_string(s.getCurrentLine()) + " " + s.currentToken.strLiteral);
}


BlockNode* Parser::parseBlock() {
    vector<ASTNode*> exps;
    while (s.getToken().type != TOK_CUR_RIGHT && s.currentToken.type != TOK_EOF) {
        exps.push_back(parseLinePrimary());
    }
    return new BlockNode(exps);
}

ASTNode* Parser::parseLinePrimary() {
    switch (s.currentToken.type) {
        case TOK_IF:
            return parseIf();
        case TOK_TYPE_INT:
        case TOK_TYPE_DOUBLE:
            return parseDeclare();
        case TOK_RETURN:
            return parseReturn();
        default:
            return parsePrimary();
    }
}

Expression* Parser::parsePrimary() {
    switch (s.currentToken.type){
        case TOK_OP_NOT:
        case TOK_OP_MINUS:
            return parseUnary();
        case TOK_INT:
            return parseInteger();
        case TOK_FLOAT:
            return parseDouble();
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