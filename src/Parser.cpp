#include "Parser.h"
#include "asts/BinaryOpNode.h"
#include "asts/NumberNode.h"
#include "asts/VariableNode.h"
#include "asts/DeclearNode.h"
#include "asts/GlobalDeclearNode.h"
#include "asts/PrototypeAST.h"
#include "asts/FunctionAST.h"

static int getTokenPrec(const Token& t) {
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

Parser::~Parser() {}

BaseExpr* Parser::parseLine() {
    switch (s.getToken().type){
    case TOK_EOF:
        break;
    case TOK_SEMI:
        s.getToken();
        break;
    case TOK_TYPE_DOUBLE:
    case TOK_TYPE_INT:
        return parseGlobalDeclear();
    default:
        BaseExpr* node = parseExpression();
        return node;
        break;
    }
    return nullptr;
}

BaseExpr* Parser::parseGlobalDeclear() {
    TOKENS type = s.currentToken.type;
    if (s.getToken().type != TOK_IND) {
        cerr << "Expect identifier at line: " << s.getCurrentLine() << " but get " << s.currentToken.strLiteral << " instead." << endl;
        s.getToken();
        return nullptr;
    }

    string name = s.currentToken.strLiteral;
    s.getToken();
    BaseExpr* node = nullptr;

    if (s.currentToken.type == TOK_OP_EQUAL) {
        s.getToken();
        node = new GlobalDeclearNode(name, type, s.currentToken.numVal);
        s.getToken();
    }
    else if (s.currentToken.type == TOK_SEMI){
        node = new GlobalDeclearNode(name, type);
    }
    else if (s.currentToken.type == TOK_OP_LEFTPAR){
        s.getToken();
        node = parseFunction(name, type);
        return node;
    }

    if (s.currentToken.type != TOK_SEMI) {
        cerr << "Expect semi-colon at line: " << s.getCurrentLine() << endl;
        s.getToken();
        return nullptr;
    }
    return node;
}

BaseExpr* Parser::parseFunction(string name, TOKENS returnType) {
    vector<DeclearNode*> args;
    while (s.currentToken.type != TOK_OP_RIGHTPAR){
        s.getToken();
        DeclearNode* arg = parseDeclear();
        if (!arg) return nullptr;
        args.push_back(arg);
    }
    if (s.getToken().type == TOK_SEMI){
        s.getToken();
        return new PrototypeAST(name, args, returnType);
    }
    if (s.currentToken.type != TOK_CUR_LEFT){ 
        cerr << "expect { or ;" << endl;
        return nullptr;
    }
    return new FunctionAST(new PrototypeAST(name, args, returnType), parseBlock());
}

BlockNode* Parser::parseBlock() {
    vector<BaseExpr *> exps;
    while (s.getToken().type != TOK_CUR_RIGHT) {
        exps.push_back(parsePrimary());
    }
    return new BlockNode(exps);
}

BaseExpr* Parser::parseExpression() {
    BaseExpr* lhs = parsePrimary();
    BaseExpr* node = parseBinOpRhs(0, lhs);
    return node;
}

BaseExpr* Parser::parsePrimary() {
    switch (s.currentToken.type){
    case TOK_TYPE_INT:
    case TOK_TYPE_DOUBLE:
        return parseDeclear();
    case TOK_NUM:
        return parseNumber();
    case TOK_IND:
        return parseIndExpression();
    case TOK_OP_LEFTPAR:
        return parseParExpression();
    default:
        return nullptr;
    }
}

BaseExpr* Parser::parseIndExpression() {
    if (s.nextToken.type != TOK_OP_LEFTPAR){
        BaseExpr* node = new VariableNode(s.currentToken.strLiteral);
        s.getToken();
        BaseExpr* expr = parseBinOpRhs(0, node);
        return expr;
    };
    return nullptr;
}

BaseExpr* Parser::parseParExpression() {
    s.getToken();
    BaseExpr* lhs = parsePrimary();
    BaseExpr* node = parseBinOpRhs(0, lhs);
    if (!node) cerr << "Error when parsing par expression" << endl;
    if (s.currentToken.type != TOK_OP_RIGHTPAR) {
        cerr << "Missing right par" << endl;
        return nullptr;
    }
    s.getToken();
    return node;
};

BaseExpr* Parser::parseBinOpRhs(int minPrec, BaseExpr* lhs){
    while (true){
        int tokPrec = getTokenPrec(s.currentToken);
        if (tokPrec < minPrec)
            return lhs;
        
        char op = s.currentToken.strLiteral[0];
        s.getToken();
        
        BaseExpr* rhs = parsePrimary();

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

DeclearNode* Parser::parseDeclear() {
    TOKENS type = s.currentToken.type;
    s.getToken();
    if (s.currentToken.type == TOK_COMMA || s.currentToken.type == TOK_OP_RIGHTPAR) {
        // cerr << "Expect identifier at line: " << s.getCurrentLine() << " but get " << s.currentToken.strLiteral << " instead." << endl;
        return new DeclearNode("", type);
    }

    string name = s.currentToken.strLiteral;
    s.getToken();
    DeclearNode* node = nullptr;

    if (s.currentToken.type == TOK_OP_EQUAL) {
        s.getToken();
        node = new DeclearNode(name, type, parsePrimary());
    }
    else {
        node = new DeclearNode(name, type);
    }

    if (s.currentToken.type == TOK_COMMA || s.currentToken.type == TOK_OP_RIGHTPAR) return node;

    if (s.currentToken.type != TOK_SEMI) {
        cerr << "Expect semi-colon at line: " << s.getCurrentLine() << endl;
        s.getToken();
        return nullptr;
    }
    return node;
}

BaseExpr* Parser::parseNumber() {
    BaseExpr* node = new NumberNode(s.currentToken.numVal);
    s.getToken();
    return node;
}