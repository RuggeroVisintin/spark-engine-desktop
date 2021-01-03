#include "Win32Dispatcher.h"
#include "Win32ControlsEvents.h"

#include <Windows.h>


namespace SE
{
	namespace platform
	{
		namespace input
		{
			Win32Dispatcher::KeyboardEventBuffer Win32Dispatcher::nextKeys() const
			{
				KeyboardEventBuffer result;
				KeyboardEvent tmpEvt;

				MSG msg;
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);

					tmpEvt.key = static_cast<KEYS>(msg.wParam);
					tmpEvt.state = static_cast<KEYBOARD_STATES>(msg.message);

					result.push_back(tmpEvt);
				}

				return result;
			}
		}
	}
}