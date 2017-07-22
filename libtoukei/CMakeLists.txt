set(SOURCES ankidb.cpp deck.cpp)

add_library(toukei ${SOURCES})
set_property(TARGET toukei PROPERTY POSITION_INDEPENDET_CODE ON)

find_library(JSON_LIBRARY jansson)

target_link_libraries(toukei sqlite3)
target_link_libraries(toukei ${JSON_LIBRARY})
target_include_directories(toukei PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
