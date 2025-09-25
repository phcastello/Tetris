# Tetris

Implementação modular do Tetris em C++20. O projeto é organizado em um motor de jogo reutilizável e camadas de apresentação que consomem esse motor (aplicações GUI e CLI). A versão gráfica usa SFML para oferecer uma partida completa em tela cheia, enquanto o executável de linha de comando hoje funciona como stub para integrações futuras.

## Visão geral da arquitetura
- `tetris_engine`: biblioteca estática com as regras do jogo.
- `tetris_ui`: biblioteca SFML responsável por renderizar o jogo, HUD, música, layout adaptável ao monitor e tratamento de inputs contínuos.
- `tetris_gui`: executável principal. Instancia a UI, exibe menu inicial, controla o loop de partida e apresenta a tela de game over.
- `tetris_cli`: executável leve que linka apenas o motor. Exibe uma mensagem placeholder e serve como ponto de partida para coisas que não tem relação com a SFML.

## Estrutura do repositório
```
├── CMakeLists.txt
├── apps/
│   ├── tetris_cli.cpp
│   └── tetris_gui.cpp
├── assets/
│   ├── HennyPenny.ttf
│   └── TetrisGameMusic.ogg
├── engine/
│   ├── CMakeLists.txt
│   ├── include/tetris/
│   └── src/
└── ui/
    ├── CMakeLists.txt
    ├── include/tetris/
    └── src/
```

## Funcionalidades principais
- Loop completo com menu inicial, gameplay contínuo, pausa por ESC e tela de game over com opção de reinício.
- Sistema de peças 7-bag com histórico para reduzir repetições consecutivas.
- Pré-visualização de próximas peças (4 slots) e suporte a hold com bloqueio por turno.
- Ghost piece, hard drop, soft drop acelerado e detecção de entradas contínuas esquerda/direita.
- Placar clássico (100/300/500/800 pontos) exibido em tempo real.
- Layout em tela cheia, HUD informativo e trilha sonora/música ambiente em loop.

## Controles (GUI)
| Tecla            | Ação                         |
|------------------|------------------------------|
| `Enter`          | Iniciar partida (menu)       |
| `ESC`            | Sair / fechar janela         |
| `←` / `→`        | Mover peça                   |
| `↓`              | *Soft drop*                  |
| `↑`              | Girar peça (sentido horário) |
| `Espaço`         | *Hard drop*                  |
| `C`              | *Hold* / troca com hold      |

## Dependências
- CMake 3.20 ou superior.
- Compilador com suporte a C++20 (g++, clang++, MSVC).
- [SFML 2.6+](https://www.sfml-dev.org/) com módulos `graphics`, `window`, `system` e `audio` (necessário apenas quando `BUILD_GUI=ON`).

## Compilação
Recomenda-se um build fora da árvore.

### Linux / macOS
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
Certifique-se de que a SFML esteja instalada no sistema. Em distribuições Debian/Ubuntu, por exemplo: `sudo apt install libsfml-dev`.

### Windows (MSVC ou MinGW)
1. Instale a SFML 2.5+ e configure a variável `SFML_DIR` apontando para o pacote CMake da biblioteca.
2. Gere o build:
   ```bash
   cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
   cmake --build build
   ```

### Opções úteis
- `-DBUILD_GUI=OFF` desabilita a camada SFML quando você quer apenas o motor ou o CLI.
- `-DBUILD_CLI=OFF` evita gerar o stub em linha de comando.

## Execução
Após a compilação, os binários ficam no diretório de build (por padrão, `build/`). Execute a GUI a partir da raiz do projeto para que os assets sejam encontrados:
```bash
./build/tetris_gui
```
O CLI atual imprime apenas `tetris_cli stub`:
```bash
./build/tetris_cli
```

> Observação: mantenha a pasta `assets/` acessível no diretório de trabalho do executável ou ajuste `tetris::config::fontPath` e `musicPath` se mover os arquivos.

## Créditos
Criadores: Pedro Hasson Castello, Ruan Pablo Martins, Patrick Correa.

## Licença
Este projeto está licenciado sob os termos descritos em `LICENSE`.
