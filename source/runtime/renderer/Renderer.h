#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>

#include "../Platform/GFX/OpenGL/GLDevice.h"
#include "../Platform/GFX/OpenGL/GLContext.h"
#include "../Platform/Assertion/Assert.h"
#include "RenderCommand.h"
#include "FrameBuffer.h"

// next version will remove renderer class and instead it will use buckets
class Renderer
{
public:
	Renderer(SE::platform::backend::GLDevice* gfx, unsigned int internalHRes, unsigned int internalVRes)
		: mGfx(gfx)
		, mInternalHRes(internalHRes)
		, mInternalVRes(internalVRes)
	{
		mFrameBuffer.setAsFrameBuffer(mGfx);
	}

	~Renderer()
	{
	}

public:
	template <class Command>
	Command*						pushRenderCommand();
	void							endFrame(SE::platform::backend::GLContext& graphicsContext);

private:
	void							drawIndexedPrimitive(command::DrawIndexed command);
	void							copyConstantBuffer(command::CopyConstantBuffer command);
	void							clearBuffers(command::ClearBuffers command);
	void							useShaderProgram(command::UseShaderProgram command);
	void							enableAdditiveBlending(command::EnableAdditiveBlending command);
	void							setFramebuffer(command::SetFrameBuffer command);
	void							useTexture(command::UseTexture command);
	void							setCulling(command::SetCulling command);

private:
	unsigned int					mInternalHRes;
	unsigned int					mInternalVRes;
	//void							swapBuffers();

private:
	SE::platform::backend::GLDevice*						mGfx;

	std::vector<RenderCommand>								mCommandBuffer;
	std::vector<RenderCommand>								mSwapBuffer;

	SE::platform::backend::GLIndexBufferHandle				mLastIndexBuffer;
	SE::platform::backend::GLVertexBufferHandle				mLastVertexBuffer;
	SE::platform::backend::GLUniformBufferHandle			mLastConstantBuffer;
	SE::platform::backend::GLShaderProgramHandle			mLastShaderProgram;

	bool													mLastBlendingMode;
	BlendingType											mLastBlendingType;

	float													mLastClearColor[4];

	// Keep hardcoded for now
	FrameBufferBase											mFrameBuffer;
};

template <class Command>
Command* Renderer::pushRenderCommand()
{
	RenderCommand renderCommand;
	renderCommand.id = Command::ID;
	renderCommand.data = new Command();
	//renderCommand.cBuffers = memcpy(cBuffers, cBuffers, sizeof(ConstantBuffer) * MAX_CBUFFERS);

	mCommandBuffer.push_back(renderCommand);

	return (Command*)renderCommand.data;
}

#endif // !__RENDERER_H__