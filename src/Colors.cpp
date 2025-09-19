#include "../include/tetris/Colors.hpp"

namespace tetris::colors {

const std::array<sf::Color, 8>& palette() {
    static const std::array<sf::Color, 8> colors = {
        sf::Color(0, 0, 0),       // vazio
        sf::Color(255, 0, 0),     // I
        sf::Color(0, 255, 0),     // Z
        sf::Color(0, 0, 255),     // S
        sf::Color(255, 255, 0),   // T
        sf::Color(255, 165, 0),   // L
        sf::Color(128, 0, 128),   // J
        sf::Color(0, 255, 255)    // O
    };
    return colors;
}

sf::Color ghost(int id) {
    sf::Color color = palette()[id];
    color.a = 100;
    return color;
}

} // namespace tetris::colors
