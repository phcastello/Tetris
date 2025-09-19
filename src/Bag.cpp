#include "../include/tetris/Bag.hpp"

#include <algorithm>

namespace tetris {

Bag::Bag() : rng_(std::random_device{}()) {
    for (int i = 0; i < static_cast<int>(pieces_.size()); ++i) {
        pieces_[i] = i;
    }
}

void Bag::refill(std::queue<int>& queue, std::size_t targetSize) {
    while (queue.size() < targetSize) {
        std::array<int, 7> bag = pieces_;
        std::shuffle(bag.begin(), bag.end(), rng_);
        for (int id : bag) {
            queue.push(id);
            if (queue.size() >= targetSize) {
                break;
            }
        }
    }
}

std::vector<int> Bag::peekN(const std::queue<int>& queue, std::size_t count) const {
    std::vector<int> result;
    result.reserve(count);

    std::queue<int> copy = queue;
    while (!copy.empty() && result.size() < count) {
        result.push_back(copy.front());
        copy.pop();
    }

    return result;
}

} // namespace tetris
