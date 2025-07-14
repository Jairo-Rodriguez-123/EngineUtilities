#pragma once
namespace EngineUtilities {
namespace Math {

/*
* @brief Mathematical constant PI (?), ratio of a circle's circumference to its diameter.
*/
const 
  float PI = 3.14159265358979323846f;
/*
  * @brief Mathematical constant HALF_PI (?/2), half of PI.
*/
const 
  float HALF_PI = PI * 0.5f;
/*
  * @brief Mathematical constant TWO_PI (2?), double of PI.
*/
const 
  float TWO_PI = PI * 2.0f;
/*
  * @brief Mathematical constant E, base of the natural logarithm.
*/
const 
  float E = 2.71828182845904523536f;

/*
* @brief Small epsilon value for floating point comparisons.
*/
const 
  float EPSILON = 0.00001f; 

/*
* @brief Returns the absolute value of a float.
*/
inline 
  float abs(float val) {
    return (val < 0.0f) ? -val : val;
  }

/*
* @brief Checks if two floats are approximately equal using EPSILON.
*/
inline 
  bool approxEqual(float a, float b) {
    return abs(a - b) < EPSILON;
  }

/*
* @brief Returns the maximum of two float values.
*/
inline 
  float EMax(float a, float b) {
    return a > b ? a : b;
  }

/*
* @brief Returns the minimum of two float values.
*/
inline 
  float EMin(float a, float b) {
    return a < b ? a : b;
  }

/*
* @brief Calculates the power of a base raised to an integer exponent.
*/
inline 
  float power(float base, int exp) {
    if (exp == 0) return 1.0f;
     if (approxEqual(base, 0.0f)) return 0.0f;

  float result = 1.0f;
    int abs_exp = abs(exp);
      for (int i = 0; i < abs_exp; ++i) {
        result *= base;
      }
      if (exp < 0) {
        return 1.0f / result;
      }
      return result;
    }

/*
* @brief Calculates the factorial of an integer n.
*/
inline 
  long long factorial(int n) {
    long long res = 1;
      for (int i = 2; i <= n; ++i) {
       res *= i;
      }
      return res;
    }

/*
* @brief Normalizes an angle in radians to the range [-PI, PI].
*/
inline 
  float normalizeAngle(float angle_rad) {
   angle_rad = angle_rad - TWO_PI * floor(angle_rad / TWO_PI);
    if (angle_rad > PI) {
      angle_rad -= TWO_PI;
      }
    if (angle_rad <= -PI) { 
      angle_rad += TWO_PI;
      }
      return angle_rad;
    }

/*
* @brief Calculates the sine of an angle in radians using Taylor series.
*/
inline 
  float sin(float angle_rad) {
    angle_rad = normalizeAngle(angle_rad); 

  float result = 0.0f;
  float x_pow = angle_rad;
  int sign = 1;
   for (int n = 1; n <= 13; n += 2) { 
    result += sign * x_pow / static_cast<float>(factorial(n));
      x_pow *= (angle_rad * angle_rad); 
        sign *= -1;
   }
    return result;
    }

/*
* @brief Calculates the cosine of an angle in radians using Taylor series.
*/
inline 
  float cos(float angle_rad) {
    angle_rad = normalizeAngle(angle_rad); 
    float result = 0.0f;
     float x_pow = 1.0f;
      int sign = 1;

      for (int n = 0; n <= 12; n += 2) { 
       result += sign * x_pow / static_cast<float>(factorial(n));
       x_pow *= (angle_rad * angle_rad);
       sign *= -1;
      }
      return result;
    }

/*
* @brief Calculates the square root of a float using the Babylonian method.
*/
inline 
  float sqrt(float val) {
    if (val < 0.0f) return 0.0f;
    if (approxEqual(val, 0.0f)) return 0.0f;

  float x = val;
  float y = 1.0f;
    for (int i = 0; i < 15; ++i) { 
      x = (x + y) / 2.0f;
      y = val / x;
    }
    return x;
    }

/*
* @brief Calculates the arctangent of x using Taylor series.
*/
inline 
  float atan(float x) {
    if (x > 1.0f) return HALF_PI - atan(1.0f / x);
    if (x < -1.0f) return -HALF_PI - atan(1.0f / x);

   float result = 0.0f;
   float x_pow = x;
   int sign = 1;
     
    for (int n = 1; n <= 25; n += 2) { // 1, 3, 5, ..., 25
      result += sign * x_pow / static_cast<float>(n);
      x_pow *= (x * x);
      sign *= -1;
    }
    return result;
    }

/*
* @brief Calculates the arctangent of y/x considering the quadrant.
*/
inline 
  float atan2(float y, float x) {
    if (approxEqual(x, 0.0f)) {
      if (approxEqual(y, 0.0f)) return 0.0f; 
        return (y > 0) ? HALF_PI : -HALF_PI;
    }

  float angle = atan(y / x);

    if (x < 0.0f) {
      if (y >= 0.0f) return angle + PI;
        else return angle - PI;
    }
      return angle; 
    }

/*
* @brief Calculates the arcsine of x using arctangent and square root.
*/
inline 
  float asin(float x) {
    if (x > 1.0f - EPSILON) return HALF_PI;
    if (x < -1.0f + EPSILON) return -HALF_PI;

float denom_sq = 1.0f - x * x;
    if (approxEqual(denom_sq, 0.0f)) {
      return (x > 0) ? HALF_PI : -HALF_PI;
      }
      return atan(x / sqrt(denom_sq));
    }

/*
*  @brief Calculates the arccosine of x using arcsine.
*/
inline 
  float acos(float x) {
    if (x > 1.0f - EPSILON) return 0.0f;
     if (x < -1.0f + EPSILON) return PI;
      return HALF_PI - asin(x);
    }

/*
*  @brief Converts degrees to radians.
*/
inline 
  float radians(float degrees) {
    return degrees * (PI / 180.0f);
  }

/*
* @brief Converts radians to degrees.
*/
inline 
  float degrees(float radians) {
    return radians * (180.0f / PI);
  }

/*
* @brief Returns the largest integer less than or equal to val.
*/
inline 
  float floor(float val) {
    long long i = (long long)val;
      if (val < 0 && val != i) {
        return (float)(i - 1);
      }
        return (float)i;
    }

/*
* @brief Returns the smallest integer greater than or equal to val.
*/
inline float ceil(float val) {
  long long i = (long long)val;
    if (val > 0 && val != i) {
       return (float)(i + 1);
    }
      return (float)i;
   }

/*
* @brief Rounds val to the nearest integer.
*/
inline 
  float round(float val) {
    return floor(val + 0.5f);
  }
 } 
}