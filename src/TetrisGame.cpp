#pragma once
#include "TetrisGame.hpp"
#include "utils.hpp"
#include "GameField.hpp"
#include "Tetromino.hpp"

TetrisGame::TetrisGame() :
    window(sf::VideoMode::getDesktopMode(), "Tetris", sf::Style::Fullscreen),
    currentTetromino(static_cast<TetrominoType>(random(0, 6)))
{
    // Carregar fonte
    std::string HennyPennyPath = "../assets/HennyPenny.ttf";
    if (!HennyPenny.loadFromFile(HennyPennyPath)) {
        std::cerr << "Erro ao carregar fonte HennyPenny em " << HennyPennyPath << "\n";
        exit(-1);
    }

    // Carregar música
    std::string TetrisGameMusicPath = "../assets/TetrisGameMusic.ogg";
    if (!TetrisGameMusic.openFromFile(TetrisGameMusicPath)) {
        std::cerr << "Erro ao carregar o áudio TetrisGameMusic em " << TetrisGameMusicPath << "\n";
        exit(-1);
    }
    TetrisGameMusic.setLoop(true);
    TetrisGameMusic.setVolume(15);
    TetrisGameMusic.play();

    // Preencher fila de peças
    for (int i = 0; i < queueSize; i++) {
        nextPieces.enqueue(random(0, 6));
    }

    // Substituir pela primeira peça da fila
    currentTetromino = Tetromino(static_cast<TetrominoType>(nextPieces.dequeue()));

    // Posição inicial da peça
    currentPosition = {3, 0};
}


void TetrisGame::processInput(const sf::Event& event) {
    if (event.type == sf::Event::Closed || 
       (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
        window.close();
    }

    if (event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Up){
            rotate = true;
        }
        else if(event.key.code == sf::Keyboard::Left){
            dx = -1;
            moveTimer = 0;
        }
        else if(event.key.code == sf::Keyboard::Right){
            dx = 1;
            moveTimer = 0;
        }
        else if(event.key.code == sf::Keyboard::Down){
            delay = fastDelay;
        }
        else if(event.key.code == sf::Keyboard::C and !holdUsed){
            if (!holdPiece.has_value()) {
                holdPiece = currentTetromino;
                currentTetromino = Tetromino(static_cast<TetrominoType>(nextPieces.dequeue()));
                nextPieces.enqueue(random(0,6));
            }
            else {
                std::swap(*holdPiece, currentTetromino);
            }
        }
        else if(sf::Event::KeyPressed and event.key.code == sf::Keyboard::Space){
            int finalY = field.getHardDropY(currentTetromino, currentPosition);
            currentPosition.y = finalY;

            field.fixTetromino(currentTetromino);
            field.clearLines();
        }
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == sf::Keyboard::Down) {
            delay = normalDelay;
        }
    }
}

void TetrisGame::update(){
    // 1. mover peça na horizontal se moveTimer ultrapassou moveDelay
    if (dx != 0 && moveTimer > moveDelay) {
        Point newPos = { currentPosition.x + dx, currentPosition.y };
        if (field.isValidPosition(currentTetromino, currentTetromino.getBlocks(), newPos)) {
            currentPosition = newPos;
        }
        dx = 0;  // resetar movimento horizontal até próxima tecla
        moveTimer = 0;
    }

    // 2. rotacionar peça, se solicitado
    if (rotate) {
        // Aqui vamos usar a rotação "tentativa"
        // A ideia: gerar os blocos rotacionados, verificar colisão e aplicar se válido
        std::vector<Point> rotatedBlocks;
        Point pivot = currentTetromino.getBlocks()[1]; // pivot é o bloco central
        
        for (const auto& block : currentTetromino.getBlocks()) {
            int x_rel = block.x - pivot.x;
            int y_rel = block.y - pivot.y;

            int x_rot = y_rel;
            int y_rot = -x_rel;

            rotatedBlocks.push_back({pivot.x + x_rot, pivot.y + y_rot});
        }

        if (field.isValidPosition(currentTetromino, rotatedBlocks, currentPosition)) {
            // Se válido, atualiza os blocos da peça
            currentTetromino.setBlocks(rotatedBlocks);  // Para isso, precisaremos do método setBlocks()
        }
        rotate = false;
    }

    // 3. avançar a peça para baixo com base no timer
    if (timer > delay) {
        Point newPos = { currentPosition.x, currentPosition.y + 1 };
        if (field.isValidPosition(currentTetromino, currentTetromino.getBlocks(), newPos)) {
            currentPosition = newPos;
        }
        else {
            // Não pode descer, fixa a peça e cria nova
            std::vector<Point> absoluteBlocks;
            for (const auto& block : currentTetromino.getBlocks()) {
                absoluteBlocks.push_back({ block.x + currentPosition.x, block.y + currentPosition.y });
            }

            currentTetromino.setBlocks(absoluteBlocks); // atualiza os blocos
            field.fixTetromino(currentTetromino);
            field.clearLines();

            currentTetromino = Tetromino(static_cast<TetrominoType>(nextPieces.dequeue()));
            nextPieces.enqueue(random(0, 6));
            currentPosition = {3, 0};
            holdUsed = false;

            // Se a nova peça já está em posição inválida, o jogo acabou!
            if (!field.isValidPosition(currentTetromino, currentTetromino.getBlocks(), currentPosition)) {
                window.close();  // por exemplo, fechar o jogo
            }
        }
        timer = 0;
    }
}

void TetrisGame::render() {
    window.clear(sf::Color::Black);

    // 1. desenhar o campo fixado
    field.draw(window);// TODO: Resolver

    // 2. desenhar a peça atual na posição atual
    for (const auto& block : currentTetromino.getBlocks()) {
        sf::RectangleShape rectangle(sf::Vector2f(30,30));
        rectangle.setFillColor(getColorFromID(currentTetromino.getColorID()));
        rectangle.setPosition((block.x + currentPosition.x) * 30, (block.y + currentPosition.y) * 30);
        window.draw(rectangle);
    }

    // 3. desenhar a peça em hold, se houver
    if (holdPiece.has_value()) {
        // desenhar holdPiece na posição fixa da tela, por exemplo no canto
        int offsetX = 12; // fora do campo
        int offsetY = 1;

        for (const auto& block : holdPiece->getBlocks()) {
            sf::RectangleShape rectangle(sf::Vector2f(30,30));
            rectangle.setFillColor(getColorFromID(holdPiece->getColorID()));
            rectangle.setPosition((block.x + offsetX) * 30, (block.y + offsetY) * 30);
            window.draw(rectangle);
        }
    }

    // 4. desenhar fila de próximas peças (opcional)

    window.display();
}

void TetrisGame::run() {
    while (window.isOpen()) {
        time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        moveTimer += time;

        sf::Event event;
        while (window.pollEvent(event)) {
            processInput(event);
        }

        update();
        render();
    }
}
