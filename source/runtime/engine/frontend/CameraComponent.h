#ifndef __CAMERACOMPONENT_H__
#define __CAMERACOMPONENT_H__

#include "../../Core/math/Frustum.h"
#include "../../Core/math/Vec3.h"

#include "../../Core/EntityComponentSystem/Component.h"
//#include "../../Renderer/ShaderBlocks.h"

namespace SE
{
	namespace engine
	{
		class CameraComponent : public SE::core::ecs::Component
		{
			typedef SE::core::ecs::Component				Super;
			typedef SE::core::math::Frustum<float>			FloatFrustum;
			typedef SE::core::math::Vec3<float>				Rgb;
			//typedef SE::renderer::ViewShaderBlockProxy			ViewShaderBlockProxy;


		public:
			//const ViewShaderBlockProxy* getProxy(StaticMeshComponent* staticMesh)
			//{
			//	SE::core::math::Mat4<float> modelMatrix = SE::core::math::Mat4<float>::makeIdentity();
			//	SE::core::math::Mat4<float> viewMatrix = SE::core::math::Mat4<float>::makeIdentity();

			//	if (staticMesh->getContainer()->hasComponent<TransformComponent>()) {
			//		modelMatrix = staticMesh->getContainer()->getComponent<TransformComponent>()->getLocalToWorld();
			//	}

			//	if (getContainer()->hasComponent<TransformComponent>()) {
			//		viewMatrix = getContainer()->getComponent<TransformComponent>()->getLocalToWorld();
			//	}

			//	mViewBlockProxy.mvpMatrix = frustum.toMat4() * viewMatrix * modelMatrix;
			//	return &mViewBlockProxy;
			//}

		private:
			//ViewShaderBlockProxy		mViewBlockProxy;

		public:
			FloatFrustum				frustum;
			Rgb							backgroundColor;

		};
	}
}


#endif // !__CAMERACOMPONENT_H__