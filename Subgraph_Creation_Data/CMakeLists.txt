set(lib_name Subgraph_Creation_Data)

add_library( ${lib_name}
        "${lib_name}.h" "${lib_name}.c"
)

target_link_libraries(${lib_name} PUBLIC Graph Matrix Steiner_Points)

target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR})