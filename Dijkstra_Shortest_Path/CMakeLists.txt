set(lib_name Dijkstra_Shortest_Path)

add_library( ${lib_name}
        "${lib_name}.h" "${lib_name}.c"
)

target_link_libraries(${lib_name} PUBLIC Graph Path_To_Source)

target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR})