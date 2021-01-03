#ifndef __WIN32_DISPATCHER_H__
#define __WIN32_DISPATCHER_H__

#include <vector>
#include "./Win32ControlsEvents.h"

namespace SE
{
	namespace platform
	{
		namespace input
		{
			class Win32Dispatcher
			{
				typedef std::vector<KeyboardEvent> KeyboardEventBuffer;

			public:
				Win32Dispatcher()
				{
				}

				~Win32Dispatcher()
				{
				}

			public:
				KeyboardEventBuffer nextKeys() const;
			};
		}
	}
}


#endif // !__WIN32_DISPATCHER_H__
