
#include "core/AppWindow.h"
#include "ui/AppUI.h"
#include "util/Logger.h"


// ReSharper disable once CppParameterMayBeConst
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {

    Logger::init();

    AppWindow window({800, 600}, "OverlayCrafter", hInstance);

    const ui::AppUI ui(&window);

    while (window.isRunning()) {
        window.update();
        ui.draw();
    }

    return 0;


}


