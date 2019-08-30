cmake_minimum_required(VERSION 3.5)

project(SOIL2)

set(CMAKE_POSITION_INDEPENDENT_CODE 1)

set(SRC_FILES
      SOIL2.c
      etc1_utils.c
      image_DXT.c
      image_helper.c
)

set(HEADER_FILES
      SOIL2.h
      etc1_utils.h
      image_DXT.h
      image_helper.h
      pkm_helper.h
      pvr_helper.h
      stb_image.h
      stb_image_write.h
      stbi_DDS.h
      stbi_DDS_c.h
      stbi_ext.h
      stbi_ext_c.h
      stbi_pkm.h
      stbi_pkm_c.h
      stbi_pvr.h
      stbi_pvr_c.h
)

add_library(soil2 STATIC ${SRC_FILES} ${HEADER_FILES})
target_include_directories(soil2 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/..)
if(CORE_SYSTEM_NAME STREQUAL darwin_embedded OR CORE_SYSTEM_NAME STREQUAL osx OR CORE_SYSTEM_NAME STREQUAL ios)
  target_link_libraries(soil2 PUBLIC "-framework CoreFoundation")
elseif(OPENGLES_FOUND)
  target_compile_definitions(soil2 PRIVATE SOIL_GLES2)
  target_link_libraries(soil2 PRIVATE ${OPENGLES_LIBRARIES})
endif()
