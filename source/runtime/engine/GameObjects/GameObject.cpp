#include "GameObjects.h"

namespace SE
{
	namespace engine
	{
		SE::core::ecs::Entity createStaticMeshEntity(TransformComponent* transform, StaticMeshComponent* staticMesh)
		{
			SE::core::ecs::Entity entity;
			entity.addComponent<TransformComponent>(transform);
			entity.addComponent<StaticMeshComponent>(staticMesh);

			return entity;
		}
	}
}