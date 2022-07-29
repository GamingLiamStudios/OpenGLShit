include(FetchContent)

# Include zlib-ng
# Might as well keep it here just in case
set(ZLIB_ENABLE_TESTS OFF)
set(WITH_NATIVE_INSTRUCTIONS ON)

FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/zlib-ng/zlib-ng
    GIT_TAG 2.0.6
)

FetchContent_MakeAvailable(zlib)

# OpenGL
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3)

if(NOT(${glfw3_FOUND} AND ${glfw3_VERSION_MAJOR} EQUAL 3))
    message(FATAL_ERROR "glfw3 not found")
endif()

if(NOT ${glfw3_VERSION_MINOR} EQUAL 3)
    if(${glfw3_VERSION_MINOR} LESS 3)
        message(FATAL_ERROR "glfw3 version 3.3 or higher is required")
    else()
        message(WARNING "glfw3 version 3.3 is recommended, as newer versions may not work.")
    endif()
endif()
