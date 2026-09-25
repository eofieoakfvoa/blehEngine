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
