#include "SparkEngine.h"

#include <ShaderBlocks.h>

#include "resources/shaders/ShadowMappingShader.h"
#include "resources/shaders/LightingShaderBase.h"

namespace SE
{
	namespace engine
	{
		SparkEngine::SparkEngine(GLDevice* gfx, EnginePathsConfig enginePaths)
			: renderer(gfx, 1360, 768)
			, mEnginePaths(enginePaths)
			, fileSystem(mEnginePaths.rootPath)
			, meshLaoder(&fileSystem, mEnginePaths.meshesKey)
			, meshManager(&meshLaoder, gfx)
			, shaderLoader(&fileSystem, mEnginePaths.shadersKey)
			, shaderManager(&shaderLoader, gfx)
			, renderSystem(&renderer, &meshManager)
			, controlSystem(&inputDisptacher)
		{
			SPARK_ASSERT(gfx != nullptr, "SparkEngine::SparkEngine passed @param gfx is null");

			SE::platform::filesystem::SearchPath_s meshSearchPath;
			meshSearchPath.mAccesRight = meshSearchPath.AR_READONLY;
			meshSearchPath.mRawPath = mEnginePaths.meshesFolder;

			SE::platform::filesystem::SearchPath_s shaderSearchPath;
			shaderSearchPath.mAccesRight = shaderSearchPath.AR_READONLY;
			shaderSearchPath.mRawPath = mEnginePaths.shadersFolder;

			SE::platform::filesystem::SearchPath_s texturesSearchPath;
			texturesSearchPath.mAccesRight = texturesSearchPath.AR_READONLY;
			texturesSearchPath.mRawPath = mEnginePaths.texturesFolder;

			fileSystem.addSearchPath(mEnginePaths.meshesKey, meshSearchPath);
			fileSystem.addSearchPath(mEnginePaths.shadersKey, shaderSearchPath);
			//fileSystem.addSearchPath(mEnginePaths.texturesKey, texturesSearchPath);

			this->initShaders(gfx);

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_FRAMEBUFFER_SRGB); // keep until render to texture is ready then switch to gamma correction in shader
		}

		void SparkEngine::update(SE::platform::backend::GLContext& context, const float& deltaTime)
		{
			controlSystem.update();
			renderSystem.update(deltaTime);
			renderer.endFrame(context);
		}

		void SparkEngine::initShaders(GLDevice* gfx)
		{
			this->initShader<SE::engine::resources::ShadowMappingShader>(gfx, "Build/fwd_shadowmapping", SE::engine::ShaderBits::ShadowMapping);
			this->initShader<SE::engine::resources::LightingShaderBase>(gfx, "Build/fwd_directional_shadow", SE::engine::ShaderBits::DirectionalLight | SE::engine::ShaderBits::Shadowing);
			
			// TODO: understand how to adapt shader
			//this->initShader<SE::engine::resources::LightingShaderBase>(gfx, "Build/fwd_directional_noShadow", SE::engine::ShaderBits::DirectionalLight);


			/*OsFile* tempVertexFile = fileSystem.openFileRead("Build/fwd_shadowmapping.vertex.glsl", mEnginePaths.shadersKey);
			OsFile* tempFragmentFile = fileSystem.openFileRead("Build/fwd_shadowmapping.fragment.glsl", mEnginePaths.shadersKey);

			SE::resource::Shader tempShader = SE::engine::resources::ShadowMappingShader(tempVertexFile, tempFragmentFile);
			tempShader.initGpuResources(gfx);
			renderSystem.registerShader(SE::engine::ShaderBits::ShadowMapping, tempShader);

			fileSystem.closeFile(tempVertexFile);
			fileSystem.closeFile(tempFragmentFile);

			tempVertexFile = fileSystem.openFileRead("Build/fwd_directional_shadow.vertex.glsl", mEnginePaths.shadersKey);
			tempFragmentFile = fileSystem.openFileRead("Build/fwd_directional_shadow.fragment.glsl", mEnginePaths.shadersKey);

			tempShader = SE::engine::resources::LightingShaderBase(tempVertexFile, tempFragmentFile);
			tempShader.initGpuResources(gfx);
			renderSystem.registerShader(SE::engine::ShaderBits::DirectionalLight | SE::engine::ShaderBits::Shadowing, tempShader);

			fileSystem.closeFile(tempVertexFile);
			fileSystem.closeFile(tempFragmentFile);*/
		}

		template <class T> void SparkEngine::initShader(GLDevice* gfx, const std::string& shaderName, unsigned int shaderBits)
		{
			OsFile* tempVertexFile = fileSystem.openFileRead(shaderName + ".vertex.glsl", mEnginePaths.shadersKey);
			OsFile* tempFragmentFile = fileSystem.openFileRead(shaderName + ".fragment.glsl", mEnginePaths.shadersKey);

			SE::resource::Shader tempShader = T(tempVertexFile, tempFragmentFile);
			tempShader.initGpuResources(gfx);
			renderSystem.registerShader(shaderBits, tempShader);

			fileSystem.closeFile(tempVertexFile);
			fileSystem.closeFile(tempFragmentFile);
		}
	}
}