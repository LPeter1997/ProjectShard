#pragma once

#include <ostream>

namespace Shard
{
	namespace Maths
	{
		template <typename T>
		struct Vector2
		{
		public:
			T x, y;

		public:
			// Constructors
			Vector2()
				: x(0), y(0)
			{
			}

			Vector2(T x, T y)
				: x(x), y(y)
			{
			}

			// Member operations
			Vector2& Add(const Vector2& other)
			{
				x += other.x;
				y += other.y;

				return *this;
			}

			Vector2& Subtract(const Vector2& other)
			{
				x -= other.x;
				y -= other.y;

				return *this;
			}

			Vector2& Multiply(const Vector2& other)
			{
				x *= other.x;
				y *= other.y;

				return *this;
			}

			Vector2& Divide(const Vector2& other)
			{
				x /= other.x;
				y /= other.y;

				return *this;
			}

			inline T Dot(const Vector2& other) const
			{
				return x * other.x + y * other.y;
			}

			static inline T DotProduct(const Vector2& a, const Vector2& b)
			{
				return a.x * b.x + a.y * b.y;
			}

			static inline T CrossProduct(const Vector2& a, const Vector2& b)
			{
				return a.x * b.y - a.y * b.x;
			}

			static inline Vector2 CrossProduct(T a, const Vector2& b)
			{
				return Vector2(-a * b.y, a * b.x);
			}

			static inline T CrossProduct(const Vector2& v, T a)
			{
				return Vector2(a * v.y, -a * v.x);
			}

			inline T Length() const
			{
				return std::sqrt(x * x + y * y);
			}

			Vector2& Normalize()
			{
				T l = Length();

				x /= l;
				y /= l;

				return *this;
			}

			Vector2 Normalized() const
			{
				T l = Length();

				return Vector2(x / l, y / l);
			}

			// Operators
			friend Vector2 operator+(const Vector2& left, const Vector2& right)
			{
				return Vector2(left.x + right.x, left.y + right.y);
			}

			friend Vector2 operator-(const Vector2& left, const Vector2& right)
			{
				return Vector2(left.x - right.x, left.y - right.y);
			}

			friend Vector2 operator*(const Vector2& left, const Vector2& right)
			{
				return Vector2(left.x * right.x, left.y * right.y);
			}

			friend Vector2 operator/(const Vector2& left, const Vector2& right)
			{
				return Vector2(left.x / right.x, left.y / right.y);
			}

			// Compound operators
			Vector2& operator+=(const Vector2& other)
			{
				return Add(other);
			}

			Vector2& operator-=(const Vector2& other)
			{
				return Subtract(other);
			}

			Vector2& operator*=(const Vector2& other)
			{
				return Multiply(other);
			}

			Vector2& operator/=(const Vector2& other)
			{
				return Divide(other);
			}

			bool operator==(const Vector2& other) const
			{
				return x == other.x && y == other.y;
			}

			bool operator!=(const Vector2& other) const
			{
				return !(*this == other);
			}

			// Output stream operator
			friend std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
			{
				stream << "x: " << vec.x << ", y: " << vec.y;
				return stream;
			}
		};

		typedef Vector2<int> Vector2i;
		typedef Vector2<float> Vector2f;
		typedef Vector2<double> Vector2d;
	}
}