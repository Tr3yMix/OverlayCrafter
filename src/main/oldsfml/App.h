#pragma once

#include "OldWindow.h"
#include "Theme.h"


class App {

public:
    App(const std::string&  title, sf::Vector2<float> windowDimensions, Theme theme);
    App();

    void update() const;

    std::unique_ptr<OldWindow> m_window;
};

