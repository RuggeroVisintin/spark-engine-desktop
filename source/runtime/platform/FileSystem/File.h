#ifndef __FILE_H__
#define __FILE_H__

#include "../Platform.h"

#ifdef WINDOWS
#include "PlatformWin32\Win32File.h"
#endif

// NOTES: size_t OsFile::readLine(char* inLine, size_t maxCount) - on Windows implementation this is still slow but good for now

namespace SE
{
	namespace platform
	{
		namespace filesystem
		{
#ifdef WINDOWS
			typedef Win32OsFile OsFile;
#endif

			//class OsFile
			//{
			//	friend class OsFileSystem;

			//public:
			//	enum OpenMode
			//	{
			//		FILE_NULL = 0xdeadfff,
			//		FILE_WRITE = 0,
			//		FILE_READ,
			//		FILE_READWRITE,
			//	};

			//public:
			//	OsFile() : mOpenMode(FILE_NULL), mCurrentPosition(0) {}
			//	virtual ~OsFile() {}

			//	virtual size_t					read(void* inBuffer, size_t count) = 0;
			//	virtual size_t					readLine(char* inLine, size_t maxCount) = 0;
			//	virtual size_t					write(const void* outBuffer, size_t count) = 0;
			//	virtual size_t					append(const void* outBuffer, size_t count) = 0;

			//	virtual bool					seekBegin(int position) = 0;
			//	virtual bool					seekCurr(int position) = 0;
			//	virtual bool					seekEnd(int position) = 0;

			//	const std::string&				getName() const { return mFileName; }
			//	const std::string&				getPath() const { return mFullPath; }
			//	size_t							getSize() const { return mFileSize; }
			//	int								getCurrentPosition() const { return mCurrentPosition; }

			//	bool							isReadOnly() const { return mOpenMode == FILE_READ; }
			//	bool							isWriteOnly() const { return mOpenMode == FILE_WRITE; }
			//	bool							isReadWrite() const { return mOpenMode == FILE_READWRITE; }
			//	bool							isEof() const { return mCurrentPosition == mFileSize; }

			//protected:
			//	std::string						mFileName;
			//	std::string						mFullPath;

			//	OpenMode						mOpenMode;
			//	size_t							mFileSize;

			//	int								mCurrentPosition;
			//	bool							mSync;
			//};
		}
	}
}

#endif // !_OSFILE_H__