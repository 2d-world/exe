cmake_minimum_required(VERSION 3.0)
project(TExe)

set(TEXE_VERSION 1.0)

include_directories(include)

add_executable(TExe src/main.c src/Library.c)

target_include_directories(TExe
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external_headers>
)

set_target_properties(TExe PROPERTIES OUTPUT_NAME "TExe")

set_target_properties(TExe PROPERTIES VERSION ${TEXE_VERSION})

install(TARGETS TExe)
