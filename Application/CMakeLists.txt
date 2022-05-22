cmake_minimum_required(VERSION 3.16.2 FATAL_ERROR)


project(Application LANGUAGES CXX)
set(TargetName Application)

add_executable(${TargetName} MACOSX_BUNDLE)
target_sources(${TargetName} PRIVATE main.cpp 
)

set_target_properties(${TargetName} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${TargetName} KSWindow imgui)