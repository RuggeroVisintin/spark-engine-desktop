#ifndef __TEXTURERESOURCE_H__
#define __TEXTURERESOURCE_H__

#include <vector>

#include "../../Platform/GFX/OpenGL/GLTypes.h"
#include "../../Platform/GFX/OpenGL/GLDevice.h"

#include <FileSystem\FileSystem.h>
#include <PlatformUtils.h>
#include <Assertion\Assert.h>
#include <Parsers\bitmap\BmpImage.h>

#include <PlatformUtils.h>

namespace SE
{
	namespace resource
	{
		class Texture
		{
			typedef SE::platform::backend::GLTexture2DHandle		TextureHandle;
			typedef std::vector<float>								Pixels;
			typedef SE::core::parser::binary::bitmap::BMP_Pixel		BmpPixel;
			typedef std::vector<BmpPixel>							BmpPixels;

		public:
			Texture()
			{
			}

			~Texture()
			{
			}

		public:
			// void loadFromJpeg
			// void loadFromPNG
			Texture&				loadFromBMP(SPARK_IN_R(SE::core::parser::binary::bitmap::BmpImage) bitmap);
			Texture&				initGpuResources(SE::platform::backend::GLDevice* graphicsDevice);
		private:
			Pixels 					mData;
			unsigned int			mWidth;
			unsigned int			mHeight;

			TextureHandle			mTextureHandle;
		};
	}
}

#endif // !__TEXTURERESOURCE_H__