#pragma once

#include "OldButton.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "Theme.h"

enum class MenuType {Horizontal, Vertical, DropDown};

class ButtonBar {

public:
    ButtonBar(MenuType type,const sf::Vector2u& size, Colors colors ,sf::Font font);

    void addButton(const std::string& text, const std::function<void()>& onClick);
    void draw(sf::RenderWindow& window, const sf::View& topView, const sf::View& leftView) const;
    void handleButtonEvents(const std::optional<sf::Event>& event, const sf::RenderWindow& window, const sf::View& view);
    bool isMouseOverElement(const sf::Vector2f& mouse) const;
    void resize(const sf::Vector2u& size);
    float getButtonsWidth() const;

private:

    MenuType m_type;
    sf::Vector2u m_size;
    Colors m_colors;
    sf::RectangleShape m_background;
    std::vector<std::unique_ptr<OldButton>> m_buttons;
    sf::Font m_font;

    float m_buttonWidth = 50.f;
    float m_buttonHeight = 40.f;
    float m_padding = 1.f;
};
