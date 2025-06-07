#include "include/utils.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());

int random(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

sf::Color getColorFromID(int id) {
    switch (id) {
        case 1: return sf::Color::Cyan;
        case 2: return sf::Color::Blue;
        case 3: return sf::Color::Yellow;
        case 4: return sf::Color::Green;
        case 5: return sf::Color::Red;
        case 6: return sf::Color(128, 0, 128); // Roxo
        case 7: return sf::Color(255,165,0);   // Laranja
        default: return sf::Color::White;
    }
}