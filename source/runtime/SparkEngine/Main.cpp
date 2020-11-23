#include <Windows.h>

#include <GFX\OpenGL\GLContext.h>
#include <Win32\Win32WindowGL.h>
#include <Renderer.h>
#include <Parsers/obj/ObjParser.h>

#include <math/Frustum.h>
#include <math/MathUtils.h>
#include <frontend/RenderSystem.h>

#include <FileSystem/FileSystem.h>
#include <FileSystem/File.h>
#include <Time/Win32/Win32HiResTimer.h>

#include <math/Quat.h>
#include <math/Transform.h>
#include <GameObjects/GameObjects.h>
#include <GameObjects/CameraEntity.h>
#include <EntityComponentSystem/Entity.h>

#include <frontend\CameraComponent.h>
#include <frontend\LightComponent.h>
#include <frontend\StaticMeshComponent.h>
#include <frontend\MaterialComponent.h>

#include <Mesh\MeshLoader.h>
#include <Mesh/MeshResource.h>
#include <Shader/ShaderResource.h>
#include <Material/MaterialResource.h>
#include <Texture/TextureResource.h>

#include <Renderer.h>
#include <ShaderBlocks.h>

#include <SparkEngine.h>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int lCmdShow)
{
	// window creation
	Win32WindowGL window = Win32WindowGL(SE::platform::backend::GLContext::GLV_32, L"SparkEngine - while in dev");
	window.show();

	// engine configuration
	SE::engine::EnginePathsConfig config;
	if (!std::string(pCmdLine).empty()) {
		config.rootPath = pCmdLine;
	} else {
		// used while debugging on my pc, change to debug on other pcs
		config.rootPath = "D:/Documenti/SparkEngine_Desktop/assets";
	}

	config.meshesFolder = "meshes";
	config.shadersFolder = "shaders";
	config.meshesKey = "MESHES";
	config.shadersKey = "SHADERS";

	// device creation
	SE::platform::backend::GLDevice* device = window.getGraphicsContext()->createGLDevice();

	// engine initialization
	SE::engine::SparkEngine sparkEngine = SE::engine::SparkEngine(device, config);

	// shader files opening
	SE::platform::filesystem::OsFile* vertFile = sparkEngine.fileSystem.openFileRead("ForwardVertexPass.vertex.glsl", config.shadersKey);
	SE::platform::filesystem::OsFile* fragFile = sparkEngine.fileSystem.openFileRead("ForwardPixelPass.fragment.glsl", config.shadersKey);

	// shader resource loading
	SE::resource::Shader shader;
	shader.setFragmentSourceFromFile(fragFile);
	shader.setVertexSourceFromFile(vertFile);

	// view constant definition setup
	SE::resource::Shader::ConstantDefinition viewConstData;
	viewConstData.name = "VIEW";
	viewConstData.size = sizeof(SE::renderer::ViewShaderBlockProxy);

	SE::resource::Shader::ConstantDefinition engineConstData;
	engineConstData.name = "ENGINE";
	engineConstData.size = sizeof(SE::renderer::EngineShaderBlockProxy);

	// material constant definition setup
	SE::resource::Shader::ConstantDefinition materialConstData;
	materialConstData.name = "MATERIAL";
	materialConstData.size = sizeof(SE::renderer::MaterialShaderBlockProxy);

	// light constant defitinition setup
	SE::resource::Shader::ConstantDefinition lightConstData;
	lightConstData.name = "LIGHT";
	lightConstData.size = sizeof(SE::renderer::LightShaderBlockProxy);

	// initialize shader gpu resources after constant definition addition
	shader.addConstantData(viewConstData);
	shader.addConstantData(materialConstData);
	shader.addConstantData(lightConstData);
	shader.addConstantData(engineConstData);
	shader.initGpuResources(device);

	// shader files closing
	sparkEngine.fileSystem.closeFile(vertFile);
	sparkEngine.fileSystem.closeFile(fragFile);

	// mesh file opening
	SE::platform::filesystem::OsFile* objFile = sparkEngine.fileSystem.openFileRead("Sphere.obj", config.meshesKey);

	// mesh resource loading
	SE::core::parser::text::wavefront::ObjParser objParser;
	SE::core::parser::text::wavefront::ObjMesh objMesh;

	objParser.readMesh(objMesh, objFile);
	sparkEngine.fileSystem.closeFile(objFile);

	SE::resource::Mesh mesh = SE::resource::Mesh();
	mesh.keepDataCached = false;
	mesh.loadFromObj(objMesh);
	mesh.initGpuResources(device);

	// mesh reource mapping into MeshManager
	SE::resource::ResourceHandle meshHandle = sparkEngine.meshManager.addResource(mesh, mesh.getName(), SE::resource::RMT_Dynamic);

	int rowCount = 0;
	int colCount = 0;

	// mesh components creation
	for (int i = 0; i < 7 * 7; i++) {
		SE::engine::StaticMeshComponent* staticMesh = new SE::engine::StaticMeshComponent(meshHandle);
		SE::engine::TransformComponent* transform = new SE::engine::TransformComponent(SE::core::math::Transform<float>());

		if ((i) % 7 == 0) {
			rowCount++;
		}

	
		SE::resource::Material tempMaterial;
		tempMaterial.params.diffuseColor = SE::core::math::Vec3<float>(1, 0, 0);
		tempMaterial.params.metalness = 0.5;
		tempMaterial.params.roughness = ((1.0f / 7.0f) * i - rowCount) + 1;
		tempMaterial.params.specularity = 0.5;

		SE::engine::MaterialComponent* materialComponent = new SE::engine::MaterialComponent(tempMaterial);



		// game object creation
		SE::core::ecs::Entity* gameObject = new SE::core::ecs::Entity();
		gameObject->addComponent<SE::engine::StaticMeshComponent>(staticMesh);
		gameObject->addComponent<SE::engine::TransformComponent>(transform);
		gameObject->addComponent<SE::engine::MaterialComponent>(materialComponent);
		transform->transform.position = SE::core::math::Vec3<float>((i % 7) * 0.35f, ((i) / 7) * -0.35f, -10.0f);
		transform->transform.scale3D = SE::core::math::Vec3<float>(0.12f, 0.12f, 0.12f);


		sparkEngine.renderSystem.registerComponent(staticMesh);

	}

	// camera object creation
	SE::engine::CameraEntity cameraObject;

	// light components creation
	SE::engine::LightComponent light;
	SE::engine::TransformComponent lightTransform = SE::engine::TransformComponent(SE::core::math::Transform<float>(0, 0, 1));

	// light object creation
	SE::core::ecs::Entity lightObject;
	lightObject.addComponent<SE::engine::LightComponent>(&light);
	lightObject.addComponent<SE::engine::TransformComponent>(&lightTransform);

	// light components creation
	SE::engine::LightComponent light2;
	SE::engine::TransformComponent lightTransform2 = SE::engine::TransformComponent(SE::core::math::Transform<float>(1, SE::core::math::toRadians(90.0f), 0));;

	// light object creation
	SE::core::ecs::Entity lightObject2;
	lightObject2.addComponent<SE::engine::LightComponent>(&light2);
	lightObject2.addComponent<SE::engine::TransformComponent>(&lightTransform2);

	// light components creation
	SE::engine::LightComponent light3;
	SE::engine::TransformComponent lightTransform3;

	// light object creation
	SE::core::ecs::Entity lightObject3;
	lightObject3.addComponent<SE::engine::LightComponent>(&light3);
	lightObject3.addComponent<SE::engine::TransformComponent>(&lightTransform3);

	light3.color = SE::core::math::Vec3<float>(1.0f, 1.0f, 1.0f);
	light3.ambientPower = 0.00f;
	light3.power = 1.0f;
	lightTransform3.transform.position.setX(0);
	lightTransform3.transform.position.setY(-1);
	lightTransform3.transform.position.setZ(0);

	// component registration
	sparkEngine.renderSystem.registerComponent(&cameraObject.camera);
	//sparkEngine.renderSystem.registerComponent(&staticMesh);
	sparkEngine.renderSystem.registerComponent(&light);
	sparkEngine.renderSystem.registerComponent(&light2);
	//sparkEngine.renderSystem.registerComponent(&light3);
	//sparkEngine.renderSystem.defaultMaterial.shaderProgram = shader;
	sparkEngine.renderSystem.forwardLightingShader = shader;

	//sparkEngine.renderSystem.defaultMaterial.params.diffuseColor = SE::core::math::Vec3<float>(1.0f, 0.878f, 0.741f);
	sparkEngine.renderSystem.defaultMaterial.params.diffuseColor = SE::core::math::Vec3<float>(1, 0, 0);
	//sparkEngine.renderSystem.defaultMaterial.params.diffuseColor = SE::core::math::Vec3<float>(0.94f, 0.72f, 0.63f);
	sparkEngine.renderSystem.defaultMaterial.params.metalness = 0.0f;
	sparkEngine.renderSystem.defaultMaterial.params.roughness = 0.5f;
	sparkEngine.renderSystem.defaultMaterial.params.specularity = 0.5f;

	bool rotate = false;
	SE::platform::time::Win32HiResTimer timer;
	double delta;
	timer.start();

	MSG msg;
	bool running = true;

	while (running) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				running = false;
			else if (msg.message == WM_KEYUP) {
				switch (msg.wParam)
				{
					// to rotate stop object rotation
				case 0x52: rotate = !rotate;
					break;
				}
			}
			else if (msg.message == WM_KEYDOWN) {
				SE::core::math::Quat<float> rotation;


				switch (msg.wParam)
				{
				case VK_F1:
					sparkEngine.renderSystem.defaultMaterial.params.specularity += 0.01f;
					if (sparkEngine.renderSystem.defaultMaterial.params.specularity > 1.0f) {
						sparkEngine.renderSystem.defaultMaterial.params.specularity = 1.0f;
					}
					break;
				case VK_F2:
					sparkEngine.renderSystem.defaultMaterial.params.specularity -= 0.01f;
					if (sparkEngine.renderSystem.defaultMaterial.params.specularity < 0.0f) {
						sparkEngine.renderSystem.defaultMaterial.params.specularity = 0.0f;
					}

					break;
				case VK_F3:
					sparkEngine.renderSystem.defaultMaterial.params.roughness += 0.01f;
					if (sparkEngine.renderSystem.defaultMaterial.params.roughness > 1.0f) {
						sparkEngine.renderSystem.defaultMaterial.params.roughness = 1.0f;
					}

					break;
				case VK_F4:
					sparkEngine.renderSystem.defaultMaterial.params.roughness -= 0.01f;
					if (sparkEngine.renderSystem.defaultMaterial.params.roughness < 0.0f) {
						sparkEngine.renderSystem.defaultMaterial.params.roughness = 0.0f;
					}

					break;
				}

				if (msg.wParam == 0x57) {
					cameraObject.getComponent<SE::engine::TransformComponent>()->transform.translate(cameraObject.getComponent<SE::engine::TransformComponent>()->transform.getForward() * 0.1f);
				}

				if (msg.wParam == 0x53) {
					cameraObject.getComponent<SE::engine::TransformComponent>()->transform.translate(cameraObject.getComponent<SE::engine::TransformComponent>()->transform.getForward() * -0.1f);
				}

				if (msg.wParam == VK_RIGHT) {
					rotation.setRotationAboutY(-0.01f);
					cameraObject.getComponent<SE::engine::TransformComponent>()->transform.rotate(rotation);
				}

				if (msg.wParam == VK_LEFT) {
					rotation.setRotationAboutY(0.01f);
					cameraObject.getComponent<SE::engine::TransformComponent>()->transform.rotate(rotation);
				}

				if (msg.wParam == VK_SPACE) {
					cameraObject.getComponent<SE::engine::TransformComponent>()->transform.translate(cameraObject.getComponent<SE::engine::TransformComponent>()->transform.getUp() * 0.01f);
				}

				if (msg.wParam == 17) {
					cameraObject.getComponent<SE::engine::TransformComponent>()->transform.translate(cameraObject.getComponent<SE::engine::TransformComponent>()->transform.getUp() * -0.01f);
				}
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {
			if (rotate) {
				//transform.transform.rotate(SE::core::math::Quat<float>(0.0f, SE::core::math::toRadians(0.01f) * delta, 0.0f, 1.0f));
			}

			delta = timer.getElapsedMs();
			sparkEngine.update(*window.getGraphicsContext(), delta);
		}
	}

	return msg.wParam;
}