

aux_source_directory(. base_SRCS)

add_library(tit_base ${base_SRCS})

target_link_libraries(tit_base pthread rt)


install(TARGETS tit_base DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/tit/base)
