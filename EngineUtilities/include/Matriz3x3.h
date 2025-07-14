
#pragma once

#include "EngineMath.h"
#include "Vector3.h" 
#include "Matriz2x2.h"      

namespace EngineUtilities {
  namespace Matriz {

    struct Matriz3x3 {
      float m[3][3]; 

      inline Matriz3x3() {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
      }


      inline Matriz3x3(float c0r0, float c0r1, float c0r2,
        float c1r0, float c1r1, float c1r2,
        float c2r0, float c2r1, float c2r2) {
        m[0][0] = c0r0; m[0][1] = c0r1; m[0][2] = c0r2;
        m[1][0] = c1r0; m[1][1] = c1r1; m[1][2] = c1r2;
        m[2][0] = c2r0; m[2][1] = c2r1; m[2][2] = c2r2;
      }

      inline Matriz3x3& operator=(const Matriz3x3& other) {
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            m[i][j] = other.m[i][j];
          }
        }
        return *this;
      }

      inline bool operator==(const Matriz3x3& other) const {
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            if (!Math::approxEqual(m[i][j], other.m[i][j])) {
              return false;
            }
          }
        }
        return true;
      }

      inline bool operator!=(const Matriz3x3& other) const {
        return !(*this == other);
      }


      inline Matriz3x3 operator+(const Matriz3x3& other) const {
        Matriz3x3 result;
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            result.m[i][j] = m[i][j] + other.m[i][j];
          }
        }
        return result;
      }

      inline Matriz3x3 operator-(const Matriz3x3& other) const {
        Matriz3x3 result;
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            result.m[i][j] = m[i][j] - other.m[i][j];
          }
        }
        return result;
      }

      inline Matriz3x3 operator*(float scalar) const {
        Matriz3x3 result;
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            result.m[i][j] = m[i][j] * scalar;
          }
        }
        return result;
      }


      inline Matriz3x3 operator*(const Matriz3x3& other) const {
        Matriz3x3 result;
        for (int r = 0; r < 3; ++r) { 
          for (int c = 0; c < 3; ++c) {
            result.m[c][r] = m[0][r] * other.m[c][0] +
              m[1][r] * other.m[c][1] +
              m[2][r] * other.m[c][2];
          }
        }
        return result;
      }

      inline Vectors::Vector3 operator*(const Vectors::Vector3& vec) const {
        return Vectors::Vector3(
          m[0][0] * vec.x + m[1][0] * vec.y + m[2][0] * vec.z,
          m[0][1] * vec.x + m[1][1] * vec.y + m[2][1] * vec.z,
          m[0][2] * vec.x + m[1][2] * vec.y + m[2][2] * vec.z
        );
      }


      inline Matriz3x3& operator+=(const Matriz3x3& other) {
        *this = *this + other;
        return *this;
      }


      inline Matriz3x3& operator-=(const Matriz3x3& other) {
        *this = *this - other;
        return *this;
      }

      inline Matriz3x3& operator*=(float scalar) {
        *this = *this * scalar;
        return *this;
      }


      inline Matriz3x3& operator*=(const Matriz3x3& other) {
        *this = *this * other;
        return *this;
      }

      static inline Matriz3x3 Identity() {
        return Matriz3x3(1.0f, 0.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 1.0f);
      }

     
      inline float cofactor(int row, int col) const {
        
        Matriz2x2 submatrix;
        int sub_r = 0, sub_c = 0;
        for (int r = 0; r < 3; ++r) {
          if (r == row) continue;
          sub_c = 0;
          for (int c = 0; c < 3; ++c) {
            if (c == col) continue;
            submatrix.m[sub_c][sub_r] = m[c][r]; 
            sub_c++;
          }
          sub_r++;
        }
        float det_sub = submatrix.determinant();
        return ((row + col) % 2 == 0) ? det_sub : -det_sub;
      }

      
      inline float determinant() const {
        return m[0][0] * cofactor(0, 0) + m[1][0] * cofactor(0, 1) + m[2][0] * cofactor(0, 2);
      }

      
      inline Matriz3x3 transposed() const {
        Matriz3x3 result;
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            result.m[j][i] = m[i][j]; 
          }
        }
        return result;
      }

     
      inline Matriz3x3 adjugate() const {
        Matriz3x3 adj;
        adj.m[0][0] = cofactor(0, 0); adj.m[1][0] = cofactor(0, 1); adj.m[2][0] = cofactor(0, 2);
        adj.m[0][1] = cofactor(1, 0); adj.m[1][1] = cofactor(1, 1); adj.m[2][1] = cofactor(1, 2);
        adj.m[0][2] = cofactor(2, 0); adj.m[1][2] = cofactor(2, 1); adj.m[2][2] = cofactor(2, 2);
        return adj.transposed();
      }


      
      inline Matriz3x3 inverse() const {
        float det = determinant();
        if (Math::abs(det) < Math::EPSILON) {
      
          return Identity();
        }
        Matriz3x3 adj = adjugate();
        return adj * (1.0f / det);
      }

      
      static inline Matriz3x3 RotationX(float angle_rad) {
        float c = Math::cos(angle_rad);
        float s = Math::sin(angle_rad);
        return Matriz3x3(1.0f, 0.0f, 0.0f,
          0.0f, c, s,
          0.0f, -s, c);
      }

      
      static inline Matriz3x3 RotationY(float angle_rad) {
        float c = Math::cos(angle_rad);
        float s = Math::sin(angle_rad);
        return Matriz3x3(c, 0.0f, -s,
          0.0f, 1.0f, 0.0f,
          s, 0.0f, c);
      }

     
      static inline Matriz3x3 RotationZ(float angle_rad) {
        float c = Math::cos(angle_rad);
        float s = Math::sin(angle_rad);
        return Matriz3x3(c, s, 0.0f,
          -s, c, 0.0f,
          0.0f, 0.0f, 1.0f);
      }

      
      static inline Matriz3x3 Scale(float sx, float sy, float sz) {
        return Matriz3x3(sx, 0.0f, 0.0f,
          0.0f, sy, 0.0f,
          0.0f, 0.0f, sz);
      }

     
      static inline Matriz3x3 Scale(const Vectors::Vector3& scaleVec) {
        return Scale(scaleVec.x, scaleVec.y, scaleVec.z);
      }
    };

    inline Matriz3x3 operator*(float scalar, const Matriz3x3& mat) {
      return mat * scalar;
    }

  } 
} 
