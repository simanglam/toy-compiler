#include "types/TypeInfo.h"
#include "types/MemoryType.h"
#include "types/DoubleTypeInfo.h"
#include "types/SignedInt32Type.h"

TypeInfo::TypeInfo() {};
TypeInfo::~TypeInfo() {};

static DoubleTypeInfo doubleTypeInfo;
static SignedInt32Type intTypeInfo;

TypeInfo* TypeInfo::getDoubleType() {
    return &doubleTypeInfo;
}

TypeInfo* TypeInfo::getMemoryType(TypeInfo* baseType) {
    return new MemoryType(baseType);
}

TypeInfo* TypeInfo::getIntType() {
    return &intTypeInfo;
}