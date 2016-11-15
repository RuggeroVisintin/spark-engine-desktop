#ifndef __GLCONTEXT_H__
#define __GLCONTEXT_H__

#include <GL\glew.h>
#include "GLDevice.h"

namespace SE
{
	namespace platform
	{
		namespace backend
		{
			class GLContext
			{
			public:
				enum GLVersion
				{
					GLV_32 = 0,
					GLV_35,
					GLV_40,
					GLV_42,
					GLV_45,
				};

			public:
				GLContext(const GLVersion& glVersion) { mGLVersion = glVersion; }
				virtual ~GLContext() {}

			public:
				virtual void				createContext() = 0;
				virtual void				deleteContext() = 0;
				virtual void				makeCurrent() = 0;
				virtual void				swapBuffers() = 0;
				virtual void				setSwapInterval(GLint swapInterval) = 0;
				virtual bool				isCurrent() = 0;
				//virtual GLVersion			findBestVersion() = 0;

				virtual GLDevice*			createGLDevice() = 0;
				const GLVersion&	        getGLVersion() const { return mGLVersion; }

			protected:
				GLVersion					mGLVersion;

			};
		}
	}
}

#endif // !__GLCONTEXT_H__