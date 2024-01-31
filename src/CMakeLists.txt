set(lib_name Src)

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_library (${lib_name}
        "kmb.h" "kmb.c"

)

target_link_libraries(${lib_name} PUBLIC Utilities Graph Steiner_Points Matrix Dijkstra_Shortest_Path Prim_MST Distance_Graph_Build Subgraph_Creation_Data)

target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR})