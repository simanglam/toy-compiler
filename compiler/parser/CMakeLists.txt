

execute_process(
    COMMAND llvm-config --cxxflags
    OUTPUT_VARIABLE LLVM_CXXFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND llvm-config --ldflags --system-libs --libs core native
    OUTPUT_VARIABLE LLVM_LDFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)


file(GLOB SRC_FILES
    "*.cpp"
)

add_library(parser ${SRC_FILES})
target_compile_options(parser PRIVATE ${LLVM_CXXFLAGS} --debug)