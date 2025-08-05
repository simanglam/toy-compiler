file(GLOB SRC_FILES
    "*.cpp"
    "CastNode/*.cpp"
)

add_library(asts ${SRC_FILES} CastNode)
target_compile_options(asts PRIVATE --debug)