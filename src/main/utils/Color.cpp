#include "Color.h"


namespace util {
    Color::Color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a): m_r(r), m_g(g), m_b(b), m_a(a) {}

    Color::Color(const std::uint32_t hex) :
    Color(parseR(hex), parseG(hex), parseB(hex), parseA(hex)){}

    int Color::r() const {
        return m_r;
    }
    int Color::g() const {
        return m_g;
    }
    int Color::b() const {
        return m_b;
    }
    int Color::a() const {
        return m_a;
    }


}
