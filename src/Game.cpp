#include "../include/tetris/Game.hpp"

#include <algorithm>
#include <utility>

namespace tetris {

namespace {

Cell computeSpawnOrigin() {
    return Cell{config::fieldWidth / 2 - 2, 0};
}

} // namespace

Game::Game() {
    reset();
}

void Game::reset() {
    board_.clear();
    score_.reset();
    hold_ = -1;
    holdUsed_ = false;
    dropTimer_ = 0.0f;

    while (!nextPieces_.empty()) {
        nextPieces_.pop();
    }

    bag_.resetHistory();
    bag_.refill(nextPieces_, queueSize_);
    active_ = ActivePiece{};
    state_ = GameState::Menu;
}

void Game::start() {
    reset();
    state_ = GameState::Playing;
    spawnFromQueue();
}

void Game::update(float dt, bool softDrop) {
    if (state_ != GameState::Playing || active_.id < 0) {
        return;
    }

    dropTimer_ += dt;
    const float delay = softDrop ? config::fastDropDelay : config::normalDropDelay;

    if (softDrop) {
        dropTimer_ = std::min(dropTimer_, delay);
    }

    while (dropTimer_ >= delay) {
        dropTimer_ -= delay;
        if (!tryMove(0, 1)) {
            lockActive();
            break;
        }
        if (!softDrop) {
            break;
        }
    }
}

void Game::moveLeft() {
    tryMove(-1, 0);
}

void Game::moveRight() {
    tryMove(1, 0);
}

void Game::rotate() {
    if (state_ != GameState::Playing || active_.id < 0) {
        return;
    }

    const int nextRotation = (active_.rotation + 1) % 4;
    if (canPlace(active_.id, nextRotation, active_.origin)) {
        active_.rotation = nextRotation;
    }
}

void Game::hardDrop() {
    if (state_ != GameState::Playing || active_.id < 0) {
        return;
    }

    while (tryMove(0, 1)) {
        // desce até o fim
    }
    lockActive();
}

void Game::hold() {
    if (state_ != GameState::Playing || active_.id < 0 || holdUsed_) {
        return;
    }

    if (hold_ == -1) {
        hold_ = active_.id;
        spawnFromQueue();
    } else {
        std::swap(hold_, active_.id);
        active_.rotation = 0;
        active_.origin = spawnOrigin();
        dropTimer_ = 0.0f;
        bag_.registerUse(active_.id);
        if (!canPlace(active_.id, active_.rotation, active_.origin)) {
            state_ = GameState::GameOver;
        }
    }

    holdUsed_ = true;
}

GameState Game::state() const {
    return state_;
}

void Game::setState(GameState state) {
    state_ = state;
}

int Game::score() const {
    return score_.value;
}

const Board& Game::board() const {
    return board_;
}

std::array<Cell, 4> Game::activeCells() const {
    if (active_.id < 0) {
        return {};
    }
    return computeCells(active_.id, active_.rotation, active_.origin);
}

std::array<Cell, 4> Game::ghostCells() const {
    if (active_.id < 0) {
        return {};
    }

    Cell ghostOrigin = active_.origin;
    while (canPlace(active_.id, active_.rotation, Cell{ghostOrigin.x, ghostOrigin.y + 1})) {
        ++ghostOrigin.y;
    }
    return computeCells(active_.id, active_.rotation, ghostOrigin);
}

std::vector<int> Game::queuePreview(std::size_t count) const {
    return bag_.peekN(nextPieces_, count);
}

bool Game::hasActivePiece() const {
    return active_.id >= 0 && state_ == GameState::Playing;
}

int Game::activePieceId() const {
    return active_.id;
}

bool Game::hasHoldPiece() const {
    return hold_ != -1;
}

int Game::holdPiece() const {
    return hold_;
}

Cell Game::spawnOrigin() {
    return computeSpawnOrigin();
}

void Game::spawnFromQueue() {
    bag_.refill(nextPieces_, queueSize_);
    if (nextPieces_.empty()) {
        state_ = GameState::GameOver;
        return;
    }

    active_.id = nextPieces_.front();
    nextPieces_.pop();
    bag_.refill(nextPieces_, queueSize_);

    active_.rotation = 0;
    active_.origin = spawnOrigin();
    dropTimer_ = 0.0f;
    holdUsed_ = false;
    bag_.registerUse(active_.id);

    if (!canPlace(active_.id, active_.rotation, active_.origin)) {
        state_ = GameState::GameOver;
    }
}

bool Game::tryMove(int dx, int dy) {
    if (state_ != GameState::Playing || active_.id < 0) {
        return false;
    }

    const Cell newOrigin{active_.origin.x + dx, active_.origin.y + dy};
    if (canPlace(active_.id, active_.rotation, newOrigin)) {
        active_.origin = newOrigin;
        return true;
    }
    return false;
}

bool Game::canPlace(int id, int rotation, const Cell& origin) const {
    const auto cells = computeCells(id, rotation, origin);
    return board_.canPlace(cells);
}

std::array<Cell, 4> Game::computeCells(int id, int rotation, const Cell& origin) const {
    return TetrominoSet::instance().cells(id, rotation, origin);
}

void Game::lockActive() {
    const auto cells = computeCells(active_.id, active_.rotation, active_.origin);
    board_.lock(cells, active_.id + 1);

    const int cleared = board_.clearFullLines();
    applyLineScore(cleared);

    if (state_ != GameState::Playing) {
        return;
    }

    spawnFromQueue();
}

void Game::applyLineScore(int lines) {
    if (lines > 0) {
        score_.addLines(lines);
    }
}

} // namespace tetris
