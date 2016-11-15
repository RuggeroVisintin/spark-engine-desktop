#ifndef __WIN32_FILE_H__
#define __WIN32_FILE_H__

#include <Windows.h>
#include <string>

// NOTES: size_t Win32OsFile::readLine(char* inLine, size_t maxCount) - is still slow but good for now
namespace SE
{
	namespace platform
	{
		namespace filesystem
		{
			class Win32OsFile
			{
				friend class Win32OsFileSystem;

			private:
				enum OpenMode
				{
					FILE_NULL = 0xdeadfff,
					FILE_WRITE = 0,
					FILE_READ,
					FILE_READWRITE,
				};

			private:
				Win32OsFile() : mOpenMode(FILE_NULL), mCurrentPosition(0) {}
				~Win32OsFile() {}

			public:
				virtual size_t			read(void* inBuffer, size_t count);

				// NOTE: tipycally this should be moved in some sort of Lexer class
				virtual size_t			readLine(char* inLine, size_t maxCount);
				virtual size_t			write(const void* outBuffer, size_t count);
				virtual size_t			append(const void* outBuffer, size_t count);

				virtual bool			seekBegin(int position);
				virtual bool			seekCurr(int position);
				virtual bool			seekEnd(int position);

				const std::string&		getName() const { return mFileName; }
				const std::string&		getPath() const { return mFullPath; }
				size_t					getSize() const { return mFileSize; }
				int						getCurrentPosition() const { return mCurrentPosition; }

				bool					isReadOnly() const { return mOpenMode == FILE_READ; }
				bool					isWriteOnly() const { return mOpenMode == FILE_WRITE; }
				bool					isReadWrite() const { return mOpenMode == FILE_READWRITE; }
				bool					isEof() const { return mCurrentPosition == mFileSize; }

			private:
				std::string				mFileName;
				std::string				mFullPath;

				OpenMode				mOpenMode;
				size_t					mFileSize;

				int						mCurrentPosition;
				bool					mSync;

				HANDLE		            mFileHandle;
				OVERLAPPED	            mAsyncHandle;

			};
		}
	}
}

#endif // !__WIN32_FILE_H__