
#include "ColorScheme.h"

#include "color_utils.h"

ColorScheme::ColorScheme(const sf::Color backgroundColor, const sf::Color foregroundColor, const sf::Color buttonColor, const sf::Color textColor) :
    backgroundColor(backgroundColor), foregroundColor(foregroundColor), buttonColor(buttonColor), textColor(textColor){}

ColorScheme ColorScheme::Dark() {
    return {fromHex(0x333), fromHex(0x555), fromHex(0x666), sf::Color::White};
}

ColorScheme ColorScheme::Light() {
    return {fromHex(0xfff), fromHex(0xccc), fromHex(0xddd), sf::Color::Black};
}


