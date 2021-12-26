add_library(structs STATIC cbuf.c map.c vla.c)
target_include_directories(structs PUBLIC ../inc)
