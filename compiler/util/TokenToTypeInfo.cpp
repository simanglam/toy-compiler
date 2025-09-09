#include "util/TokenToTypeInfo.h"

#include "types/TypeInfo.h"
#include "types/MemoryType.h"
#include "types/DoubleTypeInfo.h"
#include "types/SignedInt32Type.h"

TypeInfo* tokenToTypeInfo(TOKENS t) {
    switch (t) {
        case TOK_TYPE_DOUBLE:
            return new DoubleTypeInfo();
        case TOK_TYPE_INT:
            return new SignedInt32Type();
        default:
            break;
    }
    return nullptr;
}