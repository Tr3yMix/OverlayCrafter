#pragma once
#include <cstdint>

namespace util {


    class Color {

        public:

        Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255);

        explicit Color(std::uint32_t hex);

        int r() const;
        int g() const;
        int b() const;
        int a() const;

    private:
        int m_r, m_g, m_b, m_a;

        static std::uint8_t parseR(const std::uint32_t hex) {
            return hex <= 0xFFF ? (hex >> 8 & 0xF) * 17 :
            hex <= 0xFFFFFF ? hex >> 16 & 0xFF : hex >> 24 & 0xFF;
        }
        static std::uint8_t parseG(const std::uint32_t hex) {
            return hex <= 0xFFF ? (hex >> 4 & 0xF) * 17 :
            hex <= 0xFFFFFF ? hex >> 8 & 0xFF : hex >> 16 & 0xFF;
        }
        static std::uint8_t parseB(const std::uint32_t hex) {
            return hex <= 0xFFF ? (hex & 0xF) * 17 :
            hex <= 0xFFFFFF ? hex & 0xFF : hex >> 8 & 0xFF;
        }
        static std::uint8_t parseA(const std::uint32_t hex) {
            return hex <= 0xFFFFFF ? 255 : hex & 0xFF;
        }

    };

}

