file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

add_library(Math STATIC ${SRC_FILES})

target_include_directories(Math PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)
