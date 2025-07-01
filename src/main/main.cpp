#include "core/App.h"

int main() {

    Logger::init();

    std::string version = "0.1a";

    logf(Logger::LogType::Info, "Starting OverlayCrafter {}", version);

    App overlayCrafter(
        "OverlayCrafter",
        {1440, 810},
        {16, 16},
        Theme::Dark()
        );

    while(overlayCrafter.m_window.isOpen()) {
        overlayCrafter.update();
    }
}
