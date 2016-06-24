#pragma once

#include <ostream>

namespace Shard
{
	namespace Maths
	{
		template <typename T>
		struct Vector4
		{
		public:
			T x, y, z, w;

		public:
			// Constructors
			Vector4()
				: x(0), y(0), z(0), w(0)
			{
			}

			Vector4(T x, T y, T z, T w)
				: x(x), y(y), z(z), w(w)
			{
			}

			// Member operations
			Vector4& Add(const Vector4& other)
			{
				x += other.x;
				y += other.y;
				z += other.z;
				w += other.w;

				return *this;
			}

			Vector4& Subtract(const Vector4& other)
			{
				x -= other.x;
				y -= other.y;
				z -= other.z;
				w -= other.w;

				return *this;
			}

			Vector4& Multiply(const Vector4& other)
			{
				x *= other.x;
				y *= other.y;
				z *= other.z;
				w *= other.w;

				return *this;
			}

			Vector4& Divide(const Vector4& other)
			{
				x /= other.x;
				y /= other.y;
				z /= other.z;
				w /= other.w;

				return *this;
			}

			inline T Dot(const Vector4& other) const
			{
				return x * other.x + y * other.y + z * other.z + w * other.w;
			}

			inline T Length() const
			{
				return std::sqrt(x * x + y * y + z * z + w * w);
			}

			Vector4& Normalize()
			{
				T l = Length();

				x /= l;
				y /= l;
				z /= l;
				w /= l;

				return *this;
			}

			Vector4 Normalized() const
			{
				T l = Length();

				return Vector4(x / l, y / l, z / l, w / l);
			}

			// Operators
			friend Vector4 operator+(const Vector4& left, const Vector4& right)
			{
				return Vector4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
			}

			friend Vector4 operator-(const Vector4& left, const Vector4& right)
			{
				return Vector4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
			}

			friend Vector4 operator*(const Vector4& left, const Vector4& right)
			{
				return Vector4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
			}

			friend Vector4 operator/(const Vector4& left, const Vector4& right)
			{
				return Vector4(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
			}

			// Compound operators
			Vector4& operator+=(const Vector4& other)
			{
				return Add(other);
			}

			Vector4& operator-=(const Vector4& other)
			{
				return Subtract(other);
			}

			Vector4& operator*=(const Vector4& other)
			{
				return Multiply(other);
			}

			Vector4& operator/=(const Vector4& other)
			{
				return Divide(other);
			}

			bool operator==(const Vector4& other) const
			{
				return x == other.x && y == other.y && z == other.z && w == other.w;
			}

			bool operator!=(const Vector4& other) const
			{
				return !(*this == other);
			}

			// Output stream operator
			friend std::ostream& operator<<(std::ostream& stream, const Vector4& vec)
			{
				stream << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << ", w: " << vec.w;
				return stream;
			}
		};

		typedef Vector4<int> Vector4i;
		typedef Vector4<float> Vector4f;
		typedef Vector4<double> Vector4d;
	}
}