#include "FileSystem.h"

//namespace SE
//{
//	namespace platform
//	{
//		namespace filesystem
//		{
//			void OsFileSystem::addSearchPath(const std::string& pathKey, SearchPath_s searchPath)
//			{
//				SPARK_ASSERT(searchPath.mRawPath.c_str() != 0, "osPath is empty");
//				SPARK_ASSERT(searchPath.mRawPath.find("..") == -1, "'..' Symbol is not allowed");
//				SPARK_ASSERT(searchPath.mRawPath.find("\\") == -1, "'\\' Symbol is not allowed");
//				SPARK_ASSERT(searchPath.mRawPath.find(":") == -1, "searchPath is not a relative path");
//
//				std::string tempRelativePath = searchPath.mRawPath;
//				adjustPath(tempRelativePath);
//
//				std::string tempOsPath = buildOsPath(tempRelativePath, mRootPath);
//
//				SPARK_ASSERT(tempRelativePath[0] != '\0', "relativePath is empty");
//
//				if (!isDirectory(tempOsPath)) {
//					mLastErrorCode.wrongPath = tempOsPath;
//					mLastErrorCode.wrongPath = "cannot found selected path";
//					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
//					return;
//				}
//
//				for (std::map<std::string, SearchPath_s>::iterator it = mSearchPaths.begin(); it != mSearchPaths.end(); it++) {
//					if (searchPath.mRawPath.compare((*it).second.mRawPath) != -1) {
//						return;
//					}
//				}
//
//				mSearchPaths.insert({ pathKey, searchPath });
//
//				mLastErrorCode.wrongPath.clear();
//				mLastErrorCode.wrongPath.clear();
//				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
//			}
//
//			void OsFileSystem::setRootPath(const std::string& osPath)
//			{
//				SPARK_ASSERT(mInitialized == false, "setRootPath function unavailable during fileSystem execution");
//
//				SPARK_ASSERT(osPath.c_str() != 0, "osPath is empty");
//				SPARK_ASSERT(osPath.find("..") == -1, "'..' Symbol is not allowed");
//				SPARK_ASSERT(osPath.find("\\") == -1, "'\\' Symbol is not allowed");
//				SPARK_ASSERT(osPath.find(":"), "osPath is not an Absolute path");
//
//				std::string tempOsPath = osPath;
//				adjustPath(tempOsPath);
//
//				SPARK_ASSERT(tempOsPath[0] != '\0', "osPath is empty");
//
//				if (!isDirectory(tempOsPath)) {
//					mLastErrorCode.wrongPath = osPath;
//					mLastErrorCode.wrongPath = "cannot found selected path";
//					mLastErrorCode.errorCode = OsErrorCode::FS_NOTFOUND;
//					return;
//				}
//
//				mRootPath = tempOsPath;
//
//				mLastErrorCode.wrongPath.clear();
//				mLastErrorCode.wrongPath.clear();
//				mLastErrorCode.errorCode = OsErrorCode::FS_NOERROR;
//			}
//		}
//	}
//}