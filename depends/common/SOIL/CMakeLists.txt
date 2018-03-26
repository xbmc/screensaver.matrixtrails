cmake_minimum_required(VERSION 3.0)

project(SOIL VERSION 1.07.20071110 LANGUAGES C)

add_library(${PROJECT_NAME}
  src/image_DXT.c
  src/image_helper.c
  src/SOIL.c
  src/stb_image_aug.c
)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
)

install(FILES ${PROJECT_SOURCE_DIR}/src/SOIL.h DESTINATION include/SOIL)
