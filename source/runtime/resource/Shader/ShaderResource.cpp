#include "ShaderResource.h"
#include <Assertion/Assert.h>

namespace SE
{
	namespace resource
	{
		void Shader::setVertexSourceFromFile(SE::platform::filesystem::OsFile* vertexFile)
		{
			mVertexShaderSource.reserve(vertexFile->getSize());
			mVertexShaderSource.resize(vertexFile->getSize());
			vertexFile->read(&mVertexShaderSource[0], vertexFile->getSize());
		}

		void Shader::setFragmentSourceFromFile(SE::platform::filesystem::OsFile* fragmentFile)
		{
			mFragmentShaderSource.reserve(fragmentFile->getSize());
			mFragmentShaderSource.resize(fragmentFile->getSize());
			fragmentFile->read(&mFragmentShaderSource[0], fragmentFile->getSize());
		}

		void Shader::initGpuResources(const SE::platform::backend::GLDevice* graphicsDevice)
		{
			SPARK_ASSERT(!mVertexShaderSource.empty(), "Shader::sendGpuData - @member Shader::vertexShaderSource - must be filled");
			SPARK_ASSERT(!mFragmentShaderSource.empty(), "Shader::sendGpuData - @member Shader::fragmentShaderSource - must be filled");

			const GLchar* toPass;

			SE::platform::backend::GLShaderHandle vertexShader = graphicsDevice->createVertexShader();
			toPass = (const GLchar*)(mVertexShaderSource.data());
			graphicsDevice->setShaderSource(vertexShader, 1, &toPass, 0);
			graphicsDevice->compileShader(vertexShader);
			
			SE::platform::backend::GLShaderCompilationStatus status = graphicsDevice->getShaderCompilationStatus(vertexShader);
			SPARK_ASSERT(status.isCompiled, status.infoLog.c_str());


			SE::platform::backend::GLShaderHandle fragmentShader = graphicsDevice->createFragmentShader();
			toPass = (const GLchar*)(mFragmentShaderSource.data());
			graphicsDevice->setShaderSource(fragmentShader, 1, &toPass, 0);
			graphicsDevice->compileShader(fragmentShader);

			status = graphicsDevice->getShaderCompilationStatus(fragmentShader);
			SPARK_ASSERT(status.isCompiled, status.infoLog.c_str());

			mShaderProgramHandle = graphicsDevice->createShaderProgram();
			graphicsDevice->attachShader(mShaderProgramHandle, vertexShader);
			graphicsDevice->attachShader(mShaderProgramHandle, fragmentShader);
			graphicsDevice->linkProgram(mShaderProgramHandle);

			graphicsDevice->destroyShader(vertexShader);
			graphicsDevice->destroyShader(fragmentShader);
			
			unsigned int location;
			unsigned int bindingPoint = 0;

			for (std::vector<ConstantDefinition>::iterator it = mConstantDefinitions.begin(); it != mConstantDefinitions.end(); it++) {
				
				location = graphicsDevice->getUniformBufferLocation(mShaderProgramHandle, it->name.c_str());
				SPARK_ASSERT(location != GL_INVALID_INDEX, "Shader::initGpuResources error while initializing constant buffers");
				graphicsDevice->setUniformBufferBinding(mShaderProgramHandle, location, bindingPoint);

				it->handle = graphicsDevice->createUniformBuffer();
				graphicsDevice->bindUniformBuffer(it->handle);
				graphicsDevice->fillUniformBuffer(it->size, 0, GL_DYNAMIC_DRAW);
				graphicsDevice->bindUniformBufferBase(bindingPoint, it->handle);
				graphicsDevice->unbindUnifromBuffer();

				// this is not the right way, work on a correct implementation
				bindingPoint++;
			}
		}

	}
}