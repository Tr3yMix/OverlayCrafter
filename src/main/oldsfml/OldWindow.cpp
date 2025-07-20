
#include "OldWindow.h"
#include "AppUI.h"


OldWindow::OldWindow(const std::string& title, const sf::Vector2u size, const Theme& theme): m_initWindowSize(size), m_theme(theme) {

    //Init Window
    m_window.create(sf::VideoMode(m_initWindowSize), title, sf::Style::None);


    if(sf::Image icon; icon.loadFromFile(ResourcePaths::imagePath / "logo_256x256.png")) {
        m_window.setIcon(icon);
    }else{ log(Logger::LogType::Error, "Failed to load icon image"); }

    //Init Views
    auto defLeftRect = sf::FloatRect({0, 0}, sf::Vector2<float>(m_initWindowSize));

    m_mainView = std::make_unique<sf::View>(defLeftRect);
    m_window.setView(*m_mainView);

    m_titleBarStretchedView = std::make_unique<sf::View>(defLeftRect);
    m_titleBarLeftView = std::make_unique<sf::View>(defLeftRect);


    m_titleBarRightView = std::make_unique<sf::View>(defLeftRect);

    updateTitleBarRightView(m_initWindowSize.x, m_initWindowSize.y);

    m_appUI = std::make_unique<AppUI>(*this, sf::Vector2f(16, 16), theme);


    m_hwnd = m_window.getNativeHandle();


    m_fileDropHandler = std::make_unique<FileDropHandler>(m_hwnd);
    m_fileDropHandler->setOnDropCallback([this](const std::string& path)
        {
            if(!m_appUI->m_texture.loadFromFile(path)) {
            log(Logger::LogType::Error, "Failed to load dropped image");
            }
        }
        );
}

void OldWindow::handleEvents() {
    while(const std::optional<sf::Event> event = this->m_window.pollEvent()) {

        if(event->is<sf::Event::Closed>()) {
            m_window.close();
        }
        else if(const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if(key->scancode == sf::Keyboard::Scancode::Escape) {
                m_window.close();
            }
        }else if(const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if(mousePressed->button == sf::Mouse::Button::Left) {

                if(isResizableArea()) {
                    m_isResizing = true;
                    GetCursorPos(&m_initResizeMousePos);
                    m_initResizeWindowSize = m_window.getSize();
                }else {
                    m_isDragging = isDraggable(*m_appUI);
                }
            }
        }else if(const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            if(mouseReleased->button == sf::Mouse::Button::Left) {
                m_isDragging = false;
                m_isResizing = false;
            }
        }else if(event->is<sf::Event::MouseMoved>()) {

            if(m_isDragging) {
                dragWindow();
            }else if(m_isResizing) {
                resizeWindow();
            }
        }

        m_appUI->m_menuBar->handleButtonEvents(event, m_window, *m_titleBarLeftView);
        m_appUI->m_exitButton->handleEvent(event, m_window, *m_titleBarRightView);
        m_appUI->m_maxButton->handleEvent(event, m_window, *m_titleBarRightView);
        m_appUI->m_minButton->handleEvent(event, m_window, *m_titleBarRightView);

    }
}
void OldWindow::updateCursor() const {

    switch(m_resizeDirection) {
        case ResizeDirection::Diagonal : SetCursor(LoadCursor(nullptr, IDC_SIZENWSE)); break;
        case ResizeDirection::Horizontal : SetCursor(LoadCursor(nullptr, IDC_SIZEWE)); break;
        case ResizeDirection::Vertical : SetCursor(LoadCursor(nullptr, IDC_SIZENS)); break;
        case ResizeDirection::None : SetCursor(LoadCursor(nullptr, IDC_ARROW)); break;
    }

}

void OldWindow::update() const {
    if(m_isResizing || m_isDragging) return;

    if(isResizableArea()) {
        updateCursor();
    }


}

void OldWindow::clear() {
    m_window.clear(m_theme.getColors().background);
}

void OldWindow::draw() {

    m_window.setView(*m_mainView);
    m_window.draw(*m_appUI->m_sprite);

    m_appUI->m_menuBar->draw(m_window, *m_titleBarStretchedView, *m_titleBarLeftView);

    m_window.setView(*m_titleBarRightView);
    m_appUI->m_exitButton->draw(m_window);
    m_appUI->m_maxButton->draw(m_window);
    m_appUI->m_minButton->draw(m_window);

}

void OldWindow::display() {
    m_window.display();
}

sf::RenderWindow* OldWindow::getWindow() {
    return &m_window;
}

// === Window Dragging ===

bool OldWindow::isDraggable(const AppUI& ui){
    if(!GetCursorPos(&m_initMousePos)) return false;

    RECT rect;
    if(!GetWindowRect(m_hwnd, &rect)) return false;

    m_initWindowPos.x = rect.left;
    m_initWindowPos.y = rect.top;
    if(m_initMousePos.y < rect.top || m_initMousePos.y > rect.top + 40) return false;

    POINT clientPoint = m_initMousePos;
    ScreenToClient(m_hwnd, &clientPoint);
    const sf::Vector2i localMouse(clientPoint.x, clientPoint.y);

    if(const sf::Vector2f worldMouse = m_window.mapPixelToCoords(localMouse, *m_titleBarLeftView);
        ui.m_menuBar->isMouseOverElement(worldMouse) ) return false;

    if(const sf::Vector2f worldMouse = m_window.mapPixelToCoords(localMouse, *m_titleBarRightView);
        ui.m_exitButton->getBounds().contains(worldMouse) ||
        ui.m_maxButton->getBounds().contains(worldMouse) ||
        ui.m_minButton->getBounds().contains(worldMouse)) return false;

    return true;
}

void OldWindow::dragWindow() {
    if(m_isFullScreen) {
        SetWindowLong(m_hwnd, GWL_STYLE, m_prevWindowStyle);
        SetWindowPos(m_hwnd, HWND_TOP,
            100, 100,
            static_cast<int>(m_prevWindowSize.x), static_cast<int>(m_prevWindowSize.y),
            SWP_NOZORDER | SWP_FRAMECHANGED);

        updateViewports(static_cast<int>(m_prevWindowSize.x), static_cast<int>(m_prevWindowSize.y));
        m_isFullScreen = false;
    }

    POINT currentMousePos;
    if(GetCursorPos(&currentMousePos)) {
        const int dx = currentMousePos.x - m_initMousePos.x;
        const int dy = currentMousePos.y - m_initMousePos.y;

        SetWindowPos(
            m_hwnd,
            nullptr,
            m_initWindowPos.x + dx,
            m_initWindowPos.y + dy,
            0, 0,
            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
}

// === Resize Handling ===

bool OldWindow::isResizableArea() const {


    POINT mouse;
    if(!GetCursorPos(&mouse)) return false;

    RECT rect;
    if(!GetWindowRect(m_hwnd, &rect)) return false;

    const int mx = mouse.x;
    const int my = mouse.y;

    constexpr int edgeSize = 10;

    if(mouse.y <= 40L) return false;

    const bool nearRight = mx >= rect.right - edgeSize && mx <= rect.right;
    const bool nearLeft = mx >= rect.left && mx <= rect.left + edgeSize;
    const bool nearBottom = my >= rect.bottom - edgeSize && my <= rect.bottom;

    const bool nearSide = nearRight || nearLeft;

    if(nearSide && nearBottom) {
        m_resizeDirection = ResizeDirection::Diagonal;
        return true;
    }
    if(nearSide) {
        m_resizeDirection = ResizeDirection::Horizontal;
        return true;
    }
    if(nearBottom) {
        m_resizeDirection = ResizeDirection::Vertical;
        return true;
    }
    m_resizeDirection = ResizeDirection::None;
    return false;
}

void OldWindow::resizeWindow() const {

    POINT currentMousePos;
    if(!GetCursorPos(&currentMousePos)) return;

    const int dx = currentMousePos.x - m_initResizeMousePos.x;
    const int dy = currentMousePos.y - m_initResizeMousePos.y;

    int width = static_cast<int>(m_initResizeWindowSize.x);
    int height = static_cast<int>(m_initResizeWindowSize.y);

    switch(m_resizeDirection) {
        case ResizeDirection::Horizontal : width += dx; break;
        case ResizeDirection::Vertical : height += dy; break;
        case ResizeDirection::Diagonal : width += dx; height += dy; break;
        case ResizeDirection::None : logf(Logger::LogType::Error, "Resize Direction is set to none while resizing"); break;
    }

    const auto minLeftWidth = static_cast<unsigned int>(m_appUI->m_menuBar->getButtonsWidth());
    constexpr unsigned int minRightWidth = 40 * 3;
    constexpr unsigned int padding = 20;

    const int minWidth = static_cast<int>(minLeftWidth + padding + minRightWidth);

    width = width >= minWidth ? width : minWidth;
    height = height >= 100 ? height : 100;

    updateCursor();

    SetWindowPos(m_hwnd,
            nullptr,
            0, 0,
            width, height,
            SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

    updateViewports(width, height);


}

void OldWindow::updateViewports(const unsigned int width, const unsigned int height) const {


    updateMainView(width, height);
    updateTitleBarLeftView(width, height);
    updateTitleBarRightView(width, height);
    updateTitleBarStretchedView(width, height);
}

void OldWindow::updateMainView(const unsigned int width, const unsigned int height) const {
    const float windowAspect = static_cast<float>(width) / static_cast<float>(height);
    const float viewAspect = m_mainView->getSize().x / m_mainView->getSize().y;

    float sizeX = 1.f;
    float sizeY = 1.f;
    float posX = 0.f;
    float posY = 0.f;

    if(windowAspect > viewAspect) {
        sizeX = viewAspect / windowAspect;
        posX = (1.f - sizeX) / 2.f;
    }else {
        sizeY = windowAspect / viewAspect;
        posY = (1.f - sizeY) / 2.f;
    }

    m_mainView->setViewport(sf::FloatRect({posX, posY}, {sizeX, sizeY}));
}

void OldWindow::updateTitleBarStretchedView(const unsigned int width, const unsigned int height) const {
    const auto viewWidth = static_cast<float>(width);
    constexpr unsigned int viewHeight = 40;

    m_titleBarStretchedView->setSize({viewWidth, static_cast<float>(viewHeight)});
    m_titleBarStretchedView->setCenter({viewWidth / 2.f, viewHeight / 2.f});


    float viewportHeight = static_cast<float>(viewHeight) / static_cast<float>(height);

    m_appUI->m_menuBar->resize({width, viewHeight});

    m_titleBarStretchedView->setViewport(sf::FloatRect({0, 0}, {1.f, viewportHeight}));
}

void OldWindow::updateTitleBarLeftView(const unsigned int width, const unsigned int height) const {


    const auto viewWidth = static_cast<unsigned int>(m_appUI->m_menuBar->getButtonsWidth());
    constexpr unsigned int viewHeight = 40;

    m_titleBarLeftView->setSize({static_cast<float>(viewWidth), static_cast<float>(viewHeight)});
    m_titleBarLeftView->setCenter({static_cast<float>(viewWidth) / 2.f, viewHeight / 2.f});

    float viewportWidth = static_cast<float>(viewWidth) / static_cast<float>(width);
    float viewportHeight = static_cast<float>(viewHeight) / static_cast<float>(height);



    m_titleBarLeftView->setViewport(sf::FloatRect({0, 0}, {viewportWidth, viewportHeight}));
}

void OldWindow::updateTitleBarRightView(const unsigned int width, const unsigned int height) const {

    constexpr unsigned int viewWidth = 40 * 3;
    constexpr unsigned int viewHeight = 40;

    m_titleBarRightView->setSize({static_cast<float>(viewWidth), static_cast<float>(viewHeight)});
    m_titleBarRightView->setCenter({static_cast<float>(viewWidth) / 2.f, viewHeight / 2.f});

    float viewportWidth = static_cast<float>(viewWidth) / static_cast<float>(width);
    float viewportHeight = static_cast<float>(viewHeight) / static_cast<float>(height);


    m_titleBarRightView->setViewport(sf::FloatRect({1.f - viewportWidth, 0}, {viewportWidth, viewportHeight}));
}



void OldWindow::minimizeWindow() const {

    ShowWindow(m_hwnd, SW_MINIMIZE);
}

void OldWindow::maximizeWindow(){


    if(!m_isFullScreen) {
        m_prevWindowSize = m_window.getSize();
        m_prevWindowStyle = GetWindowLong(m_hwnd, GWL_STYLE);

        MONITORINFO monitorInfo = { sizeof(MONITORINFO)};
        if(GetMonitorInfo(MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTONEAREST), &monitorInfo)) {
            const auto&[left, top, right, bottom] = monitorInfo.rcMonitor;

            SetWindowLong(m_hwnd, GWL_STYLE, m_prevWindowStyle & ~WS_OVERLAPPEDWINDOW);
            SetWindowPos(m_hwnd, HWND_TOP,
                left, top, right - left, bottom - top,
                SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

            m_isFullScreen = true;
            updateViewports(right - left, bottom - top);
        }

    }else {
        SetWindowLong(m_hwnd, GWL_STYLE, m_prevWindowStyle);
        SetWindowPos(m_hwnd, HWND_TOP,
            100, 100,
            static_cast<int>(m_prevWindowSize.x), static_cast<int>(m_prevWindowSize.y),
            SWP_NOZORDER | SWP_FRAMECHANGED);

        m_isFullScreen = false;
        updateViewports(static_cast<int>(m_prevWindowSize.x), static_cast<int>(m_prevWindowSize.y));
    }

}

