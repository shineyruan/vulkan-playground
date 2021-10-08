#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <stdexcept>

#include "spdlog/spdlog.h"

class HelloTriangleApplication {
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  static constexpr int WINDOW_HEIGHT = 800;
  static constexpr int WINDOW_WIDTH  = 600;

  GLFWwindow* glfw_window_;
  VkInstance vk_instance_;

  void initWindow() {
    // init
    glfwInit();
    // tell GLFW not to create OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // disable GLFW window resize
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // create window
    glfw_window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan",
                                    nullptr, nullptr);
  }

  void initVulkan() { createInstance(); }

  void mainLoop() {
    while (!glfwWindowShouldClose(glfw_window_)) {
      glfwPollEvents();
    }
  }

  void cleanup() {
    vkDestroyInstance(vk_instance_, nullptr);
    if (glfw_window_) glfwDestroyWindow(glfw_window_);
    glfwTerminate();
  }

  void createInstance() {
    // 1. Init application
    VkApplicationInfo app_info{};
    app_info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName   = "Hello Triangle";
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName        = "No engine";
    app_info.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    app_info.apiVersion         = VK_API_VERSION_1_0;

    // 2. Init create info
    VkInstanceCreateInfo create_info{};
    create_info.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;

    // Vulkan is a platform agnostic API, which means that you need an extension
    // to interface with the window system.
    uint32_t glfw_extension_count = 0;
    const char** glfw_extensions =
        glfwGetRequiredInstanceExtensions(&glfw_extension_count);
    create_info.enabledExtensionCount   = 0;
    create_info.ppEnabledExtensionNames = glfw_extensions;
    // whether to enable global validation layers
    create_info.enabledLayerCount = 0;

    // 3. Enumerate supported extensions
    uint32_t supported_extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &supported_extension_count,
                                           nullptr);
    std::vector<VkExtensionProperties> supported_extensions(
        supported_extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &supported_extension_count,
                                           supported_extensions.data());
    spdlog::info("Vulkan supported extensions:");
    for (const auto& extension : supported_extensions) {
      spdlog::info("\t{}", extension.extensionName);
    }

    // 4. Create instance
    if (vkCreateInstance(&create_info, nullptr, &vk_instance_) != VK_SUCCESS) {
      throw std::runtime_error("failed to create VK instance!");
    }
  }
};

int main() {
  HelloTriangleApplication app;

  try {
    app.run();
  } catch (const std::exception& e) {
    spdlog::error(e.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
