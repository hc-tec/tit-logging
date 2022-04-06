project(tit_logging)

add_library(tit_logging
        logging.cpp
        LogStream.cpp)

target_link_libraries(tit_logging pthread rt)

install(TARGETS tit_logging DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/tit/logging)