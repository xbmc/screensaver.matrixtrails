find_path(SOIL_INCLUDE_DIRS SOIL.h PATH_SUFFIXES SOIL)

find_library(SOIL_LIBRARIES NAMES SOIL)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SOIL DEFAULT_MSG SOIL_INCLUDE_DIRS SOIL_LIBRARIES)

mark_as_advanced(SOIL_INCLUDE_DIRS SOIL_LIBRARIES)
