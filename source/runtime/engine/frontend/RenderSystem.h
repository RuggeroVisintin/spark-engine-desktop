#ifndef __RENDERSYSTEM_H__
#define __RENDERSYSTEM_H__

#include <vector>
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

		public:
			RenderSystem(Renderer* renderer, MeshManager* meshManager)
				: mRenderer(renderer)
				, mMeshManager(meshManager)
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

			void									unregisterComponent(unsigned int uuid);
			void									update(const float& deltaTime);

		private:
			Renderer*								mRenderer;
			MeshManager*							mMeshManager;

			std::vector<StaticMeshComponent*>		mStaticMeshes;
			std::vector<CameraComponent*>			mCameras;	
			std::vector<LightComponent*>			mLights;

			float									mTotalDeltaTime;

		public:
			// not found has to be in resource manager
			Material								notFoundMaterial;
			Material								defaultMaterial;

			/*Shader								forwardBasePassShader;*/
			Shader									forwardLightingShader;

			/*std::string							cameraConstantName;	*/		

		};
	}	
}

#endif // !__RENDERSYSTEM_H__