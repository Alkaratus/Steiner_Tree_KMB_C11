set(lib_name Distance_Graph_Build)

add_library( ${lib_name}
        "${lib_name}.h" "${lib_name}.c"
)

target_link_libraries(${lib_name} PUBLIC Graph Path_To_Source Steiner_Points)

target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR})