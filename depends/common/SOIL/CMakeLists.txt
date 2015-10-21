project(SOIL)

cmake_minimum_required(VERSION 2.8)

include(ExternalProject)
ExternalProject_Add(SOIL
                    SOURCE_DIR ${PROJECT_SOURCE_DIR}
                    PREFIX SOIL
                    CONFIGURE_COMMAND ""
                    BUILD_COMMAND cd <SOURCE_DIR>/src && make -f "../projects/makefile/alternate Makefile.txt"
                    INSTALL_COMMAND ""
                    BUILD_IN_SOURCE 1
                    )

install(FILES ${PROJECT_SOURCE_DIR}/src/SOIL.h DESTINATION include/SOIL)
install(FILES ${PROJECT_SOURCE_DIR}/src/libSOIL.a DESTINATION lib)
