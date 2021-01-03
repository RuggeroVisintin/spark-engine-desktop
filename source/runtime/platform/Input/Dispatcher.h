#ifndef __DISPATCHER_H__
#define __DISPATCHER_H__

#include <list>
#include "../Platform.h"
#include "ControlsEvents.h"

#ifdef WINDOWS
#include "PlatformWin32/Win32Dispatcher.h"
#endif

namespace SE
{
	namespace platform
	{
		namespace input
		{

#ifdef WINDOWS
			typedef Win32Dispatcher Dispatcher;
#endif

			/*class Dispatcher
			{
				typedef std::list<KeyboardEvent> EventList;

			public:
				Dispatcher()
				{
				}

				virtual ~Dispatcher()
				{
				}

			public:
				virtual const KeyboardEvent& getKeyStatus(const KEYS& key);

			private:
				EventList	mEventList;
			};*/
		}
	}
}

#endif // !__DISPATCHER_H__
