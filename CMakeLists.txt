project(screensaver.matrixtrails)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

enable_language(CXX)

find_package(Kodi REQUIRED)

if(APP_RENDER_SYSTEM STREQUAL "gl" OR NOT APP_RENDER_SYSTEM)
  find_package(OpenGl REQUIRED)
  set(DEPLIBS ${OPENGL_LIBRARIES})
  set(includes ${OPENGL_INCLUDE_DIR})
  add_definitions(${OPENGL_DEFINITIONS})
elseif(APP_RENDER_SYSTEM STREQUAL "gles")
  find_package(OpenGLES REQUIRED)
  set(DEPLIBS ${OPENGLES_LIBRARIES})
  set(includes ${OPENGLES_INCLUDE_DIR})
  add_definitions(${OPENGLES_DEFINITIONS})
endif()

if(NOT OPENGL_FOUND AND NOT OPENGLES_FOUND)
  message(FATAL_ERROR "No rendering API found. Bailing")
endif()

add_subdirectory(lib/SOIL2)

include_directories(${KODI_INCLUDE_DIR}/..) # Hack way with "/..", need bigger Kodi cmake rework to match right include ways

set(MATRIXTRAILS_SOURCES src/column.cpp
                         src/main.cpp
                         src/matrixtrails.cpp
                         src/shaders/GUIShader.cpp
                         src/shaders/Matrix.cpp
                         src/shaders/Shader.cpp)

set(MATRIXTRAILS_HEADERS src/column.h
                         src/main.h
                         src/matrixtrails.h
                         src/timer.h
                         src/types.h
                         src/shaders/GUIShader.h
                         src/shaders/Matrix.h
                         src/shaders/Shader.h)

list(APPEND DEPLIBS soil2)

build_addon(screensaver.matrixtrails MATRIXTRAILS DEPLIBS)

include(CPack)
