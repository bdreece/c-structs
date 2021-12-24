add_library(structs STATIC cbuf.c map.c vla.c)
target_include_directories(structs PUBLIC ../inc)

add_library(vla STATIC vla.c)
target_include_directories(vla PUBLIC ../inc)

add_library(cbuf STATIC cbuf.c)
target_include_directories(cbuf PUBLIC ../inc)

add_library(map STATIC vla.c map.c)
target_include_directories(map PUBLIC ../inc)
