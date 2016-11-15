#include "Win32WindowGL.h"
#include "../../Platform/GFX/OpenGL/Win32/Win32GLContext.h"

#include "../../Core/SmartPtrs/SharedPtr.h"

const wchar_t* Win32WindowGL::CLASS_NAME = L"WindowGL";

Win32WindowGL::Win32WindowGL(SE::platform::backend::GLContext::GLVersion contextVersion)
	: WindowGL(contextVersion)
{
	WNDCLASSEX wndClass;

	if (!GetClassInfoEx(GetModuleHandle(NULL), CLASS_NAME, &wndClass)) {
		wndClass.hInstance = GetModuleHandleA(NULL);
		wndClass.cbSize = sizeof(wndClass);
		wndClass.cbWndExtra = 0;
		wndClass.cbClsExtra = 0;
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hIcon = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_APPLICATION));
		wndClass.hIconSm = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_APPLICATION));
		wndClass.lpfnWndProc = msgRouter;
		wndClass.lpszClassName = CLASS_NAME;
		wndClass.lpszMenuName = NULL;
		wndClass.style = CS_OWNDC;

		RegisterClassEx(&wndClass);
	}

	mHandle = NULL;
}

Win32WindowGL::Win32WindowGL(SE::platform::backend::GLContext::GLContext::GLVersion contextVersion, const std::wstring& title)
	: WindowGL(contextVersion, title)
{
	WNDCLASSEX wndClass;

	if (!GetClassInfoEx(GetModuleHandle(NULL), CLASS_NAME, &wndClass)) {
		wndClass.hInstance = GetModuleHandleA(NULL);
		wndClass.cbSize = sizeof(wndClass);
		wndClass.cbWndExtra = 0;
		wndClass.cbClsExtra = 0;
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hIcon = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_APPLICATION));
		wndClass.hIconSm = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_APPLICATION));
		wndClass.lpfnWndProc = msgRouter;
		wndClass.lpszClassName = CLASS_NAME;
		wndClass.lpszMenuName = NULL;
		wndClass.style = CS_OWNDC;

		RegisterClassEx(&wndClass);
	}

	mHandle = NULL;
}

Win32WindowGL::~Win32WindowGL()
{
	if (mHandle) {
		DestroyWindow(mHandle);
	}

	if (FindWindow(CLASS_NAME, NULL) == NULL) {
		UnregisterClass(CLASS_NAME, GetModuleHandle(NULL));
	}
}

void Win32WindowGL::show()
{
	if (!mHandle) {
		mHandle = CreateWindowEx
			(
			NULL,
			CLASS_NAME,
			mTitle.c_str(),
			WS_OVERLAPPEDWINDOW,
			0,
			0,
			1360,
			768,
			NULL,
			NULL,
			GetModuleHandle(NULL),
			this
			);

		ShowWindow(mHandle, SW_SHOWNORMAL);
	}
	else {
		ShowWindow(mHandle, SW_SHOW);
	}

	UpdateWindow(mHandle);
}

void Win32WindowGL::hide()
{
	ShowWindow(mHandle, SW_HIDE);
	UpdateWindow(mHandle);
}

void Win32WindowGL::minimize()
{
	ShowWindow(mHandle, SW_MINIMIZE);
	UpdateWindow(mHandle);
}

void Win32WindowGL::maximize()
{
	ShowWindow(mHandle, SW_MAXIMIZE);
	UpdateWindow(mHandle);
}

void Win32WindowGL::focus()
{
	SetFocus(mHandle);
}

void Win32WindowGL::killFocus()
{
	SetFocus(NULL);
}

void Win32WindowGL::setFullscreen(bool fullscreen)
{
	mFullscreen = fullscreen;

	if (fullscreen == true) {
		DWORD wndStyle;

		if (isMaximized()) {
			wndStyle = WS_OVERLAPPED | WS_VISIBLE | WS_MAXIMIZE;
		}
		else {
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
	}
	else {
		DWORD wndStyle;

		if (isMaximized()) {
			wndStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE;
		}
		else {
			wndStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
		}

		SetWindowLong(mHandle, GWL_STYLE, wndStyle);
		SetWindowPos(mHandle, NULL, mX, mY, mWidth, mHeight, NULL);
	}
}

bool Win32WindowGL::isVisible()
{
	return IsWindowVisible(mHandle);
}

bool Win32WindowGL::isEnabled()
{
	return IsWindowEnabled(mHandle);
}

bool Win32WindowGL::isMinimized()
{
	WINDOWPLACEMENT wndPlace;

	if (GetWindowPlacement(mHandle, &wndPlace)){
		return wndPlace.showCmd == SW_MINIMIZE;
	}

	return false;
}

bool Win32WindowGL::isMaximized()
{
	WINDOWPLACEMENT wndPlace;

	if (GetWindowPlacement(mHandle, &wndPlace)){
		return wndPlace.showCmd == SW_MAXIMIZE;
	}

	return false;
}

bool Win32WindowGL::isFocused()
{
	return GetFocus() == mHandle;
}

bool Win32WindowGL::isFullscreen()
{
	return mFullscreen;
}

LRESULT CALLBACK Win32WindowGL::msgRouter(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Win32WindowGL* wnd = NULL;

	if (msg == WM_NCCREATE) {
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		wnd = (Win32WindowGL*)pCreate->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)wnd);

		wnd->mHandle = hwnd;
	} else {
		wnd = (Win32WindowGL*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}

	if (wnd) {
		return wnd->wndProc(hwnd, msg, wParam, lParam);
	} else {
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

LRESULT CALLBACK Win32WindowGL::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		mGraphicsContext = SE::core::memory::SharedPtr<SE::platform::backend::GLContext>(new SE::platform::backend::Win32GLContext(mHandle, mContextVersion));
		mGraphicsContext->createContext();
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
		ValidateRect(mHandle, NULL);
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
		if (mHandle) {
			DestroyWindow(mHandle);
		}

		break;
	case WM_DESTROY:
		onClosed();
		std::exit(0);
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