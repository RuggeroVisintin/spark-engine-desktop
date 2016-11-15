#ifndef __SHADERRESOURCE_H__
#define __SHADERRESOURCE_H__

#include <vector>

#include "../Resource.h"

#include <GFX/OpenGL/GLTypes.h>
#include <GFX/OpenGL/GLDevice.h>
#include <SmartPtrs/SharedPtr.h>

#include <FileSystem/File.h>
#include <PlatformUtils.h>

namespace SE
{
	namespace resource
	{
		class Shader : public IResource
		{
			typedef SE::platform::backend::GLUniformBufferHandle UniformBufferHandle;
			typedef SE::platform::backend::GLShaderProgramHandle ShaderProgramHandle;

		public:
			struct ConstantDefinition
			{
				std::string				name;
				size_t					size;
				UniformBufferHandle		handle;
			};

		public:
			Shader() {}
			~Shader() {}

		public:
			void setVertexSourceFromFile(SE::platform::filesystem::OsFile* vertexFile);
			void setFragmentSourceFromFile(SE::platform::filesystem::OsFile* fragmentFile);

			void addConstantData(ConstantDefinition constantData)
			{
				mConstantDefinitions.push_back(constantData);
			}

			void initGpuResources(const SE::platform::backend::GLDevice* graphicsDevice);

			void setVertexShaderSource(const std::string& vertexShaderSource)
			{
				mVertexShaderSource = vertexShaderSource;
			}

			void setFragmentShaderSource(const std::string& fragmentShaderSource)
			{
				mFragmentShaderSource = fragmentShaderSource;
			}

			const ShaderProgramHandle&	getShaderProgramHandle() const
			{
				return mShaderProgramHandle;
			}

			ConstantDefinition getConstantDefinition(const std::string& name) const
			{
				std::vector<ConstantDefinition>::const_iterator it;
				for (it = mConstantDefinitions.cbegin(); it != mConstantDefinitions.cend(); it++) {
					if (it->name == name) {
						return (*it);
					}
				}

				return ConstantDefinition();
			}

		private:
			std::string							mVertexShaderSource;
			std::string							mFragmentShaderSource;

			std::vector<ConstantDefinition>		mConstantDefinitions;
			ShaderProgramHandle					mShaderProgramHandle;

		};

		typedef SE::core::memory::SharedPtr<Shader>		PShaderResource;
	}
}

#endif // !__SHADERRESOURCE_H__