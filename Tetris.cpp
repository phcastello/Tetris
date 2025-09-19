#include <exception>
#include <iostream>

#include "include/tetris/App.hpp"

int main() {
    try {
        tetris::App app;
        return app.run();
    } catch (const std::exception& ex) {
        std::cerr << "Erro fatal: " << ex.what() << '\n';
    } catch (...) {
        std::cerr << "Erro desconhecido.\n";
    }
    return 1;
}
