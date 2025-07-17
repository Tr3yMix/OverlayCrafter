#include "core/App.h"
#include "core/AppWindow.h"



// ReSharper disable once CppParameterMayBeConst
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    AppWindow window;

    window.m_hInstance = hInstance;

    window.createWindow(800, 600, reinterpret_cast<LPCSTR>("My OpenGL Window"));
    window.createOpenGLContext();
    ShowWindow(window.m_hwnd, SW_SHOW);

    window.messageLoop();
    window.cleanup();

    return 0;


}



/*

int main() {

    Logger::init();

    std::string version = "0.1a";

    logf(Logger::LogType::Info, "Starting OverlayCrafter {}", version);

    const App overlayCrafter(
        "OverlayCrafter",
        {1440, 810},
        Theme::Dark()
        );



    while(overlayCrafter.m_window->getWindow()->isOpen()) {
        overlayCrafter.update();
    }
}
*/


