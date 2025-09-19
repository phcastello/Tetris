#pragma once

#include <array>

namespace tetris {

struct Cell {
    int x = 0;
    int y = 0;
};

enum class GameState {
    Menu,
    Playing,
    GameOver,
    Exit
};

struct ActivePiece {
    int id = -1;
    int rotation = 0;
    Cell origin{0, 0};
};

struct Score {
    int value = 0;

    void reset() {
        value = 0;
    }

    void addLines(int lines) {
        switch (lines) {
            case 1: value += 100; break;
            case 2: value += 300; break;
            case 3: value += 500; break;
            case 4: value += 800; break;
            default: break;
        }
    }
};

} // namespace tetris
