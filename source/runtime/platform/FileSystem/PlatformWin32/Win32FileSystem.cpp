#include "Win32FileSystem.h"
#include "../../Assertion/Assert.h"

namespace SE
{
	namespace platform
	{
		namespace filesystem
		{
			Win32OsFile* Win32OsFileSystem::openFileWrite(const std::string& relativePath, const std::string& searchPath)
			{
				SPARK_ASSERT(relativePath.c_str() != 0, "Win32OsFileSystem::openFileWrite - @param relativePath - is empty");
				SPARK_ASSERT(relativePath.find(":") == -1, "Win32OsFileSystem::openFileWrite - @param relativePath - is not a relative path");
				SPARK_ASSERT(relativePath.find("..") == -1, "Win32OsFileSystem::openFileWrite '..' invalid symbol found in - @param relativePath -");
				SPARK_ASSERT(relativePath.find("\\") == -1, "Win32OsFileSystem::openFileWrite '\\' invalid symbol found in - @param relativePath -");
		
				std::string relPath = relativePath;

				adjustPath(relPath);
				SPARK_ASSERT(relPath[0] != '\0', "Win32OsFileSystem::openFileWrite - @param relativePath - is empty");

				std::string osPath;
				bool found = false;

				if (searchPath[0] != '\0') {
					for (std::map<std::string, SearchPath_s>::iterator it = mSearchPaths.begin(); it != mSearchPaths.end(); it++) {
						if ((*it).first.compare(searchPath) != -1) {
							found = true;

							if ((*it).second.mAccesRight == (*it).second.AR_READONLY) {
								mLastErrorCode.wrongPath = (*it).second.mRawPath;
								mLastErrorCode.wrongPath = "the selected path has read_only rights";
								mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
								return NULL;
							}

							osPath = buildOsPath(relativePath, mRootPath, (*it).second.mRawPath);
							break;
						}
					}

					if (!found) {			
						mLastErrorCode.wrongPath = "cannot found selected path";
						mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
						return NULL;
					}
				} else {
					std::map<std::string, SearchPath_s>::iterator it = mSearchPaths.begin();

					osPath = buildOsPath(relativePath, mRootPath);

					if (pathExists(osPath)) {
						if ((*it).second.mAccesRight == (*it).second.AR_READONLY) {
							mLastErrorCode.wrongPath = (*it).second.mRawPath;
							mLastErrorCode.wrongPath = "the selected path has read_only rights";
							mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
							return NULL;
						}
					}

					while (it != mSearchPaths.end()) {
						osPath = buildOsPath(relativePath, mRootPath, (*it).second.mRawPath);

						if (pathExists(osPath)) {
							if ((*it).second.mAccesRight == (*it).second.AR_READONLY) {
								mLastErrorCode.wrongPath = (*it).second.mRawPath;
								mLastErrorCode.wrongPath = "the selected path has read_only rights";
								mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
								return NULL;
							}

							break;
						}

						it++;
					}

					if (!pathExists(osPath)) {
						osPath = buildOsPath(relativePath, mRootPath);
					}
				}	 

				if (isDirectory(osPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return NULL;
				}

				HANDLE fh = openOsFile(osPath.c_str(), Win32OsFileSystem::FILE_WRITE);
	
				if (fh == INVALID_HANDLE_VALUE) {

					WIN32_FIND_DATAA FindFileData;

					if (FindFirstFileA(osPath.c_str(), &FindFileData) == INVALID_HANDLE_VALUE) {
						mLastErrorCode.wrongPath = osPath;
						mLastErrorCode.wrongPath = "cannot found selected path";
						mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					} else {
						mLastErrorCode.wrongPath = osPath;
						mLastErrorCode.wrongPath = "selected path is already opened";
						mLastErrorCode.errorCode = OsErrorCode::FS_ISOPEN;
					}

					return NULL;
				}
	
				LARGE_INTEGER fileSize;
				GetFileSizeEx(fh, &fileSize);

				Win32OsFile* result			= new Win32OsFile();
				result->mFileHandle			= fh;
				result->mFullPath			= osPath;
				result->mOpenMode			= Win32OsFile::FILE_WRITE;
				result->mFileSize			= fileSize.QuadPart;
				result->mSync				= true;
				result->mFileName			= getPathName(osPath);

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;

				return result;
			}

			Win32OsFile* Win32OsFileSystem::openFileRead(const std::string& relativePath, const std::string& searchPath)
			{
				SPARK_ASSERT(relativePath.c_str() != 0, "Win32OsFileSystem::openFileRead - @param relativePath - is empty");
				SPARK_ASSERT(relativePath.find(":") == -1, "Win32OsFileSystem::openFileRead - @param relativePath - is not a relative path");
				SPARK_ASSERT(relativePath.find("..") == -1, "Win32OsFileSystem::openFileRead '..' invalid symbol found in - @param relativePath -");
				SPARK_ASSERT(relativePath.find("\\") == -1, "Win32OsFileSystem::openFileRead '\\' invalid symbol found in - @param relativePath -");

				std::string relPath = relativePath;
				adjustPath(relPath);

				SPARK_ASSERT(relPath[0] != '\0', "Win32OsFileSystem::openFileRead - @param relativePath - is empty");

				std::string osPath;
				bool found = false;

				if (searchPath[0] != '\0') {
					for (std::map<std::string, SearchPath_s>::iterator it = mSearchPaths.begin(); it != mSearchPaths.end(); it++) {
						if ((*it).first.compare(searchPath) != -1) {
							found = true;

							if ((*it).second.mAccesRight == (*it).second.AR_WRITEONLY) {
								mLastErrorCode.wrongPath = (*it).second.mRawPath;
								mLastErrorCode.wrongPath = "the selected path has write_only rights";
								mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
								return NULL;
							}


							osPath = buildOsPath(relativePath, mRootPath, (*it).second.mRawPath);
							break;
						}
					}

					if (!found) {
						mLastErrorCode.wrongPath = osPath;
						mLastErrorCode.wrongPath = "cannot found selected path";
						mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
						return NULL;			
					}
				} else {
					std::map<std::string, SearchPath_s>::iterator it = mSearchPaths.begin();

					osPath = buildOsPath(relativePath, mRootPath);

					if (pathExists(osPath)) {
						if (it != mSearchPaths.end()) {
							if ((*it).second.mAccesRight == (*it).second.AR_WRITEONLY) {
								mLastErrorCode.wrongPath = (*it).second.mRawPath;
								mLastErrorCode.wrongPath = "the selected path has write_only rights";
								mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
								return NULL;
							}
						}
					}

					while (it != mSearchPaths.end()) {
						osPath = buildOsPath(relativePath, mRootPath, (*it).second.mRawPath);

						if (pathExists(osPath)) {
							if ((*it).second.mAccesRight == (*it).second.AR_WRITEONLY) {
								mLastErrorCode.wrongPath = (*it).second.mRawPath;
								mLastErrorCode.wrongPath = "the selected path has write_only rights";
								mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
								return NULL;
							}

							break;
						}

						it++;
					}
				}

				if (!pathExists(osPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return NULL;
				}

				if (isDirectory(osPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return NULL;
				}

				HANDLE fh = openOsFile(osPath.c_str(), Win32OsFileSystem::FILE_READ);

				if (fh == INVALID_HANDLE_VALUE) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "selected path is already opened";
					mLastErrorCode.errorCode = OsErrorCode::FS_ISOPEN;
					return NULL;
				}

				LARGE_INTEGER fileSize;
				GetFileSizeEx(fh, &fileSize);

				Win32OsFile* result			= new Win32OsFile();
				result->mFileHandle			= fh;
				result->mFullPath			= osPath;
				result->mOpenMode			= Win32OsFile::FILE_READ;
				result->mFileSize			= fileSize.QuadPart;
				result->mSync				= true;
				result->mFileName			= getPathName(osPath);

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;

				return result;
			}

			Win32OsFile* Win32OsFileSystem::openFileReadWrite(const std::string& relativePath, const std::string& searchPath)
			{
				SPARK_ASSERT(relativePath.c_str() != 0, "Win32OsFileSystem::openFileReadWrite - @param relativePath - is empty");
				SPARK_ASSERT(relativePath.find(":") == -1, "Win32OsFileSystem::openFileReadWrite - @param relativePath - is not a relative path");
				SPARK_ASSERT(relativePath.find("..") == -1, "Win32OsFileSystem::openFileReadWrite '..' invalid symbol found in - @param relativePath -");
				SPARK_ASSERT(relativePath.find("\\") == -1, "Win32OsFileSystem::openFileReadWrite '\\' invalid symbol found in - @param relativePath -");

				std::string tempRelativePath = relativePath;
				adjustPath(tempRelativePath);

				SPARK_ASSERT(tempRelativePath[0] != '\0', "Win32OsFileSystem::openFileReadWrite - @param relativePath - is empty");

				std::string osPath;
				bool found = false;

				if (searchPath[0] != '\0') {
					for (std::map<std::string, SearchPath_s>::iterator it = mSearchPaths.begin(); it != mSearchPaths.end(); it++) {
						if ((*it).first.compare(searchPath) != -1) {
							found = true;

							if ((*it).second.mAccesRight == (*it).second.AR_WRITEONLY) {
								mLastErrorCode.wrongPath = (*it).second.mRawPath;
								mLastErrorCode.wrongPath = "the selected path has write_only rights";
								mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
								return NULL;
							}

							osPath = buildOsPath(relativePath, mRootPath, (*it).second.mRawPath);
							break;
						}
					}

					if (!found) {
						mLastErrorCode.wrongPath = osPath;
						mLastErrorCode.wrongPath = "cannot found selected path";
						mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
						return NULL;
					}
				} else {
					std::map<std::string, SearchPath_s>::iterator it = mSearchPaths.begin();

					osPath = buildOsPath(relativePath, mRootPath);

					if (it != mSearchPaths.end()) {
						if (pathExists(osPath)) {
							if ((*it).second.mAccesRight == (*it).second.AR_READWRITE) {
								mLastErrorCode.wrongPath = (*it).second.mRawPath;
								mLastErrorCode.wrongPath = "the selected path has write_only rights";
								mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
								return NULL;
							}
						}
					}

					while (it != mSearchPaths.end()) {
						osPath = buildOsPath(relativePath, mRootPath, (*it).second.mRawPath);

						if (pathExists(osPath)) {
							if ((*it).second.mAccesRight == (*it).second.AR_READWRITE) {
								mLastErrorCode.wrongPath = (*it).second.mRawPath;
								mLastErrorCode.wrongPath = "the selected path has write_only rights";
								mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
								return NULL;
							}

							break;
						}

						it++;
					}
				}

				if (!pathExists(osPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return NULL;
				}

				if (isDirectory(osPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return NULL;
				}

				HANDLE fh = openOsFile(osPath.c_str(), Win32OsFileSystem::FILE_READ);

				if (fh == INVALID_HANDLE_VALUE) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "selected path is already opened";
					mLastErrorCode.errorCode = OsErrorCode::FS_ISOPEN;
					return NULL;
				}

				LARGE_INTEGER fileSize;
				GetFileSizeEx(fh, &fileSize);

				Win32OsFile* result			= new Win32OsFile();
				result->mFileHandle			= fh;
				result->mFullPath			= osPath;
				result->mOpenMode			= Win32OsFile::FILE_READ;
				result->mFileSize			= fileSize.QuadPart;
				result->mSync				= true;
				result->mFileName			= getPathName(osPath);

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;

				return result;
			}

			/*Win32OsFile* Win32OsFileSystem::openFileAppend(const std::string& relativePath, const std::string& searchPath)
			{
				SPARK_ASSERT(mInitialized == true, "Win32OSFileSyste::openFileAppend function call made without initialization");
				SPARK_ASSERT(relativePath.c_str() != 0, "Win32OsFileSystem::openFileAppend - @param relativePath - is empty");
				SPARK_ASSERT(relativePath.find(":") == -1, "Win32OsFileSystem::openFileAppend - @param relativePath - is not a relative path");
				SPARK_ASSERT(relativePath.find("..") == -1, "Win32OsFileSystem::openFileAppend '..' invalid symbol found in - @param relativePath -");
				SPARK_ASSERT(relativePath.find("\\") == -1, "Win32OsFileSystem::openFileAppend '\\' invalid symbol found in - @param relativePath -");

				std::string relPath = relativePath;
				adjustPath(relPath);

				SPARK_ASSERT(relPath[0] != '\0', "Win32OsFileSystem::openFileAppend - @param relativePath - is empty");

				std::string osPath;
				bool found = false;

				if (searchPath[0] != '\0') {
					for (std::map<std::string, ISearchPath>::iterator it = mSearchPaths.begin(); it != mSearchPaths.end(); it++) {
						if ((*it).first.compare(searchPath) != -1) {
							found = true;

							if ((*it).second.mAccesRight == (*it).second.AR_READONLY) {
								mLastErrorCode.wrongPath = (*it).second.mRawPath;
								mLastErrorCode.wrongPath = "the selected path has read_only rights";
								mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
								return NULL;
							}

							osPath = buildOsPath(relativePath, mRootPath, (*it).second.mRawPath);
							break;
						}
					}

					if (!found) {
						mLastErrorCode.wrongPath = osPath;
						mLastErrorCode.wrongPath = "cannot found selected path";
						mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
						return NULL;
					}
				}
				else {
					std::map<std::string, ISearchPath>::iterator it = mSearchPaths.begin();

					osPath = buildOsPath(relativePath, mRootPath);

					if (pathExists(osPath)) {
						if ((*it).second.mAccesRight == (*it).second.AR_READONLY) {
							mLastErrorCode.wrongPath = (*it).second.mRawPath;
							mLastErrorCode.wrongPath = "the selected path has read_only rights";
							mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
							return NULL;
						}
					}

					while (it != mSearchPaths.end()) {
						osPath = buildOsPath(relativePath, mRootPath, (*it).second.mRawPath);

						if (pathExists(osPath)) {
							if ((*it).second.mAccesRight == (*it).second.AR_READONLY) {
								mLastErrorCode.wrongPath = (*it).second.mRawPath;
								mLastErrorCode.wrongPath = "the selected path has read_only rights";
								mLastErrorCode.errorCode = OsErrorCode::FS_NORIGHTS;
								return NULL;
							}

							break;
						}

						it++;
					}

					if (!pathExists(osPath)) {
						osPath = buildOsPath(relativePath, mRootPath);
					}
				}

				if (isDirectory(osPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return NULL;
				}

				HANDLE fh = openOsFile(osPath.c_str(), Win32OsFileSystem::FILE_APPEND);

				if (fh == INVALID_HANDLE_VALUE) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "selected path is already opened";
					mLastErrorCode.errorCode = OsErrorCode::FS_ISOPEN;
					return NULL;
				}

				LARGE_INTEGER fileSize;
				GetFileSizeEx(fh, &fileSize);

				Win32OsFile* result		= new Win32OsFile();
				result->mFileHandle		= fh;
				result->mFullPath		= osPath;
				result->mOpenMode		= Win32OsFile::FILE_APPEND;
				result->mFileSize		= fileSize.QuadPart;
				result->mSync			= true;
				result->seekEnd(0);
	
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;

				return result;
			}*/

			Win32OsFile* Win32OsFileSystem::openExplicitFileWrite(const std::string& osPath)
			{
				SPARK_ASSERT(!osPath.empty(), "Win32OsFileSystem::openExplicitFileWrite - @param osPath - is empty");
				SPARK_ASSERT(osPath.find(":") != -1, "Win32OsFileSystem::openExplicitFileWrite - @param osPath - is not an absolute path");
				SPARK_ASSERT(osPath.find("..") == -1, "Win32OsFileSystem::openExplicitFileWrite '..' invalid symbol found in - @param osPath -");
				SPARK_ASSERT(osPath.find("\\") == -1, "Win32OsFileSystem::openExplicitFileWrite '\\' invalid symbol found in - @param osPath -");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(!tempOsPath.empty(), "Win32OsFileSystem::openExplicitFileWrite - @param osPath - is empty");

				if (isDirectory(tempOsPath)) {
					mLastErrorCode.wrongPath = tempOsPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return NULL;
				}

				HANDLE fh = openOsFile(tempOsPath.c_str(), Win32OsFileSystem::FILE_WRITE);

				if (fh == INVALID_HANDLE_VALUE) {
					mLastErrorCode.wrongPath = tempOsPath;
					mLastErrorCode.wrongPath = "selected path is already opened";
					mLastErrorCode.errorCode = OsErrorCode::FS_ISOPEN;
					return NULL;
				}

				LARGE_INTEGER fileSize;
				GetFileSizeEx(fh, &fileSize);

				Win32OsFile* result		= new Win32OsFile();
				result->mFileName		= getPathName(tempOsPath);
				result->mFileHandle		= fh;
				result->mFullPath		= tempOsPath;
				result->mOpenMode		= Win32OsFile::FILE_WRITE;
				result->mFileSize		= fileSize.QuadPart;
				result->mSync			= true;

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;

				return result;
			}

			Win32OsFile* Win32OsFileSystem::openExplicitFileRead(const std::string& osPath)
			{
				SPARK_ASSERT(!osPath.empty(), "Win32OsFileSystem::openExplicitFileWrite - @param osPath - is empty");
				SPARK_ASSERT(osPath.find(":") != -1, "Win32OsFileSystem::openExplicitFileWrite - @param osPath - is not an absolute path");
				SPARK_ASSERT(osPath.find("..") == -1, "Win32OsFileSystem::openExplicitFileWrite '..' invalid symbol found in - @param osPath -");
				SPARK_ASSERT(osPath.find("\\") == -1, "Win32OsFileSystem::openExplicitFileWrite '\\' invalid symbol found in - @param osPath -");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(!tempOsPath.empty(), "Win32OsFileSystem::openExplicitFileWrite - @param osPath - is empty");

				if (!pathExists(tempOsPath) || isDirectory(tempOsPath)) {
					mLastErrorCode.wrongPath = tempOsPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return NULL;
				}

				HANDLE fh = openOsFile(tempOsPath.c_str(), Win32OsFileSystem::FILE_READ);

				if (fh == INVALID_HANDLE_VALUE) {
					mLastErrorCode.wrongPath = tempOsPath;
					mLastErrorCode.wrongPath = "selected path is already opened";
					mLastErrorCode.errorCode = OsErrorCode::FS_ISOPEN;
					return NULL;
				}

				LARGE_INTEGER fileSize;
				GetFileSizeEx(fh, &fileSize);

				Win32OsFile* result = new Win32OsFile();
				result->mFileName = getPathName(tempOsPath);
				result->mFileHandle = fh;
				result->mFullPath = tempOsPath;
				result->mOpenMode = Win32OsFile::FILE_READ;
				result->mFileSize = fileSize.QuadPart;
				result->mSync = true;

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;

				return result;
			}

			Win32OsFile* Win32OsFileSystem::openExplicitFileReadWrite(const std::string& osPath)
			{
				SPARK_ASSERT(!osPath.empty(), "Win32OsFileSystem::openExplicitFileReadWrite - @param osPath - is empty");
				SPARK_ASSERT(osPath.find(":") != -1, "Win32OsFileSystem::openExplicitFileReadWrite - @param osPath - is not an absolute path");
				SPARK_ASSERT(osPath.find("..") == -1, "Win32OsFileSystem::openExplicitFileReadWrite '..' invalid symbol found in - @param osPath -");
				SPARK_ASSERT(osPath.find("\\") == -1, "Win32OsFileSystem::openExplicitFileReadWrite '\\' invalid symbol found in - @param osPath -");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(!tempOsPath.empty(), "Win32OsFileSystem::openExplicitFileReadWrite - @param osPath - is empty");

				if (isDirectory(tempOsPath)) {
					mLastErrorCode.wrongPath = tempOsPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return NULL;
				}

				HANDLE fh = openOsFile(tempOsPath.c_str(), Win32OsFileSystem::FILE_READWRITE);

				if (fh == INVALID_HANDLE_VALUE) {
					mLastErrorCode.wrongPath = tempOsPath;
					mLastErrorCode.wrongPath = "selected path is already opened";
					mLastErrorCode.errorCode = OsErrorCode::FS_ISOPEN;
					return NULL;
				}

				LARGE_INTEGER fileSize;
				GetFileSizeEx(fh, &fileSize);

				Win32OsFile* result		= new Win32OsFile();
				result->mFileName		= getPathName(tempOsPath);
				result->mFileHandle		= fh;
				result->mFullPath		= tempOsPath;
				result->mOpenMode		= Win32OsFile::FILE_READWRITE;
				result->mFileSize		= fileSize.QuadPart;
				result->mSync			= true;

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;

				return result;
			}

			/*Win32OsFile* Win32OsFileSystem::openExplicitFileAppend(const std::string& osPath)
			{
				SPARK_ASSERT(!osPath.empty(), "Win32OsFileSystem::openExplicitFileWrite - @param osPath - is empty");
				SPARK_ASSERT(osPath.find(":") != -1, "Win32OsFileSystem::openExplicitFileWrite - @param osPath - is not an absolute path");
				SPARK_ASSERT(osPath.find("..") == -1, "Win32OsFileSystem::openExplicitFileWrite '..' invalid symbol found in - @param osPath -");
				SPARK_ASSERT(osPath.find("\\") == -1, "Win32OsFileSystem::openExplicitFileWrite '\\' invalid symbol found in - @param osPath -");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(!tempOsPath.empty(), "Win32OsFileSystem::openExplicitFileWrite - @param osPath - is empty");

				if (isDirectory(tempOsPath)) {
					mLastErrorCode.wrongPath = tempOsPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return NULL;
				}

				HANDLE fh = openOsFile(tempOsPath.c_str(), Win32OsFileSystem::FILE_APPEND);

				if (fh == INVALID_HANDLE_VALUE) {
					mLastErrorCode.wrongPath = tempOsPath;
					mLastErrorCode.wrongPath = "selected path is already opened";
					mLastErrorCode.errorCode = OsErrorCode::FS_ISOPEN;
					return NULL;
				}

				LARGE_INTEGER fileSize;
				GetFileSizeEx(fh, &fileSize);

				Win32OsFile* result = new Win32OsFile();
				result->mFileName = getPathName(tempOsPath);
				result->mFileHandle = fh;
				result->mFullPath = tempOsPath;
				result->mOpenMode = Win32OsFile::FILE_APPEND;
				result->mFileSize = fileSize.QuadPart;
				result->mSync = true;
				result->seekEnd(0);

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;

				return result;
			}*/

			void Win32OsFileSystem::closeFile(Win32OsFile* win32OsFile)
			{
				if (win32OsFile != NULL) {
					closeOsFile(win32OsFile->mFileHandle);
					delete win32OsFile;
				}
			}

			void Win32OsFileSystem::removeFile(const std::string& osPath)
			{
				SPARK_ASSERT(osPath.c_str() != 0, "Win32OsFileSystem::removeFile - @param osPath - is empty");
				SPARK_ASSERT(osPath.find(":") != -1, "Win32OsFileSystem::removeFile - @param osPath - is not an absolute path");
				SPARK_ASSERT(osPath.find("..") == -1, "Win32OsFileSystem::removeFile '..' invalid symbol found in - @param osPath -");
				SPARK_ASSERT(osPath.find("\\") == -1, "Win32OsFileSystem::removeFile '\\' invalid symbol found in - @param osPath -");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(tempOsPath[0] != '\0', "Win32OsFileSystem::removeFile - @param osPath - is empty");

				if (!pathExists(tempOsPath) || isDirectory(tempOsPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}

				DeleteFileA(tempOsPath.c_str());

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
			}

			void Win32OsFileSystem::moveFile(const std::string& fromOsPath, const std::string& toOsPath, bool overwrite)
			{
				SPARK_ASSERT(fromOsPath.c_str() != 0, "Win32OsFileSystem::moveFile - @param fromOsPath - is empty");
				SPARK_ASSERT(fromOsPath.find("\\") == -1, "Win32OsFileSystem::moveFile '\\' invalid symbol found in - @param fromOsPath -");
				SPARK_ASSERT(fromOsPath.find("..") == -1, "Win32OsFileSystem::moveFile '..' invalid symbol found in - @param fromOsPath -");
				SPARK_ASSERT(fromOsPath.find(":") != -1, "Win32OsFileSystem::moveFile - @param fromOsPath - is not an absolute path");

				SPARK_ASSERT(toOsPath.c_str() != 0, "Win32OsFileSystem::moveFile - @param toOsPath - is empty");
				SPARK_ASSERT(toOsPath.find("\\") == -1, "Win32OsFileSystem::moveFile '\\' invalid symbol found in - @param toOsPath -");
				SPARK_ASSERT(toOsPath.find("..") == -1, "Win32OsFileSystem::moveFile '..' invalid symbol found in - @param toOsPath -");
				SPARK_ASSERT(toOsPath.find(":") != -1, "Win32OsFileSystem::moveFile - @param toOsPath - is not an absolute path");

				std::string tempFromOsPath = fromOsPath;
				std::string tempTpOsPath = toOsPath;

				adjustPath(tempFromOsPath);
				adjustPath(tempTpOsPath);

				SPARK_ASSERT(tempFromOsPath[0] != '\0', "Win32OsFileSystem::moveFile - @param fromOsPath - is empty");
				SPARK_ASSERT(toOsPath[0] != '\0', "Win32OsFileSystem::moveFile - @param toOsPath - param is empty");

				if (!pathExists(tempFromOsPath) || isDirectory(tempFromOsPath)) {
					mLastErrorCode.wrongPath = fromOsPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}

				if (!pathExists(tempTpOsPath) || isDirectory(tempTpOsPath)) {
					mLastErrorCode.wrongPath = toOsPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}

				int namePos = tempFromOsPath.find_last_of('/');
	
				std::string fileName(tempTpOsPath + tempFromOsPath[namePos]);

				CopyFileA(fromOsPath.c_str(), fileName.c_str(), false);
				DeleteFileA(fromOsPath.c_str());

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
			}

			void Win32OsFileSystem::copyFile(const std::string& fromOsPath, const std::string& toOsPath, bool overwrite)
			{
				SPARK_ASSERT(fromOsPath.c_str() != 0, "Win32OsFileSystem::copyFile - const char* fromOsPath - param is empty");
				SPARK_ASSERT(fromOsPath.find("\\") == -1, "Win32OsFileSystem::copyFile '\\' invalid symbol found in - const char* fromOsPath - param");
				SPARK_ASSERT(fromOsPath.find("..") == -1, "Win32OsFileSystem::copyFile '..' invalid symbol found in - const char* fromOsPath - param");
				SPARK_ASSERT(fromOsPath.find(":") != -1, "Win32OsFileSystem::copyFile - const char* fromOsPath - param is not an absolute path");

				SPARK_ASSERT(toOsPath.c_str() != 0, "Win32OsFileSystem::copyFile - const char* osPath - param is empty");
				SPARK_ASSERT(toOsPath.find("\\") == -1, "Win32OsFileSystem::copyFile '\\' invalid symbol found in - const char* toOsPath - param");
				SPARK_ASSERT(toOsPath.find("..") == -1, "Win32OsFileSystem::copyFile '..' invalid symbol found in - const char* toOsPath - param");
				SPARK_ASSERT(toOsPath.find(":") != -1, "Win32OsFileSystem::copyFile - const char* toOsPath - param is not an absolute path");

				std::string tempFromOsPath = fromOsPath;
				std::string tempTpOsPath = toOsPath;

				adjustPath(tempFromOsPath);
				adjustPath(tempTpOsPath);

				SPARK_ASSERT(tempFromOsPath[0] != '\0', "Win32OsFileSystem::copyFile - const char* fromOsPath - param is empty");
				SPARK_ASSERT(toOsPath[0] != '\0', "Win32OsFileSystem::copyFile - const char* toOsPath - param is empty");

				if (!pathExists(tempFromOsPath) || isDirectory(tempFromOsPath)) {
					mLastErrorCode.wrongPath = fromOsPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}

				if (!pathExists(tempTpOsPath) || isDirectory(tempTpOsPath)) {
					mLastErrorCode.wrongPath = toOsPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}
				int namePos = tempFromOsPath.find_last_of('/');
				std::string fileName(tempTpOsPath + tempFromOsPath[namePos]);
				CopyFileA(fromOsPath.c_str(), fileName.c_str(), false);


				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
			}

			void Win32OsFileSystem::renameFile(const std::string& osPath, const std::string& newName, bool overwrite)
			{
				SPARK_ASSERT(osPath.c_str() != 0, "Win32OsFileSystem::copyFile - const char* osPath - param is empty");
				SPARK_ASSERT(osPath.find("\\") == -1, "Win32OsFileSystem::copyFile '\\' invalid symbol found in - const char* osPath - param");
				SPARK_ASSERT(osPath.find("..") == -1, "Win32OsFileSystem::copyFile '..' invalid symbol found in - const char* osPath - param");
				SPARK_ASSERT(osPath.find(":") != -1, "Win32OsFileSystem::copyFile - const char* osPath - param is not an absolute path");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(tempOsPath[0] != '\0', "Win32OsFileSystem::copyFile - const char* osPath - param is empty");

				if (!pathExists(tempOsPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}

				if (isDirectory(tempOsPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}

				int namePos = tempOsPath.find_last_of('/');
				std::string toOsPath = tempOsPath;
				toOsPath.replace(tempOsPath.begin() + namePos + 1, tempOsPath.end(), newName);



				if (toOsPath.compare(tempOsPath) == 0) {
					mLastErrorCode.wrongPath.clear();
					mLastErrorCode.wrongPath.clear();
					mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
					return;
				}

				if (pathExists(toOsPath) && !overwrite) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "selected path already exists";
					mLastErrorCode.errorCode = OsErrorCode::FS_DOUBLEPATH;
					return;
				} else {
					DeleteFileA(toOsPath.c_str());
				}

				MoveFileA(tempOsPath.c_str(), toOsPath.c_str());

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
			}

			void Win32OsFileSystem::createDirectory(const std::string& osPath)
			{
				SPARK_ASSERT(!osPath.empty(), "Win32OsFileSystem::createDirectory - @param osPath - is empty");
				SPARK_ASSERT(osPath.find("..") == -1, "Win32OsFileSystem::createDirectory '..' invalid symbol found in - @param osPath -");
				SPARK_ASSERT(osPath.find("\\") == -1, "Win32OsFileSystem::createDirectory '\\' invalid symbol found in - @param osPath -");
				SPARK_ASSERT(osPath.find(":") != -1, "Win32OsFileSystem::createDirectory - @param osPath -  is not an absolute path");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(!tempOsPath.empty(), "Win32OsFileSystem::createDirectory - @param osPath - is empty");

				if (pathExists(tempOsPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "selected path already exists";
					mLastErrorCode.errorCode = OsErrorCode::FS_DOUBLEPATH;
					return;
				}

				CreateDirectoryA(tempOsPath.c_str(), NULL);

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
			}

			Win32OsDir* Win32OsFileSystem::openDirectory(const std::string& relativePath, const std::string& searchPath)
			{
				SPARK_ASSERT(!relativePath.empty(), "Win32OsFileSystem::openDirectory - @param relativePath - is empty");
				SPARK_ASSERT(relativePath.find("..") == -1, "Win32OsFileSystem::openDirectory '..' invalid symbol found in - @param relativePath -");
				SPARK_ASSERT(relativePath.find("\\") == -1, "Win32OsFileSystem::openDirectory '\\' invalid symbol found in - @param relativePath -");
				SPARK_ASSERT(relativePath.find(":") == -1, "Win32OsFileSystem::openDirectory - @param relativePath -  is not a relative path");

				std::string tempRelativePath = relativePath;
				adjustPath(tempRelativePath);

				SPARK_ASSERT(!tempRelativePath.empty(), "Win32OsFileSystem::openDirectory - @param relativePath - is empty");

				std::string osPath = buildOsPath(relativePath, mRootPath, searchPath);

				if (!isDirectory(osPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return NULL;
				}

				unsigned int dirSize = getDirectorySize(osPath);

				WIN32_FIND_DATAA data;
				HANDLE dirHandle = NULL;

				dirHandle = openOsDir(osPath.c_str(), &data);

				if (dirHandle == INVALID_HANDLE_VALUE)  {

					SECURITY_ATTRIBUTES security;
					security.bInheritHandle = FALSE;
					security.nLength = sizeof(security);
					security.lpSecurityDescriptor = NULL;	

				}

				Win32OsDir* result = new Win32OsDir();

				result->mDirHandle	= dirHandle;
				result->mFullPath	= osPath;
				result->mDirName	= relativePath;
				result->mSync		= false;

				result->mDirSize = dirSize;

				Win32OsDir::FileType type;

				while (FindNextFileA(dirHandle, &data)) {

					if (strcmp(data.cFileName, ".") != 0 && strcmp(data.cFileName, "..") != 0) {
						DWORD dwAttribs = GetFileAttributesA(osPath.c_str());
			
						if (isDirectory(buildOsPath(data.cFileName, osPath)) == true) {
							type = Win32OsDir::TYPE_DIR;
						} else {
							type = Win32OsDir::TYPE_FILE;
						}
			
						result->mFileList.insert({ data.cFileName, type });
					}
				}

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;

				return result;
			}

			void Win32OsFileSystem::closeDirectory(Win32OsDir* directory)
			{
				if (directory != NULL) {
					closeOsDir(directory->mDirHandle);
					delete directory;
				}
			}

			void Win32OsFileSystem::copyDirectory(const std::string& fromOsPath, const std::string& toOsPath, bool merge)
			{
				SPARK_ASSERT(!fromOsPath.empty(), "Win32OsFileSystem::copyDirectory - @param fromOsPath - is empty");
				SPARK_ASSERT(fromOsPath.find("..") == -1, "Win32OsFileSystem::copyDirectory '..' invalid symbol found in - @param fromOsPath -");
				SPARK_ASSERT(fromOsPath.find("\\") == -1, "Win32OsFileSystem::copyDirectory '\\' invalid symbol found in - @param fromOsPath -");
				SPARK_ASSERT(fromOsPath.find(":") != -1, "Win32OsFileSystem::copyDirectory - @param fromOsPath -  is not an absolute path");

				SPARK_ASSERT(!toOsPath.empty(), "Win32OsFileSystem::copyDirectory - @param toOsPath - is empty");
				SPARK_ASSERT(toOsPath.find("..") == -1, "Win32OsFileSystem::copyDirectory '..' invalid symbol found in - @param toOsPath -");
				SPARK_ASSERT(toOsPath.find("\\") == -1, "Win32OsFileSystem::copyDirectory '\\' invalid symbol found in - @param toOsPath -");
				SPARK_ASSERT(toOsPath.find(":") != -1, "Win32OsFileSystem::copyDirectory - @param toOsPath -  is not an absolute path");

				std::string tempFromOsPath = fromOsPath;
				adjustPath(tempFromOsPath);

				SPARK_ASSERT(!tempFromOsPath.empty(), "Win32OsFileSystem::copyDirectory - @param fromOsPath - is empty");

				std::string tempToOsPath = toOsPath;
				adjustPath(tempFromOsPath);

				SPARK_ASSERT(!tempFromOsPath.empty(), "Win32OsFileSystem::copyDirectory - @param toOsPath - is empty");

				if (!isDirectory(tempFromOsPath)) {
					mLastErrorCode.wrongPath = fromOsPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}

				if (pathExists(tempToOsPath)) {
					if (!merge) {
						mLastErrorCode.wrongPath = toOsPath;
						mLastErrorCode.wrongPath = "selected path already exists";
						mLastErrorCode.errorCode = OsErrorCode::FS_DOUBLEPATH;
						return;
					} 
		
					if (isDirectory(tempToOsPath)) {
						CopyFileA(tempFromOsPath.c_str(), tempToOsPath.c_str(), false);
						return;
					}
				} else {
					CopyFileA(tempFromOsPath.c_str(), tempToOsPath.c_str(), false);
				}

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
			}

			void Win32OsFileSystem::moveDirectory(const std::string& fromOsPath, const std::string& toOsPath, bool merge)
			{
				SPARK_ASSERT(!fromOsPath.empty(), "Win32OsFileSystem::moveDirectory - @param fromOsPath - is empty");
				SPARK_ASSERT(fromOsPath.find("..") == -1, "Win32OsFileSystem::moveDirectory '..' invalid symbol found in - @param fromOsPath -");
				SPARK_ASSERT(fromOsPath.find("\\") == -1, "Win32OsFileSystem::moveDirectory '\\' invalid symbol found in - @param fromOsPath -");
				SPARK_ASSERT(fromOsPath.find(":") != -1, "Win32OsFileSystem::moveDirectory - @param fromOsPath -  is not an absolute path");

				SPARK_ASSERT(!toOsPath.empty(), "Win32OsFileSystem::moveDirectory - @param toOsPath - is empty");
				SPARK_ASSERT(toOsPath.find("..") == -1, "Win32OsFileSystem::moveDirectory '..' invalid symbol found in - @param toOsPath -");
				SPARK_ASSERT(toOsPath.find("\\") == -1, "Win32OsFileSystem::moveDirectory '\\' invalid symbol found in - @param toOsPath -");
				SPARK_ASSERT(toOsPath.find(":") != -1, "Win32OsFileSystem::moveDirectory - @param toOsPath -  is not an absolute path");

				std::string tempFromOsPath = fromOsPath;
				adjustPath(tempFromOsPath);

				SPARK_ASSERT(!tempFromOsPath.empty(), "Win32OsFileSystem::moveDirectory - @param fromOsPath - is empty");

				std::string tempToOsPath = toOsPath;
				adjustPath(tempFromOsPath);

				SPARK_ASSERT(!tempFromOsPath.empty(), "Win32OsFileSystem::moveDirectory - @param toOsPath - is empty");

				if (!isDirectory(tempFromOsPath)) {
					mLastErrorCode.wrongPath = fromOsPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}

				if (pathExists(tempToOsPath)) {
					if (!merge) {
						mLastErrorCode.wrongPath = toOsPath;
						mLastErrorCode.wrongPath = "selected path already exists";
						mLastErrorCode.errorCode = OsErrorCode::FS_DOUBLEPATH;
						return;
					}

					if (isDirectory(tempToOsPath)) {
						MoveFileA(tempFromOsPath.c_str(), tempToOsPath.c_str());
						return;
					}
				}
				else {
					MoveFileA(tempFromOsPath.c_str(), tempToOsPath.c_str());
				}

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
			}

			void Win32OsFileSystem::removeDirectory(const std::string& osPath)
			{
				SPARK_ASSERT(!osPath.empty(), "passed path is emtpy");
				SPARK_ASSERT(osPath.find("..") == -1, "Win32OsFileSystem::removeDirectory '..' invalid symbol found in - @param osPath -");
				SPARK_ASSERT(osPath.find("\\") == -1, "Win32OsFileSystem::removeDirectory '\\' invalid symbol found in - @param osPath -");
				SPARK_ASSERT(osPath.find(":") != -1, "Win32OsFileSystem::removeDirectory - @param osPath - is not an absolute path");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(!tempOsPath.empty(), "Win32OsFileSystem::removeDirectory - @param osPath - is empty");

				if (!isDirectory(tempOsPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}

				DeleteFileA(tempOsPath.c_str());

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
			}

			void Win32OsFileSystem::renameDirectory(const std::string& osPath, const std::string& newName)
			{
				SPARK_ASSERT(osPath.c_str() != 0, "passed path is empty");
				SPARK_ASSERT(osPath.find("\\") == -1, "'\\' Symbol is not allowed");
				SPARK_ASSERT(osPath.find("..") == -1, "'..' Symbol is not allowed");
				SPARK_ASSERT(osPath.find(":") != -1, "passed path is not an absolute path");
	
				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(tempOsPath[0] != '\0', "passed path is empty");

				SPARK_ASSERT(newName.c_str() != 0, "passed path is empty");
				SPARK_ASSERT(!newName.find("\\"), "'\\' Symbol is not allowed");
				SPARK_ASSERT(!newName.find(".."), "'..' Symbol is not allowed");
				SPARK_ASSERT(!newName.find(":"), "'newName has to be a relative path");

				std::string tempNewName = newName;
				adjustPath(tempNewName);

				SPARK_ASSERT(tempNewName[0] != '\0', "passed path is empty");

				SHFILEOPSTRUCTA fileStruct = { 0 };

				fileStruct.hwnd		= 0;
				fileStruct.wFunc	= FO_RENAME;
				fileStruct.pFrom	= tempOsPath.c_str();
				fileStruct.pTo		= tempNewName.c_str();
				fileStruct.fFlags	= FOF_NOCONFIRMMKDIR | FOF_RENAMEONCOLLISION | FOF_ALLOWUNDO | FOF_NOCONFIRMATION;

				SHFileOperationA(&fileStruct);

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
			}

			bool Win32OsFileSystem::isDirectory(const std::string& osPath)
			{
				SPARK_ASSERT(osPath.c_str() != 0, "passed path is empty");
				SPARK_ASSERT(osPath.find("\\") == -1, "'\\' Symbol is not allowed");
				SPARK_ASSERT(osPath.find("..") == -1, "'..' Symbol is not allowed");
				SPARK_ASSERT(osPath.find(":") != -1, "passed path is not an absolute path");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(tempOsPath[0] != '\0', "passed path is empty");

				if (!pathExists(tempOsPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return false;
				}

				DWORD dwAttribs = GetFileAttributesA(tempOsPath.c_str());

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;

				return dwAttribs & FILE_ATTRIBUTE_DIRECTORY;
			}

			int Win32OsFileSystem::getDirectorySize(const std::string& osPath)
			{
				SPARK_ASSERT(osPath.c_str() != 0, "passed path is empty");
				SPARK_ASSERT(osPath.find("\\") == -1, "'\\' Symbol is not allowed");
				SPARK_ASSERT(osPath.find("..") == -1, "'..' Symbol is not allowed");
				SPARK_ASSERT(osPath.find(":") != -1, "passed path is not an absolute path");
	
				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(tempOsPath[0] != '\0', "passed path is empty");

				if (!isDirectory(tempOsPath)) {
					return -1;
				}

				unsigned int size = 0;

				WIN32_FIND_DATAA data;
				HANDLE dirHandle = NULL;

				dirHandle = openOsDir(tempOsPath.c_str(), &data);

				if (dirHandle == INVALID_HANDLE_VALUE) {
					return 0;
				}

				do{
					if (strcmp(data.cFileName, ".") != 0 && strcmp(data.cFileName, "..") != 0) {
						if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {

							std::string dest = tempOsPath + "/" + data.cFileName;
							size += getDirectorySize(dest);
						} else {
							size += (int)(data.nFileSizeHigh * (MAXDWORD)+data.nFileSizeLow);
						}
					}
				} while (FindNextFileA(dirHandle, &data));

				closeOsDir(dirHandle);

				return size;
			}

			std::string Win32OsFileSystem::getPathName(const std::string& osPath)
			{
				SPARK_ASSERT(osPath.c_str() != 0, "passed path is empty");
				SPARK_ASSERT(osPath.find("\\") == -1, "'\\' Symbol is not allowed");
				SPARK_ASSERT(osPath.find("..") == -1, "'..' Symbol is not allowed");
				SPARK_ASSERT(osPath.find(":") != -1, "passed path is not an absolute path");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(tempOsPath[0] != '\0', "passed path is empty");
	
				std::string fileName = tempOsPath.substr(tempOsPath.find_last_of('/') + 1);
				return fileName;
			}

			bool Win32OsFileSystem::pathExists(const const std::string& osPath)
			{
				SPARK_ASSERT(osPath.c_str() != 0, "passed path is emtpy");
				SPARK_ASSERT(osPath.find("\\") == -1, "'\\' Symbol is not allowed");
				SPARK_ASSERT(osPath.find("..") == -1, "'..' Symbol is not allowed");
				SPARK_ASSERT(osPath.find(":") != -1, "Win32OsFileSyste::pathExists - const char* osPath - param is not an absolute path");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(tempOsPath[0] != '\0', "passed path is empty");

				WIN32_FIND_DATAA FindFileData;
				HANDLE hFound = FindFirstFileA(tempOsPath.c_str(), &FindFileData);

				bool result = !(hFound == INVALID_HANDLE_VALUE);

				FindClose(hFound);
				return result;
			}

			void Win32OsFileSystem::adjustPath(std::string& path)
			{
				SPARK_ASSERT(path.find("\\") == -1, "'\\' Symbol is not allowed");
				SPARK_ASSERT(path.find("..") == -1, "'..' Symbol is not allowed");
	
				int i = 0;

				if (path.c_str() != 0) {		

					while (path[i] == '.' || path[i] == '/') {
						path.erase(path.begin() + i);
					}
				}
			}

			std::string Win32OsFileSystem::buildOsPath(const std::string& relativePath, const std::string& basePath, const std::string& searchPath)
			{
				SPARK_ASSERT(relativePath.c_str() != 0, "relativePath is empty");
				SPARK_ASSERT(relativePath.find("\\") == -1, "'\\' Symbol is not allowed");
				SPARK_ASSERT(relativePath.find("..") == -1, "'..' Symbol is not allowed");
				SPARK_ASSERT(relativePath.find(":") == -1, "relativePath is not a relative path");

				SPARK_ASSERT(basePath.c_str() != 0, "basePath is empty");
				SPARK_ASSERT(basePath.find("\\") == -1, "'\\' Symbol is not allowed");
				SPARK_ASSERT(basePath.find("..") == -1, "'..' Symbol is not allowed");
				SPARK_ASSERT(basePath.find(":") != -1, "basePath is not an absolute path");

				std::string osPath;

				std::string tempRelativePath = relativePath;
				adjustPath(tempRelativePath);

				SPARK_ASSERT(tempRelativePath[0] != '\0', "relativePath is empty");

				std::string tempBasePath = basePath;
				adjustPath(tempBasePath);

				SPARK_ASSERT(tempBasePath[0] != '\0', "basePath is empty");

				if (searchPath.c_str() != 0 && searchPath.c_str() != "" && searchPath[0] != '\0') {
					SPARK_ASSERT(searchPath.find("\\") == -1, "'\\' Symbol is not allowed");
					SPARK_ASSERT(searchPath.find("..") == -1, "'..' Symbol is not allowed");
					SPARK_ASSERT(searchPath.find(":") == -1, "searchPath is not a relative path");

					std::string tempSearchPath = searchPath;
					adjustPath(tempSearchPath);

					SPARK_ASSERT(tempSearchPath[0] != '\0', "searchPath is empty");

					osPath = basePath + "/" + searchPath + "/" + relativePath;
				} else {		
					osPath = std::string(basePath) + std::string("/") + std::string(relativePath);
				}

				return osPath;
			}

			HANDLE Win32OsFileSystem::openOsFile(const char* osPath, OsOpenMode openMode)
			{
				DWORD dwAccess;
				DWORD dwShare;
				DWORD dwCreate;
				DWORD dwFlags;

				if (openMode == Win32OsFileSystem::FILE_READ) {
					dwAccess = GENERIC_READ;
					dwShare = 0;
					dwCreate = OPEN_EXISTING;
					dwFlags = FILE_ATTRIBUTE_NORMAL;
				} else if (openMode == Win32OsFileSystem::FILE_WRITE) {
					dwAccess = GENERIC_WRITE;
					dwShare = 0;
					dwCreate = OPEN_ALWAYS;
					dwFlags = FILE_ATTRIBUTE_NORMAL;
				/*} else if (openMode == Win32OsFileSystem::FILE_APPEND) {
					dwAccess = GENERIC_WRITE | FILE_APPEND_DATA;
					dwShare = 0;
					dwCreate = OPEN_ALWAYS;
					dwFlags = FILE_ATTRIBUTE_NORMAL;*/
				} else if (openMode == Win32OsFileSystem::FILE_READWRITE) {
					dwAccess = GENERIC_WRITE | GENERIC_READ;
					dwShare = 0;
					dwCreate = OPEN_ALWAYS;
					dwFlags = FILE_ATTRIBUTE_NORMAL;
				}

				HANDLE fh = CreateFileA(osPath, dwAccess, dwShare, NULL, dwCreate, dwFlags, NULL);
				return fh;
			}

			void Win32OsFileSystem::closeOsFile(HANDLE fileHandle)
			{
				CloseHandle(fileHandle);
			}

			HANDLE Win32OsFileSystem::openOsDir(const char* osPath, WIN32_FIND_DATAA* data)
			{
				char dest[1024];
				sprintf(dest, "%s/*.*", osPath);
				HANDLE res = FindFirstFileA(dest, data);

				return res;
			}

			void Win32OsFileSystem::closeOsDir(HANDLE dirHandle)
			{
				FindClose(dirHandle);
			}

			void Win32OsFileSystem::addSearchPath(const std::string& pathKey, SearchPath_s searchPath)
			{
				SPARK_ASSERT(searchPath.mRawPath.c_str() != 0, "osPath is empty");
				SPARK_ASSERT(searchPath.mRawPath.find("..") == -1, "'..' Symbol is not allowed");
				SPARK_ASSERT(searchPath.mRawPath.find("\\") == -1, "'\\' Symbol is not allowed");
				SPARK_ASSERT(searchPath.mRawPath.find(":") == -1, "searchPath is not a relative path");

				std::string tempRelativePath = searchPath.mRawPath;
				adjustPath(tempRelativePath);

				std::string tempOsPath = buildOsPath(tempRelativePath, mRootPath);

				SPARK_ASSERT(tempRelativePath[0] != '\0', "relativePath is empty");

				if (!isDirectory(tempOsPath)) {
					mLastErrorCode.wrongPath = tempOsPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}

				for (std::map<std::string, SearchPath_s>::iterator it = mSearchPaths.begin(); it != mSearchPaths.end(); it++) {
					if (searchPath.mRawPath.compare((*it).second.mRawPath) == 0) {
						return;
					}
				}

				mSearchPaths.insert({ pathKey, searchPath });

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
			}

			void Win32OsFileSystem::setRootPath(const std::string& osPath)
			{
				SPARK_ASSERT(osPath.c_str() != 0, "osPath is empty");
				SPARK_ASSERT(osPath.find("..") == -1, "'..' Symbol is not allowed");
				SPARK_ASSERT(osPath.find("\\") == -1, "'\\' Symbol is not allowed");
				SPARK_ASSERT(osPath.find(":"), "osPath is not an Absolute path");

				std::string tempOsPath = osPath;
				adjustPath(tempOsPath);

				SPARK_ASSERT(tempOsPath[0] != '\0', "osPath is empty");

				if (!isDirectory(tempOsPath)) {
					mLastErrorCode.wrongPath = osPath;
					mLastErrorCode.wrongPath = "cannot found selected path";
					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
					return;
				}

				mRootPath = tempOsPath;

				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.wrongPath.clear();
				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
			}
		}
	}
}