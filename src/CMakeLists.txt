add_executable(main main.cpp)

# 源文件收集（更安全的文件收集方式）
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/*.c"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/external/imgui/*.cpp"  # 将ImGUI加入到项目中
)
target_sources(main PRIVATE ${SRC_FILES})

# 包含目录（使用现代 target 作用域方式）
target_include_directories(main PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/external
        ${PROJECT_SOURCE_DIR}/external/glm
        ${PROJECT_SOURCE_DIR}/external/GL
)

add_subdirectory(Arch)

target_link_libraries(main PRIVATE Arch)
