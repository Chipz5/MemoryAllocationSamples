#pragma once

namespace Engine {
	class Vector3
	{
	public:
		Vector3() { }
		// standard constructor
		inline Vector3(float i_x, float i_y, float i_z);
		inline Vector3(float i_vec[3]);

		// copy constructor - for completeness
		inline Vector3(const Vector3& i_rhs);

		// assignment operator
		inline Vector3& operator=(const Vector3& i_rhs);

		// element accessors
		// - get individual element
		float x(void) const;
		float y(void) const;
		float z(void) const;
		// - set individual element
		void x(float i_x);
		void y(float i_y);
		void z(float i_z);

		Vector3& operator+=(const Vector3& i_rhs);
		Vector3& operator-=(const Vector3& i_rhs);

		Vector3& operator*=(float i_val);
		Vector3& operator/=(float i_val);

		// negate
		Vector3 operator-(void);

		void Normalize();
		Vector3 Normalized() const;

		float Length() const;
		float LengthSq() const;

		// - ( 0.0f, 0.0f, 0.0f )
		static const Vector3 Zero;
	private:
		float	m_x, m_y, m_z;
	};

	inline Vector3 operator+(const Vector3& i_lhs, const Vector3& i_rhs);
	inline Vector3 operator-(const Vector3& i_lhs, const Vector3& i_rhs);

	inline Vector3 operator*(const Vector3& i_lhs, const Vector3& i_rhs);
	inline Vector3 operator*(const Vector3& i_lhs, float i_rhs);
	inline Vector3 operator*(float i_lhs, const Vector3& i_rhs);
	inline Vector3 operator/(const Vector3& i_lhs, float i_rhs);

	inline bool operator==(const Vector3& i_lhs, const Vector3& i_rhs);
	inline bool operator!=(const Vector3& i_lhs, const Vector3& i_rhs);

	inline float dot(const Vector3& i_lhs, const Vector3& i_rhs);
	inline Vector3 cross(const Vector3& i_lhs, const Vector3& i_rhs);

} // namespace Engine

#include "Vector3.inl"