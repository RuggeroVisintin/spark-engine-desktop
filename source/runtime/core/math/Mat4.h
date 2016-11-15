#ifndef __MAT4_H__
#define __MAT4_H__

#include <cmath>
#include "Vec3.h"

namespace SE
{
    namespace core
    {
        namespace math
		{
            template <class T> class Mat4
            {
            public:
            	static const T EPSILON;
            
            public:
            	Mat4()
            	{
            	}
            
            	Mat4(const T& matrix00, const T& matrix01, const T& matrix02, const T& matrix03,
            		const T& matrix10, const T& matrix11, const T& matrix12, const T& matrix13,
            		const T& matrix20, const T& matrix21, const T& matrix22, const T& matrix23,
            		const T& matrix30, const T& matrix31, const T& matrix32, const T& matrix33)
            	{
            		raw[0] = matrix00; raw[1] = matrix01; raw[2] = matrix02; raw[3] = matrix03;
            		raw[4] = matrix10; raw[5] = matrix11; raw[6] = matrix12; raw[7] = matrix13;
            		raw[8] = matrix20; raw[9] = matrix21; raw[10] = matrix22; raw[11] = matrix23;
            		raw[12] = matrix30; raw[13] = matrix31; raw[14] = matrix32; raw[15] = matrix33;
            	}
            
            	~Mat4()
            	{
            		raw[0] = raw[1] = raw[2] = raw[3] = 0;
            		raw[4] = raw[5] = raw[6] = raw[7] = 0;
            		raw[8] = raw[9] = raw[10] = raw[11] = 0;
            		raw[12] = raw[13] = raw[14] = raw[15] = 0;
            	}
            
            public:
            	Mat4<T>					operator*(const Mat4<T>& other) const;
				Mat4<T>					operator*(const T& other) const;

				static Mat4<T>			makeScale(const Vec3<T>& scale);
				static Mat4<T>			makeTranslation(const Vec3<T>& translation);
				static Mat4<T>			makeRotation(const Vec3<T>& axis, const T& rad);
				static Mat4<T>			makeIdentity();

				void					setScale(const Vec3<T>& scale);
				void					setTranslation(const Vec3<T>& translation);
				void					setRotation(const Vec3<T>& axis, const T& rad);

				Mat4<T>					getScaled(const Vec3<T>& scale) const;
				Mat4<T>					getTranslated(const Vec3<T>& translation) const;
				Mat4<T>					getRotated(const Vec3<T>& axis, const T& rad) const;   
            	
            	T						determinant() const;            
            	Mat4<T>					getTransposed() const;
				Mat4<T>					getInverse() const;

    			const T*				toArray() const { return raw; }
				static size_t			memSize() { return (sizeof(raw)); }    	
    	                
            protected:
    			T						raw[16];
            };
            
            template <class T>
            const T Mat4<T>::EPSILON = 0.000001;
            
            template <class T>
            Mat4<T> Mat4<T>::operator*(const Mat4<T>& other) const
            {
            	return Mat4<T>(
            		other.raw[0] * raw[0] + other.raw[1] * raw[4] + other.raw[2] * raw[8] + other.raw[3] * raw[12],
            		other.raw[0] * raw[1] + other.raw[1] * raw[5] + other.raw[2] * raw[9] + other.raw[3] * raw[13],
            		other.raw[0] * raw[2] + other.raw[1] * raw[6] + other.raw[2] * raw[10] + other.raw[3] * raw[14],
            		other.raw[0] * raw[3] + other.raw[1] * raw[7] + other.raw[2] * raw[11] + other.raw[3] * raw[15],
            
            		other.raw[4] * raw[0] + other.raw[5] * raw[4] + other.raw[6] * raw[8] + other.raw[7] * raw[12],
            		other.raw[4] * raw[1] + other.raw[5] * raw[5] + other.raw[6] * raw[9] + other.raw[7] * raw[13],
            		other.raw[4] * raw[2] + other.raw[5] * raw[6] + other.raw[6] * raw[10] + other.raw[7] * raw[14],
            		other.raw[4] * raw[3] + other.raw[5] * raw[7] + other.raw[6] * raw[11] + other.raw[7] * raw[15],
            
            		other.raw[8] * raw[0] + other.raw[9] * raw[4] + other.raw[10] * raw[8] + other.raw[11] * raw[12],
            		other.raw[8] * raw[1] + other.raw[9] * raw[5] + other.raw[10] * raw[9] + other.raw[11] * raw[13],
            		other.raw[8] * raw[2] + other.raw[9] * raw[6] + other.raw[10] * raw[10] + other.raw[11] * raw[14],
            		other.raw[8] * raw[3] + other.raw[9] * raw[7] + other.raw[10] * raw[11] + other.raw[11] * raw[15],
            
            		other.raw[12] * raw[0] + other.raw[13] * raw[4] + other.raw[14] * raw[8] + other.raw[15] * raw[12],
            		other.raw[12] * raw[1] + other.raw[13] * raw[5] + other.raw[14] * raw[9] + other.raw[15] * raw[13],
            		other.raw[12] * raw[2] + other.raw[13] * raw[6] + other.raw[14] * raw[10] + other.raw[15] * raw[14],
            		other.raw[12] * raw[3] + other.raw[13] * raw[7] + other.raw[14] * raw[11] + other.raw[15] * raw[15]
            	);
            }

			template <class T>
			Mat4<T> Mat4<T>::operator*(const T& other) const
			{
				return Mat4<T>(
					raw[0] * other, raw[1] * other, raw[2] * other, raw[3] * other,
					raw[4] * other, raw[5] * other, raw[6] * other, raw[7] * other, 
					raw[8] * other, raw[9] * other, raw[10] * other, raw[11] * other, 
					raw[12] * other, raw[13] * other, raw[14] * other, raw[15] * other
				);
			}           
            
            
            template <class T>
            T Mat4<T>::determinant() const
            {
            	T b00 = raw[0] * raw[5] - raw[1] * raw[4];
            	T b01 = raw[0] * raw[6] - raw[2] * raw[4];
            	T b02 = raw[0] * raw[7] - raw[3] * raw[4];
            	T b03 = raw[1] * raw[6] - raw[2] * raw[5];
            
            	T b04 = raw[1] * raw[7] - raw[3] * raw[5];
            	T b05 = raw[2] * raw[7] - raw[3] * raw[6];
            	T b06 = raw[8] * raw[13] - raw[9] * raw[12];
            	T b07 = raw[8] * raw[14] - raw[10] * raw[12];
            
            	T b08 = raw[8] * raw[15] - raw[11] * raw[12];
            	T b09 = raw[9] * raw[14] - raw[10] * raw[13];
            	T b10 = raw[9] * raw[15] - raw[11] * raw[13];
            	T b11 = raw[10] * raw[15] - raw[11] * raw[14];
            
            	return (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);
            }
            
            template <class T>
			Mat4<T> Mat4<T>::getTransposed() const
            {
            	return Mat4<T>(
            		raw[0], raw[4], raw[8], raw[12],
            		raw[1], raw[5], raw[9], raw[13],
            		raw[2], raw[6], raw[10], raw[14],
            		raw[3], raw[7], raw[11], raw[15]
            	);
            }      

			template <class T>
			Mat4<T> Mat4<T>::getInverse() const
			{
				T det = determinant();

				if (!det) {
					return Mat4<T>(
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 0, 0, 0,
						0, 0, 0, 0
					);
				}

				det = 1.0 / det;
				
				T b00 = (raw[5]  * raw[10] * raw[15]  -
						 raw[5]  * raw[11] * raw[14]  -
						 raw[9]  * raw[6]  * raw[15]  -
						 raw[9]  * raw[7]  * raw[14]  +
						 raw[13] * raw[6]  * raw[11]  -
						 raw[13] * raw[7]  * raw[10]) * det;

				T b10 = (-raw[4]  * raw[10] * raw[15]  +
						  raw[4]  * raw[11] * raw[14]  +
						  raw[8]  * raw[6]  * raw[15]  -
						  raw[8]  * raw[7]	* raw[14]  -
						  raw[12] * raw[6]  * raw[11]  +
						  raw[12] * raw[7]  * raw[10]) * det;

				T b20 = (raw[4]  * raw[9]  * raw[15] -
						 raw[4]  * raw[11] * raw[13] -
						 raw[8]  * raw[5]  * raw[15] +
						 raw[8]  * raw[7]  * raw[13] +
						 raw[12] * raw[5]  * raw[11] -
						 raw[12] * raw[7]  * raw[9]) * det;

				T b30 = -(raw[4]  * raw[9]  * raw[14] +
						  raw[4]  * raw[10] * raw[13] +
						  raw[8]  * raw[5]  * raw[14] -
						  raw[8]  * raw[6]  * raw[13] -
						  raw[12] * raw[5]  * raw[10] +
						  raw[12] * raw[6]  * raw[9]) * det;

				T b01 = -(raw[1]  * raw[10] * raw[15] +
						  raw[1]  * raw[11] * raw[14] +
						  raw[9]  * raw[2]  * raw[15] -
						  raw[9]  * raw[3]  * raw[14] -
						  raw[13] * raw[2]  * raw[11] +
						  raw[13] * raw[3]  * raw[10]) * det;

				T b11 = (raw[0]  * raw[10] * raw[15] -
						 raw[0]  * raw[11] * raw[14] -
						 raw[8]  * raw[2]  * raw[15] +
						 raw[8]  * raw[3]  * raw[14] +
						 raw[12] * raw[2]  * raw[11] -
						 raw[12] * raw[3]  * raw[10]) * det;

				T b21 = -(raw[0]  * raw[9]  * raw[15] +
						  raw[0]  * raw[11] * raw[13] +
						  raw[8]  * raw[1]  * raw[15] -
						  raw[8]  * raw[3]  * raw[13] -
						  raw[12] * raw[1]  * raw[11] +
						  raw[12] * raw[3]  * raw[9]) * det;

				T b31 = (raw[0]  * raw[9]  * raw[14] -
						 raw[0]  * raw[10] * raw[13] -
						 raw[8]  * raw[1]  * raw[14] +
						 raw[8]  * raw[2]  * raw[13] +
						 raw[12] * raw[1]  * raw[10] -
						 raw[12] * raw[2]  * raw[9]) * det;

				T b02 = (raw[1]  * raw[6] * raw[15] -
						 raw[1]  * raw[7] * raw[14] -
						 raw[5]  * raw[2] * raw[15] +
						 raw[5]  * raw[3] * raw[14] +
						 raw[13] * raw[2] * raw[7]  -
						 raw[13] * raw[3] * raw[6]) * det;

				T b12 = -(raw[0]  * raw[6] * raw[15] +
						  raw[0]  * raw[7] * raw[14] +
						  raw[4]  * raw[2] * raw[15] -
						  raw[4]  * raw[3] * raw[14] -
						  raw[12] * raw[2] * raw[7]  +
						  raw[12] * raw[3] * raw[6]) * det;

				T b22 = (raw[0]  * raw[5] * raw[15] -
						 raw[0]  * raw[7] * raw[13] -
						 raw[4]  * raw[1] * raw[15] +
						 raw[4]  * raw[3] * raw[13] +
						 raw[12] * raw[1] * raw[7]  -
						 raw[12] * raw[3] * raw[5]) * det;

				T b32 = -(raw[0]  * raw[5] * raw[14] +
						  raw[0]  * raw[6] * raw[13] +
						  raw[4]  * raw[1] * raw[14] -
						  raw[4]  * raw[2] * raw[13] -
						  raw[12] * raw[1] * raw[6]  +
						  raw[12] * raw[2] * raw[5]) * det;

				T b03 = -(raw[1] * raw[6] * raw[11] +
						  raw[1] * raw[7] * raw[10] +
						  raw[5] * raw[2] * raw[11] -
						  raw[5] * raw[3] * raw[10] -
						  raw[9] * raw[2] * raw[7]  +
						  raw[9] * raw[3] * raw[6]) + det;

				T b13 = (raw[0] * raw[6] * raw[11] -
						 raw[0] * raw[7] * raw[10] -
						 raw[4] * raw[2] * raw[11] +
						 raw[4] * raw[3] * raw[10] +
						 raw[8] * raw[2] * raw[7]  -
						 raw[8] * raw[3] * raw[6]) * det;

				T b23 = -(raw[0] * raw[5] * raw[11] +
						  raw[0] * raw[7] * raw[9]  +
						  raw[4] * raw[1] * raw[11] -
						  raw[4] * raw[3] * raw[9]  -
						  raw[8] * raw[1] * raw[7]  +
						  raw[8] * raw[3] * raw[5]) * det;

				T b33 = (raw[0] * raw[5] * raw[10] -
						 raw[0] * raw[6] * raw[9]  -
						 raw[4] * raw[1] * raw[10] +
						 raw[4] * raw[2] * raw[9]  +
						 raw[8] * raw[1] * raw[6]  -
						 raw[8] * raw[2] * raw[5]) * det;

				return Mat4<T>(
					b00, b01, b02, b03,
					b10, b11, b12, b13,
					b20, b21, b22, b23,
					b30, b31, b32, b33
				);
			}
			
			template <class T>
			Mat4<T> Mat4<T>::makeScale(const Vec3<T>& scale)
			{
				T x, y, z;

				x = scale.getX();
				y = scale.getY();
				z = scale.getZ();

				return Mat4<T>(
					x, 0, 0, 0,
					0, y, 0, 0,
					0, 0, z, 0, 
					0, 0, 0, 1
				);
			}

			template <class T>
			Mat4<T> Mat4<T>::makeTranslation(const Vec3<T>& translation)
			{
				T x, y, z;

				x = translation.getX();
				y = translation.getY();
				z = translation.getZ();

				return Mat4<T>(
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					x, y, z, 1
				);
			}

			template <class T>
			Mat4<T> Mat4<T>::makeRotation(const Vec3<T>& axis, const T& rad)
			{
				T x, y, z;

				x = axis.getX();
				y = axis.getY();
				z = axis.getZ();

				T c = cos(rad);
				T s = sin(rad);

				T oneMinusC = 1 - c;

				T m00 = x * x * oneMinusC + c;
				T m01 = x * y * oneMinusC + z * s;
				T m02 = x * z * oneMinusC - y * s;
				T m03 = 0;

				T m10 = x * y * oneMinusC - z * s;
				T m11 = y * y * oneMinusC + c;
				T m12 = y * z * oneMinusC + x * s;
				T m13 = 0;

				T m20 = x * z * oneMinusC + y * s;
				T m21 = y * z * oneMinusC - x * s;
				T m22 = z * z * oneMinusC + c;
				T m23 = 0;

				return Mat4<T>(
					m00, m01, m02, m03,
					m10, m11, m12, m13,
					m20, m21, m22, m23,
					0, 0, 0, 1
				);
			}

			template <class T>
			Mat4<T> Mat4<T>::makeIdentity()
			{
				return Mat4<T>(
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1
					);
			}

			template <class T>
			void Mat4<T>::setScale(const Vec3<T>& scale)
			{
				raw[0] = scale.getX();
				raw[5] = scale.getY();
				raw[10] = scale.getZ();
			}

			template <class T>
			void Mat4<T>::setTranslation(const Vec3<T>& translation)
			{
				raw[12] = translation.getX();
				raw[13] = translation.getY();
				raw[14] = translation.getZ();
			}

			template <class T>
			void Mat4<T>::setRotation(const Vec3<T>& axis, const T& rad)
			{
				T x, y, z;

				x = axis.getX();
				y = axis.getY();
				z = axis.getZ();

				T c = cos(rad);
				T s = sin(rad);

				T oneMinusC = 1 - c;

				raw[0] = x * x * oneMinusC + c;
				raw[1] = x * y * oneMinusC + z * s;
				raw[2] = x * z * oneMinusC - y * s;

				raw[4] = x * y * oneMinusC - z * s;
				raw[5] = y * y * oneMinusC + c;
				raw[6] = y * z * oneMinusC + x * s;

				raw[8] = x * z * oneMinusC + y * s;
				raw[9] = y * z * oneMinusC - x * s;
				raw[10] = z * z * oneMinusC + c;
			}

			template <class T>
			Mat4<T> Mat4<T>::getScaled(const Vec3<T>& scale) const
			{
				T x, y, z;

				x = scale.getX();
				y = scale.getY();
				z = scale.getZ();

				return Mat4<T>(
					x * raw[0], raw[1], raw[2], raw[3],
					raw[4], y * raw[5], raw[6], raw[7],
					raw[8], raw[9], z * raw[10], raw[11],
					raw[12], raw[13], raw[14], raw[15]
				);
			}

			template <class T>
			Mat4<T> Mat4<T>::getTranslated(const Vec3<T>& translation) const
			{
				return Mat4<T>(
					raw[0], raw[1], raw[2], raw[3],
					raw[4], raw[5], raw[6], raw[7],
					raw[8], raw[9], raw[10], raw[11],
					raw[12] + translation.getX(), raw[13] + translation.getY(), raw[14] + translation.getZ(), raw[15]
				);
			}

			template <class T>
			Mat4<T> Mat4<T>::getRotated(const Vec3<T>& axis, const T& rad) const
			{
				T x, y, z;

				x = axis.getX();
				y = axis.getY();
				z = axis.getZ();

				T c = cos(rad);
				T s = sin(rad);

				T oneMinusC = 1 - c;

				T m00 = raw[0] * x * x * oneMinusC + c;
				T m01 = raw[1] * x * y * oneMinusC + z * s;
				T m02 = raw[2] * x * z * oneMinusC - y * s;
				T m03 = raw[3];

				T m10 = raw[4] * x * y * oneMinusC - z * s;
				T m11 = raw[5] * y * y * oneMinusC + c;
				T m12 = raw[6] * y * z * oneMinusC + x * s;
				T m13 = raw[7];

				T m20 = raw[8] * x * z * oneMinusC + y * s;
				T m21 = raw[9] * y * z * oneMinusC - x * s;
				T m22 = raw[10] * z * z * oneMinusC + c;
				T m23 = raw[11];

				return Mat4<T>(
					m00, m01, m02, m03,
					m10, m11, m12, m13,
					m20, m21, m22, m23,
					raw[12], raw[13], raw[14], raw[15]
				);
			}
        }
    }
}

#endif // !__MAT4_H__