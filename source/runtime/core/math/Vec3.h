#ifndef __VEC3_H__
#define __VEC3_H__

#include <cmath>

namespace SE
{
    namespace core
    {
        namespace math
        {
            template <class T> class Vec3
            {
			public:
				static const Vec3<T> ZERO_VECTOR;
				static const Vec3<T> FORWARD_VECTOR;
				static const Vec3<T> UP_VECTOR;
				static const Vec3<T> RIGHT_VECTOR;

            public:
            	Vec3() :mX(0), mY(0), mZ(0)
            	{
            
            	}
            
            	Vec3(const T& x, const T& y, const T& z)
            	{
            		mX = x;
            		mY = y;
            		mZ = z;
            	}	

				Vec3(const Vec3<T>& v)
				{
					mX = v.mX;
					mY = v.mY;
					mZ = v.mZ;
				}
            
            public:
				void				operator=(const Vec3<T>& a);
            	Vec3<T>				operator+(const Vec3<T>& a) const;
            	Vec3<T>				operator-(const Vec3<T>& a) const;
            	Vec3<T>				operator*(const Vec3<T>& a) const;
            	Vec3<T>				operator/(const Vec3<T>& a) const;
            
            	Vec3<T>				operator+(const T& value) const;
            	Vec3<T>				operator-(const T& value) const;
            	Vec3<T>				operator*(const T& value) const;
            	Vec3<T>				operator/(const T& value) const;				

				friend Vec3<T>		operator+(const T& value, const Vec3<T>& v)
				{
					return v.operator+(value);
				}

				friend Vec3<T>		operator*(const T& value, const Vec3<T>& v)
				{
					return v.operator*(value);
				}						

            	Vec3<T>&			operator+=(const Vec3<T>& v);
            	Vec3<T>&			operator-=(const Vec3<T>& v);
            	Vec3<T>&			operator*=(const Vec3<T>& v);
            	Vec3<T>&			operator/=(const Vec3<T>& v);

				bool				operator==(const Vec3<T>& vec3) const;
				bool				operator!=(const Vec3<T>& vec3) const;

            	T					dot(const Vec3<T>& a) const;
            	Vec3<T>				cross(const Vec3<T>& a) const;
            
            	T					length() const;
            	T					distance(const Vec3<T>& a) const;
            
            	Vec3<T>				normalize() const;

				bool				isNormalized() const;
            	
            	void				setX(const T& x) { mX = x; }
            	const T&			getX() const { return mX; }
            
            	void				setY(const T& y) { mY = y; }
            	const T&			getY() const { return mY; }
            
            	void				setZ(const T& z) { mZ = z; }
            	const T&			getZ() const { return mZ; }
            
            	const T*			toArray() const;

				static size_t		memSize()
				{
					return sizeof(T) * 3;
				}
            
            private:
            	T					mX, mY, mZ;
            };	

			// static variables

			template <class T>
			const Vec3<T> Vec3<T>::ZERO_VECTOR		= Vec3<T>(0, 0, 0);

			template <class T>
			const Vec3<T> Vec3<T>::FORWARD_VECTOR	= Vec3<T>(0, 0, 1);

			template <class T>
			const Vec3<T> Vec3<T>::UP_VECTOR		= Vec3<T>(0, -1, 0);

			template <class T>
			const Vec3<T> Vec3<T>::RIGHT_VECTOR		= Vec3<T>(1, 0, 0);

			// ======================================================================================================== //
			//		IMPLEMENTATION																						//
			// ======================================================================================================== //

			template <class T>
			void Vec3<T>::operator=(const Vec3<T>& a)
			{
				mX = a.mX;
				mY = a.mY;
				mZ = a.mZ;
			}

            template <class T>
            Vec3<T> Vec3<T>::operator+(const Vec3<T>& a) const
            {
            	return Vec3<T>(mX + a.mX, mY + a.mY, mZ + a.mZ);
            }
            
            template <class T>
            Vec3<T> Vec3<T>::operator-(const Vec3<T>& a) const
            {
            	return Vec3<T>(mX - a.mX, mY - a.mY, mZ - a.mZ);
            }
            
            template <class T>
            Vec3<T> Vec3<T>::operator*(const Vec3<T>& a) const
            {
            	return Vec3<T>(mX * a.mX, mY * a.mY, mZ * a.mZ);
            }
            
            template <class T>
            Vec3<T> Vec3<T>::operator/(const Vec3<T>& a) const
            {
            	return Vec3<T>(mX / a.mX, mY / a.mY, mZ / a.mZ);
            }
            
            template <class T>
            Vec3<T> Vec3<T>::operator+(const T& value) const
            {
            	return Vec3<T>(mX + value, mY + value, mZ + value);
            }
            
            template <class T>
            Vec3<T> Vec3<T>::operator-(const T& value) const
            {
            	return Vec3<T>(mX - value, mY - value, mZ - value);
            }
            
            template <class T>
            Vec3<T> Vec3<T>::operator*(const T& value) const
            {
            	return Vec3<T>(mX * value, mY * value, mZ * value);
            }
            
            template <class T>
            Vec3<T> Vec3<T>::operator/(const T& value) const
            {
            	return Vec3<T>(mX / value, mY / value, mZ / value);
            }
            
            template <class T>
            Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& v)
            {
            	mX += v.mX;
            	mY += v.mY;
            	mZ += v.mZ;
            
            	return *this;
            }
            
            template <class T>
            Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& v)
            {
            	mX -= v.mX;
            	mY -= v.mY;
            	mZ -= v.mZ;
            
            	return *this;
            }
            
            template <class T>
            Vec3<T>& Vec3<T>::operator*=(const Vec3<T>& v)
            {
            	mX *= v.mX;
            	mY *= v.mY;
            	mZ *= v.mZ;
            
            	return *this;
            }
            
            template <class T>
            Vec3<T>& Vec3<T>::operator/=(const Vec3<T>& v)
            {
            	mX /= v.mX;
            	mY /= v.mY;
            	mZ /= v.mZ;
            
            	return *this;
            }
            
			template <class T>
			bool Vec3<T>::operator==(const Vec3<T>& value) const
			{
				return mX == value.mX && mY == value.mY && mZ == value.mZ;
			}

			template <class T>
			bool Vec3<T>::operator!=(const Vec3<T>& value) const
			{
				return mX != value.mX || mY != value.mY || mZ != value.mZ;
			}			

            template <class T>
            T Vec3<T>::dot(const Vec3<T>& a) const
            {
            	return (mX * mX + mY * mY + mZ * mZ);
            }
            
            template <class T>
            Vec3<T> Vec3<T>::cross(const Vec3<T>& a) const
            {
            	return Vec3<T> (
            		mY * a.mZ - mZ * a.mY, 
            		mZ * a.mX - mX * a.mZ, 
            		mX * a.mY - mY * a.mX
            	);
            }
            
            template <class T>
            T Vec3<T>::length() const
            {
            	return sqrt(mX * mX + mY * mY + mZ * mZ);
            }
            
            template <class T>
            T Vec3<T>::distance(const Vec3<T>& a) const
            {
            	return sqrt(
            		(a.mX - mX) * (a.mX - mX) +
            		(a.mY - mY) * (a.mY - mY) +
            		(a.mZ - mZ) * (a.mZ - mZ)
            	);
            }
            
            template <class T>
            Vec3<T> Vec3<T>::normalize() const
            {
            	T l = length();
            	if (l < 0) {
            		return Vec3<T>(0, 0, 0);
            	}
            
				//l = 1 / sqrt(l);
				//return Vec3<T>(mX * l, mY * l, mZ * l);
				return Vec3<T>(mX / l, mY / l, mZ / l);
            }

			// can't count on that for now
			template <class T>
			bool Vec3<T>::isNormalized() const
			{
				T l = length();		

				return abs((l - 1 <= std::numeric_limits<T>::epsilon()));
			}
            
            template <class T>
            const T* Vec3<T>::toArray() const
            {
            	T result[3];
            
            	result[0] = mX;
            	result[1] = mY;
            	result[2] = mZ;
            
            	return result;
            }
        }
    }
}

#endif // !__VEC3_H__