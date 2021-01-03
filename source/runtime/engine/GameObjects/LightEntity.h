#ifndef __LIGHTENTITY_H__
#define __LIGHTENTITY_H__

#include <EntityComponentSystem/Entity.h>
#include "../frontend/LightComponent.h";
#include "../Transform/TransformComponent.h";

namespace SE
{
	namespace engine
	{
		class LightEntity : public SE::core::ecs::Entity {
			typedef SE::core::ecs::Entity super;

		public:
			LightEntity()
				: super()
			{
				super::addComponent<LightComponent>(&this->light);
				super::addComponent<TransformComponent>(&this->transform);
			}

			~LightEntity()
			{
			}

		public:
			LightComponent		light;
			TransformComponent	transform;
		};
	}
}


#endif // !__LIGHTENTITY_H__