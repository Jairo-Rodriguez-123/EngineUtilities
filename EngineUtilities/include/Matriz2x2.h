#pragma once

#include "EngineUtilites.h"
#include "EngineMath.h"
#include "Vector2.h" 

namespace EngineUtilities {
namespace Matriz {

/*
*  @brief Structure representing a 2x2 matrix with basic operations.
*/
  struct Matriz2x2 {
    /*
    *  @brief Matrix elements stored in column-major order.
    */
    float m[2][2];

    /*
    *  @brief Default constructor. Initializes as identity matrix.
    */
    inline Matriz2x2() {
      m[0][0] = 1.0f; m[0][1] = 0.0f;
      m[1][0] = 0.0f; m[1][1] = 1.0f;
    }

    /*
    *  @brief Constructor with explicit values for each element.
    *  @param c0r0 Value for column 0, row 0.
    *  @param c0r1 Value for column 0, row 1.
    *  @param c1r0 Value for column 1, row 0.
    *  @param c1r1 Value for column 1, row 1.
    */
    inline Matriz2x2(float c0r0, float c0r1,
      float c1r0, float c1r1) {
      m[0][0] = c0r0; m[0][1] = c0r1;
      m[1][0] = c1r0; m[1][1] = c1r1;
    }

    /*
    *  @brief Assignment operator.
    *  @param other Matrix to copy from.
    *  @return Reference to this matrix.
    */
    inline Matriz2x2& operator=(const Matriz2x2& other) {
      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
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

    inline
      bool operator==(const Matriz2x2& other) const {
      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
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
    inline bool operator!=(const Matriz2x2& other) const {
      return !(*this == other);
    }

    /*
    *  @brief Matrix addition.
    *  @param other Matrix to add.
    *  @return Resulting matrix.
    */
    inline Matriz2x2 operator+(const Matriz2x2& other) const {
      Matriz2x2 result;
      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
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
    inline Matriz2x2 operator-(const Matriz2x2& other) const {
      Matriz2x2 result;
      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
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
    inline Matriz2x2 operator*(float scalar) const {
      Matriz2x2 result;
      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
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
    inline Matriz2x2 operator*(const Matriz2x2& other) const {
      Matriz2x2 result;
      result.m[0][0] = m[0][0] * other.m[0][0] + m[1][0] * other.m[0][1];
      result.m[0][1] = m[0][1] * other.m[0][0] + m[1][1] * other.m[0][1];

      result.m[1][0] = m[0][0] * other.m[1][0] + m[1][0] * other.m[1][1];
      result.m[1][1] = m[0][1] * other.m[1][0] + m[1][1] * other.m[1][1];
      return result;
    }

    /*
    *  @brief Matrix-vector multiplication.
    *  @param vec Vector to multiply.
    *  @return Resulting vector.
    */
    inline Vectors::Vector2 operator*(const Vectors::Vector2& vec) const {
      return Vectors::Vector2(
        m[0][0] * vec.x + m[1][0] * vec.y, // m00*x + m10*y
        m[0][1] * vec.x + m[1][1] * vec.y  // m01*x + m11*y
      );
    }

    /*
    *  @brief Compound addition assignment.
    *  @param other Matrix to add.
    *  @return Reference to this matrix.
    */
    inline Matriz2x2& operator+=(const Matriz2x2& other) {
      *this = *this + other;
      return *this;
    }

    /*
    *  @brief Compound subtraction assignment.
    *  @param other Matrix to subtract.
    *  @return Reference to this matrix.
    */
    inline Matriz2x2& operator-=(const Matriz2x2& other) {
      *this = *this - other;
      return *this;
    }

    /*
    *  @brief Compound scalar multiplication assignment.
    *  @param scalar Value to multiply.
    *  @return Reference to this matrix.
    */
    inline Matriz2x2& operator*=(float scalar) {
      *this = *this * scalar;
      return *this;
    }

    /*
    *  @brief Compound matrix multiplication assignment.
    *  @param other Matrix to multiply.
    *  @return Reference to this matrix.
    */
    inline Matriz2x2& operator*=(const Matriz2x2& other) {
      *this = *this * other;
      return *this;
    }

    /*
    *  @brief Returns the identity matrix.
    *  @return Identity matrix.
    */
    static inline Matriz2x2 Identity() {
      return Matriz2x2(1.0f, 0.0f,
        0.0f, 1.0f);
    }

    /*
    *  @brief Calculates the determinant of the matrix.
    *  @return Determinant value.
    */
    inline float determinant() const {
      return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    /*
    *  @brief Returns the transposed matrix.
    *  @return Transposed matrix.
    */
    inline Matriz2x2 transposed() const {
      return Matriz2x2(m[0][0], m[1][0],
        m[0][1], m[1][1]);
    }

/*
*  @brief Returns the inverse of the matrix.
*  @return Inverse matrix, or identity if not invertible.
*/
  inline Matriz2x2 inverse() const {
    float det = determinant();
      if (Math::abs(det) < Math::EPSILON) {
        return Identity();
          }
  float invDet = 1.0f / det;
    return Matriz2x2(m[1][1] * invDet, -m[0][1] * invDet,
      -m[1][0] * invDet, m[0][0] * invDet);
  }
/*
*  @brief Creates a rotation matrix for a given angle in radians.
*  @param angle_rad Angle in radians.
*  @return Rotation matrix.
*/
  static inline Matriz2x2 Rotation(float angle_rad) {
    float c = Math::cos(angle_rad);
    float s = Math::sin(angle_rad);
      return Matriz2x2(c, s,-s, c);
  }

/*
*  @brief Creates a scaling matrix with given scale factors.
*  @param sx Scale factor for X.
*  @param sy Scale factor for Y.
*  @return Scaling matrix.
*/
  static inline Matriz2x2 Scale(float sx, float sy) {
    return Matriz2x2(sx, 0.0f,0.0f, sy);
  }

/*
*  @brief Creates a scaling matrix from a vector.
*  @param scaleVec Vector containing scale factors.
*  @return Scaling matrix.
*/
  static inline Matriz2x2 Scale(const Vectors::Vector2& scaleVec) {
    return Scale(scaleVec.x, scaleVec.y);
  }
};

/*
*  @brief Scalar multiplication (commutative).
*  @param scalar Value to multiply.
*  @param mat Matrix to multiply.
*  @return Resulting matrix.
*/
  inline Matriz2x2 operator*(float scalar, const Matriz2x2& mat) {
    return mat * scalar;
  }
/*
*  @brief Output stream operator for printing the matrix.
*  @param os Output stream.
*  @param m Matrix to print.
*  @return Output stream.
*/
  inline std::ostream& operator<<(std::ostream& os, const Matriz2x2& m) {
    os << "Matrix2x2:\n";
    os << "[" << m.m[0][0] << ", " << m.m[1][0] << "]\n"; // Columna 0
    os << "[" << m.m[0][1] << ", " << m.m[1][1] << "]";   // Columna 1
      return os;
    }
  } 
}
