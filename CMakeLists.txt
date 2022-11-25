project(hotwheels_tf2_internal)

cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SRC
        "project/*.h" ,
        "project/*.hpp" ,
        "project/*.c" ,
        "project/*.cpp" ,
        "project/*.inl" ,
        "project/**/*.h" ,
        "project/**/*.hpp" ,
        "project/**/*.c" ,
        "project/**/*.cc" ,
        "project/**/*.cpp" ,
        "project/**/*.inl" ,
        )

add_library(${PROJECT_NAME} SHARED ${SRC})


find_library(D3DX9_LIB d3dx9.lib PATHS "$ENV{DXSDK_DIR}Lib/x86")
find_library(D3D9_LIB d3d9.lib PATHS "$ENV{DXSDK_DIR}Lib/x86")
# find_library(FREETYPE_LIB freetype.lib PATHS "${PROJECT_SOURCE_DIR}/project/dependencies/freetype")
# find_library(THEMIDA_LIB SecureEngineSDK64.lib PATHS "${PROJECT_SOURCE_DIR}/project/dependencies/themida/lib")

target_link_libraries(${PROJECT_NAME} "${D3DX9_LIB}" "${D3D9_LIB}")
# target_link_libraries(${PROJECT_NAME} "${FREETYPE_LIB}")
# target_link_libraries(${PROJECT_NAME} "${THEMIDA_LIB}")

# target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/project/dependencies/freetype")

# target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/project/dependencies/freetype/include")

link_directories("$ENV{DXSDK_DIR}Lib/x86")
include_directories("$ENV{DXSDK_DIR}Include")
include_directories("${PROJECT_SOURCE_DIR}/project/dependencies/")