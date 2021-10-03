add_library(structs STATIC cbuf.c hashmap.c map.c vla.c)
target_include_directories(structs PUBLIC ../inc)

add_subdirectory(demo)