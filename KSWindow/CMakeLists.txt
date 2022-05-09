cmake_minimum_required(VERSION 3.16.2 FATAL_ERROR)

project(KSWindow LANGUAGES CXX)
set(TargetName KSWindow)

# 예제에서 사용하는 애플 프레임워크
# Cocoa :  Apple's native object-oriented application programming interface (API) for its desktop operating system macOS.
# Foundation : Access essential data types, collections, and operating-system services to define the base layer of functionality for your app.
find_library(Cocoa_lib Cocoa)
find_library(Foundation_lib Foundation)
set(FRAMEWORK ${Cocoa_lib} ${Foundation_lib})

add_library(${TargetName} STATIC)
target_sources(${TargetName} PRIVATE src/KSWindow.cpp)

set_target_properties(${TargetName} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories( ${TargetName} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${TargetName} PUBLIC Renderer ${FRAMEWORK})