#include "../include/tetris/Config.hpp"

namespace tetris::config {

Layout makeLayout(const sf::VideoMode& desktop) {
    Layout layout{};
    layout.desktop = desktop;

    constexpr float marginPercent = 0.10f;
    const int usableHeight = static_cast<int>(desktop.height * (1.0f - marginPercent));
    layout.blockSize = usableHeight / fieldHeight;
    if (layout.blockSize <= 0) {
        layout.blockSize = 1;
    }

    layout.boardPixelWidth = layout.blockSize * fieldWidth;
    layout.boardPixelHeight = layout.blockSize * fieldHeight;

    layout.offsetX = (desktop.width - layout.boardPixelWidth) / 2;
    layout.offsetY = (desktop.height - layout.boardPixelHeight) / 2;

    layout.holdBoxSize = layout.blockSize * 5;
    layout.holdBoxX = 50;
    layout.holdBoxY = 50;

    layout.queueBoxWidth = layout.blockSize * 5;
    layout.queueBoxHeight = layout.blockSize * 12;
    layout.queueBoxX = static_cast<int>(desktop.width - layout.queueBoxWidth - 50);
    layout.queueBoxY = 50;

    return layout;
}

} // namespace tetris::config
