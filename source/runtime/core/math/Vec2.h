#ifndef __VEC2_H__
#define __VEC2_H__

#include <cmath>
#include "Vec3.h"

namespace SE
{
    namespace core
    {
        namespace math
        {
            template <class T> class Vec2
            {
            public:
            	Vec2() : mX(0), mY(0) 
            	{
            	}
            
            	Vec2(const T& x, const T& y) 
            	{
            		mX = x;
            		mY = y;
            	}
            
            public:
            	Vec2<T>				operator+(const Vec2<T>& a) const;
            	Vec2<T>				operator-(const Vec2<T>& a) const;
            	Vec2<T>				operator*(const Vec2<T>& a) const;
            	Vec2<T>				operator/(const Vec2<T>& a) const;
            
            	Vec2<T>				operator+(const T& value) const;
            	Vec2<T>				operator-(const T& value) const;
            	Vec2<T>				operator*(const T& value) const;
            	Vec2<T>				operator/(const T& value) const;

				bool				operator==(const Vec2<T>& a) const;
				bool				operator!=(const Vec2<T>& a) const;
            		
            	T					dot(const Vec2<T>& a) const;
            	T					cross(const Vec2<T>& a) const;
            
            	Vec3<T>				cross3D(const Vec2<T>& a) const;
            	T					length() const;
            
            	T					distance(const Vec2<T>& a) const;
            	Vec2<T>				normalize() const;
            
            	void				setX(const T& x) { mX = x; }
            	const T&			getX() const { return mX; }
            
            	void				setY(const T& y) { mY = y; }
            	const T&			getY() const { return mY; }
            
            private:
            	T					mX, mY;
            };
            
            template <class T>
            Vec2<T> Vec2<T>::operator+(const Vec2<T>& a) const
            {
            	return Vec2<T>(mX + a.mX, mY + a.mY);
            }
            
            template <class T>
            Vec2<T> Vec2<T>::operator-(const Vec2<T>& a) const
            {
            	return Vec2<T>(mX - a.mX, mY - a.mY);
            }
            
            template <class T>
            Vec2<T> Vec2<T>::operator*(const Vec2<T>& a) const
            {
            	return Vec2<T>(mX * a.mX, mY * a.mY);
            }
            
            template <class T>
            Vec2<T> Vec2<T>::operator/(const Vec2<T>& a) const
            {
            	return Vec2<T>(mX / a.mX, mY / a.mY);
            }
            
            template <class T>
            Vec2<T> Vec2<T>::operator+(const T& value) const
            {
            	return Vec2<T>(mX + value, mY + value);
            }
            
            template <class T>
            Vec2<T> Vec2<T>::operator-(const T& value) const
            {
            	return Vec2<T>(mX - value, mY - value);
            }
            
            template <class T>
            Vec2<T> Vec2<T>::operator*(const T& value) const
            {
            	return Vec2<T>(mX * value, mY * value);
            }
            
            template <class T>
            Vec2<T> Vec2<T>::operator/(const T& value) const
            {
            	return Vec2<T>(mX / value, mY / value);
            }

			template <class T>
			bool Vec2<T>::operator==(const Vec2<T>& a) const
			{
				return mX == a.mX && mY == a.mY;
			}

			template <class T>
			bool Vec2<T>::operator!=(const Vec2<T>& a) const
			{
				return mX != a.mX || mY != a.mY;
			}
            
            template <class T>
            T Vec2<T>::dot(const Vec2<T>& a) const
            {
            	return (mX * a.mX + mY * a.mY);
            }
            
            template <class T>
            T Vec2<T>::cross(const Vec2<T>& a) const
            {
            	return mX * a.mY - mY * a.mX;
            }
            
            template <class T>
            Vec3<T> Vec2<T>::cross3D(const Vec2<T>& a) const
            {
            	return Vec3<T>(0, 0, cross(a));
            }
            
            template <class T>
            T Vec2<T>::length() const
            {
            	return sqrt(mX * mX + mY * mY);
            }
            
            template <class T>
            T Vec2<T>::distance(const Vec2<T>& a) const
            {
            	return sqrt (
            			(a.mX - mX) * (a.mX - mX) +
            			(a.mY - mY) * (a.mY - mY)
            		);
            }
            
            template <class T>
            Vec2<T> Vec2<T>::normalize() const
            {
            	T l = length();
            
            	if (l != 0){
            		return Vec2<T>(mX / l, mY / l);
            	}
            
            	return Vec2<T>();
            }
        }
    }
}

#endif // !__VEC2_H__