#include "../include/tetris/Bag.hpp"

#include <algorithm>

namespace tetris {

Bag::Bag() : rng_(std::random_device{}()) {
    for (int i = 0; i < static_cast<int>(pieces_.size()); ++i) {
        pieces_[i] = i;
    }
}

void Bag::refill(std::queue<int>& queue, std::size_t targetSize) {
    int lastInserted = lastQueued_;
    if (!queue.empty()) {
        std::queue<int> copy = queue;
        while (!copy.empty()) {
            lastInserted = copy.front();
            copy.pop();
        }
    }

    while (queue.size() < targetSize) {
        std::array<int, 7> bag = pieces_;
        std::shuffle(bag.begin(), bag.end(), rng_);

        for (std::size_t i = 0; i < bag.size() && queue.size() < targetSize; ++i) {
            auto shouldAvoid = [&](int candidate) {
                if (candidate == lastInserted) {
                    return true;
                }
                return std::find(recent_.begin(), recent_.end(), candidate) != recent_.end();
            };

            std::size_t pickIndex = i;
            if (shouldAvoid(bag[pickIndex])) {
                for (std::size_t j = i + 1; j < bag.size(); ++j) {
                    if (!shouldAvoid(bag[j])) {
                        pickIndex = j;
                        break;
                    }
                }
            }

            if (pickIndex != i) {
                std::swap(bag[i], bag[pickIndex]);
            }

            int candidate = bag[i];
            queue.push(candidate);
            lastInserted = candidate;
            lastQueued_ = candidate;
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

void Bag::registerUse(int pieceId) {
    recent_.push_back(pieceId);
    if (recent_.size() > recentLimit_) {
        recent_.pop_front();
    }
}

void Bag::resetHistory() {
    lastQueued_ = -1;
    recent_.clear();
}

} // namespace tetris
