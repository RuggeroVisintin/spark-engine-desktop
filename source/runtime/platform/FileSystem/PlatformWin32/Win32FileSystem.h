#ifndef __WIN32_FILESYSTEM_H__
#define __WIN32_FILESYSTEM_H__

#include <Windows.h>
#include "Win32File.h"
#include "Win32Directory.h"

namespace SE
{
	namespace platform
	{
		namespace filesystem
		{
			struct SearchPath_s
			{
				enum AccesRight
				{
					AR_READONLY,	// only reading operations are allowed on files in the path
					AR_WRITEONLY,	// only writing operations are allowed on files in the path
					AR_READWRITE	// both writing and reading operations are allowed on files in the path
				};

				AccesRight		mAccesRight;
				std::string		mRawPath;
			};

			class Win32OsFileSystem
			{
			private:
				// struct width path and error type
				struct OsErrorCode
				{
					enum ErrorCode {
						FS_NOERROR,		// no errors occured during last operation
						FS_DOUBLEPATH,  // there is another file/dir with the same path
						FS_NOTFOUND,	// there is no element with this path
						FS_ISOPEN,		// the file is already open and can't be shared
						FS_NORIGHTS,	// the file exists but you don't have the rights to some specific operations
					};

					ErrorCode			errorCode;
					std::string			wrongPath;
					std::string			formattedMessage;
				};

				enum OsOpenMode
				{
					FILE_WRITE,
					FILE_READ,
					FILE_APPEND,
					FILE_READWRITE
				};

			public:
				Win32OsFileSystem(const std::string& rootPath) 
				{
					this->setRootPath(rootPath);
				}

				~Win32OsFileSystem() {}

			public:
				Win32OsFile*					openFileWrite(const std::string& relativePath, const std::string& searchPath = std::string("\0"));
				Win32OsFile*					openFileRead(const std::string& relativePath, const std::string& searchPath = std::string("\0"));
				Win32OsFile*					openFileReadWrite(const std::string & relativePath, const std::string& searchPath = std::string("\0"));
				//virtual	Win32OsFile*				openFileAppend(const std::string& relativePath, const std::string& searchPath = std::string("\0")) override;

				Win32OsFile*					openExplicitFileWrite(const std::string& osPath);
				Win32OsFile*					openExplicitFileRead(const std::string& osPath);
				Win32OsFile*					openExplicitFileReadWrite(const std::string& osPath);
				//virtual Win32OsFile*					openExplicitFileAppend(const std::string& osPath) override; // TODO:

				void							closeFile(Win32OsFile* win32OsFile);
				void							removeFile(const std::string& osPath);
				void							moveFile(const std::string& fromOsPath, const std::string& toOsPath, bool overwrite);
				void							copyFile(const std::string& fromOsPath, const std::string& toOsPath, bool overwrite);
				void							renameFile(const std::string& osPath, const std::string& newName, bool overwrtie);

				void							createDirectory(const std::string& osPath);
				Win32OsDir*						openDirectory(const std::string& relativePath, const std::string& searchPath = std::string("\0"));
				void							closeDirectory(Win32OsDir* directory);
				void							copyDirectory(const std::string& fromOsPath, const std::string& toOsPath, bool merge);
				void							moveDirectory(const std::string& fromOsPath, const std::string& toOsPath, bool merge);
				void							removeDirectory(const std::string& osPath);
				void							renameDirectory(const std::string& osPath, const std::string& newName);

				bool							isDirectory(const std::string& osPath);
				int								getDirectorySize(const std::string& osPath);
				std::string						getPathName(const std::string& osPath);

				bool							pathExists(const std::string& osPath);
				void							adjustPath(std::string& osPath);
				std::string						buildOsPath(const std::string& relativePath, const std::string& basePath, const std::string& searchPath = std::string("\0"));

				/**
				* if the given path exists and it's a folder add it to the search paths
				*
				* @param searchPath - in - the path to add to the search paths
				*/
				void							addSearchPath(const std::string& pathKey, SearchPath_s searchPath);
				bool							isSearchPath(const std::string& searchPath) { return mSearchPaths.find(searchPath) != mSearchPaths.end(); }

				void							setRootPath(const std::string& searchPath);
				const std::string&				getRootPath() const { return mRootPath; }
				OsErrorCode						getLastErrorCode() const { return mLastErrorCode; }

			private:
				HANDLE							openOsFile(const char* osPath, OsOpenMode openMode);
				void							closeOsFile(HANDLE fileHandle);

				HANDLE							openOsDir(const char* osPath, WIN32_FIND_DATAA* data);
				void							closeOsDir(HANDLE dirHandle);

			private:
				std::map<std::string, SearchPath_s>		mSearchPaths;

				std::string								mRootPath;
				OsErrorCode								mLastErrorCode;

			};
		}
	}
}

#endif // !__WIN32_FILESYSTEM_H__