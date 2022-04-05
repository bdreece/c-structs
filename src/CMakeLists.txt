add_library(vla STATIC vla.c)
target_include_directories(vla PUBLIC ../inc)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(vla PUBLIC DEBUG)
endif()

add_library(ringbuf STATIC ringbuf.c)
target_include_directories(ringbuf PUBLIC ../inc)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(ringbuf PUBLIC DEBUG)
endif()

add_library(map STATIC map.c)
target_include_directories(map PUBLIC ../inc)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(map PUBLIC DEBUG)
endif()

# add_library(hashmap STATIC hashmap.c) target_include_directories(hashmap
# PUBLIC ../inc)

add_library(structs STATIC structs.c)
target_include_directories(structs PUBLIC ../inc)
