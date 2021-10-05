add_library(structs STATIC cbuf.c hashmap.c map.c vla.c tree.c)
target_include_directories(structs PUBLIC ../inc)

add_library(vla STATIC vla.c)
target_include_directories(vla PUBLIC ../inc)

add_library(cbuf STATIC cbuf.c)
target_include_directories(cbuf PUBLIC ../inc)

add_library(map STATIC vla.c map.c)
target_include_directories(map PUBLIC ../inc)

add_library(hashmap STATIC vla.c map.c hashmap.c)
target_include_directories(hashmap PUBLIC ../inc)

add_library(tree STATIC vla.c tree.c)
target_include_directories(tree PUBLIC ../inc)

add_subdirectory(demo)
