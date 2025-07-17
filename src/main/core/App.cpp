#include "App.h"

App::App(const std::string& title, const sf::Vector2<float> windowDimensions, Theme theme){

    m_window = std::make_unique<OldWindow>(title, sf::Vector2u(windowDimensions), theme);

}

App::App(): App("App", sf::Vector2f(800, 600), Theme::Light()){}



void App::update() const {
    m_window->update();
    m_window->handleEvents();
    m_window->clear();
    m_window->draw();
    m_window->display();

}




