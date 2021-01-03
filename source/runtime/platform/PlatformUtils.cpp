#include "PlatformUtils.h"

namespace SE
{
	namespace platform
	{
		void notImplementedError(const char* function, const char* file, unsigned int line)
		{
			// output setup
			std::stringstream string;
			string << std::endl << "Not Implemented Error!\n" << std::endl
				<< "FILE:       " << file << std::endl << std::endl
				<< "FUNCTION:	" << function << std::endl
				<< "LINE:       " << line << std::endl << std::endl
				<< "EXPRESSION: " << "Function not implemented yet" << std::endl << std::endl;


#ifdef _MSC_VER
			OutputDebugStringA(string.str().c_str());
#endif

			int result;

			// loop while..
			do {
				result = MessageBoxA(0, string.str().c_str(), "Not Implemented Error!", MB_ABORTRETRYIGNORE | MB_ICONERROR);
			} while (result == 4);

			if (result == 3) {
				std::exit(EXIT_FAILURE);
			}
		}
	}
}
