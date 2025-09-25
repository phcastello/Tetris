#include "tetris/Hud.hpp"

#include <string>

namespace tetris {

Hud::Hud(const sf::Font& font) : font_(font) {}

bool Hud::showMenu(sf::RenderWindow& window, const config::Layout& layout) {
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return false;
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    return true;
                }
            }
        }

        window.clear(sf::Color::Black);

        sf::Text title("TETRIS", font_, 80);
        title.setFillColor(sf::Color::White);
        const auto titleBounds = title.getLocalBounds();
        title.setPosition(
            layout.desktop.width / 2.0f - titleBounds.width / 2.0f,
            layout.desktop.height * 0.2f);
        window.draw(title);

        sf::Text play("Pressione ENTER para Jogar", font_, 40);
        play.setFillColor(sf::Color::Green);
        const auto playBounds = play.getLocalBounds();
        play.setPosition(
            layout.desktop.width / 2.0f - playBounds.width / 2.0f,
            layout.desktop.height * 0.5f);
        window.draw(play);

        sf::Text exit("Pressione ESC para Sair", font_, 40);
        exit.setFillColor(sf::Color::Red);
        const auto exitBounds = exit.getLocalBounds();
        exit.setPosition(
            layout.desktop.width / 2.0f - exitBounds.width / 2.0f,
            layout.desktop.height * 0.6f);
        window.draw(exit);

        sf::Text signature("Criadores: Pedro Hasson Castello, Ruan Pablo Martins, Patrick Correa", font_, 28);
        signature.setFillColor(sf::Color(180, 180, 180));
        const auto signatureBounds = signature.getLocalBounds();
        signature.setPosition(
            layout.desktop.width / 2.0f - signatureBounds.width / 2.0f,
            layout.desktop.height * 0.8f);
        window.draw(signature);

        window.display();
    }

    return false;
}

bool Hud::showGameOver(sf::RenderWindow& window, const config::Layout& layout, int score) {
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return false;
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    return true;
                }
            }
        }

        window.clear(sf::Color::Black);

        sf::Text gameOver("GAME OVER", font_, 80);
        gameOver.setFillColor(sf::Color::Red);
        const auto overBounds = gameOver.getLocalBounds();
        gameOver.setPosition(
            layout.desktop.width / 2.0f - overBounds.width / 2.0f,
            layout.desktop.height * 0.3f);
        window.draw(gameOver);

        sf::Text scoreText("Seu Score: " + std::to_string(score), font_, 70);
        scoreText.setFillColor(sf::Color::Yellow);
        const auto scoreBounds = scoreText.getLocalBounds();
        scoreText.setPosition(
            layout.desktop.width / 2.0f - scoreBounds.width / 2.0f,
            layout.desktop.height * 0.4f);
        window.draw(scoreText);

        sf::Text restart("Pressione ENTER para Reiniciar", font_, 40);
        restart.setFillColor(sf::Color::White);
        const auto restartBounds = restart.getLocalBounds();
        restart.setPosition(
            layout.desktop.width / 2.0f - restartBounds.width / 2.0f,
            layout.desktop.height * 0.5f);
        window.draw(restart);

        sf::Text exit("Pressione ESC para Sair", font_, 40);
        exit.setFillColor(sf::Color::White);
        const auto exitBounds = exit.getLocalBounds();
        exit.setPosition(
            layout.desktop.width / 2.0f - exitBounds.width / 2.0f,
            layout.desktop.height * 0.6f);
        window.draw(exit);

        sf::Text signature("Criadores: Pedro Hasson Castello, Ruan Pablo Martins, Patrick Correa", font_, 28);
        signature.setFillColor(sf::Color(180, 180, 180));
        const auto signatureBounds = signature.getLocalBounds();
        signature.setPosition(
            layout.desktop.width / 2.0f - signatureBounds.width / 2.0f,
            layout.desktop.height * 0.82f);
        window.draw(signature);

        window.display();
    }

    return false;
}

} // namespace tetris
