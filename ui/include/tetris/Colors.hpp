#pragma once

#include <array>

#include <SFML/Graphics/Color.hpp>

namespace tetris::colors {

const std::array<sf::Color, 8>& palette();
sf::Color ghost(int id);

} // namespace tetris::colors
