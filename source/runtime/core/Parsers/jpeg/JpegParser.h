#ifndef __JPEGPARSER_H__
#define __JPEGPARSER_H__

#include <FileSystem/File.h>

namespace SE
{
	namespace core
	{
		namespace parser
		{
			namespace binary
			{
				namespace jpeg
				{
					class JpegParser
					{
					public:
						bool read(SE::platform::filesystem::OsFile* fileHandle);
						bool write(SE::platform::filesystem::OsFile* fileHandle);
					};
				}
			}
		}
	}
}

#endif // !__JPEGPARSER_H__