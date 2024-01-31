set(lib_name Edge)

add_library( ${lib_name}
        "Edge.h" "Edge.c"
)

target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR})