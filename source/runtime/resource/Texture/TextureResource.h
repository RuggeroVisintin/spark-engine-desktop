#ifndef __TEXTURERESOURCE_H__
#define __TEXTURERESOURCE_H__

#include <vector>

#include "../../Platform/GFX/OpenGL/GLTypes.h"
#include "../../Platform/GFX/OpenGL/GLDevice.h"

namespace SE
{
	namespace resource
	{
		class Texture
		{
			typedef SE::platform::backend::GLTexture2DHandle TextureHandle;

		public:
			Texture()
			{
			}

			~Texture()
			{
			}

		public:
			void				loadFromFile(const char* filePath)
			{
			}

			void				initGpuResources(SE::platform::backend::GLDevice* graphicsDevice)
			{
				if (mTextureHandle.isNull()) {
					mTextureHandle = graphicsDevice->create2DTextureHandle();
				}

				graphicsDevice->bindTexture2D(mTextureHandle);
				graphicsDevice->generateTexture2DMipmap();
			}

		private:
			unsigned char*		mData;
			unsigned int		mWidth;
			unsigned int		mHeight;

			TextureHandle		mTextureHandle;
		};
	}
}

#endif // !__TEXTURERESOURCE_H__