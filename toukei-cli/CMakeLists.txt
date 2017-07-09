set(SOURCES cli.cpp)

add_executable (toukei-cli cli.cpp ${SOURCES})

target_link_libraries(toukei-cli LINK_PUBLIC libtoukei)
