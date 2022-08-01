cmake_minimum_required(VERSION 3.11) # so CMake doesn't complain about OGL versions
project(main-executable C)

if(NOT MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/.cmake)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/OGLShit)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/OGLShit)

# option(BUILD_SHARED_LIBS "" off)
include(fetch_libraries)

set(SOURCE_FILES

    # https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D4.6&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&loader=on
    extern/glad/glad.c

    source/main.c
    source/shaders/shaders.c
)

add_executable(main-executable ${SOURCE_FILES})

target_compile_features(main-executable PUBLIC c_std_99)
set_target_properties(main-executable PROPERTIES OUTPUT_NAME "OGLShit")

target_include_directories(main-executable PUBLIC "extern")
target_include_directories(main-executable PUBLIC "source") # to allow paths relative to project root

target_link_libraries(main-executable PRIVATE m zlib OpenGL::GL glfw)

# Generate static includes for shaders
file(GLOB SHADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/shaders/*.glsl)

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME_WE)
    set(CSHADER_NAME "generated/${SHADER_NAME}.c")
    list(APPEND SHADER_EXPORTS ${CSHADER_NAME})

    add_custom_command(OUTPUT ${CSHADER_NAME}
        COMMAND ${CMAKE_COMMAND} -DSHADER_FILE:STRING=${SHADER_FILE} -DCSHADER_NAME:STRING=${CSHADER_NAME} -DSHADER_NAME:STRING=${SHADER_NAME}
        -P ${CMAKE_MODULE_PATH}/generate_shaders.cmake
        DEPENDS ${SHADER_FILE}
        DEPENDS ${CMAKE_MODULE_PATH}/generate_shaders.cmake
        COMMENT "Generating shader ${SHADER_FILE}"
    )
endforeach()

set_source_files_properties(${SHADER_EXPORTS} PROPERTIES GENERATED TRUE)
target_sources(${PROJECT_NAME} PRIVATE ${SHADER_EXPORTS})