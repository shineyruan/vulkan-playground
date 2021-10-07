cmake_minimum_required(VERSION 3.15)
project(vulkan_tutorial)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/include/spdlog-1.9.2)

find_package(Vulkan REQUIRED)

if (UNIX)
  find_package(glfw3 REQUIRED)
  set(LIBRARIES glfw ${Vulkan_LIBRARIES})
else(UNIX)
  set(EXTERNAL "external")

  set(GLFW_ROOT_DIR ${EXTERNAL})
  set(GLFW_USE_STATIC_LIBS ON)
  find_package(GLFW REQUIRED)

  set(LIBRARIES ${GLFW_LIBRARY} ${Vulkan_LIBRARIES})
endif(UNIX)

set(glm_DIR external/include/glm-0.9.9.8/cmake/glm)
find_package(glm REQUIRED)

include_directories(
  ${GLM_INCLUDE_DIRS} 
  ${GLFW_INCLUDE_DIRS} 
  ${VULKAN_INCLUDE_DIRS} 
)

add_executable(hello_vulkan main.cpp)
target_link_libraries(hello_vulkan 
  ${LIBRARIES}
  spdlog::spdlog_header_only
)

add_executable(triangle triangle.cpp)
target_link_libraries(triangle 
  ${LIBRARIES}
  spdlog::spdlog_header_only
)
