#ifndef __GLDEVICE_H__
#define __GLDEVICE_H__

#include <GL\glew.h>
#include "GLTypes.h"

namespace SE
{
	namespace platform
	{
		namespace backend
		{
			class GLDevice
			{
			public:
				GLDevice();
				~GLDevice();

			public:
				void						clearBuffers(GLbitfield buffers) const;
				void						clearColor(float red, float blue, float green, float alpha) const;

				GLVertexBufferHandle		createVertexBuffer() const;
				GLIndexBufferHandle			createIndexBuffer() const;
				GLVertexArrayHandle			createVertexArray() const;

				GLShaderProgramHandle		createShaderProgram() const;
				GLShaderHandle				createVertexShader() const;
				GLShaderHandle				createFragmentShader() const;

				GLUniformBufferHandle		createUniformBuffer() const;

				GLTexture2DHandle			create2DTextureHandle() const;
				GLTexture3DHandle			create3DTextureHandle() const;

				void						destroyVertexBuffer(const GLVertexBufferHandle& vertexBufferHandle) const;
				void						destroyIndexBuffer(const GLIndexBufferHandle& indexBufferHandle) const;
				void						destroyVertexArray(const GLVertexArrayHandle& vertexArrayObjectHandle) const;

				void						destroyShaderProrgam(GLShaderProgramHandle shaderProgramHandle) const;
				void						destroyShader(GLShaderHandle shaderHandle) const;
				void						destroyUniformBuffer(GLUniformBufferHandle uniformBufferHandle) const;

				void						bindVertexBuffer(GLVertexBufferHandle vertexBufferHandle) const;
				void						bindIndexBuffer(GLIndexBufferHandle indexBufferHandle) const;
				void						bindVertexArray(GLVertexArrayHandle vertexArrayObjectHandle) const;
				void						bindUniformBuffer(GLUniformBufferHandle uniformBufferHandle) const;
				void						bindUniformBufferBase(GLuint index, GLUniformBufferHandle uniformBufferHandle) const;
				void						bindTexture2D(GLTexture2DHandle glTextureHandle) const;

				void						fillVertexBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage) const;
				void						fillIndexBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage) const;
				void						fillUniformBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage) const;
				void						fillTexture2D(GLint level, GLint colorFormat, GLsizei width, GLsizei height, GLint border, GLenum pixelFormat, GLenum type, const GLvoid* data) const;

				void						fillUniformBufferSub(GLintptr offset, GLsizeiptr size, const GLvoid* data) const;

				void						defineVertexAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) const;
				void						enableVertexAttributeArray(GLuint index) const;
				void						disableVertexAtributeArray(GLuint index) const;

				void						drawPrimitive(GLenum mode, GLint first, GLsizei count) const;
				void						drawIndexedPrimitive(GLenum mode, GLsizei count, GLenum type, const GLvoid* offset) const;

				void						unbindVertexBuffer() const;
				void						unbindIndexBuffer() const;
				void						unbindVertexArray() const;
				void						unbindUnifromBuffer() const;

				void						setShaderSource(GLShaderHandle shaderHandle, GLsizei count, const GLchar** shaderSource, const GLint* length) const;
				void						compileShader(GLShaderHandle shaderHandle) const;

				void						attachShader(GLShaderProgramHandle shaderProgramHandle, GLShaderHandle shaderHandle) const;
				void						linkProgram(GLShaderProgramHandle shaderProgramHandle) const;
				void						useProgram(GLShaderProgramHandle shaderProgramHandle) const;

				GLuint						getUniformLocation(GLShaderProgramHandle shaderProgram, const GLchar* name) const;
				GLuint						getUniformBufferLocation(GLShaderProgramHandle shaderProgram, const GLchar* name) const;
				void						setUniformBufferBinding(GLShaderProgramHandle shaderProgram, GLuint bufferLocation, GLuint bindingPoint) const;

				void						uniformFloat(GLint location, GLfloat value) const;
				void						uniformFloatV(GLint location, GLsizei count, const GLfloat* values) const;

				void						uniformFloat2(GLint location, GLfloat xValue, GLfloat yValue) const;
				void						uniformFloat2V(GLint location, GLsizei count, const GLfloat* values) const;

				void						uniformFloat3(GLint location, GLfloat xValue, GLfloat yValue, GLfloat zValue) const;
				void						uniformFloat3V(GLint location, GLsizei count, const GLfloat* values) const;

				void						uniformFloat4(GLint location, GLfloat xValue, GLfloat yValue, GLfloat zValue, GLfloat wValue) const;
				void						uniformFloat4V(GLint location, GLsizei count, const GLfloat* values) const;

				void						uniformFloat22(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const;
				void						uniformFloat23(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const;
				void						uniformFloat24(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const;

				void						uniformFloat32(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const;
				void						uniformFloat33(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const;
				void						uniformFloat34(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const;

				void						uniformFloat42(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const;
				void						uniformFloat43(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const;
				void						uniformFloat44(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const;

				void						uniformDouble(GLint location, GLdouble value) const;
				void						uniformDoubleV(GLint location, GLsizei count, const GLdouble* values) const;

				void						uniformDouble2(GLint location, GLdouble xValue, GLdouble yValue) const;
				void						uniformDouble2V(GLint location, GLsizei count, const GLdouble* values) const;

				void						uniformDouble3(GLint location, GLdouble xValue, GLdouble yValue, GLdouble zValue) const;
				void						uniformDouble3V(GLint location, GLsizei count, const GLdouble* values) const;

				void						uniformDouble4(GLint location, GLdouble xValue, GLdouble yValue, GLdouble zValue, GLdouble wValue) const;
				void						uniformDouble4V(GLint location, GLsizei count, const GLdouble* values) const;

				void						uniformDouble22(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const;
				void						uniformDouble23(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const;
				void						uniformDouble24(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const;

				void						uniformDouble32(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const;
				void						uniformDouble33(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const;
				void						uniformDouble34(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const;

				void						uniformDouble42(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const;
				void						uniformDouble43(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const;
				void						uniformDouble44(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const;

				void						defineTexture2DParamInt(GLenum param, GLint value) const;
				void						generateTexture2DMipmap() const;

				void						enable(GLenum cap) const;

				// WARNING: can cause performance issues
				GLVertexBufferHandle		getCurrentVertexBuffer() const;

				// WARNING: can cause performance issues
				GLIndexBufferHandle			getCurrentIndexBuffer() const;

				// WARNING: can cause performance issues
				GLVertexArrayHandle			getCurrentVertexArray() const;

				// WARNING: can cause performance issues
				GLShaderCompilationStatus	getShaderCompilationStatus(GLShaderHandle shader) const;
			};
		}
	}
}

#endif // !__GLDEVICE_H__