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
#include <EntityComponentSystem/Entity.h>

#include <frontend\CameraComponent.h>
#include <frontend\LightComponent.h>
#include <frontend\StaticMeshComponent.h>

#include <Mesh\MeshLoader.h>
#include <Mesh/MeshResource.h>
#include <Shader/ShaderResource.h>
#include <Material/MaterialResource.h>
#include <Texture/TextureResource.h>

#include <Renderer.h>
#include <ShaderBlocks.h>

#include <SparkEngine.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int lCmdShow)
{
	// window creation
	Win32WindowGL window = Win32WindowGL(SE::platform::backend::GLContext::GLV_32, L"SparkEngine - while in dev");
	window.show();

	// engine configuration
	SE::engine::EnginePathsConfig config;
	if (!std::string(pCmdLine).empty()) {
		config.rootPath		= pCmdLine;
	} else{
		// used while debugging on my pc, change to debug on other pcs
		config.rootPath = "C:/Users/rugge/Documents/Visual Studio 2015/Projects/sparkengine_desktop/assets";
	}
	
	config.meshesFolder		= "Meshes";
	config.shadersFolder	= "Shaders";
	config.meshesKey		= "MESHES";
	config.shadersKey		= "SHADERS";

	// device creation
	SE::platform::backend::GLDevice* device = window.getGraphicsContext()->createGLDevice();

	// engine initialization
	SE::engine::SparkEngine sparkEngine = SE::engine::SparkEngine(device, config);

	// shader files opening
	SE::platform::filesystem::OsFile* vertFile = sparkEngine.fileSystem.openFileRead("BRDF_LambertCookTorrance.vertex.glsl", config.shadersKey);
	SE::platform::filesystem::OsFile* fragFile = sparkEngine.fileSystem.openFileRead("ForwardPixelPass.fragment.glsl", config.shadersKey);

	// shader resource loading
	SE::resource::Shader shader;
	shader.setFragmentSourceFromFile(fragFile);
	shader.setVertexSourceFromFile(vertFile);

	// view constant definition setup
	SE::resource::Shader::ConstantDefinition viewConstData;
	viewConstData.name = "VIEW";
	viewConstData.size = sizeof(SE::renderer::ViewShaderBlockProxy);

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
	shader.initGpuResources(device);

	// shader files closing
	sparkEngine.fileSystem.closeFile(vertFile);
	sparkEngine.fileSystem.closeFile(fragFile);

	// mesh file opening
	SE::platform::filesystem::OsFile* objFile = sparkEngine.fileSystem.openFileRead("MatTester.obj", config.meshesKey);

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

	// mesh components creation
	SE::engine::StaticMeshComponent staticMesh = SE::engine::StaticMeshComponent(meshHandle);
	SE::engine::TransformComponent transform = SE::engine::TransformComponent(SE::core::math::Transform<float>());

	// game object creation
	SE::core::ecs::Entity gameObject;
	gameObject.addComponent<SE::engine::StaticMeshComponent>(&staticMesh);
	gameObject.addComponent<SE::engine::TransformComponent>(&transform);
	transform.transform.position = SE::core::math::Vec3<float>(0.0f, -1.5f, 0.0f);
	transform.transform.scale3D = SE::core::math::Vec3<float>(0.12f, 0.12f, 0.12f);

	// camera components creation
	SE::engine::CameraComponent camera;
	SE::engine::TransformComponent cameraTransform;

	// camera object creation
	SE::core::ecs::Entity cameraObject;
	cameraObject.addComponent<SE::engine::CameraComponent>(&camera);
	cameraObject.addComponent<SE::engine::TransformComponent>(&cameraTransform);

	// background color settings
	camera.backgroundColor.setX(0.0);
	camera.backgroundColor.setY(0.0);
	camera.backgroundColor.setZ(0.0);

	cameraTransform.transform.position = SE::core::math::Vec3<float>(0.0f, 0.0f, -4.0f);
	camera.frustum = SE::core::math::Frustum<float>::createPerspective(SE::core::math::toRadians<float>(60.0f), 1360.0f/768.0f, 0.1f, 1000.0f);

	// light components creation
	SE::engine::LightComponent light;
	SE::engine::TransformComponent lightTransform;

	// light object creation
	SE::core::ecs::Entity lightObject;
	lightObject.addComponent<SE::engine::LightComponent>(&light);
	lightObject.addComponent<SE::engine::TransformComponent>(&lightTransform);

	light.color = SE::core::math::Vec3<float>(0.0f, 0.0f, 1.0f);
	light.ambientPower = 0.0f;
	light.power = 1.0f;
	lightTransform.transform.position.setX(-1);
	lightTransform.transform.position.setY(SE::core::math::toRadians(60.0f));
	lightTransform.transform.position.setZ(0);

	// light components creation
	SE::engine::LightComponent light2;
	SE::engine::TransformComponent lightTransform2;

	// light object creation
	SE::core::ecs::Entity lightObject2;
	lightObject2.addComponent<SE::engine::LightComponent>(&light2);
	lightObject2.addComponent<SE::engine::TransformComponent>(&lightTransform2);

	light2.color = SE::core::math::Vec3<float>(1.0f, 1.0f, 1.0f);
	light2.ambientPower = 0.00f;
	light2.power = 1.0f;
	lightTransform2.transform.position.setX(1);
	lightTransform2.transform.position.setY(SE::core::math::toRadians(90.0f));
	lightTransform2.transform.position.setZ(0);

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
	sparkEngine.renderSystem.registerComponent(&camera);
	sparkEngine.renderSystem.registerComponent(&staticMesh);
	//sparkEngine.renderSystem.registerComponent(&light);
	sparkEngine.renderSystem.registerComponent(&light2);
	sparkEngine.renderSystem.registerComponent(&light3);
	//sparkEngine.renderSystem.defaultMaterial.shaderProgram = shader;
	sparkEngine.renderSystem.forwardLightingShader = shader;

	//sparkEngine.renderSystem.defaultMaterial.params.diffuseColor = SE::core::math::Vec3<float>(1.0f, 0.878f, 0.741f);
	sparkEngine.renderSystem.defaultMaterial.params.diffuseColor = SE::core::math::Vec3<float>(1.0f, 0.0f, 0.0f);
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
			} else if (msg.message == WM_KEYDOWN) {
				switch (msg.wParam)
				{
				case VK_ADD:
					sparkEngine.renderSystem.defaultMaterial.params.specularity += 0.01f;
					if (sparkEngine.renderSystem.defaultMaterial.params.specularity > 1.0f) {
						sparkEngine.renderSystem.defaultMaterial.params.specularity = 1.0f;
					}
					break;
				case VK_SUBTRACT:
					sparkEngine.renderSystem.defaultMaterial.params.specularity -= 0.01f;
					if (sparkEngine.renderSystem.defaultMaterial.params.specularity < 0.0f) {
						sparkEngine.renderSystem.defaultMaterial.params.specularity = 0.0f;
					}

					break;
				case VK_MULTIPLY:
					sparkEngine.renderSystem.defaultMaterial.params.roughness += 0.01f;
					if (sparkEngine.renderSystem.defaultMaterial.params.roughness > 1.0f) {
						sparkEngine.renderSystem.defaultMaterial.params.roughness = 1.0f;
					}

					break;
				case VK_DIVIDE:
					sparkEngine.renderSystem.defaultMaterial.params.roughness -= 0.01f;
					if (sparkEngine.renderSystem.defaultMaterial.params.roughness < 0.0f) {
						sparkEngine.renderSystem.defaultMaterial.params.roughness = 0.0f;
					}

					break;
				}
			} else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		} else {

			if (rotate) {
				transform.transform.rotate(SE::core::math::Quat<float>(0.0f, SE::core::math::toRadians(0.01f) * delta, 0.0f, 1.0f));
			}

			sparkEngine.update(*window.getGraphicsContext());
			delta = timer.getElapsedMs();
		}
	}

	return msg.wParam;
}