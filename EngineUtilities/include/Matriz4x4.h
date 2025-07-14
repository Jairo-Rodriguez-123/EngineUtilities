  #pragma once

#include "EngineMath.h"
#include "Vector3.h"
#include <iostream> 
#include "Matriz3x3.h"

/*
*  @brief Namespace containing matrix utilities.
*/
namespace EngineUtilities {
/*
*  @brief Namespace containing matrix types.
*/
namespace Matrices {
/*
*  @brief Structure representing a 4x4 matrix.
*/
struct Matriz4x4 {
/*
*  @brief Matrix elements in column-major order.
*/
    float m[4][4];
/*
* @brief Default constructor. Initializes as identity matrix.
*/
  inline Matriz4x4() {
    loadIdentity();
        }

/*
*  @brief Constructor with explicit values for each element.
*  @param m00 Element at row 0, column 0.
*  @param m01 Element at row 0, column 1.
*  @param m02 Element at row 0, column 2.
*  @param m03 Element at row 0, column 3.
*  @param m10 Element at row 1, column 0.
*  @param m11 Element at row 1, column 1.
*  @param m12 Element at row 1, column 2.
*  @param m13 Element at row 1, column 3.
*  @param m20 Element at row 2, column 0.
*  @param m21 Element at row 2, column 1.
*  @param m22 Element at row 2, column 2.
*  @param m23 Element at row 2, column 3.
*  @param m30 Element at row 3, column 0.
*  @param m31 Element at row 3, column 1.
*  @param m32 Element at row 3, column 2.
*  @param m33 Element at row 3, column 3.
*/
  inline Matriz4x4(float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33) {
      m[0][0] = m00; m[0][1] = m10; m[0][2] = m20; m[0][3] = m30;
      m[1][0] = m01; m[1][1] = m11; m[1][2] = m21; m[1][3] = m31;
      m[2][0] = m02; m[2][1] = m12; m[2][2] = m22; m[2][3] = m32;
      m[3][0] = m03; m[3][1] = m13; m[3][2] = m23; m[3][3] = m33;
      }

/*
*  @brief Loads the identity matrix into this matrix.
*/
   inline void loadIdentity() {
       m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
       m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
       m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
       m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
   }

      /*
        *  @brief Returns an identity matrix.
        *  @return Matriz4x4 identity matrix.
      */
      static inline Matriz4x4 Identity() {
        return Matriz4x4();
      }

      /*
        *  @brief Multiplies this matrix by another 4x4 matrix.
        *  @param other The matrix to multiply by.
        *  @return The result of the multiplication.
      */
      inline 
        Matriz4x4 operator*(const Matriz4x4& other) const {
        Matriz4x4 result;
          for (int i = 0; i < 4; ++i) { 
            for (int j = 0; j < 4; ++j) { 
              result.m[j][i] = 0.0f;
              for (int k = 0; k < 4; ++k) {
                result.m[j][i] += m[k][i] * other.m[j][k];
              }
            }
          }
          return result;
      }

      /*
        *  @brief Multiplies this matrix by a 3D vector.
        *  @param v The vector to transform.
        *  @return The transformed vector.
      */
      inline Vectors::Vector3 operator*(const Vectors::Vector3& v) const {
        float x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0];
        float y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1];
        float z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2];
        float w = m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3];

          if (!Math::approxEqual(w, 1.0f) && !Math::approxEqual(w, 0.0f)) {
            return Vectors::Vector3(x / w, y / w, z / w);
          }
          return Vectors::Vector3(x, y, z);
      }

      /*
        *  @brief Creates a translation matrix from a vector.
        *  @param t The translation vector.
        *  @return The translation matrix.
      */
      static 
        inline Matriz4x4 createTranslation(const Vectors::Vector3& t) {
          Matriz4x4 result;
          result.m[3][0] = t.x;
          result.m[3][1] = t.y;
          result.m[3][2] = t.z;
          return result;
      }

      /*
        *  @brief Creates a scale matrix from a vector.
        *  @param s The scale vector.
        *  @return The scale matrix.
      */
      static 
        inline Matriz4x4 createScale(const Vectors::Vector3& s) {
          Matriz4x4 result;
          result.m[0][0] = s.x;
          result.m[1][1] = s.y;
          result.m[2][2] = s.z;
          result.m[3][3] = 1.0f;
          return result;
      }

      /*
        *  @brief Extracts the rotation part as a 3x3 matrix.
        *  @return The rotation matrix (3x3).
      */
      inline EngineUtilities::Matriz::Matriz3x3 getRotationMatriz3x3() const  {
        return EngineUtilities::Matriz::Matriz3x3::Matriz3x3(m[0][0], m[1][0], m[2][0],
          m[0][1], m[1][1], m[2][1],
          m[0][2], m[1][2], m[2][2]);
      }
    };

    /*
      *  @brief Outputs the matrix to a stream in a readable format.
      *  @param os Output stream.
      *  @param mat Matrix to output.
      *  @return Output stream.
    */
    inline std::ostream& operator<<(std::ostream& os, const Matriz4x4& mat) {
      os << "Matriz4x4:\n";
      for (int i = 0; i < 4; ++i) { 
        os << "| ";
        for (int j = 0; j < 4; ++j) { 
          os << mat.m[j][i] << "\t"; 
        }
           os << "|\n";
      }
      return os;
    }
  } 
  }