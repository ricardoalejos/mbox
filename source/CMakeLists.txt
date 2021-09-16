cmake_minimum_required(VERSION 3.16)

project(MBOX C)
include(ExternalProject)
include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -g ")

link_directories(
    ${CMAKE_INSTALL_PREFIX}/lib
)

include_directories(
    ${CMAKE_INSTALL_PREFIX}/include
    ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/applications
)

add_subdirectory(
    ${CMAKE_CURRENT_LIST_DIR}/MBox
)

