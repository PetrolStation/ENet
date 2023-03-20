cmake_minimum_required(VERSION 3.16)

PA_NEW(ENet)

PA_LINK_LIBRARIES( PRIVATE enet )

PA_INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/enet/include
)

File(GLOB_RECURSE SOURCE_FILES src/*.cpp )
File(GLOB_RECURSE HEADER_FILES src/*.h   )

PA_ADD_SOURCE_FILES(
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

add_subdirectory(deps)
