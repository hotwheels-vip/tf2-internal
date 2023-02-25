project(hotwheels_tf2_internal)

cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_TOOLCHAIN_FILE "C:\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
SET(VCPKG_TARGET_TRIPLET "x86-windows-static-md")

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
find_library(THEMIDA_LIB SecureEngineSDK32.lib PATHS "${PROJECT_SOURCE_DIR}/project/dependencies/themida")

find_package(Freetype REQUIRED)
find_package(nameof REQUIRED)
find_package(minhook REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE "${D3DX9_LIB}" "${D3D9_LIB}" Freetype::Freetype "${THEMIDA_LIB}" nameof::nameof nlohmann_json::nlohmann_json minhook::minhook spdlog::spdlog spdlog::spdlog_header_only)

target_link_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/project/dependencies/freetype")
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/project/dependencies/freetype/include")

link_directories("$ENV{DXSDK_DIR}Lib/x86")
include_directories("$ENV{DXSDK_DIR}Include")
include_directories("${PROJECT_SOURCE_DIR}/project/dependencies/")