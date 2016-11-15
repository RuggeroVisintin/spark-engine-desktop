#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include <string>
#include "../Platform.h"

#ifdef WINDOWS
#include "PlatformWin32/Win32FileSystem.h"
#endif

namespace SE
{
	namespace platform
	{
		namespace filesystem
		{
#ifdef WINDOWS
			typedef Win32OsFileSystem OsFileSystem;
#endif
		}
	}
}

			//class OsFileSystem
			//{
			//protected:
			//	// struct width path and error type
			//	struct OsErrorCode
			//	{
			//		enum ErrorCode {
			//			FS_NOERROR,		// no errors occured during last operation
			//			FS_DOUBLEPATH,  // there is another file/dir with the same path
			//			FS_NOTFOUND,	// there is no element with this path
			//			FS_ISOPEN,		// the file is already open and can't be shared
			//			FS_NORIGHTS,	// the file exists but you don't have the rights to some specific operations
			//		};

			//		ErrorCode			errorCode;
			//		std::string			wrongPath;
			//		std::string			formattedMessage;
			//	};
			//
			//	enum OsOpenMode
			//	{
			//		FILE_WRITE,
			//		FILE_READ,
			//		FILE_APPEND,
			//		FILE_READWRITE
			//	};

			//public:
			//	OsFileSystem() : mInitialized(false) { mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR; }
			//	virtual ~OsFileSystem() { mSearchPaths.clear(); }

			//public:
			//	virtual void					init() = 0;
			//	virtual void					shutdown() = 0;
			//	virtual void					restart() = 0;

			//	virtual OsFile*					openFileWrite(const std::string& relativePath, const std::string& searchPath = std::string("\0")) = 0;
			//	virtual OsFile*					openFileRead(const std::string& relativePath, const std::string& searchPath = std::string("\0")) = 0;
			//	virtual OsFile*					openFileReadWrite(const std::string& relativePath, const std::string& searchPath = std::string("\0")) = 0;
			//	//virtual OsFile*					openFileAppend(const std::string& relativePath, const std::string& searchPath = std::string("\0")) = 0;

			//	virtual OsFile*					openExplicitFileWrite(const std::string& osPath) = 0;
			//	virtual OsFile*					openExplicitFileRead(const std::string& osPath) = 0;
			//	virtual OsFile*					openExplicitFileReadWrite(const std::string& osPath) = 0;
			//	//virtual OsFile*					openExplicitFileAppend(const std::string& osPath) = 0;

			//	virtual void					closeFile(OsFile* file) = 0;
			//	virtual void					removeFile(const std::string& osPath) = 0;
			//	virtual void					moveFile(const std::string& fromOsPath, const std::string& toOsPath, bool overwrite) = 0;
			//	virtual void					copyFile(const std::string& fromOsPath, const std::string& toOsPath, bool overwrite) = 0;
			//	virtual void					renameFile(const std::string& osPath, const std::string& newName, bool overwrtie) = 0;

			//	virtual void					createDirectory(const std::string& osPath) = 0;
			//	virtual OsDir*					openDirectory(const std::string& relativePath, const std::string& searchPath = std::string("\0")) = 0;
			//	virtual void					closeDirectory(OsDir* directory) = 0;
			//	virtual void					copyDirectory(const std::string& fromOsPath, const std::string& toOsPath, bool merge) = 0;
			//	virtual void					moveDirectory(const std::string& fromOsPath, const std::string& toOsPath, bool merge) = 0;
			//	virtual void					removeDirectory(const std::string& osPath) = 0;
			//	virtual void					renameDirectory(const std::string& osPath, const std::string& newName) = 0;

			//	/**
			//	* @return - true - if given path is a directory
			//	*/
			//	virtual bool					isDirectory(const std::string& osPath) = 0;

			//	/**
			//	* @return -1 if given path isn't a directory else return the size of the directory
			//	*/
			//	virtual int						getDirectorySize(const std::string& osPath) = 0;

			//	virtual std::string				getPathName(const std::string& osPath) = 0;

			//	/**
			//	* @return - true - if given path exists
			//	*/
			//	virtual bool					pathExists(const std::string& osPath) = 0;

			//	/**
			//	* adjust the path removing all "." and "/" symbols at first position
			//	*
			//	* @param path - in/out - the path to adjust
			//	*/
			//	virtual void					adjustPath(std::string& path) = 0;

			//	/**
			//	* if the given path exists and it's a folder add it to the search paths
			//	*
			//	* @param searchPath - in - the path to add to the search paths
			//	*/
			//	void							addSearchPath(const std::string& pathKey, SearchPath_s searchPath);
			//	bool							isSearchPath(const std::string& searchPath) { return mSearchPaths.find(searchPath) != mSearchPaths.end(); }

			//	void							setRootPath(const std::string& searchPath);
			//	const std::string&				getRootPath() const { return mRootPath; }
			//	OsErrorCode						getLastErrorCode() const { return mLastErrorCode; }

			//	bool							isInitialized() const { return mInitialized; }
			//	virtual std::string				buildOsPath(const std::string& relativePath, const std::string& basePath, const std::string& searchPath = std::string("\0")) = 0;

			//protected:
			//	std::map<std::string, SearchPath_s>		mSearchPaths;

			//	std::string								mRootPath;
			//	OsErrorCode								mLastErrorCode;

			//	bool									mInitialized;
			//};




#endif // !__FILESYSTEM_H__