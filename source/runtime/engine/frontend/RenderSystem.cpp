#include "RenderSystem.h"

#include "../Transform/TransformComponent.h"
#include "../Frontend/MaterialComponent.h"
#include "../../Core/EntityComponentSystem/Entity.h"

#include "../../Renderer/ShaderBlocks.h"

namespace SE
{
	namespace engine
	{
		void RenderSystem::registerComponent(StaticMeshComponent* component)
		{
			mStaticMeshes.push_back(component);
		}

		void RenderSystem::registerComponent(CameraComponent* component)
		{
			mCameras.push_back(component);
		}

		void RenderSystem::registerComponent(LightComponent* component)
		{
			mLights.push_back(component);
		}

		void RenderSystem::unregisterComponent(unsigned int uuid)
		{
			for (std::vector<StaticMeshComponent*>::const_iterator it = mStaticMeshes.begin();
				it != mStaticMeshes.end(); it++)
			{
				if ((*it)->getUuid() == uuid) {
					mStaticMeshes.erase(it);
					return;
				}
			}

			for (std::vector<CameraComponent*>::const_iterator it = mCameras.begin();
				it != mCameras.end(); it++)
			{
				if ((*it)->getUuid() == uuid) {
					mCameras.erase(it);
					return;
				}
			}

			for (std::vector<LightComponent*>::const_iterator it = mLights.begin();
				it != mLights.end(); it++)
			{
				if ((*it)->getUuid() == uuid) {
					mLights.erase(it);
					return;
				}
			}
		}

		void RenderSystem::update(const float& deltaTime)
		{
			mTotalDeltaTime += deltaTime;

			for (std::vector<CameraComponent*>::const_iterator camera = mCameras.begin();
				camera != mCameras.end(); camera++)
			{
				SE::core::math::Mat4<float> projection = (*camera)->frustum.toMat4();
				SE::core::math::Mat4<float> view = (*camera)->getContainer()->getComponent<SE::engine::TransformComponent>()->getLocalToWorld();

				// disable additive blending for the first pass
				this->toggleAdditiveBlending(false);

				for (std::vector<LightComponent*>::const_iterator light = mLights.begin();
					light != mLights.end(); light++)
				{	
					this->shadowMappingPass(**light);

					this->clearBuffers(**camera);
					this->useShader(this->forwardLightingShader);

					for (std::vector<StaticMeshComponent*>::const_iterator mesh = mStaticMeshes.begin();
						mesh != mStaticMeshes.end(); mesh++)
					{
						if ((*mesh)->doRendering) {
							// view and material need to change only once per mesh
							/*SE::core::math::Mat4<float> projection = (*light)->getShadowProjection().toMat4();
							SE::core::math::Mat4<float> view = (*light)->getContainer()->getComponent<SE::engine::TransformComponent>()->getLocalToWorld();*/


							SE::core::ecs::Entity* entity = (*mesh)->getContainer();

							this->viewProxySetup(projection, view, *entity);
							this->engineProxySetup();
							this->materialSetup(*entity);

							if ((*light)->doRendering) {
								// enable additive blending after the first pass
								if (light != mLights.begin()) {
									this->toggleAdditiveBlending(true);
								}

								this->lightSetup(**light, (*mesh)->getContainer()->getComponent<SE::engine::TransformComponent>()->transform.getTransformMatrix());

								command::UseTexture* useTexture = mRenderer->pushRenderCommand<command::UseTexture>();
								useTexture->textureHandle = mShadowBuffer.getTextureHandle();
								useTexture->textureBinding = 0;
								useTexture->shaderHandle = this->shadowMappingShader.getShaderProgramHandle();

								this->drawCall(**mesh);
							}
						}
					}
				}
			}
		}

		void RenderSystem::toggleAdditiveBlending(const bool& status) const
		{
			// disable additive blending for the first pass
			command::EnableAdditiveBlending* enableBlendingCommand = mRenderer->pushRenderCommand<command::EnableAdditiveBlending>();
			enableBlendingCommand->bAdditiveBlending = status;

			if (status == true)
			{
				enableBlendingCommand->blendingType = BlendingType::BT_Additive;
			}
		}

		void RenderSystem::clearBuffers(const CameraComponent& camera) const
		{
			command::ClearBuffers* clearBuffersCommand = mRenderer->pushRenderCommand<command::ClearBuffers>();
			clearBuffersCommand->bColorBuffer = true;
			clearBuffersCommand->bDepthBuffer = true;

			clearBuffersCommand->clearColor[0] = camera.backgroundColor.getX();
			clearBuffersCommand->clearColor[1] = camera.backgroundColor.getY();
			clearBuffersCommand->clearColor[2] = camera.backgroundColor.getZ();
			clearBuffersCommand->clearColor[3] = 1.0f;
		}

		void RenderSystem::useShader(const Shader& shader) const
		{
			command::UseShaderProgram* useShaderCommand = mRenderer->pushRenderCommand<command::UseShaderProgram>();
			useShaderCommand->shaderProgram = shader.getShaderProgramHandle();
		}

		void RenderSystem::drawCall(const SE::engine::StaticMeshComponent& mesh) const
		{
			command::DrawIndexed* command = mRenderer->pushRenderCommand<command::DrawIndexed>();
			command->indexBuffer = mMeshManager->getResource(mesh.getMesh())->getIndexBuffer();
			command->vertexBuffer = mMeshManager->getResource(mesh.getMesh())->getVertexBuffer();
			command->indicesCount = mMeshManager->getResource(mesh.getMesh())->getIndicesCount();
			command->indicesOffset = 0;
		}

		void RenderSystem::shadowMappingPass(const LightComponent& light) const
		{
			this->mShadowBuffer.startFrame();

			command::ClearBuffers* clearBuffersCommand = mRenderer->pushRenderCommand<command::ClearBuffers>();
			clearBuffersCommand->bColorBuffer = false;
			clearBuffersCommand->bDepthBuffer = true;

			this->useShader(this->shadowMappingShader);

			for (std::vector<StaticMeshComponent*>::const_iterator mesh = mStaticMeshes.begin();
				mesh != mStaticMeshes.end(); mesh++)
			{
				if ((*mesh)->doRendering) {
					// view and material need to change only once per mesh
					SE::core::ecs::Entity* entity = (*mesh)->getContainer();
					SE::core::math::Mat4<float> projection = light.getShadowProjection().toMat4();
					SE::core::math::Mat4<float> model = entity->getComponent<SE::engine::TransformComponent>()->transform.getTransformMatrix();
					SE::core::math::Mat4<float> view = light.getContainer()->getComponent<TransformComponent>()->getLocalToWorld();
					SE::core::math::Mat4<float> shadowMatrix = projection * view * model;

					SE::renderer::ShadowShaderBlockProxy* shadowProxy = new SE::renderer::ShadowShaderBlockProxy();
					shadowProxy->shadowMatrix = shadowMatrix;

					command::CopyConstantBuffer* shadowConstBuffer = mRenderer->pushRenderCommand<command::CopyConstantBuffer>();
					shadowConstBuffer->bufferSize = sizeof(SE::renderer::ShadowShaderBlockProxy);
					shadowConstBuffer->bufferData = shadowProxy;
					shadowConstBuffer->constantBuffer = shadowMappingShader.getConstantDefinition("SHADOW").handle;

					this->drawCall(**mesh);
				}
			}

			this->mShadowBuffer.endFrame();
		}

		void RenderSystem::viewProxySetup(const Mat4F& projection, const Mat4F& view, const SE::core::ecs::Entity& entity) const
		{
			SE::renderer::ViewShaderBlockProxy* viewProxy = new SE::renderer::ViewShaderBlockProxy();
			viewProxy->mvpMatrix = projection * (view * entity.getComponent<SE::engine::TransformComponent>()->transform.getTransformMatrix());
			viewProxy->normalMatrix = (entity.getComponent<SE::engine::TransformComponent>()->transform.getTransformMatrix() * view).getInverse().getTransposed();
			viewProxy->modelViewMatrix = view * entity.getComponent<SE::engine::TransformComponent>()->transform.getTransformMatrix();
			viewProxy->viewMatrix = view;

			command::CopyConstantBuffer* viewConstBuffer = mRenderer->pushRenderCommand<command::CopyConstantBuffer>();
			viewConstBuffer->bufferSize = sizeof(SE::renderer::ViewShaderBlockProxy);
			viewConstBuffer->bufferData = viewProxy;
			viewConstBuffer->constantBuffer = forwardLightingShader.getConstantDefinition("VIEW").handle;
		}

		void RenderSystem::engineProxySetup() const
		{
			SE::renderer::EngineShaderBlockProxy* engineProxy = new SE::renderer::EngineShaderBlockProxy();
			engineProxy->deltaTime = mTotalDeltaTime;

			command::CopyConstantBuffer* engineConstBuffer = mRenderer->pushRenderCommand<command::CopyConstantBuffer>();
			engineConstBuffer->bufferSize = sizeof(SE::renderer::EngineShaderBlockProxy);
			engineConstBuffer->bufferData = engineProxy;
			engineConstBuffer->constantBuffer = forwardLightingShader.getConstantDefinition("ENGINE").handle;
		}

		void RenderSystem::materialSetup(const SE::core::ecs::Entity& entity) const
		{
			SE::renderer::MaterialShaderBlockProxy* materialProxy = new SE::renderer::MaterialShaderBlockProxy();

			if (entity.hasComponent<SE::engine::MaterialComponent>() && entity.getComponent<SE::engine::MaterialComponent>()->doRendering) {
				SE::engine::MaterialComponent* currentMaterial = entity.getComponent<SE::engine::MaterialComponent>();

				materialProxy->albedoColor = currentMaterial->mMaterial.params.diffuseColor;
				materialProxy->roughness = currentMaterial->mMaterial.params.roughness;
				materialProxy->reflectance = currentMaterial->mMaterial.params.specularity;
				materialProxy->metalness = currentMaterial->mMaterial.params.metalness;
			}
			else {
				materialProxy->albedoColor = defaultMaterial.params.diffuseColor;
				materialProxy->roughness = defaultMaterial.params.roughness;
				materialProxy->reflectance = defaultMaterial.params.specularity;
				materialProxy->metalness = defaultMaterial.params.metalness;
			}

			command::CopyConstantBuffer* materialConstBuffer = mRenderer->pushRenderCommand<command::CopyConstantBuffer>();
			materialConstBuffer->bufferSize = sizeof(SE::renderer::MaterialShaderBlockProxy);
			materialConstBuffer->bufferData = materialProxy;
			materialConstBuffer->constantBuffer = forwardLightingShader.getConstantDefinition("MATERIAL").handle;
		}

		void RenderSystem::lightSetup(const LightComponent& light, const Mat4F& modelMatrix) const
		{
			SE::core::math::Frustum<float> lightFurstum = light.getShadowProjection();
			SE::core::math::Mat4<float> scaleBiasMatrix =
				SE::core::math::Mat4<float>(
					0.5f, 0.0f, 0.0f, 0.0f,
					0.0F, 0.5f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.5f, 0.0f,
					0.5f, 0.5f, 0.5f, 1.0f);
			SE::core::math::Mat4<float> shadowMatrix = scaleBiasMatrix * lightFurstum.toMat4() * light.getContainer()->getComponent<TransformComponent>()->transform.getTransformMatrix() * modelMatrix;

			SE::renderer::LightShaderBlockProxy* lightProxy = new SE::renderer::LightShaderBlockProxy();
			lightProxy->position = light.getContainer()->getComponent<TransformComponent>()->transform.position;
			lightProxy->color = light.color;
			lightProxy->direction = light.getContainer()->getComponent<TransformComponent>()->transform.rotation.rotateVector(SE::core::math::Vec3<float>::FORWARD_VECTOR);
			lightProxy->power = light.power;
			lightProxy->shadowMatrix = shadowMatrix;
			lightProxy->ambientPower = light.ambientPower;

			// TODO: pass shadow texture to shader

			command::CopyConstantBuffer* lightConstBuffer = mRenderer->pushRenderCommand<command::CopyConstantBuffer>();
			lightConstBuffer->bufferSize = sizeof(SE::renderer::LightShaderBlockProxy);
			lightConstBuffer->bufferData = lightProxy;
			lightConstBuffer->constantBuffer = forwardLightingShader.getConstantDefinition("LIGHT").handle;

		
		}
	}
}