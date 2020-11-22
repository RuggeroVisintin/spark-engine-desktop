#ifndef __BMPIMAGE_H__
#define __BMPIMAGE_H__

#include <vector>
#include <PlatformUtils.h>

#define BMP_FILE_HEADER_SIZE 14
#define BMP_INFO_HEADER_SIZE 40
#define BMP_PIXEL_SIZE 3
namespace SE {
	namespace core {
		namespace parser {
			namespace binary {
				namespace bitmap {
					typedef struct {
						unsigned short type;
						unsigned int size;
						unsigned int reserved;
						unsigned int offBits;

						static unsigned int getSize() {
							return BMP_FILE_HEADER_SIZE;
						}
					} BMP_FileHeader;

					typedef struct {
						unsigned int size;
						unsigned int width;
						int height;
						unsigned short planes;
						unsigned short bitcount;
						unsigned int compression;
						unsigned int imageSize;
						unsigned int xPixelsPerMeter;
						unsigned int yPixelsPerMeter;
						unsigned int unused[2];

						static unsigned int getSize() {
							return BMP_INFO_HEADER_SIZE;
						}
					} BMP_InfoHeader;

					typedef struct {
						unsigned char red;
						unsigned char green;
						unsigned char blue;

						static unsigned int getSize() {
							return BMP_PIXEL_SIZE;
						}
					} BMP_Pixel;

					class BmpImage {
						friend class BmpParser;
					public:
						BmpImage() {}
						~BmpImage() {}

					public:
						SPARK_CONST_REFERENCE(std::vector<BMP_Pixel>)	getPixels() const {
							return mPixels;
						}

						void setPixels(SPARK_CONST_REFERENCE(std::vector<BMP_Pixel>) pixels) {
							mPixels = pixels;
						}

						SPARK_CONST_REFERENCE(BMP_InfoHeader) getInfo() const {
							return mInfoHeader;
						}
					private:
						std::vector<BMP_Pixel>		mPixels;
						BMP_InfoHeader				mInfoHeader;
						BMP_FileHeader				mFileHeader;
					};
				}
			}
		}
	}
}

#endif