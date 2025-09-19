#pragma once

#include <array>

#include "Config.hpp"
#include "Types.hpp"

namespace tetris {

class Board {
public:
    Board();

    void clear();
    bool canPlace(const std::array<Cell, 4>& cells) const;
    void lock(const std::array<Cell, 4>& cells, int colorId);
    int clearFullLines();

    int cell(int x, int y) const;
    const std::array<std::array<int, config::fieldWidth>, config::fieldHeight>& data() const;

private:
    std::array<std::array<int, config::fieldWidth>, config::fieldHeight> grid_{};
};

} // namespace tetris
