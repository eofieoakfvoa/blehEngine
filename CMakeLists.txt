cmake_minimum_required(VERSION 3.19)
project(BlehEngine LANGUAGES C CXX)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Release flags: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "Debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")



set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}) 


add_subdirectory(vendors/glm)
add_subdirectory(vendors/glfw-3.4)

add_subdirectory(src)
add_subdirectory(gameProject)