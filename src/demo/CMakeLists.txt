add_executable(demo_vla demo_vla.c)
target_include_directories(demo_vla PUBLIC ../../inc)
target_link_libraries(demo_vla structs)

add_executable(demo_cbuf demo_cbuf.c)
target_include_directories(demo_cbuf PUBLIC ../../inc)
target_link_libraries(demo_cbuf structs)

add_executable(demo_map demo_map.c)
target_include_directories(demo_map PUBLIC ../../inc)
target_link_libraries(demo_map structs)

add_executable(demo_hashmap demo_hashmap.c)
target_include_directories(demo_hashmap PUBLIC ../../inc)
target_link_libraries(demo_hashmap structs)

add_executable(demo_tree demo_tree.c)
target_include_directories(demo_tree PUBLIC ../../inc)
target_link_libraries(demo_tree structs)
