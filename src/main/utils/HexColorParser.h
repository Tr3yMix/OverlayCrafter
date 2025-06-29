#pragma once

#include <SFML/Graphics.hpp>

inline sf::Color fromHex(const uint32_t hex) {
    //12 bit
    if(hex <= 0xFFF) {
        const uint8_t r = (hex >> 8 & 0xF) * 17;
        const uint8_t g = (hex >> 4 & 0xF) * 17;
        const uint8_t b = (hex & 0xF) * 17;

        return {r, g, b};
    }

    //24 bit
    if(hex <= 0xFFFFFF) {
        const uint8_t r = hex >> 16 & 0xFF;
        const uint8_t g = hex >> 8 & 0xFF;
        const uint8_t b = hex & 0xFF;

        return {r, g, b};
    }

    //32 bit

    const uint8_t r = hex >> 24 & 0xFF;
    const uint8_t g = hex >> 16 & 0xFF;
    const uint8_t b = hex >> 8 & 0xFF;
    const uint8_t a = hex & 0xFF;

    return {r, g, b, a};

}

