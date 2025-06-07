#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include "utils.hpp"
#include "GameField.hpp"

class TetrisGame {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Music TetrisGameMusic;
    sf::Font HennyPenny;

    float timer = 0.0f;
    float time = 0.0f;
    float moveTimer = 0.0f;

    float normalDelay = 0.3f;
    float fastDelay = 0.5f;
    float delay = normalDelay;
    float moveDelay = 0.1f;

    int dx = 0;
    bool rotate = false;

    Point currentPosition;

    Queue<int> nextPieces;
    bool holdUsed = false;
    const int queueSize = 4;
    std::optional<Tetromino> holdPiece;
    Tetromino currentTetromino;
    int dx = 0;

    GameField field = GameField(10, 20);

    void processInput(const sf::Event& event);
    void update();
    void render();

public:
    TetrisGame();
    void run();
};
