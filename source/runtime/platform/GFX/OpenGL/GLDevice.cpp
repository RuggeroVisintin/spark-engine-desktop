#include "GLDevice.h"
#include <string>

namespace SE
{
	namespace platform
	{
		namespace backend
		{
			GLDevice::GLDevice()
			{

			}

			GLDevice::~GLDevice()
			{

			}

			GLVertexBufferHandle GLDevice::createVertexBuffer() const
			{
				GLVertexBufferHandle bufferHandle;
				glGenBuffers(1, &bufferHandle.handleGL);

				return bufferHandle;
			}

			GLIndexBufferHandle GLDevice::createIndexBuffer() const
			{
				GLIndexBufferHandle bufferHandle;
				glGenBuffers(1, &bufferHandle.handleGL);

				return bufferHandle;
			}

			GLVertexArrayHandle GLDevice::createVertexArray() const
			{
				GLVertexArrayHandle vertexArrayHandle;
				glGenVertexArrays(1, &vertexArrayHandle.handleGL);

				return vertexArrayHandle;
			}

			GLShaderProgramHandle GLDevice::createShaderProgram() const
			{
				GLShaderProgramHandle glShaderProgramHandle;
				glShaderProgramHandle.handleGL = glCreateProgram();

				return glShaderProgramHandle;
			}

			GLShaderHandle GLDevice::createVertexShader() const
			{
				GLShaderHandle glShaderHandle;
				glShaderHandle.handleGL = glCreateShader(GL_VERTEX_SHADER);

				return glShaderHandle;
			}

			GLShaderHandle GLDevice::createFragmentShader() const
			{
				GLShaderHandle glShaderHandle;
				glShaderHandle.handleGL = glCreateShader(GL_FRAGMENT_SHADER);

				return glShaderHandle;
			}

			GLUniformBufferHandle GLDevice::createUniformBuffer() const
			{
				GLUniformBufferHandle glUniformBufferHandle;
				glGenBuffers(1, &glUniformBufferHandle.handleGL);

				return glUniformBufferHandle;
			}

			GLTexture2DHandle GLDevice::create2DTextureHandle() const
			{
				GLTexture2DHandle glTextureHandle;
				glGenTextures(1, &glTextureHandle.handleGL);

				return glTextureHandle;
			}
			
			GLTexture3DHandle GLDevice::create3DTextureHandle() const
			{
				GLTexture3DHandle glTextureHandle;
				glGenTextures(1, &glTextureHandle.handleGL);

				return glTextureHandle;
			}

			void GLDevice::destroyVertexBuffer(const GLVertexBufferHandle& vertexBufferHandle) const
			{
				glDeleteBuffers(1, &vertexBufferHandle.handleGL);
			}

			void GLDevice::destroyIndexBuffer(const GLIndexBufferHandle& indexBufferHandle) const
			{
				glDeleteBuffers(1, &indexBufferHandle.handleGL);
			}

			void GLDevice::destroyVertexArray(const GLVertexArrayHandle& vertexArrayObjectHandle) const
			{
				glDeleteVertexArrays(1, &vertexArrayObjectHandle.handleGL);
			}

			void GLDevice::destroyShaderProrgam(GLShaderProgramHandle shaderProgramHandle) const
			{
				glDeleteProgram(shaderProgramHandle.handleGL);
			}

			void GLDevice::destroyShader(GLShaderHandle shaderHandle) const
			{
				glDeleteShader(shaderHandle.handleGL);
			}

			void GLDevice::destroyUniformBuffer(GLUniformBufferHandle uniformBufferHandle) const
			{
				glDeleteBuffers(1, &uniformBufferHandle.handleGL);
			}

			void GLDevice::bindVertexBuffer(GLVertexBufferHandle vertexBufferHandle) const
			{
				glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle.handleGL);
			}

			void GLDevice::bindIndexBuffer(GLIndexBufferHandle indexBufferHandle) const
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle.handleGL);
			}

			void GLDevice::bindVertexArray(GLVertexArrayHandle vertexArrayObjectHandle) const
			{
				glBindVertexArray(vertexArrayObjectHandle.handleGL);
			}

			void GLDevice::bindUniformBuffer(GLUniformBufferHandle uniformBufferHandle) const
			{
				glBindBuffer(GL_UNIFORM_BUFFER, uniformBufferHandle.handleGL);
			}

			void GLDevice::bindUniformBufferBase(GLuint index, GLUniformBufferHandle uniformBufferHandle) const
			{
				glBindBufferBase(GL_UNIFORM_BUFFER, index, uniformBufferHandle.handleGL);
			}

			void GLDevice::bindTexture2D(GLTexture2DHandle glTextureHandle) const
			{
				glBindTexture(GL_TEXTURE_2D, glTextureHandle.handleGL);
			}

			void GLDevice::fillVertexBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage) const
			{
				glBufferData(GL_ARRAY_BUFFER, size, data, usage);
			}

			void GLDevice::fillIndexBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage) const
			{
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
			}

			void GLDevice::fillUniformBuffer(GLsizeiptr size, const GLvoid* data, GLenum usage) const
			{
				glBufferData(GL_UNIFORM_BUFFER, size, data, usage);
			}

			void GLDevice::fillTexture2D(GLint level, GLint colorFormat, GLsizei width, GLsizei height, GLint border, GLenum pixelFormat, GLenum type, const GLvoid* data) const
			{
				glTexImage2D(GL_TEXTURE_2D, level, colorFormat, width, height, border, pixelFormat, type, data);
			}

			void GLDevice::fillUniformBufferSub(GLintptr offset, GLsizeiptr size, const GLvoid* data) const
			{
				glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
			}

			void GLDevice::defineVertexAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* offset) const
			{
				glVertexAttribPointer(index, size, type, normalized, stride, offset);
			}

			void GLDevice::enableVertexAttributeArray(GLuint index) const
			{
				glEnableVertexAttribArray(index);
			}

			void GLDevice::disableVertexAtributeArray(GLuint index) const
			{
				glDisableVertexAttribArray(index);
			}

			void GLDevice::drawPrimitive(GLenum mode, GLint first, GLsizei count) const
			{
				glDrawArrays(mode, first, count);
			}

			void GLDevice::drawIndexedPrimitive(GLenum mode, GLsizei count, GLenum type, const GLvoid* offset) const
			{
				glDrawElements(mode, count, type, offset);
			}

			void GLDevice::unbindVertexBuffer() const
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			void GLDevice::unbindIndexBuffer() const
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}

			void GLDevice::unbindVertexArray() const
			{
				glBindVertexArray(0);
			}

			void GLDevice::unbindUnifromBuffer() const
			{
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}

			void GLDevice::setShaderSource(GLShaderHandle shaderHandle, GLsizei count, const GLchar** shaderSource, const GLint* length) const
			{
				glShaderSource(shaderHandle.handleGL, count, shaderSource, length);
			}

			void GLDevice::compileShader(GLShaderHandle shaderHandle) const
			{
				glCompileShader(shaderHandle.handleGL);
			}

			void GLDevice::attachShader(GLShaderProgramHandle shaderProgramHandle, GLShaderHandle shaderHandle) const
			{
				glAttachShader(shaderProgramHandle.handleGL, shaderHandle.handleGL);
			}

			void GLDevice::linkProgram(GLShaderProgramHandle shaderProgramHandle) const
			{
				glLinkProgram(shaderProgramHandle.handleGL);
			}

			void GLDevice::useProgram(GLShaderProgramHandle shaderProgramHandle) const
			{
				glUseProgram(shaderProgramHandle.handleGL);	
			}

			void GLDevice::clearBuffers(GLbitfield buffers) const
			{
				glClear(buffers);
			}


			void GLDevice::clearColor(float red, float green, float blue, float alpha) const
			{
				glClearColor(red, green, blue, alpha);
			}

			GLuint GLDevice::getUniformLocation(GLShaderProgramHandle shaderProgram, const GLchar* name) const
			{
				return glGetUniformLocation(shaderProgram.handleGL, name);
			}

			GLuint GLDevice::getUniformBufferLocation(GLShaderProgramHandle shaderProgram, const GLchar* name) const
			{
				return glGetUniformBlockIndex(shaderProgram.handleGL, name);
			}

			void GLDevice::setUniformBufferBinding(GLShaderProgramHandle shaderProgram, GLuint bufferLocation, GLuint bindingPoint) const
			{
				glUniformBlockBinding(shaderProgram.handleGL, bufferLocation, bindingPoint);
			}

			// ========================================== Int uniforms =========================================== //
			// ===================================================================================================== //

			void GLDevice::uniformInt(GLint location, GLint value) const
			{
				glUniform1i(location, value);
			}

			// ========================================== Float uniforms =========================================== //
			// ===================================================================================================== //

			void GLDevice::uniformFloat(GLint location, GLfloat value) const
			{
				glUniform1f(location, value);
			}

			void GLDevice::uniformFloatV(GLint location, GLsizei count, const GLfloat* values) const
			{
				glUniform1fv(location, count, values);
			}

			void GLDevice::uniformFloat2(GLint location, GLfloat xValue, GLfloat yValue) const
			{
				glUniform2f(location, xValue, yValue);
			}

			void GLDevice::uniformFloat2V(GLint location, GLsizei count, const GLfloat* values) const
			{
				glUniform2fv(location, count, values);
			}

			void GLDevice::uniformFloat3(GLint location, GLfloat xValue, GLfloat yValue, GLfloat zValue) const
			{
				glUniform3f(location, xValue, yValue, zValue);
			}

			void GLDevice::uniformFloat3V(GLint location, GLsizei count, const GLfloat* values) const
			{
				glUniform3fv(location, count, values);
			}

			void GLDevice::uniformFloat4(GLint location, GLfloat xValue, GLfloat yValue, GLfloat zValue, GLfloat wValue) const
			{
				glUniform4f(location, xValue, yValue, zValue, wValue);
			}

			void GLDevice::uniformFloat4V(GLint location, GLsizei count, const GLfloat* values) const
			{
				glUniform4fv(location, count, values);
			}

			void GLDevice::uniformFloat22(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const
			{
				glUniformMatrix2fv(location, count, transpose, values);
			}

			void GLDevice::uniformFloat23(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const
			{
				glUniformMatrix2x3fv(location, count, transpose, values);
			}

			void GLDevice::uniformFloat24(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const
			{
				glUniformMatrix2x4fv(location, count, transpose, values);
			}

			void GLDevice::uniformFloat32(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const
			{
				glUniformMatrix3x2fv(location, count, transpose, values);
			}

			void GLDevice::uniformFloat33(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const
			{
				glUniformMatrix3fv(location, count, transpose, values);
			}

			void GLDevice::uniformFloat34(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const
			{
				glUniformMatrix3x4fv(location, count, transpose, values);
			}

			void GLDevice::uniformFloat42(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const
			{
				glUniformMatrix4x2fv(location, count, transpose, values);
			}

			void GLDevice::uniformFloat43(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const
			{
				glUniformMatrix4x3fv(location, count, transpose, values);
			}

			void GLDevice::uniformFloat44(GLint location, GLsizei count, GLboolean transpose, const GLfloat* values) const
			{
				glUniformMatrix4fv(location, count, transpose, values);
			}

			// ========================================== Double uniforms ========================================== //
			// ===================================================================================================== //

			void GLDevice::uniformDouble(GLint location, GLdouble value) const
			{
				glUniform1d(location, value);
			}

			void GLDevice::uniformDoubleV(GLint location, GLsizei count, const GLdouble* values) const
			{
				glUniform1dv(location, count, values);
			}

			void GLDevice::uniformDouble2(GLint location, GLdouble xValue, GLdouble yValue) const
			{
				glUniform2d(location, xValue, yValue);
			}

			void GLDevice::uniformDouble2V(GLint location, GLsizei count, const GLdouble* values) const
			{
				glUniform2dv(location, count, values);
			}

			void GLDevice::uniformDouble3(GLint location, GLdouble xValue, GLdouble yValue, GLdouble zValue) const
			{
				glUniform3d(location, xValue, yValue, zValue);
			}

			void GLDevice::uniformDouble3V(GLint location, GLsizei count, const GLdouble* values) const
			{
				glUniform3dv(location, count, values);
			}

			void GLDevice::uniformDouble4(GLint location, GLdouble xValue, GLdouble yValue, GLdouble zValue, GLdouble wValue) const
			{
				glUniform4d(location, xValue, yValue, zValue, wValue);
			}

			void GLDevice::uniformDouble4V(GLint location, GLsizei count, const GLdouble* values) const
			{
				glUniform4dv(location, count, values);
			}

			void GLDevice::uniformDouble22(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const
			{
				glUniformMatrix2dv(location, count, transpose, values);
			}

			void GLDevice::uniformDouble23(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const
			{
				glUniformMatrix2x3dv(location, count, transpose, values);
			}

			void GLDevice::uniformDouble24(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const
			{
				glUniformMatrix2x4dv(location, count, transpose, values);
			}

			void GLDevice::uniformDouble32(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const
			{
				glUniformMatrix3x2dv(location, count, transpose, values);
			}

			void GLDevice::uniformDouble33(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const
			{
				glUniformMatrix3dv(location, count, transpose, values);
			}

			void GLDevice::uniformDouble34(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const
			{
				glUniformMatrix3x4dv(location, count, transpose, values);
			}

			void GLDevice::uniformDouble42(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const
			{
				glUniformMatrix4x2dv(location, count, transpose, values);
			}

			void GLDevice::uniformDouble43(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const
			{
				glUniformMatrix4x3dv(location, count, transpose, values);
			}

			void GLDevice::uniformDouble44(GLint location, GLsizei count, GLboolean transpose, const GLdouble* values) const
			{
				glUniformMatrix4dv(location, count, transpose, values);
			}

			void GLDevice::defineTexture2DParamInt(GLenum param, GLint value) const
			{
				glTexParameteri(GL_TEXTURE_2D, param, value);
			}

			void GLDevice::generateTexture2DMipmap() const
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}

			void GLDevice::enable(GLenum cap) const
			{
				glEnable(cap);
			}

			// =============================== WARNING: can cause performance issues =============================== //
			// ===================================================================================================== //

			GLVertexBufferHandle GLDevice::getCurrentVertexBuffer() const
			{
				GLVertexBufferHandle result;
				glGetIntegerv(GL_ARRAY_BUFFER_BINDING, (GLint*)&result.handleGL);

				return result;
			}

			GLIndexBufferHandle GLDevice::getCurrentIndexBuffer() const
			{
				GLIndexBufferHandle result;
				glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, (GLint*)&result.handleGL);

				return result;
			}

			GLVertexArrayHandle GLDevice::getCurrentVertexArray() const
			{
				GLVertexArrayHandle result;
				glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint*)&result.handleGL);
	
				return result;
			}

			GLShaderCompilationStatus GLDevice::getShaderCompilationStatus(GLShaderHandle shader) const
			{
				GLint isCompiled = 0;
				glGetShaderiv(shader.handleGL, GL_COMPILE_STATUS, &isCompiled);
				
				GLShaderCompilationStatus result;
				result.isCompiled = isCompiled != GL_FALSE;
				
				if (isCompiled == false) {
					// The maxLength includes the NULL character
					GLint maxLength = 0;
					glGetShaderiv(shader.handleGL, GL_INFO_LOG_LENGTH, &maxLength);

					std::string string;
					string.resize(maxLength);

					glGetShaderInfoLog(shader.handleGL, maxLength, &maxLength, &string[0]);

					result.infoLog = string;
				} else {
					result.infoLog = "Shader compilation succeded";
				}

				return result;
			}
		}
	}
}
