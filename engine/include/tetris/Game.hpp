#pragma once

#include <array>
#include <queue>
#include <vector>

#include "tetris/Bag.hpp"
#include "tetris/Board.hpp"
#include "tetris/EngineConfig.hpp"
#include "tetris/Tetromino.hpp"
#include "tetris/Types.hpp"

namespace tetris {

class Game {
public:
    Game();

    void reset();
    void start();

    void update(float dt, bool softDrop);
    void moveLeft();
    void moveRight();
    void rotate();
    void hardDrop();
    void hold();

    GameState state() const;
    void setState(GameState state);

    int score() const;

    const Board& board() const;
    std::array<Cell, 4> activeCells() const;
    std::array<Cell, 4> ghostCells() const;
    std::vector<int> queuePreview(std::size_t count) const;

    bool hasActivePiece() const;
    int activePieceId() const;

    bool hasHoldPiece() const;
    int holdPiece() const;

private:
    static Cell spawnOrigin();

    void spawnFromQueue();
    bool tryMove(int dx, int dy);
    bool canPlace(int id, int rotation, const Cell& origin) const;
    std::array<Cell, 4> computeCells(int id, int rotation, const Cell& origin) const;
    void lockActive();
    void applyLineScore(int lines);

    Board board_{};
    Bag bag_{};
    std::queue<int> nextPieces_{};
    ActivePiece active_{};
    int hold_ = -1;
    bool holdUsed_ = false;
    Score score_{};
    GameState state_ = GameState::Menu;
    float dropTimer_ = 0.0f;
    std::size_t queueSize_ = static_cast<std::size_t>(engine_cfg::queuePreviewCount);
};

} // namespace tetris
