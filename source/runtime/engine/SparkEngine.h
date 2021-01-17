#ifndef __SPARKENGINE_H__
#define __SPARKENGINE_H__

#include <string>

#include <FileSystem/FileSystem.h>

#include "frontend\RenderSystem.h"
#include "controls/ControlSystem.h"

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

			std::string		texturesFolder;
			std::string		texturesKey;
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
			typedef SE::platform::filesystem::OsFile			OsFile;
			typedef SE::platform::backend::GLDevice				GLDevice;

			typedef SE::platform::input::Dispatcher				InputDisptacher;

		public:
			SparkEngine(GLDevice* gfx, EnginePathsConfig enginePaths);

		public:
			void				init();
			//void				initialize(GLDevice* gfx, EnginePathsConfig enginePaths);

			void				update(SE::platform::backend::GLContext& context, const float& deltaTime);
			/*void				shutdown();*/		

		private:
			void				initShaders(GLDevice* gfx);

		private:
			EnginePathsConfig	mEnginePaths;

		public:
			FileSystem			fileSystem;

			RenderSystem		renderSystem;
			Renderer			renderer;

			ControlSystem		controlSystem;
			InputDisptacher		inputDisptacher;

			MeshManager			meshManager;
			MeshLoader			meshLaoder;

			ShaderManager		shaderManager;
			ShaderLoader		shaderLoader;

			bool				depthTest;
		};
	}
}

#endif //!__SPARKENGINE_H__