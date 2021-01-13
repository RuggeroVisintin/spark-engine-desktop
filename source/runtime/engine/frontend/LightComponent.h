#ifndef __LIGHTCOMPONENT_H__
#define __LIGHTCOMPONENT_H__

#include "../../Core/EntityComponentSystem/Component.h"
#include "../../Core/math/Vec3.h"
#include <math/Frustum.h>

namespace SE
{
	namespace engine
	{
		enum LightType {
			Directional = 0,
			Point = 1
		};

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

			SE::core::math::Frustum<float> getShadowProjection() const
			{
				return SE::core::math::Frustum<float>::createOrtho(-1, 1, -1, 1, 0.1f, 100.0f);
			}
			
		public:
			bool										doRendering;

			Rgb											color;
			Rgb											ambientColor;

			float										power;
			float										ambientPower;

			LightType									type;
		};
	}
}

#endif // !__LIGHTCOMPONENT_H__