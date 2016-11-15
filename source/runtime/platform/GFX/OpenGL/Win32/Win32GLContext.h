#ifndef __WIN32GLCONTEXT_H__
#define __WIN32GLCONTEXT_H__

#include <Windows.h>
#include "../GLContext.h"

#ifdef __GLEW_H__
#include <GL/wglew.h>
#endif 

namespace SE
{
	namespace platform
	{
		namespace backend
		{
			class Win32GLContext : public GLContext
			{
				typedef GLContext Super;

			public:
				Win32GLContext(HWND windowHandle, const GLVersion& glVersion);
				~Win32GLContext();

			public:
				virtual void				createContext() override;
				virtual void				deleteContext() override;
				virtual void				makeCurrent() override;
				virtual void				swapBuffers() override;
				virtual void				setSwapInterval(GLint swapInterval) override;
				virtual bool				isCurrent() override;
				//virtual GLVersion			findBestVersion() override;

				virtual GLDevice*			createGLDevice() override;

			private:
				HWND					mWindowHandle;
				HGLRC					mContextHandle;

			};
		}
	}
}

#endif // !__WIN32GLCONTEXT_H__