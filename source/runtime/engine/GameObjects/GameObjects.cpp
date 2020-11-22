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

		SE::core::ecs::Entity createCameraEntity(TransformComponent* transform, CameraComponent* camera)
		{
			SE::core::ecs::Entity entity;
			entity.addComponent<TransformComponent>(transform);
			entity.addComponent<CameraComponent>(camera);

			return entity;
		}

		SE::core::ecs::Entity createLightEntity(TransformComponent* transform, LightComponent* light)
		{
			SE::core::ecs::Entity entity;
			entity.addComponent<TransformComponent>(transform);
			entity.addComponent<LightComponent>(light);

			return entity;
		}
	}
}