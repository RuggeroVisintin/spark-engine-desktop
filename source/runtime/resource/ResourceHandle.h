#ifndef __RESOURCEHANDLE_H__
#define __RESOURCEHANDLE_H__

#include <string>

namespace SE
{
	namespace resource
	{
		enum ResourceMemType
		{
			RMT_Null			= 0,
			RMT_Persistent		= 1, // resources loaded only once that will never be freed 
			RMT_Dynamic			= 2, // resources which lifetime is dinamycally managed
			RMT_Level			= 3	 // resources that will be freed/loaded due to a level change
		};

		class ResourceHandle
		{
			template <class T> friend class				ResourceManager;

		public:
			// evaluate factory pattern, ResourceManager would be the Factory
			ResourceHandle()
				: mInstancesCount(nullptr)
				, mReleasesCount(nullptr)
				, mIndex(0)
				, mRelease(false)
				, mMemType(RMT_Null)
			{
			}

			ResourceHandle(const ResourceHandle& handle)
				: mRelease(false)
			{
				*this = handle;
			}

			~ResourceHandle()
			{
				if (mRelease == true) {
					(*mReleasesCount) -= 1;					
				}

				(*mInstancesCount) -= 1;

				mInstancesCount		= nullptr;
				mReleasesCount		= nullptr;
			}

		public:
			void operator=(const ResourceHandle& handle)
			{
				if (mRelease == true) {
					*(mReleasesCount) -= 1;
				}

				mInstancesCount = handle.mInstancesCount;
				mReleasesCount = handle.mReleasesCount;

				if (mInstancesCount != nullptr) {
					(*mInstancesCount) += 1;
				}

				mMemType = handle.mMemType;
				mIndex = handle.mIndex;
				mRelease = false;
			}

			bool isNull() const
			{
				return mIndex == 0;
			}

		private:
			bool								mRelease;
			ResourceMemType						mMemType;

			unsigned int*						mInstancesCount;
			unsigned int*						mReleasesCount;

			unsigned int						mIndex;
		};
	}
}

#endif // !__RESOURCEHANDLE_H__