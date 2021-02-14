cmake_minimum_required(VERSION 3.5)

include(cmake/cable/bootstrap.cmake)

include(CableBuildInfo)
include(CableBuildType)
include(CableToolchains)
include(HunterGate)

include(defaults/HunterCacheServers)

cable_configure_toolchain(DEFAULT cxx11)

set(HUNTER_CONFIGURATION_TYPES Release CACHE STRING "Build type of Hunter packages")
set(HUNTER_JOBS_NUMBER 6 CACHE STRING "Number of parallel builds used by Hunter")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.112.tar.gz"
    SHA1 "4b894e1d5d203f0cc9a77431dbb1b486ab6f4430"
    LOCAL
)

project(vapminer)
set(PROJECT_VERSION 0.19.0)

cable_set_build_type(DEFAULT Release CONFIGURATION_TYPES Release RelWithDebInfo)

option(VAPASHCL "Build with OpenCL mining" ON)
option(VAPASHCUDA "Build with CUDA mining" ON)
option(VAPASHCPU "Build with CPU mining (only for development)" OFF)
option(ETHDBUS "Build with D-Bus support" OFF)
option(APICORE "Build with API Server support" ON)
option(BINKERN "Install AMD binary kernels" ON)
option(DEVBUILD "Log developer metrics" OFF)
option(USE_SYS_OPENCL "Build with system OpenCL" OFF)

# propagates CMake configuration options to the compiler
function(configureProject)
    if (VAPASHCL)
        add_definitions(-DETH_VAPASHCL)
    endif()
    if (VAPASHCUDA)
        add_definitions(-DETH_VAPASHCUDA)
    endif()
    if (VAPASHCPU)
        add_definitions(-DETH_VAPASHCPU)
    endif()
    if (ETHDBUS)
        add_definitions(-DETH_DBUS)
    endif()
    if (APICORE)
        add_definitions(-DAPI_CORE)
    endif()
    if (BINKERN)
        add_definitions(-DBIN_KERN)
    endif()
    if (DEVBUILD)
        add_definitions(-DDEV_BUILD)
    endif()
    if (USE_SYS_OPENCL)
        add_definitions(-DUSE_SYS_OPENCL)
    endif()
endfunction()

hunter_add_package(Boost COMPONENTS system filesystem thread)
find_package(Boost CONFIG REQUIRED COMPONENTS system filesystem thread)

hunter_add_package(jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)

hunter_add_package(vapash)
find_package(vapash CONFIG REQUIRED)

configureProject()

if(APPLE)
    set(USE_SYS_OPENCL ON)
endif()

message("----------------------------------------------------------------------------")
message("-- CMake ${CMAKE_VERSION}")
message("-- Build ${CMAKE_BUILD_TYPE} / ${CMAKE_SYSTEM_NAME}")
message("----------------------------------------------------------------- components")
message("-- VAPASHCL         Build OpenCL components                      ${VAPASHCL}")
message("-- VAPASHCUDA       Build CUDA components                        ${VAPASHCUDA}")
message("-- VAPASHCPU        Build CPU components (only for development)  ${VAPASHCPU}")
message("-- ETHDBUS          Build D-Bus components                       ${ETHDBUS}")
message("-- APICORE          Build API Server components                  ${APICORE}")
message("-- BINKERN          Install AMD binary kernels                   ${BINKERN}")
message("-- DEVBUILD         Build with dev logging                       ${DEVBUILD}")
message("-- USE_SYS_OPENCL   Build with system OpenCL                     ${USE_SYS_OPENCL}")
message("----------------------------------------------------------------------------")
message("")

include(EthCompilerSettings)
if(UNIX AND NOT APPLE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
endif()

cable_add_buildinfo_library(PROJECT_NAME ${PROJECT_NAME})

add_subdirectory(libdevcore)
add_subdirectory(libvapcore)
add_subdirectory(libhwmon)
add_subdirectory(libpoolprotocols)

if (VAPASHCL)
    add_subdirectory(libvapash-cl)
    if (BINKERN)
        add_subdirectory(libvapash-cl/kernels)
    endif()
endif ()
if (VAPASHCUDA)
    add_subdirectory(libvapash-cuda)
endif ()
if (VAPASHCPU)
    add_subdirectory(libvapash-cpu)
endif ()
if (APICORE)
    add_subdirectory(libapicore)
endif()

add_subdirectory(vapminer)


if(WIN32)
    set(CPACK_GENERATOR ZIP)
else()
    set(CPACK_GENERATOR TGZ)
endif()
set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CHECKSUM SHA256)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY FALSE)
include(CPack)
