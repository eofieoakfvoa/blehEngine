add_executable(coolgame
    GameManager.cpp
)

target_include_directories(coolgame
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(coolgame
    PRIVATE
        blehEngine
)