# C tests. Every *.c is a standalone executable with its own main().
file(GLOB LNLIB_CAPI_TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

foreach(TEST_SOURCE ${LNLIB_CAPI_TEST_SOURCES})
    get_filename_component(TEST_NAME "${TEST_SOURCE}" NAME_WE)

    add_executable(${TEST_NAME} "${TEST_SOURCE}")
    target_include_directories(${TEST_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/../include"
        "${CMAKE_CURRENT_SOURCE_DIR}")
    target_link_libraries(${TEST_NAME} PRIVATE LNLibC)
    set_target_properties(${TEST_NAME} PROPERTIES FOLDER "LNLibAPI/Tests")

    # Place the DLL next to each test executable so it can be loaded.
    add_custom_command(TARGET ${TEST_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:LNLibC> $<TARGET_FILE_DIR:${TEST_NAME}>)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
