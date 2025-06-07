#include "Tetromino.hpp"

Tetromino::Tetromino(TetrominoType t) : type(t), color(sf::Color::White) {
    switch (t) {
        case TetrominoType::I:
            blocks = {{0,1}, {1,1}, {2,1}, {3,1}};
            color = sf::Color::Cyan;
            break;
        case TetrominoType::Z:
            blocks = {{0,0}, {1,0}, {1,1}, {2,1}};
            color = sf::Color::Red;
            break;
        case TetrominoType::S:
            blocks = {{0,1}, {1,1}, {1,0}, {2,0}};
            color = sf::Color::Green;
            break;
        case TetrominoType::T:
            blocks = {{0,1}, {1,0}, {1,1}, {2,1}};
            color = sf::Color::Yellow;
            break;
        case TetrominoType::L:
            blocks = {{0,0}, {0,1}, {1,1}, {2,1}};
            color = sf::Color(255,165,0); // laranja
            break;
        case TetrominoType::J:
            blocks = {{2,0}, {0,1}, {1,1}, {2,1}};
            color = sf::Color(128, 0, 128); // roxo
            break;
        case TetrominoType::O:
            blocks = {{1,0}, {2,0}, {1,1}, {2,1}};
            color = sf::Color::Blue;
            break;
    }
}

void Tetromino::tryRotate(const GameField& field) {
    if (type == TetrominoType::O) return; // não rotaciona
    
    // Pivô é o segundo bloco
    Point pivot = blocks[1];

    // Calcula os novos blocos rotacionados
    std::vector<Point> rotatedBlocks;
    for (const auto& block : blocks) {
        int x_rel = block.x - pivot.x;
        int y_rel = block.y - pivot.y;

        int x_rot = y_rel;
        int y_rot = -x_rel;

        rotatedBlocks.push_back({pivot.x + x_rot, pivot.y + y_rot});
    }

    // Verifica se a posição é válida
    if (field.isValidPosition(*this, rotatedBlocks)) {
        // Se sim, atualiza os blocos do tetromino para a posição rotacionada
        blocks = rotatedBlocks;
    }
    // Caso contrário, não faz nada (rotação cancelada)
}

void Tetromino::resetPosition(int offsetX) {
    for (auto& block : blocks) {
        block.x += offsetX;
    }
}

std::vector<Point> Tetromino::getBlocks() const{
    return blocks;
}

int Tetromino::getColorID() const{
    switch(type){
        case TetrominoType::I: return 1;
        case TetrominoType::O: return 2;
        case TetrominoType::T: return 3;
        case TetrominoType::S: return 4;
        case TetrominoType::Z: return 5;
        case TetrominoType::J: return 6;
        case TetrominoType::L: return 7;
        default: return 0;
    }
}

void Tetromino::setBlocks(const std::vector<Point>& newBlocks) {
    blocks = newBlocks;
}

sf::Color getColorFromID(int id) {
    switch (id) {
        case 1: return sf::Color::Cyan;
        case 2: return sf::Color::Blue;
        case 3: return sf::Color::Yellow;
        case 4: return sf::Color::Green;
        case 5: return sf::Color::Red;
        case 6: return sf::Color(128, 0, 128); // Roxo
        case 7: return sf::Color(255,165,0);   // Laranja
        default: return sf::Color::White;
    }
}