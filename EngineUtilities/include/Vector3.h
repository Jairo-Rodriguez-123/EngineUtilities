
#pragma once

#include "EngineMath.h"
#include <iostream> 

namespace EngineUtilities {
  namespace Vectors {


    struct Vector3 {
      float x, y, z;

      inline Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

      
      inline Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {}

     
      inline Vector3& operator=(const Vector3& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
      }

      inline bool operator==(const Vector3& other) const {
        return Math::approxEqual(x, other.x) && Math::approxEqual(y, other.y) && Math::approxEqual(z, other.z);
      }

      inline bool operator!=(const Vector3& other) const {
        return !(*this == other);
      }

       Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
      }


      inline Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
      }

   
      inline Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
      }

      
      inline Vector3 operator/(float scalar) const {
        if (Math::abs(scalar) < Math::EPSILON) {
          return Vector3(0.0f, 0.0f, 0.0f); 
        }
        return Vector3(x / scalar, y / scalar, z / scalar);
      }

     
      inline Vector3& operator+=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
      }

      
      inline Vector3& operator-=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
      }

      inline Vector3& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
      }

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

     
      inline float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
      }

      
      inline Vector3 cross(const Vector3& other) const {
        return Vector3(
          y * other.z - z * other.y,
          z * other.x - x * other.z,
          x * other.y - y * other.x
        );
      }

      
      inline float magnitude() const {
        return Math::sqrt(x * x + y * y + z * z);
      }

      
      inline float squareMagnitude() const {
        return x * x + y * y + z * z;
      }

     
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

   
      inline Vector3 normalized() const {
        Vector3 result = *this;
        result.normalize();
        return result;
      }

    
      inline float distance(const Vector3& other) const {
        return (*this - other).magnitude();
      }

      
      static inline Vector3 Zero() {
        return Vector3(0.0f, 0.0f, 0.0f);
      }

      static inline Vector3 UnitX() {
        return Vector3(1.0f, 0.0f, 0.0f);
      }

      static inline Vector3 UnitY() {
        return Vector3(0.0f, 1.0f, 0.0f);
      }

      
      static inline Vector3 UnitZ() {
        return Vector3(0.0f, 0.0f, 1.0f);
      }
    };

    inline Vector3 operator*(float scalar, const Vector3& v) {
      return v * scalar;
    }

    inline std::ostream& operator<<(std::ostream& os, const Vector3& v) {
      os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
      return os;
    }

  } 
} 