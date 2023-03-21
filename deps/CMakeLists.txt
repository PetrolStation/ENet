add_subdirectory(enet)

if(WIN32)
    target_link_libraries(enet winmm ws2_32)
endif()
