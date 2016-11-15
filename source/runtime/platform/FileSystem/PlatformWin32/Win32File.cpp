#include "Win32File.h"
#include "../../Assertion/Assert.h"

namespace SE
{
	namespace platform
	{
		namespace filesystem
		{
			size_t Win32OsFile::read(void* inBuffer, size_t count)
			{
				SPARK_ASSERT((mOpenMode == FILE_READ || mOpenMode == FILE_READWRITE), "Win32OsFile::read file is not opened in FILE_READ openMode");

				if (mOpenMode == FILE_READ || mOpenMode == FILE_READWRITE) {
					unsigned long result;

					if (ReadFile(mFileHandle, inBuffer, count, &result, NULL) == TRUE) {
						mCurrentPosition += result;
						return result;
					}
				}

				return -1;
			}

			size_t Win32OsFile::readLine(char* inLine, size_t maxCount) {
				SPARK_ASSERT((mOpenMode == FILE_READ || mOpenMode == FILE_READWRITE), "Win32OsFile::read file is not opened in FILE_READ openMode");

				char tempChar;
				int count = 0;

				while (count < maxCount - 1) {
					read(&tempChar, sizeof(char));

					if (tempChar != '\n') {
						inLine[count] = tempChar;
					}
					else {
						break;
					}

					count++;
				}

				inLine[count] = '\0';

				return count;
			}

			size_t Win32OsFile::write(const void* outBuffer, size_t count)
			{
				SPARK_ASSERT((mOpenMode == FILE_WRITE || mOpenMode == FILE_READWRITE), "Win32OsFile::write file is not opened in FILE_WRITE openMode");

				if (mOpenMode == FILE_WRITE || mOpenMode == FILE_READWRITE) {
					unsigned long result;

					if (WriteFile(mFileHandle, outBuffer, count, &result, NULL) == TRUE) {
						return result;
					}
				}

				return -1;
			}

			size_t Win32OsFile::append(const void* outBuffer, size_t count)
			{
				SPARK_ASSERT((mOpenMode == FILE_WRITE || mOpenMode == FILE_READWRITE), "Win32OsFile::append file is not opened in FILE_WRITE openMode");

				if (mOpenMode == FILE_WRITE || mOpenMode == FILE_READWRITE) {
					unsigned long result;

					seekEnd(0);

					if (WriteFile(mFileHandle, outBuffer, count, &result, NULL) == TRUE) {
						return result;
					}
				}

				return -1;
			}

			bool Win32OsFile::seekBegin(int position)
			{
				DWORD tempRes = SetFilePointer(mFileHandle, position, NULL, FILE_BEGIN);

				if (tempRes != INVALID_SET_FILE_POINTER) {
					mCurrentPosition = LOWORD(tempRes);

					return true;
				}

				return false;
			}

			bool Win32OsFile::seekCurr(int position)
			{
				DWORD tempRes = SetFilePointer(mFileHandle, position, NULL, FILE_CURRENT);

				if (tempRes != INVALID_SET_FILE_POINTER) {
					mCurrentPosition = LOWORD(tempRes);
					printf("%d\n", mCurrentPosition);
					return true;
				}

				return false;
			}

			bool Win32OsFile::seekEnd(int position)
			{
				DWORD tempRes = SetFilePointer(mFileHandle, position, NULL, FILE_END);

				if (tempRes != INVALID_SET_FILE_POINTER) {
					mCurrentPosition = LOWORD(tempRes);
					return true;
				}

				return false;
			}
		}
	}
}