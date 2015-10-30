project(screensaver.matrixtrails)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(kodi REQUIRED)
find_package(SOIL REQUIRED)

include(ExternalProject)

include_directories(${KODI_INCLUDE_DIR}
                    ${SOIL_INCLUDE_DIRS})

set(MATRIXTRAILS_SOURCES src/column.cpp
                         src/main.cpp
                         src/matrixtrails.cpp)

set(DEPLIBS ${SOIL_LIBRARY})

build_addon(screensaver.matrixtrails MATRIXTRAILS DEPLIBS)

include(CPack)
