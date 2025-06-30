#pragma once
#include "..\Prerequisites.h"

class CVector2
{
public:
	CVector2() { m_x = 0; m_y = 0; };

	CVector2(float x, float y) { m_x = x; m_y = y; };

	// ~CVector2();

  // Arithmetic Operators
	// Add
	CVector2
	operator+(const CVector2& other) const {
		return CVector2(m_x + other.m_x, m_y + other.m_y);
	}

	// Substract
	CVector2
	operator-(const CVector2& other) const {
		return CVector2(m_x - other.m_x, m_y - other.m_y);
	}

	// Multiply
	CVector2
	operator*(const CVector2& other) const {
		return CVector2(m_x * other.m_x, m_y * other.m_y);
	}

  // Multiply by scalar
	CVector2
	operator*(float scalar) const {
		return CVector2(m_x * scalar, m_y * scalar);
  }
	
	// Divide
	CVector2
	operator/(const CVector2& other) const {
		return CVector2(m_x / other.m_x, m_y / other.m_y);
	}

  // Divide by scalar
	CVector2
	operator/(float scalar) const {
		return CVector2(m_x / scalar, m_y / scalar);
  }

	// In place
	// Add
	CVector2&
	operator+=(const CVector2& other) {
    m_x += other.m_x;
    m_y += other.m_y;
		return *this;
	}

	// Substract
	CVector2&
	operator-=(const CVector2& other) {
		m_x -= other.m_x;
		m_y -= other.m_y;
		return *this;
	}

	// Multiply
	CVector2&
	operator*=(const CVector2& other) {
		m_x *= other.m_x;
		m_y *= other.m_y;
		return *this;
	}

	// Divide
	CVector2&
	operator/=(const CVector2& other) {
		m_x /= other.m_x;
		m_y /= other.m_y;
		return *this;
	}

	// Comparaciones
	// Equals
	bool
	operator==(const CVector2& other) const {
		return (m_x == other.m_x && m_y == other.m_y);
  }

	// Different from
	bool
	operator!=(const CVector2& other) const {
		return (m_x != other.m_x || m_y != other.m_y);
  }

	// Access from index
  float& 
	operator[](int index) {
		if (index == 0) return m_x;
		else if (index == 1) return m_y;
		else throw std::out_of_range("Index out of range for CVector2");
  }

  // Geometric functions
	// Length
	float
	length(const CVector2& other) const {
		return std::sqrt((other.m_x * other.m_x) + (other.m_y * other.m_y));
	}

  // Squared Length
	float 
	squaredLength(const CVector2& other) const {
    return (other.m_x * other.m_x) + (other.m_y * other.m_y);
	}

  // Scalar Product
	float 
	dotProduct(const CVector2& a, const CVector2& b) const {
    return (a.m_x * b.m_x) + (a.m_y * b.m_y);
	}

  // Cross Product
	float
	crossProduct(const CVector2& a, const CVector2& b) const {
		return (a.m_x * b.m_y) - (a.m_y * b.m_x);
	}

  // Normalize
	CVector2
	normalize(const CVector2& other) const {
    return CVector2(other.m_x / other.length(other), 
										other.m_y / other.length(other));
	}

  // Normalize in place
	CVector2
	normalize(CVector2& other) {
		return CVector2(other.m_x / other.length(other),
			other.m_y / other.length(other));
	}

	// Static functions
  // Returns the distance between two vectors
	static float 
	distance(const CVector2& a, const CVector2& b) {
    return (b - a).length(b - a);
	}

  // Linear Interpolation
  static CVector2
	lerp(const CVector2& a, const CVector2& b, float t) {
    return a + (b - a) * t;
	}

	// Zero Vector
	static CVector2 Zero() {
		return CVector2(0.0f, 0.0f);
	}

	// Unit Vector
	static CVector2 Unit() {
		return CVector2(1.0f, 1.0f);
	}

private:
	float m_x;
  float m_y;
};