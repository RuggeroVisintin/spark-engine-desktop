#ifndef __PLATFORMUTILS_H__
#define __PLATFORMUTILS_H__

#include <string>
#include <sstream>

#include "Platform.h"

#define SPARK_NOT_IMPLEMENTED(res) {SE::platform::notImplementedError(__FUNCTION__, __FILE__, __LINE__); return res;}

#define SPARK_CONST_REFERENCE(value) const value&
#define SPARK_CONST_POINTER(value) const value*
#define SPARK_REFERENCE(value) value&
#define SPARK_POINTER(value) value*

#define SPARK_INOUT_R(value) SPARK_REFERENCE(value)
#define SPARK_INOUT_P(value)  SPARK_POINTER(value)
#define SPARK_IN_R(value) SPARK_CONST_REFERENCE(value)
#define SPARK_IN_P(value) SPARK_CONST_POINTER(value)

#ifdef WINDOWS
#include <Windows.h>

namespace SE
{
	namespace platform
	{
		void notImplementedError(const char* function, const char* file, unsigned int line);
	}
}
#endif
#endif // !__PLATFORMUTILS_H__