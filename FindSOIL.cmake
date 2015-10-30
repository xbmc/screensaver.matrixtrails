find_path(SOIL_INCLUDE_DIRS SOIL/SOIL.h)
find_library(SOIL_LIBRARY NAMES SOIL)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SOIL DEFAULT_MSG SOIL_INCLUDE_DIRS SOIL_LIBRARY)

mark_as_advanced(SOIL_INCLUDE_DIRS SOIL_LIBRARY)
