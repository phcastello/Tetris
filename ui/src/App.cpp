#include "tetris/App.hpp"

#include <iostream>

namespace tetris {

App::App() = default;

int App::run() {
    if (!initialize()) {
        return 1;
    }

    if (!hud_->showMenu(window_, layout_)) {
        return 0;
    }

    while (window_.isOpen()) {
        game_.start();
        music_.play();

        if (!runGameLoop()) {
            break;
        }

        if (!window_.isOpen()) {
            break;
        }

        if (!hud_->showGameOver(window_, layout_, game_.score())) {
            break;
        }
    }

    return 0;
}

bool App::initialize() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    layout_ = config::makeLayout(desktop);

    window_.create(desktop, "Tetris", sf::Style::Fullscreen);
    window_.setVerticalSyncEnabled(true);

    if (!font_.loadFromFile(config::fontPath)) {
        std::cerr << "Fonte nao encontrada." << std::endl;
        return false;
    }

    if (!music_.openFromFile(config::musicPath)) {
        std::cerr << "Erro ao carregar a musica." << std::endl;
        return false;
    }
    music_.setLoop(true);
    music_.setVolume(15.0f);

    renderer_ = std::make_unique<Renderer>(layout_);
    hud_ = std::make_unique<Hud>(font_);

    return true;
}

bool App::runGameLoop() {
    leftHeld_ = false;
    rightHeld_ = false;
    softDrop_ = false;
    leftTimer_ = 0.0f;
    rightTimer_ = 0.0f;

    sf::Clock clock;

    while (window_.isOpen() && game_.state() == GameState::Playing) {
        const float dt = clock.restart().asSeconds();

        sf::Event event{};
        while (window_.pollEvent(event)) {
            if (!handleEvent(event)) {
                return false;
            }
        }

        if (game_.state() != GameState::Playing) {
            break;
        }

        updateMovement(dt);
        game_.update(dt, softDrop_);

        renderer_->draw(window_, game_, font_);

        if (game_.state() == GameState::GameOver) {
            break;
        }
    }

    if (game_.state() == GameState::GameOver) {
        music_.stop();
    }

    return window_.isOpen();
}

bool App::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window_.close();
        return false;
    }

    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                window_.close();
                return false;
            case sf::Keyboard::Left:
                game_.moveLeft();
                leftHeld_ = true;
                leftTimer_ = 0.0f;
                break;
            case sf::Keyboard::Right:
                game_.moveRight();
                rightHeld_ = true;
                rightTimer_ = 0.0f;
                break;
            case sf::Keyboard::Down:
                softDrop_ = true;
                break;
            case sf::Keyboard::Up:
                game_.rotate();
                break;
            case sf::Keyboard::Space:
                game_.hardDrop();
                break;
            case sf::Keyboard::C:
                game_.hold();
                break;
            default:
                break;
        }
    }

    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
            case sf::Keyboard::Left:
                leftHeld_ = false;
                leftTimer_ = 0.0f;
                break;
            case sf::Keyboard::Right:
                rightHeld_ = false;
                rightTimer_ = 0.0f;
                break;
            case sf::Keyboard::Down:
                softDrop_ = false;
                break;
            default:
                break;
        }
    }

    return true;
}

void App::updateMovement(float dt) {
    if (leftHeld_) {
        leftTimer_ += dt;
        if (leftTimer_ >= engine_cfg::moveRepeatDelay) {
            game_.moveLeft();
            leftTimer_ = 0.0f;
        }
    }

    if (rightHeld_) {
        rightTimer_ += dt;
        if (rightTimer_ >= engine_cfg::moveRepeatDelay) {
            game_.moveRight();
            rightTimer_ = 0.0f;
        }
    }
}

} // namespace tetris
