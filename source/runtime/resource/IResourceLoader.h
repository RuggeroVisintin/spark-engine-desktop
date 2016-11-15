#ifndef __IRESOURCELOADER_H__
#define __IRESOURCELOADER_H__

#include <string>

#include <FileSystem/FileSystem.h>
#include <Assertion/Assert.h>

namespace SE
{
	namespace resource
	{
		template <class TResource> class IResourceLoader
		{
		public:
			virtual ~IResourceLoader()
			{
			}

		public:
			virtual TResource							loadResource(SE::platform::backend::GLDevice* gfx, const std::string& filePath) = 0;
			virtual void								loadResource(SE::platform::backend::GLDevice* gfx, TResource& resource, const std::string& filePath) = 0;
		};
	}
}

#endif // !__IRESOURCELOADER_H__