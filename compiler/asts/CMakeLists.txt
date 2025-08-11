file(GLOB SRC_FILES
    "*.cpp"
    "CastNode/*.cpp"
    "BinaryOpNode/*.cpp"
)

add_library(asts ${SRC_FILES})
target_compile_options(asts PRIVATE --debug)