project(IRService)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Git)
if(GIT_FOUND)
    message("git found: ${GIT_EXECUTABLE}")
    message("git version: ${GIT_VERSION_STRING}")

    #ref: https://stackoverflow.com/questions/1435953/how-can-i-pass-git-sha1-to-compiler-as-definition-using-cmake
    exec_program(
        "git"
        ${CMAKE_CURRENT_SOURCE_DIR}
        ARGS "-C . describe"
        OUTPUT_VARIABLE VERSION_SHA1)
else()
    message("git not found")
    set(VERSION_SHA1 "unknown")
endif()
add_definitions(-DGIT_VERSION_SHA1="${VERSION_SHA1}")
message("version: ${VERSION_SHA1}")

if(MSVC)
else()
    set(CMAKE_CXX_FLAGS "-std=c++11 -DDISPLAY_STRING")
    #set(CMAKE_EXE_LINKER_FLAGS "-pthread")
endif()

# uninstall target
# ref: https://cmake.org/Wiki/CMake_FAQ#Can_I_do_.22make_uninstall.22_with_CMake.3F
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

add_subdirectory(src/irservice)

add_subdirectory(thirdparty/iniparser)
