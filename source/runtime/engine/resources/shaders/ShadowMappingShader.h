#ifndef __SHADOWMAPPINGSHADER_H__
#define __SHADOWMAPPINGSHADER_H__

#include <Shader/ShaderResource.h>
#include <FileSystem/File.h>
#include <ShaderBlocks.h>

namespace SE
{
	namespace engine
	{
		namespace resources
		{
			class ShadowMappingShader : public SE::resource::Shader
			{
				typedef SE::resource::Shader				Super;
				typedef SE::platform::filesystem::OsFile	OsFile;

			public:
				ShadowMappingShader(OsFile* vertexFile, OsFile* fragmentFile)
					: Super()
				{
					this->setVertexSourceFromFile(vertexFile);
					this->setFragmentSourceFromFile(fragmentFile);

					SE::resource::Shader::ConstantDefinition shadowConstData;
					shadowConstData.name = "SHADOW";
					shadowConstData.size = sizeof(SE::renderer::ShadowShaderBlockProxy);

					this->addConstantData(shadowConstData);
				}
			};
		}
	}
}

#endif // !__SHADOWMAPPINGSHADER_H__