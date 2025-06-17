#include <SFML/Graphics.hpp>

#include "App.h"
#include "ColorScheme.h"

int main() {

    App overlayCrafter(
        "OverlayCrafter",
        sf::Vector2<float>(800, 600),
        sf::Vector2<float>(16, 16),
        ColorScheme::Dark()
        );



    while(overlayCrafter.window.isOpen()) {
        overlayCrafter.update();
    }

}
