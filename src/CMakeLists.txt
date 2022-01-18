add_library(structs STATIC structs.c)
target_compile_options(structs PUBLIC -Os)
target_include_directories(structs PUBLIC ../inc)
