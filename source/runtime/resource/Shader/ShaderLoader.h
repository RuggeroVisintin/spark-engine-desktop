#ifndef __SHADERLOADER_H__
#define __SHADERLOADER_H__

#include <Assertion/Assert.h>

#include "../Shader/ShaderResource.h"

#include "../IResourceLoader.h"
#include "../ResourceManager.h"

namespace SE
{
	namespace resource
	{
		class ShaderLoader : public IResourceLoader<Shader>
		{
			typedef IResourceLoader<Shader> Super;
			typedef SE::platform::filesystem::OsFileSystem OsFileSystem;

		public:
			ShaderLoader(OsFileSystem* fileSystem,
						 const std::string& searchPath)
			{
				SPARK_ASSERT(fileSystem != nullptr,
					"ShaderLaoder::ShaderLaoder passed @param fileSystem is null");

				mFileSystem = fileSystem;
				mSearchPath = searchPath;
			}

		public:
			virtual Shader			loadResource(SE::platform::backend::GLDevice* gfx, const std::string& filePath) override { return Shader(); }
				virtual void		loadResource(SE::platform::backend::GLDevice* gfx, Shader& shader, const std::string& filePath) override {}

		private:
			OsFileSystem*			mFileSystem;
			std::string				mSearchPath;
		};
	}
}

#endif // !__SHADERLOADER_H__