#pragma once
#include <cmath>
#include <iostream>

namespace CW {
    template<typename T>
    class Vector2 {
    public:
        T x, y;

        Vector2() : x(0), y(0) {}
        Vector2(T x, T y) : x(x), y(y) {}
        Vector2(const Vector2& other) : x(other.x), y(other.y) {}

        Vector2& operator=(const Vector2& other) {
            x = other.x;
            y = other.y;
            return *this;
        }

        // Addition
        Vector2 operator+(const Vector2& rhs) const {
            return Vector2(x + rhs.x, y + rhs.y);
        }
        Vector2& operator+=(const Vector2& rhs) {
            x += rhs.x; y += rhs.y;
            return *this;
        }

        // Subtraction
        Vector2 operator-(const Vector2& rhs) const {
            return Vector2(x - rhs.x, y - rhs.y);
        }
        Vector2& operator-=(const Vector2& rhs) {
            x -= rhs.x; y -= rhs.y;
            return *this;
        }

        // Scalar multiplication
        Vector2 operator*(T scalar) const {
            return Vector2(x * scalar, y * scalar);
        }

        // Scalar division
        Vector2 operator/(T scalar) const {
            return Vector2(x / scalar, y / scalar);
        }

        // Equality
        bool operator==(const Vector2& rhs) const {
            return x == rhs.x && y == rhs.y;
        }
        bool operator!=(const Vector2& rhs) const {
            return !(*this == rhs);
        }

        // Dot product
        T dot(const Vector2& rhs) const {
            return x * rhs.x + y * rhs.y;
        }

        // Cross product (returns scalar in 2D)
        T cross(const Vector2& rhs) const {
            return x * rhs.y - y * rhs.x;
        }

        // Magnitude (length)
        T magnitude() const {
            return std::sqrt(x * x + y * y);
        }

        // Magnitude squared (faster if you don’t need sqrt)
        T magnitudeSquared() const {
            return x * x + y * y;
        }

        // Normalized vector (unit length)
        Vector2 normalized() const {
            T mag = magnitude();
            return (mag == 0) ? Vector2(0, 0) : Vector2(x / mag, y / mag);
        }

        // Direction (angle w.r.t. x-axis)
        T direction() const {
            return std::atan2(y, x);
        }

        // Angle between two vectors
        T angleBetween(const Vector2& other) const {
            T dotProd = this->dot(other);
            T magProd = this->magnitude() * other.magnitude();
            return std::acos(dotProd / magProd);
        }

        // Static constructors
        static Vector2 ones() { return Vector2(1, 1); }
        static Vector2 zeros() { return Vector2(0, 0); }
        static Vector2 up() { return Vector2(0, 1); }

        // Output stream
        friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
            os << "(" << v.x << ", " << v.y << ")";
            return os;
        }
    };

    // Common typedefs
    typedef Vector2<float> vec2f;
    typedef Vector2<int> vec2i;
}
