#ifndef __MAT3_H__
#define __MAT3_H__

#include <cmath>

namespace SE
{
    namespace core
    {
        namespace math
        {
            template <class T> class Mat3
            {
            public:
            	Mat3()
            	{
            		*this = identity();
            	}
            
            	Mat3(const T& matrix00, const T& matrix01, const T& matrix02,
            		const T& matrix10, const T& matrix11, const T& matrix12,
            		const T& matrix20, const T& matrix21, const T& matrix22)
            	{
            		m00 = matrix00; m01 = matrix01; m02 = matrix02;
            		m10 = matrix10; m11 = matrix11; m12 = matrix12;
            		m20 = matrix20; m21 = matrix21; m22 = matrix22;
            	}
            
            	~Mat3()
            	{
            		m00 = m01 = m02 = 0;
            		m10 = m11 = m12 = 0;
            		m20 = m21 = m22 = 0;
            	}
            
            public:
            	const Mat3<T>&			operator*(const Mat3<T>& a) const;
            
            	Mat3<T>					identity() const;
            	T						determine() const;
            
            	Mat3<T>					transpose() const;
            	Mat3<T>					invert() const;
            
            	Mat3<T>					translate(const T& xTranslation, const T& yTranslation) const;
            	Mat3<T>					rotate(const T& rad) const;
            	Mat3<T>					scale(const T& xScalar, const T& yScalar) const;            
            	            
            private:
            	T						m00, m01, m02;
            	T						m10, m11, m12;
            	T						m20, m21, m22;
            };
            
            template <class T>
            Mat3<T> Mat3<T>::operator*(const Mat3<T>& a) const
            {
            	return Mat3<T>(
            		a.m00 * m00 + a.m01 * m10 + a.m02 * m20,
            		a.m00 * m01 + a.m01 * m11 + a.m02 * m21,
            		a.m00 * m02 + a.m01 * m12 + a.m02 * m22,
            
            		a.m10 * m00 + a.m11 * m10 + a.m12 * m20,
            		a.m10 * m01 + a.m11 * m11 + a.m12 * m21,
            		a.m10 * m02 + a.m11 * m12 + a.m12 * m22,
            
            		a.m20 * m00 + a.m21 * m10 + a.m22 * m20,
            		a.m20 * m01 + a.m21 * m11 + a.m22 * m21,
            		a.m20 * m02 + a.m21 * m12 + a.m22 * m22
            	);
            }
            
            template <class T>
            Mat3<T> Mat3<T>::identity() const
            {
            	return Mat3<T>(1, 0, 0, 0, 1, 0, 0, 0, 1);
            }
            
            template <class T>
            T Mat3<T>::determine() const
            {
            	return (
            		m00 * (m22 * m11 - m12 * m21) + 
            		m01 * (-m22 * m10 + m12 * m20) + 
            		m02 * (m21 * m10 - m11 * m20)
            	);
            }
            
            template <class T>
            Mat3<T> Mat3<T>::invert() const
            {
            	T det = determine();
            
            	if (!det) {
            		return Mat3<T>(
            			0, 0, 0,
            			0, 0, 0,
            			0, 0, 0
            		);
            	}
            
            	det = 1.0 / det;
            
            	return Mat3<T>(
            		(m22 * m11 - m12 * m21) * det,
            		(-m22 * m01 + m02 * m21) * det,
            		(m12 * m01 - m02 * m11) * det,
            
            		(-m22 * m10 + m12 * m20) * det,
            		(m22 * m00 - m02 * m20) * det,
            		(-m12 * m00 + m02 * m10) * det,
            
            		(m21 * m10 - m11 * m20) * det,
            		(-m21 * m00 + m01 * m20) * det,
            		(m11 * m00 - m01 * m10) * det
            	);
            }
            
            template <class T>
            Mat3<T> Mat3<T>::translate(const T& xTranslation, const T& yTranslation) const
            {
            	return Mat3<T>(
            		m00, m01, m02,
            		m10, m11, m12,
            		xTranslation * m00 + yTranslation * m10 + m20,
            		xTranslation * m01 + yTranslation * m11 + m12,
            		xTranslation * m02 + yTranslation * m12 + m22
            	);
            }
            
            template <class T>
            Mat3<T> Mat3<T>::rotate(const T& rad) const
            {
            	T s = sin(rad);
            	T c = cos(rad);
            
            	return Mat3<T>(
            		c * m00 + s * m10, c * m01 + s * m11, c * m02 + s * m12,
            		c * m10 - s * m00, c * m11 - s * m01, c * m12 - s * m02,
            		m20, m21, m22
            	);
            }
            
            template <class T>
            Mat3<T> Mat3<T>::scale(const T& xScalar, const T& yScalar) const
            {
            	return Mat3<T>(
            		m00 * xScalar, m01 * xScalar, m02 * xScalar,
            		m10 * yScalar, m11 * yScalar, m12 * yScalar,
            		m20, m21, m22
            	);
            }
        }
    }
}

#endif // !__MAT3_H__