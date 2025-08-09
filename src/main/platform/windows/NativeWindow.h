#pragma once
#include <string>
#include <windows.h>

#include "NativeGLContext.h"
#include "math/Uint.h"
#include "math/Vector2.h"

namespace win {

    //window message context
    struct WMC {
        HWND hwnd;
        UINT msg;
        WPARAM wParam;
        LPARAM lParam;
        class NativeWindow* window;

        // ReSharper disable once CppParameterMayBeConst
        WMC(HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam, NativeWindow* window) : hwnd(hwnd), msg(msg), wParam(wParam), lParam(lParam), window(window) {}
    };

    class NativeWindow {
    public:
        NativeWindow(HINSTANCE hinstance, const std::string& title, const math::Vector2u& windowSize);
        ~NativeWindow();

        [[nodiscard]] HDC getDC() const;
        [[nodiscard]] HWND getWindowHandle() const;

        static void processMessages();
        void swapBuffers() const;

        math::Uint m_width, m_height;

        bool m_isRunning;

    private:

        static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        NativeGLContext m_glContext;

        HWND m_hwnd;
        HDC m_hdc;
        HGLRC m_hglrc{};

        void cleanup();




    };

} // win
