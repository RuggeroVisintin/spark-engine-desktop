#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include "../Platform/GFX/OpenGL/GLDevice.h"

class FrameBufferBase
{
public:
	void		setAsFrameBuffer(SE::platform::backend::GLDevice* gfx)
	{
		glGenFramebuffers(1, &frameBufferHandle);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);

		glGenTextures(1, &colorTextureHandle);
		glBindTexture(GL_TEXTURE_2D, colorTextureHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTextureHandle, 0);

		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glGenBuffers(1, &quad);
		glBindBuffer(GL_ARRAY_BUFFER, quad);

		static const GLfloat g_quad_vertex_buffer_data[] =
		{
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			1.0f,  1.0f, 0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
	}

	void		startFrame(SE::platform::backend::GLDevice* gfx)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
		glViewport(0, 0, 1024, 768);
	}

	void		endFrame(SE::platform::backend::GLDevice* gfx)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

public:
	int			verticalResolution;
	int			horizontalResolution;

private:
	GLuint		frameBufferHandle;
	GLuint		colorTextureHandle;
	GLuint		rbo;

public:
	GLuint		quad;

};

#endif // !__FRAMEBUFFER_H__