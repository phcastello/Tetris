#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include "DataStructLib.hpp"

const int fieldWidth = 10;
const int fieldHeight = 20;
int score = 0;

// campo de jogo
int field[fieldHeight][fieldWidth] = {0};

// peças
int figures[7][4] = {
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

struct Point{
    int x, y;
} a[4], b[4];

int offsetSpawnFig = (fieldWidth / 2) - 1;

std::random_device rd;
std::mt19937 gen(rd());

int random(int min, int max){
    std::uniform_int_distribution<> dist(min,max);
    return dist(gen);
}

bool check() {
    for (int i = 0; i < 4; i++) {
        if (a[i].x < 0 || a[i].x >= fieldWidth || a[i].y >= fieldHeight) return false;
        else if (field[a[i].y][a[i].x]) return false;
    }
    return true;
}

bool check(Point p[4]) {
    for (int i = 0; i < 4; i++) {
        if (p[i].x < 0 || p[i].x >= fieldWidth || p[i].y >= fieldHeight) return false;
        else if (field[p[i].y][p[i].x]) return false;
    }
    return true;
}

bool showGameOver(sf::RenderWindow& window, const sf::VideoMode& desktop){
    sf::Font font;
    if (!font.loadFromFile("HennyPenny-Regular.ttf")) {
        return false;
    }

    sf::Text gameOverText("GAME OVER", font, 80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(desktop.width / 2.f - gameOverText.getGlobalBounds().width / 2, desktop.height * 0.3f);

    sf::Text scoreText("Seu Score: " + std::to_string(score), font, 70);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(desktop.width/2.f - scoreText.getGlobalBounds().width/2, desktop.height * 0.4f);

    sf::Text restartText("Pressione ENTER para Reiniciar", font, 40);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(desktop.width / 2.f - restartText.getGlobalBounds().width / 2, desktop.height * 0.5f);

    sf::Text exitText("Pressione ESC para Sair", font, 40);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(desktop.width / 2.f - exitText.getGlobalBounds().width / 2, desktop.height * 0.6f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    return false;
                if (event.key.code == sf::Keyboard::Enter)
                    return true;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(gameOverText);
        window.draw(scoreText);
        window.draw(restartText);
        window.draw(exitText);
        window.display();
    }

    return false;
}

bool showMenu(sf::RenderWindow& window, const sf::VideoMode& desktop){
    sf::Font font;
    if (!font.loadFromFile("HennyPenny-Regular.ttf")) {
        return false;
    }

    sf::Text title("TETRIS", font, 80);
    title.setFillColor(sf::Color::White);
    title.setPosition(desktop.width / 2.f - title.getGlobalBounds().width / 2, desktop.height * 0.2f);

    sf::Text playText("Pressione ENTER para Jogar", font, 40);
    playText.setFillColor(sf::Color::Green);
    playText.setPosition(desktop.width / 2.f - playText.getGlobalBounds().width / 2, desktop.height * 0.5f);

    sf::Text exitText("Pressione ESC para Sair", font, 40);
    exitText.setFillColor(sf::Color::Red);
    exitText.setPosition(desktop.width / 2.f - exitText.getGlobalBounds().width / 2, desktop.height * 0.6f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter)
                    return true;
                if (event.key.code == sf::Keyboard::Escape)
                    return false;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(playText);
        window.draw(exitText);
        window.display();
    }

    return false; // se fechar a janela
}

void setPiece(int pieceIndex, Point a[4], int figures[7][4]) {
    for (int i = 0; i < 4; ++i) {
        a[i].x = (figures[pieceIndex][i] % 2) + offsetSpawnFig;
        a[i].y = figures[pieceIndex][i] / 2;
    }
}

int main() {
    sf::Font font;
    if (!font.loadFromFile("HennyPenny-Regular.ttf")){
        std::cerr << "Fonte não encontrada.";
        return false;
    }
    float moveTimer = 0;
    float moveDelay = 0.1f;

    // Tela cheia
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Tetris", sf::Style::Fullscreen);

    if (!showMenu(window, desktop)) {
        return 0; // jogador saiu no menu
    }

    sf::Music music;
    if (!music.openFromFile("Tetris.ogg")) {
        std::cerr << "Erro ao carregar a música\n";
        return -1;
    }
    music.setLoop(true);     // Repete a música
    music.setVolume(15);     // Volume de 0 a 100
    music.play();

    sf::Color colors[] = {
        sf::Color(0, 0, 0),       // 0 - vazio
        sf::Color(255, 0, 0),     // 1 - vermelho (I)
        sf::Color(0, 255, 0),     // 2 - verde (Z)
        sf::Color(0, 0, 255),     // 3 - azul (S)
        sf::Color(255, 255, 0),   // 4 - amarelo (T)
        sf::Color(255, 165, 0),   // 5 - laranja (L)
        sf::Color(128, 0, 128),   // 6 - roxo (J)
        sf::Color(0, 255, 255)    // 7 - ciano (O)
    };
    Queue<int> nextPieces;
    int holdPiece = -1;       // -1 significa nenhum hold ainda
    bool holdUsed = false;    // impede múltiplos holds por peça
    const int queueSize = 4;  // quantas peças mantemos na fila

    for (int i = 0; i < queueSize; ++i) {
        nextPieces.enqueue(random(0, 6));
    }

    float marginPercent = 0.10f; // 10% de margem vertical
    int usableHeight = desktop.height * (1.0f - marginPercent);
    int blockSize = usableHeight / fieldHeight;

    int totalFieldHeightPixels = blockSize * fieldHeight;

    // Calcula as margens automáticas para centralizar verticalmente
    int offsetY = (desktop.height - totalFieldHeightPixels) / 2;
    int offsetX = (desktop.width - blockSize * fieldWidth) / 2;

    sf::RectangleShape block(sf::Vector2f(blockSize - 2, blockSize - 2));
    block.setFillColor(sf::Color::White);

    sf::RectangleShape border(sf::Vector2f(blockSize, blockSize));
    border.setFillColor(sf::Color::Black);

    sf::Clock clock;
    float timer = 0;
    float normalDelay = 0.3f;
    float fastDelay = 0.05f;
    float delay = normalDelay;

    int n = nextPieces.dequeue();
    int colorNum = n + 1;   
    int dx = 0;
    bool rotate = false;

    float time;
    for (int i = 0; i < 4; i++) {
        a[i].x = figures[n][i] % 2 + offsetSpawnFig;
        a[i].y = figures[n][i] / 2;
    }

    while(window.isOpen()){
        time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        moveTimer += time;

        sf::Event e;
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed || 
               (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape))
                window.close();

            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Up) rotate = true;
                else if (e.key.code == sf::Keyboard::Left) {
                    dx = -1;
                    moveTimer = 0; // reseta o timer pra permitir repetição mais natural
                }
                else if (e.key.code == sf::Keyboard::Right) {
                    dx = 1;
                    moveTimer = 0;
                }
            }
            if(e.type == sf::Event::KeyPressed and e.key.code == sf::Keyboard::C and !holdUsed) {
                if (holdPiece == -1) {
                    holdPiece = n;
                    n = nextPieces.dequeue();
                    nextPieces.enqueue(rand() % 7);
                } else {
                    std::swap(holdPiece, n);
                }
            
                colorNum = n + 1;
                setPiece(n, a, figures);
                holdUsed = true;
            }
            if(e.type == sf::Event::KeyPressed and e.key.code == sf::Keyboard::Space){
                while (true) {
                    for (int i = 0; i < 4; i++) b[i] = a[i]; // salva estado atual
                    for (int i = 0; i < 4; i++) a[i].y += 1; // tenta descer 1
                    if (!check()) { // se colidiu
                        for (int i = 0; i < 4; i++) a[i] = b[i]; // volta 1 passo
                        break;
                    }
                }
            }  
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (moveTimer > moveDelay) {
                dx = -1;
                moveTimer = 0;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (moveTimer > moveDelay) {
                dx = 1;
                moveTimer = 0;
            }
        }


        // move horizontal
        for (int i = 0; i < 4; i++){
            b[i] = a[i]; a[i].x += dx;
        }
        if (!check()){
            for (int i = 0; i < 4; i++){
                a[i] = b[i];
            }
        }
        dx = 0;

        // rotate
        if (rotate) {
            Point p = a[1]; // centro de rotação
            for (int i = 0; i < 4; i++) {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
        }
        rotate = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            delay = fastDelay;
        else
            delay = normalDelay;

        if (timer > delay){
            for (int i = 0; i < 4; i++){
                b[i] = a[i]; a[i].y += 1;
            }

            if (!check()){
                for (int i = 0; i < 4; i++){
                    field[b[i].y][b[i].x] = colorNum;
                }
                holdUsed = false;
                n = nextPieces.dequeue();

                colorNum = n + 1;

                // Enfileira uma nova peça aleatória para manter a fila cheia
                nextPieces.enqueue(random(0,6));

                // Atualiza a peça atual "a" com os novos pontos
                for (int i = 0; i < 4; i++) {
                    a[i].x = figures[n][i] % 2 + offsetSpawnFig;
                    a[i].y = figures[n][i] / 2;
                }
                
            }

            if (!check()){
                music.stop();
                showGameOver(window, desktop);
                return 0;
            }
            timer = 0;
        }


        // linha completa
        int k = fieldHeight - 1;
        int linesCleared = 0; // contador de linhas limpas

        for (int i = fieldHeight - 1; i >= 0; i--) {
            int count = 0;
            for (int j = 0; j < fieldWidth; j++) {
                if (field[i][j]) count++;
                field[k][j] = field[i][j];
            }

            if (count < fieldWidth) {
                k--; // move para cima
            } else {
                linesCleared++; // linha completa encontrada
            }
        }

        switch (linesCleared){
            case 1: score += 100; break;
            case 2: score += 300; break;
            case 3: score += 500; break;
            case 4: score += 800; break;
            default: break; // 0 linhas limpas -> nada muda
        }

        Point ghost[4];
        for (int i = 0; i < 4; ++i)
            ghost[i] = a[i]; // copia as posições da peça atual

        while (true) {
            for (int i = 0; i < 4; ++i)
                ghost[i].y += 1;

            if (!check(ghost)) {
                for (int i = 0; i < 4; ++i)
                    ghost[i].y -= 1;
                break;
            }
        }

        // draw
        window.clear(sf::Color::Black);

        // desenha os blocos fixos no campo
        for (int y = 0; y < fieldHeight; y++) {
            for (int x = 0; x < fieldWidth; x++) {
                int value = field[y][x];
                if (value == 0) continue;

                block.setFillColor(colors[value]);
                block.setPosition(offsetX + x * blockSize + 1, offsetY + y * blockSize + 1);
                window.draw(block);
            }
        }

        // fundo da área jogável (cinza escuro)
        sf::RectangleShape gameAreaBg(sf::Vector2f(fieldWidth * blockSize, fieldHeight * blockSize));
        gameAreaBg.setPosition(offsetX, offsetY);
        gameAreaBg.setFillColor(sf::Color(30, 30, 30)); // cinza escuro
        window.draw(gameAreaBg);

        // linhas verticais do quadriculado
        sf::Vertex line[2];
        for (int j = 1; j < fieldWidth; j++) {
            float x = offsetX + j * blockSize;
            line[0] = sf::Vertex(sf::Vector2f(x, offsetY), sf::Color(50, 50, 50));
            line[1] = sf::Vertex(sf::Vector2f(x, offsetY + fieldHeight * blockSize), sf::Color(50, 50, 50));
            window.draw(line, 2, sf::Lines);
        }

        // linhas horizontais do quadriculado
        for (int i = 1; i < fieldHeight; i++) {
            float y = offsetY + i * blockSize;
            line[0] = sf::Vertex(sf::Vector2f(offsetX, y), sf::Color(50, 50, 50));
            line[1] = sf::Vertex(sf::Vector2f(offsetX + fieldWidth * blockSize, y), sf::Color(50, 50, 50));
            window.draw(line, 2, sf::Lines);
        }

        // campo
        for (int i = 0; i < fieldHeight; i++) {
            for (int j = 0; j < fieldWidth; j++) {
                if (field[i][j] == 0) continue;
                block.setPosition(offsetX + j * blockSize, offsetY + i * blockSize);
                block.setFillColor(colors[field[i][j]]);
                window.draw(block);
            }
        }

        sf::Color ghostColor = colors[colorNum];
        ghostColor.a = 100;
        for (int i = 0; i < 4; i++) {
            block.setFillColor(ghostColor);
            block.setPosition(offsetX + ghost[i].x * blockSize + 1, offsetY + ghost[i].y * blockSize + 1);
            window.draw(block);
        }

        // peça atual
        for (int i = 0; i < 4; i++) {
            block.setFillColor(colors[colorNum]);
            block.setPosition(offsetX + a[i].x * blockSize + 1, offsetY + a[i].y * blockSize + 1);
            window.draw(block);
        }

        // desenha a area de hold
        int holdBoxX = 50;
        int holdBoxY = 50;
        int holdBoxSide = 5 * blockSize;
        sf::RectangleShape holdArea(sf::Vector2f(holdBoxSide, holdBoxSide));
        holdArea.setPosition(holdBoxX, holdBoxY);
        holdArea.setFillColor(sf::Color(50, 50, 50)); // cinza escuro
        window.draw(holdArea);

        // desenha a area de fila
        float queueAreaMarginRight = 50;
        float queueAreaMarginTop = 50;
        float queueBoxWidth = holdBoxSide;
        float queueBoxHeight = holdBoxSide * 3;
        sf::RectangleShape queueArea(sf::Vector2f(queueBoxWidth,queueBoxHeight));
        float posX = desktop.width - queueBoxWidth - queueAreaMarginRight;
        float posY = queueAreaMarginTop;
        queueArea.setPosition(posX, posY);
        queueArea.setFillColor(sf::Color(50, 50, 50)); //cinza
        window.draw(queueArea);

        // mostra a fila
        Node<int>* currentNode = nextPieces.getHead();
        float spacingBetweenPieces = 100.0f;
        int index = 0;
        
        while(currentNode != nullptr and index < queueSize){
            int pieceId = currentNode->getInfo();

            // calculo para centralização de cada peça
            int minX = 10, maxX = -10, minY = 10, maxY = -10;
            for(int i=0; i < 4; i++){
                int x = figures[pieceId][i] % 2;
                int y = figures[pieceId][i] / 2;
                minX = std::min(minX, x);
                maxX = std::max(maxX, x);
                minY = std::min(minY, y);
                maxY = std::max(maxY, y);
            }
            int pieceWidth = maxX - minX + 1;
            int pieceHeight = maxY - minY + 1;

            // posição da peça na fila
            float offsetPieceX = posX + (queueBoxWidth - pieceWidth * blockSize) / 2.0f - minX * blockSize;
            float offsetPieceY = posY + index * (blockSize * 3 + spacingBetweenPieces) + (blockSize - minY * blockSize);

            for(int i=0; i < 4; i++){
                int x = figures[pieceId][i] % 2;
                int y = figures[pieceId][i] / 2;

                block.setFillColor(colors[pieceId + 1]);
                block.setPosition(offsetPieceX + x * blockSize, offsetPieceY + y * blockSize);
                window.draw(block);
            }
            currentNode = currentNode->getLink();
            index++;
        }


        // mostra a peça hold
        if (holdPiece != -1) {
            int minX = 10, maxX = -10, minY = 10, maxY = -10;
            for (int i = 0; i < 4; i++) {
                int x = figures[holdPiece][i] % 2;
                int y = figures[holdPiece][i] / 2;
                if (x < minX) minX = x;
                if (x > maxX) maxX = x;
                if (y < minY) minY = y;
                if (y > maxY) maxY = y;
            }
            int pieceWidth = (maxX - minX + 1);
            int pieceHeight = (maxY - minY + 1);
        
            float offsetPieceX = holdBoxX + (holdBoxSide - pieceWidth * blockSize) / 2 - minX * blockSize;
            float offsetPieceY = holdBoxY + (holdBoxSide - pieceHeight * blockSize) / 2 - minY * blockSize;
        
            for (int i = 0; i < 4; i++) {
                int x = figures[holdPiece][i] % 2;
                int y = figures[holdPiece][i] / 2;
        
                block.setFillColor(colors[holdPiece + 1]);
                block.setPosition(offsetPieceX + x * blockSize, offsetPieceY + y * blockSize);
                window.draw(block);
            }
        }

        sf::Text holdLabel;
        holdLabel.setFont(font);
        holdLabel.setString("HOLD");
        holdLabel.setCharacterSize(48);
        holdLabel.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = holdLabel.getLocalBounds();
        int holdBoxMarginX = 50;
        int holdBoxMarginY = 50;
        // centraliza o texto abaixo da caixa
        float textX = holdBoxMarginX + (holdBoxSide / 2) - (textBounds.width / 2);
        float textY = holdBoxMarginY + holdBoxSide + 10;
        holdLabel.setPosition(textX,textY); // abaixo da caixa
        window.draw(holdLabel);

        sf::Text queueLabel;
        queueLabel.setFont(font);
        queueLabel.setString("Proximas Pecas");
        queueLabel.setCharacterSize(48);
        queueLabel.setFillColor(sf::Color::White);
        // calcula centralização horizontal em relação à queueArea
        sf::FloatRect queueTextBounds = queueLabel.getLocalBounds();
        float queueTextX = posX + (queueBoxWidth / 2) - (queueTextBounds.width / 2);
        float queueTextY = posY + queueBoxHeight + 10;
        queueLabel.setPosition(queueTextX, queueTextY);
        window.draw(queueLabel);

        sf::Text scoreLabel;
        scoreLabel.setFont(font);
        scoreLabel.setString("Score: " + std::to_string(score));
        scoreLabel.setCharacterSize(100);
        scoreLabel.setFillColor(sf::Color::White);
        sf::FloatRect bounds = scoreLabel.getLocalBounds();
        // Corrigir a origem para alinhar exatamente pela parte inferior esquerda
        scoreLabel.setOrigin(bounds.left, bounds.top + bounds.height);

        // Agora posicionar no canto inferior esquerdo da janela
        scoreLabel.setPosition(10.f, window.getSize().y - 10.f);
        window.draw(scoreLabel);

        
        window.display();
    }

    return 0;
}
