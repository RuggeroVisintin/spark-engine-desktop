#ifndef __HIRESTIMER_H__
#define __HIRESTIMER_H__

namespace SE
{
	namespace platform
	{
		namespace time
		{
			class HiResTimer
			{
			public:
				HiResTimer() {}
				virtual ~HiResTimer() {}

			public:
				virtual void start() = 0;
				virtual void stop() = 0;
				virtual void clear() = 0;

				virtual double getElapsedMs() = 0;
				virtual double getElapsedS() = 0;
				virtual int getElapsedTicks() = 0;
			};
		}
	}
}

#endif // !__HIRESTIMER_H__