#ifndef __RENDERCOMMAND_H__
#define __RENDERCOMMAND_H__

#include "../Platform/GFX/OpenGL/GLTypes.h"
#include "../Core/SmartPtrs/SharedPtr.h"

//#define MAX_CBUFFERS 12

enum RenderCommandID
{
	RC_NullCommand				= 0,
	RC_DrawIndexed				= 1,
	RC_Draw						= 2,
	RC_CopyConstBuffer			= 3,
	RC_ClearBuffers				= 4,
	RC_UseShaderProgram			= 5,
	RC_EnableAdditiveBlending	= 6,
	RC_SetFrameBuffer			= 7,
	RC_UseTexture				= 8,
	RC_SetCulling				= 9,
};

enum BlendingType
{
	BT_Additive = 0,
};

struct RenderCommand
{
	RenderCommandID		id;
	void*				data;
};

namespace command
{
	struct Draw
	{
		SE::platform::backend::GLVertexBufferHandle			vertexBuffer;

		unsigned int										verticesCount;
		unsigned int										verticesOffset;

		static const RenderCommandID						ID = RenderCommandID::RC_Draw;
	};

	struct DrawIndexed
	{
		SE::platform::backend::GLIndexBufferHandle			indexBuffer;
		SE::platform::backend::GLVertexBufferHandle			vertexBuffer;

		unsigned int										indicesCount;
		const void*											indicesOffset;

		static const RenderCommandID						ID = RenderCommandID::RC_DrawIndexed;
	};

	struct CopyConstantBuffer
	{
		SE::platform::backend::GLUniformBufferHandle		constantBuffer;

		void*												bufferData;
		unsigned int										bufferSize;

		static const RenderCommandID						ID = RenderCommandID::RC_CopyConstBuffer;
	};

	struct ClearBuffers
	{
		bool							bDepthBuffer;
		bool							bColorBuffer;

		float							clearColor[4];
		double							depthValue;

		static const RenderCommandID	ID = RenderCommandID::RC_ClearBuffers;
	};

	struct UseShaderProgram
	{
		SE::platform::backend::GLShaderProgramHandle			shaderProgram;

		static const RenderCommandID							ID = RenderCommandID::RC_UseShaderProgram;
	};

	struct EnableAdditiveBlending
	{
		bool							bAdditiveBlending;
		BlendingType					blendingType;

		static const RenderCommandID	ID = RenderCommandID::RC_EnableAdditiveBlending;
	};

	struct SetFrameBuffer
	{
		GLuint							frameBufferHandle;
		unsigned int					hResolution;
		unsigned int					vResolution;

		static const RenderCommandID	ID = RenderCommandID::RC_SetFrameBuffer;
	};

	struct UseTexture
	{
		unsigned int									textureHandle;
		unsigned int									textureBinding;
		unsigned int									textureLocation;

		SE::platform::backend::GLShaderProgramHandle	shaderHandle;

		static const RenderCommandID	ID = RenderCommandID::RC_UseTexture;
	};

	struct SetCulling
	{
		bool status;

		static const RenderCommandID ID = RenderCommandID::RC_SetCulling;
	};
}

//struct ConstantBuffer
//{
//	GLUniformBufferHandle		bufferHandle;
//
//	const void*					bufferData;
//	size_t						bufferSize;
//};
//
//struct RenderCommand
//{
//	GLShaderProgramHandle		shader;
//	ConstantBuffer				cBuffers[MAX_CBUFFERS];
//
//	DrawCalls::DrawCallID		drawCallID;
//	void*						drawCall;
//};

#endif // !__RENDECOMMAND_H__