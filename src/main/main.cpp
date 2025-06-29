#include "core/App.h"

int main() {
    App overlayCrafter(
        "OverlayCrafter",
        {800, 600},
        {16, 16},
        Theme::Dark()
        );

    while(overlayCrafter.m_window.isOpen()) {
        overlayCrafter.update();
    }
}
