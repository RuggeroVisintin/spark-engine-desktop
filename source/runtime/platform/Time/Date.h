#ifndef __DATE_H__
#define __DATE_H__

#include <Windows.h>
#include <string>

namespace SE
{
    namespace platform
    {
        namespace time
        {        
            class Win32Date
            {
            public:
				Win32Date()
                {
					update();
                }
                
				~Win32Date()
                {
                }
                
            public:
				void                    update()
				{
					GetLocalTime(&mTime);
				}

				std::string				toString() const
				{
					std::string finalDate;

					if (mTime.wMonth < 10) {
						finalDate.push_back('0');
					}
					
					finalDate.append(std::to_string(mTime.wMonth) + "/");

					if (mTime.wDay < 10) {
						finalDate.push_back('0');
					}

					finalDate.append(std::to_string(mTime.wDay) + "/");

					if (mTime.wYear < 10) {
						finalDate.push_back('0');
					}

					finalDate.append(std::to_string(mTime.wYear) + " ");

					if (mTime.wHour < 10) {
						finalDate.push_back('0');
					}

					finalDate.append(std::to_string(mTime.wHour) + ":");

					if (mTime.wMinute < 10) {
						finalDate.push_back('0');
					}

					finalDate.append(std::to_string(mTime.wMinute) + ":");

					if (mTime.wSecond < 10) {
						finalDate.push_back('0');
					}

					finalDate.append(std::to_string(mTime.wSecond));

					return finalDate;
				}
                
            private:
                SYSTEMTIME              mTime;          
                
            };

			typedef Win32Date Date;
        }
    }
}

#endif // !__DATE_H__