#include "Win32GLContext.h"
#include "../../../Assertion/Assert.h"

namespace SE
{
	namespace platform
	{
		namespace backend
		{
			Win32GLContext::Win32GLContext(HWND windowHandle, const GLVersion& glVersion)
				: Super(glVersion)
				, mContextHandle(NULL)
			{
				mWindowHandle = windowHandle;
			}

			Win32GLContext::~Win32GLContext()
			{
				deleteContext();
			}

			void Win32GLContext::createContext()
			{
				SPARK_ASSERT(mWindowHandle != NULL, "Win32GLContext::createContext - @param windowHandle is empty");

				PIXELFORMATDESCRIPTOR pfd;

				pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
				pfd.nVersion = 1;
				pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
				pfd.iPixelType = PFD_TYPE_RGBA;
				pfd.cColorBits = 32;

				pfd.cRedBits = 0;
				pfd.cRedShift = 0;

				pfd.cGreenBits = 0;
				pfd.cGreenShift = 0;

				pfd.cBlueBits = 0;
				pfd.cBlueShift = 0;

				pfd.cAlphaBits = 0;
				pfd.cAlphaShift = 0;

				pfd.cAccumBits = 0;
				pfd.cAccumRedBits = 0;
				pfd.cAccumGreenBits = 0;
				pfd.cAccumBlueBits = 0;
				pfd.cAccumAlphaBits = 0;

				pfd.cDepthBits = 24;
				pfd.cStencilBits = 8;
				pfd.iLayerType = PFD_MAIN_PLANE;
				pfd.bReserved = 0;
				pfd.dwLayerMask = 0;
				pfd.dwVisibleMask = 0;
				pfd.dwDamageMask = 0;

				HDC windowDc = GetDC(mWindowHandle);

				int pixelFormat = ChoosePixelFormat(windowDc, &pfd);

				if (pixelFormat != 0) {

					if (SetPixelFormat(windowDc, pixelFormat, &pfd)) {

						mContextHandle = wglCreateContext(windowDc);
						makeCurrent();

						if (glewInit() == GLEW_OK) {
							int majorVersion;
							int minorVersion;

							switch (mGLVersion) {
							case GLV_32:
								majorVersion = 3;
								minorVersion = 2;
								break;

							case GLV_35:
								majorVersion = 3;
								minorVersion = 5;
								break;

							case GLV_40:
								majorVersion = 4;
								minorVersion = 0;
								break;

							case GLV_42:
								majorVersion = 4;
								minorVersion = 2;
								break;

							case GLV_45:
								majorVersion = 4;
								minorVersion = 5;
								break;
							}

							int attributes[] =
							{
								WGL_CONTEXT_MAJOR_VERSION_ARB, majorVersion,
								WGL_CONTEXT_MINOR_VERSION_ARB, minorVersion,
								WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
								/*WGL_CONTEXT_PROFILE_MASK_ARB, 0,*/
								0
							};

							if (wglewIsSupported("WGL_ARB_create_context") == 1) {
								mContextHandle = wglCreateContextAttribsARB(windowDc, NULL, attributes);
							}
						}
					}
				}

				SPARK_ASSERT(mContextHandle != NULL, "Win32GLContext::createContext - context creation failed");
				ReleaseDC(mWindowHandle, windowDc);
			}

			void Win32GLContext::deleteContext()
			{
				if (mContextHandle != NULL) {
					wglDeleteContext(mContextHandle);
				}
			}

			void Win32GLContext::makeCurrent()
			{
				if (isCurrent() == false) {
					wglMakeCurrent(NULL, NULL);
					wglMakeCurrent(GetDC(mWindowHandle), mContextHandle);
				}
			}

			void Win32GLContext::swapBuffers()
			{
				HDC dc = GetDC(mWindowHandle);
				SwapBuffers(dc);
				ReleaseDC(mWindowHandle, dc);
			}

			void Win32GLContext::setSwapInterval(GLint swapInterval)
			{
				wglSwapIntervalEXT(swapInterval);
			}

			bool Win32GLContext::isCurrent()
			{
				return wglGetCurrentContext() == mContextHandle;
			}

			GLDevice* Win32GLContext::createGLDevice()
			{
				return new GLDevice();
			}
		}
	}
}