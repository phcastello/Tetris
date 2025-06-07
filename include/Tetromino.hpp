#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "GameField.hpp"

enum class TetrominoType { I, Z, S, T, L, J, O};

class Tetromino {
private:
    TetrominoType type;
    std::vector<Point> blocks;
    sf::Color color;

public:
    Tetromino(TetrominoType t);
    
    void tryRotate(const GameField&);
    void resetPosition(int offsetX);
    std::vector<Point> getBlocks() const;
    void setBlocks(const std::vector<Point>& newBlocks);
    int getColorID() const;
    
};
