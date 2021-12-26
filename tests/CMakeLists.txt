find_package(
  Boost
  COMPONENTS unit_test_framework
  REQUIRED)

enable_testing()

add_executable(test_vla test_vla.cpp)
target_include_directories(test_vla PUBLIC ../inc)
target_link_libraries(test_vla structs ${Boost_UNIT_TEST_FRAMEWORK})
add_test(NAME vla COMMAND test_vla -r detailed)

add_executable(test_cbuf test_cbuf.cpp)
target_include_directories(test_cbuf PUBLIC ../inc)
target_link_libraries(test_cbuf structs ${Boost_UNIT_TEST_FRAMEWORK})
add_test(NAME cbuf COMMAND test_cbuf -r detailed)

add_executable(test_map test_map.cpp)
target_include_directories(test_map PUBLIC ../inc)
target_link_libraries(test_map structs ${Boost_UNIT_TEST_FRAMEWORK})
add_test(NAME map COMMAND test_map -r detailed)
