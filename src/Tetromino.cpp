#include "../include/tetris/Tetromino.hpp"

#include <stdexcept>

namespace tetris {

namespace {

std::array<Cell, 4> maskToCells(std::uint16_t mask, const Cell& origin) {
    std::array<Cell, 4> cells{};
    int index = 0;
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (mask & (1u << (y * 4 + x))) {
                if (index >= 4) {
                    throw std::logic_error("Invalid tetromino mask");
                }
                cells[index++] = Cell{origin.x + x, origin.y + y};
            }
        }
    }
    if (index != 4) {
        throw std::logic_error("Tetromino mask must contain exactly 4 cells");
    }
    return cells;
}

} // namespace

TetrominoSet::TetrominoSet() {
    masks_ = {{
        {0x2222, 0x00F0, 0x2222, 0x00F0}, // I
        {0x2310, 0x3600, 0x2310, 0x0360}, // Z
        {0x1320, 0x0630, 0x2640, 0x6300}, // S
        {0x2320, 0x0720, 0x2620, 0x2700}, // T
        {0x2230, 0x0074, 0x0622, 0x02E0}, // L
        {0x3220, 0x0710, 0x2260, 0x4700}, // J
        {0x0660, 0x0660, 0x0660, 0x0660}  // O
    }};
}

const TetrominoSet& TetrominoSet::instance() {
    static const TetrominoSet set;
    return set;
}

std::array<Cell, 4> TetrominoSet::cells(int id, int rotation, const Cell& origin) const {
    const int normalizedId = id % static_cast<int>(masks_.size());
    const int normalizedRotation = rotation % 4;
    return maskToCells(masks_[normalizedId][normalizedRotation], origin);
}

bool TetrominoSet::occupied(int id, int rotation, int x, int y) const {
    if (x < 0 || x >= 4 || y < 0 || y >= 4) {
        return false;
    }
    const int normalizedId = id % static_cast<int>(masks_.size());
    const int normalizedRotation = rotation % 4;
    std::uint16_t mask = masks_[normalizedId][normalizedRotation];
    return (mask & (1u << (y * 4 + x))) != 0;
}

} // namespace tetris
