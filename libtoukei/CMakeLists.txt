set(SOURCES ankidb.cpp)

add_library(toukei ${SOURCES})

find_library(JSON_LIBRARY jansson)

target_link_libraries(toukei sqlite3)
target_link_libraries(toukei ${JSON_LIBRARY})
target_include_directories(toukei PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
