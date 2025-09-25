#pragma once

#include <array>

#include "tetris/EngineConfig.hpp"
#include "tetris/Types.hpp"

namespace tetris {

class Board {
public:
    Board();

    void clear();
    bool canPlace(const std::array<Cell, 4>& cells) const;
    void lock(const std::array<Cell, 4>& cells, int colorId);
    int clearFullLines();

    int cell(int x, int y) const;
    const std::array<std::array<int, engine_cfg::fieldWidth>, engine_cfg::fieldHeight>& data() const;

private:
    std::array<std::array<int, engine_cfg::fieldWidth>, engine_cfg::fieldHeight> grid_{};
};

} // namespace tetris
