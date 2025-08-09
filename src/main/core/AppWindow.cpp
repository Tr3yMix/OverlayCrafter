#include "AppWindow.h"

#include "../platform/windows/NativeEventHandler.h"
#include "ui/Drawable.h"
#include "ui/RectanglePrimitive.h"
#include "ui/Text.h"

// ReSharper disable once CppParameterMayBeConst
AppWindow::AppWindow(const math::Vector2u windowSize, const LPCSTR title, HINSTANCE hInstance){

    m_nativeWindow = std::make_unique<win::NativeWindow>(hInstance, title, windowSize);

    m_width = windowSize.signedX();
    m_height = windowSize.signedY();
}

void AppWindow::draw(ui::Drawable& drawable) const {
    drawable.draw(*this);
}

void AppWindow::update() const {
    m_nativeWindow->processMessages();
    m_nativeWindow->swapBuffers();
}

HDC AppWindow::getDC() const {
    return m_nativeWindow->getDC();
}

bool AppWindow::isRunning() const {
    return m_nativeWindow->m_isRunning;
}
