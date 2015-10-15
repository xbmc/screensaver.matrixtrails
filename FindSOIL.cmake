find_path(SOIL_INCLUDE_DIRS SOIL.h PATH_SUFFIXES SOIL)
find_library(SOIL_LIBRARIES NAMES SOIL)

if(NOT SOIL_LIBRARIES AND NOT SOIL_INCLUDE_DIRS)
  include(${PROJECT_SOURCE_DIR}/depends/common/SOIL/CMakeLists.txt)
else()
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(SOIL DEFAULT_MSG SOIL_INCLUDE_DIRS SOIL_LIBRARIES)
endif()

mark_as_advanced(SOIL_INCLUDE_DIRS SOIL_LIBRARIES)
