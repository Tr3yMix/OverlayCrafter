#include "App.h"

int main() {
    App overlayCrafter(
        "OverlayCrafter",
        {800, 600},
        {16, 16},
        ColorScheme::Dark()
        );

    while(overlayCrafter.window.isOpen()) {
        overlayCrafter.update();
    }
}
