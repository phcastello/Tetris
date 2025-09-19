#pragma once

#include <SFML/Graphics.hpp>

namespace tetris::config {

constexpr int fieldWidth = 10;
constexpr int fieldHeight = 20;

constexpr float normalDropDelay = 0.3f;
constexpr float fastDropDelay = 0.05f;
constexpr float moveRepeatDelay = 0.1f;

constexpr const char* fontPath = "assets/HennyPenny.ttf";
constexpr const char* musicPath = "assets/TetrisGameMusic.ogg";

struct Layout {
    sf::VideoMode desktop{};
    int blockSize = 0;
    int offsetX = 0;
    int offsetY = 0;
    int boardPixelWidth = 0;
    int boardPixelHeight = 0;
    int holdBoxSize = 0;
    int holdBoxX = 0;
    int holdBoxY = 0;
    int queueBoxWidth = 0;
    int queueBoxHeight = 0;
    int queueBoxX = 0;
    int queueBoxY = 0;
};

Layout makeLayout(const sf::VideoMode& desktop);

} // namespace tetris::config
