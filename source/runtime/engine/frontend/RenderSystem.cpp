#include "RenderSystem.h"

#include "../Transform/TransformComponent.h"
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

		void RenderSystem::update() const
		{
			for (std::vector<CameraComponent*>::const_iterator camera = mCameras.begin();
				camera != mCameras.end(); camera++)
			{
				SE::core::math::Mat4<float> projection = (*camera)->frustum.toMat4();
				SE::core::math::Mat4<float> view = (*camera)->getContainer()->getComponent<SE::engine::TransformComponent>()->getLocalToWorld();

				// disable additive blending for the first pass
				command::EnableAdditiveBlending* disableBlendingCommand = mRenderer->pushRenderCommand<command::EnableAdditiveBlending>();
				disableBlendingCommand->bAdditiveBlending = false;

				// clear buffers
				command::ClearBuffers* clearBuffersCommand = mRenderer->pushRenderCommand<command::ClearBuffers>();
				clearBuffersCommand->bColorBuffer = true;
				clearBuffersCommand->bDepthBuffer = true;

				clearBuffersCommand->clearColor[0] = (*camera)->backgroundColor.getX();
				clearBuffersCommand->clearColor[1] = (*camera)->backgroundColor.getY();
				clearBuffersCommand->clearColor[2] = (*camera)->backgroundColor.getZ();
				clearBuffersCommand->clearColor[3] = 1.0f;

				// use forward lighting shader
				command::UseShaderProgram* useShaderCommand = mRenderer->pushRenderCommand<command::UseShaderProgram>();
				useShaderCommand->shaderProgram = forwardLightingShader.getShaderProgramHandle();

				for (std::vector<StaticMeshComponent*>::const_iterator mesh = mStaticMeshes.begin();
					mesh != mStaticMeshes.end(); mesh++)
				{
					if ((*mesh)->doRendering) {
						// view and material need to change only once per mesh
						SE::core::ecs::Entity* entity = (*mesh)->getContainer();

						// view setup
						SE::renderer::ViewShaderBlockProxy* viewProxy = new SE::renderer::ViewShaderBlockProxy();
						viewProxy->mvpMatrix = projection *  view * entity->getComponent<SE::engine::TransformComponent>()->transform.getTransformMatrix();
						viewProxy->normalMatrix = (entity->getComponent<SE::engine::TransformComponent>()->transform.getTransformMatrix() * view).getInverse().getTransposed();
						viewProxy->modelViewMatrix = view * entity->getComponent<SE::engine::TransformComponent>()->transform.getTransformMatrix();
						viewProxy->viewMatrix = view;

						command::CopyConstantBuffer* viewConstBuffer = mRenderer->pushRenderCommand<command::CopyConstantBuffer>();
						viewConstBuffer->bufferSize = sizeof(SE::renderer::ViewShaderBlockProxy);
						viewConstBuffer->bufferData = viewProxy;
						viewConstBuffer->constantBuffer = forwardLightingShader.getConstantDefinition("VIEW").handle;

						// material setup
						SE::renderer::MaterialShaderBlockProxy* materialProxy = new SE::renderer::MaterialShaderBlockProxy();
						materialProxy->albedoColor = defaultMaterial.params.diffuseColor;
						materialProxy->roughness = defaultMaterial.params.roughness;
						materialProxy->reflectance = defaultMaterial.params.specularity;
						materialProxy->metalness = defaultMaterial.params.metalness;

						command::CopyConstantBuffer* materialConstBuffer = mRenderer->pushRenderCommand<command::CopyConstantBuffer>();
						materialConstBuffer->bufferSize = sizeof(SE::renderer::MaterialShaderBlockProxy);
						materialConstBuffer->bufferData = materialProxy;
						materialConstBuffer->constantBuffer = forwardLightingShader.getConstantDefinition("MATERIAL").handle;

						for (std::vector<LightComponent*>::const_iterator light = mLights.begin();
							light != mLights.end(); light++)
						{
							if ((*light)->doRendering) {
								// enable additive blending after the first pass
								if (light != mLights.begin()) {
									command::EnableAdditiveBlending* enableBlendingCommand = mRenderer->pushRenderCommand<command::EnableAdditiveBlending>();
									enableBlendingCommand->bAdditiveBlending = true;
									enableBlendingCommand->blendingType = BlendingType::BT_Additive;
								}

								// light setup
								SE::renderer::LightShaderBlockProxy* lightProxy = new SE::renderer::LightShaderBlockProxy();
								lightProxy->position = (*light)->getContainer()->getComponent<TransformComponent>()->transform.position;
								lightProxy->color = (*light)->color;
								lightProxy->direction = SE::core::math::Vec3<float>(1.0, 0.0, 0.0);
								lightProxy->power = (*light)->power;
								lightProxy->ambientPower = (*light)->ambientPower;

								command::CopyConstantBuffer* lightConstBuffer = mRenderer->pushRenderCommand<command::CopyConstantBuffer>();
								lightConstBuffer->bufferSize = sizeof(SE::renderer::LightShaderBlockProxy);
								lightConstBuffer->bufferData = lightProxy;
								lightConstBuffer->constantBuffer = forwardLightingShader.getConstantDefinition("LIGHT").handle;

								command::DrawIndexed* command = mRenderer->pushRenderCommand<command::DrawIndexed>();
								command->indexBuffer = mMeshManager->getResource((*mesh)->getMesh())->getIndexBuffer();
								command->vertexBuffer = mMeshManager->getResource((*mesh)->getMesh())->getVertexBuffer();
								command->indicesCount = mMeshManager->getResource((*mesh)->getMesh())->getIndicesCount();
								command->indicesOffset = 0;
							}
						}
					}
				}
			}
		}
	}
}