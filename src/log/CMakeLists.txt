project(tit_log)

add_library(tit_log
        logging.cpp
        log_stream.cpp)

#target_link_libraries(tit_log)

install(TARGETS tit_log DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/tit/log)