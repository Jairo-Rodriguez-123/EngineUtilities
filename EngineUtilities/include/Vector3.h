#pragma once

#include "EngineMath.h"
#include <iostream> 

namespace EngineUtilities {
  namespace Vectors {


    struct Vector3 {
      /*
        *  @brief X component of the vector
      */
      float x, 
      /*
        *  @brief Y component of the vector
      */
      y, 
      /*
        *  @brief Z component of the vector
      */
      z;

      /*
        *  @brief Default constructor. Initializes all components to zero.
      */
      inline Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

      /*
        *  @brief Constructor with custom values for each component.
        *  @param inX X component
        *  @param inY Y component
        *  @param inZ Z component
      */
      inline Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {}

      /*
        *  @brief Assignment operator.
        *  @param other Vector to copy from
        *  @return Reference to this vector
      */
      inline Vector3& operator=(const Vector3& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
      }

      /*
        *  @brief Equality operator.
        *  @param other Vector to compare
        *  @return True if all components are approximately equal
      */
      inline bool operator==(const Vector3& other) const {
        return Math::approxEqual(x, other.x) && Math::approxEqual(y, other.y) && Math::approxEqual(z, other.z);
      }

      /*
        *  @brief Inequality operator.
        *  @param other Vector to compare
        *  @return True if any component is not approximately equal
      */
      inline bool operator!=(const Vector3& other) const {
        return !(*this == other);
      }

      /*
        *  @brief Addition operator.
        *  @param other Vector to add
        *  @return Resulting vector
      */
      Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
      }

      /*
        *  @brief Subtraction operator.
        *  @param other Vector to subtract
        *  @return Resulting vector
      */
      inline Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
      }

      /*
        *  @brief Scalar multiplication operator.
        *  @param scalar Value to multiply
        *  @return Resulting vector
      */
      inline Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
      }

      /*
        *  @brief Scalar division operator.
        *  @param scalar Value to divide
        *  @return Resulting vector, or zero vector if scalar is near zero
      */
      inline Vector3 operator/(float scalar) const {
        if (Math::abs(scalar) < Math::EPSILON) {
          return Vector3(0.0f, 0.0f, 0.0f); 
        }
        return Vector3(x / scalar, y / scalar, z / scalar);
      }

      /*
        *  @brief Addition assignment operator.
        *  @param other Vector to add
        *  @return Reference to this vector
      */
      inline Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
      }

      /*
        *  @brief Subtraction assignment operator.
        *  @param other Vector to subtract
        *  @return Reference to this vector
      */
      inline Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
      }

      /*
        *  @brief Scalar multiplication assignment operator.
        *  @param scalar Value to multiply
        *  @return Reference to this vector
      */
      inline Vector3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
      }

      /*
        *  @brief Scalar division assignment operator.
        *  @param scalar Value to divide
        *  @return Reference to this vector, or zero vector if scalar is near zero
      */
      inline Vector3& operator/=(float scalar) {
        if (Math::abs(scalar) < Math::EPSILON) {
          x = y = z = 0.0f;
        }
        else {
          x /= scalar;
          y /= scalar;
          z /= scalar;
        }
        return *this;
      }

      /*
        *  @brief Dot product with another vector.
        *  @param other Vector to dot with
        *  @return Scalar dot product
      */
      inline float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
      }

      /*
        *  @brief Cross product with another vector.
        *  @param other Vector to cross with
        *  @return Resulting vector
      */
      inline Vector3 cross(const Vector3& other) const {
        return Vector3(
          y * other.z - z * other.y,
          z * other.x - x * other.z,
          x * other.y - y * other.x
        );
      }

      /*
        *  @brief Magnitude (length) of the vector.
        *  @return Magnitude as a float
      */
      inline float magnitude() const {
        return Math::sqrt(x * x + y * y + z * z);
      }

      /*
        *  @brief Squared magnitude of the vector.
        *  @return Squared magnitude as a float
      */
      inline float squareMagnitude() const {
        return x * x + y * y + z * z;
      }

      /*
        *  @brief Normalizes the vector in place.
        *  @return Reference to this vector
      */
      inline Vector3& normalize() {
        float mag = magnitude();
        if (mag > Math::EPSILON) {
          x /= mag;
          y /= mag;
          z /= mag;
        }
        else {
          x = y = z = 0.0f; 
        }
        return *this;
      }

      /*
        *  @brief Returns a normalized copy of the vector.
        *  @return Normalized vector
      */
      inline Vector3 normalized() const {
        Vector3 result = *this;
        result.normalize();
        return result;
      }

      /*
        *  @brief Distance to another vector.
        *  @param other Vector to measure distance to
        *  @return Distance as a float
      */
      inline float distance(const Vector3& other) const {
        return (*this - other).magnitude();
      }

      /*
        *  @brief Returns a zero vector.
        *  @return Zero vector
      */
      static inline Vector3 Zero() {
        return Vector3(0.0f, 0.0f, 0.0f);
      }

      /*
        *  @brief Returns a unit vector along the X axis.
        *  @return Unit X vector
      */
      static inline Vector3 UnitX() {
        return Vector3(1.0f, 0.0f, 0.0f);
      }

      /*
        *  @brief Returns a unit vector along the Y axis.
        *  @return Unit Y vector
      */
      static inline Vector3 UnitY() {
        return Vector3(0.0f, 1.0f, 0.0f);
      }

      /*
        *  @brief Returns a unit vector along the Z axis.
        *  @return Unit Z vector
      */
      static inline Vector3 UnitZ() {
        return Vector3(0.0f, 0.0f, 1.0f);
      }
    };

    /*
      *  @brief Scalar multiplication operator (scalar * vector).
      *  @param scalar Value to multiply
      *  @param v Vector to multiply
      *  @return Resulting vector
    */
    inline Vector3 operator*(float scalar, const Vector3& v) {
      return v * scalar;
    }

    /*
      *  @brief Output stream operator for Vector3.
      *  @param os Output stream
      *  @param v Vector to output
      *  @return Output stream
    */
    inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
      os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
      return os;
    }

  } 
}