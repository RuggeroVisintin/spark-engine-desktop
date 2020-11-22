#include "TextureResource.h"

namespace SE
{
	namespace resource
	{
		Texture& Texture::loadFromBMP(SPARK_IN_R(SE::core::parser::binary::bitmap::BmpImage) bitmap) {
			this->mWidth = bitmap.getInfo().width;
			this->mHeight = bitmap.getInfo().height;
			
			for (BmpPixels::const_iterator& it = bitmap.getPixels().cbegin(); it != bitmap.getPixels().cend(); it++) {
				this->mData.push_back(it->red);
				this->mData.push_back(it->green);
				this->mData.push_back(it->blue);
			}

			return *this;
		}

		Texture& Texture::initGpuResources(SE::platform::backend::GLDevice* graphicsDevice)
		{
			if (mTextureHandle.isNull()) {
				mTextureHandle = graphicsDevice->create2DTextureHandle();
			}

			graphicsDevice->bindTexture2D(mTextureHandle);
			graphicsDevice->fillTexture2D(0, GL_RGB, this->mWidth, this->mHeight, 0, GL_RGB, GL_FLOAT, this->mData.data());
			graphicsDevice->generateTexture2DMipmap();

			return *this;
		}

	}
}