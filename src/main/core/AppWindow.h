#pragma once

#include <windows.h>

#include "math/Vector2.h"
#include "ui/Drawable.h"
#include "ui/DrawTarget.h"
#include "util/Color.h"


struct WindowMessage {
    HWND hwnd;
    UINT msg;
    WPARAM wParam;
    LPARAM lParam;

    // ReSharper disable once CppParameterMayBeConst
    WindowMessage(HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) : hwnd(hwnd), msg(msg), wParam(wParam), lParam(lParam) {}
};

class AppWindow final : public ui::DrawTarget{

public:

    AppWindow(math::Vector2u windowSize, LPCSTR title, HINSTANCE hInstance);



    bool m_isRunning;

    void update() const;
    void cleanup() const;

    static void clear(util::Color color);

    void draw(ui::Drawable& drawable) const override;

    HINSTANCE m_hInstance;
    HWND m_hwnd;
    HDC m_hdc;

private:

    void createWindow(LPCSTR title);
    void createOpenGLContext();

    static void processMessages();

    void resizeWindowEvent(const WindowMessage& message);
    static void leftButtonDownEvent(const WindowMessage& message);
    void windowCloseEvent(const WindowMessage& message);


    HGLRC m_hglrc;


    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    LRESULT handleMessages(const WindowMessage &message) noexcept;


    void display() const;


};

