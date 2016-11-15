#ifndef __MATERIALLOADER_H__
#define __MATERIALLOADER_H__

#include "../IResourceLoader.h"
#include "../ResourceManager.h"

#include "../Texture/TextureResource.h"
#include "MaterialResource.h"

namespace SE
{
	namespace resource
	{
		//class MaterialLoader : public IResourceLoader<Material>
		//{
		//	typedef IResourceLoader<Material>					Super;
		//	typedef SE::platform::filesystem::OsFileSystem		OsFileSystem;
		//	typedef ResourceManager<Texture>					TextureManager;

		//public:
		//	MaterialLoader(OsFileSystem* fileSystem,
		//					const std::string& searchPath/*,
		//					ResourceManager<Texture>* textureManager*/)
		//	{
		//		SPARK_ASSERT(fileSystem != nullptr,
		//			"MaterialLoader::MaterialLoader passed @param fileSystem is null");
		//	}

		//public:
		//	virtual Material		loadResource(const std::string& name) override;
		//	virtual void			loadResource(Material& material) override;

		//private:
		//	OsFileSystem*			mFileSystem;
		//	std::string				mSearchPath;
		//	TextureManager*			mTextureManager;
		//};
	}
}

#endif // !__MATERIALLOADER_H__