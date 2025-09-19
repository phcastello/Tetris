#pragma once

#include <SFML/Graphics.hpp>

#include "Config.hpp"

namespace tetris {

class Hud {
public:
    explicit Hud(const sf::Font& font);

    bool showMenu(sf::RenderWindow& window, const config::Layout& layout);
    bool showGameOver(sf::RenderWindow& window, const config::Layout& layout, int score);

private:
    const sf::Font& font_;
};

} // namespace tetris
