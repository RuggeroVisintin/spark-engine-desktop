#ifndef __MAT2_H__
#define __MAT2_H__

#include <cmath>

namespace SE
{
    namespace core
    {
        namespace math
        {
            template <class T> class Mat2
            {
            public:
            	static const T EPSILON;
            
            public:
            	Mat2()
            	{
            		*this = identity();
            	}
            
            	Mat2(const T& matrix00, const T& matrix01,
            		const T& matrix10, const T& matrix11)
            	{
            		m00 = matrix00; m01 = matrix01;
            		m10 = matrix10; m11 = matrix11;
            	}
            
            	~Mat2()
            	{
            		m00 = m01 = 0;
            		m10 = m11 = 0;
            	}
            
            public:
            	Mat2<T>			        operator*(const Mat2<T>& a) const;
                    
            	Mat2<T>			        identity() const;
            	T				        determine() const;
                    
            	Mat2<T>			        transpose() const;
            	Mat2<T>			        invert() const;
                    
            	Mat2<T>			        rotate(const T& rad) const;
            	Mat2<T>			        scale(const T& xScalar, const T& yScalar) const;
            
            	void					set00(const T& matrix00) { m00 = matrix00; }
            	const T&				get00() const { return m00; }
            
            	void					set01(const T& matrix01) { m01 = matrix01; }
            	const T&				get01() const { return m01; }
            
            	void					set10(const T& matrix10) { m10 = matrix10; }
            	const T&				get10() const { return m10; }
            	
            	void					set11(const T& matrix11) { m11 = matrix11; }
            	const T&				get11() const{ return m11; }
            
            private:
            	T						m00, m01;
            	T						m10, m11;
            
            };
            
            template <class T>
            const T Mat2<T>::EPSILON = 0.000001;
            
            template <class T>
            Mat2<T> Mat2<T>::operator*(const Mat2<T>& a) const
            {
            	return Mat2<T>(
            		m00 * a.m00 + m10 * a.m01,
            		m01 * a.m00 + m11 * a.m01,
            		m00 * a.m10 + m10 * a.m11,
            		m01 * a.m10 + m11 * a.m11
            	);
            }
            
            template <class T>
            Mat2<T> Mat2<T>::identity() const
            {
            	return Mat2<T>(1, 0, 0, 1);
            }
            
            template <class T>
            T Mat2<T>::determine() const
            {
            	return (m00 * m11 - m10 * m01);
            }
            
            template <class T>
            Mat2<T> Mat2<T>::transpose() const
            {
            	return Mat2<T>(m00, m10, m01, m11);
            }
            
            template <class T>
            Mat2<T> Mat2<T>::invert() const
            {
            	T det = determine();
            
            	if (!det) {
            		return Mat2<T>(0, 0, 0, 0);
            	}
            
            	det = 1.0 / det;
            
            	return Mat2<T>(m11 * det, m01 * det * -1, m10 * det * -1, m00 * det);
            }
            
            template <class T>
            Mat2<T> Mat2<T>::rotate(const T& rad) const
            {
            	T s = sin(rad);
            	T c = cos(rad);
            
            	return Mat2<T>(
            		m00 * c + m10 * s, m01 * c + m11 * s,
            		m00 * s * -1 + m10 * c,
            		m01 * s * -1 + m11 * c
            	);
            }
            
            template <class T>
            Mat2<T> Mat2<T>::scale(const T& xScalar, const T& yScalar) const
            {
            	return Mat2<T>(
            		m00 * xScalar, 
            		m01 * xScalar, 
            		m10 * yScalar,
            		m11 * yScalar
            	);
            }
        }
    }
}

#endif // !__MAT2_H__