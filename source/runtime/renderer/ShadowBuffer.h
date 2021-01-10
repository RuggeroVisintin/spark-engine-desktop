#ifndef __SHADOWBUFFER_H__
#define __SHADOWBUFFER_H__

#include <GFX/OpenGL/GLDevice.h>
#include "Renderer.h"

class ShadowBuffer
{
public:
	ShadowBuffer(Renderer* renderer, unsigned int vResolution, unsigned int hResolution)
		: vResolution(vResolution)
		, hResolution(hResolution)
		, mRenderer(renderer)
	{
		SPARK_ASSERT(mRenderer != nullptr, "ShadowBuffer::constructor - @param renderer - is null");

		glGenFramebuffers(1, &mFrameBufferHandle);
		glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferHandle);

		// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
		glGenTextures(1, &mTextureHandle);
		glBindTexture(GL_TEXTURE_2D, mTextureHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, vResolution, hResolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mTextureHandle, 0);

		glDrawBuffer(GL_NONE);

		/*glGenFramebuffers(1, &mFrameBufferHandle);
		glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferHandle);

		glGenTextures(1, &mTextureHandle);
		glBindTexture(GL_TEXTURE_2D, mTextureHandle);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32, hResolution, vResolution);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mTextureHandle, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);*/

		SPARK_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "ShadowBuffer::constructor - error during framebuffer initialization");
	}

public:
	void startFrame() const {
		command::SetFrameBuffer* setFrameBufferCommand = mRenderer->pushRenderCommand<command::SetFrameBuffer>();
		setFrameBufferCommand->frameBufferHandle = mFrameBufferHandle;
		setFrameBufferCommand->hResolution = hResolution;
		setFrameBufferCommand->vResolution = vResolution;
	}

	void endFrame() const {
		command::SetFrameBuffer* setFrameBufferCommand = mRenderer->pushRenderCommand<command::SetFrameBuffer>();
		setFrameBufferCommand->frameBufferHandle = 0;
	}
	
	GLuint getTextureHandle() const {
		return this->mTextureHandle;
	}

public:
	unsigned int		vResolution;
	unsigned int		hResolution;

private:
	GLuint				mFrameBufferHandle;
	GLuint				mTextureHandle;

	Renderer*			mRenderer;
};

#endif // !__SHADOWBUFFER_H__
