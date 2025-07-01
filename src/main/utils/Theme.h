#pragma once

#include "SFML/Graphics.hpp"

#include "HexColorParser.h"
#include "core/ResourcePaths.h"

#include <utility>

#include "Logger.h"

struct Colors {
    sf::Color background;
    sf::Color foreground;
    sf::Color button;
    sf::Color highlight;
    sf::Color critical;
    sf::Color text;
};

class Theme {

public:
//fromHex(0x323232)
    explicit Theme(const Colors& colors, sf::Font font): m_colors(colors), m_font(std::move(font)) {}

    static Theme Dark() {
        const Colors colors = { fromHex(0x111), fromHex(0x222), sf::Color::Transparent,
            fromHex(0x666), sf::Color::Red, sf::Color::White};
        return Theme(colors, sf::Font());
    }
    static Theme Light() {
        const Colors colors = {fromHex(0xaaa), fromHex(0xddd), sf::Color::Transparent,
            fromHex(0xeee),sf::Color::Red, fromHex(0x444)};
        return Theme(colors, sf::Font());
    }

    [[nodiscard]] Colors getColors() const {return m_colors;}
    [[nodiscard]] sf::Font getFont() const {return m_font;}

private:
    Colors m_colors;
    sf::Font m_font;

    void loadFont() {
        if(!m_font.openFromFile(ResourcePaths::fontPath / "arial.ttf")) {
            log(Logger::LogType::Error, "Failed to load font file");
        }
    }

};

