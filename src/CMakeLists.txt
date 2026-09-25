



add_library(blehEngine STATIC
    blehEngine.cpp
    Camera.cpp
    errorReporting.cpp

    renderer/Buffers.cpp
    renderer/Renderer.cpp
    renderer/Shader.cpp
    renderer/Texture.cpp
    renderer/VertexArrayObject.cpp

    Services/InputService.cpp
    Services/Window.cpp
    Services/blehServices.cpp
    Services/blehGame.cpp

    "Services/Assets/Model.cpp"
    "Services/Assets/AssetManager.cpp"

    Platform/glad.c
    stb.cpp
  "Random.h" "Services/Assets/handle.h" "Debug.h" "Services/WindowManager.cpp")


target_compile_definitions("blehEngine" PUBLIC ResourcePath="${CMAKE_CURRENT_SOURCE_DIR}/engineResources/")
# #target_compile_definitions("BlehEngine" PUBLIC ResourcePath="./src/res/") tror det ska vara såhär ifall jag ska skicka koden till någon annan


target_include_directories(blehEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/vendors
        ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(blehEngine PUBLIC
        glfw
        opengl32
        "-lstdc++exp"
)