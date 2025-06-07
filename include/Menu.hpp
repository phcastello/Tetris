#pragma once
#include <SFML/Graphics.hpp>
#include "utils.hpp"

class Menu {
public:
    Menu(const sf::VideoMode& desktop);

    // Retorna true se o jogador apertar ENTER, false se apertar ESC ou fechar.
    bool show(sf::RenderWindow& window);
private:
    sf::Font font;
    sf::Text title;
    sf::Text playText;
    sf::Text exitText;
    sf::VideoMode desktop;

    sf::Text createText(const std::string& content, unsigned int size, sf::Color color, float yPercent);
};
