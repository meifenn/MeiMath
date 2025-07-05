#pragma once
#include <iostream>
#include <cmath>
#include "Vector2.hpp"

namespace CW {
    class Matrix4x4 {
    public:
        float m[4][4];

        // Constructors
        Matrix4x4() {
            setZero();
        }

        // Identity Matrix
        static Matrix4x4 identity() {
            Matrix4x4 result;
            for (int i = 0; i < 4; ++i) result.m[i][i] = 1.0f;
            return result;
        }

        // Zero Matrix
        static Matrix4x4 zero() {
            return Matrix4x4();
        }

        // Scalar multiplication
        Matrix4x4 operator*(float scalar) const {
            Matrix4x4 result;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    result.m[i][j] = m[i][j] * scalar;
            return result;
        }

        // Matrix multiplication
        Matrix4x4 operator*(const Matrix4x4& rhs) const {
            Matrix4x4 result;
            for (int row = 0; row < 4; ++row) {
                for (int col = 0; col < 4; ++col) {
                    for (int k = 0; k < 4; ++k) {
                        result.m[row][col] += m[row][k] * rhs.m[k][col];
                    }
                }
            }
            return result;
        }

        // Multiply with 2D vector (assumes z=0, w=1)
        Vector2<float> operator*(const Vector2<float>& v) const {
            float x = m[0][0] * v.x + m[0][1] * v.y + m[0][3];
            float y = m[1][0] * v.x + m[1][1] * v.y + m[1][3];
            return Vector2<float>(x, y);
        }

        // Transpose
        Matrix4x4 transpose() const {
            Matrix4x4 result;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    result.m[i][j] = m[j][i];
            return result;
        }

        // Inverse (limited: assumes only scale/translate/rotate)
        Matrix4x4 inverse() const {
            // Use glm or implement general inverse if needed.
            Matrix4x4 inv = identity();
            // Placeholder - recommend using GLM or Eigen for general inverse
            return inv;
        }

        // Translation
        static Matrix4x4 translate(float tx, float ty, float tz = 0.0f) {
            Matrix4x4 mat = identity();
            mat.m[0][3] = tx;
            mat.m[1][3] = ty;
            mat.m[2][3] = tz;
            return mat;
        }

        // Scaling
        static Matrix4x4 scale(float sx, float sy, float sz = 1.0f) {
            Matrix4x4 mat = identity();
            mat.m[0][0] = sx;
            mat.m[1][1] = sy;
            mat.m[2][2] = sz;
            return mat;
        }

        // Rotation (around Z-axis)
        static Matrix4x4 rotateZ(float angleRad) {
            Matrix4x4 mat = identity();
            float c = std::cos(angleRad);
            float s = std::sin(angleRad);
            mat.m[0][0] = c;
            mat.m[0][1] = -s;
            mat.m[1][0] = s;
            mat.m[1][1] = c;
            return mat;
        }

        // Orthographic Projection
        static Matrix4x4 ortho(float left, float right, float bottom, float top, float near, float far) {
            Matrix4x4 mat = identity();
            mat.m[0][0] = 2.0f / (right - left);
            mat.m[1][1] = 2.0f / (top - bottom);
            mat.m[2][2] = -2.0f / (far - near);
            mat.m[0][3] = -(right + left) / (right - left);
            mat.m[1][3] = -(top + bottom) / (top - bottom);
            mat.m[2][3] = -(far + near) / (far - near);
            return mat;
        }

        // Perspective Projection
        static Matrix4x4 perspective(float fovY, float aspect, float near, float far) {
            Matrix4x4 mat = zero();
            float f = 1.0f / std::tan(fovY / 2.0f);
            mat.m[0][0] = f / aspect;
            mat.m[1][1] = f;
            mat.m[2][2] = (far + near) / (near - far);
            mat.m[2][3] = (2.0f * far * near) / (near - far);
            mat.m[3][2] = -1.0f;
            return mat;
        }

        void setZero() {
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    m[i][j] = 0.0f;
        }

        // Output stream
        friend std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat) {
            for (int i = 0; i < 4; ++i) {
                os << "| ";
                for (int j = 0; j < 4; ++j)
                    os << mat.m[i][j] << " ";
                os << "|\n";
            }
            return os;
        }
    };
}
