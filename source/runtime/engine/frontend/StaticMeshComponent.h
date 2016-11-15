#ifndef __STATICMESHCOMPONENT_H__
#define __STATICMESHCOMPONENT_H__

#include "../../Core/EntityComponentSystem/Component.h"
#include "../../Resource/Mesh/MeshResource.h"
#include "../../Resource/Material/MaterialResource.h"

namespace SE
{
	namespace engine
	{
			class StaticMeshComponent : public SE::core::ecs::Component
			{
				friend class										RenderSystem;

				typedef SE::core::ecs::Component					Super;		
				typedef SE::resource::ResourceHandle				MeshResource;

			public:
				StaticMeshComponent(MeshResource mesh)
					: Super()
					, mMesh(mesh)
				{
					doRendering = true;
				}

			public:	
				StaticMeshComponent&		setMesh(const MeshResource& mesh)
				{
					mMesh = mesh;
					return *this;
				}

				MeshResource				getMesh() const
				{
					return mMesh;
				}

			public:
				bool						doRendering;

			private:
				MeshResource				mMesh;

			};		
	}
}

#endif // !__STATICMESHCOMPONENT_H__