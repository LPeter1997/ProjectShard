#pragma once

#include <ostream>

namespace Shard
{
	namespace Maths
	{
		template <typename T>
		struct Vector3
		{
		public:
			T x, y, z;

		public:
			// Constructors
			Vector3()
				: x(0), y(0), z(0)
			{
			}

			Vector3(T x, T y, T z)
				: x(x), y(y), z(z)
			{
			}

			// Member operations
			Vector3& Add(const Vector3& other)
			{
				x += other.x;
				y += other.y;
				z += other.z;

				return *this;
			}

			Vector3& Subtract(const Vector3& other)
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;

				return *this;
			}

			Vector3& Multiply(const Vector3& other)
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;

				return *this;
			}

			Vector3& Divide(const Vector3& other)
			{
				x /= other.x;
				y /= other.y;
				z /= other.z;

				return *this;
			}

			inline T Dot(const Vector3& other) const
			{
				return x * other.x + y * other.y + z * other.z;
			}

			static inline T DotProduct(const Vector3& a, const Vector3& b)
			{
				return a.x * b.x + a.y * b.y + a.z * b.z;
			}

			inline Vector3& Cross(const Vector3& other)
			{
				T _x = y * other.z - z * other.y;
				T _y = z * other.x - x * other.z;
				T _z = x * other.y - y * other.x;
				x = _x;
				y = _y;
				z = _z;
				return *this;
			}

			inline Vector3 Crossed(const Vector3& other) const
			{
				return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
			}

			static inline Vector3 CrossProduct(const Vector3& a, const Vector3& b)
			{
				return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
			}

			inline T Length() const
			{
				return std::sqrt(x * x + y * y + z * z);
			}

			Vector3& Normalize()
			{
				T l = Length();

				x /= l;
				y /= l;
				z /= l;

				return *this;
			}

			Vector3 Normalized() const
			{
				T l = Length();

				return Vector3(x / l, y / l, z / l);
			}

			// Operators
			friend Vector3 operator+(const Vector3& left, const Vector3& right)
			{
				return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
			}

			friend Vector3 operator-(const Vector3& left, const Vector3& right)
			{
				return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
			}

			friend Vector3 operator*(const Vector3& left, const Vector3& right)
			{
				return Vector3(left.x * right.x, left.y * right.y, left.z * right.z);
			}

			friend Vector3 operator/(const Vector3& left, const Vector3& right)
			{
				return Vector3(left.x / right.x, left.y / right.y, left.z / right.z);
			}

			// Compound operators
			Vector3& operator+=(const Vector3& other)
			{
				return Add(other);
			}

			Vector3& operator-=(const Vector3& other)
			{
				return Subtract(other);
			}

			Vector3& operator*=(const Vector3& other)
			{
				return Multiply(other);
			}

			Vector3& operator/=(const Vector3& other)
			{
				return Divide(other);
			}

			bool operator==(const Vector3& other) const
			{
				return x == other.x && y == other.y && z == other.z;
			}

			bool operator!=(const Vector3& other) const
			{
				return !(*this == other);
			}

			// Output stream operator
			friend std::ostream& operator<<(std::ostream& stream, const Vector3& vec)
			{
				stream << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z;
				return stream;
			}
		};

		typedef Vector3<int> Vector3i;
		typedef Vector3<float> Vector3f;
		typedef Vector3<double> Vector3d;
	}
}