// EngineUtilities/Vectors/Vector2.h
#pragma once
#include "EngineMath.h"
#include "EngineMath.h" // La ruta de inclusión ahora es relativa a la carpeta raíz de EngineUtilities

namespace EngineUtilities {
namespace Vectors {

    /**
     * @brief Estructura que representa un vector 2D.
     * Contiene componentes x e y, y métodos para operaciones comunes de vectores.
     */
    struct Vector2 {
        float x; ///< El componente X del vector.
        float y; ///< El componente Y del vector.

        /**
         * @brief Constructor por defecto. Inicializa el vector a (0.0f, 0.0f).
         */
        inline Vector2() : x(0.0f), y(0.0f) {}

        /**
         * @brief Constructor que inicializa el vector con valores específicos.
         * @param inX El valor inicial para el componente X.
         * @param inY El valor inicial para el componente Y.
         */
        inline Vector2(float inX, float inY) : x(inX), y(inY) {}

        // --- Operadores de Asignación ---

        /**
         * @brief Operador de asignación por copia.
         * @param other El vector 2D a copiar.
         * @return Una referencia a este vector después de la asignación.
         */
        inline Vector2& operator=(const Vector2& other) {
            x = other.x;
            y = other.y;
            return *this;
        }

        // --- Operadores Aritméticos (Vector + Vector) ---

        /**
         * @brief Suma dos vectores 2D.
         * @param other El vector a sumar.
         * @return Un nuevo vector 2D que es la suma de ambos.
         */
        inline Vector2 operator+(const Vector2& other) const {
            return Vector2(x + other.x, y + other.y);
        }

        /**
         * @brief Resta dos vectores 2D.
         * @param other El vector a restar.
         * @return Un nuevo vector 2D que es la resta de ambos.
         */
        inline Vector2 operator-(const Vector2& other) const {
            return Vector2(x - other.x, y - other.y);
        }

        // --- Operadores Aritméticos (Vector * Escalar / Vector / Escalar) ---

        /**
         * @brief Multiplica el vector por un escalar.
         * @param scalar El valor escalar por el que multiplicar.
         * @return Un nuevo vector 2D escalado.
         */
        inline Vector2 operator*(float scalar) const {
            return Vector2(x * scalar, y * scalar);
        }

        /**
         * @brief Divide el vector por un escalar.
         * @param scalar El valor escalar por el que dividir.
         * @return Un nuevo vector 2D escalado.
         */
        inline Vector2 operator/(float scalar) const {
            // Considerar manejo de división por cero si 'scalar' puede ser 0
            if (scalar != 0.0f) {
                return Vector2(x / scalar, y / scalar);
            }
            return Vector2(); // Retorna un vector nulo o maneja el error
        }
        
        // --- Operadores de Asignación Compuesta ---

        /**
         * @brief Suma un vector a este vector y asigna el resultado.
         * @param other El vector a sumar.
         * @return Una referencia a este vector después de la operación.
         */
        inline Vector2& operator+=(const Vector2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        /**
         * @brief Resta un vector a este vector y asigna el resultado.
         * @param other El vector a restar.
         * @return Una referencia a este vector después de la operación.
         */
        inline Vector2& operator-=(const Vector2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        /**
         * @brief Multiplica este vector por un escalar y asigna el resultado.
         * @param scalar El valor escalar por el que multiplicar.
         * @return Una referencia a este vector después de la operación.
         */
        inline Vector2& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        /**
         * @brief Divide este vector por un escalar y asigna el resultado.
         * @param scalar El valor escalar por el que dividir.
         * @return Una referencia a este vector después de la operación.
         */
        inline Vector2& operator/=(float scalar) {
            if (scalar != 0.0f) {
                x /= scalar;
                y /= scalar;
            }
            return *this;
        }

        // --- Comparación ---

        /**
         * @brief Compara si dos vectores 2D son aproximadamente iguales.
         * @param other El vector a comparar.
         * @return True si los vectores son aproximadamente iguales, false en caso contrario.
         */
        inline bool operator==(const Vector2& other) const {
            return Math::approxEqual(x, other.x) && Math::approxEqual(y, other.y);
        }

        /**
         * @brief Compara si dos vectores 2D son diferentes.
         * @param other El vector a comparar.
         * @return True si los vectores son diferentes, false en caso contrario.
         */
        inline bool operator!=(const Vector2& other) const {
            return !(*this == other);
        }

        // --- Métodos de Vector ---

        /**
         * @brief Calcula el producto punto (dot product) de este vector con otro.
         * @param other El otro vector 2D.
         * @return El resultado escalar del producto punto.
         */
        inline float dot(const Vector2& other) const {
            return x * other.x + y * other.y;
        }

        /**
         * @brief Calcula la magnitud (longitud) de este vector.
         * @return La magnitud del vector.
         */
        inline float magnitude() const {
            return Math::sqrt(x * x + y * y);
        }

        /**
         * @brief Calcula la magnitud al cuadrado (longitud al cuadrado) de este vector.
         * Es más rápido que magnitude() ya que evita la operación de raíz cuadrada.
         * @return La magnitud al cuadrado del vector.
         */
        inline float squareMagnitude() const {
            return x * x + y * y;
        }

        /**
         * @brief Normaliza este vector, convirtiéndolo en un vector unitario.
         * Modifica el vector actual.
         * @return Una referencia a este vector normalizado.
         */
        inline Vector2& normalize() {
            float mag = magnitude();
            if (mag > Math::EPSILON) { // Evitar división por cero o por un número muy pequeño
                x /= mag;
                y /= mag;
            }
            return *this;
        }

        /**
         * @brief Retorna un vector unitario en la misma dirección que este vector, sin modificar el original.
         * @return Un nuevo vector 2D normalizado.
         */
        inline Vector2 normalized() const {
            float mag = magnitude();
            if (mag > Math::EPSILON) {
                return Vector2(x / mag, y / mag);
            }
            return Vector2(); // Retorna un vector nulo si la magnitud es cero o muy pequeña
        }

        /**
         * @brief Calcula la distancia entre este vector (punto) y otro vector (punto).
         * @param other El otro vector 2D (punto).
         * @return La distancia euclidiana entre los dos puntos.
         */
        inline float distance(const Vector2& other) const {
            float dx = x - other.x;
            float dy = y - other.y;
            return Math::sqrt(dx * dx + dy * dy);
        }

        /**
         * @brief Calcula la distancia al cuadrado entre este vector (punto) y otro vector (punto).
         * Más eficiente que distance() ya que evita la raíz cuadrada.
         * @param other El otro vector 2D (punto).
         * @return La distancia al cuadrado entre los dos puntos.
         */
        inline float squareDistance(const Vector2& other) const {
            float dx = x - other.x;
            float dy = y - other.y;
            return dx * dx + dy * dy;
        }
    };

    // --- Sobrecarga de operador de multiplicación escalar para permitir escalar * Vector2 ---
    /**
     * @brief Multiplica un escalar por un vector 2D.
     * @param scalar El valor escalar.
     * @param vec El vector 2D.
     * @return Un nuevo vector 2D escalado.
     */
  inline Vector2 operator*(float scalar, const Vector2& vec) {
   return Vector2(vec.x * scalar, vec.y * scalar);
    }
  inline std::ostream& operator<<(std::ostream& os, const Vector2& v) {
   os << "(" << v.x << ", " << v.y << ")";
    return os;
    }

} // namespace Vectors
} // namespace EngineUtilities#pragma once
