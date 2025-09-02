


add_subdirectory(asts)
add_subdirectory(parser)
add_subdirectory(types)


add_library(scanner Scanner.cpp)
target_compile_options(scanner PRIVATE --debug)

add_library(compiler Compiler.cpp)
target_compile_options(compiler PRIVATE --debug)

add_library(analyser Analyser.cpp)
target_compile_options(analyser PRIVATE --debug)

add_library(commandLineParser CommandLineParser.cpp)
target_compile_options(commandLineParser PRIVATE --debug)

target_link_libraries(compiler analyser scanner asts parser commandLineParser types ${LLVM_LIB_PATH} ${LLVM_LIB})

