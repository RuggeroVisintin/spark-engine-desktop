#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#pragma once

#include <cmath>
#include "Vec3.h"
#include "Mat4.h"

namespace SE
{
    namespace core
    {
        namespace math
        {
            template <class T> class Quat
            {
			public:
				static const Quat<T> IDENTITY;

            public:
            	Quat()
            		: x(0)
            		, y(0)
            		, z(0)
            		, w(1)
            	{		
            	}
            
            	Quat(const T& x, const T& y, const T& z, const T& w)
            		: x(x)
            		, y(y)
            		, z(z)
            		, w(w)
            	{
            	}
            
				~Quat()
				{
				}
            
            public:
            	Quat<T>		operator+(const Quat<T>& q) const;
            	Quat<T>		operator*(const Quat<T>& q) const; 
				Quat<T>		operator*(const Vec3<T>& v) const;

				Quat<T>&	operator+=(const Quat<T>& q);
				Quat<T>&	operator*=(const Quat<T>& q);
				Quat<T>&	operator*=(const Vec3<T>& v);

				bool		operator==(const Quat<T>& q) const;
				bool		operator!=(const Quat<T>& q) const;

				void		setRotationAboutX(const T& theta);
				void		setRotationAboutY(const T& theta);
				void		setRotationAboutZ(const T& theta);
				void		setRotation(const Vec3<T>& axis, const T& theta);

				/*Quat<T>&	getRotatedAboutX(const T& theta) const;
				Quat<T>&	getRotatedAboutY(const T& theta) const;
				Quat<T>&	getRotatedAboutZ(const T& theta) const;
				Quat<T>&	getRotated(const Vec3<T>& axis, const T& theta);*/

				Vec3<T>		rotateVector(const Vec3<T>& v) const;
				void		getRotatedVector(Vec3<T>& v) const;

				Quat<T>		getNormalized() const;
				void		normalize();

				Quat<T>		getConjugate() const;
				void		conjugate();

				Mat4<T>		toMat4() const;
				Quat<T>		copy() const;
            	
            private:
				T x;
				T y;
				T z;
				T w;
            };

			// static variables
			template <class T>
			const Quat<T> Quat<T>::IDENTITY = Quat<T>(0, 0, 0, 1);

			// ======================================================================================================== //
			//		IMPLEMENTATION																						//
			// ======================================================================================================== //
            
            template <class T>
            Quat<T> Quat<T>::operator+(const Quat<T>& q) const
            {
            	return Quat<T>(x + q.x, y + q.y, z + q.z, w + q.w);
            }
            
            template <class T>
            Quat<T> Quat<T>::operator*(const Quat<T>& q) const
            {
            	return Quat<T>(
            		x * q.w + w * q.x + y * q.z - z * q.y,
            		y * q.w + w * q.y + z * q.x - x * q.z,
            		z * q.w + w * q.z + x * q.y - y * q.x,
            		w * q.w - x * q.x - y * q.y - z * q.z
            	);
            }  

			template <class T>
			Quat<T> Quat<T>::operator*(const Vec3<T>& v) const
			{
				T mW = -x * v.getX() - y * v.getY() - z * v.getZ();
				T mX = w * v.getX() + y * v.getZ() - z * v.getY();
				T mY = w * v.getY() + z * v.getX() - x * v.getZ();
				T mZ = w * v.getZ() + x * v.getY() - y * v.getX();

				return Quat<T>(mX, mY, mZ, mW);
			}

			template <class T>
			Quat<T>& Quat<T>::operator+=(const Quat<T>& q)
			{
				x += q.x; y += q.y; z += q.z; w += q.w;

				return *this;
			}

			template <class T>
			Quat<T>& Quat<T>::operator*=(const Quat<T>& q)
			{
				x = x * q.w + w * q.x + y * q.z - z * q.y;
				y = y * q.w + w * q.y + z * q.x - x * q.z;
				z = z * q.w + w * q.z + x * q.y - y * q.x;
				w = w * q.w - x * q.x - y * q.y - z * q.z;

				return *this;
			}

			template <class T>
			bool Quat<T>::operator==(const Quat<T>& q) const
			{
				return (x == q.x && y == q.y && z == q.z && w == q.w);
			}

			template <class T>
			bool Quat<T>::operator!=(const Quat<T>& q) const
			{
				return (x != q.x || y != q.y || z != q.z || w != q.w);
			}

			template <class T>
			void Quat<T>::setRotationAboutX(const T& theta)
			{
				T thetaOverTwo = theta * 0.5f;

				w = cos(thetaOverTwo);
				x = sin(thetaOverTwo);
				y = y;
				z = z;

				normalize();
			}

			template <class T>
			void Quat<T>::setRotationAboutY(const T& theta)
			{
				T thetaOverTwo = theta * 0.5f;

				w = cos(thetaOverTwo);
				x = x;
				y = sin(thetaOverTwo);
				z = z;				

				normalize();
			}

			template <class T>
			void Quat<T>::setRotationAboutZ(const T& theta)
			{
				T thetaOverTwo = theta * 0.5f;

				w = cos(thetaOverTwo);
				x = x;
				y = y;
				z = sin(thetaOverTwo);

				normalize();
			}

			template <class T>
			void Quat<T>::setRotation(const Vec3<T>& axis, const T& theta)
			{
				// axis has to be a normalized vector
				SPARK_ASSERT(axis.isNormalized(), "Quat<T>::setRotation - @param const Vec3<T>& axis - is not a normalized vector");

				T cosHalfTheta = cos(theta / 2.0f);
				T sinHalfTheta = sin(theta / 2.0f);

				w = cosHalfTheta;
				x = axis.getX() * sinHalfTheta;
				y = axis.getY() * sinHalfTheta;
				z = axis.getZ() * sinHalfTheta;
			}

			template <class T>
			Vec3<T> Quat<T>::rotateVector(const Vec3<T>& v) const
			{
				Quat<T> conjugate = getConjugate();
				Quat<T> w = (*this * v) * conjugate;

				Vec3<T> result = Vec3<T>(w.x, w.y, w.z);

				// this should be faster but doesn't work as aspected
				/*Vec3<T> q(x, y, z);
				Vec3<T> t = 2 * q.cross(v) ;
				Vec3<T> result = v + (w * t) + q.cross(v);*/

				return result;
			}

			template <class T>
			void Quat<T>::getRotatedVector(Vec3<T>& v) const
			{
				// this should be faster but doesn't work as aspected
				/*const Vec3<T> q(x, y, z);
				const Vec3<T> t = 2 * q.cross(v);

				v = v + (w * t) + q.cross(v);*/

				Quat<T> conjugate = getConjugate();
				Quat<T> w = (*this * v) * conjugate;

				v.setX(w.x);
				v.setY(w.y);
				v.setZ(w.z);
			}

			template <class T>
			Quat<T> Quat<T>::getConjugate() const
			{
				return Quat<T>(-x, -y, -z, w);
			}

			template <class T>
			void Quat<T>::conjugate()
			{
				x = -x;
				y = -y;
				z = -z;
			}

			template <class T>
			Quat<T> Quat<T>::getNormalized() const
			{
				T m = sqrt(w * w + x * x + y * y + z * z);

				return Quat<T>(x / m, y / m, z / m, w / m);
			}

			template <class T>
			void Quat<T>::normalize()
			{
				T m = sqrt(w * w + x * x + y * y + z * z);

				w /= m;
				x /= m;
				y /= m;
				z /= m;
			}

			template <class T>
			Mat4<T> Quat<T>::toMat4() const
			{
				// Is this really needed?
				Quat<T> q = getNormalized();

				T m00 = 1 - 2 * (q.y * q.y + q.z * q.z);
				T m10 = 2 * (q.x * q.y + q.w * q.z);
				T m20 = 2 * (q.x * q.z - q.w * q.y);

				T m01 = 2 * (q.x * q.y - q.w * q.z);
				T m11 = 1 - 2 * (q.x * q.x + q.z * q.z);
				T m21 = 2 * (q.y * q.z + q.w * q.x);

				T m02 = 2 * (q.x * q.z + q.w * q.y);
				T m12 = 2 * (q.y * q.z - q.w * q.x);
				T m22 = 1 - 2 * (q.x * q.x + q.y * q.y);

				return Mat4<T> (
					m00, m01, m02, 0,
					m10, m11, m12, 0,
					m20, m21, m22, 0,
					0, 0, 0, 1
				);
 			}

			template <class T>
			Quat<T> Quat<T>::copy() const
			{
				return Quat<T>(x, y, z, w);
			}
		}
    }
}

#endif // !__QUATERNION_H__