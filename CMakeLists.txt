cmake_minimum_required(VERSION "3.19")
add_subdirectory(vendors/glm)
add_subdirectory(vendors/glfw-3.4)
project("BlehEngine")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") # https://www.youtube.com/watch?v=IBgfeZME2Vw säger att det är bra
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}) # Gör så att .exe filen hamnar högst upp i mappen
file(GLOB_RECURSE SRC_FILES # lägger till alla .cpp filer, dock så tror jag att GLOB_RECURSE är dåligt dock använder videon det som är länkad åvan
    src/*.cpp
    src/glad.c
    lib/stb.cpp
)
add_executable("BlehEngine" ${SRC_FILES})
target_compile_definitions("BlehEngine" PUBLIC ResourcePath="${CMAKE_CURRENT_SOURCE_DIR}/src/engineResources/") # gör så att programmet kan hitta resources mappen genom att använda ResourcePath i koden

#target_compile_definitions("BlehEngine" PUBLIC ResourcePath="./src/res/") tror det ska vara såhär ifall jag ska skicka koden till någon annan
target_include_directories("BlehEngine" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendors")
target_include_directories("BlehEngine" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib")
target_include_directories("BlehEngine" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories("BlehEngine" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendors/glfw-3.4/include")
target_link_libraries("BlehEngine" PRIVATE glm)
target_link_libraries("BlehEngine" PRIVATE glfw)