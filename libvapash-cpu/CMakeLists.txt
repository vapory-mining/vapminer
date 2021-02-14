file(GLOB sources "*.cpp")
file(GLOB headers "*.h")

add_library(vapash-cpu ${sources} ${headers})
#target_link_libraries(vapash-cpu vapcore vapash::vapash Boost::fiber Boost::thread)
target_link_libraries(vapash-cpu vapcore vapash::vapash Boost::thread)
target_include_directories(vapash-cpu PRIVATE .. ${CMAKE_CURRENT_BINARY_DIR})
