#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>

namespace SE
{
	namespace resource
	{
		class IResource
		{
			template <class T> friend class ResourceManager;

		public:
			/*IResource(const std::string& name)				
			{
				mName = name;
			}*/

			virtual ~IResource()
			{
			}

		public:
			// don't need to worry about vtable, these functions doesn't need to be called frequently
			//virtual void		deserialize(SE::core::platform::OsFile* fileHandle) = 0;
			//virtual void		initRenderingMemory(SE::platform::backend::GLDevice* graphicsDevice) = 0;
			//virtual void		freeRenderingMemory(SE::platform::backend::GLDevice* graphicsDevice) = 0;
			//virtual void		freeMemory() = 0;		

			const std::string& getName() const	{
				return mName;
			}

			const std::string& getId() const {
				return mResourceId;
			}

			const std::string& getFilePath() const {
				return mFilePath;
			}

			bool isLoaded() const {
				return mLoaded;
			}

		protected:
			std::string			mName;
			std::string			mResourceId;
			std::string			mFilePath; 
			bool				mLoaded;
		};
	}
}

#endif // !__RESOURCE_H__