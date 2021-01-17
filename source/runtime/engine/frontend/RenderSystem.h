#ifndef __RENDERSYSTEM_H__
#define __RENDERSYSTEM_H__

#include <vector>
#include <ShadowBuffer.h>

#include <PlatformUtils.h>
#include "../../Platform/Assertion/Assert.h"
#include "../../Renderer/Renderer.h"

#include "StaticMeshComponent.h"
#include "CameraComponent.h"
#include "LightComponent.h"

#include "../../Resource/Material/MaterialResource.h"
#include "../../Resource/ResourceManager.h"
#include "../../Resource/ResourceHandle.h"

namespace SE
{
	namespace engine
	{
		enum ShaderBits
		{
			// TODO:
			DirectionalLight = 0x0001,
			PointLight = 0x0002,
			SpotLight = 0x0003,
			ShadowMapping = 0x0004,
			Shadowing = 0x0005
		};

		/**
		* TODO: extend to allow the usage of different shading paths
		* @brief - RenderSystem uses forward shading for now
		*/
		class RenderSystem
		{
			typedef SE::resource::Material					Material;
			typedef SE::resource::Shader					Shader;
			typedef SE::resource::Mesh						Mesh;

			typedef SE::resource::ResourceManager<Shader>	ShaderManager;
			typedef SE::resource::ResourceManager<Mesh>		MeshManager;

			typedef SE::core::math::Mat4<float>				Mat4F;

		public:
			RenderSystem(Renderer* renderer, MeshManager* meshManager)
				: mRenderer(renderer)
				, mMeshManager(meshManager)
				, mShadowBuffer(renderer, 1024, 1024)
				, mTotalDeltaTime(0)
			{
				SPARK_ASSERT(mRenderer != nullptr, "RenderSystem::constructor - @param renderer - is null");
				SPARK_ASSERT(mMeshManager != nullptr, "RenderSystem::constructor - @param meshManager - is null");
			}

			~RenderSystem()
			{
			}

		public:
			void									registerComponent(StaticMeshComponent* component);
			void									registerComponent(CameraComponent* component);
			void									registerComponent(LightComponent* component);

			void									registerShader(unsigned int shaderId, Shader shader);

			void									unregisterComponent(unsigned int uuid);
			void									update(const float& deltaTime);

		private:
			void									toggleAdditiveBlending(const bool& status) const;
			void									clearBuffers(const CameraComponent& camera) const;
			void									useShader(const Shader& shader) const;
			void									drawCall(const SE::engine::StaticMeshComponent& mesh) const;

			void									shadowMappingPass(const LightComponent& light, const Shader& shadowMappingShader) const;

			void									viewProxySetup(const Mat4F& projection, const Mat4F& view, const SE::core::ecs::Entity& entity, const Shader& shader) const;
			void									engineProxySetup(const Shader& shader) const;
			void									materialSetup(const SE::core::ecs::Entity& entity, const Shader& shader) const;
			void									lightSetup(const LightComponent& light, const Mat4F& modelMatrix, const Shader& Shader) const;

		private:
			Renderer*								mRenderer;
			MeshManager*							mMeshManager;

			std::vector<StaticMeshComponent*>		mStaticMeshes;
			std::vector<CameraComponent*>			mCameras;	
			std::vector<LightComponent*>			mLights;

			std::map<unsigned int, Shader>			mShadersMap;

			float									mTotalDeltaTime;

			ShadowBuffer							mShadowBuffer;

		public:
			// not found has to be in resource manager
			Material								notFoundMaterial;
			Material								defaultMaterial;
		};
	}	
}

#endif // !__RENDERSYSTEM_H__