#ifndef __LIGHTINGSHADERWITHSHADOWS_H__
#define __LIGHTINGSHADERWITHSHADOWS_H__

#include <Shader/ShaderResource.h>
#include <FileSystem/File.h>
#include <ShaderBlocks.h>

namespace SE
{
	namespace engine
	{
		namespace resources
		{
			class LightingShaderWithShadows : public SE::resource::Shader
			{
				typedef SE::resource::Shader				Super;
				typedef SE::platform::filesystem::OsFile	OsFile;

			public:
				LightingShaderWithShadows(OsFile* vertexFile, OsFile* fragmentFile)
					: Super()
				{
					this->setVertexSourceFromFile(vertexFile);
					this->setFragmentSourceFromFile(fragmentFile);

					// view constant definition setup
					SE::resource::Shader::ConstantDefinition viewConstData;
					viewConstData.name = "VIEW";
					viewConstData.size = sizeof(SE::renderer::ViewShaderBlockProxy);

					SE::resource::Shader::ConstantDefinition engineConstData;
					engineConstData.name = "ENGINE";
					engineConstData.size = sizeof(SE::renderer::EngineShaderBlockProxy);

					// material constant definition setup
					SE::resource::Shader::ConstantDefinition materialConstData;
					materialConstData.name = "MATERIAL";
					materialConstData.size = sizeof(SE::renderer::MaterialShaderBlockProxy);

					// light constant defitinition setup
					SE::resource::Shader::ConstantDefinition lightConstData;
					lightConstData.name = "LIGHT";
					lightConstData.size = sizeof(SE::renderer::LightShaderBlockProxy);

					SE::resource::Shader::ConstantDefinition shadowConstData;
					shadowConstData.name = "SHADOW";
					shadowConstData.size = sizeof(SE::renderer::ShadowShaderBlockProxy);

					this->addConstantData(viewConstData);
					this->addConstantData(engineConstData);
					this->addConstantData(materialConstData);
					this->addConstantData(lightConstData);
					this->addConstantData(shadowConstData);
				}
			};
		}
	}
}

#endif // !__LIGHTINGSHADERWITHSHADOWS_H__