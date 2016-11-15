#ifndef __WIN32HIRESTIMER_H__
#define __WIN32HIRESTIMER_H__

#include <Windows.h>
#include "../HiResTimer.h"

namespace SE
{
	namespace platform
	{
		namespace time
		{
			class Win32HiResTimer : public HiResTimer
			{
			public:
				Win32HiResTimer();
				~Win32HiResTimer();

			public:
				virtual void start() override;
				virtual void stop() override;
				virtual void clear() override;

				virtual double getElapsedMs() override;
				virtual double getElapsedS() override;
				virtual int getElapsedTicks() override;

			private:
				LARGE_INTEGER	mTick1;
				LARGE_INTEGER   mTick2;
				LARGE_INTEGER	mFrequency;

			};
		}
	}
}

#endif // !__WIN32HIRESTIMER_H__