#include "BmpParser.h"
#include <Assertion\Assert.h>
#include <stdio.h>

namespace SE {
	namespace core {
		namespace parser {
			namespace binary {
				namespace bitmap {
					BmpParser::BmpParser() {

					}

					BmpParser::~BmpParser() {

					}

					bool BmpParser::readBitmap(BmpImage& image, SE::platform::filesystem::OsFile* fileHandle) {
						SPARK_ASSERT(fileHandle != nullptr, "BmpParser::readBitmap @param fileHandle is not a valid pointer to a file");

						fileHandle->read(&image.mFileHeader, BMP_FileHeader::getSize());
						fileHandle->read(&image.mInfoHeader, BMP_InfoHeader::getSize());

						BMP_Pixel* pixels = (BMP_Pixel*)malloc(BMP_Pixel::getSize() * image.mInfoHeader.width *  image.mInfoHeader.height);
						fileHandle->read(pixels, BMP_Pixel::getSize() *  image.mInfoHeader.width *  image.mInfoHeader.height);
						
						image.mPixels.assign(pixels, pixels + (image.mInfoHeader.width *  image.mInfoHeader.height));

						return true;
					}
				}
			}
		}
	}
}