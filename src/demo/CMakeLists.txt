add_executable(demo_vla vla_demo.c)
target_include_directories(demo_vla PUBLIC ../../inc)
target_link_libraries(demo_vla structs)

add_executable(demo_cbuf cbuf_demo.c)
target_include_directories(demo_cbuf PUBLIC ../../inc)
target_link_libraries(demo_cbuf structs)
