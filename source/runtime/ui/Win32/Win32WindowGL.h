#ifndef __WIN32WINDOWGL_H__
#define __WIN32WINDOWGL_H__

#include <Windows.h>
#include "../WindowGL.h"
#include "../../Platform/GFX/OpenGL/GLContext.h"

class Win32WindowGL : public WindowGL
{
public:
	Win32WindowGL(SE::platform::backend::GLContext::GLVersion contextVersion);
	Win32WindowGL(SE::platform::backend::GLContext::GLVersion contextVersion, const std::wstring& title);
	~Win32WindowGL();

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
	HWND						mHandle;
	static const wchar_t*		CLASS_NAME;
};


#endif // !__WIN32WINDOWGL_H__