#ifndef __GPUVEC3_H__
#define __GPUVEC3_H__

#include "../Vec3.h"

namespace SE
{
	namespace core
	{
		namespace math
		{
			// TODO: the class may works only in case of flaot vectors, have to study another approach
			// WARNING: this class has an extra float member to address GPU padding issues, use only in situations
			// where padding becomes an issue
			template <class T> class GpuVec3 : public Vec3<T>
			{
				typedef Vec3<T> Super;

			public:
				GpuVec3()
					: Super()
				{

				}

				GpuVec3(Vec3<T> v)
					: Super(v)
				{

				}

			private:
				// extra padding float
				float p;
			};
		}
	}
}

#endif // !__GPUVEC£_H__