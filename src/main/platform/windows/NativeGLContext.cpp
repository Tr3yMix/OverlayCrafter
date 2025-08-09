
#include "NativeGLContext.h"

#include <GL/gl.h>

#include "util/Logger.h"

namespace win {
    NativeGLContext::NativeGLContext()= default;

    NativeGLContext::~NativeGLContext() {
        cleanup();
    }

    // ReSharper disable once CppParameterMayBeConst
    bool NativeGLContext::initialize(HDC hdc) {
        m_hdc = hdc;

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
            return false;
        }

        if (!SetPixelFormat(m_hdc, pixelFormat, &pfd)) {
            Logger::error("Failed to set pixel format.");
            return false;
        }

        m_hglrc = wglCreateContext(m_hdc);
        if (!m_hglrc) {
            Logger::error("Failed to create OpenGL context.");
            return false;
        }
        if (!wglMakeCurrent(m_hdc, m_hglrc)) {
            Logger::error("Failed to make OpenGL context current.");
            return false;
        }

        Logger::info("OpenGL context created successfully.");

        return true;
    }

    void NativeGLContext::makeCurrent() const {
        if (m_hdc && m_hglrc) {
            wglMakeCurrent(m_hdc, m_hglrc);
        }
    }

    void NativeGLContext::cleanup() {

        if (m_hglrc) {
            wglMakeCurrent(nullptr, nullptr);
            wglDeleteContext(m_hglrc);
            m_hglrc = nullptr;
        }
        m_hdc = nullptr;
    }

    void NativeGLContext::swapBuffers() const {
        SwapBuffers(m_hdc);
    }
}




