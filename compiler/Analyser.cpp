#include "Analyser.h"

Analyser::Analyser() {

}

Analyser::~Analyser() {
    
}

bool Analyser::eval(Expression* e) {
    e->eval(*this);
}