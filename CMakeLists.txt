cmake_minimum_required(VERSION 3.10)

project(indulc)

if(CMAKE_BUILD_TYPE STREQUAL "")
        # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
        # differentiation between debug and release builds.
        set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release." FORCE)
endif()

if(LINUX)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLINUX")
endif(LINUX)
if(WIN32)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWIN32")
endif(WIN32)
# set(CMAKE_C_STANDARD 11)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/${CMAKE_BUILD_TYPE})

include(FetchContent)
FetchContent_Declare(
        cJson
        GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
        GIT_TAG v1.7.19
)
FetchContent_Declare(
        Blueprint
        GIT_REPOSITORY https://github.com/RTrave/Factorio_Json_to_blueprint.git
        GIT_TAG cmake2
)
FetchContent_MakeAvailable(cJson Blueprint)

set(CJSON_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/cjson-src/)
set(BLUEPRINT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/blueprint-src/)

include_directories(
        ./
        ./hdr
        ./lib/hdr
        ${CJSON_DIRECTORY}
        ${BLUEPRINT_DIRECTORY}/include
        ${BLUEPRINT_DIRECTORY}/hdr
        ${BLUEPRINT_DIRECTORY}/lib/hdr
        ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/cjson-src/
        ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/blueprint-src/
)

file(
        GLOB_RECURSE
        lib_files
        CONFIGURE_DEPENDS
        lib/*.c
)

file(
        GLOB_RECURSE
        bin_files
        CONFIGURE_DEPENDS
        lib/*.c
        src/*.c
)

add_library(
        ${PROJECT_NAME}
        SHARED
        ${lib_files}

)
# include_directories(
#         # BEFORE
#         ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/cjson-src/
#         ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/blueprint-src/
# )


target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC
        blueprint
        cjson
        PUBLIC
        
        # base64
        # z
)

add_executable(
        ${PROJECT_NAME}_exe
        ${bin_files}
)

target_link_libraries(
        ${PROJECT_NAME}_exe
        PUBLIC
        ${PROJECT_NAME}
        cjson
        blueprint
        # base64
        # z
)
