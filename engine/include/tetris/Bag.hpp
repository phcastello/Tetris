#pragma once

#include <array>
#include <deque>
#include <queue>
#include <random>
#include <vector>

namespace tetris {

class Bag {
public:
    Bag();

    void refill(std::queue<int>& queue, std::size_t targetSize);
    std::vector<int> peekN(const std::queue<int>& queue, std::size_t count) const;
    void registerUse(int pieceId);
    void resetHistory();

private:
    mutable std::mt19937 rng_;
    std::array<int, 7> pieces_{};
    int lastQueued_ = -1;
    std::deque<int> recent_;
    std::size_t recentLimit_ = 3;
};

} // namespace tetris
