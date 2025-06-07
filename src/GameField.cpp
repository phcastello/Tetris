#pragma once
#include <SFML/Graphics.hpp>
#include "include/GameField.hpp"

GameField::GameField(int width_, int height_) : width(width_), height(height_){
    field = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
}

bool GameField::isValidPosition(const Tetromino &t, const std::vector<Point> &positions, const Point& pos) const {
    for(const auto &p : positions){
        int x = p.x + pos.x;
        int y = p.y + pos.y;

        if(x < 0 || x >= width || y < 0 || y >= height) return false;
        if(field[y][x] != 0) return false;
    }
    return true;
}

void GameField::fixTetromino(const Tetromino &t){
    int colorID = t.getColorID();
    std::vector<Point> blocks = t.getBlocks();

    for(const auto &block : blocks){
        if(block.y >= 0 and block.y < height and block.x >= 0 and block.x < width){
            field[block.y][block.x] = colorID;
        }
    }
}

void GameField::clearLines(){
    for(int y = height - 1; y >= 0; y--){
        bool full = true;
        for(int x = 0; x < width; x++){
            if(field[x][y] == 0){
                full = false;
                break;
            }
        }

        if(full){
            for(int yy = y; yy > 0; yy--){
                field[yy] = field[yy - 1];
            }
            field[0] = std::vector<int>(width, 0);
            y++;
        }
    }
}

void GameField::draw(sf::RenderWindow &window, float blockSize){
    sf::RectangleShape block(sf::Vector2f(blockSize - 1, blockSize - 1));

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            if(field[y][x] != 0){
                block.setPosition(x * blockSize, y * blockSize);

                //definir a cor de acordo com o valor
                block.setFillColor(sf::Color::Green);

                window.draw(block);
            }
        }
    }
}

int GameField::getHardDropY(const Tetromino& t, const Point& position) const {
    int dropY = position.y;

    while (true) {
        std::vector<Point> movedBlocks = t.getBlocks();  // blocos relativos

        // Tentativa de deslocar para a próxima linha abaixo
        Point testPos = { position.x, dropY + 1 };

        if (isValidPosition(t, movedBlocks, testPos)) {
            dropY++;
        } else {
            break;
        }
    }

    return dropY;
}