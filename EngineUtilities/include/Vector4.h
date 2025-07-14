
#pragma once
#include "EngineUtilites.h"
#include "EngineMath.h"

namespace EngineUtilities {
  namespace Vectors {

    
    struct Vector4 {
      float x; 
      float y; 
      float z; 
      float w;

      
      inline Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

      
      inline Vector4(float inX, float inY, float inZ, float inW) : x(inX), y(inY), z(inZ), w(inW) {}

      
      inline Vector4& operator=(const Vector4& other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
      }

     
      inline Vector4 operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
      }
      inline Vector4 operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
      }

      
      inline Vector4 operator*(float scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
      }
      inline Vector4 operator/(float scalar) const {
        if (scalar != 0.0f) {
          return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }
        return Vector4();
      }

      
      inline Vector4& operator+=(const Vector4& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
      }
      inline Vector4& operator-=(const Vector4& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
      }
      inline Vector4& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
      }
      inline Vector4& operator/=(float scalar) {
        if (scalar != 0.0f) {
          x /= scalar;
          y /= scalar;
          z /= scalar;
          w /= scalar;
        }
        return *this;
      }

      
      inline bool operator==(const Vector4& other) const {
        return Math::approxEqual(x, other.x) &&
          Math::approxEqual(y, other.y) &&
          Math::approxEqual(z, other.z) &&
          Math::approxEqual(w, other.w);
      }
      inline bool operator!=(const Vector4& other) const {
        return !(*this == other);
      }

      inline float dot(const Vector4& other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
      }

      
      inline float magnitude() const {
        return Math::sqrt(x * x + y * y + z * z + w * w);
      }

      
      inline float squareMagnitude() const {
        return x * x + y * y + z * z + w * w;
      }

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

      
      inline Vector4 normalized() const {
        float mag = magnitude();
        if (mag > Math::EPSILON) {
          return Vector4(x / mag, y / mag, z / mag, w / mag);
        }
        return Vector4();
      }

      
      inline float distance(const Vector4& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        float dw = w - other.w;
        return Math::sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
      }

      
      inline float squareDistance(const Vector4& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        float dw = w - other.w;
        return dx * dx + dy * dy + dz * dz + dw * dw;
      }
    };

   
    inline Vector4 operator*(float scalar, const Vector4& vec) {
      return Vector4(vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar);
    }

    inline std::ostream& operator<<(std::ostream& os, const Vector4& v) {
      os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
      return os;
    }

  } 
} 
