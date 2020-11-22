#ifndef __SAHDERBLOCKS_H__
#define __SHADERBLOCKS_H__

#include "../Core/math/Vec3.h"
#include "../Core/math/Mat4.h"
#include "../Core/math/Gpu/GpuVec3.h"

namespace SE
{
	namespace renderer
	{
		// float p are padding, because of glsl implementation, have to find a better approach
		struct LightShaderBlockProxy
		{
			SE::core::math::Vec3<float>		color;
			float							power;
			SE::core::math::Vec3<float>		position;
			float							ambientPower;

			SE::core::math::GpuVec3<float>	direction;
			//SE::core::math::GpuVec3<float>	ambientColor;
		};

		struct MaterialShaderBlockProxy
		{
			SE::core::math::Vec3<float>		albedoColor;
			float roughness;
			float reflectance;
			float metalness;
		};

		struct ViewShaderBlockProxy
		{
			SE::core::math::Mat4<float>		mvpMatrix;
			SE::core::math::Mat4<float>		normalMatrix;
			SE::core::math::Mat4<float>		modelViewMatrix;
			SE::core::math::Mat4<float>		viewMatrix;
		};

		struct EngineShaderBlockProxy
		{
			float deltaTime;
		};
	}
}

#endif // !__SHADERBLOCKS_H__