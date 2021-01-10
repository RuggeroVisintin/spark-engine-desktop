#ifndef __SHADOWSCENE_H__
#define __SHADOWSCENE_H__

#include <SparkEngine.h>
#include <ShaderBlocks.h>
#include <GFX/OpenGL/GLDevice.h>
#include <Parsers/obj/ObjParser.h>

#include <EntityComponentSystem/Entity.h>

#include <frontend/MaterialComponent.h>
#include <frontend/StaticMeshComponent.h>
#include <frontend/MaterialComponent.h>
#include <Transform/TransformComponent.h>

namespace SE
{
	namespace sandbox
	{
		class ShadowScene
		{
		public:
			ShadowScene(SE::engine::SparkEngine* engine,
				SE::platform::backend::GLDevice* device,
				const SE::engine::EnginePathsConfig& config)
				: mSparkEngine(engine)
				, mDevice(device)
			{
				initShaders(config);
				initGameObjects(config);
			}

		private:
			void initShaders(const SE::engine::EnginePathsConfig& config) {
				SE::platform::filesystem::OsFile* shadowVertFile = mSparkEngine->fileSystem.openFileRead("Forward/Shadowing.vertex.glsl", config.shadersKey);
				SE::platform::filesystem::OsFile* shadowFragFile = mSparkEngine->fileSystem.openFileRead("Forward/Shadowing.fragment.glsl", config.shadersKey);

				// shader resource loading
				SE::resource::Shader shadowShader;
				shadowShader.setFragmentSourceFromFile(shadowFragFile);
				shadowShader.setVertexSourceFromFile(shadowVertFile);

				// view constant definition setup
				SE::resource::Shader::ConstantDefinition shadowConstData;
				shadowConstData.name = "SHADOW";
				shadowConstData.size = sizeof(SE::renderer::ShadowShaderBlockProxy);

				shadowShader.addConstantData(shadowConstData);
				shadowShader.initGpuResources(mDevice);

				mSparkEngine->fileSystem.closeFile(shadowVertFile);
				mSparkEngine->fileSystem.closeFile(shadowFragFile);

				mSparkEngine->renderSystem.shadowMappingShader = shadowShader;
			}

			void initGameObjects(const SE::engine::EnginePathsConfig& config) {
				SE::platform::filesystem::OsFile* objFile = mSparkEngine->fileSystem.openFileRead("head.obj", config.meshesKey);

				// mesh resource loading
				SE::core::parser::text::wavefront::ObjParser objParser;
				SE::core::parser::text::wavefront::ObjMesh objMesh;

				objParser.readMesh(objMesh, objFile);
				mSparkEngine->fileSystem.closeFile(objFile);

				SE::resource::Mesh mesh = SE::resource::Mesh();
				mesh.keepDataCached = false;
				mesh.loadFromObj(objMesh, "head");
				mesh.initGpuResources(mDevice);

				// mesh reource mapping into MeshManager
				SE::resource::ResourceHandle meshHandle = mSparkEngine->meshManager.addResource(mesh, mesh.getName(), SE::resource::RMT_Dynamic);

				SE::engine::StaticMeshComponent* staticMesh = new SE::engine::StaticMeshComponent(meshHandle);
				SE::engine::TransformComponent* transform = new SE::engine::TransformComponent(SE::core::math::Transform<float>());

				SE::resource::Material tempMaterial;
				tempMaterial.params.diffuseColor = SE::core::math::Vec3<float>(1, 0, 0);
				tempMaterial.params.metalness = 0.5;
				tempMaterial.params.roughness = 0.5;
				tempMaterial.params.specularity = 0.5;

				SE::engine::MaterialComponent* materialComponent = new SE::engine::MaterialComponent(tempMaterial);

				SE::core::ecs::Entity* gameObject = new SE::core::ecs::Entity();
				gameObject->addComponent<SE::engine::StaticMeshComponent>(staticMesh);
				gameObject->addComponent<SE::engine::TransformComponent>(transform);
				gameObject->addComponent<SE::engine::MaterialComponent>(materialComponent);
				transform->transform.position = SE::core::math::Vec3<float>(0.0f, 0.7, -10.0f);
				transform->transform.scale3D = SE::core::math::Vec3<float>(2, 2, 2);

				SE::platform::filesystem::OsFile* planeFile = mSparkEngine->fileSystem.openFileRead("plane.obj", config.meshesKey);
				SE::core::parser::text::wavefront::ObjMesh planeObjMesh;

				objParser.readMesh(planeObjMesh, planeFile);
				mSparkEngine->fileSystem.closeFile(planeFile);

				SE::resource::Mesh planeMesh = SE::resource::Mesh();
				planeMesh.keepDataCached = false;
				planeMesh.loadFromObj(planeObjMesh, "plane");
				planeMesh.initGpuResources(mDevice);

				SE::resource::ResourceHandle planeMeshHandle = mSparkEngine->meshManager.addResource(planeMesh, planeMesh.getName(), SE::resource::RMT_Dynamic);

				SE::engine::StaticMeshComponent* planeStaticMesh = new SE::engine::StaticMeshComponent(planeMeshHandle);
				SE::engine::TransformComponent* planeTransform = new SE::engine::TransformComponent(SE::core::math::Transform<float>());

				SE::resource::Material planeMaterial;
				planeMaterial.params.diffuseColor = SE::core::math::Vec3<float>(1, 1, 1);

				SE::engine::MaterialComponent* planeMaterialComponent = new SE::engine::MaterialComponent(tempMaterial);

				SE::core::ecs::Entity* planeGameObject = new SE::core::ecs::Entity();
				planeGameObject->addComponent<SE::engine::StaticMeshComponent>(planeStaticMesh);
				planeGameObject->addComponent<SE::engine::TransformComponent>(planeTransform);
				planeGameObject->addComponent<SE::engine::MaterialComponent>(planeMaterialComponent);
				planeTransform->transform.position = SE::core::math::Vec3<float>(0.0f, 0.0f, -10.0f);

				mSparkEngine->renderSystem.registerComponent(planeStaticMesh);
				mSparkEngine->renderSystem.registerComponent(staticMesh);

			}

		private:
			SE::engine::SparkEngine*			mSparkEngine;
			SE::platform::backend::GLDevice*	mDevice;
		};
	}
}

#endif // !__SHADOWSCENE_H__
