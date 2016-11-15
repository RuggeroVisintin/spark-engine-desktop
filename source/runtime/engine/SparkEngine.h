#ifndef __SPARKENGINE_H__
#define __SPARKENGINE_H__

#include <string>

#include "../Platform/FileSystem/FileSystem.h"

#include "frontend\RenderSystem.h"

#include "../Resource/ResourceManager.h"
#include "../Resource/Mesh/MeshResource.h"
#include "../Resource/Mesh/MeshLoader.h"
#include "../Resource/Shader/ShaderResource.h"
#include "../Resource/Shader/ShaderLoader.h"

#include "../Renderer/Renderer.h"

namespace SE
{
	namespace engine
	{
		struct EnginePathsConfig
		{
			std::string		rootPath;

			std::string		meshesFolder;
			std::string		meshesKey;

			std::string		shadersFolder;
			std::string		shadersKey;
		};

		class SparkEngine
		{
			typedef SE::resource::Mesh							Mesh;
			typedef SE::resource::Shader						Shader;

			typedef SE::resource::ResourceManager<Mesh>			MeshManager;
			typedef SE::resource::ResourceManager<Shader>		ShaderManager;

			typedef SE::resource::MeshLoader					MeshLoader;
			typedef SE::resource::ShaderLoader					ShaderLoader;

			typedef SE::platform::filesystem::OsFileSystem		FileSystem;
			typedef SE::platform::backend::GLDevice				GLDevice;

		public:
			SparkEngine(GLDevice* gfx, EnginePathsConfig enginePaths);

		public:
			//void				initialize();
			//void				initialize(GLDevice* gfx, EnginePathsConfig enginePaths);

			void				update(SE::platform::backend::GLContext& context);
			/*void				shutdown();*/							

		private:
			EnginePathsConfig	mEnginePaths;

		public:
			FileSystem			fileSystem;

			RenderSystem		renderSystem;
			Renderer			renderer;

			MeshManager			meshManager;
			MeshLoader			meshLaoder;

			ShaderManager		shaderManager;
			ShaderLoader		shaderLoader;

			bool				depthTest;
		};
	}
}

#endif //!__SPARKENGINE_H__