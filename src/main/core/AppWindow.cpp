#include "AppWindow.h"

#include <vector>

#include "ui/Drawable.h"
#include "ui/RectanglePrimitive.h"
#include "utils/Color.h"

void AppWindow::createWindow(const int width, const int height, const LPCSTR title) {
    WNDCLASS wc = {};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = reinterpret_cast<LPCSTR>("OpenGLWindowClass");
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClass(&wc);

    m_hwnd = CreateWindowEx(0, wc.lpszClassName, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, width, height, nullptr, nullptr, m_hInstance, this);

    m_hdc = GetDC(m_hwnd);
}

// ReSharper disable once CppParameterMayBeConst
LRESULT AppWindow::WndProc(HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) {

    AppWindow* instance = nullptr;

    if(msg == WM_NCCREATE) {
        const auto* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
        instance = static_cast<AppWindow*>(createStruct->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(instance));
    }else {
        instance = reinterpret_cast<AppWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if(instance) {
        return instance->handleMessage(hWnd, msg, wParam, lParam);
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);

}

// ReSharper disable once CppDFAUnreachableFunctionCall
// ReSharper disable once CppParameterMayBeConst
LRESULT AppWindow::handleMessage(HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE:
            running = false;
        PostQuitMessage(0);
        return 0;
        case WM_DESTROY:
            return 0;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

void AppWindow::createOpenGLContext() {
    constexpr PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0,0,0,0,0,0,
        0,0,0,0,0,0,0,
        24, 8, 0,
        PFD_MAIN_PLANE,
        0,0,0,0
    };

    const int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
    SetPixelFormat(m_hdc, pixelFormat, &pfd);

    m_hglrc = wglCreateContext(m_hdc);
    wglMakeCurrent(m_hdc, m_hglrc);
}

void AppWindow::clear(const util::Color color) {

    const auto red = static_cast<GLclampf>(color.r());
    const auto green = static_cast<GLclampf>(color.g());
    const auto blue = static_cast<GLclampf>(color.b());
    const auto alpha = static_cast<GLclampf>(color.a());


    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void AppWindow::draw(const ui::Drawable& drawable) const {

    const util::Color color(0xffffffff);

    clear(color);

    drawable.draw();

    SwapBuffers(m_hdc);
}




void AppWindow::messageLoop() const {
    MSG msg = {};
    while (running) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        ui::RectanglePrimitive rect(-1, 1, 1, -1);

        rect.setColor(1, 1, 1, 1);

        draw(rect);
    }
}

void AppWindow::cleanup() const {
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(m_hglrc);
    ReleaseDC(m_hwnd, m_hdc);
    DestroyWindow(m_hwnd);
}




