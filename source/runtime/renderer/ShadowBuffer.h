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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, vResolution, hResolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mTextureHandle, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		SPARK_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "ShadowBuffer::constructor - error during framebuffer initialization");
	}

public:
	void startFrame() const {
		command::SetCulling* setCullingCommand = mRenderer->pushRenderCommand<command::SetCulling>();
		setCullingCommand->status = false;

		command::SetFrameBuffer* setFrameBufferCommand = mRenderer->pushRenderCommand<command::SetFrameBuffer>();
		setFrameBufferCommand->frameBufferHandle = mFrameBufferHandle;
		setFrameBufferCommand->hResolution = hResolution;
		setFrameBufferCommand->vResolution = vResolution;
	}

	void endFrame() const {
		command::SetFrameBuffer* setFrameBufferCommand = mRenderer->pushRenderCommand<command::SetFrameBuffer>();
		setFrameBufferCommand->frameBufferHandle = 0;

		command::SetCulling* setCullingCommand = mRenderer->pushRenderCommand<command::SetCulling>();
		setCullingCommand->status = true;
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
