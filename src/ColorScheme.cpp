
#include "ColorScheme.h"

ColorScheme::ColorScheme(const sf::Color backgroundColor, const sf::Color foregroundColor, const sf::Color buttonColor) {
    this->backgroundColor = backgroundColor;
    this->foregroundColor = foregroundColor;
    this->buttonColor = buttonColor;
}
ColorScheme::ColorScheme(): ColorScheme(sf::Color::Black, sf::Color::White, sf::Color(50, 50, 50)) {

}

