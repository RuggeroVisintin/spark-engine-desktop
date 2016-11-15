#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__


#include "../Platform.h"

#ifdef WINDOWS
#include "PlatformWin32\Win32Directory.h"
#endif

namespace SE
{
	namespace platform
	{
		namespace filesystem
		{
#ifdef WINDOWS
			typedef Win32OsDir OsDir;
#endif

			//class OsDir
			//{
			//public:
			//	enum FileType
			//	{
			//		TYPE_FILE,
			//		TYPE_DIR
			//	};

			//protected:
			//	OsDir() {}
			//	virtual ~OsDir()
			//	{
			//		mFileList.clear();
			//	}

			//public:
			//	const std::string	getName() const { return mDirName; }
			//	const std::string	getPath() const { return mFullPath; }
			//	size_t getSize() const { return mDirSize; }

			//	const std::string& getFromList(unsigned int index, FileType type)
			//	{
			//		if (index < mFileList.size()) {
			//			int i = 0;

			//			for (std::map<std::string, FileType>::iterator it = mFileList.begin(); it != mFileList.end(); it++) {
			//				if (i == index && it->second == type) {
			//					return it->first;
			//				}

			//				i++;
			//			}
			//		}

			//		// returns an empty string intead of null pointer to avoid breakpoints
			//		return "\0";
			//	}

			//protected:

			//protected:
			//	std::string		mDirName;
			//	std::string		mFullPath;

			//	size_t			mDirSize;
			//	bool			mSync;

			//	std::map<std::string, FileType> mFileList;
			//};
		}
	}
}

#endif // !__DIRECTORY_H__