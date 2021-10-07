#include <vulkan/vulkan.h>

#include <cstdlib>
#include <stdexcept>

#include "spdlog/spdlog.h"

class HelloTriangleApplication {
public:
  void run() {
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  void initVulkan() {}

  void mainLoop() {}

  void cleanup() {}
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
