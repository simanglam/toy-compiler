#include "Parser.h"
#include "asts/VariableNode.h"
#include "asts/DeclareNode.h"
#include "asts/GlobalDeclareNode.h"
#include "asts/PrototypeAST.h"
#include "asts/FunctionAST.h"
#include "asts/ErrorExpr.h"

#include "types/TypeInfo.h"
#include "types/DoubleTypeInfo.h"
#include "types/SignedInt32Type.h"
#include "types/MemoryType.h"


Statement* Parser::parseFunction(string name, TOKENS returnType) {
    vector<DeclareNode*> args;
    while (s.currentToken.type != TOK_OP_RIGHTPAR){
        s.getToken();
        DeclareNode* arg = parseFunctionDeclare();
        if (arg) args.push_back(arg);
    }
    if (s.getToken().type == TOK_SEMI){
        return new PrototypeAST(name, args, returnType);
    }
    if (s.currentToken.type != TOK_CUR_LEFT){ 
        return (Statement*) new ErrorExpr("expect { or ;");
    }
    return new FunctionAST(new PrototypeAST(name, args, returnType), parseBlock());
}

DeclareNode* Parser::parseFunctionDeclare() {
    TypeInfo* type = nullptr;
    switch (s.currentToken.type) {
        case TOK_TYPE_INT:
            type = new SignedInt32Type();
            break;
        case TOK_TYPE_DOUBLE:
            type = new DoubleTypeInfo();
            break;
        case TOK_OP_RIGHTPAR:
            return nullptr;
        default:
            return (DeclareNode *) new ErrorExpr("Unexpect Token: " + s.currentToken.strLiteral);
    }
    s.getToken();
    if (s.currentToken.type == TOK_IND) {
        DeclareNode* node = new DeclareNode(type, s.currentToken.strLiteral);
        s.getToken();
        return node;
    }
    else if (s.currentToken.type == TOK_COMMA || s.currentToken.type == TOK_OP_RIGHTPAR) {
        return new DeclareNode(type, "");
    }
    return nullptr;
}