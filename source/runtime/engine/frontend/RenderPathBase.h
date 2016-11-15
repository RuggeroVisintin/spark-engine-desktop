#ifndef __RENDERPATHBASE_H__
#define __RENDERPATHBASE_H__

#include "../../Resource/ResourceManager.h"
#include "../../Resource/Mesh/MeshResource.h"

#include "../../Renderer/Renderer.h"

namespace SE
{
	namespace engine
	{
		class RenderPathBase
		{
			typedef SE::resource::Mesh					Mesh;
			typedef SE::resource::ResourceManager<Mesh> MeshManager;

		private:
			Renderer*								mRenderer;
			MeshManager*							mMeshManager;
		};
	}
}

#endif // !__RENDERPATHBASE_H__