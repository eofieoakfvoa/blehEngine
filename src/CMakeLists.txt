
add_library(blehEngine STATIC
    blehEngine.cpp
    Camera.cpp

    renderer/Buffers.cpp
    renderer/Renderer.cpp
    renderer/Shader.cpp
    renderer/Texture.cpp
    renderer/Triangle.cpp
    renderer/VertexArrayObject.cpp

    Services/InputService.cpp
    Services/Window.cpp
    
    glad.c
    stb.cpp
)

target_include_directories(blehEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/vendors
        ${CMAKE_SOURCE_DIR}/lib
)
add_library(glfw SHARED IMPORTED)

set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/glfw3.dll
    IMPORTED_IMPLIB
        ${CMAKE_SOURCE_DIR}/lib/libglfw3dll.a
)

target_include_directories(glfw INTERFACE
        ${CMAKE_SOURCE_DIR}/vendors/GLFW
)

target_link_libraries(blehEngine PUBLIC
        glfw
)