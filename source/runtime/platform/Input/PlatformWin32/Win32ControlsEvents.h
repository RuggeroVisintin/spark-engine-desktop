#ifndef __WIN32_CONTROLSEVENTS_H__
#define __WIN32_CONTROLSEVENTS_H__

namespace SE
{
	namespace platform
	{
		namespace input
		{
			enum KEYBOARD_STATES
			{
				KEY_RELEASED		= 0x0101,
				KEY_PRESSED			= 0x0100
			};
			
			enum KEYS
			{
				KEY_W		= 0x57,
				KEY_S		= 0x53,
				KEY_A		= 0x41, 
				KEY_D		= 0x44,

				KEY_LEFT	= 0x25,
				KEY_UP		= 0x26,
				KEY_RIGHT	= 0x27,
				KEY_DOWN	= 0x28,

				KEY_CTRL	= 0x11,
				KEY_SPACE	= 0x20
			};

			struct KeyboardEvent
			{
				KEYBOARD_STATES state;
				KEYS			key;
			};
		}
	}
}


#endif // !__WIN32_CONTROLSEVENTS_H__
