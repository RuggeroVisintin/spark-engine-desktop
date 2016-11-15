#ifndef __WIN32_DIRECTORY_H__
#define __WIN32_DIRECTORY_H__

#include <Windows.h>
#include <map>
#include <vector>

namespace SE
{
	namespace platform
	{
		namespace filesystem
		{
			class Win32OsDir
			{
				friend class Win32OsFileSystem;
			public:

				enum FileType
				{
					TYPE_FILE,
					TYPE_DIR
				};

			private:
				Win32OsDir() {}
				virtual ~Win32OsDir()
				{
					mFileList.clear();
				}

			public:
				const std::string	getName() const { return mDirName; }
				const std::string	getPath() const { return mFullPath; }
				size_t getSize() const { return mDirSize; }

				const std::string& getFromList(unsigned int index, FileType type)
				{
					if (index < mFileList.size()) {
						int i = 0;

						for (std::map<std::string, FileType>::iterator it = mFileList.begin(); it != mFileList.end(); it++) {
							if (i == index && it->second == type) {
								return it->first;
							}

							i++;
						}
					}

					// returns an empty string intead of null pointer to avoid breakpoints
					return "\0";
				}

			private:
				std::string		mDirName;
				std::string		mFullPath;

				size_t			mDirSize;
				bool			mSync;

				std::map<std::string, FileType> mFileList;

				HANDLE		mDirHandle;
			};
		}
	}
}

#endif // !____WIN32_DIRECTORY_H__