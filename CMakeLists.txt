cmake_minimum_required(VERSION 3.5)
project(screensaver.matrixtrails)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

find_package(Kodi REQUIRED)

if(NOT WIN32 AND (APP_RENDER_SYSTEM STREQUAL "gl" OR NOT APP_RENDER_SYSTEM))
  find_package(OpenGl REQUIRED)
  set(DEPLIBS ${OPENGL_LIBRARIES})
  set(includes ${OPENGL_INCLUDE_DIR})
  add_definitions(${OPENGL_DEFINITIONS})
else()
  find_package(OpenGLES REQUIRED)
  set(DEPLIBS ${OPENGLES_LIBRARIES})
  set(includes ${OPENGLES_INCLUDE_DIR})
  add_definitions(${OPENGLES_DEFINITIONS})
endif()

include_directories(${KODI_INCLUDE_DIR}/..) # Hack way with "/..", need bigger Kodi cmake rework to match right include ways

add_subdirectory(lib/SOIL2)

set(MATRIXTRAILS_SOURCES src/column.cpp
                         src/main.cpp
                         src/matrixtrails.cpp)

set(MATRIXTRAILS_HEADERS src/column.h
                         src/main.h
                         src/matrixtrails.h
                         src/timer.h
                         src/types.h)

list(APPEND DEPLIBS soil2)

build_addon(screensaver.matrixtrails MATRIXTRAILS DEPLIBS)

include(CPack)
