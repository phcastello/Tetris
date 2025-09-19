#pragma once

#include <array>
#include <cstdint>

#include "Types.hpp"

namespace tetris {

class TetrominoSet {
public:
    static const TetrominoSet& instance();

    std::array<Cell, 4> cells(int id, int rotation, const Cell& origin) const;
    bool occupied(int id, int rotation, int x, int y) const;

private:
    TetrominoSet();

    std::array<std::array<std::uint16_t, 4>, 7> masks_{};
};

} // namespace tetris
