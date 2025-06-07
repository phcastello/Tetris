#include "Menu.hpp"

Menu::Menu(const sf::VideoMode& desktop) : desktop(desktop){
    if (!font.loadFromFile("../assets/HennyPenny-Regular.ttf")) {
        throw std::runtime_error("Falha ao carregar a fonte HennyPenny-Regular.ttf");
    }

    sf::Text title = createText("TETRIS", 80, sf::Color::White, 0.2f);
    sf::Text playText = createText("Pressione ENTER para Jogar", 40, sf::Color::Green, 0.5f);
    sf::Text exitText = createText("Pressione ESC para Sair",    40, sf::Color::Red,   0.6f);
}

sf::Text Menu::createText(const std::string& content, unsigned int size, sf::Color color, float yPercent){
    sf::Text text(content, font, size);
    text.setFillColor(color);
    float x = desktop.width / 2.f;
    float y = desktop.height * yPercent;
    text.setPosition(x - text.getGlobalBounds().width / 2, y);
    return text;
}   

bool Menu::show(sf::RenderWindow& window) {
    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Enter){
                    return true;
                }
                if(event.key.code == sf::Keyboard::Escape){
                    return false;
                }
                    
            }
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(playText);
        window.draw(exitText);
        window.display();
    }

    return false; // Se a janela for fechada
}
