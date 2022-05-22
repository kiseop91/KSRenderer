cmake_minimum_required(VERSION 3.16.2 FATAL_ERROR)

project(imgui LANGUAGES CXX)
set(TargetName imgui)

# 예제에서 사용하는 애플 프레임워크
# Cocoa :  Apple's native object-oriented application programming interface (API) for its desktop operating system macOS.
# Foundation : Access essential data types, collections, and operating-system services to define the base layer of functionality for your app.


# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++")

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/library/GLFW/lib/cmake/glfw3")
find_package(glfw3 CONFIG REQUIRED)
find_library(QuartzCore_lib QuartzCore)

set(FRAMEWORK ${QuartzCore_lib})

add_library(${TargetName} STATIC)
target_sources(${TargetName} PRIVATE 
imgui_demo.cpp
imgui_draw.cpp
imgui_impl_glfw.cpp 
imgui_impl_metal.mm
imgui_tables.cpp 
imgui_widgets.cpp 
imgui.cpp 
)

set_target_properties(${TargetName} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories( ${TargetName} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/library/metal-cpp-extensions
    ${CMAKE_SOURCE_DIR}/library/metal-cpp
)

target_link_libraries(${TargetName} PUBLIC glfw ${FRAMEWORK})