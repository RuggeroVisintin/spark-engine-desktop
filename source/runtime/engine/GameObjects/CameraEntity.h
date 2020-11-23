#ifndef __CAMERAENTITY_H__
#define __CAMERAENTITY_H__

#include <EntityComponentSystem/Entity.h>
#include "../frontend/CameraComponent.h"
#include "../Transform/TransformComponent.h";

namespace SE 
{
	namespace engine
	{
		class CameraEntity : public SE::core::ecs::Entity {
			typedef SE::core::ecs::Entity super;

		public:
			CameraEntity()
				: super()
			{
				super::addComponent<CameraComponent>(&this->camera);
				super::addComponent<TransformComponent>(&this->transform);

				this->camera.frustum = SE::core::math::Frustum<float>::createPerspective(SE::core::math::toRadians<float>(60.0f), 1360.0f / 768.0f, 0.1f, 1000.0f);
			}

			~CameraEntity()
			{
			}

		public:
			CameraComponent		camera;
			TransformComponent	transform;
		};
	}
}

#endif // !__CAMERAENTITY_H__