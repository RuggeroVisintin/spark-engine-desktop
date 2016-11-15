#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include "Mat4.h"

namespace SE
{
    namespace core
    {
    	namespace math
    	{
    		// VR frustum?
    		template <class T> class Frustum : private Mat4<T> 
    		{
    			typedef Mat4<T> Super;
    
    		public:
    			Frustum()
    				: Super()
    			{
    			}
    
    			~Frustum()
    			{
    			}
    
    		public:
    			static Frustum<T>   createPerspective(const T& fov, const T& ratio, const T& near, const T& far);
    			//static Frustum<T> createOrtho(const T& left, const T& right, const T& bottom, const T& top, const T& near, const T& far);
    
    			Frustum<T>&         makePerspective(const T& fov, const T& ratio, const T& near, const T& far);
    			//Frustum<T>&       makeOrtho(const T& left, const T& right, const T& bottom, const T& top, const T& near, const T& far);
    		
				Mat4<T>				toMat4() const;

    			const T*            toArray() const { return Super::toArray(); }
    			size_t              memSize() const { return Super::memSize(); }
    		};
    
			template <class T>
			Frustum<T> Frustum<T>::createPerspective(const T& fov, const T& ratio, const T& nearPlane, const T& farPlane)
			{
				T halfFov = 1.0 / tan((fov / 2.0));
				T nf = 1.0 / (nearPlane - farPlane);

				Frustum<T> result;

				result.raw[0] = halfFov / ratio;			result.raw[1] = 0;					result.raw[2] = 0;											result.raw[3] = 0;
				result.raw[4] = 0;							result.raw[5] = halfFov;			result.raw[6] = 0;											result.raw[7] = 0;
				result.raw[8] = 0;							result.raw[9] = 0;					result.raw[10] = (farPlane + nearPlane) * nf;				result.raw[11] = -1;
				result.raw[12] = 0;							result.raw[13] = 0;					result.raw[14] = (2 * farPlane * nearPlane) * nf;			result.raw[15] = 0;

				return result;
			}

			template <class T>
			Frustum<T>& Frustum<T>::makePerspective(const T& fov, const T& ratio, const T& nearPlane, const T& farPlane)
			{
				T halfFov = 1.0 / tan((fov / 2.0));
				T nf = 1.0 / (nearPlane - farPlane);

				raw[0] = halfFov / ratio;       raw[1] = 0;             raw[2] = 0;										raw[3] = 0;
				raw[4] = 0;                     raw[5] = halfFov;       raw[6] = 0;										raw[7] = 0;
				raw[8] = 0;                     raw[9] = 0;             raw[10] = (farPlane + nearPlane) * nf;          raw[11] = -1;
				raw[12] = 0;                    raw[13] = 0;            raw[14] = (2 * farPlane * nearPlane) * nf;		raw[15] = 0;

				return *this;
			}

			template <class T>
			Mat4<T> Frustum<T>::toMat4() const
			{
				return Mat4<T>(
					raw[0], raw[1], raw[2], raw[3],
					raw[4], raw[5], raw[6], raw[7],
					raw[8], raw[9], raw[10], raw[11],
					raw[12], raw[13], raw[14], raw[15]
				);
			}
    	}
    }
}

#endif // !__FRUSTUM_H__