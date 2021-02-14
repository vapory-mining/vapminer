cmake_policy(SET CMP0015 NEW)

aux_source_directory(. SRC_LIST)

include_directories(BEFORE ..)

set(EXECUTABLE vapminer)

file(GLOB HEADERS "*.h")

add_executable(${EXECUTABLE} ${SRC_LIST} ${HEADERS})
if(MSVC)
	target_sources(${EXECUTABLE} PRIVATE vapminer.rc)
endif()

hunter_add_package(CLI11)
find_package(CLI11 CONFIG REQUIRED)

target_link_libraries(vapminer PRIVATE vapcore poolprotocols devcore vapminer-buildinfo CLI11::CLI11 Boost::system Boost::thread)

if(ETHDBUS)
	find_package(PkgConfig)
	set( ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/lib/x86_64-linux-gnu/pkgconfig" )
	pkg_check_modules(DBUS dbus-1)
	include_directories(${DBUS_INCLUDE_DIRS})
	link_directories(${DBUS_LIBRARY_DIRS})
	target_link_libraries(vapminer PRIVATE ${DBUS_LIBRARIES})
endif()

if(APICORE)
	target_link_libraries(vapminer PRIVATE apicore)
endif()

include(GNUInstallDirs)
install(TARGETS vapminer DESTINATION ${CMAKE_INSTALL_BINDIR})
if(MSVC)
    install(FILES $<TARGET_PDB_FILE:vapminer> DESTINATION ${CMAKE_INSTALL_BINDIR} OPTIONAL)
endif()
