
project(tit_base)

add_library(tit_base
        thread.cpp
        mutex.h
        noncopyable.h
        atomic_int.h
        platform_thread.cpp
        timestamp.cpp
        simple_thread.cpp
        types.h
        )

target_link_libraries(tit_base pthread rt)


install(TARGETS tit_base DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/tit/base)
