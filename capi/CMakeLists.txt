# ---------------------------------------------------------------------------
# LNLibC - standalone, language-agnostic C API for the LNLib kernel.
#
# Enabled from the top-level CMakeLists.txt with -DENABLE_C_API=ON. This module
# is self-contained: it consumes the `LNLib` target and adds no dependency to
# the rest of the project.
# ---------------------------------------------------------------------------

file(GLOB_RECURSE LNLIB_CAPI_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(LNLibC SHARED ${LNLIB_CAPI_SOURCES})

target_include_directories(LNLibC
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/lnlib"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/src/LNLib/include")

# The C API always compiles itself with LNLIB_CAPI_BUILD so its own functions
# are exported. LNLib is a separate target: when it is built shared, its headers
# must resolve LNLIB_EXPORT to dllimport (define nothing); when it is built
# static, define LNLIB_HOME + LNLIB_STATIC so LNLIB_EXPORT stays empty and the
# kernel symbols are linked in.
target_compile_definitions(LNLibC PRIVATE LNLIB_CAPI_BUILD)
if(NOT LNLib_BUILD_SHARED)
    target_compile_definitions(LNLibC PRIVATE LNLIB_HOME LNLIB_STATIC)
endif()

target_link_libraries(LNLibC PRIVATE LNLib)

set_target_properties(LNLibC PROPERTIES
    OUTPUT_NAME "LNLibC"
    PREFIX "")           # Windows-style name (LNLibC.dll) on every toolchain

if(MSVC)
    target_compile_options(LNLibC PRIVATE /W3)
else()
    target_compile_options(LNLibC PRIVATE -Wall)
endif()

# C API tests: one standalone executable per tests/*.c file, registered with
# CTest. Disable with -DENABLE_C_API_TESTS=OFF. (enable_testing() is called in
# the top-level CMakeLists.txt when ENABLE_C_API is on.)
option(ENABLE_C_API_TESTS "Build the C API tests" ON)
if(ENABLE_C_API_TESTS)
    add_subdirectory(tests)
endif()
