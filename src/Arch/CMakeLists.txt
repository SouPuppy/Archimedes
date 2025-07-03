add_library(Arch Engine.cpp)

# 源文件收集（更安全的文件收集方式）
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/external/imgui/*.cpp"  # 将ImGUI加入到项目中
)
target_sources(Arch PRIVATE ${SRC_FILES})

# 包含目录（使用现代 target 作用域方式）
target_include_directories(Arch PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/external
        ${PROJECT_SOURCE_DIR}/external/glm
        ${PROJECT_SOURCE_DIR}/external/GL
)

# 公共依赖项
find_package(Threads REQUIRED)
target_link_libraries(Arch PRIVATE Threads::Threads)

# 平台特定配置
if(UNIX AND NOT APPLE)
    # Linux 配置
    find_package(X11 REQUIRED)

    target_link_directories(Arch PRIVATE ${PROJECT_SOURCE_DIR}/libs/Unix)

    target_link_libraries(Arch PRIVATE
            glfw3
            GLEW
            GL
            dl
            X11
            ${X11_Xrandr_LIB}
            ${X11_Xinerama_LIB}
            ${X11_Xcursor_LIB}
    )

elseif(WIN32)
    # Windows 配置优化
    set(WIN_LIB_DIR ${PROJECT_SOURCE_DIR}/libs/WIN64)

    # 编译定义
    target_compile_definitions(Arch PRIVATE
            GLEW_STATIC  # 假设使用静态GLEW
    )

    # 库文件链接（显式指定扩展名）
    target_link_libraries(Arch PRIVATE
            ${WIN_LIB_DIR}/glew32.lib  # 静态库/导入库
            ${WIN_LIB_DIR}/glfw3dll.lib   # GLFW导入库
            opengl32
            gdi32
            user32
            shell32
    )

    # 自动复制运行时依赖项
    set(WIN_DLLS
            ${WIN_LIB_DIR}/glfw3.dll
            ${WIN_LIB_DIR}/glew32.dll
    )
    add_custom_command(TARGET Arch POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${WIN_DLLS}
            $<TARGET_FILE_DIR:Arch>
            COMMENT "Copying runtime DLLs"
    )
endif()

# 验证源文件存在（放在最后以确保所有源文件已收集）
if(NOT SRC_FILES)
    message(FATAL_ERROR "No source files found in src directory!")
endif()