#include "../include/tetris/Renderer.hpp"

#include <algorithm>
#include <string>
#include <vector>

#include "../include/tetris/Colors.hpp"
#include "../include/tetris/Tetromino.hpp"

namespace tetris {

Renderer::Renderer(const config::Layout& layout)
    : layout_(layout),
      block_(sf::Vector2f(static_cast<float>(layout.blockSize - 2), static_cast<float>(layout.blockSize - 2))),
      boardBackground_(sf::Vector2f(static_cast<float>(layout.boardPixelWidth), static_cast<float>(layout.boardPixelHeight))),
      holdArea_(sf::Vector2f(static_cast<float>(layout.holdBoxSize), static_cast<float>(layout.holdBoxSize))),
      queueArea_(sf::Vector2f(static_cast<float>(layout.queueBoxWidth), static_cast<float>(layout.queueBoxHeight))) {
    block_.setFillColor(sf::Color::White);

    boardBackground_.setPosition(static_cast<float>(layout.offsetX), static_cast<float>(layout.offsetY));
    boardBackground_.setFillColor(sf::Color(30, 30, 30));

    holdArea_.setPosition(static_cast<float>(layout.holdBoxX), static_cast<float>(layout.holdBoxY));
    holdArea_.setFillColor(sf::Color(50, 50, 50));

    queueArea_.setPosition(static_cast<float>(layout.queueBoxX), static_cast<float>(layout.queueBoxY));
    queueArea_.setFillColor(sf::Color(50, 50, 50));
}

void Renderer::draw(sf::RenderWindow& window, const Game& game, const sf::Font& font) {
    window.clear(sf::Color::Black);
    window.draw(boardBackground_);

    drawBoard(window, game);
    drawGhost(window, game);
    drawActive(window, game);
    drawHold(window, game, font);
    drawQueue(window, game, font);
    drawScore(window, game, font);

    window.display();
}

void Renderer::drawBoard(sf::RenderWindow& window, const Game& game) {
    sf::Vertex line[2];
    for (int col = 1; col < config::fieldWidth; ++col) {
        float x = static_cast<float>(layout_.offsetX + col * layout_.blockSize);
        line[0] = sf::Vertex({x, static_cast<float>(layout_.offsetY)}, sf::Color(50, 50, 50));
        line[1] = sf::Vertex({x, static_cast<float>(layout_.offsetY + layout_.boardPixelHeight)}, sf::Color(50, 50, 50));
        window.draw(line, 2, sf::Lines);
    }

    for (int row = 1; row < config::fieldHeight; ++row) {
        float y = static_cast<float>(layout_.offsetY + row * layout_.blockSize);
        line[0] = sf::Vertex({static_cast<float>(layout_.offsetX), y}, sf::Color(50, 50, 50));
        line[1] = sf::Vertex({static_cast<float>(layout_.offsetX + layout_.boardPixelWidth), y}, sf::Color(50, 50, 50));
        window.draw(line, 2, sf::Lines);
    }

    const auto& grid = game.board().data();
    const auto& palette = colors::palette();

    for (int y = 0; y < config::fieldHeight; ++y) {
        for (int x = 0; x < config::fieldWidth; ++x) {
            int value = grid[y][x];
            if (value == 0) {
                continue;
            }
            block_.setFillColor(palette[value]);
            block_.setPosition(
                static_cast<float>(layout_.offsetX + x * layout_.blockSize + 1),
                static_cast<float>(layout_.offsetY + y * layout_.blockSize + 1));
            window.draw(block_);
        }
    }
}

void Renderer::drawGhost(sf::RenderWindow& window, const Game& game) {
    if (!game.hasActivePiece()) {
        return;
    }

    const auto cells = game.ghostCells();
    const int colorId = game.activePieceId() + 1;
    block_.setFillColor(colors::ghost(colorId));

    for (const auto& cell : cells) {
        block_.setPosition(
            static_cast<float>(layout_.offsetX + cell.x * layout_.blockSize + 1),
            static_cast<float>(layout_.offsetY + cell.y * layout_.blockSize + 1));
        window.draw(block_);
    }
}

void Renderer::drawActive(sf::RenderWindow& window, const Game& game) {
    if (!game.hasActivePiece()) {
        return;
    }

    const auto cells = game.activeCells();
    const int colorId = game.activePieceId() + 1;
    const auto& palette = colors::palette();
    block_.setFillColor(palette[colorId]);

    for (const auto& cell : cells) {
        block_.setPosition(
            static_cast<float>(layout_.offsetX + cell.x * layout_.blockSize + 1),
            static_cast<float>(layout_.offsetY + cell.y * layout_.blockSize + 1));
        window.draw(block_);
    }
}

void Renderer::drawHold(sf::RenderWindow& window, const Game& game, const sf::Font& font) {
    window.draw(holdArea_);

    if (game.hasHoldPiece()) {
        drawPreviewPiece(
            window,
            game.holdPiece(),
            holdArea_.getPosition().x,
            holdArea_.getPosition().y,
            holdArea_.getSize().x,
            holdArea_.getSize().y);
    }

    sf::Text label;
    label.setFont(font);
    label.setString("HOLD");
    label.setCharacterSize(static_cast<unsigned int>(layout_.blockSize));
    label.setFillColor(sf::Color::White);

    const auto bounds = label.getLocalBounds();
    const float x = holdArea_.getPosition().x + holdArea_.getSize().x / 2.0f - bounds.width / 2.0f;
    const float y = holdArea_.getPosition().y + holdArea_.getSize().y + 10.0f;
    label.setPosition(x, y);
    window.draw(label);
}

void Renderer::drawQueue(sf::RenderWindow& window, const Game& game, const sf::Font& font) {
    window.draw(queueArea_);

    const auto preview = game.queuePreview(4);
    const float pieceHeight = static_cast<float>(layout_.blockSize * 3);

    for (std::size_t index = 0; index < preview.size(); ++index) {
        drawPreviewPiece(
            window,
            preview[index],
            queueArea_.getPosition().x,
            queueArea_.getPosition().y + static_cast<float>(index) * pieceHeight,
            queueArea_.getSize().x,
            pieceHeight);
    }

    sf::Text label;
    label.setFont(font);
    label.setString("Proximas Pecas");
    label.setCharacterSize(static_cast<unsigned int>(layout_.blockSize));
    label.setFillColor(sf::Color::White);

    const auto bounds = label.getLocalBounds();
    const float x = queueArea_.getPosition().x + queueArea_.getSize().x / 2.0f - bounds.width / 2.0f;
    const float y = queueArea_.getPosition().y + queueArea_.getSize().y + 10.0f;
    label.setPosition(x, y);
    window.draw(label);
}

void Renderer::drawScore(sf::RenderWindow& window, const Game& game, const sf::Font& font) {
    sf::Text label;
    label.setFont(font);
    label.setString("Score: " + std::to_string(game.score()));
    label.setCharacterSize(static_cast<unsigned int>(layout_.blockSize * 2));
    label.setFillColor(sf::Color::White);

    const auto bounds = label.getLocalBounds();
    label.setOrigin(bounds.left, bounds.top + bounds.height);
    label.setPosition(10.0f, static_cast<float>(layout_.desktop.height) - 10.0f);
    window.draw(label);
}

void Renderer::drawPreviewPiece(sf::RenderWindow& window, int pieceId, float x, float y, float width, float height) {
    const auto cells = TetrominoSet::instance().cells(pieceId, 0, Cell{0, 0});

    int minX = 4;
    int minY = 4;
    int maxX = -1;
    int maxY = -1;
    for (const auto& cell : cells) {
        minX = std::min(minX, cell.x);
        minY = std::min(minY, cell.y);
        maxX = std::max(maxX, cell.x);
        maxY = std::max(maxY, cell.y);
    }

    const int pieceWidth = maxX - minX + 1;
    const int pieceHeight = maxY - minY + 1;

    const float offsetX = x + (width - static_cast<float>(pieceWidth * layout_.blockSize)) / 2.0f;
    const float offsetY = y + (height - static_cast<float>(pieceHeight * layout_.blockSize)) / 2.0f;

    const auto& palette = colors::palette();
    block_.setFillColor(palette[pieceId + 1]);

    for (const auto& cell : cells) {
        const float px = offsetX + static_cast<float>(cell.x - minX) * layout_.blockSize + 1.0f;
        const float py = offsetY + static_cast<float>(cell.y - minY) * layout_.blockSize + 1.0f;
        block_.setPosition(px, py);
        window.draw(block_);
    }
}

} // namespace tetris
