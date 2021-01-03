#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Quat.h"
#include "Vec3.h"
#include "Mat4.h"

namespace SE
{
    namespace core
    {
        namespace math
        {
            template <class T> class Transform
            {
            public:
            	Transform()
					: scale3D(1, 1, 1)
            	{				
            	}       

            	~Transform()
            	{
            	}

				
            
            public:
				bool					operator==(const Transform<T>& t) const;
				bool					operator!=(const Transform<T>& t) const;

            	void					accumulate(const Transform<T>& t);
				Transform<T>			getAccumulated(const Transform<T>& t) const;
			
				void					rotate(const Quat<T>& q);
				Transform<T>			getRotated(const Quat<T>& q) const;

				void					translate(const Vec3<T>& v);
				Transform<T>			getTranslated(const Vec3<T>& v) const;

				void					scale(const Vec3<T>& v);
				Transform<T>			getScaled(const Vec3<T>& v) const;

				Vec3<T>					getForward() const;
				Vec3<T>					getBackward() const;
				Vec3<T>					getUp() const;
				Vec3<T>					getDown() const;
				Vec3<T>					getRight() const;
				Vec3<T>					getLeft() const;

				Mat4<T>					getTransformMatrix() const;
	            
            public:
            	Quat<T>					rotation;
            	Vec3<T>					scale3D;
            	Vec3<T>					position;
            
            };

			template <class T>
			bool Transform<T>::operator==(const Transform<T>& t) const
			{
				return (rotation == t.rotation && position == t.position && scale3D == t.scale3D);
			}
            
			template <class T>
			bool Transform<T>::operator!=(const Transform<T>& t) const
			{
				return (rotation != t.rotation || position != t.position || scale3D != t.scale3D);
			}

            template <class T>
			void Transform<T>::accumulate(const Transform<T>& t)
            {
				rotation *= t.rotation;
				position += t.position;
				scale3D *= t.scale;
            } 

			template <class T>
			Transform<T> Transform<T>::getAccumulated(const Transform<T>& t) const
			{
				Transform<T> result;
				result.rotation = t.rotation * rotation;
				result.position = t.position + position;
				result.scale3D = t.scale3D * scale3D;

				return result;
			}

			template <class T>
			void Transform<T>::rotate(const Quat<T>& q)
			{
				rotation *= q;
			}

			template <class T>
			Transform<T> Transform<T>::getRotated(const Quat<T>& q) const
			{
				Transform<T> result;
				result.rotation = rotation * q;
				result.position = position;
				result.scale3D = scale3D;

				return result;
			}

			template <class T>
			void Transform<T>::translate(const Vec3<T>& v)
			{
				position += v;
			}

			template <class T>
			Transform<T> Transform<T>::getTranslated(const Vec3<T>& v) const
			{
				Transform<T> result;
				result.rotation = rotation;
				result.position = position + v;
				result.scale3D = scale3D;

				return result;
			}

			template <class T>
			void Transform<T>::scale(const Vec3<T>& v)
			{
				scale3D *= v;
			}

			template <class T>
			Transform<T> Transform<T>::getScaled(const Vec3<T>& v) const
			{
				Transform<T> result;
				result.rotation = rotation;
				result.position = position;
				result.scale3D = scale3D * v;
			}

			template <class T>
			Vec3<T> Transform<T>::getForward() const
			{
				return rotation.rotateVector(Vec3<T>::FORWARD_VECTOR);
			}

			template <class T>
			Vec3<T> Transform<T>::getBackward() const
			{
				return rotation.rotateVector(Vec3<T>::FORWARD_VECTOR * -1);
			}

			template <class T>
			Vec3<T> Transform<T>::getUp() const
			{
				return rotation.rotateVector(Vec3<T>::UP_VECTOR);
			}

			template <class T>
			Vec3<T> Transform<T>::getDown() const
			{
				return rotation.rotateVector(Vec3<T>::UP_VECTOR * -1);
			}

			template <class T>
			Vec3<T> Transform<T>::getRight() const
			{
				return rotation.rotateVector(Vec3<T>::RIGHT_VECTOR);
			}

			template <class T>
			Vec3<T> Transform<T>::getLeft() const
			{
				return rotation.rotateVector(Vec3<T>::RIGHT_VECTOR * -1);
			}

			template <class T>
			Mat4<T> Transform<T>::getTransformMatrix() const
			{
				Mat4<T> t = Mat4<T>::makeTranslation(position);
				Mat4<T> r = rotation.toMat4();
				Mat4<T> s = Mat4<T>::makeScale(scale3D);

				return Mat4<T>((r * t) * s);
			}
        }
    }
}

#endif // !__TRANSFORM_H__