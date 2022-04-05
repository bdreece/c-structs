add_library(vla STATIC vla.c)
target_include_directories(vla PUBLIC ../inc)

add_library(ringbuf STATIC ringbuf.c)
target_include_directories(ringbuf PUBLIC ../inc)

add_library(map STATIC map.c)
target_include_directories(map PUBLIC ../inc)

# add_library(hashmap STATIC hashmap.c)
# target_include_directories(hashmap PUBLIC ../inc)

add_library(structs STATIC structs.c)
target_include_directories(structs PUBLIC ../inc)
