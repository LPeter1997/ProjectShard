#pragma once

#include <type_traits>
#include <ostream>
#include "../Types.h"
#include "Vector3.h"
#include "Trigonometry.h"

namespace Shard
{
	namespace Maths
	{
		// Matrix of any size
		template <uint N, uint M, typename T>
		struct Matrix
		{
		public:
			T Elements[N * M];

		public:
			// Constructors
			Matrix()
			{
				for (uint i = 0; i < N * M; i++)
					Elements[i] = 0;
			}

			Matrix(T diag)
				: Matrix()
			{
				for (uint i = 0; i < N; i++)
					Elements[i + i * N] = diag;
			}

			// Null matrix
			static inline Matrix<N, M, T> Null()
			{
				return Matrix<N, M, T>();
			}

			// Identity for square matrices only
			template <typename = typename std::enable_if<N == M>::type>
			static inline Matrix<N, N, T> Identity()
			{
				return Matrix<N, N, T>(1);
			}

			// Member operations
			inline Matrix<N, M, T>& Add(const Matrix<N, M, T>& other)
			{
				for (uint i = 0; i < N * M; i++)
					Elements[i] += other.Elements[i];

				return *this;
			}

			inline Matrix<N, M, T>& Subtract(const Matrix<N, M, T>& other)
			{
				for (uint i = 0; i < N * M; i++)
					Elements[i] -= other.Elements[i];

				return *this;
			}

			inline Matrix<N, M, T>& Multiply(const T scalar)
			{
				for (uint i = 0; i < N * M; i++)
					Elements[i] *= scalar;

				return *this;
			}

			template <uint K>
			inline Matrix<M, K, T> Multiply(const Matrix<K, N, T>& other) const
			{
				Matrix<M, K, T> result;
				for (uint y = 0; y < M; y++)
				{
					for (uint x = 0; x < K; x++)
					{
						T sum = 0;
						for (uint i = 0; i < N; i++)
							sum += Elements[i + y * N] * other.Elements[x + i * M];

						result.Elements[x + y * K] = sum;
					}
				}

				return result;
			}

			// Multiply it with a 3D vector as it was (x, y, z, 0) for 3D matrix only
			template <typename = typename std::enable_if<(N == M) && (N == 4)>::type>
			inline Vector3<T> Multiply(const Vector3<T>& other) const
			{
				return Vector3<T>
				(
					Elements[0] * other.x + Elements[4] * other.y + Elements[8] * other.z + Elements[12],
					Elements[1] * other.x + Elements[5] * other.y + Elements[9] * other.z + Elements[13],
					Elements[2] * other.x + Elements[6] * other.y + Elements[10] * other.z + Elements[14]
				);
			}

			// Multiply it with a 2D vector for 2D 2x2 matrix only
			template <typename = typename std::enable_if<(N == M) && (N == 2)>::type>
			inline Vector2<T> Multiply(const Vector2<T>& other) const
			{
				return Vector2<T>
				(
					Elements[0] * other.x + Elements[1] * other.y,
					Elements[2] * other.x + Elements[3] * other.y,
				);
			}

			Matrix<M, N, T> Transposed() const
			{
				Matrix<M, N, T> ret;
				for (unsigned int i = 0; i < N; i++)
				{
					for (unsigned int j = 0; j < M; j++)
					{
						ret.Elements[j + i * M] = Elements[i + j * N];
					}
				}

				return ret;
			}

			// In place transpose for square matrices only
			template <typename = typename std::enable_if<N == M>::type>
			Matrix<N, N, T>& Transpose()
			{
				for (unsigned int i = 0; i < N; i++)
				{
					for (unsigned int j = 0; j < N; j++)
					{
						T tmp = Elements[i + j * N];
						Elements[i + j * N] = Elements[j + i * N];
						Elements[i + j* N] = tmp;
					}
				}

				return *this;
			}

			// Self transformation
			template <typename = typename std::enable_if<(N == M) && (N == 4)>::type>
			Matrix<N, M, T>& Translate(const Vector3<T>& other)
			{
				Elements[0 + 3 * 4] += Elements[0] * other.x + Elements[0 + 1 * 4] * other.y + Elements[0 + 2 * 4] * other.z;
				Elements[1 + 3 * 4] += Elements[1] * other.x + Elements[1 + 1 * 4] * other.y + Elements[1 + 2 * 4] * other.z;
				Elements[2 + 3 * 4] += Elements[2] * other.x + Elements[2 + 1 * 4] * other.y + Elements[2 + 2 * 4] * other.z;
				Elements[3 + 3 * 4] += Elements[3] * other.x + Elements[3 + 1 * 4] * other.y + Elements[3 + 2 * 4] * other.z;

				return *this;
			}

			template <typename = typename std::enable_if<(N == M) && (N == 4)>::type>
			Matrix<N, M, T>& Scale(const Vector3<T>& scale)
			{
				Elements[0 + 0 * 4] *= scale.x;
				Elements[1 + 0 * 4] *= scale.x;
				Elements[2 + 0 * 4] *= scale.x;
				Elements[3 + 0 * 4] *= scale.x;
				Elements[0 + 1 * 4] *= scale.y;
				Elements[1 + 1 * 4] *= scale.y;
				Elements[2 + 1 * 4] *= scale.y;
				Elements[3 + 1 * 4] *= scale.y;
				Elements[0 + 2 * 4] *= scale.z;
				Elements[1 + 2 * 4] *= scale.z;
				Elements[2 + 2 * 4] *= scale.z;
				Elements[3 + 2 * 4] *= scale.z;

				return *this;
			}

			template <typename = typename std::enable_if<(N == M) && (N == 4)>::type>
			Matrix<N, M, T>& Rotate(T angle, const Vector3<T>& axis)
			{
				double r = ToRadians(angle);
				double c = cos(r);
				double s = sin(r);
				double omc = 1 - c;

				T x = axis.x;
				T y = axis.y;
				T z = axis.z;

				T f00 = x * x * omc + c;
				T f01 = x * y * omc + z * s;
				T f02 = x * z * omc - y * s;

				T f10 = x * y * omc - z * s;
				T f11 = y * y * omc + c;
				T f12 = y * z * omc + x * s;

				T f20 = x * z * omc + y * s;
				T f21 = y * z * omc - x * s;
				T f22 = z * z * omc + c;

				T t00 = Elements[0 + 0 * 4] * f00 + Elements[0 + 1 * 4] * f01 + Elements[0 + 2 * 4] * f02;
				T t01 = Elements[1 + 0 * 4] * f00 + Elements[1 + 1 * 4] * f01 + Elements[1 + 2 * 4] * f02;
				T t02 = Elements[2 + 0 * 4] * f00 + Elements[2 + 1 * 4] * f01 + Elements[2 + 2 * 4] * f02;
				T t03 = Elements[3 + 0 * 4] * f00 + Elements[3 + 1 * 4] * f01 + Elements[3 + 2 * 4] * f02;
				T t10 = Elements[0 + 0 * 4] * f10 + Elements[0 + 1 * 4] * f11 + Elements[0 + 2 * 4] * f12;
				T t11 = Elements[1 + 0 * 4] * f10 + Elements[1 + 1 * 4] * f11 + Elements[1 + 2 * 4] * f12;
				T t12 = Elements[2 + 0 * 4] * f10 + Elements[2 + 1 * 4] * f11 + Elements[2 + 2 * 4] * f12;
				T t13 = Elements[3 + 0 * 4] * f10 + Elements[3 + 1 * 4] * f11 + Elements[3 + 2 * 4] * f12;

				Elements[0 + 2 * 4] = Elements[0 + 0 * 4] * f20 + Elements[0 + 1 * 4] * f21 + Elements[0 + 2 * 4] * f22;
				Elements[1 + 2 * 4] = Elements[1 + 0 * 4] * f20 + Elements[1 + 1 * 4] * f21 + Elements[1 + 2 * 4] * f22;
				Elements[2 + 2 * 4] = Elements[2 + 0 * 4] * f20 + Elements[2 + 1 * 4] * f21 + Elements[2 + 2 * 4] * f22;
				Elements[3 + 2 * 4] = Elements[3 + 0 * 4] * f20 + Elements[3 + 1 * 4] * f21 + Elements[3 + 2 * 4] * f22;

				Elements[0 + 0 * 4] = t00;
				Elements[1 + 0 * 4] = t01;
				Elements[2 + 0 * 4] = t02;
				Elements[3 + 0 * 4] = t03;
				Elements[0 + 1 * 4] = t10;
				Elements[1 + 1 * 4] = t11;
				Elements[2 + 1 * 4] = t12;
				Elements[3 + 1 * 4] = t13;

				return *this;
			}

			// Friend operators
			inline friend Matrix<N, M, T> operator+(Matrix<N, M, T> left, const Matrix<M, N, T>& right)
			{
				return left.Add(right);
			}

			inline friend Matrix<N, M, T> operator-(Matrix<N, M, T> left, const Matrix<M, N, T>& right)
			{
				return left.Subtract(right);
			}

			inline friend Matrix<N, M, T> operator*(Matrix<N, M, T> left, const T scalar)
			{
				return left.Multiply(scalar);
			}

			inline friend Matrix<N, M, T> operator*(const T scalar, Matrix<N, M, T> left)
			{
				return left.Multiply(scalar);
			}

			template <typename = typename std::enable_if<(N == M) && (N == 4)>::type>
			inline friend Vector3<T> operator*(const Matrix<4, 4, T>& left, const Vector3<T>& right)
			{
				return left.Multiply(right);
			}

			template <typename = typename std::enable_if<(N == M) && (N == 2)>::type>
			inline friend Vector2<T> operator*(const Matrix<2, 2, T>& left, const Vector2<T>& right)
			{
				return left.Multiply(right);
			}

			template <unsigned int K>
			inline friend Matrix<M, K, T> operator*(const Matrix<N, M, T>& left, const Matrix<K, N, T>& right)
			{
				return left.Multiply(right);
			}

			// Compound operators
			inline Matrix<N, M, T>& operator+=(const Matrix<M, N, T>& other)
			{
				return Add(other);
			}

			inline Matrix<N, M, T>& operator-=(const Matrix<M, N, T>& other)
			{
				return Subtract(other);
			}

			inline Matrix<N, M, T>& operator*=(const T scalar)
			{
				return Multiply(other);
			}

			template <unsigned int K>
			inline Matrix<M, K, T>& operator*=(const Matrix<K, N, T>& other)
			{
				return Multiply(other);
			}

			inline bool operator==(const Matrix<N, M, T>& other) const
			{
				for (unsigned int i = 0; i < N * M; i++)
					if (Elements[i] != other.Elements[i])
						return false;

				return true;
			}

			inline bool operator!=(const Matrix<N, M, T>& other) const
			{
				for (unsigned int i = 0; i < N * M; i++)
					if (Elements[i] != other.Elements[i])
						return true;

				return false;
			}

			// Output stream operator
			friend std::ostream& operator<<(std::ostream& stream, const Matrix<N, M, T>& mat)
			{
				stream << "[";
				for (unsigned int y = 0; y < M; y++)
				{
					for (unsigned int x = 0; x < N; x++)
					{
						stream << mat.Elements[x + y * N];
						if (!(y == M - 1 && x == N - 1))
							stream << ',';
					}
					if (y < M - 1)
						stream << std::endl;
				}
				stream << "]";
				return stream;
			}

			// 3d transformation matrices (Matrix4)
			template <typename = typename std::enable_if<(N == M) && (N == 4)>::type>
			static Matrix<4, 4, T> Translation(const Vector3<T>& trans)
			{
				Matrix<4, 4, T> result(1);

				result.Elements[0 + 3 * 4] = trans.x;
				result.Elements[1 + 3 * 4] = trans.y;
				result.Elements[2 + 3 * 4] = trans.z;

				return result;
			}

			template <typename = typename std::enable_if<(N == M) && (N == 4)>::type>
			static Matrix<4, 4, T> Scaling(const Vector3<T>& scale)
			{
				Matrix<4, 4, T> result(1);

				result.Elements[0 + 0 * 4] = scale.x;
				result.Elements[1 + 1 * 4] = scale.y;
				result.Elements[2 + 2 * 4] = scale.z;

				return result;
			}

			// 2D rotation
			template <typename = typename std::enable_if<(N == M) && (N == 2)>::type>
			static Matrix<2, 2, T> Rotation2D(T radians)
			{
				Matrix<2, 2, T> result;

				float c = std::cos(radians);
				float s = std::sin(radians);

				result.Elements[0] = c;
				result.Elements[1] = -s;
				result.Elements[2] = s;
				result.Elements[3] = c;

				return result;
			}

			template <typename = typename std::enable_if<(N == M) && (N == 4)>::type>
			static Matrix<4, 4, T> Rotation(T angle, const Vector3<T>& axis)
			{
				Matrix<4, 4, T> result(1);

				double r = ToRadians(angle);
				double c = std::cos(r);
				double s = std::sin(r);
				double omc = 1 - c;

				T x = axis.x;
				T y = axis.y;
				T z = axis.z;

				result.Elements[0 + 0 * 4] = x * x * omc + c;
				result.Elements[1 + 0 * 4] = y * x * omc + z * s;
				result.Elements[2 + 0 * 4] = x * z * omc - y * s;

				result.Elements[0 + 1 * 4] = x * y * omc - z * s;
				result.Elements[1 + 1 * 4] = y * y * omc + c;
				result.Elements[2 + 1 * 4] = y * z * omc + x * s;

				result.Elements[0 + 2 * 4] = x * z * omc + y * s;
				result.Elements[1 + 2 * 4] = y * z * omc - x * s;
				result.Elements[2 + 2 * 4] = z * z * omc + c;

				return result;
			}

			template <typename = typename std::enable_if<(N == M) && (N == 4)>::type>
			static Matrix<4, 4, T> Orthographic(T left, T right, T bottom, T top, T near, T far)
			{
				Matrix<4, 4, T> result(1);

				result.Elements[0 + 0 * 4] = 2 / (right - left);
				result.Elements[1 + 1 * 4] = 2 / (top - bottom);
				result.Elements[2 + 2 * 4] = 2 / (near - far);

				result.Elements[0 + 3 * 4] = (left + right) / (left - right);
				result.Elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
				result.Elements[2 + 3 * 4] = (far + near) / (far - near);

				return result;
			}

			template <typename = typename std::enable_if<(N == M) && (N == 4)>::type>
			static Matrix<4, 4, T> Perspective(T fov, T aspectRatio, T near, T far)
			{
				Matrix<4, 4, T> result(1);

				T q = 1 / std::tan(ToRadians(0.5 * fov));
				T a = q / aspectRatio;

				T b = (near + far) / (near - far);
				T c = (2 * near * far) / (near - far);

				result.Elements[0 + 0 * 4] = a;
				result.Elements[1 + 1 * 4] = q;
				result.Elements[2 + 2 * 4] = b;
				result.Elements[3 + 2 * 4] = -1;
				result.Elements[2 + 3 * 4] = c;

				return result;
			}
		};

		template <unsigned int N, unsigned int M> using Matrixi = Matrix<N, M, int>;
		template <unsigned int N, unsigned int M> using Matrixf = Matrix<N, M, float>;
		template <unsigned int N, unsigned int M> using Matrixd = Matrix<N, M, double>;

		template <typename T> using Matrix2 = Matrix<2, 2, T>;
		template <typename T> using Matrix3 = Matrix<3, 3, T>;
		template <typename T> using Matrix4 = Matrix<4, 4, T>;

		typedef Matrix2<int> Matrix2i;
		typedef Matrix2<float> Matrix2f;
		typedef Matrix2<double> Matrix2d;

		typedef Matrix3<int> Matrix3i;
		typedef Matrix3<float> Matrix3f;
		typedef Matrix3<double> Matrix3d;

		typedef Matrix4<int> Matrix4i;
		typedef Matrix4<float> Matrix4f;
		typedef Matrix4<double> Matrix4d;
	}
}