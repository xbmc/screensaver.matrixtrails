project(SOIL)

cmake_minimum_required(VERSION 2.8)

file(READ ${PROJECT_SOURCE_DIR}/depends/common/SOIL/SOIL.txt SOIL_URL)
STRING(REGEX REPLACE "\n" "" SOIL_URL "${SOIL_URL}")
STRING(REGEX REPLACE "SOIL " "" SOIL_URL "${SOIL_URL}")

include(ExternalProject)
ExternalProject_Add(SOIL
                    URL ${SOIL_URL}
                    PATCH_COMMAND patch -Np1 -i ${PROJECT_SOURCE_DIR}/depends/common/SOIL/linking_correctly.patch
                    CONFIGURE_COMMAND ""
                    BUILD_COMMAND cd <SOURCE_DIR>/src && make -f "../projects/makefile/alternate Makefile.txt"
                    INSTALL_COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/SOIL &&
                                    ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/src/SOIL.h ${CMAKE_CURRENT_BINARY_DIR}/SOIL &&
                                    ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/src/libSOIL.a ${CMAKE_CURRENT_BINARY_DIR}/SOIL
                    BUILD_IN_SOURCE 1
                    )
set(SOIL_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(SOIL_LIBRARIES ${CMAKE_CURRENT_BINARY_DIR}/SOIL/libSOIL.a)
