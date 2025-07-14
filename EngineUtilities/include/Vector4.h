#pragma once
#include "EngineUtilites.h"
#include "EngineMath.h"

namespace EngineUtilities {
  namespace Vectors {

    /*
      *  @brief Represents a 4D vector with float components.
    */
    struct Vector4 {
      /*
        *  @brief X component of the vector.
      */
      float x; 
      /*
        *  @brief Y component of the vector.
      */
      float y; 
      /*
        *  @brief Z component of the vector.
      */
      float z; 
      /*
        *  @brief W component of the vector.
      */
      float w;

      /*
        *  @brief Default constructor. Initializes all components to 0.0f.
      */
      inline Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

      /*
        *  @brief Constructs a Vector4 with specified components.
        *  @param inX X component.
        *  @param inY Y component.
        *  @param inZ Z component.
        *  @param inW W component.
      */
      inline Vector4(float inX, float inY, float inZ, float inW) : x(inX), y(inY), z(inZ), w(inW) {}

      /*
        *  @brief Assignment operator.
        *  @param other Vector4 to copy from.
        *  @return Reference to this vector.
      */
      inline Vector4& operator=(const Vector4& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
      }

      /*
        *  @brief Adds two Vector4 objects.
        *  @param other Vector4 to add.
        *  @return Resulting Vector4.
      */
      inline Vector4 operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
      }
      /*
        *  @brief Subtracts another Vector4 from this one.
        *  @param other Vector4 to subtract.
        *  @return Resulting Vector4.
      */
      inline Vector4 operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
      }

      /*
        *  @brief Multiplies the vector by a scalar.
        *  @param scalar Scalar value.
        *  @return Resulting Vector4.
      */
      inline Vector4 operator*(float scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
      }
      /*
        *  @brief Divides the vector by a scalar.
        *  @param scalar Scalar value.
        *  @return Resulting Vector4.
      */
      inline Vector4 operator/(float scalar) const {
        if (scalar != 0.0f) {
          return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }
        return Vector4();
      }

      /*
        *  @brief Adds another Vector4 to this one (in-place).
        *  @param other Vector4 to add.
        *  @return Reference to this vector.
      */
      inline Vector4& operator+=(const Vector4& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
      }
      /*
        *  @brief Subtracts another Vector4 from this one (in-place).
        *  @param other Vector4 to subtract.
        *  @return Reference to this vector.
      */
      inline Vector4& operator-=(const Vector4& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
      }
      /*
        *  @brief Multiplies this vector by a scalar (in-place).
        *  @param scalar Scalar value.
        *  @return Reference to this vector.
      */
      inline Vector4& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
      }
      /*
        *  @brief Divides this vector by a scalar (in-place).
        *  @param scalar Scalar value.
        *  @return Reference to this vector.
      */
      inline Vector4& operator/=(float scalar) {
        if (scalar != 0.0f) {
          x /= scalar;
          y /= scalar;
          z /= scalar;
          w /= scalar;
        }
        return *this;
      }

      /*
        *  @brief Checks if two Vector4 objects are approximately equal.
        *  @param other Vector4 to compare.
        *  @return True if equal, false otherwise.
      */
      inline bool operator==(const Vector4& other) const {
        return Math::approxEqual(x, other.x) &&
          Math::approxEqual(y, other.y) &&
          Math::approxEqual(z, other.z) &&
          Math::approxEqual(w, other.w);
      }
      /*
        *  @brief Checks if two Vector4 objects are not equal.
        *  @param other Vector4 to compare.
        *  @return True if not equal, false otherwise.
      */
      inline bool operator!=(const Vector4& other) const {
        return !(*this == other);
      }

      /*
        *  @brief Calculates the dot product with another Vector4.
        *  @param other Vector4 to dot with.
        *  @return Dot product value.
      */
      inline float dot(const Vector4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
      }

      /*
        *  @brief Returns the magnitude (length) of the vector.
        *  @return Magnitude as a float.
      */
      inline float magnitude() const {
        return Math::sqrt(x * x + y * y + z * z + w * w);
      }

      /*
        *  @brief Returns the squared magnitude of the vector.
        *  @return Squared magnitude as a float.
      */
      inline float squareMagnitude() const {
        return x * x + y * y + z * z + w * w;
      }

      /*
        *  @brief Normalizes the vector in-place.
        *  @return Reference to this vector.
      */
      inline Vector4& normalize() {
        float mag = magnitude();
        if (mag > Math::EPSILON) {
          x /= mag;
          y /= mag;
          z /= mag;
          w /= mag;
        }
        return *this;
      }

      /*
        *  @brief Returns a normalized copy of the vector.
        *  @return Normalized Vector4.
      */
      inline Vector4 normalized() const {
        float mag = magnitude();
        if (mag > Math::EPSILON) {
          return Vector4(x / mag, y / mag, z / mag, w / mag);
        }
        return Vector4();
      }

      /*
        *  @brief Calculates the distance to another Vector4.
        *  @param other Vector4 to measure distance to.
        *  @return Distance as a float.
      */
      inline float distance(const Vector4& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        float dw = w - other.w;
        return Math::sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
      }

      /*
        *  @brief Calculates the squared distance to another Vector4.
        *  @param other Vector4 to measure squared distance to.
        *  @return Squared distance as a float.
      */
      inline float squareDistance(const Vector4& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        float dw = w - other.w;
        return dx * dx + dy * dy + dz * dz + dw * dw;
      }
    };

    /*
      *  @brief Multiplies a scalar by a Vector4.
      *  @param scalar Scalar value.
      *  @param vec Vector4 to multiply.
      *  @return Resulting Vector4.
    */
    inline Vector4 operator*(float scalar, const Vector4& vec) {
      return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
    }

    /*
      *  @brief Outputs a Vector4 to an output stream.
      *  @param os Output stream.
      *  @param v Vector4 to output.
      *  @return Reference to the output stream.
    */
    inline std::ostream& operator<<(std::ostream& os, const Vector4& v) {
      os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
      return os;
    }

  } 
}
