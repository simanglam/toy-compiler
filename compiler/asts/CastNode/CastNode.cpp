#include "asts/CastNode.h"

CastNode::CastNode(Expression* _expr, EVALTYPE target, CastNodeStrategy& _castStrategy): expr(_expr), castStrategy(_castStrategy) {
    evalType = target;
}

CastNode::~CastNode() {
    delete expr;
}

llvm::Value* CastNode::codegenExpr(Compiler& c) {
    return castStrategy.cast(expr->codegenExpr(c), evalType, c);
}

bool CastNode::eval(Analyser& a) {
    return castStrategy.eval(evalType);
}