#ifndef __WIN32WINDOW_H__
#define __WIN32WINDOW_H__

#include <Windows.h>
#include "../Window.h"

class Win32Window : public Window
{
	typedef Window Super;

public:
	Win32Window();
	Win32Window(const std::wstring& title);
	~Win32Window();

public:
	virtual void		show() override;
	virtual void		hide() override;

	virtual void		minimize() override;
	virtual void		maximize() override;

	virtual void		focus() override;
	virtual void		killFocus() override;

	virtual void		setFullscreen(bool fullscreen) override;

	virtual bool		isVisible() override;
	virtual bool		isEnabled() override;

	virtual bool		isMinimized() override;
	virtual bool		isMaximized() override;

	virtual bool		isFocused() override;
	virtual bool		isFullscreen() override;

	virtual void		onCreate() override {}
	virtual void		onResize(int width, int height) override {}
	virtual void		onPaint() override {}
	virtual void		onMove(int x, int y) override {}
	virtual void		onFocus() override {}
	virtual void		onKillFocus() override {}
	virtual void		onClosing() override {}
	virtual void		onClosed() override {}
	virtual void		onIdle() override {}
	virtual void		onKeyDown(int keyCode) override {}
	virtual void		onKeyUp(int keyCode) override {}
	virtual void		onMouseMove(int x, int y) override {}
	virtual void		onLeftMouseUp(int x, int y) override {}
	virtual void		onLeftMouseDown(int x, int y) override {}
	virtual void		onRightMouseDown(int x, int y) override {}

private:
	static LRESULT CALLBACK msgRouter(HWND, UINT, WPARAM, LPARAM);
	virtual LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

private:
	HWND				mHandle;

};

#endif // !__WIN32WINDOW_H__