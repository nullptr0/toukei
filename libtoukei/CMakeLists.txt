set(SOURCES ankidb.cpp)

add_library(libtoukei ${SOURCES})

find_library(JSON_LIBRARY jansson)

target_link_libraries(libtoukei sqlite3)
target_link_libraries(libtoukei ${JSON_LIBRARY})
target_include_directories(libtoukei PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
