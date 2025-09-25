cmake_minimum_required(VERSION 3.20)

project(tetris_ai_suite LANGUAGES CXX)

# Padrões de compilação
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Opções de build
option(BUILD_GUI "Build SFML GUI app" ON)
option(BUILD_CLI "Build headless CLI app" ON)

# Subprojetos
add_subdirectory(engine)
if(BUILD_GUI)
  add_subdirectory(ui)
endif()

# Executáveis
if(BUILD_CLI)
  add_executable(tetris_cli apps/tetris_cli.cpp)
  target_link_libraries(tetris_cli PRIVATE tetris_engine)
  target_compile_features(tetris_cli PRIVATE cxx_std_20)
endif()

if(BUILD_GUI)
  add_executable(tetris_gui apps/tetris_gui.cpp)
  target_link_libraries(tetris_gui PRIVATE tetris_ui)
  target_compile_features(tetris_gui PRIVATE cxx_std_20)
endif()
