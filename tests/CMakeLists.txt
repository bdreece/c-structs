find_package(
  Boost
  COMPONENTS unit_test_framework
  REQUIRED)

enable_testing()

add_executable(test_vla test_vla.cpp)
target_include_directories(test_vla PUBLIC . ../inc)
target_link_libraries(test_vla vla ${Boost_UNIT_TEST_FRAMEWORK})
add_test(NAME vla COMMAND test_vla --logger=HRF,message,test_vla.log -r
                          detailed)

add_executable(test_ringbuf test_ringbuf.cpp)
target_include_directories(test_ringbuf PUBLIC . ../inc)
target_link_libraries(test_ringbuf ringbuf ${Boost_UNIT_TEST_FRAMEWORK})
add_test(NAME ringbuf COMMAND test_ringbuf
                              --logger=HRF,message,test_ringbuf.log -r detailed)

if(FALSE)
  add_executable(test_map test_map.cpp)
  target_include_directories(test_map PUBLIC . ../inc)
  target_link_libraries(test_map map ${Boost_UNIT_TEST_FRAMEWORK})
  add_test(NAME map COMMAND test_map --logger=HRF,message,test_map.log -r
                            detailed)
endif()

if(FALSE)
  add_executable(test_hashmap test_hashmap.cpp)
  target_include_directories(test_hashmap PUBLIC . ../inc)
  target_link_libraries(test_hashmap hashmap ${Boost_UNIT_TEST_FRAMEWORK})
  add_test(NAME hashmap COMMAND test_hashmap -r detailed)
endif()
