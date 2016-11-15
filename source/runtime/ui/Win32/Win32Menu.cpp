#include "Win32Menu.h"

void Win32MenuBar::appendMenuItem(SubMenu* item)
{
	AppendMenu(((Win32SubMenu*)item)->mHandle)
}