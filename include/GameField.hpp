#pragma once
#include "utils.hpp"
#include "Tetromino.hpp"

class GameField{
private:
    int width, height;
    std::vector<std::vector<int>> field;
public:
    GameField(int width, int height);

    bool isValidPosition(const Tetromino &t, const std::vector<Point> &positions, const Point& pos) const;
    void fixTetromino(const Tetromino &t);
    void clearLines();
    void draw(sf::RenderWindow &window, float blockSize);
    int getHardDropY(const Tetromino& t, const Point& position) const;
};