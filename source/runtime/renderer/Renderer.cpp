#include "Renderer.h"

void Renderer::endFrame(SE::platform::backend::GLContext& graphicsContext)
{
	//mFrameBuffer.startFrame(mGfx);

	for each(RenderCommand renderCommand in mSwapBuffer) {

		// this is the very early version
		switch (renderCommand.id) 
		{
			case command::DrawIndexed::ID: 
			{
				command::DrawIndexed* data = (command::DrawIndexed*)renderCommand.data;
				drawIndexedPrimitive(*data);

				break;
			} 
			case command::CopyConstantBuffer::ID: 
			{
				command::CopyConstantBuffer* data = (command::CopyConstantBuffer*)renderCommand.data;
				copyConstantBuffer(*data);

				break;
			}
			case command::ClearBuffers::ID:
			{
				command::ClearBuffers* data = (command::ClearBuffers*)renderCommand.data;
				clearBuffers(*data);

				break;
			}
			case command::UseShaderProgram::ID:
			{
				command::UseShaderProgram* data = (command::UseShaderProgram*)renderCommand.data;
				useShaderProgram(*data);

				break;
			}
			case command::EnableAdditiveBlending::ID:
			{
				command::EnableAdditiveBlending* data = (command::EnableAdditiveBlending*)renderCommand.data;
				enableAdditiveBlending(*data);

				break;
			}
		}

		delete renderCommand.data;
	}

	//mFrameBuffer.endFrame(mGfx);
	

	mSwapBuffer = mCommandBuffer;
	mCommandBuffer.clear();
	graphicsContext.swapBuffers();
}

void Renderer::drawIndexedPrimitive(command::DrawIndexed command)
{
	if (mLastIndexBuffer != command.indexBuffer) 
{
		mGfx->bindIndexBuffer(command.indexBuffer);
		mLastIndexBuffer = command.indexBuffer;
	}

	mGfx->drawIndexedPrimitive(GL_TRIANGLES, command.indicesCount, GL_UNSIGNED_INT, command.indicesOffset);
}

void Renderer::copyConstantBuffer(command::CopyConstantBuffer command)
{
	if (mLastConstantBuffer != command.constantBuffer) {
		mGfx->bindUniformBuffer(command.constantBuffer);
		mLastConstantBuffer = command.constantBuffer;
	}

	mGfx->fillUniformBufferSub(0, command.bufferSize, command.bufferData);
	delete command.bufferData;
}

void Renderer::clearBuffers(command::ClearBuffers command)
{
	unsigned int bitfield = 0;

	if (command.bDepthBuffer == true) {
		bitfield |= GL_DEPTH_BUFFER_BIT;

		if (mLastClearColor[0] != command.clearColor[0] || 
			mLastClearColor[1] != command.clearColor[1] || 
			mLastClearColor[2] != command.clearColor[2] || 
			mLastClearColor[3] != command.clearColor[3]) 
		{
			mGfx->clearColor(command.clearColor[0],
							command.clearColor[1],
							command.clearColor[2],
							command.clearColor[3]);

			mLastClearColor[0] = command.clearColor[0];
			mLastClearColor[1] = command.clearColor[1];
			mLastClearColor[2] = command.clearColor[2];
			mLastClearColor[3] = command.clearColor[3];
		}
	}

	if (command.bColorBuffer == true) {
		bitfield |= GL_COLOR_BUFFER_BIT;
	}

	mGfx->clearBuffers(bitfield);
}

void Renderer::useShaderProgram(command::UseShaderProgram command)
{
	if (command.shaderProgram != mLastShaderProgram)
	{
		mGfx->useProgram(command.shaderProgram);
		mLastShaderProgram = command.shaderProgram;
	}
}

void Renderer::enableAdditiveBlending(command::EnableAdditiveBlending command)
{
	if (mLastBlendingMode != command.bAdditiveBlending) {
		if (command.bAdditiveBlending == true) {
			glEnable(GL_BLEND);
			glDepthMask(GL_FALSE);
			glDepthFunc(GL_LEQUAL);

			if (command.blendingType != mLastBlendingType) {
				switch (command.blendingType)
				{
					case BlendingType::BT_Additive:
					{
						glBlendFunc(GL_ONE, GL_ONE);

						break;
					}
				}
			}
		} else {
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);
			glDepthFunc(GL_LESS);
		}
	}
}