cmake_minimum_required(VERSION 3.20)
project(MiniMetroAdvancedClone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL QUIET)
find_package(glfw3 QUIET)

if(OpenGL_FOUND AND glfw3_FOUND)
  add_executable(mini_metro
    src/main.cpp
    src/Game.cpp
    src/core/Core.cpp
    src/engine/Engine.cpp
    src/world/World.cpp
    src/metro/Metro.cpp
    src/passenger/Passenger.cpp
    src/systems/Systems.cpp
    src/ui/UI.cpp
    src/render/Render.cpp
    src/save/Save.cpp
  )
  target_include_directories(mini_metro PRIVATE src)
  target_link_libraries(mini_metro PRIVATE glfw OpenGL::GL)
else()
  message(WARNING "OpenGL/glfw3 not found in this environment. Project source is complete, but binary target is skipped.")
endif()
