#ifndef __FXPARSER_H__
#define __FXPARSER_H__

#include "SSLShader.h"
#include <FileSystem/File.h>

namespace SE
{
	namespace core
	{
		namespace parser
		{
			namespace text
			{
				namespace ssl
				{
					class SSLParser
					{
					public:
						bool		writeFx(const SSLShader& shader, SE::platform::filesystem::OsFile* fileHandle);
						bool		readFx(SSLShader& shader, SE::platform::filesystem::OsFile* fileHandle);

					};
				}
			}
		}
	}
}

#endif // !__FXPARSER_H__