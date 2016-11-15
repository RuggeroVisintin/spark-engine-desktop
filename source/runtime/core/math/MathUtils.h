#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__

namespace SE
{
	namespace core
	{
		namespace math
		{
			template <class T> class Constants
			{
			};

			template<> class Constants<float>
			{
			public:
				typedef float T;

				static const T PI;
				static const T PI2;
				static const T PI4;
			};

			const float Constants<float>::PI	= 3.14159265358979f;
			const float Constants<float>::PI2	= 1.57079632679489f;
			const float Constants<float>::PI4	= 0.78539816339745f;			

			template <> class Constants<double>
			{
			public:
				typedef double T;

				static const T PI;
				// TODO: calculate double Pi
				/*static const T PI2 = 1.57079632679489;
				static const T PI4 = 0.78539816339745;*/
			};

			const double Constants<double>::PI = 3.141592653589793238463;

			template <class T>
			T toDegrees(T radians)
			{
				return (radians * 180 / Constants<T>::PI);
			}

			template <class T>
			T toRadians(T degrees)
			{
				return (degrees * Constants<T>::PI / 180);
			}
		}
	}
}

#endif // !__MATHUTILS_H__