add_library(vla STATIC vla.c)
target_include_directories(vla PUBLIC ../inc)

add_library(cbuf STATIC cbuf.c)
target_include_directories(cbuf PUBLIC ../inc)

add_library(map STATIC map.c)
target_include_directories(map PUBLIC ../inc)

add_library(hashmap STATIC hashmap.c)
target_include_directories(hashmap PUBLIC ../inc)

add_library(structs STATIC structs.c)
target_include_directories(structs PUBLIC ../inc)
