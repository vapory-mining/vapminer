set(SOURCES
	VapashAux.h VapashAux.cpp
	Farm.cpp Farm.h
	Miner.h Miner.cpp
)

include_directories(BEFORE ..)

add_library(vapcore ${SOURCES})
target_link_libraries(vapcore PUBLIC devcore vapash::vapash PRIVATE hwmon)

if(VAPASHCL)
	target_link_libraries(vapcore PRIVATE vapash-cl)
endif()
if(VAPASHCUDA)
	target_link_libraries(vapcore PUBLIC vapash-cuda)
endif()
if(VAPASHCPU)
	target_link_libraries(vapcore PUBLIC vapash-cpu)
endif()
