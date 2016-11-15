#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <string>

class Window
{
public:
	Window() {}
	Window(const std::wstring& title) { mTitle = title; }
	virtual ~Window() {}

public:
	virtual void				show() = 0;
	virtual void				hide() = 0;

	virtual void				minimize() = 0;
	virtual void				maximize() = 0;

	virtual void				focus() = 0;
	virtual void				killFocus() = 0;

	virtual void				setFullscreen(bool fullscreen) = 0;

	virtual bool				isVisible() = 0;
	virtual bool				isEnabled() = 0;

	virtual bool				isMinimized() = 0;
	virtual bool				isMaximized() = 0;

	virtual bool				isFocused() = 0;
	virtual bool				isFullscreen() = 0;

	// put beside function callbacks, so the ui can manage itself and external events that needs
	// to know when some Ui events is generated can acces from outside the class
	virtual void				onCreate() = 0;
	virtual void				onResize(int width, int height) = 0;
	virtual void				onPaint() = 0;
	virtual void				onMove(int x, int y) = 0;
	virtual void				onFocus() = 0;
	virtual void				onKillFocus() = 0;
	virtual void				onClosing() = 0;
	virtual void				onClosed() = 0;
	virtual void				onIdle() = 0;
	virtual void				onKeyDown(int keyCode) = 0;
	virtual void				onKeyUp(int keyCode) = 0;
	virtual void				onMouseMove(int x, int y) = 0;
	virtual void				onLeftMouseUp(int x, int y) = 0;
	virtual void				onLeftMouseDown(int x, int y) = 0;
	virtual void				onRightMouseDown(int x, int y) = 0;

	void						setTitle(const std::wstring& title) { mTitle = title; }
	const std::wstring&			getTitle() const { return mTitle; }
	
protected:
	std::wstring				mTitle;

	int							mX;
	int							mY;
	int							mWidth;
	int							mHeight;

	bool						mFullscreen;

};

#endif // !__WINDOW_H__