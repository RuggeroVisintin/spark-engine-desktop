#ifndef __TRANSLATIONMATRIX_H__
#define __TRANSLATIONMATRIX_H__

#include "Mat4.h"
#include "Vec3.h"

namespace SE
{
	namespace core
	{
		namespace math
		{
			template <class T> class TranslationMatrix : private Mat4<T>
			{
				typedef Mat4<T> Super;

			public:
				TranslationMatrix(const Vec3<T>& delta);

			public:
				static Mat4<T>	make(const Vec3<T>& delta)
				{
					return TranslationMatrix(delta);
				}
			};

			template <class T>
			TranslationMatrix<T>::TranslationMatrix<T>(const Vec3<T>& delta)
				: Super(
					1.0, 0.0, 0.0, delta.getX(),
					0.0, 1.0, 0.0, delta.getY(),
					0.0, 0.0, 1.0, delta.getZ(),
					0.0, 0.0, 0.0, 1.0)
			{				
			}
		}
	}
}

#endif // !__TRANSLATIONMATRIX_H__