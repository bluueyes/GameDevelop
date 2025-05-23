add_executable(SDLShooterExample example.cpp)

target_include_directories(SDLShooterExample PRIVATE
    ${SDL2_INCLUDE_DIR}
)

target_link_libraries(SDLShooterExample
    ${SDL2_LIBS}
)

# 自动复制dll和资源
add_custom_command(TARGET SDLShooterExample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_LIB_DIR}/lib/x64/SDL2.dll"
        "${SDL2_LIB_DIR}/lib/x64/SDL2_image.dll"
        "${SDL2_LIB_DIR}/lib/x64/SDL2_ttf.dll"
        "${SDL2_LIB_DIR}/lib/x64/SDL2_mixer.dll"
        $<TARGET_FILE_DIR:SDLShooterExample>
)