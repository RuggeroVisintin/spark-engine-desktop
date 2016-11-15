#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include <vector>
#include <unordered_map>

#include <Assertion/Assert.h>
//#include "GFX/OpenGL/GLDevice.h"

#include "ResourceHandle.h"
#include "Resource.h"
#include "IResourceLoader.h"

namespace SE
{
	namespace resource
	{
		// maybe the right name could be ResourceCache
		// OPTIMIZATIONS: avoid the usage of a realease counter since it is not strictly
		// necessary
		template <class T> class ResourceManager
		{
			typedef std::vector<T>					ResourceVector;
			typedef std::vector<unsigned int*>		CounterVector;
			typedef std::vector<T*>					FreeVector;
			typedef std::vector<std::string>		PathVector;

		public:
			ResourceManager(IResourceLoader<T>* resourceLoader, SE::platform::backend::GLDevice* gfx)
			{
				SPARK_ASSERT((std::is_base_of<SE::resource::IResource, T>::value == true), 
					"ResourceManager::ResourceManager passed @templated-param T is not a derived of IResource");

				SPARK_ASSERT(resourceLoader != nullptr,
					"ResourceManager::ResourceManager passed @param resourceLoader is null");

				SPARK_ASSERT(gfx != nullptr,
					"ResourceManager::ResourceManager passed @param gfx is null");

				mResourceLoader = resourceLoader;
				mGfx = gfx;
			}

		public:
			ResourceHandle				addResource(const std::string& resourceName, const std::string& filePath, ResourceMemType memType);
			ResourceHandle				addResource(const T& resource, const std::string& filePath, ResourceMemType memType);
			//ResourceHandle				addResource(const T& resource, ResourceMemType memType);

			T*							getResource(ResourceHandle& handle);
			void						freeResource(ResourceHandle& handle);

			ResourceHandle				getResourceHandleByPath(const std::string& filePath) const;
			ResourceHandle				getResourceHandleByName(const std::string& resourceName) const;

		protected:
			IResourceLoader<T>*			mResourceLoader;
			SE::platform::backend::GLDevice* mGfx;


			// memory vector of resources
			ResourceVector				mResources[3];

			// total amount of instances of a Resource
			CounterVector				mInstanceCounters[3];

			// count of instances marked as free
			CounterVector				mFreeCounters[3];

			// vector of paths to easy access by handle
			PathVector					mResourcePaths[3];

			// help finding a resource by its path
			std::unordered_map<std::string, std::pair<unsigned int, ResourceMemType>> mResourceMapByPath;
			
			// help finding a resource by its name
			std::unordered_map<std::string, std::pair<unsigned int, ResourceMemType>> mResourceMapByName;
		};

		template <class T>
		ResourceHandle ResourceManager<T>::addResource(const std::string& resourceName, const std::string& filePath, ResourceMemType memType)
		{
			SPARK_ASSERT((mResourceMapByName.find(resourceName) == mResourceMapByName.end()),
				"ResourceManager::addResource the resource is already cached");
			
			SPARK_ASSERT((mResourceMapByPath.find(filePath) == mResourceMapByPath.end()),
				"ResourceManager::addResource the resource is already cached");

			//T resource(resourcePath);
			T resource;
			mResources[memType - 1].push_back(resource);
			mResourcePaths[memType - 1].push_back(filePath);

			mInstanceCounters[memType - 1].push_back(new unsigned int(1));
			mFreeCounters[memType  -1].push_back(new unsigned int(0));

			ResourceHandle result;
			result.mIndex = mResources[memType - 1].size();
			result.mMemType = memType;
			result.mInstancesCount = mInstanceCounters[memType - 1][result.mIndex - 1];
			result.mReleasesCount = mFreeCounters[memType - 1][result.mIndex - 1];

			std::pair<unsigned int, ResourceMemType> pair(result.mIndex, memType);
			mResourceMapByPath.insert({ filePath, pair });
			mResourceMapByName.insert({ resourceName, pair });
			
			return result;
		}

		template <class T>
		ResourceHandle ResourceManager<T>::addResource(const T& resource, const std::string& filePath, ResourceMemType memType)
		{		
			SPARK_ASSERT((mResourceMapByName.find(resource.mName) == mResourceMapByName.end()),
				"ResourceManager::addResource the resource is already cached");

			SPARK_ASSERT((mResourceMapByPath.find(filePath) == mResourceMapByPath.end()),
				"ResourceManager::addResource the resource is already cached");

			ResourceHandle result;
			mResources[memType - 1].push_back(resource);

			//avoid all this heap allocations, maybe use a stack of int
			mInstanceCounters[memType - 1].push_back(new unsigned int(1));
			mFreeCounters[memType - 1].push_back(new unsigned int(0));

			result.mIndex = mResources[memType - 1].size();
			result.mMemType = memType;
			result.mInstancesCount = mInstanceCounters[memType - 1][result.mIndex - 1];
			result.mReleasesCount = mFreeCounters[memType - 1][result.mIndex - 1];

			std::pair<unsigned int, ResourceMemType> pair(result.mIndex, memType);
			mResourceMapByPath.insert({ filePath, pair });
			mResourceMapByName.insert({ resource.mName, pair });

			return result;
		}

		template <class T>
		T* ResourceManager<T>::getResource(ResourceHandle& handle)
		{
			SPARK_ASSERT(handle.mInstancesCount == mInstanceCounters[handle.mMemType - 1][handle.mIndex - 1], 
				"ResourceManager::getResource passed @param handle does not belong to this ResourceManager");

			SPARK_ASSERT(!handle.isNull(), "ResourceManager::getResource passed @param handle is null");

			if (handle.mRelease == true) {
				handle.mRelease = false;
				*(handle.mReleasesCount) -= 1;
			}

			T* resource = &(mResources[handle.mMemType - 1][handle.mIndex - 1]);

			if (resource->mLoaded == false) {
				mResourceLoader->loadResource(mGfx, *(resource), mResourcePaths[handle.mMemType - 1][handle.mIndex - 1]);
				resource->mLoaded = true;
			}

			return resource;
		}

		template <class T>
		ResourceHandle ResourceManager<T>::getResourceHandleByPath(const std::string& resourcePath) const
		{
			SPARK_ASSERT(mResourceMapByPath.find(resourcePath) != mResourceMapByPath.end(),
				"ResourceManager::getResourceHandle no resource with given path was founded");

			std::pair<unsigned int, ResourceMemType> pair = mResourceMapByPath[resourcePath];

			ResourceHandle result;
			result.mIndex = pair.first();
			result.mMemType = pair.second();
			result.mInstancesCount = mInstanceCounters[result.mMemType - 1][result.mIndex - 1];
			result.mReleasesCount = mFreeCounters[result.mMemType - 1][result.mIndex - 1];
			
			return result;
		}

		template <class T>
		ResourceHandle ResourceManager<T>::getResourceHandleByName(const std::string& resourceName) const
		{
			SPARK_ASSERT(mResourceMapByName.find(resourceName) != mResourceMapByName.end(),
				"ResourceManager::getResourceHandle no resource with given path was founded");

			std::pair<unsigned int, ResourceMemType> pair = mResourceMapByName[resourceName];

			ResourceHandle result;
			result.mIndex = pair.first();
			result.mMemType = pair.second();
			result.mInstancesCount = mInstanceCounters[result.mMemType - 1][result.mIndex - 1];
			result.mReleasesCount = mFreeCounters[result.mMemType - 1][result.mIndex - 1];

			return result;
		}

		template <class T>
		void ResourceManager<T>::freeResource(ResourceHandle& handle)
		{
			SPARK_ASSERT(handle.mInstancesCount == mInstanceCounters[handle.mMemType - 1][handle.mIndex - 1],
				"ResourceManager::freeResource passed @param handle does not belong to this ResourceManager");

			SPARK_ASSERT(!handle.isNull(), "ResourceManager::freeResource passed @param handle is null");

			if (handle.mRelease != true) {
				handle.mRelease = true;
				*(mFreeCounters[handle.mMemType - 1][handle.mIndex - 1]) += 1;
			}

			if (handle.mMemType == ResourceMemType::RMT_Dynamic) {
				if (*(mFreeCounters[handle.mMemType - 1][handle.mIndex - 1]) == *(mInstanceCounters[handle.mMemType - 1][handle.mIndex - 1])) {
					std::cout << "free resource" << std::endl;
				}
			}
		}
	}
}

#endif // !__RESOURCEMANAGER_H__