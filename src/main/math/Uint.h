#pragma once
#include <iostream>


namespace math {

    struct Uint{

        unsigned int value;

        constexpr Uint(): value(0) {}

        constexpr explicit Uint(const unsigned int value) : value(value) {}
        constexpr explicit Uint(const signed int value) : value(value < 0 ? 0 : static_cast<unsigned int>(value)) {}

        [[nodiscard]]constexpr signed int signedInt() const {return static_cast<signed int>(value);}


        // ReSharper disable once CppNonExplicitConversionOperator
        constexpr operator unsigned int() const {return value;}

        // ReSharper disable once CppNonExplicitConversionOperator
        constexpr operator signed int() const {return static_cast<signed int>(value);}



        template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
        // ReSharper disable once CppNonExplicitConvertingConstructor
        Uint(T v) : value(v < 0 ? 0u : static_cast<unsigned int>(v)) {}



        static constexpr unsigned int clampToUint(const long long value) {
            if (value < 0) return 0;
            if (value > UINT_MAX) return UINT_MAX;
            return static_cast<unsigned int>(value);
        }

        // Comparison
        bool operator==(const Uint& other) const {return value == other.value;}
        bool operator!=(const Uint& other) const { return value != other.value; }
        bool operator<(const Uint& other) const { return value < other.value; }
        bool operator<=(const Uint& other) const { return value <= other.value; }
        bool operator>(const Uint& other) const { return value > other.value; }
        bool operator>=(const Uint& other) const { return value >= other.value; }

        // Arithmetic
        friend constexpr Uint operator+(const Uint& a, const Uint& b) {
            const unsigned long long sum = a.value + b.value;
            return Uint(sum > UINT_MAX ? UINT_MAX : static_cast<unsigned int>(sum));
        }
        friend constexpr Uint operator-(const Uint& a, const Uint& b) {
            if (b > a) return Uint(0); return Uint(a.value - b.value);
        }
        friend constexpr Uint operator*(const Uint& a, const Uint& b) {
            const unsigned long long product = a.value * b.value;
            return Uint(product > UINT_MAX ? UINT_MAX : static_cast<unsigned int>(product));
        }
        friend constexpr Uint operator/(const Uint& a, const Uint& b) {
            if (b.value == 0) throw std::runtime_error("Division by zero");
            return Uint(a.value / b.value);
        }
        friend constexpr Uint operator%(const Uint& a, const Uint& b) {
            if (b.value == 0) throw std::runtime_error("Mod by zero");
            return Uint(a.value % b.value);
        }

        // Compound assignment
        Uint& operator+=(const Uint& other) {
            const unsigned long long sum = value + other.value;
            value = sum > UINT_MAX ? UINT_MAX : static_cast<unsigned int>(sum);
            return *this;
        }
        Uint& operator-=(const Uint& other) {
            value = other.value > value ? 0 : value - other.value;
            return *this;
        }
        Uint& operator*=(const Uint& other) {
            const unsigned long long product = value * other.value;
            value = product > UINT_MAX ? UINT_MAX : static_cast<unsigned int>(product);
            return *this;
        }
        Uint& operator/=(const Uint& other) {
            if (other.value == 0) throw std::runtime_error("Division by zero");
            value /= other.value;
            return *this;
        }
        Uint& operator%=(const Uint& other) {
            if (other.value == 0) throw std::runtime_error("Mod by zero");
            value %= other.value;
            return *this;
        }

        // Increment / Decrement
        constexpr Uint& operator++() {
            if (value != UINT_MAX) ++value;
            return *this;
        }
        constexpr Uint operator++(int) {
            const Uint tmp = *this;
            if (value != UINT_MAX) ++value;
            return tmp;
        }
        constexpr Uint& operator--() {
            if (value > 0) --value;
            return *this;
        }
        constexpr Uint operator--(int) { const Uint tmp = *this;
            if (value > 0) --value;
            return tmp;
        }

        // Bitwise
        friend constexpr Uint operator&(const Uint& a, const Uint& b) { return Uint(a.value & b.value); }
        friend constexpr Uint operator|(const Uint& a, const Uint& b) { return Uint(a.value | b.value); }
        friend constexpr Uint operator^(const Uint& a, const Uint& b) { return Uint(a.value ^ b.value); }
        Uint& operator&=(const Uint& other) { value &= other.value; return *this; }
        Uint& operator|=(const Uint& other) { value |= other.value; return *this; }
        Uint& operator^=(const Uint& other) { value ^= other.value; return *this; }

        // Shift
        friend constexpr Uint operator<<(const Uint& a, const unsigned int shift) { return Uint(a.value << shift); }
        friend constexpr Uint operator>>(const Uint& a, const unsigned int shift) { return Uint(a.value >> shift); }
        Uint& operator<<=(const unsigned int shift) { value <<= shift; return *this; }
        Uint& operator>>=(const unsigned int shift) { value >>= shift; return *this; }

        // Stream output
        friend std::ostream& operator<<(std::ostream& os, const Uint& u) {
            return os << u.value;
        }
    };


}
