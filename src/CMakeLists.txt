add_library(structs STATIC cbuf.c hashmap.c map.c vla.c)
target_include_directories(structs PUBLIC ../inc)

add_executable(demo_libstructs demo.c)
target_include_directories(demo_libstructs PUBLIC ../inc)
target_link_libraries(demo_libstructs structs)
