cmake_minimum_required(VERSION 3.10.0)
project(PlaneWar VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 摘自 raylib 的 cmake 示例项目中的代码
# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()

# 指定 raylib 文件目录
set(RAYLIB_INCLUDE_DIR ${CMAKE_BINARY_DIR}/_deps/raylib-src/src)

# 添加 raylib 头文件目录
include_directories(${RAYLIB_INCLUDE_DIR})

add_executable(
    PlaneWar
    src/main.cpp
    # test/player_display.cpp
    src/game.cpp
    src/window/window.cpp
    src/entity/entity.cpp
    src/entity/player.cpp
    src/entity/enemy.cpp
    src/entity_pool/entity_pool.cpp
    src/entity_pool/enemy_pool.cpp
)

# 链接 raylib 库
target_link_libraries(PlaneWar raylib)