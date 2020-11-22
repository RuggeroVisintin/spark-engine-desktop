#ifndef __GAMEOBJECTS_H__
#define __GAMEOBJECTS_H__

#include "../../Core/EntityComponentSystem/Entity.h"

#include "../frontend/StaticMeshComponent.h"
#include "../frontend/CameraComponent.h"
#include "../frontend/LightComponent.h"
#include "../Transform/TransformComponent.h"

namespace SE
{
	namespace engine
	{
		SE::core::ecs::Entity createStaticMeshEntity(TransformComponent* transform, StaticMeshComponent* staticMesh);
		SE::core::ecs::Entity createCameraEntity(TransformComponent* transform, CameraComponent* camera);
		SE::core::ecs::Entity createLightEntity(TransformComponent* transform, LightComponent* light);
	}
}

#endif // !__GAMEOBJECTS_H__