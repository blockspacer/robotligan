#include <iostream>
#include <entt.hpp>
#include <glob/graphics.h>
#include <NetAPI/networkTest.hpp>
#include <NetAPI/packet.hpp>
#include <NetAPI/socket/server.hpp>
#include <NetAPI/socket/tcpclient.hpp>
#include <chrono>
#include <thread>
#include "PrintPositionSystem.h"
#include "util/meminfo.h"
//#include <glad/glad.h>
#pragma comment(lib, "Ws2_32.lib")
int main(unsigned argc, char **argv) {
  std::cout << "Hello World!*!!!111\n";

  std::cout << "Test fr�n development\n";
  entt::registry registry;

  auto entity = registry.create();
  registry.assign<Position>(entity, 1.0f, 2.0f, 3.0f);
  registry.assign<Velocity>(entity, 3.0f, 2.0f, 1.0f);
  print(registry);

  std::cout << "Test fr�n development2 " << glob::GraphicsTest() << "\n";

  std::cout << "WSA is initialized? " << std::boolalpha
            << NetAPI::Initialization::WinsockInitialized() << std::endl;

  std::cout << "RAM usage: " << util::MemoryInfo::GetInstance().GetUsedRAM()
            << " MB\n";
  std::cout << "VRAM usage: " << util::MemoryInfo::GetInstance().GetUsedVRAM()
            << " MB\n";
  std::cin.ignore();
  return EXIT_SUCCESS;
}