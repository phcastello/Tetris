#pragma once

#include <array>
#include <queue>
#include <random>
#include <vector>

namespace tetris {

class Bag {
public:
    Bag();

    void refill(std::queue<int>& queue, std::size_t targetSize);
    std::vector<int> peekN(const std::queue<int>& queue, std::size_t count) const;

private:
    mutable std::mt19937 rng_;
    std::array<int, 7> pieces_{};
};

} // namespace tetris
