#ifndef __EULER_H__
#define __EULER_H__

#include <math.h>

namespace SE
{
	namespace core
	{
		namespace math
		{
			template <class T> class Euler
			{
			public:
				Euler()
				{
				}

				Euler(const T& pitch, const T& yaw, const T& roll)
					: pitch(pitch)
					, yaw(yaw)
					, roll(roll)
				{
				}

				~Euler()
				{
				}
			
			public:
				Euler<T>		operator+(const Euler<T>& other) const;
				Euler<T>		operator-(const Euler<T>& other) const;

				Euler<T>&		operator+=(const Euler<T>& other);
				Euler<T>&		operator-=(const Euler<T>& other);

				bool			operator==(const Euler<T>& other) const;
				bool			operator!=(const Euler<T>& other) const;

				void			rotate(const T& deltaPitch, const T& deltaYaw, const T& deltaRoll);
				Euler<T>		getRotated(const T& deltaPitch, const T& deltaPitch, const T& deltaRoll) const;

				bool			equals(const Euler<T>& other, const T& tollerance) const;

			public:
				T pitch;
				T yaw;
				T roll;
			};

			template <class T>
			Euler<T> Euler<T>::operator+(const Euler<T>& other) const
			{
				return Euler<T>(pitch + other.pitch, yaw + other.yaw, roll + other.roll);
			}

			template <class T>
			Euler<T> Euler<T>::operator-(const Euler<T>& other) const
			{
				return Euler<T>(pitch - other.pitch, yaw - other.yaw, roll - other.roll);
			}

			template <class T>
			Euler<T>& Euler<T>::operator+=(const Euler<T>& other)
			{
				pitch += other.pitch;
				yaw += other.yaw;
				roll += other.yaw;

				return *this;
			}

			template <class T>
			Euler<T>& Euler<T>::operator-=(const Euler<T>& other)
			{
				pitch -= other.pitch;
				yaw -= other.yaw;
				roll -= other.yaw;

				return *this;
			}

			template <class T>
			bool Euler<T>::operator==(const Euler<T>& other) const
			{
				return (ptich == other.pitch && yaw == other.yaw && roll == other.roll);
			}

			template <class T>
			bool Euler<T>::operator!=(const Euler<T>& other) const
			{
				return (ptich != other.pitch || yaw != other.yaw || roll != other.roll);
			}

			template <class T>
			void Euler<T>::rotate(const T& deltaPitch, const T& deltaYaw, const T& deltaRoll)
			{
				pitch += deltaPitch;
				yaw += deltaYaw;
				roll += deltaRoll;
			}

			template <class T>
			Euler<T> Euler<T>::getRotated(const T& deltaPitch, const T& deltaYaw, const T& deltaRoll) const
			{
				return Euler<T>(pitch + deltaPitch, yaw + deltaYaw, roll + deltaRoll);
			}

			template <class T>
			bool Euler<T>::equals(const Euler<T>& other, const T& tollerance) const
			{
				T pitchDelta = pitch - other.pitch;
				T yawDelta = yaw - other.yaw;
				T rollDelta = roll - other.roll;

				return (
					abs(pitchDelta) <= tollerance 
					&& abs(yawDelta) <= tollerance 
					&& abs(rollDelta) <= tollerance
				);
			}
		}
	}
}

#endif // !__EULER_H__