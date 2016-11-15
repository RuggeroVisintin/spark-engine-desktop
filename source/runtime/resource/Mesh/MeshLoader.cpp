#include "MeshLoader.h"
#include <Parsers/spk/SpkParser.h>

namespace SE
{
	namespace resource
	{
		Mesh MeshLoader::loadResource(SE::platform::backend::GLDevice* gfx, const std::string& filePath)
		{
			Mesh result;

			SE::platform::filesystem::OsFile* meshFile	= mFileSystem->openFileRead(filePath, mSearchPath);

			SE::core::parser::binary::spk::SpkParser	spkParser;
			SE::core::parser::binary::spk::SpkMesh		spkMesh;

			spkParser.readMesh(spkMesh, meshFile);
			result.deSerialize(spkMesh);
			result.initGpuResources(gfx);

			return result;
		}

		void MeshLoader::loadResource(SE::platform::backend::GLDevice* gfx, Mesh& mesh, const std::string& filePath)
		{
			SE::platform::filesystem::OsFile* meshFile = mFileSystem->openFileRead(filePath, mSearchPath);

			SE::core::parser::binary::spk::SpkParser	spkParser;
			SE::core::parser::binary::spk::SpkMesh		spkMesh;

			spkParser.readMesh(spkMesh, meshFile);
			mesh.deSerialize(spkMesh);
			mesh.initGpuResources(gfx);
		}
	}
}