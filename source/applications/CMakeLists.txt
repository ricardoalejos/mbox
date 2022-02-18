add_custom_target(application)

function(add_applications)
    foreach(app_source_name IN LISTS ARGV)
        string(REGEX REPLACE "\\.[^.]*$" "" app_name ${app_source_name})
        message("Adding application ${app_name}.")
        add_executable(${app_name} ${app_name}.c)
        target_link_libraries(${app_name} mboxdynamic)
        install(
            TARGETS ${app_name}
            DESTINATION bin
        )
        add_dependencies(application ${app_name})
        add_test(
            NAME "run_${app_name}"
            COMMAND "bin/${app_name}"
            WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX})
    endforeach()
endfunction()

file(
    GLOB c_files
    RELATIVE ${CMAKE_CURRENT_LIST_DIR}
    "*.c"
)

add_applications(${c_files})
