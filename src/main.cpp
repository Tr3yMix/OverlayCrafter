#include <SFML/Graphics.hpp>

#include "App.h"
#include "color_utils.h"
#include "ColorScheme.h"

int main() {
    const ColorScheme colorScheme(fromHex(0x333), fromHex(0x555), fromHex(0x666));

    App overlayCrafter(
        "OverlayCrafter",
        sf::Vector2<float>(800, 600),
        sf::Vector2<float>(16, 16),
        colorScheme
        );



    while(overlayCrafter.window.isOpen()) {
        overlayCrafter.update();
    }

}
