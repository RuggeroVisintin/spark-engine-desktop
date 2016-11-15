#include "Win32HiResTimer.h"

namespace SE
{
	namespace platform
	{
		namespace time
		{
			Win32HiResTimer::Win32HiResTimer()
			{
				QueryPerformanceFrequency(&mFrequency);
			}

			Win32HiResTimer::~Win32HiResTimer()
			{

			}

			void Win32HiResTimer::start()
			{
				QueryPerformanceCounter(&mTick1);
			}

			void Win32HiResTimer::stop()
			{
				QueryPerformanceCounter(&mTick2);
			}

			void Win32HiResTimer::clear()
			{
				mTick1.HighPart = 0;
				mTick1.LowPart = 0;
				mTick1.QuadPart = 0;

				mTick2.HighPart = 0;
				mTick2.LowPart = 0;
				mTick2.QuadPart = 0;
			}

			double Win32HiResTimer::getElapsedMs()
			{
				stop();
				float res = (mTick2.QuadPart - mTick1.QuadPart) * 1000 / double(mFrequency.QuadPart);
				start();
				return res;
			}

			double Win32HiResTimer::getElapsedS()
			{
				return (double)((mTick2.QuadPart - mTick1.QuadPart) / double(mFrequency.QuadPart));
			}

			int Win32HiResTimer::getElapsedTicks()
			{
				return (mTick2.QuadPart - mTick1.QuadPart);
			}
		}
	}
}