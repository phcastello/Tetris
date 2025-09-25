# Tetris

Implementação em C++17 do clássico Tetris utilizando [SFML](https://www.sfml-dev.org/). O projeto foi refatorado para uma arquitetura modular, cobrindo menu, jogo completo em tela cheia e telas de fim de jogo, além de funcionalidades modernas como *ghost piece*, *hold*, *hard drop* e pré-visualização de peças.

## Recursos principais
- **Loop completo de jogo** com menu inicial, partida, desligamento por ESC e tela de *game over* com opção de reiniciar.
- **Sistema de peças 7-bag ajustado** para evitar repeticoes consecutivas e garantir variedade.
- **Fila de proximas peças** com visual alinhado a nova arquitetura e máscaras 4x4 pré-computadas.
- **Hold de peça** com bloqueio por turno e preview dedicado.
- **Ghost e hard drop** para jogabilidade ágil.
- **Pontuação clássica** (100/300/500/800) e exibição em tempo real.
- **Música e fontes** já integradas (assets na pasta `assets/`).

## Controles
| Tecla            | Ação                         |
|------------------|------------------------------|
| `Enter`          | Iniciar partida (menu)       |
| `ESC`            | Sair / fechar janela         |
| `←` / `→`        | Mover peca                   |
| `↓`              | *Soft drop*                  |
| `↑`              | Girar peca (sentido horario) |
| `Espaço`         | *Hard drop*                  |
| `C`              | *Hold* / troca com hold      |

## Dependências
- [SFML 2.5+](https://www.sfml-dev.org/) (módulos graphics, window, system, audio).
- Compilador compatível com C++17 (g++, clang++, MSVC).

## Estrutura do projeto
```
├── CMakeLists.txt
├── LICENSE
├── README.md
├── apps
│   ├── tetris_cli.cpp
│   └── tetris_gui.cpp
├── assets
│   ├── HennyPenny.ttf
│   └── TetrisGameMusic.ogg
├── build
│   ├── cli
│   │   ├── CMakeCache.txt
│   │   ├── CMakeFiles/
│   │   ├── Makefile
│   │   ├── cmake_install.cmake
│   │   ├── engine
│   │   │   ├── CMakeFiles/
│   │   │   ├── Makefile
│   │   │   ├── cmake_install.cmake
│   │   │   └── libtetris_engine.a
│   │   └── tetris_cli
│   └── gui
│       ├── CMakeCache.txt
│       ├── CMakeFiles/
│       ├── Makefile
│       ├── cmake_install.cmake
│       ├── compile_commands.json
│       ├── engine
│       │   ├── CMakeFiles
│       │   │   ├── CMakeDirectoryInformation.cmake
│       │   │   ├── progress.marks
│       │   │   └── tetris_engine.dir
│       │   ├── Makefile
│       │   ├── cmake_install.cmake
│       │   └── libtetris_engine.a
│       ├── tetris_gui
│       └── ui
│           ├── CMakeFiles/
│           ├── Makefile
│           ├── cmake_install.cmake
│           └── libtetris_ui.a
├── engine
│   ├── CMakeLists.txt
│   ├── include
│   │   └── tetris
│   │       ├── Bag.hpp
│   │       ├── Board.hpp
│   │       ├── EngineConfig.hpp
│   │       ├── Game.hpp
│   │       ├── Tetromino.hpp
│   │       └── Types.hpp
│   └── src
│       ├── Bag.cpp
│       ├── Board.cpp
│       ├── Game.cpp
│       └── Tetromino.cpp
├── include
│   └── tetris
├── src
└── ui
    ├── CMakeLists.txt
    ├── include
    │   └── tetris
    │       ├── App.hpp
    │       ├── Colors.hpp
    │       ├── Config.hpp
    │       ├── Hud.hpp
    │       └── Renderer.hpp
    └── src
        ├── App.cpp
        ├── Colors.cpp
        ├── Config.cpp
        ├── Hud.cpp
        └── Renderer.cpp
```

## Compilação
### Linux / macOS
```bash
g++ -std=c++17 Tetris.cpp src/*.cpp -Iinclude \
    $(pkg-config --cflags --libs sfml-graphics sfml-window sfml-system sfml-audio) \
    -o tetris
```

### Windows (MinGW)
```bash
g++ -std=c++17 Tetris.cpp src/*.cpp -Iinclude \
    -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o tetris.exe
```
Para compilar, é necessário que o SFML esteja instalado e configurado corretamente no sistema.
Certifique-se de que as DLLs/SO do SFML estejam acessíveis na execução.


## Execução
```bash
./tetris
```
A aplicacao abre em tela cheia. Utilize `ESC` para encerrar a qualquer momento.

## Créditos
Criadores: Pedro Hasson Castello, Ruan Pablo Martins, Patrick Correa.
