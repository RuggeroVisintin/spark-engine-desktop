#ifndef __MESHLOADER_H__
#define __MESHLOADER_H__

#include <Assertion/Assert.h>

#include "../Material/MaterialResource.h"
#include "MeshResource.h"

#include "../IResourceLoader.h"
#include "../ResourceManager.h"

namespace SE
{
	namespace resource
	{
		// load the mesh from single file
		class MeshLoader : public IResourceLoader<Mesh>
		{
			typedef IResourceLoader<Mesh> Super;
			typedef SE::platform::filesystem::OsFileSystem OsFileSystem;

		public:
			MeshLoader(OsFileSystem* fileSystem,
						const std::string& searchPath/*,
						ResourceManager<Material>* materialManager*/)
			{
				SPARK_ASSERT(fileSystem != nullptr,
					"MeshLoader::MeshLoader passed @param fileSystem is null");

				//SPARK_ASSERT(materialManager != nullptr,
					//"MeshLoader::MeshLoader passed @param materialManager is null");

				//mMaterialManager	= materialManager;
				mFileSystem			= fileSystem;
				mSearchPath			= searchPath;
			}

			~MeshLoader()
			{
			}

		public:
			virtual Mesh					loadResource(SE::platform::backend::GLDevice* gfx, const std::string& filePath) override;
			virtual void					loadResource(SE::platform::backend::GLDevice* gfx, Mesh& mesh, const std::string& filePath) override;

		private:
			OsFileSystem*					mFileSystem;
			std::string						mSearchPath;

			ResourceManager<Material>*		mMaterialManager;
		};
	}
}

#endif // !__MESHLOADER_H__