#include "Assert.h"

namespace SE
{
	namespace platform
	{
		namespace assert
		{
			Win32Assert::Win32Assert(bool condition, const char* error_message, const char* file, const char* function, unsigned int line)
			{
				if (condition == false) {
					// output setup
					std::stringstream string;
					string << std::endl << "Debug Assertion Failed!\n" << std::endl
						<< "FILE:       " << file << std::endl << std::endl
						<< "FUNCTION:	" << function << std::endl
						<< "LINE:       " << line << std::endl << std::endl
						<< "EXPRESSION: " << error_message << std::endl << std::endl;


					#ifdef _MSC_VER
					OutputDebugStringA(string.str().c_str());
					#endif

					int result;

					// loop while..
					do{
						result = MessageBoxA(0, string.str().c_str(), "Debug Assertion Failed!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
					} while (result == 4);

					if (result == 3) {
						std::exit(EXIT_FAILURE);
					}
				}
			}
		}
	}
}