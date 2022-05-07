cmake_minimum_required(VERSION 3.16.2 FATAL_ERROR)

project(KSRenderer LANGUAGES CXX VERSION 1.0.0)

add_subdirectory(Renderer)
add_subdirectory(Application)
add_subdirectory(KSWindow)

add_dependencies(KSWindow Renderer)
add_dependencies(Application Renderer)
