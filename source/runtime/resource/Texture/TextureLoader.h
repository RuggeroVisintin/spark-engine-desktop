#ifndef __TEXTURELOADER_H__
#define __TEXTURELOADER_H__

#include <Assertion\Assert.h>
#include <FileSystem\FileSystem.h>
#include <GFX\OpenGL\GLDevice.h>
#include <PlatformUtils.h>

#include "../IResourceLoader.h"
#include "TextureResource.h"

namespace SE
{
	namespace resource
	{
		class TextureLoader : public IResourceLoader<Texture>
		{
			typedef IResourceLoader<Texture>					Super;
			typedef SE::platform::filesystem::OsFileSystem		OsFileSystem;	

		public:
			TextureLoader(OsFileSystem* fileSystem)
			{
				SPARK_ASSERT(fileSystem != nullptr,
					"TextureLoader::TextureLoader passed @param fileSystem is null");

				mFileSystem = fileSystem;
				//mSearchPath = searchPath;
			}

		public:
			virtual Texture loadResource(SE::platform::backend::GLDevice* gfx, const std::string& filePath) override SPARK_NOT_IMPLEMENTED(Texture());
			virtual void	loadResource(SE::platform::backend::GLDevice* gfx, Texture& mesh, const std::string& filePath) override;

		private:
			OsFileSystem*	mFileSystem;
			std::string		mSearchPath;

		};
	}
}

#endif // !__TEXTURELOADER_H__