add_executable(coolgame GameManager.cpp )

target_include_directories(coolgame
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(coolgame
    PRIVATE
        blehEngine
        "-lstdc++exp"
)
target_compile_definitions("coolgame" PUBLIC GameResources="${CMAKE_CURRENT_SOURCE_DIR}/GameResources/")
# #target_compile_definitions("BlehEngine" PUBLIC ResourcePath="./src/res/") tror det ska vara såhär ifall jag ska skicka koden till någon annan