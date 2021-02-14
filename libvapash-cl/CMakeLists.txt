# A custom command and target to turn the OpenCL kernel into a byte array header
# The normal build depends on it properly and if the kernel file is changed, then
# a rebuild of libvapash-cl should be triggered

#TODO: clean up the copy&pasting here
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/vapash.h
	COMMAND ${CMAKE_COMMAND} ARGS
	-DBIN2H_SOURCE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/kernels/cl/vapash.cl"
	-DBIN2H_VARIABLE_NAME=vapash_cl
	-DBIN2H_HEADER_FILE="${CMAKE_CURRENT_BINARY_DIR}/vapash.h"
	-P "${CMAKE_CURRENT_SOURCE_DIR}/bin2h.cmake"
	COMMENT "Generating OpenCL Kernel Byte Array"
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cl/vapash.cl
)
add_custom_target(clbin2h_stable DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/vapash.h ${CMAKE_CURRENT_SOURCE_DIR}/cl/vapash.cl)

set(SOURCES
	CLMiner.h CLMiner.cpp
	${CMAKE_CURRENT_BINARY_DIR}/vapash.h
)

if(USE_SYS_OPENCL)
	# On macOS or using ROCm-OpenCL, use system OpenCL library.
	find_package(OpenCL REQUIRED)
else()
	hunter_add_package(OpenCL)
	find_package(OpenCL CONFIG REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(..)

add_library(vapash-cl ${SOURCES})
target_link_libraries(vapash-cl PUBLIC vapcore vapash::vapash)
target_link_libraries(vapash-cl PRIVATE OpenCL::OpenCL)
target_link_libraries(vapash-cl PRIVATE Boost::filesystem Boost::thread)
