file(GLOB SRC_FILES
    "*.cpp"
)

add_library(types ${SRC_FILES})
target_compile_options(types PRIVATE --debug)