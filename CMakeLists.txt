cmake_minimum_required(VERSION 3.0)
project(BtatesCraft)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_RPATH "./lib")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/BtatesCraft/)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include(FindPkgConfig)
pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(glm REQUIRED glm)

find_library(IRRKLANG_LIBRARY
  IrrKlang
  PATH BtatesCraft/lib)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/BtatesCraft/src/*.cpp)

set(INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}/BtatesCraft/src/
  ${CMAKE_CURRENT_SOURCE_DIR}/BtatesCraft/src/vendor/
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIR}
  ${GLFW_INCLUDE_DIR}
  ${GLM_INCLUDE_DIR})
set(LIBRARIES
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${GLFW_STATIC_LIBRARIES}
  ${IRRKLANG_LIBRARY})

add_executable(BtatesCraft ${SOURCES})
target_include_directories(BtatesCraft PUBLIC ${INCLUDES})
target_link_libraries(BtatesCraft ${LIBRARIES})
