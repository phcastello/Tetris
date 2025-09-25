#pragma once

#include <SFML/Graphics.hpp>

#include "tetris/Config.hpp"
#include "tetris/Game.hpp"

namespace tetris {

class Renderer {
public:
    explicit Renderer(const config::Layout& layout);

    void draw(sf::RenderWindow& window, const Game& game, const sf::Font& font);

private:
    void drawBoard(sf::RenderWindow& window, const Game& game);
    void drawGhost(sf::RenderWindow& window, const Game& game);
    void drawActive(sf::RenderWindow& window, const Game& game);
    void drawHold(sf::RenderWindow& window, const Game& game, const sf::Font& font);
    void drawQueue(sf::RenderWindow& window, const Game& game, const sf::Font& font);
    void drawScore(sf::RenderWindow& window, const Game& game, const sf::Font& font);
    void drawPreviewPiece(sf::RenderWindow& window, int pieceId, float x, float y, float width, float height);

    const config::Layout layout_;
    sf::RectangleShape block_;
    sf::RectangleShape boardBackground_;
    sf::RectangleShape holdArea_;
    sf::RectangleShape queueArea_;
};

} // namespace tetris
