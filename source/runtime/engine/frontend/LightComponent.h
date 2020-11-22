#ifndef __LIGHTCOMPONENT_H__
#define __LIGHTCOMPONENT_H__

#include "../../Core/EntityComponentSystem/Component.h"
#include "../../Core/math/Vec3.h"

namespace SE
{
	namespace engine
	{
		class LightComponent : public SE::core::ecs::Component
		{
			friend class								RenderSystem;
			typedef SE::core::ecs::Component			Super;
			typedef SE::core::math::Vec3<float>			Rgb;

		public:
			LightComponent()
				: doRendering(true)
				, color(1.0, 1.0, 1.0)
				, ambientColor(0.0, 0.0, 0.0)
				, power(1)
				, ambientPower(0)
			{
			}
			
		public:
			bool										doRendering;

			Rgb											color;
			Rgb											ambientColor;

			float										power;
			float										ambientPower;

		};
	}
}

#endif // !__LIGHTCOMPONENT_H__