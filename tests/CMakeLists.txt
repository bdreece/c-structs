find_package(
  Boost
  COMPONENTS unit_test_framework
  REQUIRED)

enable_testing()

add_executable(test_vla test_vla.cpp)
target_include_directories(test_vla PUBLIC . ../inc)
target_link_libraries(test_vla vla ${Boost_UNIT_TEST_FRAMEWORK})
add_test(NAME vla COMMAND test_vla --logger=HRF,message,test_vla.log -r detailed)

add_executable(test_cbuf test_cbuf.cpp)
target_include_directories(test_cbuf PUBLIC . ../inc)
target_link_libraries(test_cbuf cbuf ${Boost_UNIT_TEST_FRAMEWORK})
add_test(NAME cbuf COMMAND test_cbuf --logger=HRF,message,test_cbuf.log -r detailed)

add_executable(test_map test_map.cpp)
target_include_directories(test_map PUBLIC . ../inc)
target_link_libraries(test_map map ${Boost_UNIT_TEST_FRAMEWORK})
add_test(NAME map COMMAND test_map --logger=HRF,message,test_map.log -r detailed)

if(FALSE)
  add_executable(test_hashmap test_hashmap.cpp)
  target_include_directories(test_hashmap PUBLIC . ../inc)
  target_link_libraries(test_hashmap hashmap ${Boost_UNIT_TEST_FRAMEWORK})
  add_test(NAME hashmap COMMAND test_hashmap -r detailed)
endif()
