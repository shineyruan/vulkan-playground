#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "print_glm.hpp"
#include "spdlog/spdlog.h"

int main() {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow* window =
      glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

  spdlog::info(
      "vkEnumerateInstanceExtensionProperties: {} extensions supported",
      extensionCount);

  glm::mat4 matrix;
  glm::vec4 vec;
  auto test = matrix * vec;
  std::cout << "test matrix: " << test << "\n";

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();

  return 0;
}