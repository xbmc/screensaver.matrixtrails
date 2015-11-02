message("hoi ${SOIL_LIBRARIES}")

find_path(SOIL_INCLUDE_DIRS SOIL/SOIL.h)
find_library(SOIL_LIBRARIES NAMES SOIL)

message("hai ${SOIL_LIBRARIES}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SOIL DEFAULT_MSG SOIL_INCLUDE_DIRS SOIL_LIBRARIES)

mark_as_advanced(SOIL_INCLUDE_DIRS SOIL_LIBRARIES)
