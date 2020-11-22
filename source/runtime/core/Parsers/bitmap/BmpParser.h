#ifndef __BMPPPARSER_H__
#define __BMPPPARSER_H__

#include <FileSystem\File.h>
#include "BmpImage.h"

namespace SE {
	namespace core {
		namespace parser {
			namespace binary {
				namespace bitmap {
					class BmpParser
					{
					public:
						BmpParser();
						~BmpParser();

					public:
						bool readBitmap(BmpImage& image, SE::platform::filesystem::OsFile* fileHandle);
					};
				}
			}
		}
	}
}

#endif // !__BMPPPARSER_H__
