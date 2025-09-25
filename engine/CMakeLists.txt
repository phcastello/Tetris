# Biblioteca do motor (somente lógica do jogo)
add_library(tetris_engine STATIC
  src/Bag.cpp
  src/Board.cpp
  src/Game.cpp
  src/Tetromino.cpp
)

# Headers públicos do motor
target_include_directories(tetris_engine
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Warnings úteis
if(MSVC)
  target_compile_options(tetris_engine PRIVATE /W4 /permissive-)
else()
  target_compile_options(tetris_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_compile_features(tetris_engine PUBLIC cxx_std_20)
