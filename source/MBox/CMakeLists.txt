file(
    GLOB c_files
    RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    "*.c"
)
add_custom_target(mbox ALL)
add_library(mboxstatic ${c_files})
add_library(mboxdynamic SHARED ${c_files})
add_dependencies(mbox mboxstatic mboxdynamic)
target_include_directories(
    mboxstatic
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_include_directories(
    mboxdynamic
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
install(
    TARGETS mboxstatic mboxdynamic
    DESTINATION lib
)

file(
    GLOB h_files
    RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    "*.h"
)
install(
    FILES ${h_files}
    DESTINATION include/MBox
)
