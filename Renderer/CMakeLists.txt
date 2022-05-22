cmake_minimum_required(VERSION 3.16.2 FATAL_ERROR)

project(Renderer LANGUAGES CXX)
set(TargetName Renderer)

# 예제에서 사용하는 애플 프레임워크
find_library(Metal_lib Metal)
find_library(CoreGraphics_lib CoreGraphics)
find_library(MetalKit_lib MetalKit)
set(FRAMEWORK ${Metal_lib} ${CoreGraphics_lib} ${MetalKit_lib})

add_library(${TargetName} STATIC)
target_sources(${TargetName} PRIVATE src/Renderer.cpp)

set_target_properties(${TargetName} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories( ${TargetName} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/library/metal-cpp-extensions
    ${CMAKE_SOURCE_DIR}/library/metal-cpp
)

target_link_libraries(${TargetName} PUBLIC ${FRAMEWORK} imgui)