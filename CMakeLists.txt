cmake_minimum_required(VERSION 3.10)
project(SDLShooter VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#设置编译选项
if(MSVC)
    add_compile_options(/W4)  # MSVC 编译器的警告级别
else()
    add_compile_options(-Wall -Wextra -Wpedantic)  # GCC/Clang 编译器的警告选项
endif()

# 设置 CMake 的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})


# 设置 SDL2 的路径（相对路径）
set(SDL2_LIB_DIR "${CMAKE_SOURCE_DIR}/Library/SDL2")  # CMAKE_SOURCE_DIR 是工程根目录
# 手动指定头文件和库路径
set(SDL2_INCLUDE_DIR "${SDL2_LIB_DIR}/include")
set(SDL2_LIBS
    "${SDL2_LIB_DIR}/lib/x64/SDL2.lib"
    "${SDL2_LIB_DIR}/lib/x64/SDL2main.lib"
    "${SDL2_LIB_DIR}/lib/x64/SDL2_image.lib"
    "${SDL2_LIB_DIR}/lib/x64/SDL2_ttf.lib"
    "${SDL2_LIB_DIR}/lib/x64/SDL2_mixer.lib"
    )

include_directories(${SDL2_INCLUDE_DIR})

add_executable(${TARGET} src/main.cpp
                         src/Game.cpp
                         src/SceneMain.cpp
                         
)

target_link_libraries(${TARGET} ${SDL2_LIBS})

# 添加dll到bin目录
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_LIB_DIR}/lib/x64/SDL2.dll"
        "${SDL2_LIB_DIR}/lib/x64/SDL2_image.dll"
        "${SDL2_LIB_DIR}/lib/x64/SDL2_ttf.dll"
        "${SDL2_LIB_DIR}/lib/x64/SDL2_mixer.dll"
        $<TARGET_FILE_DIR:${TARGET}>
)

# 启用示例模块（可选构建）
option(BUILD_EXAMPLES "Build example programs" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()