#include "Analyser.h"

Analyser::Analyser() {

}

Analyser::~Analyser() {
    
}

bool Analyser::eval(BaseExpr* e) {
    e->eval(*this);
}