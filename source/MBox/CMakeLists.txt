file(
    GLOB c_files
    RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    "*.c"
)
add_library(mbox ${c_files})
target_include_directories(
    mbox
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
install(
    TARGETS mbox
    DESTINATION lib
)

file(
    GLOB h_files
    RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    "*.h"
)
install(
    FILES ${h_files}
    DESTINATION include
)
