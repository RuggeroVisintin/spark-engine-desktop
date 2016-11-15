#include "SparkEngine.h"

#include "../Platform/Assertion/Assert.h"

namespace SE
{
	namespace engine
	{
		SparkEngine::SparkEngine(GLDevice* gfx, EnginePathsConfig enginePaths)
			: renderer(gfx)
			, mEnginePaths(enginePaths)
			, fileSystem(mEnginePaths.rootPath)
			, meshLaoder(&fileSystem, mEnginePaths.meshesKey)
			, meshManager(&meshLaoder, gfx)
			, shaderLoader(&fileSystem, mEnginePaths.shadersKey)
			, shaderManager(&shaderLoader, gfx)
			, renderSystem(&renderer, &meshManager)
		{
			// TODO: Asserts and initialization
			SPARK_ASSERT(gfx != nullptr, "SparkEngine::SparkEngine passed @param gfx is null");

			SE::platform::filesystem::SearchPath_s meshSearchPath;
			meshSearchPath.mAccesRight = meshSearchPath.AR_READONLY;
			meshSearchPath.mRawPath = mEnginePaths.meshesFolder;

			SE::platform::filesystem::SearchPath_s shaderSearchPath;
			shaderSearchPath.mAccesRight = shaderSearchPath.AR_READONLY;
			shaderSearchPath.mRawPath = mEnginePaths.shadersFolder;

			fileSystem.addSearchPath(mEnginePaths.meshesKey, meshSearchPath);
			fileSystem.addSearchPath(mEnginePaths.shadersKey, shaderSearchPath);

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_FRAMEBUFFER_SRGB);
		}

		void SparkEngine::update(SE::platform::backend::GLContext& context)
		{
			renderSystem.update();
			renderer.endFrame(context);
		}
	}
}