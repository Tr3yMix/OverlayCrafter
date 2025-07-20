#pragma once


#include "SFML/Graphics/RenderWindow.hpp"
#include <windows.h>

#include "FileDropHandler.h"
#include "AppUI.h"
#include "Theme.h"

enum class ResizeDirection { None, Horizontal, Vertical, Diagonal };

class OldWindow {


public:
    OldWindow(const std::string& title, sf::Vector2u size, const Theme& theme);
    void handleEvents();
    void update() const;
    void clear();
    void draw();
    void display();

    sf::RenderWindow* getWindow();

    HWND m_hwnd;

    std::unique_ptr<AppUI> m_appUI;

    std::unique_ptr<sf::View> m_mainView;

    void updateCursor() const;

    void minimizeWindow() const;
    void maximizeWindow();

private:

    mutable ResizeDirection m_resizeDirection = ResizeDirection::None;

    sf::RenderWindow m_window;
    sf::Vector2u m_initWindowSize;

    Theme m_theme;



    std::unique_ptr<sf::View> m_titleBarStretchedView;
    std::unique_ptr<sf::View> m_bottomView;
    std::unique_ptr<sf::View> m_titleBarLeftView;
    std::unique_ptr<sf::View> m_titleBarRightView;


    std::unique_ptr<FileDropHandler> m_fileDropHandler;

    //dragging logic

    bool m_isDragging = false;
    POINT m_initMousePos{};
    POINT m_initWindowPos{};

    bool isDraggable(const AppUI& ui);
    void dragWindow();

    //resize logic

    bool m_isResizing = false;
    POINT m_initResizeMousePos{};
    sf::Vector2u m_initResizeWindowSize;

    bool isResizableArea() const;
    void resizeWindow() const;

    void updateViewports(unsigned int width, unsigned int height) const;

    void updateMainView(unsigned int width, unsigned int height) const;
    void updateTitleBarStretchedView(unsigned int width, unsigned int height) const;
    void updateTitleBarLeftView(unsigned int width, unsigned int height) const;
    void updateTitleBarRightView(unsigned int width, unsigned int height) const;

    bool m_isFullScreen = false;
    sf::Vector2u m_prevWindowSize;
    LONG m_prevWindowStyle = 0;



};

