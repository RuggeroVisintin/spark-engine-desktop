#ifndef __GLTYPES_H__
#define __GLTYPES_H__

#define GLEW_STATIC
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

#include <GL\glew.h>
#include <string>

#define SPARK_GL_NULL GL_INVALID_INDEX

namespace SE
{
	namespace platform
	{
		namespace backend
		{
			class GLTexture2DHandle
			{
				friend class GLDevice;

			public:
				bool			isNull() const { return handleGL == SPARK_GL_NULL; }

				bool			operator!=(const GLTexture2DHandle& texture2DHandle) const
				{
					return handleGL != texture2DHandle.handleGL;
				}

				bool			operator==(const GLTexture2DHandle& texture2DHandle) const
				{
					return handleGL == texture2DHandle.handleGL;
				}

			private:
				GLuint			handleGL = SPARK_GL_NULL;
			};

			class GLTexture3DHandle
			{
				friend class GLDevice;

			public:
				bool			isNull() const { return handleGL == SPARK_GL_NULL; }

				bool			operator!=(const GLTexture3DHandle& texture3DHandle) const
				{
					return handleGL != texture3DHandle.handleGL;
				}

				bool			operator==(const GLTexture3DHandle& texture3DHandle) const
				{
					return handleGL == texture3DHandle.handleGL;
				}

			private:
				GLuint			handleGL = SPARK_GL_NULL;
			};

			class GLVertexBufferHandle
			{
				friend class GLDevice;

			public:
				bool			isNull() const { return handleGL == SPARK_GL_NULL; }

				bool			operator!=(const GLVertexBufferHandle& vertexBuffer) const
				{
					return handleGL != vertexBuffer.handleGL;
				}

				bool			operator==(const GLVertexBufferHandle& vertexBuffer) const
				{
					return handleGL == vertexBuffer.handleGL;
				}

			private:
				GLuint			handleGL = SPARK_GL_NULL;
			};

			class GLIndexBufferHandle
			{
				friend class GLDevice;

			public:
				bool			isNull() const { return handleGL == SPARK_GL_NULL; }

				bool			operator!=(const GLIndexBufferHandle& indexBuffer) const
				{
					return handleGL != indexBuffer.handleGL;
				}

				bool			operator==(const GLIndexBufferHandle& indexBuffer) const
				{
					return handleGL == indexBuffer.handleGL;
				}

			private:
				GLuint			handleGL = SPARK_GL_NULL;
			};

			class GLVertexArrayHandle
			{
				friend class GLDevice;

			public:
				bool			isNull() const { return handleGL == SPARK_GL_NULL; }

			private:
				GLuint			handleGL = SPARK_GL_NULL;
			};

			class GLShaderProgramHandle
			{
				friend class GLDevice;

			public:
				bool			isNull() const { return handleGL == SPARK_GL_NULL; }

				bool			operator!=(const GLShaderProgramHandle& shaderProrgam) const
				{
					return handleGL != shaderProrgam.handleGL;
				}

				bool			operator==(const GLShaderProgramHandle& shaderProrgam) const
				{
					return handleGL == shaderProrgam.handleGL;
				}

			private:
				GLuint			handleGL = SPARK_GL_NULL;
			};

			class GLShaderHandle
			{
				friend class GLDevice;

			public:
				bool			isNull() const { return handleGL == SPARK_GL_NULL; }

			private:
				GLuint			handleGL = SPARK_GL_NULL;
			};

			class GLUniformBufferHandle
			{
				friend class GLDevice;

			public:
				bool			isNull() const { return handleGL == SPARK_GL_NULL; }

				bool			operator!=(const GLUniformBufferHandle& uniformBuffer) const
				{
					return handleGL != uniformBuffer.handleGL;
				}

				bool			operator==(const GLUniformBufferHandle& uniformBuffer) const
				{
					return handleGL == uniformBuffer.handleGL;
				}

			private:
				GLuint			handleGL = SPARK_GL_NULL;

			};

			class GLShaderCompilationStatus
			{
			public:
				bool				isCompiled;
				std::string			infoLog;
			};
		}
	}
}

#endif // !__GLTYPES_H__