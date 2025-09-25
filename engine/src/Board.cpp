#include "tetris/Board.hpp"

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
        if (cell.x < 0 || cell.x >= engine_cfg::fieldWidth) {
            return false;
        }
        if (cell.y < 0 || cell.y >= engine_cfg::fieldHeight) {
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
        if (cell.y >= 0 && cell.y < engine_cfg::fieldHeight &&
            cell.x >= 0 && cell.x < engine_cfg::fieldWidth) {
            grid_[cell.y][cell.x] = colorId;
        }
    }
}

int Board::clearFullLines() {
    int targetRow = engine_cfg::fieldHeight - 1;
    int cleared = 0;

    for (int row = engine_cfg::fieldHeight - 1; row >= 0; --row) {
        int filled = 0;
        for (int col = 0; col < engine_cfg::fieldWidth; ++col) {
            if (grid_[row][col] != 0) {
                ++filled;
            }
            grid_[targetRow][col] = grid_[row][col];
        }

        if (filled == engine_cfg::fieldWidth) {
            ++cleared;
        } else {
            --targetRow;
        }
    }

    for (int row = targetRow; row >= 0; --row) {
        for (int col = 0; col < engine_cfg::fieldWidth; ++col) {
            grid_[row][col] = 0;
        }
    }

    return cleared;
}

int Board::cell(int x, int y) const {
    if (x < 0 || x >= engine_cfg::fieldWidth || y < 0 || y >= engine_cfg::fieldHeight) {
        return 0;
    }
    return grid_[y][x];
}

const std::array<std::array<int, engine_cfg::fieldWidth>, engine_cfg::fieldHeight>& Board::data() const {
    return grid_;
}

} // namespace tetris
