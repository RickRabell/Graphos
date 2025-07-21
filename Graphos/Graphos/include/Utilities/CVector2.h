#pragma once
#include "..\Prerequisites.h"

/*
  *  @class CVector2
  *  @brief Represents a 2D vector with float components and provides common vector operations.
  *
  *  This class encapsulates a two-dimensional vector with floating-point components (x, y).
  *  It provides constructors for initialization, conversion from SFML vector types, and
  *  supports arithmetic operations such as addition, subtraction, multiplication, and division
  *  (both component-wise and with scalars). The class also includes methods for vector length,
  *  squared length, dot and cross products, normalization, distance calculation, and linear
  *  interpolation. Utility static methods are provided for zero and unit vectors.
  *
  *  @note This class is compatible with C++17 and integrates with SFML vector types.
*/
class CVector2 {
public:
	/*
	*  @brief The x component of the vector.
*/
	float m_x;
	/*
		*  @brief The y component of the vector.
	*/
	float m_y;
	/*
		*  @brief Default constructor. Initializes both components to zero.
	*/
	CVector2() { m_x = 0; m_y = 0; };

	/*
		*  @brief Constructs a vector with specified x and y components.
		*  @param x The x component.
		*  @param y The y component.
	*/
	CVector2(float x, float y) { m_x = x; m_y = y; };

	/*
		*  @brief Conversion constructor from sf::Vector2f.
		*  @param v The SFML 2D float vector.
	*/
	CVector2(const sf::Vector2f& v) : m_x(v.x), m_y(v.y) {}

	/*
		*  @brief Conversion constructor from sf::Vector2i.
		*  @param v The SFML 2D integer vector.
	*/
	CVector2(const sf::Vector2i& v) : m_x(static_cast<float>(v.x)), m_y(static_cast<float>(v.y)) {}

	// ~CVector2();

	/*
		*  @brief Adds two vectors.
		*  @param other The vector to add.
		*  @return The result of vector addition.
	*/
	CVector2
	operator+(const CVector2& other) const {
		return CVector2(m_x + other.m_x, m_y + other.m_y);
	}

	/*
		*  @brief Subtracts another vector from this vector.
		*  @param other The vector to subtract.
		*  @return The result of vector subtraction.
	*/
	CVector2
	operator-(const CVector2& other) const {
		return CVector2(m_x - other.m_x, m_y - other.m_y);
	}

	/*
		*  @brief Multiplies two vectors component-wise.
		*  @param other The vector to multiply.
		*  @return The result of component-wise multiplication.
	*/
	CVector2
	operator*(const CVector2& other) const {
		return CVector2(m_x * other.m_x, m_y * other.m_y);
	}

	/*
		*  @brief Multiplies the vector by a scalar.
		*  @param scalar The scalar value.
		*  @return The result of scalar multiplication.
	*/
	CVector2
	operator*(float scalar) const {
		return CVector2(m_x * scalar, m_y * scalar);
	}
	
	/*
		*  @brief Divides this vector by another vector component-wise.
		*  @param other The vector to divide by.
		*  @return The result of component-wise division.
	*/
	CVector2
	operator/(const CVector2& other) const {
		return CVector2(m_x / other.m_x, m_y / other.m_y);
	}

	/*
		*  @brief Divides the vector by a scalar.
		*  @param scalar The scalar value.
		*  @return The result of scalar division.
	*/
	CVector2
	operator/(float scalar) const {
		return CVector2(m_x / scalar, m_y / scalar);
	}

	/*
		*  @brief Adds another vector to this vector in place.
		*  @param other The vector to add.
		*  @return Reference to this vector.
	*/
	CVector2&
	operator+=(const CVector2& other) {
		m_x += other.m_x;
		m_y += other.m_y;
		return *this;
	}

	/*
		*  @brief Subtracts another vector from this vector in place.
		*  @param other The vector to subtract.
		*  @return Reference to this vector.
	*/
	CVector2&
	operator-=(const CVector2& other) {
		m_x -= other.m_x;
		m_y -= other.m_y;
		return *this;
	}

	/*
		*  @brief Multiplies this vector by another vector component-wise in place.
		*  @param other The vector to multiply.
		*  @return Reference to this vector.
	*/
	CVector2&
	operator*=(const CVector2& other) {
		m_x *= other.m_x;
		m_y *= other.m_y;
		return *this;
	}

	/*
		*  @brief Divides this vector by another vector component-wise in place.
		*  @param other The vector to divide by.
		*  @return Reference to this vector.
	*/
	CVector2&
	operator/=(const CVector2& other) {
		m_x /= other.m_x;
		m_y /= other.m_y;
		return *this;
	}

	CVector2&
	operator/=(const float other) {
		m_x /= other;
		m_y /= other;
		return *this;
	}

	/*
		*  @brief Checks if two vectors are equal.
		*  @param other The vector to compare.
		*  @return True if both components are equal, false otherwise.
	*/
	bool
	operator==(const CVector2& other) const {
		return (m_x == other.m_x && m_y == other.m_y);
	}

	/*
		*  @brief Checks if two vectors are not equal.
		*  @param other The vector to compare.
		*  @return True if any component is different, false otherwise.
	*/
	bool
	operator!=(const CVector2& other) const {
		return (m_x != other.m_x || m_y != other.m_y);
	}

	/*
		*  @brief Accesses a component by index.
		*  @param index 0 for x, 1 for y.
		*  @return Reference to the component.
		*  @throws std::out_of_range if index is not 0 or 1.
	*/
	float&
	operator[](int index) {
		if (index == 0) return m_x;
		else if (index == 1) return m_y;
		else throw std::out_of_range("Index out of range for CVector2");
	}

	/*
		*  @brief Calculates the length (magnitude) of a vector.
		*  @param other The vector whose length is calculated.
		*  @return The length of the vector.
	*/
	float
	length(const CVector2& other) const {
		return std::sqrt((other.m_x * other.m_x) + (other.m_y * other.m_y));
	}

	/*
		*  @brief Calculates the squared length of a vector.
		*  @param other The vector whose squared length is calculated.
		*  @return The squared length of the vector.
	*/
	float
	squaredLength(const CVector2& other) const {
		return (other.m_x * other.m_x) + (other.m_y * other.m_y);
	}

	/*
		*  @brief Calculates the dot product of two vectors.
		*  @param a The first vector.
		*  @param b The second vector.
		*  @return The dot product.
	*/
	float
	dotProduct(const CVector2& a, const CVector2& b) const {
		return (a.m_x * b.m_x) + (a.m_y * b.m_y);
	}

	/*
		*  @brief Calculates the cross product of two vectors.
		*  @param a The first vector.
		*  @param b The second vector.
		*  @return The cross product.
	*/
	float
	crossProduct(const CVector2& a, const CVector2& b) const {
		return (a.m_x * b.m_y) - (a.m_y * b.m_x);
	}

	/*
		*  @brief Returns the normalized (unit length) version of a vector.
		*  @param other The vector to normalize.
		*  @return The normalized vector.
	*/
	CVector2
	normalize(const CVector2& other) const {
		return CVector2(other.m_x / other.length(other), 
						other.m_y / other.length(other));
	}

	/*
		*  @brief Normalizes a vector in place.
		*  @param other The vector to normalize.
		*  @return The normalized vector.
	*/
	CVector2
	normalize(CVector2& other) {
		return CVector2(other.m_x / other.length(other),
						other.m_y / other.length(other));
	}

	/*
		*  @brief Calculates the distance between two vectors.
		*  @param a The first vector.
		*  @param b The second vector.
		*  @return The distance between the vectors.
	*/
	static float
	distance(const CVector2& a, const CVector2& b) {
		return (b - a).length(b - a);
	}

	/*
		*  @brief Performs linear interpolation between two vectors.
		*  @param a The start vector.
		*  @param b The end vector.
		*  @param t The interpolation factor (0.0 to 1.0).
		*  @return The interpolated vector.
	*/
	static CVector2
	lerp(const CVector2& a, const CVector2& b, float t) {
		return a + (b - a) * t;
	}

	/*
		*  @brief Returns a zero vector (0, 0).
		*  @return The zero vector.
	*/
	static CVector2 Zero() {
		return CVector2(0.0f, 0.0f);
	}

	/*
		*  @brief Returns a unit vector (1, 1).
		*  @return The unit vector.
	*/
	static CVector2 Unit() {
		return CVector2(1.0f, 1.0f);
	}
};