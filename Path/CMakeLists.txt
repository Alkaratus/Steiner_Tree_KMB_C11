set(lib_name Path)

add_library( ${lib_name}
        "${lib_name}.h" "${lib_name}.c"
)

target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR})