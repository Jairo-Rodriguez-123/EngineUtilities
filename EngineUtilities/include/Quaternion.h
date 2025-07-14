 
    #pragma once

    #include "EngineMath.h"
    #include "Vector3.h"
    #include "Matriz4x4.h" /
    #include <iostream>

    namespace EngineUtilities {
      namespace Rotations {

        /*
          *  @brief Structure representing a quaternion for 3D rotations.
        */
        struct Quaternion {
          /*
            *  @brief X component of the quaternion.
          */
          float x, y, z, w;

          /*
            *  @brief Default constructor. Initializes as identity quaternion.
          */
          inline Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
          /*
            *  @brief Constructor with explicit values for each component.
            *  @param inX X component.
            *  @param inY Y component.
            *  @param inZ Z component.
            *  @param inW W component.
          */
          inline Quaternion(float inX, float inY, float inZ, float inW) : x(inX), y(inY), z(inZ), w(inW) {}

          /*
            *  @brief Constructs a quaternion from an axis and angle in radians.
            *  @param axis Rotation axis.
            *  @param angle_rad Rotation angle in radians.
          */
          inline Quaternion(const Vectors::Vector3& axis, float angle_rad) {
            float half_angle = angle_rad * 0.5f;
            float sin_half_angle = Math::sin(half_angle);
            w = Math::cos(half_angle);
            x = axis.x * sin_half_angle;
            y = axis.y * sin_half_angle;
            z = axis.z * sin_half_angle;
            normalize();
          }

          /*
            *  @brief Assignment operator.
            *  @param other Quaternion to assign from.
            *  @return Reference to this quaternion.
          */
          inline Quaternion& operator=(const Quaternion& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            w = other.w;
            return *this;
          }

          /*
            *  @brief Equality operator.
            *  @param other Quaternion to compare.
            *  @return True if equal, false otherwise.
          */
          inline bool operator==(const Quaternion& other) const {
            return Math::approxEqual(x, other.x) &&
              Math::approxEqual(y, other.y) &&
              Math::approxEqual(z, other.z) &&
              Math::approxEqual(w, other.w);
          }

          /*
            *  @brief Inequality operator.
            *  @param other Quaternion to compare.
            *  @return True if not equal, false otherwise.
          */
          inline bool operator!=(const Quaternion& other) const {
            return !(*this == other);
          }

          /*
            *  @brief Quaternion multiplication.
            *  @param other Quaternion to multiply by.
            *  @return Resulting quaternion.
          */
          inline Quaternion operator*(const Quaternion& other) const {
            return Quaternion(
              w * other.x + x * other.w + y * other.z - z * other.y,
              w * other.y - x * other.z + y * other.w + z * other.x,
              w * other.z + x * other.y - y * other.x + z * other.w,
              w * other.w - x * other.x - y * other.y - z * other.z
            );
          }

          /*
            *  @brief Scalar multiplication.
            *  @param scalar Scalar value.
            *  @return Resulting quaternion.
          */
          inline Quaternion operator*(float scalar) const {
            return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
          }

          /*
            *  @brief Rotates a vector by this quaternion.
            *  @param vec Vector to rotate.
            *  @return Rotated vector.
          */
          inline Vectors::Vector3 operator*(const Vectors::Vector3& vec) const {
            Quaternion p(vec.x, vec.y, vec.z, 0.0f);

            Quaternion q_inv;
            q_inv.x = -x;
            q_inv.y = -y;
            q_inv.z = -z;
            q_inv.w = w;

            Quaternion temp = (*this) * p;
            Quaternion rotated_p = temp * q_inv;

            return Vectors::Vector3(rotated_p.x, rotated_p.y, rotated_p.z);
          }

          /*
            *  @brief Returns the magnitude of the quaternion.
            *  @return Magnitude as float.
          */
          inline float magnitude() const {
            return Math::sqrt(x * x + y * y + z * z + w * w);
          }

          /*
            *  @brief Returns the squared magnitude of the quaternion.
            *  @return Squared magnitude as float.
          */
          inline float squareMagnitude() const {
            return x * x + y * y + z * z + w * w;
          }

          /*
            *  @brief Normalizes the quaternion in place.
            *  @return Reference to this quaternion.
          */
          inline Quaternion& normalize() {
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
            *  @brief Returns a normalized copy of the quaternion.
            *  @return Normalized quaternion.
          */
          inline Quaternion normalized() const {
            Quaternion q = *this;
            q.normalize();
            return q;
          }

          /*
            *  @brief Returns the conjugate of the quaternion.
            *  @return Conjugated quaternion.
          */
          inline Quaternion conjugate() const {
            return Quaternion(-x, -y, -z, w);
          }

          /*
            *  @brief Returns the inverse of the quaternion.
            *  @return Inverted quaternion.
          */
          inline Quaternion inverse() const { 
            float sqMag = squareMagnitude(); 
            if (Math::abs(sqMag) < Math::EPSILON) { 
              return Quaternion(0.0f, 0.0f, 0.0f, 0.0f); 
            } 
            return conjugate() * (1.0f / sqMag); 
          } 

          /*
            *  @brief Spherical linear interpolation between two quaternions.
            *  @param q1 Start quaternion.
            *  @param q2 End quaternion.
            *  @param t Interpolation factor [0,1].
            *  @return Interpolated quaternion.
          */
          static inline Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) {
            float cos_theta = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;

            Quaternion target_q = q2;
            if (cos_theta < 0.0f) {
              target_q.x = -q2.x;
              target_q.y = -q2.y;
              target_q.z = -q2.z;
              target_q.w = -q2.w;
              cos_theta = -cos_theta;
            }

            if (cos_theta > 1.0f - Math::EPSILON) {
              return q1;
            }

            float angle = Math::acos(cos_theta);
            float sin_angle = Math::sin(angle);

            if (Math::abs(sin_angle) < Math::EPSILON) {
              return Quaternion(
                (1.0f - t) * q1.x + t * target_q.x,
                (1.0f - t) * q1.y + t * target_q.y,
                (1.0f - t) * q1.z + t * target_q.z,
                (1.0f - t) * q1.w + t * target_q.w
              ).normalize();
            }

            float ratio1 = Math::sin((1.0f - t) * angle) / sin_angle;
            float ratio2 = Math::sin(t * angle) / sin_angle;

            return Quaternion(
              ratio1 * q1.x + ratio2 * target_q.x,
              ratio1 * q1.y + ratio2 * target_q.y,
              ratio1 * q1.z + ratio2 * target_q.z,
              ratio1 * q1.w + ratio2 * target_q.w
            );
          }

          /*
            *  @brief Returns the identity quaternion.
            *  @return Identity quaternion.
          */
          static inline Quaternion Identity() {
            return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
          }

          /*
            *  @brief Converts the quaternion to a 4x4 rotation matrix.
            *  @return Rotation matrix as Matriz4x4.
          */
          inline Matrices::Matriz4x4 toMatrix4x4() const {
            Matrices::Matriz4x4 mat;

            float x2 = x * x;
            float y2 = y * y;
            float z2 = z * z;
            float xy = x * y;
            float xz = x * z;
            float yz = y * z;
            float wx = w * x;
            float wy = w * y;
            float wz = w * z;

            mat.m[0][0] = 1.0f - 2.0f * (y2 + z2);
            mat.m[0][1] = 2.0f * (xy + wz);
            mat.m[0][2] = 2.0f * (xz - wy);
            mat.m[0][3] = 0.0f;

            mat.m[1][0] = 2.0f * (xy - wz);
            mat.m[1][1] = 1.0f - 2.0f * (x2 + z2);
            mat.m[1][2] = 2.0f * (yz + wx);
            mat.m[1][3] = 0.0f;

            mat.m[2][0] = 2.0f * (xz + wy);
            mat.m[2][1] = 2.0f * (yz - wx);
            mat.m[2][2] = 1.0f - 2.0f * (x2 + y2);
            mat.m[2][3] = 0.0f;

            mat.m[3][0] = 0.0f;
            mat.m[3][1] = 0.0f;
            mat.m[3][2] = 0.0f;
            mat.m[3][3] = 1.0f;

            return mat;
          }

          /*
            *  @brief Creates a quaternion from a 4x4 rotation matrix.
            *  @param mat Rotation matrix.
            *  @return Quaternion representing the rotation.
          */
          static inline Quaternion fromMatrix4x4(const Matrices::Matriz4x4& mat) {
            float m00 = mat.m[0][0]; float m11 = mat.m[1][1]; float m22 = mat.m[2][2];
            float m01 = mat.m[1][0]; float m10 = mat.m[0][1];
            float m02 = mat.m[2][0]; float m20 = mat.m[0][2];
            float m12 = mat.m[2][1]; float m21 = mat.m[1][2];

            float trace = m00 + m11 + m22;
            Quaternion q;

            if (trace > Math::EPSILON) {
              float s = 0.5f / Math::sqrt(trace + 1.0f);
              q.w = 0.25f / s;
              q.x = (m21 - m12) * s;
              q.y = (m02 - m20) * s;
              q.z = (m10 - m01) * s;
            }
            else {
              if (m00 > m11 && m00 > m22) {
                float s = 2.0f * Math::sqrt(1.0f + m00 - m11 - m22);
                q.x = 0.25f * s;
                q.y = (m01 + m10) / s;
                q.z = (m02 + m20) / s;
                q.w = (m21 - m12) / s;
              }
              else if (m11 > m22) {
                float s = 2.0f * Math::sqrt(1.0f + m11 - m00 - m22);
                q.x = (m01 + m10) / s;
                q.y = 0.25f * s;
                q.z = (m12 + m21) / s;
                q.w = (m02 - m20) / s;
              }
              else {
                float s = 2.0f * Math::sqrt(1.0f + m22 - m00 - m11);
                q.x = (m02 + m20) / s;
                q.y = (m12 + m21) / s;
                q.z = 0.25f * s;
                q.w = (m10 - m01) / s;
              }
            }
            return q.normalize();
          }

          /*
            *  @brief Converts the quaternion to axis-angle representation.
            *  @param axis Output axis vector.
            *  @param angle_rad Output angle in radians.
          */
          inline void toAxisAngle(Vectors::Vector3& axis, float& angle_rad) const {
            Quaternion q_normalized = this->normalized();

            if (q_normalized.w > 1.0f - Math::EPSILON) {
              axis = Vectors::Vector3::UnitX();
              angle_rad = 0.0f;
              return;
            }
            if (q_normalized.w < -1.0f + Math::EPSILON) {
              axis = Vectors::Vector3::UnitX();
              angle_rad = Math::PI;
              return;
            }

            angle_rad = 2.0f * Math::acos(q_normalized.w);
            float inv_sin_half_angle = 1.0f / Math::sqrt(1.0f - q_normalized.w * q_normalized.w);

            if (Math::abs(inv_sin_half_angle) < Math::EPSILON) {
              axis = Vectors::Vector3::UnitX();
              return;
            }

            axis.x = q_normalized.x * inv_sin_half_angle;
            axis.y = q_normalized.y * inv_sin_half_angle;
            axis.z = q_normalized.z * inv_sin_half_angle;
            axis.normalize();
          }
        };

        /*
          *  @brief Scalar multiplication operator for quaternion.
          *  @param scalar Scalar value.
          *  @param q Quaternion to multiply.
          *  @return Resulting quaternion.
        */
        inline Quaternion operator*(float scalar, const Quaternion& q) {
          return q * scalar;
        }

        /*
          *  @brief Output stream operator for quaternion.
          *  @param os Output stream.
          *  @param q Quaternion to output.
          *  @return Output stream.
        */
        inline std::ostream& operator<<(std::ostream& os, const Quaternion& q) {
          os << "Quaternion(x:" << q.x << ", y:" << q.y << ", z:" << q.z << ", w:" << q.w << ")";
          return os;
        }

      } 
    } 