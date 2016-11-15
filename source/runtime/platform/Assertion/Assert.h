#ifndef __ASSERT_H__
#define __ASSERT_H__

#include <string>
#include <sstream>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#if defined(SPARK_DEV) ||  defined(_DEBUG)
#define SPARK_ASSERT(condition, message) do { SE::platform::assert::Win32Assert(condition, message, __FILE__, __FUNCTION__, __LINE__);\
											  if (condition == false){ __debugbreak(); std::exit(EXIT_FAILURE); }\
											} while (0); 
#else
// remove all asserts while in production
#define SPARK_ASSERT(condition, message) {}										
#endif
#endif

namespace SE
{
	namespace platform
	{
		namespace assert
		{
			// TODO: review the implementation

			// use in windows only
			class Win32Assert
			{
			public:
				/**
				* @param condition          - the check you want to pay attention to
				* @param error_message      - the message you want to show if the condition is false
				* @param file               - the file where the error occurs
				* @param line               - the line where the error occurs
				*/
				Win32Assert(bool condition, const char* error_message, const char* file, const char* function, unsigned int line);
				~Win32Assert(){}
			};
		}
	}
}

#endif // !_ASSERT_H_