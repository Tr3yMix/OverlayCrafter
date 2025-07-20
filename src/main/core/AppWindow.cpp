#include "AppWindow.h"

#include <GL/gl.h>

#include "ui/Drawable.h"
#include "ui/RectanglePrimitive.h"
#include "ui/Text.h"
#include "util/Color.h"

// ReSharper disable once CppParameterMayBeConst
AppWindow::AppWindow(const math::Vector2u windowSize, const LPCSTR title, HINSTANCE hInstance) :
m_isRunning(true), m_hInstance(hInstance), m_hwnd(nullptr), m_hdc(nullptr), m_hglrc(nullptr)
 {

    m_width = windowSize.signedX();
    m_height = windowSize.signedY();

    createWindow(title);
    createOpenGLContext();
}

void AppWindow::createWindow(const LPCSTR title) {

    WNDCLASSEX wc = {};

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = "OpenGLWindowClass";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = nullptr;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    if (!RegisterClassExA(&wc)) throw std::runtime_error("Failed to register window class.");

    m_hwnd = CreateWindowEx(0, wc.lpszClassName, title, WS_POPUP, CW_USEDEFAULT,
        CW_USEDEFAULT, m_width, m_height, nullptr, nullptr, m_hInstance, this);
    if (!m_hwnd) throw std::runtime_error("Failed to create window.");

    m_hdc = GetDC(m_hwnd);
    if (!m_hdc) throw std::runtime_error("Failed to get device context.");

    ShowWindow(m_hwnd, SW_SHOW);
    UpdateWindow(m_hwnd);

}


// ReSharper disable once CppParameterMayBeConst
LRESULT AppWindow::WndProc(HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) {
    AppWindow* instance = nullptr;

    switch (msg) {
        case WM_NCCREATE: {
            const auto* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
            instance = static_cast<AppWindow*>(createStruct->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(instance));
            break;
        }
        default:
            instance = reinterpret_cast<AppWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
            break;
    }


    if(instance) {
        return instance->handleMessages(WindowMessage(hWnd, msg, wParam, lParam));
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);

}

// ReSharper disable once CppDFAUnreachableFunctionCall
// ReSharper disable once CppParameterMayBeConst
LRESULT AppWindow::handleMessages(const WindowMessage &message) noexcept {
    switch (message.msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(message.hwnd, &ps);
            EndPaint(message.hwnd, &ps);
            break;
        }
        case WM_SIZE: {
            resizeWindowEvent(message);
            break;
        }
        case WM_LBUTTONDOWN: {
            leftButtonDownEvent(message);
            break;
        }
        case WM_CLOSE: {
            windowCloseEvent(message);
            break;
        }
        case WM_DESTROY: break;
        default: return DefWindowProc(message.hwnd, message.msg, message.wParam, message.lParam);
    }
    return 0;
}

void AppWindow::createOpenGLContext() {

    constexpr PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0,0,0,0,0,0,
        0,
        0,
        0,
        0,0,0,0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,0,0,0
    };

    const int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
    if (pixelFormat == 0) {
        Logger::error("Failed to choose pixel format.");
        return;
    }

    if (!SetPixelFormat(m_hdc, pixelFormat, &pfd)) {
        Logger::error("Failed to set pixel format.");
        return;
    }

    m_hglrc = wglCreateContext(m_hdc);
    if (!m_hglrc) {
        Logger::error("Failed to create OpenGL context.");
        return;
    }
    if (!wglMakeCurrent(m_hdc, m_hglrc)) {
        Logger::error("Failed to make OpenGL context current.");
        return;
    }
    Logger::info("OpenGL context created successfully.");
}

void AppWindow::processMessages() {
    MSG msg = {};

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// ReSharper disable once CppDFAUnreachableFunctionCall
void AppWindow::resizeWindowEvent(const WindowMessage& message) {
    m_width = LOWORD(message.lParam);
    m_height = HIWORD(message.lParam);
    glViewport(0, 0, m_width, m_height);
}

// ReSharper disable once CppDFAUnreachableFunctionCall
void AppWindow::leftButtonDownEvent(const WindowMessage& message) {
    const int yPos = HIWORD(message.lParam);
    if (yPos <= 40) {
        ReleaseCapture();
        SendMessage(message.hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
    }
}

// ReSharper disable once CppDFAUnreachableFunctionCall
void AppWindow::windowCloseEvent(const WindowMessage& message) {
    m_isRunning = false;
    PostQuitMessage(0);
}

void AppWindow::clear(const util::Color color) {

        const GLclampf r = color.rF();
        const GLclampf g = color.gF();
        const GLclampf b = color.bF();
        const GLclampf a = color.aF();

        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void AppWindow::draw(ui::Drawable& drawable) const {
        drawable.draw(*this);
    }


    void AppWindow::display() const {
        SwapBuffers(m_hdc);
    }

    void AppWindow::update() const {
        processMessages();
        display();
    }

    void AppWindow::cleanup() const {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(m_hglrc);
        ReleaseDC(m_hwnd, m_hdc);
        DestroyWindow(m_hwnd);

        ui::Text::CleanupFont();
    }



