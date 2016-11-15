#include "Win32Window.h"

Win32Window::Win32Window()
{
	WNDCLASSEX wndClass;

	if (!GetClassInfoEx(GetModuleHandle(NULL), L"Window", &wndClass)) {
		wndClass.hInstance = GetModuleHandleA(NULL);
		wndClass.cbSize = sizeof(wndClass);
		wndClass.cbWndExtra = 0;
		wndClass.cbClsExtra = 0;
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndClass.hCursor = LoadCursor(GetModuleHandleA(NULL), IDC_ARROW);
		wndClass.hIcon = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_APPLICATION));
		wndClass.hIconSm = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_APPLICATION));
		wndClass.lpfnWndProc = msgRouter;
		wndClass.lpszClassName = L"Window";
		wndClass.lpszMenuName = NULL;
		wndClass.style = CS_OWNDC;

		RegisterClassEx(&wndClass);
	}
}

Win32Window::Win32Window(const std::wstring& title)
{
	WNDCLASSEX wndClass;

	if (!GetClassInfoEx(GetModuleHandle(NULL), L"Window", &wndClass)) {
		wndClass.hInstance = GetModuleHandleA(NULL);
		wndClass.cbSize = sizeof(wndClass);
		wndClass.cbWndExtra = 0;
		wndClass.cbClsExtra = 0;
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndClass.hCursor = LoadCursor(GetModuleHandleA(NULL), IDC_ARROW);
		wndClass.hIcon = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_APPLICATION));
		wndClass.hIconSm = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_APPLICATION));
		wndClass.lpfnWndProc = msgRouter;
		wndClass.lpszClassName = L"Window";
		wndClass.lpszMenuName = NULL;
		wndClass.style = CS_OWNDC;

		RegisterClassEx(&wndClass);
	}
}

Win32Window::~Win32Window()
{
	if (mHandle) {
		DestroyWindow(mHandle);
	}

	if (FindWindow(L"Window", NULL) == NULL) {
		UnregisterClass(L"Window", GetModuleHandle(NULL));
	}
}

void Win32Window::show()
{
	if (!mHandle) {

		mHandle = CreateWindowEx
			(
			NULL,
			L"Window",
			mTitle.c_str(),
			WS_OVERLAPPEDWINDOW,
			0,
			0,
			640,
			480,
			NULL,
			NULL,
			GetModuleHandle(NULL),
			this
			);


		ShowWindow(mHandle, SW_SHOWNORMAL);
	} else {
		ShowWindow(mHandle, SW_SHOW);
	}

	UpdateWindow(mHandle);
}

void Win32Window::hide()
{
	ShowWindow(mHandle, SW_HIDE);
	UpdateWindow(mHandle);
}

void Win32Window::minimize()
{
	ShowWindow(mHandle, SW_MINIMIZE);
	UpdateWindow(mHandle);
}

void Win32Window::maximize()
{
	ShowWindow(mHandle, SW_MAXIMIZE);
	UpdateWindow(mHandle);
}

void Win32Window::focus()
{
	SetFocus(mHandle);
}

void Win32Window::killFocus()
{
	SetFocus(NULL);
}

void Win32Window::setFullscreen(bool fullscreen)
{
	mFullscreen = fullscreen;

	if (fullscreen == true) {
		DWORD wndStyle;

		if (isMaximized()) {
			wndStyle = WS_OVERLAPPED | WS_VISIBLE | WS_MAXIMIZE;
		} else {
			wndStyle = WS_OVERLAPPED | WS_VISIBLE;
		}

		SetWindowLong(mHandle, GWL_STYLE, wndStyle);

		int windowX, windowY, windowWidth, windowHeight;

		MONITORINFO monitorInfo;
		monitorInfo.cbSize = sizeof(monitorInfo);

		GetMonitorInfo(MonitorFromWindow(mHandle, MONITOR_DEFAULTTONEAREST), &monitorInfo);

		windowX = monitorInfo.rcMonitor.left;
		windowY = monitorInfo.rcMonitor.top;

		windowWidth = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
		windowHeight = monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top;

		SetWindowPos(mHandle, HWND_TOP, windowX, windowY, windowWidth, windowHeight, SWP_NOREDRAW);
	} else {
		DWORD wndStyle;

		if (isMaximized()) {
			wndStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE;
		} else {
			wndStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
		}

		SetWindowLong(mHandle, GWL_STYLE, wndStyle);
		SetWindowPos(mHandle, NULL, mX, mY, mWidth, mHeight, NULL);
	}
}

bool Win32Window::isVisible()
{
	return IsWindowVisible(mHandle);
}

bool Win32Window::isEnabled()
{
	return IsWindowEnabled(mHandle);
}

bool Win32Window::isMinimized()
{
	WINDOWPLACEMENT wndPlace;

	if (GetWindowPlacement(mHandle, &wndPlace)){
		return wndPlace.showCmd == SW_MINIMIZE;
	}

	return false;
}

bool Win32Window::isMaximized()
{
	WINDOWPLACEMENT wndPlace;

	if (GetWindowPlacement(mHandle, &wndPlace)){
		return wndPlace.showCmd == SW_MAXIMIZE;
	}

	return false;
}

bool Win32Window::isFocused()
{
	return GetFocus() == mHandle;
}

bool Win32Window::isFullscreen()
{
	return mFullscreen;
}

LRESULT CALLBACK Win32Window::msgRouter(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Win32Window* wnd = NULL;

	if (msg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		wnd = (Win32Window*)pCreate->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)wnd);

		wnd->mHandle = hwnd;
	} else {
		wnd = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}

	if (wnd) {
		return wnd->wndProc(hwnd, msg, wParam, lParam);
	} else {
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

LRESULT CALLBACK Win32Window::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) 
	{
	case WM_CREATE:
		onCreate();
		break;

	case WM_SIZE:
		if (!mFullscreen) {
			RECT rect;

			GetWindowRect(hwnd, &rect);

			mWidth = rect.right - rect.left;
			mHeight = rect.bottom - rect.top;
		}

		onResize((int)LOWORD(lParam), (int)HIWORD(lParam));
		break;

	case WM_PAINT:
		onPaint();
		break;

	case WM_MOVE:
		if (!mFullscreen) {
			RECT rect;

			GetWindowRect(hwnd, &rect);

			mX = rect.left;
			mY = rect.top;
		}

		onMove((int)LOWORD(lParam), (int)HIWORD(lParam));
		break;

	case WM_SETFOCUS:
		onFocus();
		break;

	case WM_KILLFOCUS:
		onKillFocus();
		break;

	case WM_CLOSE:
		onClosing();
		break;

	case WM_DESTROY:
		onClosed();
		break;

	case WM_KEYDOWN:
		onKeyDown((int)wParam);
		break;

	case WM_KEYUP:
		onKeyUp((int)wParam);
		break;

	case WM_MOUSEMOVE:
		onMouseMove((int)LOWORD(lParam), (int)HIWORD(lParam));
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}