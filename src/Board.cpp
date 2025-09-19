#include "../include/tetris/Board.hpp"

namespace tetris {

Board::Board() {
    clear();
}

void Board::clear() {
    for (auto& row : grid_) {
        row.fill(0);
    }
}

bool Board::canPlace(const std::array<Cell, 4>& cells) const {
    for (const auto& cell : cells) {
        if (cell.x < 0 || cell.x >= config::fieldWidth) {
            return false;
        }
        if (cell.y < 0 || cell.y >= config::fieldHeight) {
            return false;
        }
        if (grid_[cell.y][cell.x] != 0) {
            return false;
        }
    }
    return true;
}

void Board::lock(const std::array<Cell, 4>& cells, int colorId) {
    for (const auto& cell : cells) {
        if (cell.y >= 0 && cell.y < config::fieldHeight &&
            cell.x >= 0 && cell.x < config::fieldWidth) {
            grid_[cell.y][cell.x] = colorId;
        }
    }
}

int Board::clearFullLines() {
    int targetRow = config::fieldHeight - 1;
    int cleared = 0;

    for (int row = config::fieldHeight - 1; row >= 0; --row) {
        int filled = 0;
        for (int col = 0; col < config::fieldWidth; ++col) {
            if (grid_[row][col] != 0) {
                ++filled;
            }
            grid_[targetRow][col] = grid_[row][col];
        }

        if (filled == config::fieldWidth) {
            ++cleared;
        } else {
            --targetRow;
        }
    }

    for (int row = targetRow; row >= 0; --row) {
        for (int col = 0; col < config::fieldWidth; ++col) {
            grid_[row][col] = 0;
        }
    }

    return cleared;
}

int Board::cell(int x, int y) const {
    if (x < 0 || x >= config::fieldWidth || y < 0 || y >= config::fieldHeight) {
        return 0;
    }
    return grid_[y][x];
}

const std::array<std::array<int, config::fieldWidth>, config::fieldHeight>& Board::data() const {
    return grid_;
}

} // namespace tetris
