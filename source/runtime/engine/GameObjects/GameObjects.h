#ifndef __GAMEOBJECTS_H__
#define __GAMEOBJECTS_H__

#include "../../Core/EntityComponentSystem/Entity.h"

#include "../frontend/StaticMeshComponent.h"
#include "../Transform/TransformComponent.h"


namespace SE
{
	namespace engine
	{
		SE::core::ecs::Entity createStaticMeshEntity(TransformComponent* transform, StaticMeshComponent* staticMesh);
	}
}

#endif // !__GAMEOBJECTS_H__