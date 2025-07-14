
#pragma once

#include "EngineMath.h"
#include "Vector3.h" 
#include "Matriz2x2.h"      

namespace EngineUtilities {
  namespace Matriz {

    /*
      *  @brief Structure representing a 3x3 matrix with basic operations.
    */
    struct Matriz3x3 {
      /*
        *  @brief Matrix elements stored in column-major order.
      */
      float m[3][3]; 

      /*
        *  @brief Default constructor. Initializes as identity matrix.
      */
      inline Matriz3x3() {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
      }

      /*
        *  @brief Constructor with explicit values for each element.
        *  @param c0r0 Value for column 0, row 0.
        *  @param c0r1 Value for column 0, row 1.
        *  @param c0r2 Value for column 0, row 2.
        *  @param c1r0 Value for column 1, row 0.
        *  @param c1r1 Value for column 1, row 1.
        *  @param c1r2 Value for column 1, row 2.
        *  @param c2r0 Value for column 2, row 0.
        *  @param c2r1 Value for column 2, row 1.
        *  @param c2r2 Value for column 2, row 2.
      */
      inline Matriz3x3(float c0r0, float c0r1, float c0r2,
        float c1r0, float c1r1, float c1r2,
        float c2r0, float c2r1, float c2r2) {
        m[0][0] = c0r0; m[0][1] = c0r1; m[0][2] = c0r2;
        m[1][0] = c1r0; m[1][1] = c1r1; m[1][2] = c1r2;
        m[2][0] = c2r0; m[2][1] = c2r1; m[2][2] = c2r2;
      }

      /*
        *  @brief Assignment operator.
        *  @param other Matrix to copy from.
        *  @return Reference to this matrix.
      */
      inline Matriz3x3& operator=(const Matriz3x3& other) {
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            m[i][j] = other.m[i][j];
          }
        }
        return *this;
      }

      /*
        *  @brief Equality operator.
        *  @param other Matrix to compare.
        *  @return True if matrices are approximately equal.
      */
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

      /*
        *  @brief Inequality operator.
        *  @param other Matrix to compare.
        *  @return True if matrices are not equal.
      */
      inline bool operator!=(const Matriz3x3& other) const {
        return !(*this == other);
      }

      /*
        *  @brief Matrix addition.
        *  @param other Matrix to add.
        *  @return Resulting matrix.
      */
      inline Matriz3x3 operator+(const Matriz3x3& other) const {
        Matriz3x3 result;
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            result.m[i][j] = m[i][j] + other.m[i][j];
          }
        }
        return result;
      }

      /*
        *  @brief Matrix subtraction.
        *  @param other Matrix to subtract.
        *  @return Resulting matrix.
      */
      inline Matriz3x3 operator-(const Matriz3x3& other) const {
        Matriz3x3 result;
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            result.m[i][j] = m[i][j] - other.m[i][j];
          }
        }
        return result;
      }

      /*
        *  @brief Scalar multiplication.
        *  @param scalar Value to multiply each element.
        *  @return Resulting matrix.
      */
      inline Matriz3x3 operator*(float scalar) const {
        Matriz3x3 result;
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            result.m[i][j] = m[i][j] * scalar;
          }
        }
        return result;
      }

      /*
        *  @brief Matrix multiplication.
        *  @param other Matrix to multiply.
        *  @return Resulting matrix.
      */
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

      /*
        *  @brief Matrix-vector multiplication.
        *  @param vec Vector to multiply.
        *  @return Resulting vector.
      */
      inline Vectors::Vector3 operator*(const Vectors::Vector3& vec) const {
        return Vectors::Vector3(
          m[0][0] * vec.x + m[1][0] * vec.y + m[2][0] * vec.z,
          m[0][1] * vec.x + m[1][1] * vec.y + m[2][1] * vec.z,
          m[0][2] * vec.x + m[1][2] * vec.y + m[2][2] * vec.z
        );
      }

      /*
        *  @brief Compound addition assignment.
        *  @param other Matrix to add.
        *  @return Reference to this matrix.
      */
      inline Matriz3x3& operator+=(const Matriz3x3& other) {
        *this = *this + other;
        return *this;
      }

      /*
        *  @brief Compound subtraction assignment.
        *  @param other Matrix to subtract.
        *  @return Reference to this matrix.
      */
      inline Matriz3x3& operator-=(const Matriz3x3& other) {
        *this = *this - other;
        return *this;
      }

      /*
        *  @brief Compound scalar multiplication assignment.
        *  @param scalar Value to multiply.
        *  @return Reference to this matrix.
      */
      inline Matriz3x3& operator*=(float scalar) {
        *this = *this * scalar;
        return *this;
      }

      /*
        *  @brief Compound matrix multiplication assignment.
        *  @param other Matrix to multiply.
        *  @return Reference to this matrix.
      */
      inline Matriz3x3& operator*=(const Matriz3x3& other) {
        *this = *this * other;
        return *this;
      }

      /*
        *  @brief Returns the identity matrix.
        *  @return Identity matrix.
      */
      static inline Matriz3x3 Identity() {
        return Matriz3x3(1.0f, 0.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          0.0f, 0.0f, 1.0f);
      }

      /*
        *  @brief Calculates the cofactor of the element at (row, col).
        *  @param row Row index.
        *  @param col Column index.
        *  @return Cofactor value.
      */
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

      /*
        *  @brief Calculates the determinant of the matrix.
        *  @return Determinant value.
      */
      inline float determinant() const {
        return m[0][0] * cofactor(0, 0) + m[1][0] * cofactor(0, 1) + m[2][0] * cofactor(0, 2);
      }

      /*
        *  @brief Returns the transposed matrix.
        *  @return Transposed matrix.
      */
      inline Matriz3x3 transposed() const {
        Matriz3x3 result;
        for (int i = 0; i < 3; ++i) {
          for (int j = 0; j < 3; ++j) {
            result.m[j][i] = m[i][j]; 
          }
        }
        return result;
      }

      /*
        *  @brief Returns the adjugate matrix.
        *  @return Adjugate matrix.
      */
      inline Matriz3x3 adjugate() const {
        Matriz3x3 adj;
        adj.m[0][0] = cofactor(0, 0); adj.m[1][0] = cofactor(0, 1); adj.m[2][0] = cofactor(0, 2);
        adj.m[0][1] = cofactor(1, 0); adj.m[1][1] = cofactor(1, 1); adj.m[2][1] = cofactor(1, 2);
        adj.m[0][2] = cofactor(2, 0); adj.m[1][2] = cofactor(2, 1); adj.m[2][2] = cofactor(2, 2);
        return adj.transposed();
      }

      /*
        *  @brief Returns the inverse of the matrix.
        *  @return Inverse matrix, or identity if not invertible.
      */
      inline Matriz3x3 inverse() const {
        float det = determinant();
        if (Math::abs(det) < Math::EPSILON) {
          return Identity();
        }
        Matriz3x3 adj = adjugate();
        return adj * (1.0f / det);
      }

      /*
        *  @brief Creates a rotation matrix for a given angle in radians around the X axis.
        *  @param angle_rad Angle in radians.
        *  @return Rotation matrix.
      */
      static inline Matriz3x3 RotationX(float angle_rad) {
        float c = Math::cos(angle_rad);
        float s = Math::sin(angle_rad);
        return Matriz3x3(1.0f, 0.0f, 0.0f,
          0.0f, c, s,
          0.0f, -s, c);
      }

      /*
        *  @brief Creates a rotation matrix for a given angle in radians around the Y axis.
        *  @param angle_rad Angle in radians.
        *  @return Rotation matrix.
      */
      static inline Matriz3x3 RotationY(float angle_rad) {
        float c = Math::cos(angle_rad);
        float s = Math::sin(angle_rad);
        return Matriz3x3(c, 0.0f, -s,
          0.0f, 1.0f, 0.0f,
          s, 0.0f, c);
      }

      /*
        *  @brief Creates a rotation matrix for a given angle in radians around the Z axis.
        *  @param angle_rad Angle in radians.
        *  @return Rotation matrix.
      */
      static inline Matriz3x3 RotationZ(float angle_rad) {
        float c = Math::cos(angle_rad);
        float s = Math::sin(angle_rad);
        return Matriz3x3(c, s, 0.0f,
          -s, c, 0.0f,
          0.0f, 0.0f, 1.0f);
      }

      /*
        *  @brief Creates a scaling matrix with given scale factors.
        *  @param sx Scale factor for X.
        *  @param sy Scale factor for Y.
        *  @param sz Scale factor for Z.
        *  @return Scaling matrix.
      */
      static inline Matriz3x3 Scale(float sx, float sy, float sz) {
        return Matriz3x3(sx, 0.0f, 0.0f,
          0.0f, sy, 0.0f,
          0.0f, 0.0f, sz);
      }

      /*
        *  @brief Creates a scaling matrix from a vector.
        *  @param scaleVec Vector containing scale factors.
        *  @return Scaling matrix.
      */
      static inline Matriz3x3 Scale(const Vectors::Vector3& scaleVec) {
        return Scale(scaleVec.x, scaleVec.y, scaleVec.z);
      }
    };

    /*
      *  @brief Scalar multiplication (commutative).
      *  @param scalar Value to multiply.
      *  @param mat Matrix to multiply.
      *  @return Resulting matrix.
    */
    inline Matriz3x3 operator*(float scalar, const Matriz3x3& mat) {
      return mat * scalar;
    }

  } 
}
